// ExtMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtMaker.h"
#include "ExtMakerDlg.h"
#include "SMLFileWork.h"
#include "md5.h"
#include "_md5.h"
#include "base64.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtMakerDlg dialog

CExtMakerDlg::CExtMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtMakerDlg)
	v_swv = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//initialize variable
	OFilePath = "";  //output ext file path
	//OFileName = "";  //output ext file name
	MCodeArr.clear();  //mobile country network code vector
}

void CExtMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtMakerDlg)
	DDX_Control(pDX, IDC_EDIT2, m_pro);
	DDX_Control(pDX, IDC_RADIO1, m_PSWRd);
	DDX_Control(pDX, IDC_EDIT3, m_swv);
	DDX_Control(pDX, IDC_EDIT1, m_mcode);
	DDX_Text(pDX, IDC_EDIT3, v_swv);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtMakerDlg, CDialog)
	//{{AFX_MSG_MAP(CExtMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnExtFileBNClick)
	ON_BN_CLICKED(IDC_BUTTON2, OnStartClick)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtMakerDlg message handlers

BOOL CExtMakerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//set input textbox's attribute
	//SetLimitText()
    //((CEdit *)GetDlgItem(IDC_EDIT3))->SetLimitText(2);
	m_swv.SetLimitText(40);
	m_mcode.SetLimitText(209);
	m_pro.SetLimitText(12);
	//this->SetFocus()
	m_swv.SetFocus();
    //m_PSWRd.SetCheck(1);
	//EnPSW checked
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	//GetDlgItem(IDC_RADIO2)
	//20110713 Wujian add Start(v1.2)
	//SIM1 and SIM2 MCCMNC CHECKBOX CHECK AND EDIT ENABLE
    ((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(1);
    //SIM3 and SIM4 EDIT DISABLE(1,5,6,7)
    ((CEdit *)GetDlgItem(IDC_EDIT6))->EnableWindow(FALSE);
	((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(FALSE);
	//20110713 Wujian add End(v1.2)
	//20111031 Wujian add Start(v1.3)
	LoadDefaultConfig();
    //20111031 Wujian add End(v1.3)
	//20121218 Wujian modify Start
    ((CEdit *)GetDlgItem(IDC_EDIT1))->SetLimitText(UINT_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT5))->SetLimitText(UINT_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT6))->SetLimitText(UINT_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT7))->SetLimitText(UINT_MAX);
	//20121218 Wujian modify End
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CExtMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX || (nID & 0xFFF0) == SC_CONTEXTHELP)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
		
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExtMakerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExtMakerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/**********************************************
Click "Select..." button function
CFileDialog : input save as file name
**********************************************/
void CExtMakerDlg::OnExtFileBNClick() 
{
	//1.input save as file name
	//Ext and SML files save as path
	char path[MAX_PATH]={0};
    BROWSEINFO bi;
	memset(&bi,0, sizeof(BROWSEINFO));
    ITEMIDLIST   *pidl = NULL;
	//set floder brower parameter 
	bi.hwndOwner = this->GetSafeHwnd();
    bi.ulFlags   = BIF_RETURNONLYFSDIRS;
	bi.iImage    = 0; 
	bi.lParam    = 0; 
	bi.lpfn      = 0; 
	bi.lpszTitle = "Please Select File Folder:"; 
	bi.pidlRoot  = 0; 
	bi.pszDisplayName = 0; 
	pidl = SHBrowseForFolder(&bi); 
	if(SHGetPathFromIDList(pidl,path) == TRUE) 
	{
		//AfxMessageBox(path);
		OFilePath = path;
		//set UI "File Path"
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetWindowText(OFilePath);
	}
	/*CFileDialog fileDlg(FALSE,"EXT",NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_EXPLORER,"EXT Files (*.ext)|*.ext|All Files (*.*)|*.*||");
    CFileDialog fileDlg(FALSE);
	if( fileDlg.DoModal ()==IDOK )
	{
		OFilePath = fileDlg.GetPathName();
		OFileName = fileDlg.GetFileName();
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetWindowText(OFilePath);
	}
    */
}

/**********************************************
Is the input software version valid or invalid
TRUE : valid
FALSE: invalid
**********************************************/
BOOL CExtMakerDlg::IsSWvalid(CString swStr)
{
  int len = swStr.GetLength();
  char *letr = swStr.GetBuffer(len);
  do 
  {
	  if (!isalpha(*letr) && !isdigit(*letr)) 
	  {
		  //add "-" is valid 
		  //modify by huangheqing's advice
		  if ((*letr)!='_' && (*letr)!='.' && (*letr)!='+' && (*letr)!='-')  //"_" , "." and "+" is valid
		  {
			  return FALSE;
		  }
	  } 
	  letr++;
  } while(*letr != '\0');
  return TRUE;
}

