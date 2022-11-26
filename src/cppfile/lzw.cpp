#include "../headerfile/dawn.hpp"
using namespace std;
int lzwcprs(char *inf,char *outf,bool cover)
{
	string outs=outf;
	addkzm(outs,".dwn");
	outf=Cc outs.c_str();
	if(checkfile(outf)&&!cover)
	  return OUTFILEALREADY;//OUTFILEALREADY;
	ull filesize=getfilesize(inf);
	FILE *rd=fopen(inf,"rb"),*wt=fopen(outf,"wb");
	if(rd==NULL)
	  return INFILENOTFOUND;//INFILENOTFOUND;
	U char filetype=2;
	fwrite(&filetype,1,1,wt);
	fwritevlq(wt,filesize);
	map<string,U int> dictionary;
	string p="";
	char c;
	int ps=256;
	for(int i=0;i<256;i++)
	{
		string a="";
		a+=i;
		dictionary[a]=i;
	}
	int tp=0;
	hufchar out=0;
	while(fread(&c,1,1,rd))
	  if(dictionary.count(p+c))
	    p=p+c;
	  else
	  {
		  int i=0;
		  for(;i<64&&ps>pow(2,i);i++);
		  ull tmp=dictionary[p];
		  for(int k=0;k<i;k++)
		  {
		  	  out+=tmp%2<<(tp);
		  	  tp++;
		  	  tmp/=2;
		  	  if(tp==8)
		  	  {
		  	  	  fwrite(&out,1,1,wt);
		  	  	  out=0;
		  	  	  tp=0;
			  }
		  } 
		  dictionary[p+c]=ps;
		  ps++;
		  p=c;
	  }
	int i=0;
	for(;i<64&&ps>pow(2,i);i++);
	  ull tmp=dictionary[p];
	for(int k=0;k<i;k++)
	{
	  	out+=tmp%2<<(tp);
		tp++;
		tmp/=2;
		if(tp==8)
		{
		    fwrite(&out,1,1,wt);
		    out=0;
		    tp=0;
		}
	} 
	if(tp)
	{
		out<<(tp);
		fwrite(&out,1,1,wt);
	}
	fclose(wt);
	fclose(rd);
	return OK;//done;
}
int lzwdec(char *inf,char*outf,bool cover)
{
	if(checkfile(outf)&&!cover)
	  return OUTFILEALREADY;//OUTFILEALREADY;
	FILE *rd=fopen(inf,"rb"),*wt=fopen(outf,"wb");
	if(rd==NULL)
	  return INFILENOTFOUND;//INFILENOTFOUND;
	U char filetyp;
	fread(&filetyp,1,1,rd);
    ull filesize=freadvlq(rd);
	U int cw,ps=256,pw;
	map<U int,string> dictionary;
	for(int i=0;i<256;i++)
	{
		string a="";
		a+=(char)i;
		dictionary[i]=a;
	}
	U char read;
	fread(&read,1,1,rd);
	int tp=0,i=0;
	cw=0;
	for(;i<64&&ps>pow(2,i);i++);
	while(i)
	{
		cw+=(read%2)<<(tp);
		read/=2;
		tp++;
		i--;
		if(tp==8)
		{
			fread(&read,1,1,rd);
			tp=0;
		}
	}
	fwrite(dictionary[cw].c_str(),1,dictionary[cw].size(),wt);
	filesize-=dictionary[cw].size(); 
	pw=cw;
	while(filesize)//解压时字典中的编码总是等于现实编码-1 
	{
		int i;
		cw=0;
		for(i=0;i<64&&ps>=pow(2,i);i++);
		int ti=i;
		bool flag=false;
		while(i)
		{			
			cw+=(read%2)<<(ti-i);
			read/=2;
			tp++;
			if(tp==8)
			{
				fread(&read,1,1,rd);
				tp=0;
			}
			i--;
		}
		fwrite(dictionary[(dictionary.count(cw))?cw:pw].c_str(),1,dictionary[(dictionary.count(cw))?cw:pw].size(),wt);
		filesize-=dictionary[(dictionary.count(cw))?cw:pw].size();
		if(!dictionary.count(cw))
		{
			fwrite(&dictionary[pw][0],1,1,wt);
			filesize--;
		}
		dictionary[ps++]=dictionary[pw]+dictionary[(dictionary.count(cw))?cw:pw][0];
		pw=cw;
	}	
	fclose(rd);
	fclose(wt);
}
