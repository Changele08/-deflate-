 #include "../headerfile/dawn.hpp"
IL void printtitle()
{
	system("cls");
	cout<<"****************************************"<<endl;
    cout<<"*dawncompress V9.1CopyRight(c) by ChZL *"<<endl;
    cout<<"*    Production time: November26,2022  *"<<endl;
    cout<<"*      ����汾��V9.1,�ļ��汾��V9     *"<<endl; 
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
		cout<<"��������ȷ�Ĳ�����"<<endl;
		cout<<"��������������dawn -h ��dawn /h��ȡ����"<<endl;
		syspause;  
		return UNKNOWERROR;
	}
	if(argv[1][0]=='-'&&(argv[1][1]=='h'||argv[1][1]=='H')&&(argv[1][2]!='c'&&argv[1][2]!='d'))
	{ 
		cout<<"����˵�����������ǰ����Ҫ����-���򽫻ᱻ��Ϊ���ļ�����"<<endl; 
		cout<<"-c                  �ļ�ѹ�����������������е��ļ�ѹ��Ϊ���һ��������ļ�"<<endl;
		cout<<"-d                  �ļ���ѹ����������������ļ���ѹ������Ҫд����ļ������Զ���ѹ"<<endl;
		cout<<"-r                  �ֵ䳤�ȣ�Խ��ѹ�������ļ�ԽС����ʱ��Խ���������Գ����ļ���С����С��17"<<endl;
		cout<<"-rall               �������ļ��Ĵ�С��Ϊ�ֵ䳤��"<<endl; 
		cout<<"-l                  �鿴�ļ��б��鿴ѹ�������ļ��б�"<<endl;
		cout<<"-p                  �������룬��ѹ��ʱ���Բ�д�ò�����������Ҫ������ʾ��������"<<endl;
		cout<<"-w                  ���ò��һ�����(���׵Ļ�������)��С������Ϊ0������ʱĬ�ϲ��һ�����Ϊ�ֵ䳤�ȣ��޻������ڣ�����ȫƥ�䣩�����ò��һ������������ٶȽ�����������������ѹ������ļ�������"<<endl;
		cout<<endl<<"�����"<<endl;
		cout<<"-hc                 ʹ��huffman�㷨�������ļ�ѹ��"<<endl;
		cout<<"-hd                 ʹ��huffman�㷨�������ļ���ѹ���������һ���ļ�������Ϊ����ļ���"<<endl;
		cout<<"-opse               ʹ��ops�㷨�������ļ����ܣ���Ҫʹ��-p������"<<endl;
		cout<<"-opsd               ʹ��ops�㷨�������ļ����ܣ����Բ�д-p������������Ҫ������ʾ�������룩"<<endl;
		cout<<"-bc                 ������ļ���������Ϊ�����е����һ���ļ�"<<endl;
		cout<<"-bd                 ������ļ����������Ҫָ������ļ�"<<endl;
		cout<<endl<<"�����"<<endl;
		cout<<"-enablecoveroutfile �򿪸�������ļ�"<<endl;
		cout<<"-fast               ��������ѡ��ֱ�Ϊ1~3��1ѡ���ٶ���죬3�������ٶ�Խ��ѹ�����ļ�Խ��ʹ�÷�ʽ��-fast1�������ٶ�ѡ��Ϊ1��������˲�����Ĭ��Ϊ3��" <<endl;
		cout<<"ע�⣬����-enablecoveroutfile������������������"<<endl; 
		cout<<"ѹ������ѹ������:\nѹ��������dawn.exe infile1 infile2 ... -c outfile -rdirsize [-ppassword] [-disablehuffman] [-enablecoveroutfile]\n��ѹ��������\n dawn infile -d [-ppassword] [-enablecoveroutfile]"<<endl;
		cout<<"ʹ��huffmanѹ������ѹ��������dawn.exe infile -hc|-hd outfile [-disablehuffman] [-enablecoveroutfile]"<<endl;
		cout<<"��������������dawn.exe infile -bc|-bd outfile [-enablecoveroutfile]"<<endl;
		cout<<"ʹ��ops���ܽ��ܷ�����dawn.exe infile -opse|-opsd outfile [-enablecoveroutfile]"<<endl;
		cout<<"[]�еĴ����ѡ������������Ҳ�����ó�����ȷ����"<<endl;
		cout<<"|����ѡ������-c|-d����������-c��ѹ������-d����ѹ��"<<endl;
		cout<<"�������ʹ��G++������һ���������������뱣֤����ļ������һ���ļ�����"<<endl;
		cout<<"����dawn infile -c outfile -r65535��dawn -c -r65535 infile outfile�ȼ�"<<endl;
		cout<<"���Ǻ� dawn -c -r65535 outfile infile ���ȼۣ���ʱoutfile���ᱻ�����������ļ�"<<endl;
		cout<<endl<<endl;
		cout<<"�������ʹ��deflate32�Ĳ������������ڴ�СΪ32768���������ļ���Ϊһ�������ȡ���������룺dawn infile -c outfile -rall -w32768 ����deflate32�Ĳ����£�dawn�㷨ѹ�����ļ���deflate32ѹ�����ļ�ҪС��"<<endl;
		cout<<"����������鱾�㷨��͵�ѹ���ʣ���ѹ�����ļ���С����������:dawn infile -c outfile -rall"<<endl; 
		cout<<endl<<endl;
		cout<<"����ֵ�б�"<<endl;
		cout<<"����ֵ0��5���������κδ��󣬳�����������"<<endl;
		cout<<"����ֵ1��   ������������˴�������룬����޷���ѹ����ܣ�ע�⣬����ѹʱ���֡����飺������󣿡��Ĵ���ʱҲ�᷵�ظ�ֵ����ѹ���ļ�û�����뵫��ѹʱ���ָ÷���ֵӦ����Ϊѹ���ļ���"<<endl;
		cout<<"����ֵ2��   δ֪���󣬵��޷�ȷ�����ļ��𻵻����������ʱ���ظ�ֵ"<<endl;
		cout<<"����ֵ3��   �޷��ҵ�����ļ�"<<endl;
		cout<<"����ֵ4��   ����ļ��Ѵ��ڣ�ͬʱ��������ļ�����δ������������-enablecoveroutfile?������ѹ������ѹ������ʱ�ļ���ռ��"<<endl;
		cout<<"����ֵ6��   ���ѳ��ֵĴ���ƴ���ļ�ʱ���ִ��󡣣����ⲿ�������ѹ��ʱ��������ʱ�ļ�����"<<endl;
		cout<<"����ֵ7��   ѹ���ļ����𻵻���ѹ���ļ�"<<endl;		 
		cout<<"����ֵ8��   �ڴ治��"<<endl; 
		cout<<"����ֵ9��   ��ѹ��������ļ��汾̫�ͣ��޷���ѹ�ɸ��ļ��汾ѹ�����ѹ���ļ�"<<endl;
		cout<<"�����ʹ��c++��c�����е�system�����鿴����ֵ��ʹ�÷���ֵ���жϳ��������Ƿ�ɹ�"<<endl; 
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
	cover=(getargvcom(argv,argc,(char*)"-enablecoveroutfile")!=-1||getargvcom(argv,argc,(char*)"-ENABLECOVEROUTFILE")!=-1||getargvcom(argv,argc,(char*)"-Enablecoveroutfile")!=-1);//���ļ����� 
	if((getargvcom(argv,argc,(char*)"-p")!=-1||getargvcom(argv,argc,(char*)"-P")!=-1))//���� 
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
			cout<<"��������ȷ"<<endl<<"����-h ��/h��ȡ����"<<endl;
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
			windowsiz.erase(0,2);//ȥ����ͷ��-w 
			easywindowsize=string2int(windowsiz);
		}
		return dawncompress((char *)"bag.tmps",(char*)outf.c_str(),ds,cover,1,mp,(!((getargvcom(argv,argc,(char*)"-F2")!=-1||getargvcom(argv,argc,(char*)"-f2")!=-1)||(getargvcom(argv,argc,(char*)"-F3")!=-1||getargvcom(argv,argc,(char*)"-f3")!=-1))),password,jmsz,string2int(fast),easywindowsize,easywindowsize,(getargvcom(argv,argc,(char*)"-automtf")!=-1)||getargvcom(argv,argc,(char*)"-AUTOMTF")!=-1,debug);
	}
	if((getargvcom(argv,argc,(char*)"-d")!=-1||getargvcom(argv,argc,(char*)"-D")!=-1))//��ѹ��
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
	if((getargvcom(argv,argc,(char*)"-l")!=-1||getargvcom(argv,argc,(char*)"-L")!=-1))//��ȡ�ļ��б� 
    {
    	vector<string> files;
     	getlist((char*)inf.c_str(),files,password);
     	for(int i=0;i<files.size();i++)
		  cout<<files[i]<<endl; 
     	return OK; 
	}  
	ull tmp;
	bool b;          
    returnif((getargvcom(argv,argc,(char*)"-hc")!=-1||getargvcom(argv,argc,(char*)"-HC")!=-1),huffmanfilecompress((char *)inf.c_str(),(char *)outf.c_str(),tmp,b,cover));//huffmanѹ�� 
    returnif((getargvcom(argv,argc,(char*)"-hd")!=-1||getargvcom(argv,argc,(char*)"-HD")!=-1),huffmanfiledecompress((char *)inf.c_str(),(char *)outf.c_str(),0,cover));//huffman��ѹ�� 
	returnif((getargvcom(argv,argc,(char*)"-opse")!=-1||getargvcom(argv,argc,(char*)"-OPSE")!=-1),opsfileencode((char *)inf.c_str(),(char *)outf.c_str(),password,tmp,cover););//ops����  
	returnif((getargvcom(argv,argc,(char*)"-opsd")!=-1||getargvcom(argv,argc,(char*)"-OPSD")!=-1),opsfiledecode((char *)inf.c_str(),(char *)outf.c_str(),password,cover));//ops����  
	files.erase(files.begin()+files.size()-1);
	if(files.size())
	  addkzm(files[files.size()-1],".bag");
	returnif((getargvcom(argv,argc,(char*)"-bc")!=-1||getargvcom(argv,argc,(char*)"-BC")!=-1),bag(files.size(),files,tmp,cover));//bag��� 
	returnif((getargvcom(argv,argc,(char*)"-bd")!=-1||getargvcom(argv,argc,(char*)"-BD")!=-1),unbag(1,(char *)inf.c_str(),cover));//bag��� 
	if((getargvcom(argv,argc,(char*)"-rlc")!=-1||getargvcom(argv,argc,(char*)"-RLC")!=-1))//crlcѹ�� 
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
	returnif((getargvcom(argv,argc,(char*)"-rld")!=-1||getargvcom(argv,argc,(char*)"-RLD")!=-1),crlc(Cc inf.c_str(),Cc outf.c_str(),1,1,1));//crlc��ѹ 
	
	returnif((getargvcom(argv,argc,(char*)"-lzwc")!=-1||getargvcom(argv,argc,(char*)"-LZWC")!=-1),lzwcprs(Cc inf.c_str(),Cc outf.c_str(),1));//lzwѹ�� 
	returnif((getargvcom(argv,argc,(char*)"-lzwd")!=-1||getargvcom(argv,argc,(char*)"-LZWD")!=-1),lzwdec(Cc inf.c_str(),Cc outf.c_str(),1));//crlc��ѹ 
	goto cserr;//���������˶�û�з���֤�������������������Ϸ� 
} 
