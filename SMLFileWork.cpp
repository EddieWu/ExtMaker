// SMLFileWork.cpp: implementation of the SMLFileWork class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExtMaker.h"
#include "SMLFileWork.h"
#include "shlwapi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//20110713 Wujian add Start(v1.2)
#define SMLFileVer 987651
//20110713 Wujian add End(v1.2)
SMLFileWork::SMLFileWork()
{
	char TmpArr[6]={'!','H','Q','S','M','L'};
	memcpy((void*)Head,TmpArr,sizeof(TmpArr));
}

SMLFileWork::~SMLFileWork()
{

}

int SMLFileWork::WriteStrToFile(char *str, char* swstr/*20110713 v1.2*/, char *filepath)
{
	SimLockDataFile  tmpFile;
	//20110713 Wujian modify Start
	//if(StrToStruct( str, tmpFile) == 0)
	if(StrToStruct( str, swstr, tmpFile) == 0)
    //20110713 Wujian modify end
	{
		FILE *file;
		// 锁卡数据 30个字节，3个字节一组，共10组，分配到 TStringList 中，然后进行比较
		if((file = fopen(filepath,"wb"))==NULL)
		{
			AfxMessageBox("Open & Create sml file fail!Try again!");
			return 1;
		}
		//
		//fprintf(file,lockList,sizeof(lockList));
		fwrite(Head, sizeof(Head), 1, file); // 写入文件头
		fwrite((void*)&tmpFile, sizeof(tmpFile), 1, file); /* write struct s to file */
		fclose(file);
    }else
    {
		AfxMessageBox("SimLock list is illegal");
		return 2;
    }
    return 0;
}

int SMLFileWork::StrToStruct(char *str, char* swstr/*20110713 v1.2*/, SimLockDataFile &datafile)
{
	// 将字符串分割后存入数据结构体
	int sum = 0;
    const char *seps = ",";
	char *token;
	int i = 0;
	//20110713 Wujian add Start
    // 如果开头是4个0，那么表示锁网，那么后面的就表示为软件版本识别码
    int ZeroCount = 0;
	//20110713 Wujian add End
	token = strtok(str,seps);
	while (token != NULL) 
	{
		SimLockData tmp;
		//tmp.num = StrToIntDef(lockList->Strings[i],-1);
		//20110713 Wujian add Start(v1.2)
		if(i<UnlockConst && token  == "0" ){
		  ZeroCount++;
		}
		//20110713 Wujian add End(v1.2)
		int RetInt = 0;
		if(!StrToIntEx(token,STIF_SUPPORT_HEX,&RetInt))
		{
			return 1;
		}
        tmp.num = RetInt;
		sum+= tmp.num;
		CString tmpStr = token;
		tmp.len =  tmpStr.GetLength();
		datafile.data[i] = tmp;
		token = strtok(NULL, seps);		
		i++;
	}
	/*
    for(int i=0;i<lockList->Count;i++)
    {
		SimLockData tmp;
		tmp.num = StrToIntDef(lockList->Strings[i],-1);
		if( tmp.num == -1)
		{
			return 1;
		}
		sum+= tmp.num;
		tmp.len =  lockList->Strings[i].Length();
		datafile.data[i] = tmp;
    }
	*/
	//20110713 Wujian add Start(v1.2)
	// 写入软件版本信息
    datafile.bad1[0] = SMLFileVer;
    int verlen =  strlen(swstr)/4+1;
    char* verbuffer = new char[4*verlen];
    memset(verbuffer,0,4*verlen);
    strcpy(verbuffer,swstr);
    int versum = 0;
    // 设置长度
    datafile.bad2[0] = verlen;
    for(int j=0;j<verlen&&j<30;j++)
    {
		datafile.data[j].bad1[0]= verbuffer[4*j]+5;
		datafile.data[j].bad1[2]= verbuffer[4*j+1]+4;
		datafile.data[j].bad2[0]= verbuffer[4*j+2]+3;
		datafile.data[j].bad2[2]= verbuffer[4*j+3]+2;
		versum+= verbuffer[4*j]+verbuffer[4*j+1]+verbuffer[4*j+2]+verbuffer[4*j+3]+14;
    }
    //
    datafile.bad2[1] = versum; // ver的checksum值
    delete []verbuffer;
    //20110713 Wujian add End(v1.2)
    datafile.len = i;//lockList->Count;
    datafile.check = sum;
    return 0;
}
