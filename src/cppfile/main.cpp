 #include "../headerfile/dawn.hpp"
IL void printtitle()
{
	system("cls");
	cout<<"****************************************"<<endl;
    cout<<"*dawncompress V9.1CopyRight(c) by ChZL *"<<endl;
    cout<<"*    Production time: November26,2022  *"<<endl;
    cout<<"*      软件版本：V9.1,文件版本：V9     *"<<endl; 
    cout<<"****************************************"<<endl;
    return ;
} 
int egetargvcom(char *argv[],int size,char *get)
{
	for(int i=0;i<size;i++)
	{
		int j=0;
		for(;j<strlen(get);j++)
	      if(argv[i][j]!=get[j])
	      	break;
		if(j==strlen(get))
	      return i;
	}
	return -1;
}
int main(int argc,char *argv[])//dawncompress.exe a.in -c a.out -r100 -pabc 
{
	printtitle();
	if(argc<2)
	{
		cserr:
		cout<<"请输入正确的参数！"<<endl;
		cout<<"在命令行中输入dawn -h 或dawn /h获取帮助"<<endl;
		syspause;  
		return UNKNOWERROR;
	}
	if(argv[1][0]=='-'&&(argv[1][1]=='h'||argv[1][1]=='H')&&(argv[1][2]!='c'&&argv[1][2]!='d'))
	{ 
		cout<<"参数说明：命令参数前都需要加上-否则将会被认为是文件参数"<<endl; 
		cout<<"-c                  文件压缩参数，将输入所有的文件压缩为最后一个输入的文件"<<endl;
		cout<<"-d                  文件解压缩参数，将输入的文件解压，不需要写输出文件，将自动解压"<<endl;
		cout<<"-r                  字典长度，越长压缩出的文件越小，但时间越长。不可以超过文件大小或是小于17"<<endl;
		cout<<"-rall               将整个文件的大小作为字典长度"<<endl; 
		cout<<"-l                  查看文件列表，查看压缩包的文件列表"<<endl;
		cout<<"-p                  输入密码，解压缩时可以不写该参数，但是需要按照提示输入密码"<<endl;
		cout<<"-w                  设置查找缓冲区(简易的滑动窗口)大小，设置为0或不设置时默认查找缓冲区为字典长度（无滑动窗口，进行全匹配）。设置查找缓冲区后程序的速度将会有所提升，但是压缩后的文件将更大"<<endl;
		cout<<endl<<"其他项："<<endl;
		cout<<"-hc                 使用huffman算法将单个文件压缩"<<endl;
		cout<<"-hd                 使用huffman算法将单个文件解压缩（将最后一个文件参数作为输出文件）"<<endl;
		cout<<"-opse               使用ops算法将单个文件加密（需要使用-p参数）"<<endl;
		cout<<"-opsd               使用ops算法将单个文件解密（可以不写-p参数，但是需要按照提示输入密码）"<<endl;
		cout<<"-bc                 将多个文件打包，输出为输入中的最后一个文件"<<endl;
		cout<<"-bd                 将打包文件解包，不需要指定输出文件"<<endl;
		cout<<endl<<"功能项："<<endl;
		cout<<"-enablecoveroutfile 打开覆盖输出文件"<<endl;
		cout<<"-fast               共有三个选项，分别为1~3。1选项速度最快，3最慢。速度越快压缩后文件越大。使用方式：-fast1：设置速度选项为1。不输入此参数则默认为3。" <<endl;
		cout<<"注意，对于-enablecoveroutfile适用于其他所有命令"<<endl; 
		cout<<"压缩，解压缩范例:\n压缩范例：dawn.exe infile1 infile2 ... -c outfile -rdirsize [-ppassword] [-disablehuffman] [-enablecoveroutfile]\n解压缩范例：\n dawn infile -d [-ppassword] [-enablecoveroutfile]"<<endl;
		cout<<"使用huffman压缩，解压缩范例：dawn.exe infile -hc|-hd outfile [-disablehuffman] [-enablecoveroutfile]"<<endl;
		cout<<"打包，解包范例：dawn.exe infile -bc|-bd outfile [-enablecoveroutfile]"<<endl;
		cout<<"使用ops加密解密范例：dawn.exe infile -opse|-opsd outfile [-enablecoveroutfile]"<<endl;
		cout<<"[]中的代表可选参数即不输入也可以让程序正确运行"<<endl;
		cout<<"|代表选择，例如-c|-d您可以输入-c来压缩或是-d来解压缩"<<endl;
		cout<<"你可以像使用G++编译器一样调换参数，但请保证输出文件是最后一个文件参数"<<endl;
		cout<<"例：dawn infile -c outfile -r65535和dawn -c -r65535 infile outfile等价"<<endl;
		cout<<"但是和 dawn -c -r65535 outfile infile 不等价，此时outfile将会被看做是输入文件"<<endl;
		cout<<endl<<endl;
		cout<<"如果你想使用deflate32的参数（滑动窗口大小为32768，将整个文件作为一整个块读取），请输入：dawn infile -c outfile -rall -w32768 （在deflate32的参数下，dawn算法压缩的文件比deflate32压缩的文件要小）"<<endl;
		cout<<"如果你想体验本算法最低的压缩率（即压缩后文件最小），请输入:dawn infile -c outfile -rall"<<endl; 
		cout<<endl<<endl;
		cout<<"返回值列表："<<endl;
		cout<<"返回值0或5：不存在任何错误，程序正常运行"<<endl;
		cout<<"返回值1：   密码错误，输入了错误的密码，造成无法解压或解密（注意，当解压时出现“建议：密码错误？”的错误时也会返回该值，当压缩文件没有密码但解压时出现该返回值应当视为压缩文件损坏"<<endl;
		cout<<"返回值2：   未知错误，当无法确定是文件损坏还是密码错误时返回该值"<<endl;
		cout<<"返回值3：   无法找到或打开文件"<<endl;
		cout<<"返回值4：   输出文件已存在，同时覆盖输出文件功能未开启（忘记了-enablecoveroutfile?）或是压缩，解压缩的临时文件被占用"<<endl;
		cout<<"返回值6：   极难出现的错误，拼接文件时出现错误。（用外部程序打开了压缩时产生的临时文件？）"<<endl;
		cout<<"返回值7：   压缩文件已损坏或不是压缩文件"<<endl;		 
		cout<<"返回值8：   内存不足"<<endl; 
		cout<<"返回值9：   解压缩软件的文件版本太低，无法解压由高文件版本压缩后的压缩文件"<<endl;
		cout<<"你可以使用c++或c语言中的system函数查看返回值并使用返回值来判断程序运行是否成功"<<endl; 
		return UNKNOWERROR;
	}
	if(argc<3)
	  goto cserr;
	bool havhuf=true,cover=false,mp=false,debug=(getargvcom(argv,argc,(char*)"-debug")!=-1||getargvcom(argv,argc,(char*)"-DEBUG")!=-1||getargvcom(argv,argc,(char*)"-Debug")!=-1);
	string password="";
	unsigned int ds;
	vector<string> files;
	int i=getfileinargv(argv,argc,1);
	for(int j=2;i!=-1;j++)
	{
		string file=argv[i];
		files.push_back(file);
		i=getfileinargv(argv,argc,j);
	} 
	string inf,outf=files[files.size()-1];
	files[files.size()-1]="bag.tmps";
	if(getfileinargv(argv,argc,1)==-1)
	  goto cserr;
	else
	  inf=argv[getfileinargv(argv,argc,1)];
	cover=(getargvcom(argv,argc,(char*)"-enablecoveroutfile")!=-1||getargvcom(argv,argc,(char*)"-ENABLECOVEROUTFILE")!=-1||getargvcom(argv,argc,(char*)"-Enablecoveroutfile")!=-1);//打开文件覆盖 
	if((getargvcom(argv,argc,(char*)"-p")!=-1||getargvcom(argv,argc,(char*)"-P")!=-1))//密码 
	{
		int ws=getargvcom(argv,argc,(char*)"-p");
		if(ws==-1)
		  ws=getargvcom(argv,argc,(char*)"-P");
		password=argv[ws];
		password.erase(0,2);
		mp=true;
	}
	if((getargvcom(argv,argc,Cc"-c")!=-1||getargvcom(argv,argc,Cc"-C")!=-1))//compress
	{
		ull jmsz; 
		bag(files.size(),files,jmsz,1);
		int r=egetargvcom(argv,argc,(char*)"-r");
		if(r==-1) 
		  r=egetargvcom(argv,argc,(char*)"-R");
		if(r==-1&&(getargvcom(argv,argc,(char*)"-rall")==-1&&getargvcom(argv,argc,(char*)"-RALL")==-1))
		{
			cout<<"参数不正确"<<endl<<"输入-h 或/h获取帮助"<<endl;
			return 0;
		}  
		if((getargvcom(argv,argc,Cc"-rall")!=-1||getargvcom(argv,argc,Cc"-RALL")!=-1))
		  ds=getfilesize(Cc"bag.tmps");
		else
		{
			string dir=argv[r];
			dir.erase(0,2);
			ds=string2int(dir);
		}
		addkzm(outf,".dwn");
		U I fs=getargvcom(argv,argc,(char*)"-FAST"),ews=getargvcom(argv,argc,(char*)"-w"),easywindowsize=0;
		if(fs==-1) 
		  fs=getargvcom(argv,argc,(char*)"-fast");
		string fast="-fast3";
		if(fs!=-1)
		  fast=argv[fs];
		fast.erase(0,5);
		ews=egetargvcom(argv,argc,(char *)"-w");
		if(ews==-1)
		  ews=egetargvcom(argv,argc,(char *)"-W");
		if(ews!=-1)
		{
			string windowsiz=argv[ews];
			windowsiz.erase(0,2);//去掉开头的-w 
			easywindowsize=string2int(windowsiz);
		}
		return dawncompress((char *)"bag.tmps",(char*)outf.c_str(),ds,cover,1,mp,(!((getargvcom(argv,argc,(char*)"-F2")!=-1||getargvcom(argv,argc,(char*)"-f2")!=-1)||(getargvcom(argv,argc,(char*)"-F3")!=-1||getargvcom(argv,argc,(char*)"-f3")!=-1))),password,jmsz,string2int(fast),easywindowsize,easywindowsize,(getargvcom(argv,argc,(char*)"-automtf")!=-1)||getargvcom(argv,argc,(char*)"-AUTOMTF")!=-1,debug);
	}
	if((getargvcom(argv,argc,(char*)"-d")!=-1||getargvcom(argv,argc,(char*)"-D")!=-1))//解压缩
    {
    	short res=dawndecompress((char *)inf.c_str(),(char*)"tmp.bag",cover,password,debug);
     	if(res!=OK)
     	{
     		//if(checkfile(Cc "tmp.bag"))
     		  //system("@del tmp.bag");
     	    return res;
		}
		res=unbag(1,(char*)"tmp.bag",1);
		if(checkfile(Cc "tmp.bag"))
     	  system("@del tmp.bag");
		return res;
	}    
	if((getargvcom(argv,argc,(char*)"-l")!=-1||getargvcom(argv,argc,(char*)"-L")!=-1))//获取文件列表 
    {
    	vector<string> files;
     	getlist((char*)inf.c_str(),files,password);
     	for(int i=0;i<files.size();i++)
		  cout<<files[i]<<endl; 
     	return OK; 
	}  
	ull tmp;
	bool b;          
    returnif((getargvcom(argv,argc,(char*)"-hc")!=-1||getargvcom(argv,argc,(char*)"-HC")!=-1),huffmanfilecompress((char *)inf.c_str(),(char *)outf.c_str(),tmp,b,cover));//huffman压缩 
    returnif((getargvcom(argv,argc,(char*)"-hd")!=-1||getargvcom(argv,argc,(char*)"-HD")!=-1),huffmanfiledecompress((char *)inf.c_str(),(char *)outf.c_str(),0,cover));//huffman解压缩 
	returnif((getargvcom(argv,argc,(char*)"-opse")!=-1||getargvcom(argv,argc,(char*)"-OPSE")!=-1),opsfileencode((char *)inf.c_str(),(char *)outf.c_str(),password,tmp,cover););//ops加密  
	returnif((getargvcom(argv,argc,(char*)"-opsd")!=-1||getargvcom(argv,argc,(char*)"-OPSD")!=-1),opsfiledecode((char *)inf.c_str(),(char *)outf.c_str(),password,cover));//ops解密  
	files.erase(files.begin()+files.size()-1);
	if(files.size())
	  addkzm(files[files.size()-1],".bag");
	returnif((getargvcom(argv,argc,(char*)"-bc")!=-1||getargvcom(argv,argc,(char*)"-BC")!=-1),bag(files.size(),files,tmp,cover));//bag打包 
	returnif((getargvcom(argv,argc,(char*)"-bd")!=-1||getargvcom(argv,argc,(char*)"-BD")!=-1),unbag(1,(char *)inf.c_str(),cover));//bag解包 
	if((getargvcom(argv,argc,(char*)"-rlc")!=-1||getargvcom(argv,argc,(char*)"-RLC")!=-1))//crlc压缩 
	{
		U I fs=getargvcom(argv,argc,(char*)"-FAST");
		if(fs==-1) 
		  fs=getargvcom(argv,argc,(char*)"-fast");
		string fast="-fast2";
		if(fs!=-1)
		  fast=argv[fs];
		fast.erase(0,5);
		return crlc(Cc inf.c_str(),Cc outf.c_str(),0,string2int(fast)-1,1);
	}
	returnif((getargvcom(argv,argc,(char*)"-rld")!=-1||getargvcom(argv,argc,(char*)"-RLD")!=-1),crlc(Cc inf.c_str(),Cc outf.c_str(),1,1,1));//crlc解压 
	
	returnif((getargvcom(argv,argc,(char*)"-lzwc")!=-1||getargvcom(argv,argc,(char*)"-LZWC")!=-1),lzwcprs(Cc inf.c_str(),Cc outf.c_str(),1));//lzw压缩 
	returnif((getargvcom(argv,argc,(char*)"-lzwd")!=-1||getargvcom(argv,argc,(char*)"-LZWD")!=-1),lzwdec(Cc inf.c_str(),Cc outf.c_str(),1));//crlc解压 
	goto cserr;//如果到最后了都没有返回证明输入的命令参数都不合法 
} 
