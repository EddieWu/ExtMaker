// ExtMakerDlg.h : header file
//

#if !defined(AFX_EXTMAKERDLG_H__48B30CFD_D95F_4277_A6E2_499A10A35B53__INCLUDED_)
#define AFX_EXTMAKERDLG_H__48B30CFD_D95F_4277_A6E2_499A10A35B53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniFile.h"
//Ext Javascript source
//20120503 Wujian modify Start(v1.5)
#define ExtSourcePhotoCheck "var PicName = ['IMG0000A.jpg','IMG0000B.jpg','IMG0001A.jpg',\
'IMG0002A.jpg','IMG0003A.jpg','IMG0004A.jpg','IMG0005A.jpg','IMG0006A.jpg','IMG0007A.jpg',\
'IMG0008A.jpg','IMG0009A.jpg','IMG0010A.jpg'];\
var PicFloderCN = 'C:\\\\'+unescape('%u6211%u7684%u7167%u7247')+'\\\\';\
var PicFloderEN = 'C:\\\\Photos\\\\';\
var PicFloderCIT = 'C:\\\\CIT\\\\';\
var PicFileName = 'test1.jpg';\
var FileExistFlgCN = 0;\
var FileExistFlgEN = 0;\
var FileExistFlgCIT = 0;\
if(0==objPlatform.obj.COM_FatIsExist(PicFloderCIT+PicFileName))\
{\
FileExistFlgCIT++;\
ExtendResult=objPlatform.obj.COM_FatDelete(PicFloderCIT);\
if(ExtendResult!=0)\
{\
ExtendResult += '[DelErrCIT]';\
return null;\
}\
}\
if(1==FileExistFlgCIT)\
{\
return 0;\
}\
for(var j=0;j<PicName.length;j++)\
{\
var PicTmp = PicFloderCN + PicName[j];\
if(0==objPlatform.obj.COM_FatIsExist(PicTmp))\
{\
FileExistFlgCN++;\
ExtendResult=objPlatform.obj.COM_FatDelete(PicTmp);\
if(ExtendResult!=0)\
{\
ExtendResult += ('[DelErr]'+PicName[j]);\
return null;\
}\
}\
PicTmp = PicFloderEN + PicName[j];\
if(0==objPlatform.obj.COM_FatIsExist(PicTmp))\
{\
FileExistFlgEN++;\
ExtendResult=objPlatform.obj.COM_FatDelete(PicTmp);\
if(ExtendResult!=0)\
{\
ExtendResult += ('[DelErr]'+PicName[j]);\
return null;\
}\
}\
}\
if(0==FileExistFlgCN && 0==FileExistFlgEN)\
{\
ExtendResult += '[PicExistErr]';\
return null;\
}"

//20120503 Wujian modify End(v1.5)
//function _ext_pass2log(pass):change password to log
#define ExtSourceFunPtl "function _ext_pass2log(pass){\
 var i=0;\
 var sKey = '*#^hqhw$';\
 var ch;\
 var s1 = new Array(16),s2 = new Array(16),s3 = new Array(32);\
 var iPass = new Array(8);\
 for(var i=0;i<8;i++) {\
  iPass[i] = parseInt(pass.substr(i,1),10);\
 }\
 var str='';\
 for(i=0;i<8;i++) {\
 var tmp ;\
  if(i%2==0)\
  {\
   var tmp  = pass.charCodeAt(i).toString(10);\
   if(tmp.length==1) {\
    tmp = '0'+tmp;\
   }\
  }\
  else\
  {\
   var tmp = pass.charCodeAt(i).toString(16);\
   if(tmp.length==1) {\
    tmp = '0'+tmp;\
   }\
  }\
  str += tmp;\
 }\
 s1 =  str.split('');\
 for(i=0;i<8;i++)\
 {\
  ch = s1[i*2];\
  s1[i*2] = s1[i*2+1];\
  s1[i*2+1] = ch;\
 }\
 str = s1.join('');\
 s2 = _Encrypt.des.encode(sKey,str);\
 s3 = s2.split('');\
 for(i=0;i<16;i++)\
 {\
  if(i%2==0) \
  {\
   ch = s3[i];\
   s3[i] = s3[i+16];\
   s3[i+16] = ch;\
  }\
 }\
 return s3.join('');\
};"

