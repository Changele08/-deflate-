#include "../headerfile/dawn.hpp"
#include "../headerfile/head.hpp"
using namespace std;
void tryout(short &num,binarychar &bc,FILE *file,ull &change)
{
	returnif(num!=8,);
	hufchar hc=binarychar2hufchar(bc);
	fwrite(&hc,1,1,file);
	memset(&bc.binary,0,8);
	num=0;
	change++;
}
void halffile1(char *inf,char *outf,char *outf2)
{
	ull filesize=getfilesize(inf);
	FILE *rd=fopen(inf,"rb"),*wt=fopen(outf,"wb"),*wb=fopen(outf2,"wb");
	U char ch;
	for(int i=0;i<filesize/2;i++)
	{
		fread(&ch,1,1,rd);
		fwrite(&ch,1,1,wt);
	}
	fclose(wt);
	while(fread(&ch,1,1,rd))
	  fwrite(&ch,1,1,wb);
	fclose(wb);
	fclose(rd);
	return;
}
void halffile2(char *inf,char *outf,char *outf2)
{
	ull filesize=getfilesize(inf);
	FILE *rd=fopen(inf,"rb"),*wt=fopen(outf,"wb"),*wb=fopen(outf2,"wb");
	U char ch[4];
	for(int i=0;i<filesize/2;i+=4)
	{
		fread(ch,1,4,rd);
		fwrite(ch,1,4,wt);
	}
	fclose(wt);
	while(fread(ch,1,4,rd))
	{
		fwrite(ch,1,4,wb);
		ch[0]=ch[1]=ch[2]=ch[3]=0;
	}
	fclose(wb);
	fclose(rd);
	return;
}
short mgfile(vector<fileinfo> files,string outfile,bool cover)
{
	returnif(!cover&&checkfile((char *)outfile.c_str()),OUTFILEALREADY);
	FILE *wt=fopen(outfile.c_str(),"wb");
	for(int i=0;i<files.size();i++)
	{
		FILE *rd=fopen(files[i].filename.c_str(),"rb");
		returnif(rd==NULL,INFILENOTFOUND);
		U char ch;
		while(fread(&ch,1,1,rd))
		  fwrite(&ch,1,1,wt);
		fclose(rd);
	}
	fclose(wt);
	return OK;
}
void delfile(string filename)
{
	string cmd="@del /F /Q "+filename;
	system(cmd.c_str());
	return ;
}
void dellist(string *filelist,int siz)
{
	for(int i=0;i<siz;i++)
	  if(checkfile(Cc filelist[i].c_str()))
	    delfile(filelist[i]);
}
bool checklist(string *filelist,int size)
{
	bool ono=true;
	for(int i=0;i<size;i++)
	  if(checkfile(Cc filelist[i].c_str()))
	  {
	  	  cout<<"以下文件将会在压缩中作为临时文件被覆盖并删除："<<filelist[i]<<' '<<"如果该文件是您所需要的文件，请使它和本软件不处于同一目录。"<<endl;
	  	  ono=false;
	  }
	return ono;
}
ull freadvlq(FILE *rd)
{
	U char ch[8],c=0xff,p=0;
	while((c&0x80))//最高位，vlq标志
	{
		fread(&c,1,1,rd);
		ch[p++]=c;
	} 
	return vlq2int(ch);
}
int fwritevlq(FILE *wt,ull vlq)
{
	U char ch[8];
	int sz=int2vlq(vlq,ch);
	fwrite(ch,1,sz,wt);
	return sz;
} 
void copyFILE(FILE *rd,char *out,ull sz)
{
	FILE *wt=fopen(out,"wb");
	for(ull i=0;i<sz;i++)
	{
		U char ch;
		fread(&ch,1,1,rd);
		fwrite(&ch,1,1,wt);
	}
	fclose(wt);
	return;
}
short split(FILE *rd,U short head,string password)
{
	ull ullfilesize[5]={freadvlq(rd),(gethl(head))?freadvlq(rd):ullfilesize[1]=0,freadvlq(rd),(getfc(head))?freadvlq(rd):ullfilesize[3]=0,freadvlq(rd)};
	U char ch;
	FILE *wt=fopen("dawn.main","wb");
	for(;fread(&ch,1,1,rd);fwrite(&ch,1,1,wt));
	fclose(wt);
	if(getmp(head))
	{
		U short res=opsfiledecode(Cc"dawn.main",Cc"dawn.m",password,1);
		returnif(res!=OK,res);
		returnif(!copyfile(Cc"dawn.m",Cc"dawn.main",1),OUTFILEALREADY);
	} 
	fclose(rd);
	rd=fopen("dawn.main","rb");
	if(gethl(head))
	{
		copyFILE(rd,Cc"dawn1.sh",ullfilesize[0]);
		returnif(shhuffmanfiledecompress(Cc"dawn1.sh",Cc"dawn1.lile",(head&8)>>3,1)!=OK,COMPRESSFILEBREAK);
		copyFILE(rd,Cc"dawn2.sh",ullfilesize[1]);
		returnif(shhuffmanfiledecompress(Cc"dawn2.sh",Cc"dawn2.lile",(head&4)>>2,1)!=OK,COMPRESSFILEBREAK);
		returnif(!mergerfiles(Cc"dawn1.lile",Cc"dawn2.lile",Cc"dawn.lile",1),MERGERFILESERROR);
	}
	else
	{
		copyFILE(rd,Cc"dawn.sh",ullfilesize[0]);
		shhuffmanfiledecompress(Cc"dawn.sh",Cc"dawn.lile",(head&8)>>3,1);
	}
	if(getfc(head))
	{
		copyFILE(rd,Cc"distance1.huf",ullfilesize[2]);
		copyFILE(rd,Cc"distance2.huf",ullfilesize[3]);
		returnif(huffmanfiledecompress("distance1.huf","distance1.vlq",(head&2)>>1,1)!=OK,COMPRESSFILEBREAK);
		returnif(huffmanfiledecompress("distance2.huf","distance2.vlq",head&1,1)!=OK,COMPRESSFILEBREAK);
		returnif(!mergerfiles(Cc"distance1.vlq",Cc"distance2.vlq",Cc"distance.tmp",1),MERGERFILESERROR);
	}
	else
	{
		copyFILE(rd,Cc"distance.huf",ullfilesize[2]);
		returnif(huffmanfiledecompress("distance.huf","distance.tmp",(head&2)>>1,1)!=OK,COMPRESSFILEBREAK);
	}
	wt=fopen("dawn.eta","wb");
	for(;fread(&ch,1,1,rd);fwrite(&ch,1,1,wt));
	fclose(wt);
	fclose(rd);
	return OK;
}
