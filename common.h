#ifndef COMMONH
#define COMMONH
//====================
#include <vector>
#include <list>
#include <afxtempl.h>
#include "ErrorCode.h"

using namespace std;
//====================
//常量定义
#define GPIBERR 10000 //GPIBError 起始大小
#define VISAERR 20000 //GPIBError 起始大小
#define SN_LEN (16)//系列号长度
#define ERROR_VALUE 9999.77
#define MAXIDN 110 // IDN查询出的最大长度
//====================
//for Callibration
#define MAX_BANDMODE_LEN (30)//最大频段模式长度
#define MAX_BAND_NUM (4)//最大频段数
#define MAX_STEP (26)//功率Step数
#define GSM900_CHANNEL_NUM (124)//GSM900信道数
#define GSM850_CHANNEL_NUM (124)//GSM850信道数
#define DCS1800_CHANNEL_NUM (374)//DCS信道数
#define PCS1900_CHANNEL_NUM (299)//PCS信道数
#define MAX_PCL_NUM (32)//最大功率等级数目
//====================
#define CHECKEXIT(pRunFlag) if(CheckStopFlag(pRunFlag)==true){return Result_OK;}
//====================

//#define CHECKPRIVILEGE				//是否需要检查权限
#define CHECKLICENSE					//是否需要检查授权信息
#define ENCRYPTCONFIGFILE				//加密配置文件
#define COMPULSIVECALIBRATECABLELOSS	//强制按时校准Cableloss
//#define VERSION_LABORATORY			//实验室版本，去掉所有校验

//设备状态
typedef enum DEVSTATETag
{
		DEVST_CREATE=0,//未知状态，用于创建时
		DEVST_USELESS=1,//不可用
		DEVST_READY=2,//待命
		DEVST_OCCUPIED=3//被占用
}DEVSTATE;

typedef enum BANDMODETag
{
	BAND_GSM900=0,
	BAND_DCS1800,
	BAND_PCS1900,
	BAND_GSM850,
	BAND_USC,
	BAND_LAST
}BANDMODE;

typedef enum RUNFLAGtag
{
	RUNFLAG_NOREADY,
	RUNFLAG_READY,
	RUNFLAG_RUNNING,
	RUNFLAG_STOP,
	RUNFLAG_PAUSE
}RUNFLAG;

//=========================
//Calibration
//AFC校准结果数据结构
typedef struct AFCItemResulttag
{
	short			cdac;
	ULONG			Multiplier;//
	long			slopePPB;//斜率
	unsigned short	nominalAfcValue;
}AFCItemResult;
//AGC校准结果数据结构
typedef struct AGCItemResulttag
{
	CList<unsigned short,unsigned short> *AGCData_GSM900;
	CList<unsigned short,unsigned short> *AGCData_DCS1800;
	CList<unsigned short,unsigned short> *AGCData_GSM850;
	CList<unsigned short,unsigned short> *AGCData_PCS1900;

	CList<short,short> *AGCAccurateData_GSM900;
	CList<short,short> *AGCAccurateData_DCS1800;
	CList<short,short> *AGCAccurateData_GSM850;
	CList<short,short> *AGCAccurateData_PCS1900;

	CList<int , int> *Rssi_GSM900;
	CList<int , int> *Rssi_DCS1800;
	CList<int , int> *Rssi_GSM850;
	CList<int , int> *Rssi_PCS1900;

} AGCItemResult;

