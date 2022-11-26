#include "../headerfile/dawn.hpp"
using namespace std;
#include "../headerfile/devfunctionlibrary/standard_template_library/queue.hpp"
bool msizecmp(mhuffcode a,mhuffcode b)
{
	return a.code.size()<b.code.size();
} 
bool mchcmp(mhuffcode a,mhuffcode b)
{
	return a.ch<b.ch;
}
bool mhuffmanSRH(mhuffcode *a,mhuffcode *b)//huffmanС���ѽ��� 
{
	return a->num<b->num;
}
bool sizecmp(huffcode a,huffcode b)
{
	return a.code.size()<b.code.size();
} 
bool chcmp(huffcode a,huffcode b)
{
	return a.ch<b.ch;
}
bool huffmandown(mhuffcode a,mhuffcode b)
{
	return a.num>b.num; 
} 
void fillcod(huffcode *huffman)
{
	sort(huffman,huffman+256,chcmp);
	sort(huffman,huffman+256,sizecmp);
	int t=0;
	for(;huffman[t].code.size()==0;t++);
	ull icode=1;
	for(int i=0;i<huffman[t].code.size();i++)
	  icode=icode<<1;
	for(int i=t;huffman[i].code.size();i++)
	{
		ull tmp=icode++;
		huffman[i].code="";
		while(tmp!=1)
		{
			huffman[i].code+=((tmp%2)+'0');
			tmp/=2; 
		}
		reverse(huffman[i].code.begin(),huffman[i].code.end());
		if(i==255)
		  break;
		if(huffman[i].code.size()!=huffman[i+1].code.size())
		  icode=icode<<(huffman[i+1].code.size()-huffman[i].code.size());
	}
}
void mnumfillcod(mhuffcode *huffman)
{
	sort(huffman,huffman+285,mchcmp);
	sort(huffman,huffman+512,msizecmp);
	int t=0;
	for(;huffman[t].code.size()==0;t++);
	ull icode=1;
	for(int i=0;i<huffman[t].code.size();i++)
	  icode=icode<<1;
	for(int i=t;huffman[i].code.size();i++)
	{
		ull tmp=icode++;
		huffman[i].code="";
		while(tmp!=1)
		{
			huffman[i].code+=((tmp%2)+'0');
			tmp/=2; 
		}
		reverse(huffman[i].code.begin(),huffman[i].code.end());
		if(i==511)
		  break;
		if(huffman[i].code.size()!=huffman[i+1].code.size())
		  icode=icode<<(huffman[i+1].code.size()-huffman[i].code.size());
	}
}
void mfillcode(mhuffcode *fill,string thiscode)
{
	fill->code=thiscode;
	if(fill->left!=NULL&&fill->right!=NULL)
	{
		mfillcode(fill->left,thiscode+'0');
	    mfillcode(fill->right,thiscode+'1');
	}
	return;
}
void mmakehuffmancode(mhuffcode huffman[512])
{
	for(int i=0;i<512;i++)//�����벿������,�����ڵ�ȡ�� 
	{
		huffman[i].root=false;
	    huffman[i].code="";
	}
	priorityqueue<mhuffcode *,mhuffmanSRH> pq;//����С���� 
	mhuffcode sv[1024];
	sort(huffman,huffman+512,huffmandown);
	returnif(huffman[0].num==0,);//û�в���� 
	if(huffman[0].num!=0&&huffman[1].num==0)//ֻ��һ������� 
	{
		huffman[0].code="0";
		return;
	}
	int p=0,t=0;//p:sv����ѡ��,t:���ƻصı���ѡ��
	for(int i=0;i<512;i++)//���������� 
	  if(huffman[i].num!=0)
	  {
	  	  sv[p]=huffman[i];
	  	  sv[p].isleaf=true;
	  	  pq.push(&sv[p++]);
	  } 
	while(!pq.empty())//����huffman�� 
	{
		sv[p].left=pq.top();
		pq.pop();
		if(pq.empty())//root�������� 
		  break;
		sv[p].right=pq.top();
		pq.pop();
		sv[p].num=sv[p].left->num+sv[p].right->num;
		sv[p].isleaf=sv[p].root=false;
		pq.push(&sv[p++]);
	}  
	sv[p-1].root=true;//���һ�����Ǹ��ڵ� 
	mfillcode(&sv[p-1],"");//fillcode(�ڼ����ڵ㣬��һ������),�ݹ�һ¥�Ǹ��ڵ㣬����codeΪ��  
	for(int i=0;i<512;i++)//�ص�ǰ��� 
	{
		huffman[i].ch=i;
		huffman[i].num=0;
		huffman[i].left=huffman[i].right=NULL;
		huffman[i].isleaf=huffman[i].root=false; 
		huffman[i].code=""; 
	}
	for(int i=0;i<p;i++)
	  if(sv[i].isleaf)
	  	huffman[sv[i].ch]=sv[i];
	return; 
}
