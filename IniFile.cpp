// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define         MAX_SECTION                260        //Section��󳤶�

#define         MAX_KEY                         260        //KeyValues��󳤶�

#define         MAX_ALLSECTIONS     65535    //����Section����󳤶�

#define         MAX_ALLKEYS              65535    //����KeyValue����󳤶�
CIniFile::CIniFile()
{
	strErrorDetail = _T("");
	blExtendKey = true;
}

CIniFile::~CIniFile()
{

}
BOOL CIniFile::SetPath(CString strPath)
{
         m_strPath = strPath;
        
         //       ����ļ��Ƿ����
         DWORD  dwFlag = GetFileAttributes((LPCTSTR)m_strPath);
        
         //       �ļ�����·�������ڣ�����FALSE
         if( 0xFFFFFFFF == dwFlag )
                   return FALSE;
        
         //       ·����Ŀ¼������FALSE
         if (  FILE_ATTRIBUTE_DIRECTORY & dwFlag )
                   return FALSE;
 
         return TRUE;
}
CString CIniFile::GetPath( )
{
	return m_strPath;
}
BOOL CIniFile::SectionExist(CString strSection)
{
         TCHAR chSection[MAX_SECTION];
         DWORD dwRetValue;
 
         dwRetValue = GetPrivateProfileString(
                  (LPCTSTR)strSection,
                   NULL,
                   _T(""),
                  chSection,
                  sizeof(chSection)/sizeof(TCHAR),
                  (LPCTSTR)m_strPath);
 
         return (dwRetValue>0);
}
 
CString CIniFile::GetKeyStrValue(CString strSection,CString strKey)
{
		doCheckExist(strSection,strKey);
         TCHAR         chKey[MAX_KEY];
         DWORD         dwRetValue;
         CString strKeyValue=_T("");

         dwRetValue = GetPrivateProfileStringEx(
                  (LPCTSTR)strSection,
                  (LPCTSTR)strKey,
                   _T(""),
                   chKey,
                  sizeof(chKey)/sizeof(TCHAR),
                  (LPCTSTR)m_strPath);      
        
         strKeyValue = chKey;
        
         return strKeyValue;
 
}
CString CIniFile::GetKeyStrValue(CString strSection,CString strKey,CString DefalutVal)
{
	doCheckExist(strSection,strKey);
	TCHAR         chKey[MAX_KEY];
	DWORD         dwRetValue;
	CString strKeyValue=_T("");

	//dwRetValue = GetPrivateProfileStringEx(
	dwRetValue = GetPrivateProfileString(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		(LPCTSTR)DefalutVal,
		chKey,
		sizeof(chKey)/sizeof(TCHAR),
		(LPCTSTR)m_strPath);      

	strKeyValue = chKey;

	return strKeyValue;

}
void CIniFile::SetKeyStrValue(CString strSection,CString strKey,CString strKeyValue)
{
         WritePrivateProfileString(
                  (LPCTSTR)strSection,
                  (LPCTSTR)strKey,
                  (LPCTSTR)strKeyValue,
                  (LPCTSTR)m_strPath);
}
int CIniFile::GetKeyIntValue(CString strSection,CString strKey,int defaultInt)
{
	doCheckExist(strSection,strKey);
	int RetValue;
	RetValue = GetPrivateProfileInt(strSection,strKey,defaultInt,m_strPath);      
	return RetValue;	
}
double CIniFile::GetKeyDblValue(CString strSection,CString strKey,double defaultDbl)
{
	doCheckExist(strSection,strKey);
	double RetValue;
	CString strRetValue,tmpValue;
	strRetValue = GetKeyStrValue(strSection,strKey);
	if( strRetValue == _T("") )
	{
		RetValue = defaultDbl;
	}else
	{
		RetValue = atof( strRetValue );
		strRetValue.TrimLeft( _T("0.0") );	
		if ( RetValue ==0 && strRetValue!=_T("") )
		{
			// ����ַ�����ʽ���Ծͷ���Ĭ��ֵ
			RetValue = defaultDbl;
		}
	}
	return RetValue;	
}
void CIniFile::SetKeyNumValue(CString strSection,CString strKey,int intKeyValue)
{
	CString strKeyValue;
	strKeyValue.Format( _T("%d"),intKeyValue);
	SetKeyStrValue(strSection,strKey,strKeyValue);
}
void CIniFile::SetKeyNumValue(CString strSection,CString strKey,double dblKeyValue)
{
	CString strKeyValue;
	strKeyValue.Format(_T("%f"),dblKeyValue);
	SetKeyStrValue(strSection,strKey,strKeyValue);
}
void CIniFile::DeleteKey(CString strSection, CString strKey)
{
         WritePrivateProfileString(
                  (LPCTSTR)strSection,
                  (LPCTSTR)strKey,
                   NULL,          //       ����дNULL,��ɾ��Key
                  (LPCTSTR)m_strPath);
}
 
