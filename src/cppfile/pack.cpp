#include "../headerfile/dawn.hpp"
extern void getFiles( string path, vector<string>& files);
extern void errors(char *color,char *title,char *error);
short bag(int argc,vector<string> argv,ull &hdsize,bool cover=true)
{
	hdsize=0;
	ull allfilesize=0;
	FILE *wt,*rd;
	if(checkfile((char*)argv[argc-1].c_str())&&!cover)
	{
		errors((char*)"color",(char*)"Error:",(char*)"输出文件已经存在");
		return OUTFILEALREADY;
	}	
	opt:
	wt=fopen(argv[argc-1].c_str(),"wb");
	vector<string> files;
	for(int i=0;i<argc-1;i++)
	{
		string tmp=argv[i];
		if(!checkfile((char *)tmp.c_str()))//是目录 
		{
			tmp+='\\';
			files.push_back(tmp);
			int a=files.size();
			getFiles(argv[i],files);
			if(a==files.size())
			{
				cout<<argv[i]<<"既不是目录（或目录为空）也不是文件"<<endl;
				return INFILENOTFOUND; 
			}
		} 
		else
		  files.push_back(argv[i]); 
	}
	ull filesize[files.size()];
	for(int i=0;i<files.size();i++)
	  if(files[i][files[i].size()-1]!='\\')
	  {
	  	  filesize[i]=getfilesize((char *)files[i].c_str());
	 	  allfilesize+=filesize[i];
	  }	
	char *dirsign=(char *)"therearedirlist\n";
	fwrite(dirsign,1,strlen(dirsign),wt);
	hdsize+=strlen(dirsign);
	for(ull i=0;i<files.size();i++)
	  if(files[i][files[i].size()-1]=='\\')//是目录
	  {
	  	  char ttmp='\n';
	  	  fwrite(files[i].c_str(),1,files[i].size(),wt);
	  	  hdsize+=files[i].size();
	  	  fwrite(&ttmp,1,1,wt);
	  	  hdsize++;
	  }
	char *endsign=(char *)"dirlistover\n";
	fwrite(endsign,1,strlen(endsign),wt);
	hdsize+=strlen(endsign);
	for(int i=0;i<files.size();i++)
	  if(files[i][files[i].size()-1]!='\\')
	  {
		  char ttmp='\n';
		  fwrite(files[i].c_str(),1,files[i].size(),wt);
		  hdsize+=files[i].size();
		  fwrite(&ttmp,1,1,wt);
		  hdsize+=9;
		  fwrite(&filesize[i],8,1,wt);
	  }
	endsign=(char *)"filelistover\n";
	fwrite(endsign,1,strlen(endsign),wt);
	hdsize+=strlen(endsign);
	ull onesize=0,allsize=0;
	for(int i=0;i<files.size();i++)
	  if(files[i][files[i].size()-1]!='\\')
	  {
	  	  onesize=0;
		  FILE *rd=fopen(files[i].c_str(),"rb");
		  char *read=new char[MB];
		  ull last=0,n=fread(read,1,MB,rd);
		  while(n!=0)
		  {
		  	  fwrite(read,1,n,wt);
		  	  onesize+=n;
		  	  allsize+=n;
			  n=fread(read,1,MB,rd);
		  }
		  delete[] read;
	  }
	fclose(rd);
	fclose(wt);
	return OK;
}
short unbag(int argc,char *argv,bool cover=true)
{
	bool flag=false;
	returnif(!checkfile(argv),INFILENOTFOUND);
	ull filesizes=getfilesize(argv),oksize=0;
	FILE *wt,*rd=fopen(argv,"rb");
	string filedir="";
	char tmp=0;
	int n;
	n=fread(&tmp,1,1,rd);
	while(tmp!='\n'&&n!=0)
	{
		filedir+=tmp;
		n=fread(&tmp,1,1,rd);
		oksize++;
	}
	filedir="";
	n=fread(&tmp,1,1,rd);
	while(tmp!='\n'&&n!=0)
	{
		filedir+=tmp;
		n=fread(&tmp,1,1,rd);
		oksize++;
	}
	while(filedir!="dirlistover"&&n)
	{
		string com="";
		com="@md ";
		com+='"'+filedir+'"';
		system(com.c_str());
		filedir="";
		n=fread(&tmp,1,1,rd);
		oksize++;
		while(tmp!='\n'&&n!=0)
		{
			filedir+=tmp;
			n=fread(&tmp,1,1,rd);
			oksize++;
		}
	}
	filedir="";
	vector<fileinfo> files;
	n=fread(&tmp,1,1,rd);
	while(tmp!='\n'&&n!=0)
	{
		filedir+=tmp;
		n=fread(&tmp,1,1,rd);
		oksize++;
	}
	ull allfilesize=0,onefilesize;
	fread(&onefilesize,8,1,rd);
	oksize+=8;
	while(n)
	{
		fileinfo finf;
		finf.filename=filedir;
		finf.size=onefilesize;
		allfilesize+=onefilesize;
		files.push_back(finf);
		filedir="";
		n=fread(&tmp,1,1,rd);
		oksize++;
		while(tmp!='\n'&&n!=0)
		{
			filedir+=tmp;
			n=fread(&tmp,1,1,rd);
			oksize++;
		}
		if(filedir=="filelistover")
		  break;
		fread(&onefilesize,8,1,rd);
		oksize+=8;
	}
	for(ull i=0;i<files.size();i++)
	{
		onefilesize=files[i].size;
		if(checkfile((char*)files[i].filename.c_str())&&!cover)
		{
			cout<<"错误：输出文件已存在"<<endl;
			return OUTFILEALREADY; 
		}
		FILE *wt=fopen(files[i].filename.c_str(),"wb");
		if(wt==NULL)
		{
			cout<<"错误:输出文件无法打开（正在使用中？）"<<endl;
			return OUTFILEALREADY; 
		}
		char read;
		ull last=0;
		for(ull j=0;j<onefilesize;j++)
		{
			returnif(!fread(&read,1,1,rd),COMPRESSFILEBREAK);
			oksize++;
			fwrite(&read,1,1,wt);
		}
	}
	fclose(wt);
	fclose(rd);
	return OK;
}
