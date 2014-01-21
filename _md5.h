/*
作者：  crazyd <crazydiamondzgy@hotmail.com>
日期：  2002-12-29
说明:   这段代码用嵌入式汇编写成,md5最为核心的部分用汇编写成
		具有很高的运算速度,比C代码快将近两倍,
		使用方法是按照次序调用MD5Init,MD5Update,MD5Final这三个函数
		如下面的标准代码：

标准代码：
	#include "md5.h"
	void main()
	{
		MD5_CTX context;
		
		MD5Init (&context);
		MD5Update (&context, "crazyd", strlen("crazyd"));
		MD5Final (&context);
	}

特殊说明：
	context.state[0]是32位的无符号整数，后面的数组元素也是这样，
	他们在内存的存放和显示的方向是相反的，所以要特别注意。
*/
#include <windows.h>

typedef struct MD5_CTXtag
{
	DWORD state[4];			//encypted message
	DWORD count[2];			//bits of plaintext
	unsigned char buffer[64];
}MD5_CTX;

void MD5InitSelf(MD5_CTX *);
void MD5UpdateSelf(MD5_CTX *, unsigned char *, unsigned int);//待加密的明文是中间那个参数
void MD5FinalSelf(MD5_CTX *);

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define a esi
#define b edi
#define c edx
#define d ebx
#define tmp1 eax
#define tmp2 ecx

#define x(i) [x+4*i]

static void MD5Transform (DWORD [4], unsigned char [64]);

static unsigned char PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define FF(a, b, c, d, x, s, ac) \
	__asm mov tmp1,b \
	__asm and tmp1,c \
	__asm mov tmp2,b \
	__asm not tmp2 \
	__asm and tmp2,d \
	__asm or tmp2,tmp1 \
	__asm lea a,[tmp2+a+ac] \
	__asm add a,x \
	__asm rol a,s \
	__asm add a,b \

#define GG(a, b, c, d, x, s, ac) \
	__asm mov tmp1,b \
	__asm and tmp1,d \
	__asm mov tmp2,d \
	__asm not tmp2 \
	__asm and tmp2,c \
	__asm or tmp2,tmp1 \
	__asm lea a,[tmp2+a+ac] \
	__asm add a,x \
	__asm rol a,s \
	__asm add a,b 

#define HH(a,b,c, d, x, s, ac) \
	__asm mov tmp2,b \
	__asm xor tmp2,c \
	__asm xor tmp2,d \
	__asm lea a,[tmp2+a+ac] \
	__asm add a,x \
	__asm rol a,s \
	__asm add a,b

#define II(a, b, c, d, x, s, ac) \
	__asm mov tmp2,d \
	__asm not tmp2 \
	__asm or tmp2,b \
	__asm xor tmp2,c \
	__asm lea a,[tmp2+a+ac] \
	__asm add a,x \
	__asm rol a,s \
	__asm add a,b