void CIniFile::DeleteSection(CString strSection)
{
         WritePrivateProfileString(
                  (LPCTSTR)strSection,
                   NULL,         
                   NULL,          //       ���ﶼдNULL,��ɾ��Section
                  (LPCTSTR)m_strPath);
}
 
int CIniFile::GetAllSections(CStringArray& strArrSection)
{
         int dwRetValue, i, j, iPos=0;
         TCHAR chAllSections[MAX_ALLSECTIONS];
         TCHAR chTempSection[MAX_SECTION];
 
         ZeroMemory(chAllSections, MAX_ALLSECTIONS);
         ZeroMemory(chTempSection, MAX_SECTION);
 
         dwRetValue = GetPrivateProfileSectionNames(
                  chAllSections,
                  MAX_ALLSECTIONS,
                  m_strPath);
 
         //       ��ΪSection�������еĴ����ʽΪ��Section1����0����Section2����0��0��
    //       ���������⵽��������0����break
         for(i=0; i<MAX_ALLSECTIONS; i++)
         {
                  if( chAllSections[i] == NULL )
                   {
                            if( chAllSections[i] == chAllSections[i+1] )
                           break;
                   }
         }
        
         i++; //         ��֤���ݶ���
         strArrSection.RemoveAll(); //         �������
        
         for(j=0; j<i; j++)
         {
                  chTempSection[iPos++] = chAllSections[j];
                  if( chAllSections[j] == NULL )
                   { 
                            strArrSection.Add(chTempSection);
                            ZeroMemory(chTempSection, MAX_SECTION);
                            iPos = 0;
                   }
         }
        
         return strArrSection.GetSize();
}
 
int CIniFile::GetAllKeysAndValues(CString  strSection,
                                                            CStringArray&         strArrKey,
                                                            CStringArray& strArrKeyValue)
{
         int dwRetValue, i, j, iPos=0;
         TCHAR chAllKeysAndValues[MAX_ALLKEYS];
         TCHAR chTempkeyAndValue[MAX_KEY];
         CString strTempKey;
 
         ZeroMemory(chAllKeysAndValues, MAX_ALLKEYS);
         ZeroMemory(chTempkeyAndValue, MAX_KEY);
 
         dwRetValue = GetPrivateProfileSection(
                  strSection,
                  chAllKeysAndValues,
                  MAX_ALLKEYS,
                  m_strPath);
 
         //       ��ΪSection�������еĴ����ʽΪ��Key1=KeyValue1����0����Key2=KeyValue2����0
         //       ���������⵽��������0����break
         for(i=0; i<MAX_ALLSECTIONS; i++)
         {
                  if( chAllKeysAndValues[i] == NULL )
                   {
                            if( chAllKeysAndValues[i] == chAllKeysAndValues[i+1] )
                                     break;
                   }
         }
        
         i++;
         strArrKey.RemoveAll();
         strArrKeyValue.RemoveAll();
        
         for(j=0; j<i; j++)
         {
                  chTempkeyAndValue[iPos++] = chAllKeysAndValues[j];
                  if( chAllKeysAndValues[j] == NULL )
                   { 
                            strTempKey = chTempkeyAndValue;
                            strArrKey.Add( strTempKey.Left(strTempKey.Find('=')) );
                            strArrKeyValue.Add( strTempKey.Mid(strTempKey.Find('=')+1) );
                            ZeroMemory(chTempkeyAndValue, MAX_KEY);
                            iPos = 0;
                   }
         }
        
         return strArrKey.GetSize();
}
 
