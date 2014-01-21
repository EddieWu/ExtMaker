// ExtMaker.h : main header file for the EXTMAKER application
//

#if !defined(AFX_EXTMAKER_H__D537FDE6_CAE6_44B5_B07A_B24E8D8684BA__INCLUDED_)
#define AFX_EXTMAKER_H__D537FDE6_CAE6_44B5_B07A_B24E8D8684BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtMakerApp:
// See ExtMaker.cpp for the implementation of this class
//

class CExtMakerApp : public CWinApp
{
public:
	CExtMakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtMakerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExtMakerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTMAKER_H__D537FDE6_CAE6_44B5_B07A_B24E8D8684BA__INCLUDED_)
