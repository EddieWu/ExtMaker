#ifndef COMMONH
#define COMMONH
//====================
#include <vector>
#include <list>
#include <afxtempl.h>
#include "ErrorCode.h"

using namespace std;
//====================
//��������
#define GPIBERR 10000 //GPIBError ��ʼ��С
#define VISAERR 20000 //GPIBError ��ʼ��С
#define SN_LEN (16)//ϵ�кų���
#define ERROR_VALUE 9999.77
#define MAXIDN 110 // IDN��ѯ������󳤶�
//====================
//for Callibration
#define MAX_BANDMODE_LEN (30)//���Ƶ��ģʽ����
#define MAX_BAND_NUM (4)//���Ƶ����
#define MAX_STEP (26)//����Step��
#define GSM900_CHANNEL_NUM (124)//GSM900�ŵ���
#define GSM850_CHANNEL_NUM (124)//GSM850�ŵ���
#define DCS1800_CHANNEL_NUM (374)//DCS�ŵ���
#define PCS1900_CHANNEL_NUM (299)//PCS�ŵ���
#define MAX_PCL_NUM (32)//����ʵȼ���Ŀ
//====================
#define CHECKEXIT(pRunFlag) if(CheckStopFlag(pRunFlag)==true){return Result_OK;}
//====================

//#define CHECKPRIVILEGE				//�Ƿ���Ҫ���Ȩ��
#define CHECKLICENSE					//�Ƿ���Ҫ�����Ȩ��Ϣ
#define ENCRYPTCONFIGFILE				//���������ļ�
#define COMPULSIVECALIBRATECABLELOSS	//ǿ�ư�ʱУ׼Cableloss
//#define VERSION_LABORATORY			//ʵ���Ұ汾��ȥ������У��

//�豸״̬
typedef enum DEVSTATETag
{
		DEVST_CREATE=0,//δ֪״̬�����ڴ���ʱ
		DEVST_USELESS=1,//������
		DEVST_READY=2,//����
		DEVST_OCCUPIED=3//��ռ��
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
//AFCУ׼������ݽṹ
typedef struct AFCItemResulttag
{
	short			cdac;
	ULONG			Multiplier;//
	long			slopePPB;//б��
	unsigned short	nominalAfcValue;
}AFCItemResult;
//AGCУ׼������ݽṹ
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

//APCУ׼������ݽṹ
typedef struct APCItemResulttag
{
	CList<unsigned short,unsigned short>	*APCData_GSM900;
	CList<unsigned short,unsigned short>	*APCData_GSM850;
	CList<unsigned short,unsigned short>	*APCData_DCS1800;
	CList<unsigned short,unsigned short>	*APCData_PCS1900;
}APCItemResult;
// TxCompItemResult У׼������ݽṹ
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

	int		m_iTestTime;//���Ժķѵ�ʱ��zjb 070105
	CString m_strFailItem;//zjb 070105
}MOBILEINFO,*pMOBILEINFO;

//��������
typedef union TESTITEMRESULTtag
{
	AFCItemResult	afcItemResult;
	AGCItemResult	agcItemResult;
	APCItemResult	apcItemResult;
	TxCompItemResult txcompItemResult;
	MOBILEINFO		*pMobinfo;
	double			rfNumbericResult;	
}TESTITEMRESULT;

//������Ŀ���
typedef struct TESTRESULTtag
{
	char			strItemName[50];//������Ŀ����
	int 			iItemIndex;
	bool			bResult;//���Խ����Pass��Failed
	TESTITEMRESULT	itemResult;//���Խ������
}TESTRESULT;
// ���Ե�specһ�����½�
typedef struct BAND_INDEPENDENT_SPECtag
{
	double	fUpLimit;
	double	fDownLimit;
	double	fExpect; // ����
}BAND_INDEPENDENT_SPEC;
// ����ģʽ
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
//Ƶ������׼ֵ���ݽṹ
typedef struct FREQUENCYERRSPECTag
{
	OpModeType	bandMode;//Ƶ��ģʽ
	double		fLowLimit;//����ֵHZΪ��λ
	double		fUpLimit;//����ֵHZΪ��λ
}FREQUENCYERRSPEC;
//��ֵ���ʱ�׼�б�
typedef struct PEAKPOWERSPECTag
{
	OpModeType	bandMode;//Ƶ��ģʽ
	int			pcl;//���ʿ��Ƶȼ�
	double		fLowLimit;//����
	double		fUpLimit;//����
	double		fExpect; // ����
}PEAKPOWERSPEC;

