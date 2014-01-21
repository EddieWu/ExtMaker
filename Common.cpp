#include "stdafx.h"
#include "Common.h"
#include "stdio.h"
#include "afxwin.h"
#include "md5.h"
//#include "strsafe.h"

//#pragma comment(lib,"strsafe.lib")
#pragma comment(lib,"Version.lib")

#ifdef MFTSYSTEM
extern SYS_USER theUser;
#endif

CString GetShortIDN(char str[])
{
	CString strResult;
	strResult = "";
	long startCopy = 0,len;
	len = strlen(str);
	if ( len == 0 )
	{
		return strResult;
	}
	char desStr[MAXIDN];
	memset(desStr,0,MAXIDN);
	for (int i=0;i<MAXIDN;i++)
	{
		if ( str[i] == ',')
		{
			startCopy = i+1;
			break;
		}
	}
	if ( startCopy != 0 )
	{
		memcpy(desStr,str+startCopy,len-startCopy);
		strResult = desStr;
	}	
	return strResult.Trim(); // ȥ�����Ļ��е�
}
CString GetSelfVersion()
{
	HRESULT hr;
	TCHAR lpszFile[MAX_PATH];
	CString strReturn(_T(""));
	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

	HMODULE h = AfxGetInstanceHandle( ); 
	if( !h ) return strReturn ;
	memset(lpszFile, 0, MAX_PATH*sizeof(TCHAR));
	GetModuleFileName(h,lpszFile,MAX_PATH-1);


	DWORD dwSize = GetFileVersionInfoSize(lpszFile,NULL);
	BYTE *pBlock = new BYTE[dwSize];
	if (!GetFileVersionInfo(lpszFile,0,dwSize,pBlock))
	{
		delete[] pBlock;
		return strReturn;
	}
	// Read the list of languages and code pages.
	UINT cbTranslate;
	VerQueryValue(pBlock, 
		TEXT("\\VarFileInfo\\Translation"),
		(LPVOID*)&lpTranslate,
		&cbTranslate);

	// Read the file description for each language and code page.

	TCHAR SubBlock[50];
	for(int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
	{
		hr = StringCchPrintf(SubBlock, 50,
			TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
			lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage);
		if (FAILED(hr))
		{
			delete[] pBlock;
		}
		LPVOID lpBuffer;
		UINT dwBytes;
		// Retrieve file description for language and code page "i". 
		if (VerQueryValue(pBlock, 
			SubBlock, 
			&lpBuffer,
			&dwBytes))
		{
			CString tmp;
			//CString strR((char*)lpBuffer,dwBytes);
			strReturn.SetString((TCHAR*)lpBuffer,dwBytes);
			strReturn.Remove(0);
			delete[] pBlock;
			return strReturn;
		}
	}
	return strReturn;
}

void GetSystemDir(CString &strDir)
{
	static bool bAlreadyGet = false;
	static TCHAR strSystemDir[MAX_PATH];

	if(!bAlreadyGet)
	{
		memset(strSystemDir, 0, MAX_PATH*sizeof(TCHAR));
		GetModuleFileName(NULL,strSystemDir,MAX_PATH-1);

		strDir=strSystemDir;
		strDir=strDir.Left(strDir.ReverseFind('\\'));
		_tcscpy_s(strSystemDir,strDir.GetBuffer(strDir.GetLength()));
		bAlreadyGet = true;
	}
	else
	{
		strDir=strSystemDir;
	}
}
void GetSystemDllDir(CString &strDir)
{
	static bool bAlreadyGet = false;
	static TCHAR strSystemDir[MAX_PATH];

	if(!bAlreadyGet)
	{
		HMODULE h = AfxGetInstanceHandle( ); 
		if( !h ) return;
		memset(strSystemDir, 0, MAX_PATH*sizeof(TCHAR));
		GetModuleFileName(h,strSystemDir,MAX_PATH-1);

		strDir=strSystemDir;
		strDir=strDir.Left(strDir.ReverseFind('\\'));
		_tcscpy_s(strSystemDir,strDir.GetBuffer(strDir.GetLength()));
		bAlreadyGet = true;
	}
	else
	{
		strDir=strSystemDir;
	}
}
void FreeStrings(TCHAR **lpstr, int count)
{
	if(lpstr==NULL)
	{
		return;
	}

	for(int i=0;i<count;i++)
	{
		if(lpstr[i]!=NULL)
			free(lpstr[i]);		
	}

	free(lpstr);
}
// �˺�������ExtractStr�������������ڿ��Դ��������ķָ��������ҷ��ظ�vector����
void SplitStr(LPCTSTR source, LPCTSTR seprator, vector<CString> *DesArray)
{
//	int           i;
	TCHAR    *ptr;
	TCHAR    *buffer;
	TCHAR    *StrPos,*preStrPos;
	int           iStrLen,spSize,tmpSize;
	CString str;
	iStrLen = _tcslen(source)+1;
	spSize = _tcslen(seprator);
	buffer = new TCHAR [iStrLen];
	_tcscpy_s(buffer,iStrLen,source);
	// �����ж��ٸ� *seprator ���� ͳ����󳤶Ⱥ͸���;
	StrPos = buffer;
	preStrPos = buffer;
	while( 1 )
	{
		StrPos = _tcsstr( StrPos,seprator);
		if ( StrPos == NULL)
		{
			// �Ҳ����ָ�������ô���Ⱦ��������ַ���
			tmpSize = _tcslen(preStrPos);
		}else
		{
			tmpSize = StrPos-preStrPos;
		}
		ptr = new TCHAR [tmpSize+1];
		memset( ptr, 0,(tmpSize+1)*sizeof(TCHAR));
		memcpy( ptr,preStrPos,tmpSize*sizeof(TCHAR));
		str = ptr; // ���и�ֵ���Զ�ת��
		DesArray->push_back( str );
		delete ptr;

		if ( StrPos== NULL )
		{
			break;
		}
		StrPos+= spSize;
		preStrPos = StrPos;
	}
	delete []buffer;

}
// �ַ����ָ�����޷����������ķָ������޷�������β�Ƿָ�����ַ���
TCHAR** ExtractStr(LPCTSTR source, LPCTSTR seprator, int *count)
{
	int           i;
	TCHAR *token;
	TCHAR **pstr;
	TCHAR    **ptr;
	TCHAR    *buffer;
	TCHAR    *StrPos,*preStrPos;
	int           iStrLen,iArrCount,iArrSize,isize,spSize,tmpSize;
	iStrLen = _tcslen(source)+1;
	spSize = _tcslen(seprator);
	buffer = new TCHAR [iStrLen];
	TCHAR loacalseperator=seprator[0];

	_tcscpy_s(buffer,iStrLen,source);

	// �����ж��ٸ� *seprator ���� ͳ����󳤶Ⱥ͸���;
	StrPos = buffer;
	preStrPos = buffer;
	iArrCount =1; // Ĭ�ϸ���Ϊ1,����Ϊ �ַ�������
	iArrSize = iStrLen;
	isize=0; // ��ʼ��С����
	// ������Ȳ���1���ַ��������ʾ��seprator���е������ַ�����
	if(spSize!=1)
	{
		for(i=0;i<iStrLen-1;i++)
		{
			if(_tcschr(seprator+1,buffer[i]))
			{
				buffer[i]=seprator[0];
			}
		}
	}
	// ����ѭ�����ж��ַ������������ĳ���
	while( (StrPos = _tcschr( StrPos,loacalseperator))!=NULL)
	{
		iArrCount++;
		tmpSize = StrPos-preStrPos;
		isize = max(isize, tmpSize);
		StrPos+=1;
		preStrPos = StrPos;
	}
	// ���һ���ĳ���
	tmpSize = _tcslen(preStrPos);
	isize = max(isize,tmpSize);

	isize ++ ; //���һ����������
	iArrSize = min(iArrSize , isize);

	*count=0;
	pstr=(TCHAR **)malloc(iArrCount*sizeof(TCHAR *));
	ptr=pstr;

	for(i=0;i<iArrCount;i++)
		pstr[i]=(TCHAR*)malloc(iArrSize*sizeof(TCHAR));
	// �� strtok�޷����� �����ķָ������ʼ�ͽ�β�ķָ���
	TCHAR *temptoken=NULL;
	token = _tcstok_s(buffer, seprator,&temptoken);

	if(token!=NULL)
	{
		_tcscpy_s(*ptr,iArrSize,token);
		(*count)++;
		*ptr++;

		while(token!=NULL)
		{
			token = _tcstok_s(NULL, seprator,&temptoken);

			if(token!=NULL)
			{
				_tcscpy_s(*ptr,iArrSize,token);
				(*count)++;
				*ptr++; 
			}
		}
	}
	delete []buffer;
	if(*count==0)
	{
		FreeStrings(pstr,iArrCount);
		return NULL;
	}
	else
		return pstr;
}

bool CheckFileValidity(CString filename)
{
	if(GetFileAttributes(filename)==0xFFFFFFFF)
	{
//		AfxMessageBox(CString(LNG_NoFileFind)+filename);
		return false;
	}

	return true;
}

#ifdef MFTSYSTEM
bool CheckRole(int flag)
{
/* ����flag���Ȩ�ޣ�flag��������
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
22	��Ŀ�������
23	��Ŀ����Ȩ��
 */
	// �õ�ϵͳ���� theUser
#ifndef CHECKPRIVILEGE
	return true;
#endif
	DWORD64 PrivilegeCode = theUser.PrivilegeCode;
	bool blResult=false;
	blResult = ((PrivilegeCode & 0x01<<flag)>>flag)==0 ? false:true;
	return blResult;

}

// �õ�MD5��
void GetMd5(CString pwd,CString *MD5String)
{
	MD5_CTX context;
	MD5InitSelf (&context);
	MD5UpdateSelf (&context, (unsigned char *)(LPCTSTR)pwd , _tcslen(pwd));
	MD5FinalSelf (&context);
	// 32̫��ֻȡ16λ��
	MD5String->Format(TEXT("%x%x"),
		context.state[1],
		context.state[2]);
}
#endif//MFTSYSTEM

CString GetLastProject(CString strSource,CString tagName)
{
	const CString lTag=TEXT("[")+tagName+TEXT("]"),rTag=TEXT("[/")+tagName+TEXT("]");
	int tagLen= lTag.GetLength();
	int tmplPos=-tagLen,lPos=0,StrLen=0;
	CString lowSource = strSource,strResult = TEXT("");
	lowSource.MakeLower();

	// �������ı��
	while(tmplPos != -1)
	{
		tmplPos+=tagLen;
		lowSource = lowSource.Mid(tmplPos);
		lPos =lPos + tmplPos;
		tmplPos = lowSource.Find(lTag);
	}
	StrLen = lowSource.Find(rTag);
	if(StrLen<1)return TEXT("");
	strResult = strSource.Mid(lPos,StrLen);
	return strResult;
}

void SetDirWritable(CString dir)
{
	CFileFind findfile;
	
	//���Ƚ��ļ�������Ϊ��д
	DWORD fileattributes=GetFileAttributes(dir);
	SetFileAttributes(dir,fileattributes & ~(FILE_ATTRIBUTE_NORMAL));
	
	//Ȼ������ļ��У����ļ����ڵ��ļ������ļ��ж�����Ϊ��д
	if(!findfile.FindFile(CString(dir)+TEXT("\\*.*")))
	{
		return;
	}
	
	while(1)
	{
		BOOL flag=findfile.FindNextFile();
		
		if(findfile.IsDots())
		{
			if(!flag)
			{
				break;
			}
			continue;
		}
		
		if(findfile.IsDirectory())
		{
			SetDirWritable(findfile.GetFilePath());
			
			if(!flag)
			{
				break;
			}
			continue;
		}
		
		CString filename=findfile.GetFilePath();
		fileattributes=GetFileAttributes(filename);
		SetFileAttributes(filename,fileattributes & ~(FILE_ATTRIBUTE_READONLY));
		
		if(!flag)
		{
			break;
		}
	}
	
	findfile.Close();
}

//��ȡϵͳ���д���
BOOL GetSystemSerialComport(CArray<CString,CString> &comarray)
{
	HKEY hKey=NULL;

	comarray.RemoveAll();

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS)
	{
		return FALSE;
	}

	CString valuename,databuffer;
	DWORD valuenamebufferlength=200,valuetype,databuddersize=200;

	int i=0;
	while(RegEnumValue(hKey,i++,valuename.GetBuffer(200),&valuenamebufferlength,NULL,&valuetype,(BYTE*)databuffer.GetBuffer(200),&databuddersize) != ERROR_NO_MORE_ITEMS)
	{
		comarray.Add(CString(databuffer));

		databuddersize=200;
		valuenamebufferlength=200;
	}

	RegCloseKey(hKey);

	return TRUE;
}