//APC校准结果数据结构
typedef struct APCItemResulttag
{
	CList<unsigned short,unsigned short>	*APCData_GSM900;
	CList<unsigned short,unsigned short>	*APCData_GSM850;
	CList<unsigned short,unsigned short>	*APCData_DCS1800;
	CList<unsigned short,unsigned short>	*APCData_PCS1900;
}APCItemResult;
// TxCompItemResult 校准结果数据结构
typedef struct TxCompItemResulttag
{
	CList<unsigned short,unsigned short>	*TxCompData_GSM900;
	CList<unsigned short,unsigned short>	*TxCompData_GSM850;
	CList<unsigned short,unsigned short>	*TxCompData_DCS1800;
	CList<unsigned short,unsigned short>	*TxCompData_PCS1900;
}TxCompItemResult;
//=========================
typedef struct MOBILEINFOtag
{
	CString m_strSubProjectName;
	CString m_strBoxNum;
	CString m_strPalletNum;
	CString m_strIMEI;
	bool    m_bPass;
	CString m_strSN;

	int		m_iTestTime;//测试耗费的时间zjb 070105
	CString m_strFailItem;//zjb 070105
}MOBILEINFO,*pMOBILEINFO;

//测试数据
typedef union TESTITEMRESULTtag
{
	AFCItemResult	afcItemResult;
	AGCItemResult	agcItemResult;
	APCItemResult	apcItemResult;
	TxCompItemResult txcompItemResult;
	MOBILEINFO		*pMobinfo;
	double			rfNumbericResult;	
}TESTITEMRESULT;

//测试项目结果
typedef struct TESTRESULTtag
{
	char			strItemName[50];//测试项目名称
	int 			iItemIndex;
	bool			bResult;//测试结果：Pass、Failed
	TESTITEMRESULT	itemResult;//测试结果数据
}TESTRESULT;
// 测试的spec一般上下界
typedef struct BAND_INDEPENDENT_SPECtag
{
	double	fUpLimit;
	double	fDownLimit;
	double	fExpect; // 期望
}BAND_INDEPENDENT_SPEC;
// 测试模式
typedef enum OpModeTypetag
{
	NOMODE = -1,
	BASE = 0,
	GSM900,
	GSM900_NSIG,
	DCS1800,
	DCS1800_NSIG,
	PCS1900,
	PCS1900_NSIG,
	F_NSIG,
	Audio,
	GSM850,
	GSM850_NSIG,
	GSM900_EDGE,
	DCS1800_EDGE,
	PCS1900_EDGE,
	GSM850_EDGE,
	GSM900_EDGE_SIG,
	DCS1800_EDGE_SIG,
	PCS1900_EDGE_SIG,
	GSM850_EDGE_SIG,
	WCDMA19FDD_SIG,
	WCDMA19FDD_NSIG,
}OpModeType;
//频率误差标准值数据结构
typedef struct FREQUENCYERRSPECTag
{
	OpModeType	bandMode;//频段模式
	double		fLowLimit;//下限值HZ为单位
	double		fUpLimit;//上限值HZ为单位
}FREQUENCYERRSPEC;
//峰值功率标准列表
typedef struct PEAKPOWERSPECTag
{
	OpModeType	bandMode;//频段模式
	int			pcl;//功率控制等级
	double		fLowLimit;//下限
	double		fUpLimit;//上限
	double		fExpect; // 期望
}PEAKPOWERSPEC;

typedef enum TESTITEMSTATEtag
{
	READY=4,EXECUTING=2,FAIL=0,SUCCESS=3
}TESTITEMSTATE;

typedef enum DISPLAYACTIONtag
{
	ADDNEWITEM,//在界面添加一条新记录
	CHANGEITEMSTATE,//在界面上改变测试项目结果状态
	DELETEITEMS,//删除记录
	UPDATEITEM, //更新界面上的最后一行
	PROGRESSBAR,//更改进度条状态
	SHOWSN,//显示SN
	SHOWPASSFAILDLG,//显示测试结果对话框
	SHOWSWVER,//显示软件版本号
	SHOWHWVER,//显示硬件版本号
	SHOWWARNNINGMSG,//显示警告信息
	UPDATELICENSE
}DISPLAYACTION;

