#include "../headerfile/head.hpp"
#include "../headerfile/devfunctionlibrary/devfunctionlibrary.hpp" //V22.08.15
#include "../headerfile/dawn.hpp"
using namespace std;
ull pow256[8]={0,256,65536,16777216,4294967296}; 
U int lilemap[35]={3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258,0xffff},lileeta[35]={0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0},dstmap[70],dsteta[70],*mtf;//mtf:存储最近最常用的32个distance 
binarychar lengtheta,distanceeta;
short lgbcp=0,dsbcp=0;
ull lls,ld;
struct node
{
	U int num;
	U char ch;
}; 
bool nodecmp(node a,node b)
{
	return a.num>b.num;
}
void outputablock(U I distance,U I length,FILE *wt,binarychar &bc,short &num,FILE *wbs,FILE *w,U I mtfsz,bool automtf)//wt:dawn.lile&dst2 wbs=dawn.eta w=ds1
{
	if(distance==0)//length中存放着literal
	{
		length&=0xff;
		fwrite(&length,2,1,wt);//此时wbs为无用参数 
	}
	else//length中是len 
	{
		lls=length;
		ld=distance;
		U I i;
		for(i=0;length>=lilemap[i+1];i++);
		U I ti=i+256; 
		fwrite(&ti,2,1,wt);
		hufchar tmp=(U char)length-lilemap[i];
		binarychar bt=hufchar2binarychar(tmp);
		for(int j=0;j<lileeta[i];j++)
		{
			ull aas=0;//无用的变量，只是为了凑参数 
			lengtheta.binary[lgbcp++]=bt.binary[j+(8-lileeta[i])];
			tryout(lgbcp,lengtheta,wbs,aas);
		}
		for(i=0;i<mtfsz;i++)
		  if(distance==mtf[i])//mtf算法，由于mtfsz=ews所以不可能找不到 
		  {
		  	  U I k; 
		  	  i++;
		  	  for(k=0;i>=dstmap[k+1];k++);
		  	  fwrite(&k,1,1,w);
		  	  U I tmp=i-dstmap[k];
		  	  binaryint bt=hufint2binaryint(tmp);
		  	  for(int j=0;j<dsteta[k];j++)
			  {
				  ull aas=0;//无用的变量，只是为了凑参数 
				  lengtheta.binary[lgbcp++]=bt.binary[j+(32-dsteta[k])];
				  tryout(lgbcp,lengtheta,wbs,aas); 
			  }
			  i--;
			  for(int j=i;j>0;j--)
			    mtf[j]=mtf[j-1];
			  mtf[0]=distance;
			  break; 
		  }
	}
}
void longest(char *readbuf,U I n,vector<U I> *wherelist,int i,int lessthan,U I &dstc,U I &lgth,U I fast,U I easywindowsize)//fast:1~3
{
	dstc=lgth=0;
	if(fast==1)
	{
		returnif(wherelist[(U I)((U char)readbuf[i])].size()==0,);//返回值是void，所以第二个参数不填 
		U I last=wherelist[(U I)((U char)readbuf[i])][wherelist[(U I)((U char)readbuf[i])].size()-1];
		for(U I k=i;readbuf[k]==readbuf[last++]&&k<n&&k-i<=lessthan;k++);
		lgth=last-1-wherelist[(U I)((U char)readbuf[i])][wherelist[(U I)((U char)readbuf[i])].size()-1];
		dstc=wherelist[(U I)((U char)readbuf[i])][wherelist[(U I)((U char)readbuf[i])].size()-1];
		return;
	}
	while(wherelist[(U I)((U char)readbuf[i])].size()>0&&(i-wherelist[(U I)((U char)readbuf[i])][0])>=easywindowsize)
	  wherelist[(U I)((U char)readbuf[i])].erase(wherelist[(U I)((U char)readbuf[i])].begin());
	for(U I j=0;j<wherelist[(U I)((U char)readbuf[i])].size();j++) 
	{
		U I last=wherelist[(U I)((U char)readbuf[i])][j];
		for(U I k=i;readbuf[k]==readbuf[last++]&&k<n&&k-i<=lessthan;k++);
		if(last-1-wherelist[(U I)((U char)readbuf[i])][j]>=lgth)
		{
			lgth=last-1-wherelist[(U I)((U char)readbuf[i])][j];
			dstc=wherelist[(U I)((U char)readbuf[i])][j];
		}
		returnif(fast==2&&lgth>=3,); 
		if(lgth>lessthan)
	      lgth=lessthan; 
	}
	return;
}
short cprs(char *inf,char *outf,U I dsize,bool usehuffman,bool mp,string password,ll jmsz,U I fast,U I easywindowsize,bool automtf,U I mtfsize)//compresskernel
{
	mtf=new U I[mtfsize];
	for(int i=0;i<mtfsize;i++)
	  mtf[i]=i+1;
	char *readbuf=new char[dsize+5];
	short morethan=3,lessthan=258;	  
	FILE *rd=fopen(inf,"rb"),*wt=fopen("dawn.lile","wb"),*wb=fopen("distance.tmp","wb"),*w=fopen("dawn.eta","wb");
	returnif(wt==NULL||wb==NULL||w==NULL,OUTFILECANTOPEN);
	memset(readbuf,0,dsize+5);
	int n=fread(readbuf,1,dsize,rd);
	readbuf[n]='\0';
	short num=0;
	binarychar bc;
	memset(&bc.binary,0,8);
	while(n)
	{
		vector<U I> wherelist[256];
		if(n<morethan)
		{
			for(int i=0;i<n;i++)
			  outputablock(0,readbuf[i],wt,bc,num,w,wb,mtfsize,automtf);
			break;
		}
		U I laststart=0,lastlen=0,start=0,len=0;
		bool ard=false;
		for(int i=0;i<n;i++)
		{
			laststart=start;
			lastlen=len;
			longest(readbuf,n,wherelist,i,lessthan,start,len,fast,easywindowsize);
			wherelist[(U I)((U char)readbuf[i])].push_back(i);
			if(lastlen>=morethan&&len<=lastlen)//上一次匹配足够好
			{
				for(int j=1;j<lastlen;j++)
				  wherelist[(U I)((U char)readbuf[j+i-1])].push_back(j+i-1);
				outputablock(i-laststart-1,lastlen,wt,bc,num,w,wb,mtfsize,automtf);
				i+=lastlen-2;
				len=0;
				ard=false;
			}
			else
			  if(ard)//ard==true:不是开始或是上一个为dstc+lgth压缩串 
			  	outputablock(0,readbuf[i-1],wt,bc,num,w,wb,mtfsize,automtf);//上一次的匹配并不是那么好，将上一个匹配的首个字符输出，并将第二个字符作为首位并继续匹配 
			  else
			    ard=true;  
		}
		if(ard)//最后有没输出的
		  outputablock(0,readbuf[n-1],wt,bc,num,w,wb,mtfsize,automtf);
		n=fread(readbuf,1,dsize,rd);
		readbuf[n]='\0';
	}
	if(lgbcp!=0)
	{
		lgbcp=8;
		ull aas;
		tryout(lgbcp,lengtheta,w,aas);
	}
	delete[] readbuf; 
	fclose(rd);
	fclose(wt);
	fclose(w);
	fclose(wb);
	U short head=0;
	bool b1,b2,b3;
	vector<fileinfo> gethfhd;   
	ull dawnsize=0,dawns2,dawntmp,distc=0,distc2=0;
	halffile2(Cc"dawn.lile",Cc"dawn1.lile",Cc"dawn2.lile");
	shhuffmanfilecompress(Cc"dawn.lile",Cc"dawn.sh",dawnsize,b1,1);//铁定比不压缩小，因为都是0~285的数（只要9bit)，存储时用了2byte(16bit)，产生浪费 
	shhuffmanfilecompress(Cc"dawn1.lile",Cc"dawn1.sh",dawns2,b2,1);
	shhuffmanfilecompress(Cc"dawn2.lile",Cc"dawn2.sh",dawntmp,b3,1);
	dawns2+=dawntmp;
	sethl(!(dawns2>dawnsize),head);
	head|=(dawns2>dawnsize)?(b1<<3):(b2<<3);
	fileinfo file;
	if(dawns2>dawnsize)
	{
		file.filename="dawn.sh";
		file.size=dawnsize;
		gethfhd.push_back(file);
	}
	else
	{
		head|=b3<<2;
		file.filename="dawn1.sh";
		file.size=dawns2-dawntmp;
		gethfhd.push_back(file);
		file.filename="dawn2.sh";
		file.size=dawntmp;
		gethfhd.push_back(file);
	}
	halffile1(Cc"distance.tmp",Cc"distance1.tmp",Cc"distance2.tmp");
	huffmanfilecompress(Cc"distance.tmp",Cc"distance.huf",distc,b1,1);
	huffmanfilecompress(Cc"distance1.tmp",Cc"distance1.huf",distc2,b2,1);
	huffmanfilecompress(Cc"distance2.tmp",Cc"distance2.huf",dawntmp,b3,1);
	distc2+=dawntmp;
	setfc(!(distc2>distc),head);
	head|=(distc2>distc)?(b1<<1):(b2<<1);
	if(distc2>distc)            
	{
		file.filename="distance.huf";
		file.size=distc;
		gethfhd.push_back(file);
	}
	else
	{
		head|=b3;
		file.filename="distance1.huf";
		file.size=distc2-dawntmp;
		gethfhd.push_back(file);
		file.filename="distance2.huf";
		file.size=dawntmp; 
		gethfhd.push_back(file);
	}
	file.filename="dawn.eta";
	file.size=getfilesize(Cc"dawn.eta");
	gethfhd.push_back(file); 
	FILE *wrt=fopen("dawnhead.tmp","wb");
	char ch[4]={"CZL"};
	fwrite(ch,1,3,wrt);
	U char filetype=0;//dawn 
	fwrite(&filetype,1,1,wrt);
	setmp(mp,head);
	setvers(9,head);//压缩文件版本8，非算法版本8
	fwrite(&head,2,1,wrt); 
	fwritevlq(wrt,dsize);
	fwritevlq(wrt,jmsz);
	fwritevlq(wrt,mtfsize);
	for(int i=0;i<gethfhd.size();i++)//顺序依次是lilemain和distance+lileeta 
	  fwritevlq(wrt,gethfhd[i].size);
	fclose(wt);
	fclose(wb);
	fclose(w);
	fclose(wrt);
	returnif(mgfile(gethfhd,"dawn.main",1)!=OK,MERGERFILESERROR);
	if(mp)
	{
		ull tmp;//凑参数用的 
		U short res=opsfileencode("dawn.main","dawn.ops",password,tmp,1);
		returnif(res!=OK,res);
		returnif(!mergerfiles(Cc"dawnhead.tmp",Cc"dawn.ops",outf,1),MERGERFILESERROR);
		delfile("dawn.ops");
 	}
 	else
	  returnif(!mergerfiles(Cc"dawnhead.tmp",Cc"dawn.main",outf,1),MERGERFILESERROR);
	return COMPRESSOK;
}
short dawncompress(char *inf,char *of,unsigned int dsize,bool cover,bool usehuffman,bool mp,bool ty,string password,ll jmsz,U I fast,U I easywindowsize,U I mtfsize,bool automtf,bool debug)
{
	string delflist[17]={"dawn.eta","dawn.sh","dawn1.sh","dawn2.sh","dawn.lile","dawn1.lile","dawn2.lile","distance.tmp","distance1.tmp","distance2.tmp","distance.huf","distance1.huf","distance2.huf","dawnhead.tmp","dawn.main","dst.tmp","bag.tmps"};
	dsize=(U I)max((U I)min(dsize,(U I)400000000),(U I)17);//17byte<=dsize<=4GB
	if(!debug)
	  returnif(!checklist(delflist,16),OUTFILEALREADY);
	returnif(!checkfile(inf),INFILENOTFOUND);
	returnif(checkfile(of)&&!cover,OUTFILEALREADY);
	if(!easywindowsize)//==0
	  easywindowsize=dsize;
	U int eq=5,etbs=1;
	for(int i=4;i+1<=64;i+=2)
	{
		dsteta[i]=etbs;
		dsteta[i+1]=etbs;
		dstmap[i]=eq;
		dstmap[i+1]=eq+pow(2,etbs);
		eq+=pow(2,etbs)*2;
		etbs++;
	}
	dstmap[0]=1;
	dstmap[1]=2;
	dstmap[2]=3;
	dstmap[3]=4;
	dsteta[0]=dsteta[1]=dsteta[2]=dsteta[3]=0;
	dstmap[64]--;//=maxvvalue,0xffffffffffffffff
	short res=cprs(inf,of,dsize,usehuffman,mp,password,jmsz,fast,easywindowsize,automtf,mtfsize);
	if(!debug)
	  dellist(delflist,17);
	return res; 
}
short dcprs(char *outf,U I dsize,U I mtfsize)
{
	mtf=new U I[mtfsize];
	for(int i=0;i<mtfsize;i++)
	  mtf[i]=i+1; 
	FILE *rd=fopen("dawn.lile","rb"),*rb=fopen("distance.tmp","rb"),*r=fopen("dawn.eta","rb"),*wt=fopen(outf,"wb");
	U short ch,p=0;
	ull dp=0;//dsize p
	U char *buf=new U char[dsize];
	hufchar hc;
	binarychar bc;
	fread(&hc,1,1,r);
	bc=hufchar2binarychar(hc);
	while(fread(&ch,2,1,rd))
	{
		if(ch<256)//literal
		{
			fwrite(&ch,1,1,wt);
			buf[dp++]=ch;
		}
		else//length
		{
			ch-=256;
			U int add=0;
			for(int i=0;i<lileeta[ch];i++)//读取lgth的eta 
			{
				add=(add<<1)+bc.binary[p++];
				if(p==8)
				{
					p=0;
					fread(&hc,1,1,r);
					bc=hufchar2binarychar(hc);
				}
			}
			U I len=lilemap[ch]+add,dstc=0;
			ch=add=0;
			fread(&ch,1,1,rb);
			for(int i=0;i<dsteta[ch];i++)//读取dstc的eta 
			{
				add=(add<<1)+bc.binary[p++];
				if(p==8)
				{
					p=0;
					fread(&hc,1,1,r);
					bc=hufchar2binarychar(hc);
				}
			}
			dstc=mtf[dstmap[ch]+add-1];
			for(int j=dstmap[ch]+add-1;j>0;j--)
		  	  mtf[j]=mtf[j-1];
		  	mtf[0]=dstc;
		  	if(dstc>dp||dp+len>=dsize+10)
			{
				cout<<"jump(字典单词跳转值)："<<dstc<<endl<<"length(单词长度）："<<len<<endl<<"当前字典长："<<dp<<endl<<"错误：跳转值超过字典或是单词长度过长，文件损坏。"<<endl<<"建议：密码错误？"<<endl; 
				fclose(rd);
				fclose(wt);
				fclose(rb);
				fclose(r);
				return WRONGPASSWORD;
			} 
			while(len--)//len次
			{
				buf[dp]=buf[dp-dstc];
				fwrite(&buf[dp++],1,1,wt);
			}
		}
		if(dp>=dsize)
		  dp=0;//不需要对buf清空，因为接下来的内容会覆盖掉 
	}
	delete[] buf;
	fclose(rd);
	fclose(rb);
	fclose(r);
	fclose(wt);
	return OK;
}
short dawndecompress(char *inf,char *outf,bool cover,string password,bool debug)
{
	string delflist[15]={"dawn.main","dawn.m","dawn1.sh","dawn2.sh","dawn.sh","dawn1.lile","dawn2.lile","dawn.lile","distance1.huf","distance2.huf","distance1.vlq","distance2.vlq","distance.huf","distance.tmp","dawn.eta"};
	if(!debug)
	  returnif(!checklist(delflist,15),OUTFILEALREADY);
	returnif(!checkfile(inf),INFILENOTFOUND);
	returnif(checkfile(outf)&&!cover,OUTFILEALREADY);
	U int eq=5,etbs=1;
	for(int i=4;i+1<=64;i+=2)
	{
		dsteta[i]=etbs;
		dsteta[i+1]=etbs;
		dstmap[i]=eq;
		dstmap[i+1]=eq+pow(2,etbs);
		eq+=pow(2,etbs)*2;
		etbs++;
	}
	dstmap[0]=1;
	dstmap[1]=2;
	dstmap[2]=3;
	dstmap[3]=4;
	dsteta[0]=dsteta[1]=dsteta[2]=dsteta[3]=0;
	dstmap[64]--;//=maxvvalue,0xffffffffffffffff
	FILE *rd=fopen(inf,"rb");
	char sign[4];
	fread(sign,3,1,rd);
	sign[3]='\0';
	returnif(strcmp(sign,"CZL"),COMPRESSFILEBREAK);
	U char type;
	fread(&type,1,1,rd);
	returnif(type!=0,COMPRESSFILEBREAK);//不是dawn文件
	U short head;
	fread(&head,2,1,rd);
	returnif(getvers(head)>9,VTL);//version too low 
	U I dsize=freadvlq(rd),tmp=freadvlq(rd),mtfsize=freadvlq(rd);//tmp:文件列表的大小，在getlist中只需要解压tmp大小的部分就可以获取文件列表，但是在全解压当中无用，故跳过 
	U short res=split(rd,head,password);
	returnif(res!=OK,res);
	res=dcprs(outf,dsize,mtfsize);
	if(!debug)
	  dellist(delflist,15);
	return res;
} 
short getlist(char *input,vector<string> &files,string password)
{
	string delflist[16]={"dawn.main","dawn.m","dawn1.sh","dawn2.sh","dawn.sh","dawn1.lile","dawn2.lile","dawn.lile","distance1.huf","distance2.huf","distance1.vlq","distance2.vlq","distance.huf","distance.tmp","dawn.eta","lst.tmp"};
	returnif(!checklist(delflist,16),OUTFILEALREADY);
	returnif(!checkfile(input),INFILENOTFOUND);
	U int eq=5,etbs=1;
	for(int i=4;i+1<=64;i+=2)
	{
		dsteta[i]=etbs;
		dsteta[i+1]=etbs;
		dstmap[i]=eq;
		dstmap[i+1]=eq+pow(2,etbs);
		eq+=pow(2,etbs)*2;
		etbs++;
	}
	dstmap[0]=1;
	dstmap[1]=2;
	dstmap[2]=3;
	dstmap[3]=4;
	dsteta[0]=dsteta[1]=dsteta[2]=dsteta[3]=0;
	dstmap[64]--;//=maxvvalue,0xffffffffffffffff
	FILE *rd=fopen(input,"rb");
	char sign[4];
	fread(sign,3,1,rd);
	sign[3]='\0';
	returnif(strcmp(sign,"CZL"),COMPRESSFILEBREAK);
	U char type;
	fread(&type,1,1,rd);
	if(type!=0)
	  return COMPRESSFILEBREAK;
	U short head;
	fread(&head,2,1,rd);
	returnif(getvers(head)>9,VTL);
	U I dsize=freadvlq(rd),listfilesize=freadvlq(rd),mtfsize=freadvlq(rd);
	U short res=split(rd,head,password);
	returnif(res!=OK,res);
	mtf=new U I[mtfsize];
	for(int i=0;i<mtfsize;i++)
	  mtf[i]=i+1; 
	rd=fopen("dawn.lile","rb");
	FILE *wt=fopen("lst.tmp","wb"),*rb=fopen("distance.tmp","rb"),*r=fopen("dawn.eta","rb");
	U short sh,p=0;
	ull dp=0;//dsize p
	U char *buf=new U char[dsize];
	hufchar hc;
	binarychar bc;
	fread(&hc,1,1,r);
	bc=hufchar2binarychar(hc);
	while(fread(&sh,2,1,rd))
	{
		if(sh<256)//literal
		{
			fwrite(&sh,1,1,wt);
			buf[dp++]=sh;
			if(--listfilesize==0)
			  break;
		}
		else//length
		{
			sh-=256;
			int add=0;
			for(int i=0;i<lileeta[sh];i++)
			{
				add=(add<<1)+bc.binary[p++];
				if(p==8)
				{
					p=0;
					fread(&hc,1,1,r);
					bc=hufchar2binarychar(hc);
				}
			}
			U I len=lilemap[sh]+add,dstc=0;
			char ch;
			ch=add=0;
			fread(&ch,1,1,rb);
			for(int i=0;i<dsteta[ch];i++)//读取dstc的eta 
			{
				add=(add<<1)+bc.binary[p++];
				if(p==8)
				{
					p=0;
					fread(&hc,1,1,r);
					bc=hufchar2binarychar(hc);
				}
			}
			dstc=mtf[dstmap[ch]+add-1];
			for(int j=dstmap[ch]+add-1;j>0;j--)
		  	  mtf[j]=mtf[j-1];
		  	mtf[0]=dstc;
			if(dstc>dp||dp+len>=dsize+10)
			{
				cout<<"jump(字典单词跳转值)："<<dstc<<endl<<"length(单词长度）："<<len<<endl<<"当前字典长："<<dp<<endl<<"错误：跳转值超过字典或是单词长度过长，文件损坏。"<<endl<<"建议：密码错误？"<<endl; 
				fclose(wt);
				dellist(delflist,16);
				return WRONGPASSWORD;
			} 
			while(len--)//len次
			{
				buf[dp]=buf[dp-dstc];
				fwrite(&buf[dp++],1,1,wt);	
				if(--listfilesize==0)
			  	  break;
			}
		}
		if(dp==dsize)
		  dp=0;//不需要对buf清空，因为接下来的内容会覆盖掉 
	}
	delete[] buf;
	fclose(rd);
	fclose(rb);
	fclose(r);
	fclose(wt);
	rd=fopen("lst.tmp","rb");
	if(rd==NULL)
	{
		files.push_back("错误：无法找到需要查找列表的文件");
		return -1;
	}
	string filedir;
	char tmp=0;
	int n=fread(&tmp,1,1,rd);
	while(tmp!='\n'&&n!=0)
	{
		filedir+=tmp;
		n=fread(&tmp,1,1,rd);
	}
	filedir="";
	n=fread(&tmp,1,1,rd);
	while(tmp!='\n'&&n!=0)
	{
		filedir+=tmp;
		n=fread(&tmp,1,1,rd);
	}
	while(filedir!="dirlistover"&&n)
	{
		files.push_back("目录："+filedir);
		filedir="";
		n=fread(&tmp,1,1,rd);
		while(tmp!='\n'&&n!=0)
		{
			filedir+=tmp;
			n=fread(&tmp,1,1,rd);
		}
	}
	files.push_back("\n");
	filedir="";
	n=fread(&tmp,1,1,rd);
	while(tmp!='\n'&&n!=0)
	{
		filedir+=tmp;
		n=fread(&tmp,1,1,rd);
	}
	ull filestart=files.size();
	vector<ull> filesize;
	ull onesize;
	fread(&onesize,8,1,rd);
	while(n)
	{
		files.push_back("文件："+filedir);
		filesize.push_back(onesize);
		filedir="";
		n=fread(&tmp,1,1,rd);
		while(tmp!='\n'&&n!=0)
		{
			filedir+=tmp;
			n=fread(&tmp,1,1,rd);
		}
		if(filedir=="filelistover")
		  break;
		fread(&onesize,8,1,rd);
	}
	int maxsize=0,maxsize2=0;
	for(int i=filestart;i<files.size();i++)
	  maxsize=max((ull)files[i].size(),(ull)maxsize);
	for(int i=filestart;i<files.size();i++)
	  maxsize2=max((ull)int2string(filesize[i-filestart]).size(),(ull)maxsize2);
	for(int i=filestart;i<files.size();i++)
	{
		ull src=files[i].size();
		for(int j=0;j<maxsize-src+10;j++)
		  files[i]+=' ';
		files[i]+="大小(压缩前):"+int2string(filesize[i-filestart]);
		for(int j=0;j<maxsize2-int2string(filesize[i-filestart]).size();j++)
		  files[i]+=' ';
		files[i]+="(以字节为单位)";
	}	 
	fclose(rd);
	dellist(delflist,16);
	return COMPRESSOK;
}
