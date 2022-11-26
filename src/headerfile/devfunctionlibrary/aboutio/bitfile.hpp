/*
bitfile实现For C++! 
概述：以bit为级别读写文件（即读写分度值为bit） 
制作时间：2022-06-29
版本：V22.06.29
头文件信息：
这是一个内部头文件，是dev_function_library函数库中的一个头文件。
请不要尝试直接调用它的头文件名！ 
此头文件授予了使用权利但是并没有授予以下权利：复制、修改、分发和销售本头文件 
这个头文件仅仅适用于C++！ 
*/
class bitfile
{
	private:
		int tp;
		U char io,reads;
		FILE *rw;
		bool rd,cn;
	public:
		void flush()
		{
			if(tp!=0&&!rd)
			  fwrite(&io,1,1,rw);
		}
		bitfile(const char *file,const char *cmd)
		{
			rw=fopen(file,cmd);
			rd=strcmp(cmd,"rb")==0;
			tp=io=0;
			cn=true;
		}
		~bitfile()
		{
			flush();
		}
		bitfile()
		{
			tp=io=0;
		}
		FILE *getFILE()
		{
			return rw;
		}
		bool isread()
		{
			return rd;
		}
		int getnowbit()
		{
			return tp;
		}
		U char getio()
		{
			return io;
		}
		U char thisread()
		{
			return reads;
		}
		bool firstread()
		{
			return cn;
		}
		bool open(const char *file,const char *cmd)
		{
			close();
			rw=fopen(file,cmd);
			rd=strcmp(cmd,"rb")==0;
			tp=io=0;
			cn=true;
		}
		bool close()
		{
			flush(); 
			fclose(rw);
			io=tp=0;
		}
		ull write(void *buf,int onebit,ull byte)//从低位开始 
		{
			if(rd)
			  return -1;
			ull ret=0;
			U char *wb=(U char*)buf;
			for(ull i=0;i<byte;i++)
			  for(int k=0;k<onebit;k++)
		  	  {
		  	      io+=wb[i]%2<<(tp);
		  	      tp++;
		  	      wb[i]/=2;
		  	      if(tp==8)
		  	      {
		  	  	      fwrite(&io,1,1,rw);
		  	  	      cout<<(U I)io<<endl;
		  	  	      io=tp=0;
			      }
			      ret++;
		      }  
		    return ret;
		}
		ull read(void *buf,int onebit,ull byte)
		{
			if(!rd)
			  return -1;
			ull ret=0,p=0,ps=0;
			U char *rb=(U char*)buf;
			if(cn)
			{
				cn=false;
				fread(&reads,1,1,rw);
			}
			for(int i=0;i<byte*onebit;i++)
			{
				ret++;
				io+=(reads%2)<<(ps);
				reads/=2;
				tp++;
				ps++;
				if(tp==8)
				{
					if(!fread(&reads,1,1,rw))
					{
						rb[p++]=io;
						return ret;
					}
					tp=0;
				}
				if(ps==onebit)
				{
					rb[p++]=io;
					io=0;
				}
			}
			return ret;
		}
		void operator=(bitfile bf)
		{
			rw=bf.getFILE();
			reads=bf.thisread();
			io=bf.getio();
			rd=bf.isread();
			cn=bf.firstread();
			tp=bf.getnowbit();
		}
		bool operator==(bitfile yic)
		{
			return rw==yic.getFILE()&&
			reads==yic.thisread()&&
			io==yic.getio()&&
			rd==yic.isread()&&
			cn==yic.firstread()&&
			tp==yic.getnowbit();
		}
}; 
