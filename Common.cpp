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
	return strResult.Trim(); // 去除最后的换行等
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
// 此函数类似ExtractStr，但是区别在于可以处理连续的分隔符，并且返回给vector类型
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
	// 查找有多少个 *seprator 并且 统计最大长度和个数;
	StrPos = buffer;
	preStrPos = buffer;
	while( 1 )
	{
		StrPos = _tcsstr( StrPos,seprator);
		if ( StrPos == NULL)
		{
			// 找不到分隔符，那么长度就是最后的字符串
			tmpSize = _tcslen(preStrPos);
		}else
		{
			tmpSize = StrPos-preStrPos;
		}
		ptr = new TCHAR [tmpSize+1];
		memset( ptr, 0,(tmpSize+1)*sizeof(TCHAR));
		memcpy( ptr,preStrPos,tmpSize*sizeof(TCHAR));
		str = ptr; // 进行赋值和自动转换
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
// 字符串分割，但是无法处理连续的分隔符，无法处理首尾是分割符的字符串
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

	// 查找有多少个 *seprator 并且 统计最大长度和个数;
	StrPos = buffer;
	preStrPos = buffer;
	iArrCount =1; // 默认个数为1,长度为 字符串长度
	iArrSize = iStrLen;
	isize=0; // 开始最小长度
	// 如果长度不是1个字符，这里表示用seprator其中的任意字符劈分
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
	// 初次循环，判断字符串中最大数组的长度
	while( (StrPos = _tcschr( StrPos,loacalseperator))!=NULL)
	{
		iArrCount++;
		tmpSize = StrPos-preStrPos;
		isize = max(isize, tmpSize);
		StrPos+=1;
		preStrPos = StrPos;
	}
	// 最后一个的长度
	tmpSize = _tcslen(preStrPos);
	isize = max(isize,tmpSize);

	isize ++ ; //添加一个结束符号
	iArrSize = min(iArrSize , isize);

	*count=0;
	pstr=(TCHAR **)malloc(iArrCount*sizeof(TCHAR *));
	ptr=pstr;

	for(i=0;i<iArrCount;i++)
		pstr[i]=(TCHAR*)malloc(iArrSize*sizeof(TCHAR));
	// 用 strtok无法区分 连续的分割符及开始和结尾的分隔符
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
/* 根据flag检查权限，flag含义如下
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
22	项目配置浏览
23	项目配置权限
 */
	// 得到系统变量 theUser
#ifndef CHECKPRIVILEGE
	return true;
#endif
	DWORD64 PrivilegeCode = theUser.PrivilegeCode;
	bool blResult=false;
	blResult = ((PrivilegeCode & 0x01<<flag)>>flag)==0 ? false:true;
	return blResult;

}

// 得到MD5码
void GetMd5(CString pwd,CString *MD5String)
{
	MD5_CTX context;
	MD5InitSelf (&context);
	MD5UpdateSelf (&context, (unsigned char *)(LPCTSTR)pwd , _tcslen(pwd));
	MD5FinalSelf (&context);
	// 32太长只取16位了
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

	// 查找最后的标记
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
	
	//首先将文件夹设置为可写
	DWORD fileattributes=GetFileAttributes(dir);
	SetFileAttributes(dir,fileattributes & ~(FILE_ATTRIBUTE_NORMAL));
	
	//然后遍历文件夹，将文件夹内的文件和子文件夹都设置为可写
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

//获取系统所有串口
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