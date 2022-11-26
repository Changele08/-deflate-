#include "../headerfile/devfunctionlibrary/aboutvariable.hpp"
#include "../headerfile/devfunctionlibrary/stdc++.hpp"
#define printtitle printdawntitle
#define WRONGPASSWORD 1//ops 
#define UNKNOWERROR 2//ops
#define INFILENOTFOUND 3
#define OUTFILECANTOPEN 4
#define OUTFILEALREADY 4
#define OUTFILEOPENERROR 4
#define COMPRESSOK 5
#define ALLOK 5
#define OK 5
#define MERGERFILESERROR 6 
#define INFILEOPENERROR 1
#define COMPRESSFILEBREAK 7
#define FILEBREAK 7
#define MEMORYISNOTENOUGH 8
#define VTL 9 
#define ASCIIchar2int(a) ((U char)(a))
#define addkzm(to,add) ((to)=((to).size()<=3||(to).substr((to).size()-4,4)!=(add))?(to)+(add):(to))
#define IL inline
#define Cc (char *)//Const char* 2 Char *
#define MB 1000000
#define syspause system("pause")
#ifndef DFLMATH
#define DFLMATH
#define Ceil ceil
#endif
#define returnif(a,ret) if((a)) return ret
using namespace std;
#ifndef HUFFM
#define HUFFM
#define hufchar U char
struct huffcode
{
	ull num;   //字符个数 
	U char ch; //所表示字符 
	bool isleaf,root;//是叶节点，是根节点 
	string code; //编码 
	huffcode *left,*right;//左右子树 
};
struct binarychar
{
	bool binary[8];
};
#endif
struct mhuffcode
{
	ull num;   //字符个数 
	U short ch; //所表示字符 
	bool isleaf,root;//是叶节点，是根节点 
	string code; //编码 
	mhuffcode *left,*right;//左右子树 
};
struct fileinfo
{
	string filename;
	ull size;
};
extern ull getfilesize(char *file);
extern bool checkfile(char *filename);
extern void getpassword(string &password);
extern unsigned char Sbox[256];
extern short opsenc(unsigned char *to,unsigned char *readbuf,ull n,unsigned char *key,unsigned char *sbox);
extern short opsdec(unsigned char *to,unsigned char *readbuf,int n,unsigned char *key,unsigned char *nsbox);
//main
extern int getfileinargv(char *argv[],int size,int tms);
extern int getargvcom(char *argv[],int size,char *get);
extern int huffmanfilecompress(const char *file,const char *of,ull &nfs,bool &is16,bool cover);
extern int huffmanfiledecompress(const char *input,const char *output,bool is16,bool cover);
extern short bag(int argc,vector<string> argv,ull &hdsize,bool cover);
extern short unbag(int argc,char *argv,bool cover);
extern bool copyfile(char *from,char *to,bool cover);
extern long long string2int(string a);
extern short dawncompress(char *inf,char *of,unsigned int dsize,bool cover,bool usehuffman,bool mp,bool ty,string password,ll jmsz,U I fast,U I easywindowsize,U I mtfsize,bool automtf,bool debug);
extern short dawndecompress(char *inf,char *outf,bool cover,string password,bool debug);
extern short getlist(char *input,vector<string> &files,string password);
extern void errors(char *color,char *title,char *error); 
extern int getlastfile(char *argv[],int size);
extern short crlc(char *in,char *out,int mod,bool huf,bool coverout);
extern int lzwdec(char *inf,char*outf,bool cover);
extern int lzwcprs(char *inf,char *outf,bool cover);
//huffman
extern void fillcod(huffcode *huffman);
extern void mnumfillcod(mhuffcode *huffman);
extern void mmakehuffmancode(mhuffcode huffman[512]);
extern bool sizecmp(huffcode a,huffcode b);
extern bool chcmp(huffcode a,huffcode b);
extern bool sizecmp(huffcode a,huffcode b);
extern bool mchcmp(mhuffcode a,mhuffcode b);
extern bool msizecmp(mhuffcode a,mhuffcode b);
extern ull Hstring2int(string change);
extern void makehuffmancode(huffcode huffman[256]);
extern hufchar binarychar2hufchar(binarychar bin);
extern binarychar hufchar2binarychar(hufchar hs);
//dawn:
extern void delfile(string filename);
extern short mgfile(vector<fileinfo> files,string outfile,bool cover);
extern void halffile2(char *inf,char *outf,char *outf2);
extern void halffile1(char *inf,char *outf,char *outf2);
extern void tryout(short &num,binarychar &bc,FILE *file,ull &change);
extern int shhuffmanfilecompress(char *file,char *of,ull &nfs,bool &is16,bool cover);
extern int shhuffmanfiledecompress(char *input,char *output,bool is16,bool cover);
extern short opsfileencode(const char *inf,const char *outf,string password,ull &flsz,bool cover);
extern short opsfiledecode(char *inf,char *outf,string password,bool cover);
extern void dellist(string *filelist,int siz);
extern bool checklist(string *filelist,int size);
extern int fwritevlq(FILE *wt,ull vlq);
extern ull freadvlq(FILE *rd);
extern void copyFILE(FILE *rd,char *out,ull sz);
extern short split(FILE *rd,U short head,string password);
//fileio:
extern int int2vlq(ull num,unsigned char *vlq);
extern ull vlq2int(unsigned char *vlq);
extern bool mergerfiles(char *infile,char *infile1,char *outfile,bool cover);
