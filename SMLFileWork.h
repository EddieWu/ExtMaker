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
// ��ͷ4��0��ʾ ���� 
#define UnlockConst 4
//20110713 Wujian add End(v1.2)
#define SIMLOCK_MAXNUM 100  // ע���ַ�����
typedef struct SimLockDataTag{
    char bad1[4];    // ����    ��1,3�������Ű汾���汾�ܳ���С��100���ֽ�(v1.2)
    int  num;        // ���ڶ������֣��Ҳ�����6λ��ת��Ϊint����
    char bad2[4];    // ����    ��1,3�������Ű汾���汾�ܳ���С��100���ֽ�(v1.2)
    int  len;        // ��ʾһ����λ��������0��ͷ
} SimLockData;

typedef struct SimLockDataFileTag{
    int  bad1[2];     // ����    ��һ������Ϊ987651 ��ʾΪSML�ļ��°汾1(v1.2)
    SimLockData data[SIMLOCK_MAXNUM];
    int  bad2[3];     // ����    ��һ������Ϊ�汾�ĳ���/4+1 ����ѭ�����ٸ�data,�ڶ�������Ϊ�汾��checksum(v1.2)
    int  len;         // ���ݳ���
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
