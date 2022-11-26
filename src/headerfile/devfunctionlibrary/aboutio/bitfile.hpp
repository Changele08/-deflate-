/*
bitfileʵ��For C++! 
��������bitΪ�����д�ļ�������д�ֶ�ֵΪbit�� 
����ʱ�䣺2022-06-29
�汾��V22.06.29
ͷ�ļ���Ϣ��
����һ���ڲ�ͷ�ļ�����dev_function_library�������е�һ��ͷ�ļ���
�벻Ҫ����ֱ�ӵ�������ͷ�ļ����� 
��ͷ�ļ�������ʹ��Ȩ�����ǲ�û����������Ȩ�������ơ��޸ġ��ַ������۱�ͷ�ļ� 
���ͷ�ļ�����������C++�� 
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
		ull write(void *buf,int onebit,ull byte)//�ӵ�λ��ʼ 
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
