// SMLFileWork.h: interface for the SMLFileWork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMLFILEWORK_H__69182D37_50FA_408A_81EA_1BFFFD010EBE__INCLUDED_)
#define AFX_SMLFILEWORK_H__69182D37_50FA_408A_81EA_1BFFFD010EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#pragma comment(lib,"Shlwapi.lib")

//20110713 Wujian add Start(v1.2)
// 开头4个0表示 解锁 
#define UnlockConst 4
//20110713 Wujian add End(v1.2)
#define SIMLOCK_MAXNUM 100  // 注意字符对齐
typedef struct SimLockDataTag{
    char bad1[4];    // 混淆    第1,3个数组存放版本，版本总长度小于100个字节(v1.2)
    int  num;        // 由于都是数字，且不超过6位，转换为int类型
    char bad2[4];    // 混淆    第1,3个数组存放版本，版本总长度小于100个字节(v1.2)
    int  len;        // 表示一共几位，可能以0开头
} SimLockData;

typedef struct SimLockDataFileTag{
    int  bad1[2];     // 混淆    第一个数组为987651 表示为SML文件新版本1(v1.2)
    SimLockData data[SIMLOCK_MAXNUM];
    int  bad2[3];     // 混淆    第一个数组为版本的长度/4+1 可以循环多少个data,第二个数组为版本的checksum(v1.2)
    int  len;         // 数据长度
    int  bad3;
    int  check;
} SimLockDataFile;

class SMLFileWork  
{
public:
	//20110713 Wujian modify Start(v1.2)
	/*
	int StrToStruct( char* str, SimLockDataFile &datafile);
	int WriteStrToFile( char* str, char *filepath);
	*/
	int StrToStruct( char* str, char* swstr, SimLockDataFile &datafile);
	int WriteStrToFile( char* str, char* swstr, char *filepath);
	//20110713 Wujian modify End(v1.2)
	SMLFileWork();
	virtual ~SMLFileWork();
private:
	char Head[6];

};

#endif // !defined(AFX_SMLFILEWORK_H__69182D37_50FA_408A_81EA_1BFFFD010EBE__INCLUDED_)