typedef enum TESTITEMSTATEtag
{
	READY=4,EXECUTING=2,FAIL=0,SUCCESS=3
}TESTITEMSTATE;

typedef enum DISPLAYACTIONtag
{
	ADDNEWITEM,//�ڽ������һ���¼�¼
	CHANGEITEMSTATE,//�ڽ����ϸı������Ŀ���״̬
	DELETEITEMS,//ɾ����¼
	UPDATEITEM, //���½����ϵ����һ��
	PROGRESSBAR,//���Ľ�����״̬
	SHOWSN,//��ʾSN
	SHOWPASSFAILDLG,//��ʾ���Խ���Ի���
	SHOWSWVER,//��ʾ����汾��
	SHOWHWVER,//��ʾӲ���汾��
	SHOWWARNNINGMSG,//��ʾ������Ϣ
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
	DISPLAYACTION m_DspAction;//���m_DspAction��DELETEITEMS,��ɾ���������DelCount��
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
//	CString			strName;//�豸����
	char			strName[50];//�豸����
//	CString			strType;//�豸����
	char			strType[50];//�豸����
	YHBaseDevice*	pDevInst;//�豸ʵ��ָ��
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

// ���Ե�spec����
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
	BAND_INDEPENDENT_SPEC	CRC;//ѭ������У��
	BAND_INDEPENDENT_SPEC	RBERII;//�������������
	BAND_INDEPENDENT_SPEC	RxLevel;//BSLevel�����²�����Χ
	BAND_INDEPENDENT_SPEC	PVT;//Time Mask
	BAND_INDEPENDENT_SPEC	SwitchSpectrum;//����Ƶ��
	BAND_INDEPENDENT_SPEC	ModulationSpectrum;//����Ƶ��

	BAND_INDEPENDENT_SPEC	OffCurrent;
	BAND_INDEPENDENT_SPEC	CurrentDrain;
	BAND_INDEPENDENT_SPEC	HighTemp;// ����¶�
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
	
	BAND_INDEPENDENT_SPEC	FrameErasureRate;//֡������  zjb 060827
	BAND_INDEPENDENT_SPEC	TimingAdvance;//ʱ����ǰ��  zjb 060827
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
	char m_sWorkSiteName[100];//��λ����
	char m_sWorkSiteNote[200];//���ڸù�λ��˵��
	char m_sSolution[50];//��������
	char m_sProjectName[30];//��Ŀ����
	char m_sSubprojectName[30];//����Ŀ����
	char m_sCurrTestSch[MAX_PATH];//��ǰ���Է���ȫ·��
	char m_sCurrStorer[50];//��ǰ�洢��������
	
	double m_fVoltageBattery;//��ǰ��ص�ѹ
	double m_fVoltageCharger;//��ǰ����ѹ
	double m_fCurrentBattery;//��ǰ������Ƶ���
	double m_fCurrentCharger;//��ǰ������Ƶ���

	RF_PERFORMANCE_SPEC m_TestSpec;//���Խ����Χ

	RF_GOLDENPOWER m_GoldenPower;//melancholic 20060512 a for Auto Measure Cableloss

	bool m_bUseSim;//�Ƿ�ʹ��sim��
	bool m_bOnlyBattery;//����ʱֻʹ��battery
	bool m_bRunLocal;//��ʹ���������ݿ�

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
	//������Ӵ洢����ʾ�߳�ʹ�õ�

	DEVTEMPLATE* m_pDevTemplate;
	HANDLE		 m_hTest;

	const RUNFLAG* pRunFlag;//zjb 060612 ������ֹͣ���԰�ťʱ�����ܹ���ʱֹͣ

}TESTITEMPARA,*pTESTITEMPARA;

