// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__8577D2E3_5901_4D38_AD98_AEB837760A63__INCLUDED_)
#define AFX_INIFILE_H__8577D2E3_5901_4D38_AD98_AEB837760A63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
	CIniFile();

	virtual ~CIniFile();
	//    ����ini�ļ�·��
    //    �ɹ�����TRUE;���򷵻�FALSE
	BOOL  SetPath(CString strPath);
	CString  GetPath();
	//    ���section�Ƿ����
    //    ���ڷ���TRUE;���򷵻�FALSE
	BOOL  SectionExist(CString strSection);
	//    ��ָ����Section��Key��ȡKeyValue
	//    ����KeyValue
	CString GetKeyStrValue(CString    strSection,CString    strKey);    
	CString GetKeyStrValue(CString strSection,CString strKey,CString DefalutVal);
	//    ����Section��Key�Լ�KeyValue����Section����Key�������򴴽�
	int   GetKeyIntValue(CString strSection,CString strKey,int defaultInt);
	double GetKeyDblValue(CString strSection,CString strKey,double defaultDbl);

	void  SetKeyStrValue(CString    strSection,CString    strKey,CString    strKeyValue);
	void  SetKeyNumValue(CString strSection,CString strKey,int intKeyValue);
	void  SetKeyNumValue(CString strSection,CString strKey,double dlbKeyValue);
	//    ɾ��ָ��Section�µ�һ��Key
	void  DeleteKey(CString strSection,	CString strKey);
	//    ɾ��ָ����Section�Լ����µ�����Key
	void  DeleteSection(CString strSection);
	//    ������е�Section
	//    ����Section��Ŀ
	int   GetAllSections(CStringArray& strArrSection);
	//    ����ָ��Section�õ����µ�����Key��KeyValue
	//    ����Key����Ŀ
	int   GetAllKeysAndValues(CString strSection,
		CStringArray& strArrKey,
		CStringArray& strArrKeyValue);
	//       ɾ������Section
	void  DeleteAllSections();
	CString  GetLastErrorDetail(int flag=0); // ���ӻ�ȡ����ź���մ�����Ϣ
	void  SetCheckExist( BOOL val);
	bool CheckKeyExist(CString strSection,CString strKey);
	void SetEnableExtendKey( bool val );
private:
	//       ini�ļ�·��
         CString m_strPath;
		 bool blCheckExist;
		 CString strErrorDetail;
		 bool blExtendKey;
		 void doCheckExist(CString strSection,CString strKey);
		 DWORD GetPrivateProfileStringEx(LPCTSTR strSection,LPCTSTR strKey,LPCTSTR strDefault,TCHAR* chKey,int nSize ,LPCTSTR m_strPath);
};

#endif // !defined(AFX_INIFILE_H__8577D2E3_5901_4D38_AD98_AEB837760A63__INCLUDED_)
