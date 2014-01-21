/*
���ߣ�  crazyd <crazydiamondzgy@hotmail.com>
���ڣ�  2002-12-29
˵��:   ��δ�����Ƕ��ʽ���д��,md5��Ϊ���ĵĲ����û��д��
		���кܸߵ������ٶ�,��C����콫������,
		ʹ�÷����ǰ��մ������MD5Init,MD5Update,MD5Final����������
		������ı�׼���룺

��׼���룺
	#include "md5.h"
	void main()
	{
		MD5_CTX context;
		
		MD5Init (&context);
		MD5Update (&context, "crazyd", strlen("crazyd"));
		MD5Final (&context);
	}

����˵����
	context.state[0]��32λ���޷������������������Ԫ��Ҳ��������
	�������ڴ�Ĵ�ź���ʾ�ķ������෴�ģ�����Ҫ�ر�ע�⡣
*/
#include <windows.h>

typedef struct MD5_CTXtag
{
	DWORD state[4];			//encypted message
	DWORD count[2];			//bits of plaintext
	unsigned char buffer[64];
}MD5_CTX;

void MD5InitSelf(MD5_CTX *);
void MD5UpdateSelf(MD5_CTX *, unsigned char *, unsigned int);//�����ܵ��������м��Ǹ�����
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
