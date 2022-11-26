#include "../headerfile/dawn.hpp"//V22.04.10
using namespace std;
struct crlcnode
{
	char ch;
	U char cnt;
};
short crlc(char *in,char *out,int mod,bool huf,bool coverout=true)
{
	if(!checkfile(in))
	  return INFILENOTFOUND;
	if(checkfile(out)&&!coverout)
	  return OUTFILEALREADY;
	if(mod==0)//compress
	{
		string outf=out;
		addkzm(outf,".dwn");
		out=Cc outf.c_str();
		FILE *rd=fopen(in,"rb"),*wb=fopen("sign.tmp","wb"),*wt=fopen("body.tmp","wb");
		if(wb==NULL||wt==NULL)
		  return OUTFILEALREADY;
		ull signsz=0;
		binarychar bc;
		memset(&bc.binary,0,8);
		short num=0;
		char ch,last;
		int n=fread(&ch,1,1,rd);
		crlcnode rlc;
		rlc.ch=last=ch;
		rlc.cnt=0;
		while(n)
		{
			if(last==ch&&rlc.cnt<255)
			  rlc.cnt++;
			else
			{
				if(rlc.cnt<=2)
				  for(int i=0;i<rlc.cnt;i++)
				  {
				  	  fwrite(&rlc.ch,1,1,wt);
					  bc.binary[num++]=0;
					  tryout(num,bc,wb,signsz);
				  }
				else
				{
					fwrite(&rlc,2,1,wt);
					bc.binary[num++]=1;
					tryout(num,bc,wb,signsz);
				}
				last=ch;
				rlc.ch=ch;
				rlc.cnt=1;
			}
			n=fread(&ch,1,1,rd);
		}
		if(rlc.cnt<=2)
		{
			for(int i=0;i<rlc.cnt;i++)
			{
				fwrite(&rlc.ch,1,1,wt);
				bc.binary[num++]=0;
				tryout(num,bc,wb,signsz);
			}
		}
		else
		{
			fwrite(&rlc,2,1,wt);
			bc.binary[num++]=1;
			tryout(num,bc,wb,signsz);
		}
		if(num!=0)
		{
			num=8;
			tryout(num,bc,wb,signsz);
		}
		fclose(wb);
		fclose(rd);
		fclose(wt);
		ull nfs=0,srcfs=getfilesize((char *)"sign.tmp");
		bool is16,havhuf=true;
		huffmanfilecompress("sign.tmp","cpsg.tmp",nfs,is16,1);
		if(nfs>=srcfs||!huf)
		{
			havhuf=false;
			rd=fopen("sign.tmp","rb");
			wt=fopen("cpsg.tmp","wb");
			U char ch;
			for(;fread(&ch,1,1,rd);fwrite(&ch,1,1,wt));
			fclose(rd);
			fclose(wt);
			nfs=srcfs;
		} 
		wt=fopen("headinfo.tmp","wb");
		U char filetype=3;
		fwrite(&filetype,1,1,wt);
		is16=(is16)?1:0;
		fwrite(&is16,1,1,wt);
		fwrite(&havhuf,1,1,wt);
		fwritevlq(wt,nfs);
		fclose(wt);
		returnif(!mergerfiles(Cc"headinfo.tmp",Cc"cpsg.tmp",Cc"tmp.tmp",1),MERGERFILESERROR);
		returnif(!mergerfiles(Cc"tmp.tmp",Cc"body.tmp",out,1),MERGERFILESERROR);
	}
	if(mod==1)
	{
		FILE *rd=fopen(in,"rb"),*wt=fopen(out,"wb");
		if(rd==NULL)
		  return INFILENOTFOUND;
		U char filetype;
		fread(&filetype,1,1,rd);
		if(filetype!=3)
		  return COMPRESSFILEBREAK;
		bool is16,havhuf;
		fread(&is16,1,1,rd);
		fread(&havhuf,1,1,rd);
		ull signsize=freadvlq(rd);
		copyFILE(rd,Cc"cpsg.tmp",signsize);
		if(havhuf)
		  huffmanfiledecompress("cpsg.tmp","sign.tmp",is16,1);
		else
		  copyfile(Cc"cpsg.tmp",Cc"sign.tmp",1);
		FILE *wb=fopen("sign.tmp","rb");
		char ch;
		crlcnode rlc;
		hufchar hc;
		fread(&hc,1,1,wb);
		short num=0;
		binarychar bc=hufchar2binarychar(hc);
		while(1)
		{
			if(!bc.binary[num++])
			{
				if(!fread(&ch,1,1,rd))
				  break;
				fwrite(&ch,1,1,wt);
			}
			else
			{
				if(!fread(&rlc,2,1,rd))
				  break;
				while(rlc.cnt--)
				  fwrite(&rlc.ch,1,1,wt);
			}
			if(num==8)
			{
				fread(&hc,1,1,wb);
				num=0;
				bc=hufchar2binarychar(hc);
			}
		}
		fclose(rd);
		fclose(wb);
		fclose(wt);
	}
	system("del *.tmp");
	return OK;
}