typedef struct DISPLAYSTRUCTtag
{
	char m_strIndex[50];
	char m_strItemName[50];
	char m_strLowLimit[50];
	char m_strHighLimit[50];
	char m_strResult[50];

	int     DelCount;
	TESTITEMSTATE m_NewItemState;
	DISPLAYACTION m_DspAction;//如果m_DspAction＝DELETEITEMS,则删除最后连续DelCount行
}DISPLAYSTRUCT;

typedef struct CABLELOSStag
{
	char strTesterName[20];

	char m_strDCSHC[20];
	char m_strDCSLC[20];
	char m_strDCSMC[20];
	char m_strGSMHC[20];
	char m_strGSMLC[20];
	char m_strGSMMC[20];
	char m_strPCSHC[20];
	char m_strPCSLC[20];
	char m_strPCSMC[20];
	//melancholic 20061218 a b for GSM850
	char m_strGSM850HC[20];
	char m_strGSM850LC[20];
	char m_strGSM850MC[20];
	//melancholic 20061218 a e for GSM850

}CABLELOSS;

class YHBaseDevice;
typedef struct DEVTEMPNODEtag
{
//	CString			strName;//设备名称
	char			strName[50];//设备名称
//	CString			strType;//设备类型
	char			strType[50];//设备类型
	YHBaseDevice*	pDevInst;//设备实例指针
	CABLELOSS       Cableloss;
}DEVTEMPNODE;

typedef struct DEVTEMPLATEtag
{
	DEVTEMPNODE m_BatteryDevice;
	DEVTEMPNODE m_ChargerDevice;
	DEVTEMPNODE m_TesterDevice;
	DEVTEMPNODE m_MobileDevice;
	
	bool m_bNeedMobile;
	bool m_bNeedRFTester;
	bool m_bNeedCharger;
	bool m_bNeedBattery;
}DEVTEMPLATE;

// 测试的spec数据
typedef struct RF_PERFORMANCE_SPECtag
{
	FREQUENCYERRSPEC		FrequencyErrorSpec[4/*3*/];//GSM900,DCS1800,PCS1900//melancholic 20061218 m for GSM850
	PEAKPOWERSPEC			PeakPowerSpec_GSM[15];
	PEAKPOWERSPEC			PeakPowerSpec_DCS[16];
	PEAKPOWERSPEC			PeakPowerSpec_PCS[16];
	PEAKPOWERSPEC			PeakPowerSpec_GSM850[15];//melancholic 20061218 a for GSM850

	PEAKPOWERSPEC			CalibratedPowerSpec_GSM[15];
	PEAKPOWERSPEC			CalibratedPowerSpec_DCS[16];
	PEAKPOWERSPEC			CalibratedPowerSpec_PCS[16];
	PEAKPOWERSPEC			CalibratedPowerSpec_GSM850[15];//melancholic 20061218 a for GSM850

	BAND_INDEPENDENT_SPEC	PosFlatNess;
	BAND_INDEPENDENT_SPEC	NegFlatNess;
	BAND_INDEPENDENT_SPEC	PeakPhaseError;
	BAND_INDEPENDENT_SPEC	RMSPhaseError;
	BAND_INDEPENDENT_SPEC	RXQuality;
	BAND_INDEPENDENT_SPEC	CRC;//循环冗余校验
	BAND_INDEPENDENT_SPEC	RBERII;//残余二类误码率
	BAND_INDEPENDENT_SPEC	RxLevel;//BSLevel的上下波动范围
	BAND_INDEPENDENT_SPEC	PVT;//Time Mask
	BAND_INDEPENDENT_SPEC	SwitchSpectrum;//开关频谱
	BAND_INDEPENDENT_SPEC	ModulationSpectrum;//调制频谱

	BAND_INDEPENDENT_SPEC	OffCurrent;
	BAND_INDEPENDENT_SPEC	CurrentDrain;
	BAND_INDEPENDENT_SPEC	HighTemp;// 最高温度
	BAND_INDEPENDENT_SPEC	NormalTemp;
	BAND_INDEPENDENT_SPEC	PreChargeCurrent;
	BAND_INDEPENDENT_SPEC	TATCurrent;
	BAND_INDEPENDENT_SPEC	TXCurrent;

	bool IsLoaded;

	//zjb 060715 b
	BAND_INDEPENDENT_SPEC	LCDBacklightCurrent;
	BAND_INDEPENDENT_SPEC	VibratorCurrent;
	BAND_INDEPENDENT_SPEC	LEDCurrent;
	//zjb 060715 e
	
	BAND_INDEPENDENT_SPEC	FrameErasureRate;//帧擦除率  zjb 060827
	BAND_INDEPENDENT_SPEC	TimingAdvance;//时间提前量  zjb 060827
}RF_PERFORMANCE_SPEC;