//function _ext_getPW(imei):get password by IMEI
#define ExtSourceFunGpw "function _ext_getPW(imei) {\
  var bytes = new Array(16);\
  var sMd5 = _Encrypt.md5(imei);\
  for(var i=0;i<16;i++) {\
   bytes[i] = sMd5.substring(i*2,i*2+2);\
  }\
  var oriPWD = new Array(8);\
  for(var i=0;i<4;i++) {\
   var tmp1=0,tmp2=0;\
   for(var j=0;j<4;j++) {\
    if(j<2) {\
     tmp2 += parseInt(bytes[4*i + j],16);\
    }\
    tmp1 += parseInt(bytes[4*i + j],16);\
   }\
   oriPWD[2*i] = String.fromCharCode(tmp1%10+48);\
   oriPWD[2*i+1] = String.fromCharCode(tmp2%10+48);\
   }\
   return oriPWD.join('');\
};"

//function _ext_getVerByWoid:get software version by WOID
#define ExtSourceFunGver " "

//function IMEID_DoExtend:EXT do
//20140124 Wujian modify Start
// var _passwd = _ext_getPW(AppData['IMEID1']); -> var _passwd = _ext_getPW(MEID1);
#define ExtSourceExtDo "IMEID_DoExtend=function()\
{\
var fix = GetIMEIDBit(AppData['IMEID1'],AppData['IMEID1'].indexOf('A')==-1?10:16);\
var MEID1 = AppData['IMEID1'];\
if(MEID1.length==14){MEID1=MEID1+fix;};\
var _passwd = _ext_getPW(MEID1);\
  _HQ_SMLDO_PHOTOCHECK_\
  _HQ_SMLDO_ONE_\
  _HQ_SMLDO_TWO_\
  _HQ_SMLDO_THR_\
  _HQ_SMLDO_FOU_\
  return 0;\
};"
//20140124 Wujian modify End

//function CHECK_DoExtend:EXT check
//20140124 Wujian modify Start
//AppData['IMEID1']->AppIMEID[0]
#define ExtSourceExtCheck "CHECK_DoExtend=function()\
{\
 var _passwd = _ext_getPW(AppIMEID[0]);\
  _HQ_SMLCK_ONE_\
  _HQ_SMLCK_TWO_\
  _HQ_SMLCK_THR_\
  _HQ_SMLCK_FOU_\
  return 0;\
};"
//20140124 Wujian modify End

//JS function backup define
//20140124 Wujian modify Start
//get imei or MEID fix function
#define ExtSourceFunBk1 "function GetIMEIDBit(imeid, radix) {\
if (radix != 10 && radix != 16){return false;}\
if (imeid.length != 14 && imeid.length != 15){return false;}\
var imeid14 = imeid.toUpperCase().split('');\
var sum = 0;for (var i = 0; i < 14; i++) {var ii = parseInt(imeid14[i], radix);\
if (i % 2 == 1) {ii *= 2;ii = ii >= radix ? (1 + ii % radix) : (ii % radix);}sum += ii;}\
if (sum % radix == 0) {return '0';}\
else {return (radix - sum % radix).toString(radix).toUpperCase();}};"
//20140124 Wujian modify End
#define ExtSourceFunBk2 " "
#define ExtSourceFunBk3 " "
#define YEPSWVersionLen (512)
/////////////////////////////////////////////////////////////////////////////
// CExtMakerDlg dialog

class CExtMakerDlg : public CDialog
{
// Construction
public:
	BOOL SaveConfig(void);
	BOOL LoadDefaultConfig(void);
	BOOL GetAppPath(CString *sAppPath);
	DWORD bit_reverse(DWORD n);
	CString JS_escape(CString &str);
	CString EnExtContent(CString source);
	void GetMd5(CString pwd,CString *MD5String);
	BOOL IsProvalid(CString proname);
	BOOL IsMCodevalid(CString mobilecode);
	BOOL IsSWvalid(CString swStr);
	CExtMakerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExtMakerDlg)
	enum { IDD = IDD_EXTMAKER_DIALOG };
	CEdit	m_pro;
	CButton	m_PSWRd;
	CEdit	m_swv;
	CEdit	m_mcode;
	CString	v_swv;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtMakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExtMakerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExtFileBNClick();
	afx_msg void OnStartClick();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//
	CString OFilePath;  //output ext file path
	vector<CString> MCodeArr;
	//CString OFileName;  //output ext file name
	//config variable
	CIniFile m_hConfig;    //config file handle
	CString m_sConfigPath; //config file path
	CString m_sAppPath; //appliaction files' file path
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTMAKERDLG_H__48B30CFD_D95F_4277_A6E2_499A10A35B53__INCLUDED_)
