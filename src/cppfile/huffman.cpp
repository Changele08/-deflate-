#include "../headerfile/dawn.hpp"
using namespace std;
#include "../headerfile/devfunctionlibrary/standard_template_library/smpvector.hpp"
#include "../headerfile/devfunctionlibrary/standard_template_library/hashmap.hpp"
int huffmanfilecompress(const char *file,const char *of,ull &nfs,bool &is16,bool cover=true)//Ñ¹Ëõ 
{
	is16=true;
	returnif(!checkfile((char *)file),INFILENOTFOUND);
	returnif(checkfile((char *)of)&&!cover,OUTFILEALREADY);
	huffcode *huffman=new huffcode[256]; 
	for(int i=0;i<256;i++)
	{
		huffman[i].ch=i;
		huffman[i].num=0;
		huffman[i].left=huffman[i].right=NULL;
		huffman[i].isleaf=huffman[i].root=false; 
		huffman[i].code=""; 
	}
	FILE *rd=fopen(file,"rb"),*wt=fopen(of,"wb");
	U char read=1;
	fwrite(&read,1,1,wt);//huffman£º1 
	nfs=fwritevlq(wt,getfilesize((char *)file))+1; 
	while(fread(&read,1,1,rd)>0)
	{
		huffman[read].ch=read;
		huffman[read].num++;
		huffman[read].isleaf=true;
	}
	makehuffmancode(huffman);
	fillcod(huffman);
	fclose(rd);
	rd=fopen(file,"rb");
	short p=0;
	binarychar bc;
	memset(bc.binary,0,sizeof(bc.binary));
	sort(huffman,huffman+256,chcmp); 
	for(int i=0;i<256;i++)
	  if(huffman[i].code.size()>=16)
	    is16=false;
	for(int i=0;(!is16)?i<256:i+1<256;i+=(!is16)?1:2)
	{
		U char s=(!is16)?huffman[i].code.size():huffman[i].code.size()<<4|huffman[i+1].code.size();
		fwrite(&s,1,1,wt);
		nfs++;
	}
	U char l;
	while(fread(&read,1,1,rd))//cout<<"µÚ"<<cs<<"´ÎÑ¹Ëõ"<<endl;
	  for(int oks=0;oks<huffman[read].code.size();bc.binary[p++]=(huffman[read].code[oks++]=='1'))
		tryout(p,bc,wt,nfs);
	if(p!=0)
	{
		p=8;
		tryout(p,bc,wt,nfs);
	}
	fclose(rd);
	fclose(wt);
	delete[] huffman;
	return OK;
}
int huffmanfiledecompress(const char *input,const char *output,bool is16,bool cover=true)//½âÑ¹Ëõ 
{
	returnif(!checkfile((char *)input),INFILENOTFOUND);
	returnif(checkfile((char *)output)&&!cover,OUTFILEALREADY);
	huffcode *huffman=new huffcode[256]; 
	for(int i=0;i<256;i++)
	{
		huffman[i].ch=i;
		huffman[i].num=0;
		huffman[i].left=huffman[i].right=NULL;
		huffman[i].isleaf=huffman[i].root=false; 
		huffman[i].code=""; 
	}
	FILE *rd=fopen(input,"rb"),*wt=fopen(output,"wb");
	U char type;
	fread(&type,1,1,rd);
	if(type!=1)
	  return COMPRESSFILEBREAK;
	ull filesize=freadvlq(rd);
	if(!is16)
	  for(int i=0;i<256;i+=1)
	  {
		  U char siz;
		  fread(&siz,1,1,rd);
		  for(int j=0;j<siz;j++) 
		    huffman[i].code+="0";
	  }
	else
	  for(int i=0;i+1<256;i+=2)
	  {
		  U char siz;
		  fread(&siz,1,1,rd);
		  for(int j=0;j<((siz&0xf0)>>4);j++) 
		    huffman[i].code+="0";
		  for(int j=0;j<(siz&0x0f);j++) 
		    huffman[i+1].code+="0";
	  }
	fillcod(huffman);
	hufchar hc;
	int p=0,n=fread(&hc,sizeof(hufchar),1,rd);//96
	bool flag=true;
	binarychar bc;
	hashmap<string,huffcode> hm;
	sort(huffman,huffman+256,chcmp);
	for(int i=0;i<256;i++)
	  if(huffman[i].code.size())
	    hm.push(huffman[i].code,huffman[i]);
	string fd="";
	bc=hufchar2binarychar(hc);//100 101 10
	p=0;
	while(n)
	{
		for(;p<8;p++)
		{
			fd+=(bc.binary[p]+'0');
			if(hm.findkey(fd))
			{
				fwrite(&hm.getvalue(fd).ch,1,1,wt);
				if(!--filesize)
				  break;
				fd="";
			}
		}
		if(!filesize)
		  break;
		if(p==8)	
		{
			p=0;
			n=fread(&hc,1,1,rd);
			bc=hufchar2binarychar(hc);//100 101 10
		}
	}
	fclose(rd);
	fclose(wt);
	return OK;
}
int shhuffmanfilecompress(char *file,char *of,ull &nfs,bool &is16,bool cover=true)//Ñ¹Ëõ 
{
	is16=true;
	returnif(!checkfile(file),INFILENOTFOUND);
	returnif(checkfile(of)&&!cover,OUTFILEALREADY);
	mhuffcode *huffman=new mhuffcode[512]; 
	for(int i=0;i<512;i++)
	{
		huffman[i].ch=i;
		huffman[i].num=0;
		huffman[i].left=huffman[i].right=NULL;
		huffman[i].isleaf=huffman[i].root=false; 
		huffman[i].code=""; 
	}
	ull filesize=getfilesize(file); 
	FILE *rd=fopen(file,"rb"),*wt=fopen(of,"wb");
	U short read;
	nfs=fwritevlq(wt,filesize); 
	while(fread(&read,2,1,rd)>0)
	{
		huffman[read].ch=read;
		huffman[read].num++;
		huffman[read].isleaf=true;
	}
	mmakehuffmancode(huffman);
	mnumfillcod(huffman);
	fclose(rd);
	rd=fopen(file,"rb");
	short p=0;
	binarychar bc;
	memset(bc.binary,0,sizeof(bc.binary));
	sort(huffman,huffman+512,mchcmp);
	for(int i=0;i<285;i++)
	  if(huffman[i].code.size()>=16)
	    is16=false;
	for(int i=0;(!is16)?i<285:i+1<286;i+=(!is16)?1:2)
	{
		U char s=(!is16)?huffman[i].code.size():huffman[i].code.size()<<4|huffman[i+1].code.size();
		fwrite(&s,1,1,wt);
		nfs++; 
	}
	while(fread(&read,2,1,rd)>0)//cout<<"µÚ"<<cs<<"´ÎÑ¹Ëõ"<<endl;
	  for(int oks=0;oks<huffman[read].code.size();bc.binary[p++]=(huffman[read].code[oks++]=='1'))
		tryout(p,bc,wt,nfs);
	if(p!=0)
	{
		p=8;
		tryout(p,bc,wt,nfs);
	}
	fclose(rd);
	fclose(wt);
	delete[] huffman;
	return OK;
}
int shhuffmanfiledecompress(char *input,char *output,bool is16,bool cover=true)//½âÑ¹Ëõ 
{
	returnif(!checkfile(input),INFILENOTFOUND);
	returnif(checkfile(output)&&!cover,OUTFILEALREADY);
	mhuffcode *huffman=new mhuffcode[512]; 
	for(int i=0;i<512;i++)
	{
		huffman[i].ch=i;
		huffman[i].num=0;
		huffman[i].left=huffman[i].right=NULL;
		huffman[i].isleaf=huffman[i].root=false; 
		huffman[i].code=""; 
	}
	FILE *rd=fopen(input,"rb"),*wt=fopen(output,"wb");
	ull filesize=freadvlq(rd);
	if(!is16)
	  for(int i=0;i<285;i+=1)
	  {
		  U char siz;
		  fread(&siz,1,1,rd);
		  for(int j=0;j<siz;j++)
		    huffman[i].code+="0";
	  }
	else
	  for(int i=0;i+1<286;i+=2)
	  {
		  U char siz;
		  fread(&siz,1,1,rd);
		  for(int j=0;j<((siz&0xf0)>>4);j++)
		    huffman[i].code+="0";
		  for(int j=0;j<(siz&0x0f);j++)
		    huffman[i+1].code+="0";
	  }
	mnumfillcod(huffman);
	hufchar hc;
	int p=0,n=fread(&hc,sizeof(hufchar),1,rd);//96
	bool flag=true;
	binarychar bc;
	ull dfs=getfilesize(input),oksize=1;
	hashmap<string,mhuffcode> hm;
	sort(huffman,huffman+512,mchcmp);
	for(int i=0;i<512;i++)
	  if(huffman[i].code.size())
	    hm.push(huffman[i].code,huffman[i]);
	string fd="";
	bc=hufchar2binarychar(hc);//100 101 10
	while(n)
	{
		for(;p<8;p++)
		{
			fd+=(bc.binary[p]+'0');
			if(hm.findkey(fd))
		    {
			    U short hcs=hm.getvalue(fd).ch;
			    fwrite(&hcs,2,1,wt);
			    filesize-=2;
			    if(!filesize)
			      break;
			    fd="";
	        }
		}
		if(!filesize)
		  break;
		if(p==8)	
		{
			p=0;
			n=fread(&hc,sizeof(hufchar),1,rd);
			bc=hufchar2binarychar(hc);//100 101 10
		}
	}
	fclose(rd);
	fclose(wt);
	return OK;
}