//melancholic 20060512 a b for Auto Measure Cableloss
typedef struct RF_GOLDENPOWERtag
{
	//char strTesterName[20];
	char m_strDCSHC[20];
	char m_strDCSLC[20];
	char m_strDCSMC[20];
	char m_strGSMHC[20];
	char m_strGSMLC[20];
	char m_strGSMMC[20];
	char m_strPCSHC[20];
	char m_strPCSLC[20];
	char m_strPCSMC[20];
	//melancholic 20061218 a b for GSM850
	char m_strGSM850HC[20];
	char m_strGSM850LC[20];
	char m_strGSM850MC[20];
	//melancholic 20061218 a e for GSM850
}RF_GOLDENPOWER;
//melancholic 20060512 a e for Auto Measure Cableloss

typedef struct SYSTEMCONFIGtag
{
	char m_sWorkSiteName[100];//工位名称
	char m_sWorkSiteNote[200];//关于该工位的说明
	char m_sSolution[50];//方案名称
	char m_sProjectName[30];//项目名称
	char m_sSubprojectName[30];//子项目名称
	char m_sCurrTestSch[MAX_PATH];//当前测试方案全路径
	char m_sCurrStorer[50];//当前存储方案名称
	
	double m_fVoltageBattery;//当前电池电压
	double m_fVoltageCharger;//当前充电电压
	double m_fCurrentBattery;//当前电池限制电流
	double m_fCurrentCharger;//当前充电限制电流

	RF_PERFORMANCE_SPEC m_TestSpec;//测试结果范围

	RF_GOLDENPOWER m_GoldenPower;//melancholic 20060512 a for Auto Measure Cableloss

	bool m_bUseSim;//是否使用sim卡
	bool m_bOnlyBattery;//测试时只使用battery
	bool m_bRunLocal;//不使用网络数据库

	DWORD m_LicenseNumber;
//	CString m_strLicenseFile;
	char  m_strLicenseFile[MAX_PATH];
}SYSTEMCONFIG;

typedef struct TESTITEMPARAtag
{
	CList<DISPLAYSTRUCT,DISPLAYSTRUCT&>* m_pDisplayArrary;
	vector<double> para1;
	vector<double> para2;
	vector<double> para3;
	vector<double> para4;
	vector<double> para5;
	int  *m_pWriteFlag;
	double fUpLimit;
	double fLowLimit;
	//	vector<double> fTestResult;
	TESTRESULT TestItemResult;

	int iRetryCount;
	//这里添加存储和显示线程使用的

	DEVTEMPLATE* m_pDevTemplate;
	HANDLE		 m_hTest;

	const RUNFLAG* pRunFlag;//zjb 060612 当按下停止测试按钮时测试能够及时停止

}TESTITEMPARA,*pTESTITEMPARA;

typedef RetCode (*TESTFUNCTION)(pTESTITEMPARA);//测试函数指针类型

