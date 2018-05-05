// Welding Rod DBDlg.h : header file
//

#if !defined(AFX_WELDINGRODDBDLG_H__FDA45A41_CB78_468D_881C_88B2E7CAA8E5__INCLUDED_)
#define AFX_WELDINGRODDBDLG_H__FDA45A41_CB78_468D_881C_88B2E7CAA8E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWeldingRodDBDlg dialog

class CWeldingRodDBDlg : public CDialog
{
// Construction
public:
	void trigger(BOOL &m, char *name);
	void show_clear();
	void show_result(int index);
	CWeldingRodDBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWeldingRodDBDlg)
	enum { IDD = IDD_WELDINGRODDB_DIALOG };
	CString	m_sRodBrand1;
	CString	m_sRodType1;
	CString	m_sStickBrand1;
	CString	m_sStickType1;
	BOOL	m_bQ235BC;
	BOOL	m_bQ235AF;
	BOOL	m_b1020;
	CString	m_sRodBrand2;
	CString	m_sRodType2;
	CString	m_sStickBrand2;
	CString	m_sStickType2;
	CString	m_sRodBrand3;
	CString	m_sRodType3;
	CString	m_sStickBrand3;
	CString	m_sStickType3;
	BOOL	m_b00Cr17Ni14Mo2;
	BOOL	m_b00Cr17Ni14Mo3;
	BOOL	m_b00Cr19Ni10;
	BOOL	m_b00Cr19Ni13Mo3;
	BOOL	m_b07MnCrMoVR;
	BOOL	m_b07MnNiCrMoVDR;
	BOOL	m_b09MnD;
	BOOL	m_b09MnNiDR;
	BOOL	m_b0Cr13;
	BOOL	m_b0Cr17Ni12Mo2;
	BOOL	m_b0Cr18Ni10Ti;
	BOOL	m_b0Cr18Ni12Mo2Ti;
	BOOL	m_b0Cr18Ni9;
	BOOL	m_b0Cr19Ni13Mo3;
	BOOL	m_b10Ni3MoVD;
	BOOL	m_b12Cr1MoVG;
	BOOL	m_b12Cr2Mo1R;
	BOOL	m_b12Cr2MoG;
	BOOL	m_b12CrMoG;
	BOOL	m_b13MnNiMoNbR;
	BOOL	m_b14Cr1MoR;
	BOOL	m_b15CrMoGR;
	BOOL	m_b15MnNbR;
	BOOL	m_b15MnNIDR;
	BOOL	m_b15MnVR;
	BOOL	m_b16Mn;
	BOOL	m_b16MnDR;
	BOOL	m_b16MnR;
	BOOL	m_b18MnMoNbR;
	BOOL	m_b1Cr18Ni9Ti;
	BOOL	m_b1Cr5Mo;
	BOOL	m_b20g;
	BOOL	m_b20MnMo;
	BOOL	m_b20MnMoD;
	BOOL	m_b20MnMoNb;
	BOOL	m_b20R;
	CString	m_sRodBrand4;
	CString	m_sRodType4;
	CString	m_sStickBrand4;
	CString	m_sStickType4;
	CString	m_sRodBrand5;
	CString	m_sRodType5;
	CString	m_sStickBrand5;
	CString	m_sStickType5;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeldingRodDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWeldingRodDBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckQ235af();
	afx_msg void OnCheck1020();
	afx_msg void OnCHECK00Cr17Ni14Mo2();
	afx_msg void OnCHECK00Cr17Ni14Mo3();
	afx_msg void OnCHECK00Cr19Ni10();
	afx_msg void OnCHECK00Cr19Ni13Mo3();
	afx_msg void OnCHECK07MnCrMoVR();
	afx_msg void OnCHECK07MnNiCrMoVDR();
	afx_msg void OnCHECK09MnD();
	afx_msg void OnCHECK09MnNiDR();
	afx_msg void OnCHECK0Cr13();
	afx_msg void OnCHECK0Cr17Ni12Mo2();
	afx_msg void OnCHECK0Cr18Ni10Ti();
	afx_msg void OnCHECK0Cr18Ni12Mo2Ti();
	afx_msg void OnCHECK0Cr18Ni9();
	afx_msg void OnCHECK0Cr19Ni13Mo3();
	afx_msg void OnCHECK10Ni3MoVD();
	afx_msg void OnCHECK12Cr1MoVG();
	afx_msg void OnCHECK12Cr2Mo1R();
	afx_msg void OnCHECK12Cr2MoG();
	afx_msg void OnCHECK12CrMoG();
	afx_msg void OnCHECK13MnNiMoNbR();
	afx_msg void OnCHECK14Cr1MoR();
	afx_msg void OnCHECK15CrMoGR();
	afx_msg void OnCHECK15MnNbR();
	afx_msg void OnCHECK15MnNIDR();
	afx_msg void OnCHECK15MnVR();
	afx_msg void OnCHECK16Mn();
	afx_msg void OnCHECK16MnDR();
	afx_msg void OnCHECK16MnR();
	afx_msg void OnCHECK18MnMoNbR();
	afx_msg void OnCHECK1Cr18Ni9Ti();
	afx_msg void OnCHECK1Cr5Mo();
	afx_msg void OnCheck20g();
	afx_msg void OnCHECK20g();
	afx_msg void OnCHECK20MnMo();
	afx_msg void OnCHECK20MnMoD();
	afx_msg void OnCHECK20MnMoNb();
	afx_msg void OnCheck20r();
	afx_msg void OnCheckQ235bc();
	afx_msg void OnButtonReload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELDINGRODDBDLG_H__FDA45A41_CB78_468D_881C_88B2E7CAA8E5__INCLUDED_)
