//数学相关函数 
//比大小类宏定义
#ifndef __cplusplus
	#error This library is only for C++
#endif 
#ifndef DFLMATH
#define DFLMATH
#define eps 1e-8
#define maxv(a,b) ((a)>(b)?(a):(b)) 
#define minv(a,b) ((a)<(b)?(a):(b) )
#define dequ(a,b)  ((fabs((a)-(b)))<(eps))
#define dmore(a,b) (((a)-(b))>(eps))
#define dless(a,b) (((a)-(b))<(-eps))
#define dme(a,b)   (((a)-(b))>(-eps))
#define dle(a,b)   (((a)-(b))<(eps))
#define PI (3.1415926535898)
#define absolute(a) ((a)>0?(a):-(a) )
#define Ceil(a) (((a)!=(ll)(a))?(ll)(a+1):(ll)(a))
#define Floor(a) ((ll)(a))
#define rounding(a) ((ll)((a)+0.5)) 
#define getdecimal(a) ((long double)(a)-Floor((a)))    
#define lcm(a,b) ((a)*(b)/(gcd((a),(b)))*2) 
#define opposite(a) (-(a))
#define complementary(a,b) ((bool)(a)+(b)==90)
#define supplementary(a,b) ((bool)(a)+(b)==180)  
#define TPC(x,y,x1,y1,x2,y2) ((bool)((((x1)-(x))*((y2)-(y)))==(((x2)-(x))*((y1)-(y)))))//三点共线 
#define Hsplchar2int(o,t,th,f) ((o)*0x1000000+(t)*0x10000+(th)*0x100+(f)*0x01)
#define Hsplchar2ll(o,t,th,f,fi,s,se,e) ((o)*0x100000000000000000000000+(f)*0x100000000+(fi)*0x1000000+(s)*0x10000+(se)*0x100+(e)*0x01)
#define slope(x,y,x1,y1) (((y)-(y1))/(double)((x)-(x1)))//斜率 
#define TAS(s,n,a,x) (((x)*(n)*(n)-3*(x)*(n))/2+(x)+(a)*(n)-(a)+(s))//双等数列求N 
#define sumofOAS(s,m,xs) ((((s)+(m))*(xs))/2)//单等差求和 
#define OAS(s,gc,n) (((n)-1)*(gc)+(s))//单等差第N项 
#define TSD(a,b) (((a)-(b))*((a)+(b))) //平方差 
#define SOM(n) (((n)*((n)-1)*(2*(n)+1))/6) //平方和
#define CS(n) (((n)*(n)*((n)+1)*((n)+1))/4)//立方和 
#include "aboutpav.hpp"
#include "aboutarrays.hpp" 
#endif
inline long double power(long double a,long long b)//求a的b次方 
{
	return (b==0)?1:(a==1)?1.00:(a==-1)?(b%2==0LL)?1:-1:(a==0)?0.00:(b<0)?1.00/power(a,-b):(b>0)?a*1.00*power(a,b-1):1.00;
} 
inline double Sqrt(long long a)
{
	ull less=0;
	for(;less*less<=a;less++);
	less--;
	return less+(a-less*less)/(less*2.0);
}
long double DS(long double a,long long b)//a的圈b次方 
{
	return 1.0/power(a,b-1); 
}
bool isprime(ll prime)
{
	prime=fabs(prime);
	if((prime>10&&prime%10!=1&&prime%10!=3&&prime%10!=7&&prime%10!=9)||(prime==0||prime==1))
	  return false;
	for(ll i=3;i<=sqrt(prime);i+=2)
	  if(prime%i==0)
	    return false;
	return true;
}
ll fibonacci(ll a)//求斐波那契数列 
{
	int b=1,c=1,d;
	if(a==1||a==2)
	  return 1;
	if(a==3)
	  return 2;
	for(int i=3;i<=a;i++)
	{
		d=b+c;
		b=c;
		c=d;
	}
	return d;
}
ull factorial(U I a)//阶乘 
{
	return a>1?a*factorial(a-1):1;
}
ll gcd(ll a,ll b)
{
	ll mod=2;
	for(;(a%mod||b%mod)&&mod<=min(a,b);mod++);
	return (mod>min(a,b))?1:mod*gcd(a/mod,b/mod);
} 
string ull2H(ull to)
{
	string ret="";
	while(to!=0)
	{
		ret+="0123456789ABCDEF"[to%16];
		to/=16;
	}
	reverse(ret.begin(),ret.end());
	return ret; 
} 
template<typename tp>
inline tp manyminv(tp *start,tp *end)
{
	tp *ts=start;
	tp ret=0x3fffff;
	while(ts<=end)
	{
		ret=minv(ret,*ts);
		ts++;
	}  
	return ret;
}
template<typename tp>
inline tp manymaxv(tp *start,tp *end)
{
	tp *ts=start;
	tp ret=0;
	while(ts<=end)
	{
		ret=maxv(ret,*ts);
		ts++;
	}  
	return ret;
}  