typedef struct TESTITEMtag//zjb 测试时使用的测试项目列表节点
{
	CString m_sTestItemName;//已清除射频参数，其实这是测试函数的名称
	CString m_sFullTestItemName;//测试项目全名
	int  m_iTestItemIndex;

	double  m_fLowLimit;
	double  m_fHighLimit;
	vector<double>  m_fTestResult;

	bool m_bSave;
	int  m_iRetryCount;

	TESTFUNCTION  TestFunction;
	TESTITEMSTATE m_ItemStatus;
}TESTITEM;

typedef enum OPERATIONStag
{
	NOOPERATION=0,
	OPER_ADDNEW,
	OPER_DELETE,
	OPER_MODIFY
}OPERATIONS;

typedef struct TESTITEMLISTtag//zjb 测试项目节点，在测试项目管理器和测试项目管理对话框中使用
{
	CString		m_sTestItemName;
	int			m_iTestItemIndex;
	OPERATIONS	m_TestItemState;//zjb 061231; 只用于测试项目管理对话框中,标识测试项目是否需要保存 
}TESTITEMLIST;

typedef struct RFSETTINGtag//zjb 当前测试模块的射频设置:频段、频道、功率等级、基站功率等
{
	OpModeType  m_eTestBand;
	int  m_iChannel;
	int  m_iPCL;
	int  m_iBSLevelHigh;
	int  m_iBSLevelLow;
}RFSETTING;

typedef struct TESTMODULEtag//zjb 测试时使用的模块列表，在测试序列对象中使用
{
	CString m_sModuleName;
	int  m_iModuleIndex;
	RFSETTING m_RFSetting;

	vector<TESTITEM> m_vTestItemList;//当前测试模块包含的测试项目
}TESTMODULE;

typedef struct TESTMODULELISTtag//zjb 所有测试模块的列表，仅在测试项目管理器中使用
{
	CString	m_sModuleName;
	int		m_iModuleIndex;
	OPERATIONS m_TestModuleState;
}TESTMODULELIST;

typedef enum RESULTSTATEtag
{
	RESULTST_PASS,
	RESULTST_FAIL,
	RESULTST_NONE
}RESULTSTATE;

typedef enum MOBILEMODEtag
{
	TESTMODE,
	NORMALMODE
}MOBILEMODE;

typedef struct STORERITEMtag
{
	CString m_strName;
	CString m_strNewName;
	CString m_strDatabaseName;
	CString m_strServer;
	CString m_strPassWord;
	CString m_strUser;
	CString m_strType;
	bool    m_bInitialized;
}STORERITEM;

//====================
//extern void GetSystemDir(CString &strDir);//取得测试系统目录
extern CString GetSelfVersion(); //获取版本号
extern CString GetShortIDN(char* str); //获取简短的IDN
extern void GetSystemDllDir(CString &strDir); // 得到DLL 的目录
extern BOOL GetSystemSerialComport(CArray<CString,CString> &comarray);
extern void SplitStr(LPCTSTR source, LPCTSTR seprator, vector<CString> *DesArray);
extern TCHAR** ExtractStr(LPCTSTR source, LPCTSTR seprator, int *count);
extern void FreeStrings(TCHAR **lpstr, int count);
extern void GetMd5(CString pwd,CString *MD5String); // 获取MD5码
extern bool CheckFileValidity(CString filename);
extern bool CheckRole(int flag);/*
0	用户管理浏览
1	用户管理设置
2	更改密码
3	系统配置浏览
4	系统配置设置
5	所有设备浏览
6	所有设备设置
7	设备列表浏览
8	设备列表设置
9	设备模板浏览
10	设备模板设置
11	线损浏览
12	线损设置
13	测试方案浏览
14	测试方案设置
15	测试系列浏览
16	测试系列设置
17	存储方式浏览
18	存储方式设置
19	测试标准浏览
20	测试标准设置
21	数据统计浏览
22	项目配置权限
 */
//====================
//登陆系统用户及其角色信息