typedef RetCode (*TESTFUNCTION)(pTESTITEMPARA);//���Ժ���ָ������

typedef struct TESTITEMtag//zjb ����ʱʹ�õĲ�����Ŀ�б�ڵ�
{
	CString m_sTestItemName;//�������Ƶ��������ʵ���ǲ��Ժ���������
	CString m_sFullTestItemName;//������Ŀȫ��
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

typedef struct TESTITEMLISTtag//zjb ������Ŀ�ڵ㣬�ڲ�����Ŀ�������Ͳ�����Ŀ����Ի�����ʹ��
{
	CString		m_sTestItemName;
	int			m_iTestItemIndex;
	OPERATIONS	m_TestItemState;//zjb 061231; ֻ���ڲ�����Ŀ����Ի�����,��ʶ������Ŀ�Ƿ���Ҫ���� 
}TESTITEMLIST;

typedef struct RFSETTINGtag//zjb ��ǰ����ģ�����Ƶ����:Ƶ�Ρ�Ƶ�������ʵȼ�����վ���ʵ�
{
	OpModeType  m_eTestBand;
	int  m_iChannel;
	int  m_iPCL;
	int  m_iBSLevelHigh;
	int  m_iBSLevelLow;
}RFSETTING;

typedef struct TESTMODULEtag//zjb ����ʱʹ�õ�ģ���б��ڲ������ж�����ʹ��
{
	CString m_sModuleName;
	int  m_iModuleIndex;
	RFSETTING m_RFSetting;

	vector<TESTITEM> m_vTestItemList;//��ǰ����ģ������Ĳ�����Ŀ
}TESTMODULE;

typedef struct TESTMODULELISTtag//zjb ���в���ģ����б����ڲ�����Ŀ��������ʹ��
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
//extern void GetSystemDir(CString &strDir);//ȡ�ò���ϵͳĿ¼
extern CString GetSelfVersion(); //��ȡ�汾��
extern CString GetShortIDN(char* str); //��ȡ��̵�IDN
extern void GetSystemDllDir(CString &strDir); // �õ�DLL ��Ŀ¼
extern BOOL GetSystemSerialComport(CArray<CString,CString> &comarray);
extern void SplitStr(LPCTSTR source, LPCTSTR seprator, vector<CString> *DesArray);
extern TCHAR** ExtractStr(LPCTSTR source, LPCTSTR seprator, int *count);
extern void FreeStrings(TCHAR **lpstr, int count);
extern void GetMd5(CString pwd,CString *MD5String); // ��ȡMD5��
extern bool CheckFileValidity(CString filename);
extern bool CheckRole(int flag);/*
0	�û��������
1	�û���������
2	��������
3	ϵͳ�������
4	ϵͳ��������
5	�����豸���
6	�����豸����
7	�豸�б����
8	�豸�б�����
9	�豸ģ�����
10	�豸ģ������
11	�������
12	��������
13	���Է������
14	���Է�������
15	����ϵ�����
16	����ϵ������
17	�洢��ʽ���
18	�洢��ʽ����
19	���Ա�׼���
20	���Ա�׼����
21	����ͳ�����
22	��Ŀ����Ȩ��
 */
//====================
//��½ϵͳ�û������ɫ��Ϣ

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

//ץȡ���д�����Ϣ���������ݿ��������
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

//�����ץ���������Ϣ��û�����ݿ������Ϣ
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

//��SystemDeviceDlg.h��ת�Ƶ�����
typedef struct DEVINFOITEMtag
{
	CString	strName;
	CString	strType;
	CString	strDLLName;
	CString	strAddress;
	CString	strInterface;
	CString strBoard;//GPIB����ϵͳ��ţ�ֻ��GPIB�豸���õ����,Ҳ����������
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
