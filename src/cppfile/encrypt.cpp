#include "../headerfile/dawn.hpp"
#include <conio.h>
#ifndef CSL
#define CSL
#define UP        72
#define DOWN      80
#define LEFT      75
#define RIGHT     77
#define ENTER     13
#define ESC       27
#define TAB       9
#define DEL       83
#define BACKSPACE 8
void getpassword(string &password)
{
	returnif(password!="",);//忘记输入密码了
	cout<<"错误，无法找到密码，忘记输入？"<<endl<<"请重新输入(不会显示)"<<endl;;
	char ch=getch();
	while(ch!=ENTER)
	{
		cout<<'*';
		password+=ch;
		ss:
		ch=getch();
		if(ch==BACKSPACE)
		{
			cout<<"\b \b";
			password.erase(password.size()-1,1);
			goto ss;
		}
	}
	putch('\n');
	return;
}
#endif 
short opsfileencode(const char *inf,const char *outf,string password,ull &flsz,bool cover=true)
{
	getpassword(password);
	ull filesize=getfilesize((char *)inf);
	returnif(filesize==0,INFILENOTFOUND);
	returnif(checkfile((char *)outf)&&!cover,OUTFILEALREADY);
	FILE *rd=fopen(inf,"rb"),*wt=fopen(outf,"wb");
	fwrite(&filesize,8,1,wt);
	flsz=8;
	unsigned char *encbuf=new unsigned char[password.size()],*readbuf=new unsigned char[password.size()];
	memset(readbuf,0,password.size());
	int n=fread(readbuf,1,password.size(),rd);
	ull ops=0;
	while(n)
	{
		opsenc(encbuf,readbuf,n,(unsigned char*)password.c_str(),Sbox);
		fwrite(encbuf,1,password.size(),wt);
		flsz+=password.size();
		memset(readbuf,0,password.size());
		n=fread(readbuf,1,password.size(),rd);
	}
	delete[] encbuf;
	delete[] readbuf;
	fclose(rd);
	fclose(wt);
	return OK;
}
short opsfiledecode(char *inf,char *outf,string password,bool cover=true)
{
	getpassword(password);
	U char *nsbox=new U char[256];
	for(int i=0;i<256;i++)
	  nsbox[Sbox[i]]=(unsigned char)i;
	returnif(checkfile(outf)&&!cover,OUTFILEALREADY);
	FILE *rd=fopen(inf,"rb"),*wt=fopen(outf,"wb");
	returnif(rd==NULL,INFILENOTFOUND);
	ull filesize=0;
	fread(&filesize,8,1,rd);
	if(getfilesize(inf)<filesize)
	{
		filebreak:
		fclose(rd);
		fclose(wt);
		return COMPRESSFILEBREAK;
	}
	unsigned char *readbuf=new unsigned char[password.size()],*encbuf=new unsigned char[password.size()];
	int n=fread(readbuf,1,password.size(),rd);
	ull ofs=0;
	while(n)
	{
		opsdec(encbuf,readbuf,n,(unsigned char*)password.c_str(),nsbox);
		ofs+=fwrite(encbuf,1,min(password.size(),filesize-ofs),wt);
		if(ofs==filesize)
		  break;
		n=fread(readbuf,1,password.size(),rd);
		if(!n)
		{
			system(((string)"@del "+outf).c_str());
			goto filebreak;
		}
	}
	delete[] encbuf;
	delete[] readbuf;
	delete[] nsbox;
	fclose(rd);
	fclose(wt);
	return OK;
}