/**********************************************
Click "Start" button function
1.Check input value(SW Version,MCC,MNC,SML File Name)
2.Create files(*.sml,*.ext)<-Class SMLFileWork
**********************************************/
void CExtMakerDlg::OnStartClick() 
{
	// TODO: Add your control notification handler code here
	/*
	CString mbtext;
	mbtext.Format("%d",m_PSWRd.GetCheck());
	MessageBox(mbtext,"Test",MB_OK);
	return;
	*/
	//EnExtContent("IMEID_DoExtend=function(){return 0};CHECK_DoExtend=function(){return 0};");
	//return;
	
	//Check input value
    CString ISW  = "";  //Software Version
	//20110713 Wujian modify Start
	CString IMCCNC1 = "";  //SIM1 MCCMNC
	CString IMCCNC2 = "";  //SIM2 MCCMNC
	CString IMCCNC3 = "";  //SIM3 MCCMNC
	CString IMCCNC4 = "";  //SIM4 MCCMNC
	int SIM1 = ((CButton *)(GetDlgItem(IDC_CHECK1)))->GetCheck();
	int SIM2 = ((CButton *)(GetDlgItem(IDC_CHECK2)))->GetCheck();
	int SIM3 = ((CButton *)(GetDlgItem(IDC_CHECK3)))->GetCheck();
	int SIM4 = ((CButton *)(GetDlgItem(IDC_CHECK4)))->GetCheck();
	CString SMLFileNm = "";  //SML file name
	//20110713 Wujian modify End
	CString IPro = "";	//project name
	GetDlgItem(IDC_EDIT3)->GetWindowText(ISW);
	//20120503 Wujian modify Start(v1.5)
    int bPhotoCheck = ((CButton *)(GetDlgItem(IDC_CHECK5)))->GetCheck();
	bool bPhotoCheckConfirm = false;
	//20120503 Wujian modify End(v1.5)

	//20110713 Wujian modify Start
	if(SIM1==1){
	  GetDlgItem(IDC_EDIT1)->GetWindowText(IMCCNC1);
	  IMCCNC1.TrimLeft();
	  IMCCNC1.TrimRight();
	}
	if(SIM2==1){
      GetDlgItem(IDC_EDIT5)->GetWindowText(IMCCNC2);
	  IMCCNC2.TrimLeft();
	  IMCCNC2.TrimRight();
	}
	if(SIM3==1){
	  GetDlgItem(IDC_EDIT6)->GetWindowText(IMCCNC3);
	  IMCCNC3.TrimLeft();
	  IMCCNC3.TrimRight();
	}
	if(SIM4==1){
	  GetDlgItem(IDC_EDIT7)->GetWindowText(IMCCNC4);
	  IMCCNC4.TrimLeft();
	  IMCCNC4.TrimRight();
	}
    //get SML file name
	GetDlgItem(IDC_EDIT8)->GetWindowText(SMLFileNm);
	SMLFileNm.TrimLeft();
	SMLFileNm.TrimRight();
	//20110713 Wujian modify End

	GetDlgItem(IDC_EDIT2)->GetWindowText(IPro);
	//GetDlgItem(IDC_EDIT2)->GetWindowText(IMNC);
    ISW.TrimLeft();
	ISW.TrimRight();
	IPro.TrimLeft();
	IPro.TrimRight();
	//check software version
    if(!IsSWvalid(ISW))
	{
		MessageBox("Software version is invalid!","input error",MB_OK);
		return;
	}
	//check project name 
	if(!IsProvalid(IPro))
	{
		MessageBox("Project is invalid!","input error",MB_OK);
		return;
	}
	//check MCCMNC
	if (SIM1==1)
	{
		if(!IsMCodevalid(IMCCNC1))
		{
			MessageBox("MCC MNC I is invalid!","input error",MB_OK);
			return;
		}
	}

	if (SIM2==1)
	{
		if(!IsMCodevalid(IMCCNC2))
		{
			MessageBox("MCC MNC II is invalid!","input error",MB_OK);
			return;
		}
	}

	if (SIM3==1)
	{
		if(!IsMCodevalid(IMCCNC3))
		{
			MessageBox("MCC MNC III is invalid!","input error",MB_OK);
			return;
		}
	}

	if (SIM4==1)
	{
		if(!IsMCodevalid(IMCCNC4))
		{
			MessageBox("MCC MNC IV is invalid!","input error",MB_OK);
			return;
		}
	}
	
	/*
	//check MNC
	if(!IsMCodevalid(IMNC))
	{
        MessageBox("MNC is invalid!","input error",MB_OK);
		return;
	}
	*/

	//20110713 Wujian add Start
    //check SML file name
	if(!IsSWvalid(SMLFileNm))
	{
		MessageBox("SML file name is invalid!","input error",MB_OK);
		return;
	}
	//20110713 Wujian add End
	//20120503 Wujian add Start(v1.5)
	//CString strFunPhotoCheck = ExtSourcePhotoCheck;
    if(1==bPhotoCheck)
	{
		if(1==AfxMessageBox("Are you sure photo checking?",MB_OKCANCEL))
		{
			//ExtDo.Replace("_HQ_SMLDO_PHOTOCHECK_",ExtSourcePhotoCheck);
			bPhotoCheckConfirm = true;
		}else{
			//ExtDo.Replace("_HQ_SMLDO_PHOTOCHECK_","");
			return;
		}
	}
	//20120503 Wujian add End(v1.5)
	//Create files
	SMLFileWork sfw;
	//CString MCode = IMCC+IMNC;
	/*
	UpdateData(TRUE);
    v_swv.TrimLeft();
	v_swv.TrimRight();
	//UpdateData(TRUE);
	int proint = v_swv.FindOneOf("_");
	if(proint==-1)
	{
		MessageBox("Can't find pro name!","input error",MB_OK);
		return;
	}
	*/
	//get current date
	CTime dt = CTime::GetCurrentTime();
	CString m_date = "";
	//int imon = dt.GetMonth();
	//int iday = dt.GetDay();
	m_date.Format("%d%02d%02d",dt.GetYear(),dt.GetMonth(),dt.GetDay());
	//get pro name
	//CString proNM = v_swv.Mid(0,proint);
	//sml file full path
	CString SMLPath1 = "";
	CString SMLPath2 = "";
	CString SMLPath3 = "";
	CString SMLPath4 = "";
	//ext file full path
	CString EXTPath = "";
	//sml file name
	CString SMLName = IPro+"_"+MCodeArr[0]+"_"+m_date+".sml";
	CString SMLName1 = "";
	CString SMLName2 = "";
	CString SMLName3 = "";
	CString SMLName4 = "";
	//ext file name
	CString EXTName = IPro+"_SIMLOCK_v1.0_"+m_date+".ext";
	//check file path
	if (OFilePath.IsEmpty()) 
	{
		MessageBox("Please select file path!","input error",MB_OK);
		return;
	}
	//check select folder path
	if (OFilePath.Right(1)=='\\') 
	{
      //PC root folder
	  //20110713 Wujian modify Start(v1.2)
	  //SMLPath = OFilePath+SMLName;
	  if (SMLFileNm.Right(4)==".sml")
	  {
		  int SMLFileNmLen = SMLFileNm.GetLength();
		  SMLName1 = SMLFileNm.Left(SMLFileNmLen-4)+"_1.sml";
		  SMLName2 = SMLFileNm.Left(SMLFileNmLen-4)+"_2.sml";
		  SMLName3 = SMLFileNm.Left(SMLFileNmLen-4)+"_3.sml";
		  SMLName4 = SMLFileNm.Left(SMLFileNmLen-4)+"_4.sml";
		  SMLPath1 = OFilePath + SMLName1;
		  SMLPath2 = OFilePath + SMLName2;
		  SMLPath3 = OFilePath + SMLName3;
		  SMLPath4 = OFilePath + SMLName4;
	  }else
	  {
		  SMLName1 = SMLFileNm+"_1.sml";
		  SMLName2 = SMLFileNm+"_2.sml";
		  SMLName3 = SMLFileNm+"_3.sml";
		  SMLName4 = SMLFileNm+"_4.sml";
		  SMLPath1 = OFilePath + SMLName1;
		  SMLPath2 = OFilePath + SMLName2;
		  SMLPath3 = OFilePath + SMLName3;
		  SMLPath4 = OFilePath + SMLName4;
	  }
	  //20110713 Wujian modify End(v1.2)
	  EXTPath = OFilePath+EXTName;
	}else
	{
	  //20110713 Wujian modify Start(v1.2)
      //SMLPath = OFilePath+"\\"+SMLName;
	  if (SMLFileNm.Right(4)==".sml")
	  {
		  int SMLFileNmLen = SMLFileNm.GetLength();
		  SMLName1 = SMLFileNm.Left(SMLFileNmLen-4)+"_1.sml";
		  SMLName2 = SMLFileNm.Left(SMLFileNmLen-4)+"_2.sml";
		  SMLName3 = SMLFileNm.Left(SMLFileNmLen-4)+"_3.sml";
		  SMLName4 = SMLFileNm.Left(SMLFileNmLen-4)+"_4.sml";
		  SMLPath1 = OFilePath +"\\"+ SMLName1;
		  SMLPath2 = OFilePath +"\\"+ SMLName2;
		  SMLPath3 = OFilePath +"\\"+ SMLName3;
		  SMLPath4 = OFilePath +"\\"+ SMLName4;
	  }else
	  {
		  SMLName1 = SMLFileNm+"_1.sml";
		  SMLName2 = SMLFileNm+"_2.sml";
		  SMLName3 = SMLFileNm+"_3.sml";
		  SMLName4 = SMLFileNm+"_4.sml";
		  SMLPath1 = OFilePath +"\\"+ SMLName1;
		  SMLPath2 = OFilePath +"\\"+ SMLName2;
		  SMLPath3 = OFilePath +"\\"+ SMLName3;
		  SMLPath4 = OFilePath +"\\"+ SMLName4;
	  }
	  //20110713 Wujian modify End(v1.2)
	  EXTPath = OFilePath+"\\"+EXTName;
	}
	//create SML file
	//20110713 Wujian modify Start(v1.2)
	//sfw.WriteStrToFile(IMCCNC.GetBuffer(209),SMLPath.GetBuffer(MAX_PATH));
	if(SIM1==1)
	{
	
		sfw.WriteStrToFile(IMCCNC1.GetBuffer(209),ISW.GetBuffer(ISW.GetLength()),SMLPath1.GetBuffer(MAX_PATH));
	}

	if(SIM2==1)
	{
		sfw.WriteStrToFile(IMCCNC2.GetBuffer(209),ISW.GetBuffer(ISW.GetLength()),SMLPath2.GetBuffer(MAX_PATH));
	}

	if(SIM3==1)
	{
		sfw.WriteStrToFile(IMCCNC3.GetBuffer(209),ISW.GetBuffer(ISW.GetLength()),SMLPath3.GetBuffer(MAX_PATH));
	}

	if(SIM4==1)
	{
		sfw.WriteStrToFile(IMCCNC4.GetBuffer(209),ISW.GetBuffer(ISW.GetLength()),SMLPath4.GetBuffer(MAX_PATH));
	}
	
	//20110713 Wujian modify End(v1.2)
	//create EXT file
	FILE *Extfile;
	CString ExtStr = "";  //ext file content
	CString ExtStrEncrypt = "";  //ext file content(Encrypt)
	char *FunChangePsw = ExtSourceFunPtl;   //change password to log
	char *FunGetPswIME = ExtSourceFunGpw;   //get password by IMEI1 
	char *FunGetVerWID = ExtSourceFunGver;  //get software version by Woid
	char *FunBK1 = ExtSourceFunBk1;   //backup1
	char *FunBK2 = ExtSourceFunBk2;   //backup2
	char *FunBK3 = ExtSourceFunBk3;   //backup3
	CString ExtDo = ExtSourceExtDo;         //Extend Do
    CString ExtCk = ExtSourceExtCheck;	    //Extend Check
	//replace software and sml file name
    ExtDo.Replace("_HQ_SFW_",ISW);
	//ExtDo.Replace("_HQ_SMLF_",SMLName);  //modify by Wujian(v1.2)
	ExtCk.Replace("_HQ_SFW_",ISW);
	//ExtCk.Replace("_HQ_SMLF_",SMLName);  //modify by Wujian(v1.2)
	//20120503 Wujian add Start(v1.5)
	//CString strFunPhotoCheck = ExtSourcePhotoCheck;
    if(bPhotoCheckConfirm)
	{
		ExtDo.Replace("_HQ_SMLDO_PHOTOCHECK_",ExtSourcePhotoCheck);	
	}else{
        ExtDo.Replace("_HQ_SMLDO_PHOTOCHECK_","");
	}
	//20120503 Wujian add End(v1.5)
	//20110714 Wujian add Start(v1.2)
    if(SIM1==1)
	{
	   CString dostr = "ExtendResult = objPlatform.obj.COM_DoSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName1;
	   dostr += "',_passwd,1);";
	   //20110826 Wujian modify Start(v1.2.1)
	   //dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
	   dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
	   //20110826 Wujian modify End(v1.2.1)
	   dostr += "else{return null;}";
	   CString ckstr = "ExtendResult = objPlatform.obj.COM_CheckSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName1;
	   ckstr += "',_passwd,1);";
	   //20110826 Wujian modify Start(v1.2.1)
       //ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
	   ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
	   //20110826 Wujian modify End(v1.2.1)
       ckstr += "else{return null;}";
       ExtDo.Replace("_HQ_SMLDO_ONE_",dostr);
	   ExtCk.Replace("_HQ_SMLCK_ONE_",ckstr);
	}
	else
	{
       ExtDo.Replace("_HQ_SMLDO_ONE_","");
	   ExtCk.Replace("_HQ_SMLCK_ONE_","");
	}

	if(SIM2==1)
	{
		CString dostr = "ExtendResult = objPlatform.obj.COM_DoSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName2;
		dostr += "',_passwd,2);";
		//20110826 Wujian modify Start(v1.2.1)
		//dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
		dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
		//20110826 Wujian modify End(v1.2.1)
		dostr += "else{return null;}";
		CString ckstr = "ExtendResult = objPlatform.obj.COM_CheckSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName2;
		ckstr += "',_passwd,2);";
		//20110826 Wujian modify Start(v1.2.1)
		//ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
		ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
		//20110826 Wujian modify End(v1.2.1)
		ckstr += "else{return null;}";
		ExtDo.Replace("_HQ_SMLDO_TWO_",dostr);
		ExtCk.Replace("_HQ_SMLCK_TWO_",ckstr);
	}
	else
	{
		ExtDo.Replace("_HQ_SMLDO_TWO_","");
		ExtCk.Replace("_HQ_SMLCK_TWO_","");
	}

	if(SIM3==1)
	{
		CString dostr = "ExtendResult = objPlatform.obj.COM_DoSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName3;
		dostr += "',_passwd,3);";
		//20110826 Wujian modify Start(v1.2.1)
		//dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
		dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
		//20110826 Wujian modify End(v1.2.1)
		dostr += "else{return null;}";
		CString ckstr = "ExtendResult = objPlatform.obj.COM_CheckSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName3;
		ckstr += "',_passwd,3);";
		//20110826 Wujian modify Start(v1.2.1)
		//ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
		ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
		//20110826 Wujian modify End(v1.2.1)
		ckstr += "else{return null;}";
		ExtDo.Replace("_HQ_SMLDO_THR_",dostr);
		ExtCk.Replace("_HQ_SMLCK_THR_",ckstr);
	}
	else
	{
		ExtDo.Replace("_HQ_SMLDO_THR_","");
		ExtCk.Replace("_HQ_SMLCK_THR_","");
	}

	if(SIM4==1)
	{
		CString dostr = "ExtendResult = objPlatform.obj.COM_DoSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName4;
		dostr += "',_passwd,4);";
		//20110826 Wujian modify Start(v1.2.1)
		//dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
		dostr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
		//20110826 Wujian modify End(v1.2.1)
		dostr += "else{return null;}";
		CString ckstr = "ExtendResult = objPlatform.obj.COM_CheckSimLockEx('D:\\\\huaqin\\\\simlock\\\\" + SMLName4;
		ckstr += "',_passwd,4);";
		//20110826 Wujian modify Start(v1.2.1)
		//ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;return 0;}";
		ckstr += "if(ExtendResult == 0){AppData.SMLDATA = _HQ_PSW_TYPE_;}";
		//20110826 Wujian modify End(v1.2.1)
		ckstr += "else{return null;}";
		ExtDo.Replace("_HQ_SMLDO_FOU_",dostr);
		ExtCk.Replace("_HQ_SMLCK_FOU_",ckstr);
	}
	else
	{
		ExtDo.Replace("_HQ_SMLDO_FOU_","");
		ExtCk.Replace("_HQ_SMLCK_FOU_","");
	}

	//20110714 Wujian add End(v1.2)
	//replace password upload style
	if(((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck())
	{
	  //upload encrypt password
      ExtDo.Replace("_HQ_PSW_TYPE_","_ext_pass2log(_passwd)");
	  ExtCk.Replace("_HQ_PSW_TYPE_","_ext_pass2log(_passwd)");
	}else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()) 
	{
	  //upload original password
	  ExtDo.Replace("_HQ_PSW_TYPE_","_passwd");
	  ExtCk.Replace("_HQ_PSW_TYPE_","_passwd");
	}else
	{
	  //upload ext file id
	  ExtDo.Replace("_HQ_PSW_TYPE_","AppData.SMLDATA");
	  ExtCk.Replace("_HQ_PSW_TYPE_","AppData.SMLDATA");
	}

	//open file
	if((Extfile = fopen(EXTPath,"wb"))==NULL)
	{
		AfxMessageBox("Open & Create ext file fail!Try again!");
		return;
	}
	//write file
	ExtStr.Format("%s%s%s%s%s%s",FunChangePsw,FunGetPswIME,FunGetVerWID,FunBK1,FunBK2,FunBK3);
	ExtStr+=ExtDo;
    ExtStr+=ExtCk;
	/*
	fwrite(FunChangePsw, strlen(FunChangePsw), 1, Extfile); 
	fwrite(FunGetPswIME, strlen(FunGetPswIME), 1, Extfile); 
	fwrite(FunGetVerWID, strlen(FunGetVerWID), 1, Extfile); 
	fwrite(ExtDo.GetBuffer(ExtDo.GetLength()), ExtDo.GetLength(), 1, Extfile); 
	fwrite(ExtCk.GetBuffer(ExtCk.GetLength()), ExtCk.GetLength(), 1, Extfile); 
	*/
	ExtStr = EnExtContent(ExtStr);
	fwrite(ExtStr.GetBuffer(ExtStr.GetLength()),ExtStr.GetLength(),1,Extfile);
	//close file
	fclose(Extfile);
	MessageBox("Create successfully!","Done",MB_OK);
}
/**********************************************
Is the input MCC/MNC valid or invalid
TRUE : valid
FALSE: invalid
**********************************************/
BOOL CExtMakerDlg::IsMCodevalid(CString mobilecode)
{
	const char *seps = ",";
	MCodeArr.clear();
	int len = mobilecode.GetLength();	
	char *str = mobilecode.GetBuffer(len);
	char *token;
	token = strtok(str,seps);
	while (token != NULL) 
	{
		//code's length must less than or equal 6
		MCodeArr.push_back(token);
		int t = strlen(token);  //debug test
		//20120918 Wujian add Start
        //钓鱼岛是中国的！
		if (strlen(token)==0 && *token == '0')
		{
			return TRUE;
		}
		//20120918 Wujian add End
		if(strlen(token)!=6 && strlen(token)!=5)
		{
			return FALSE;
		}
		//code should be numeric
		do 
		{
			if (!isdigit(*token)) 
			{
				return FALSE;
			} 
			token++;
		} while(*token != '\0');
		//
	    token = strtok(NULL, seps);	
	}
	//none from MCode
	if (MCodeArr.size()==0)
	{
		return FALSE;
	}
	return TRUE;
}
/**********************************************
Is the input project valid or invalid
TRUE : valid
FALSE: invalid
**********************************************/
BOOL CExtMakerDlg::IsProvalid(CString proname)
{
    int len = proname.GetLength();
	char *letr = proname.GetBuffer(len);
	do 
	{
		if (!isalpha(*letr) && !isdigit(*letr)) 
		{
		  if ((*letr)!='_' && (*letr)!='.' && (*letr)!='+')  //"_" , "." and "+" is valid
		  {
            return FALSE;
		  }
		} 
		letr++;
	} while(*letr != '\0');
	return TRUE;
}
/**********************************************
Get MD5 code
**********************************************/
void CExtMakerDlg::GetMd5(CString pwd, CString *MD5String)
{
	MD5_CTX context;
	MD5InitSelf (&context);
	MD5UpdateSelf (&context, (unsigned char *)(LPCTSTR)pwd , _tcslen(pwd));
	MD5FinalSelf (&context);
	MD5String->Format(TEXT("%x%x%x%x"),context.state[0],context.state[1],context.state[2],context.state[3]);
}
/**********************************************
Change EXT file content 
**********************************************/
CString CExtMakerDlg::EnExtContent(CString source)
{
	CString restr ="";
	CString strMD5 = "";
	CString chkmd5 = "";
	CString base64Str = source;
	int base64Len = base64Str.GetLength();
	/*
	FILE *file;
    file = fopen("D:\\test.txt","wb");
	fwrite(source.GetBuffer(source.GetLength()),source.GetLength(),1,file);
	fclose(file);
	*/
	const string so = source.GetBuffer(source.GetLength());
	//GetMd5(source,&strMD5);
	MD5 md5(so);
	//md5.update(so);
	//md5.update("abcdefghijklmnopqrstuvwxyz");
	strMD5 = md5.toString().c_str();
	strMD5.MakeUpper();
	int lenmd = strMD5.GetLength();
	char *charmd51 = strMD5.GetBuffer(lenmd);
	char *charmd52 = strMD5.GetBuffer(lenmd);
    charmd52+=lenmd/2;
	for (int i=0; i<(lenmd/2); i++) 
	{
	  //chkmd5.push( String.fromCharCode( 33+parseInt(strMD5[i]+strMD5[len+i],16)/2.8 ) ); --js
	  char hexstr[2];
	  hexstr[0] = *charmd51;
      hexstr[1] = *charmd52;
	  int bro = (int)strtol(hexstr,NULL,16);
      chkmd5 = chkmd5 + (33+bro/2.8);
	  charmd51++;
	  charmd52++;
	}
    JS_escape(base64Str);
	base64Len = base64Str.GetLength();
	base64Str = base64Encode(base64Str.GetBuffer(base64Len),base64Len);
    restr = chkmd5+base64Str;
	//MessageBox(chkmd5,"test",MB_OK);
    return restr;
}
/**********************************************
JavaScript function escape(only ASCII)
**********************************************/
CString CExtMakerDlg::JS_escape(CString &str)
{
	CString tmpstr = str;
	int len = tmpstr.GetLength();
	char *sour = tmpstr.GetBuffer(len);
	str = "";
	//20120503 Wujian modify Start(v1.5)
	/*
	int len = tmpstr.GetLength();
	//setlocale(LC_CTYPE,"");
	setlocale(LC_ALL,"chs");
	wchar_t aa[1<<10];
	mbstowcs(aa,tmpstr.GetBuffer(len),len);
    wstring wcs(aa);
	
	for(int i=0;i<wcs.size();i++)
	{
		if(wcs[i]>0xff)
		{
			char tmp[5];
			sprintf(tmp,"%x",wcs[i]);
			str += "%u";
			str += tmp;
		}
		else
		{
			if( (wcs[i]>='a' && wcs[i]<='z') || (wcs[i]>='A' && wcs[i]<='Z') || ( wcs[i]>='0' && wcs[i]<='9' ) ||wcs[i]=='-'||wcs[i]=='_'||wcs[i]=='.')
			{
				char tmp[2];
				sprintf(tmp,"%c",wcs[i]);
				str += tmp;
			}
			else
			{
				char tmp[3];
				sprintf(tmp,"%02x",wcs[i]);
				str += "%";
				str += tmp;
			}
		}
	}
	*/
	//20120503 Wujian modify End(v1.5)
	for(int i=0;i<len;i++)
	{
       if((*sour)>0xff)
	   {
		   char tmp[5];
		   sprintf(tmp,"%s%x","%u",*sour);
		   str+=tmp;
	   }
	   else
	   {
		   if(((*sour)>='a'&&(*sour)<='z')||((*sour)>='A'&&(*sour)<='Z')||((*sour)>='0'&&(*sour)<='9')||(*sour)=='-'||(*sour)=='_'||(*sour)=='.')
		   {
			   char tmp[2];
			   sprintf(tmp,"%c",*sour);
			   str+=tmp;
		   }
		   else
		   {
			   char tmp[3];
			   sprintf(tmp,"%%%02X",*sour);
			   str+=tmp;
		   }
	   }
       sour++;
	}
   return str;
}

DWORD CExtMakerDlg::bit_reverse(DWORD n)
{
	n = ((n >> 1) & 0x55555555) | ((n << 1) & 0xaaaaaaaa);
	n = ((n >> 2) & 0x33333333) | ((n << 2) & 0xcccccccc);
	n = ((n >> 4) & 0x0f0f0f0f) | ((n << 4) & 0xf0f0f0f0);
	n = ((n >> 8) & 0x00ff00ff) | ((n << 8) & 0xff00ff00);
	n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);
	return n;
}
/**********************************************
SIM CARD CHOOSE
**********************************************/
void CExtMakerDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	//input SIM1 mccmnc edit is valid or not
	if (((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
      ((CEdit *)GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
	}
	else
	{
      ((CEdit *)GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	}
}

void CExtMakerDlg::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	//input SIM2 mccmnc edit is valid or not
	if (((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		((CEdit *)GetDlgItem(IDC_EDIT5))->EnableWindow(TRUE);
	}
	else
	{
		((CEdit *)GetDlgItem(IDC_EDIT5))->EnableWindow(FALSE);
	}
}

void CExtMakerDlg::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	//input SIM3 mccmnc edit is valid or not
	if (((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		((CEdit *)GetDlgItem(IDC_EDIT6))->EnableWindow(TRUE);
	}
	else
	{
		((CEdit *)GetDlgItem(IDC_EDIT6))->EnableWindow(FALSE);
	}
}

void CExtMakerDlg::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	//input SIM4 mccmnc edit is valid or not
	if (((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck())
	{
		((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(TRUE);
	}
	else
	{
		((CEdit *)GetDlgItem(IDC_EDIT7))->EnableWindow(FALSE);
	}
}
//20111031 Wujian add Start(v1.3)
/************************************************************************

  get the application's position
  
************************************************************************/
BOOL CExtMakerDlg::GetAppPath(CString *sAppPath)
{
	CString sFullPath;
	TCHAR szFilePath[MAX_PATH+1];
	GetModuleFileName(NULL,szFilePath,MAX_PATH);
	sFullPath.Format("%s",szFilePath);
	int index = sFullPath.ReverseFind('\\');
	*sAppPath = sFullPath.Left(index+1);
	//sAppName = sFullPath.Right(sFullPath.GetLength()-index-1);
	return 0;
}
/************************************************************************

  Loading the default config when this run
  
************************************************************************/
BOOL CExtMakerDlg::LoadDefaultConfig()
{
	CString sSWV;       //software version
	CString sProName;   //project name
	INT iSIMCheck1;     //sim1 check box
	INT iSIMCheck2;     //sim2 check box
	INT iSIMCheck3;     //sim3 check box
	INT iSIMCheck4;     //sim4 check box
	CString sMCCMNC1;   //sim1 MCC/MNC
	CString sMCCMNC2;   //sim2 MCC/MNC
	CString sMCCMNC3;   //sim3 MCC/MNC
	CString sMCCMNC4;   //sim4 MCC/MNC
	CString sSMLFileNm; //sml file name 
	//CString sCreateFilePath; //create file path --"OFilePath"
	INT iPSWType;       //password type	
	//20120502 Wujian modify Start(v1.5)
    INT bPhotoCheck;    //Photo check flag
	//20120502 Wujian modify End(v1.5)
	GetAppPath(&m_sAppPath);
	m_sConfigPath = m_sAppPath + "config.ini";

	CString sSection,sTmp;
	if(TRUE==m_hConfig.SetPath(m_sConfigPath))
	{
		//basic
		sSWV = m_hConfig.GetKeyStrValue("Settings","Software","");
		sProName = m_hConfig.GetKeyStrValue("Settings","Project","");
		//SIM
		iSIMCheck1 =  m_hConfig.GetKeyIntValue("Settings","SIMCheck1",0);		
		iSIMCheck2 =  m_hConfig.GetKeyIntValue("Settings","SIMCheck2",0);
		iSIMCheck3 =  m_hConfig.GetKeyIntValue("Settings","SIMCheck3",0);
		iSIMCheck4 =  m_hConfig.GetKeyIntValue("Settings","SIMCheck4",0);
		sMCCMNC1 = m_hConfig.GetKeyStrValue("Settings","MCCMNC1","");
		sMCCMNC2 = m_hConfig.GetKeyStrValue("Settings","MCCMNC2","");
		sMCCMNC3 = m_hConfig.GetKeyStrValue("Settings","MCCMNC3","");
		sMCCMNC4 = m_hConfig.GetKeyStrValue("Settings","MCCMNC4","");
		//advanced
		sSMLFileNm = m_hConfig.GetKeyStrValue("Settings","SMLFile","");
		OFilePath = m_hConfig.GetKeyStrValue("Settings","CreateFile","");
		iPSWType = m_hConfig.GetKeyIntValue("Settings","PSWType",2);
		//20120502 Wujian modify Start(v1.5)
		bPhotoCheck = m_hConfig.GetKeyIntValue("Settings","PhotoCheck",0);
		//20120502 Wujian modify End(v1.5)

		//set software
        m_swv.SetWindowText(sSWV);
		m_pro.SetWindowText(sProName);
		//set sim checkbox
		if (iSIMCheck1==0)
		{
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
			OnCheck1();
		} else {
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
			OnCheck1();
		}
		if (iSIMCheck2==0)
		{
			((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);
			OnCheck2();
		} else {
			((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
			OnCheck2();
		}
		if (iSIMCheck3==0)
		{
			((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(FALSE);
			OnCheck3();
		} else {
			((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(TRUE);
			OnCheck3();
		}
		if (iSIMCheck4==0)
		{
			((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(FALSE);
			OnCheck4();
		} else {
			((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(TRUE);
			OnCheck4();
		}
		//set mcc/mnc
        if (sMCCMNC1!="")
        {
			((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(sMCCMNC1);
        }
		if (sMCCMNC2!="")
        {
			((CEdit*)GetDlgItem(IDC_EDIT5))->SetWindowText(sMCCMNC2);
        }
		if (sMCCMNC3!="")
        {
			((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(sMCCMNC3);
        }
		if (sMCCMNC4!="")
        {
			((CEdit*)GetDlgItem(IDC_EDIT7))->SetWindowText(sMCCMNC4);
        }
		//set SML file name
        if (sSMLFileNm!="")
        {
            ((CEdit*)GetDlgItem(IDC_EDIT8))->SetWindowText(sSMLFileNm);
        }
		//set create file path
        if (OFilePath!="")
        {
            ((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(OFilePath);
        }
		//set password type
		switch(iPSWType)
		{
			case 0:
				((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
				((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
				break;
			case 1:
				((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
				((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
				break;
			case 2:
				((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
				break;
			default:
				((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
				break;
		}
		//set PhotoCheck Checkbox
		//20120502 Wujian modify Start(v1.5)
		if (bPhotoCheck==0)
		{
			((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(FALSE);
		} else {
			((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(TRUE);
		}
	    //20120502 Wujian modify End(v1.5)
		//m_EditNvramDb.SetWindowText(sNvramDb);
	} else {
		sSWV = "";
		sProName = "";
        iSIMCheck1 = 0;
		iSIMCheck2 = 0;
		iSIMCheck3 = 0;
		iSIMCheck4 = 0;
		sMCCMNC1 = "";
		sMCCMNC2 = "";
		sMCCMNC3 = "";
		sMCCMNC4 = "";
		sSMLFileNm = "";
		OFilePath = "";
		iPSWType = 2;
		//20120502 Wujian modify Start(v1.5)
		bPhotoCheck = 0;
		//20120502 Wujian modify End(v1.5)
	}
	return 0;
}
/************************************************************************

  save config file
  
************************************************************************/
BOOL CExtMakerDlg::SaveConfig()
{
	CString sSWV;       //software version
	CString sProName;   //project name
	INT iSIMCheck1;     //sim1 check box
	INT iSIMCheck2;     //sim2 check box
	INT iSIMCheck3;     //sim3 check box
	INT iSIMCheck4;     //sim4 check box
	CString sMCCMNC1;   //sim1 MCC/MNC
	CString sMCCMNC2;   //sim2 MCC/MNC
	CString sMCCMNC3;   //sim3 MCC/MNC
	CString sMCCMNC4;   //sim4 MCC/MNC
	CString sSMLFileNm; //sml file name
	//CString sCreateFilePath; //create file path  --"OFilePath"
	INT iPSWType;       //password type	
	//20120502 Wujian modify Start(v1.5)
    INT bPhotoCheck;   //Photo check flag	
	//20120502 Wujian modify End(v1.5)
	m_swv.GetWindowText(sSWV);
	m_pro.GetWindowText(sProName);
	iSIMCheck1 = ((CButton *)(GetDlgItem(IDC_CHECK1)))->GetCheck();
	iSIMCheck2 = ((CButton *)(GetDlgItem(IDC_CHECK2)))->GetCheck();
	iSIMCheck3 = ((CButton *)(GetDlgItem(IDC_CHECK3)))->GetCheck();
	iSIMCheck4 = ((CButton *)(GetDlgItem(IDC_CHECK4)))->GetCheck();
	//
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(sMCCMNC1);
	((CEdit*)GetDlgItem(IDC_EDIT5))->GetWindowText(sMCCMNC2);
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(sMCCMNC3);
	((CEdit*)GetDlgItem(IDC_EDIT7))->GetWindowText(sMCCMNC4);
	((CEdit*)GetDlgItem(IDC_EDIT8))->GetWindowText(sSMLFileNm);
    //((CEdit*)GetDlgItem(IDC_EDIT4))->GetWindowText(OFilePath);
	//
	if(((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
	{
       iPSWType = 0;
	} else if(((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()) {
       iPSWType = 1;
	} else {
       iPSWType = 2;
	}
	//20120502 Wujian modify Start(v1.5)
    bPhotoCheck = ((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck();
	//20120502 Wujian modify End(v1.5)
	m_hConfig.SetKeyStrValue("Settings","Software",sSWV);
	m_hConfig.SetKeyStrValue("Settings","Project",sProName);
	m_hConfig.SetKeyNumValue("Settings","SIMCheck1",iSIMCheck1);
	m_hConfig.SetKeyNumValue("Settings","SIMCheck2",iSIMCheck2);
	m_hConfig.SetKeyNumValue("Settings","SIMCheck3",iSIMCheck3);
	m_hConfig.SetKeyNumValue("Settings","SIMCheck4",iSIMCheck4);
	m_hConfig.SetKeyStrValue("Settings","MCCMNC1",sMCCMNC1);
	m_hConfig.SetKeyStrValue("Settings","MCCMNC2",sMCCMNC2);
	m_hConfig.SetKeyStrValue("Settings","MCCMNC3",sMCCMNC3);
	m_hConfig.SetKeyStrValue("Settings","MCCMNC4",sMCCMNC4);
	m_hConfig.SetKeyStrValue("Settings","SMLFile",sSMLFileNm);
	m_hConfig.SetKeyStrValue("Settings","CreateFile",OFilePath);
	m_hConfig.SetKeyNumValue("Settings","PSWType",iPSWType);
	//20120502 Wujian modify Start(v1.5)
	m_hConfig.SetKeyNumValue("Settings","PhotoCheck",bPhotoCheck);
	//20120502 Wujian modify End(v1.5)
	
	return 0;
}
/************************************************************************

  save the config file when this close
  
************************************************************************/
void CExtMakerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	SaveConfig();
	CDialog::OnClose();
}
//20111031 Wujian add End(v1.3)

