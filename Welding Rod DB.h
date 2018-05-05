// Welding Rod DB.h : main header file for the WELDING ROD DB application
//

#if !defined(AFX_WELDINGRODDB_H__861329EB_DCA1_4639_8CD9_66DB31FA917C__INCLUDED_)
#define AFX_WELDINGRODDB_H__861329EB_DCA1_4639_8CD9_66DB31FA917C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWeldingRodDBApp:
// See Welding Rod DB.cpp for the implementation of this class
//

class CWeldingRodDBApp : public CWinApp
{
public:
	CWeldingRodDBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeldingRodDBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWeldingRodDBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELDINGRODDB_H__861329EB_DCA1_4639_8CD9_66DB31FA917C__INCLUDED_)