#ifdef MFTSYSTEM
typedef struct SYS_USER_Tag
{
	CString UserName;
	CString UserPassword;
	CString RoleName;
	DWORD64 PrivilegeCode;
	int  RoleCode;

	SYS_USER_Tag(CString strUsername,CString strUserpassword,CString strRolename,DWORD64 PrivilegeCodetemp,int Rolecodetemp)
	{
		UserName=strUsername;
		UserPassword=strUserpassword;
		RoleName=strRolename;
		PrivilegeCode=PrivilegeCodetemp;
		RoleCode=Rolecodetemp;
	};
}SYS_USER;
#endif

typedef enum SWITCHFLAGtag
{
	ON=0,
	OFF
}SWITCHFLAG;

typedef enum STATIONFLAGtag
{
	BTFT_FLAG=0,
	BT_FLAG,
	FT_FLAG
}STATIONFLAG;

typedef YHBaseDevice* ( * DEVFUNCTION)( void );

//抓取所有错误信息，包括数据库操作错误
#define MYCATCH(b,c) \
	catch(const _com_error& e)\
{\
	CString sBuff = GetProviderError(c);\
	if(sBuff.IsEmpty())\
{\
	sBuff=GetComError(e);\
}\
	AfxMessageBox(sBuff);\
	b\
}\
	catch(COleException* e)\
{\
	if(e)\
{\
	TCHAR szMsg[255];\
	e->GetErrorMessage(szMsg, 255);\
	AfxMessageBox(szMsg);\
	e->Delete();\
}\
	b\
}\
	catch(COleDispatchException* e)\
{\
	if(e)\
{\
	AfxMessageBox(e->m_strDescription);\
	e->Delete();\
}\
	b\
}\
	catch(CMemoryException* e)\
{\
	if(e) e->Delete();\
	AfxMessageBox(_T("Out-of-memory."));\
	b\
}\
	catch(LPCTSTR e)\
{\
	AfxMessageBox(e);\
	b\
}\
	catch(...)\
{\
	AfxMessageBox(TEXT("<Unexpected Error>"));\
	b\
}

//这个宏抓常规错误信息，没有数据库错误信息
#define MYCATCH_B(a)\
	catch(const _com_error& e)\
{\
	CString sBuff;\
	AfxMessageBox(GetComError(e));\
	a\
}\
	catch(COleException* e)\
{\
	if(e)\
{\
	TCHAR szMsg[255];\
	e->GetErrorMessage(szMsg, 255);\
	AfxMessageBox(szMsg);\
	e->Delete();\
}\
	a\
}\
	catch(COleDispatchException* e)\
{\
	if(e)\
{\
	AfxMessageBox(e->m_strDescription);\
	e->Delete();\
}\
	a\
}\
	catch(CMemoryException* e)\
{\
	if(e) e->Delete();\
	AfxMessageBox(_T("Out-of-memory."));\
	a\
}\
	catch(LPCTSTR e)\
{\
	AfxMessageBox(e);\
}\
	catch(...)\
{\
	AfxMessageBox(TEXT("<Unexpected Error>"));\
	a\
}

typedef enum CURRENTTESTMODEtag
{
	OFFCURRENT,
	STANDBYCURRENT,
	NOCTMODE
}CURRENTTESTMODE;

//从SystemDeviceDlg.h中转移到这里
typedef struct DEVINFOITEMtag
{
	CString	strName;
	CString	strType;
	CString	strDLLName;
	CString	strAddress;
	CString	strInterface;
	CString strBoard;//GPIB卡的系统编号，只有GPIB设备会用到这个,也用作波特率
}DEVINFOITEM;

typedef struct DEVTEMPLATEITEMtag
{
	CString m_sName;
	CString m_sNewName;
	CString m_sBattery;
	CString m_sCharger;
	CString m_sRFTester;
	CString m_sMobile;
}DEVTEMPLATEITEM;

typedef struct TESTSCHINFOtag
{
	CString strSchName;
	CString strType;
	CString strDeviceList;
	CString strTestSeqs;
}TESTSCHINFO;

#endif
