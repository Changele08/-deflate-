//head.hpp,�й���ѹ���ļ�ͷ��
//get:
#define getvers(s) (((s)&0xF000)/0x1000)
#define getfc(s) (((s)&0x800)/0x800) 
#define gethl(s) (((s)&0x400)/0x400)
#define getmp(s) (((s)&0x200)/0x200)
//set:
#define setvers(vs,to) ((to)=((to)&0x0FFF)|((vs)*0x1000)) //vers
#define setfc(vs,to) ((to)=((to)&0xF7FF)|((vs)*0x800)) //halfdistance?
#define sethl(vs,to) ((to)=((to)&0xFBFF)|((vs)*0x400)) //halflile
#define setmp(vs,to) ((to)=((to)&0xFDFF)|((vs)*0x200))//password?
/*
fast:
0:����ѹ��
1��ֻ�������ƥ�� 
2��ƥ�䣬����غϽ�����=morethanbreak
3��ȫƥ�� 
*/ 
/*
0:dawn
1:huffman
2:lzw
3:crlc
4:bag
*/