void CIniFile::DeleteAllSections()
{
         int nSecNum;
         CStringArray strArrSection;
         nSecNum = GetAllSections(strArrSection);
         for(int i=0; i<nSecNum; i++)
         {
                  WritePrivateProfileString(
                            (LPCTSTR)strArrSection[i],
                            NULL,
                            NULL,
                            (LPCTSTR)m_strPath);      
         }
}
CString  CIniFile::GetLastErrorDetail( int flag)
{
	// Ĭ�ϴ�����մ����¼�Ĺ���
	CString res = strErrorDetail;
	if ( flag == 0 )
	{
		strErrorDetail =_T("");
	}
	return res;
}
void  CIniFile::SetCheckExist( BOOL val)
{
	blCheckExist = (val!=FALSE);
}
void CIniFile::doCheckExist(CString strSection,CString strKey)
{
	if ( blCheckExist )
	{
		// ���ڵ�
		if ( !CheckKeyExist(strSection,strKey) )
		{
			// ������
			strErrorDetail += strSection + _T("|") + strKey + _T("|Not Exist,");
		}
	}
}
void CIniFile::SetEnableExtendKey( bool val )
{
	blExtendKey = val;
}
bool CIniFile::CheckKeyExist(CString strSection,CString strKey)
{
	TCHAR         chKey[MAX_KEY];
	DWORD         dwRetValue;
	CString strKeyValue=_T("");
	CString strDefault=_T("{22B4ADA0-16CA-43b7-8E18-739DE4D16679}");

	dwRetValue = GetPrivateProfileStringEx(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		strDefault,
		chKey,
		sizeof(chKey)/sizeof(TCHAR),
		(LPCTSTR)m_strPath);      

	strKeyValue = chKey;
	if ( strKeyValue == strDefault )
	{
		// ������
		return false;
	}
	else
	{
		return true;
	}
}

DWORD CIniFile::GetPrivateProfileStringEx(LPCTSTR strSection,LPCTSTR strKey,LPCTSTR strDefault,TCHAR* chKey,int nSize ,LPCTSTR m_strPath)
{
	TCHAR  m_chKey[MAX_KEY];
	// ��չ GetPrivateProfileString �ĺ���ʹ֮���Զ�ȡ Line0001 Line0002 ...��ֵ
	CString m_strKeyValue=_T("");
	CString m_strDefault=_T("{22B4ADA0-16CA-43b7-8E18-739DE4D16679}");
	CString m_strKey;
	DWORD ret;
	ret = GetPrivateProfileString(strSection,strKey,m_strDefault,m_chKey,nSize,m_strPath); 
	m_strKeyValue = m_chKey;
	m_strKey = strKey;
	if ( m_strKeyValue == m_strDefault )
	{
		m_strKeyValue = _T("");
		// ������
		CString m_Key,m_KeyVal;
		// �Ƿ���Ҫ��չ��ȡ�ĺ���
		for( int i=1;i<15&& blExtendKey ;i++)
		{
			#ifndef _VC6
			//m_strKey.AppendFormat( _T(" Line%04d"),i);
			#else
			CString sTmp;
			sTmp.Format(_T(" Line%04d"),i);
			m_strKey = strKey;
			m_strKey += sTmp;
			#endif
			//
			GetPrivateProfileString(strSection,m_strKey,m_strDefault,m_chKey,nSize,m_strPath); 
			m_KeyVal = m_chKey;
			if ( m_strDefault == m_KeyVal)
			{
				//  ��������ڣ�ֱ�ӷ���
				break;
			}
			// ��ʼ�� �ַ�������
			#ifndef _VC6
			//m_strKeyValue.Append( m_KeyVal);
			#else
			m_strKeyValue += m_KeyVal;
			#endif
		}
		if (  m_strKeyValue == _T("") )
		{
			// ���ֵ��ȻΪ�գ���ֵĬ��
			m_strKeyValue = strDefault;
		}
	}
#ifndef _VC6
	//_tcscpy_s(chKey,nSize,m_strKeyValue);
#else
	strcpy(chKey,m_strKeyValue);
#endif
	return ret;
}
