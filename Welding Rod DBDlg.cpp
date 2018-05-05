// Welding Rod DBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Welding Rod DB.h"
#include "Welding Rod DBDlg.h"

#include   <fstream.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDMAPSIZE 1024
#define MAPSIZE 1024*8
#define MAXCONTIATION 3
#define MAXRESULT     5

struct RESULT_SET
{
	char *field1;  
	char *field2;
	char *field3;
	char *field4;
};

struct MAP_TABLE
{
	int index1;
	int index2;
	int index3;
	struct RESULT_SET result[MAXRESULT];
	int count;
};

struct ID_MAP
{
	int  id;
	char name[128];
}g_id_map[IDMAPSIZE];

struct MAP_TABLE g_map[MAPSIZE];

int g_con[MAXCONTIATION];

int getid(char *name)
{
	int i;

	if (name == NULL)
		return 0;

	for (i=0; i<IDMAPSIZE; i++)
	{
		if (strlen(g_id_map[i].name) == 0)
			break;

		if (strcmp(g_id_map[i].name, name) == 0)
			return g_id_map[i].id;
	}
	
	return 0;
}

int parse_conf(void)
{
	char line[1024];
	ifstream OpenFile("db.conf");
	int i = 0, j=0, mapindex = 0; 
	char *p1, *p2, *p3;
	char *t1, *t2, *t3;
	char *con[3];
	char *result[MAXRESULT][4];

	while(OpenFile.getline(line,sizeof(line)))
	{
		if (line[0] == ';' || strlen(line) == 0)
			continue;

		p1 = p2 = p3 = t1 = t2 = t3 = NULL;
		memset(con, 0, sizeof(con));
		memset(result, 0, sizeof(result));

		//Q235AF,1020=E1,W1,U1,P1;E2,W2,U2,P2;
		//^          ^^
		//p1        p2p3

		p1 = line;
		p2 = strchr(line, '=');
		if (p2 == NULL)
			continue;
		p3 = p2+1; *p2 = '\0';

		//  解析条件
		t1 = p1;
		i = 0; 
		for ( ;*t1!='\0'; )
		{
			if (*t1 == ',' && i < 3)
			{
				*t1 = '\0';
				con[i] = p1;
				p1 = t1 + 1;
				i++;
				t1++;
			}
			else
				t1++;
		}
		if (i < 3)
			con[i] = p1;

		//解析结果
		t1 = p3;
		i = 0; j=0;
		for ( ;*t1!='\0'; )
		{
			if (*t1 == ';')
			{
				*t1 = '\0';
				result[j][i] = p3;
				p3 = t1 +1;
				j++; t1++; i=0;
				continue;
			}

			if (*t1 == ',' && i < MAXRESULT)
			{
				*t1 = '\0';
				result[j][i] = p3;
				p3 = t1 + 1;
				i++; t1++;
			}
			else
				t1++;
		}

		//save into global map
		g_map[mapindex].index1 = getid(con[0]);
		g_map[mapindex].index2 = getid(con[1]);
		g_map[mapindex].index3 = getid(con[2]);

		for (i=0; i<MAXRESULT; i++)
		{
			if (result[i][0] != NULL)
			{
				g_map[mapindex].result[i].field1 = (char *)malloc(256);
				strcpy(g_map[mapindex].result[i].field1, result[i][0]);
			}
			if (result[i][1] != NULL)
			{
				g_map[mapindex].result[i].field2 = (char *)malloc(128);
				strcpy(g_map[mapindex].result[i].field2, result[i][1]);
			}
			if (result[i][2] != NULL)
			{
				g_map[mapindex].result[i].field3 = (char *)malloc(128);
				strcpy(g_map[mapindex].result[i].field3, result[i][2]);
			}
			if (result[i][3] != NULL)
			{
				g_map[mapindex].result[i].field4 = (char *)malloc(128);
				strcpy(g_map[mapindex].result[i].field4, result[i][3]);
			}

		}
		
		mapindex++;
	}


	OpenFile.close();

	return 0;
}

void init_id_map(void)
{
	int i;
	char *name[] = {
		"Q235AF", "Q235BC", "1020", "20G", "20R",
		"1Cr18Ni9Ti", "0Cr18Ni9", "0Cr18Ni10Ti", "00Cr19Ni10",
		"0Cr17Ni12Mo2", "0Cr18Ni12Mo2Ti", "00Cr17Ni14Mo2",
		"0Cr19Ni13Mo3", "00Cr19Ni13Mo3",
		"16Mn", "16MnR", "15MnVR", "15MnNbR", "20MnMo",
		"09MnD", "09MnNiDR", "16MnDR", "15MnNIDR", "20MnMoD",
		"07MnNiCrMoVDR", "08MnNiCrMoVD", "10Ni3MoVD",
		"13MnNiMoNbR", "18MnMoNbR", "20MnMoNb", "07MnCrMoVR",
		"1Cr5Mo", "0Cr13", "12CrMoG", "15CrMoGR", "14Cr1MoR", "12Cr1MoVG",
		"12Cr2MoG", "12Cr2Mo1R", NULL
	};

	memset(g_map, 0, sizeof(g_map));
	memset(g_id_map, 0, sizeof(g_id_map));

	for (i=0; i<IDMAPSIZE; i++) 
	{
		if (name[i] != NULL) 
		{
			strcpy(g_id_map[i].name, name[i]);
			g_id_map[i].id = i+1;
		}
		else
			break;
	}

	parse_conf();

	g_con[0] = g_con[1] = g_con[2] = 0;
}
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
// CWeldingRodDBDlg dialog

CWeldingRodDBDlg::CWeldingRodDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWeldingRodDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWeldingRodDBDlg)
	m_sRodBrand1 = _T("");
	m_sRodType1 = _T("");
	m_sStickBrand1 = _T("");
	m_sStickType1 = _T("");
	m_bQ235BC = FALSE;
	m_bQ235AF = FALSE;
	m_b1020 = FALSE;
	m_sRodBrand2 = _T("");
	m_sRodType2 = _T("");
	m_sStickBrand2 = _T("");
	m_sStickType2 = _T("");
	m_sRodBrand3 = _T("");
	m_sRodType3 = _T("");
	m_sStickBrand3 = _T("");
	m_sStickType3 = _T("");
	m_sRodBrand4 = _T("");
	m_sRodType4 = _T("");
	m_sStickBrand4 = _T("");
	m_sStickType4 = _T("");
	m_sRodBrand5 = _T("");
	m_sRodType5 = _T("");
	m_sStickBrand5 = _T("");
	m_sStickType5 = _T("");	
	m_b00Cr17Ni14Mo2 = FALSE;
	m_b00Cr17Ni14Mo3 = FALSE;
	m_b00Cr19Ni10 = FALSE;
	m_b00Cr19Ni13Mo3 = FALSE;
	m_b07MnCrMoVR = FALSE;
	m_b07MnNiCrMoVDR = FALSE;
	m_b09MnD = FALSE;
	m_b09MnNiDR = FALSE;
	m_b0Cr13 = FALSE;
	m_b0Cr17Ni12Mo2 = FALSE;
	m_b0Cr18Ni10Ti = FALSE;
	m_b0Cr18Ni12Mo2Ti = FALSE;
	m_b0Cr18Ni9 = FALSE;
	m_b0Cr19Ni13Mo3 = FALSE;
	m_b10Ni3MoVD = FALSE;
	m_b12Cr1MoVG = FALSE;
	m_b12Cr2Mo1R = FALSE;
	m_b12Cr2MoG = FALSE;
	m_b12CrMoG = FALSE;
	m_b13MnNiMoNbR = FALSE;
	m_b14Cr1MoR = FALSE;
	m_b15CrMoGR = FALSE;
	m_b15MnNbR = FALSE;
	m_b15MnNIDR = FALSE;
	m_b15MnVR = FALSE;
	m_b16Mn = FALSE;
	m_b16MnDR = FALSE;
	m_b16MnR = FALSE;
	m_b18MnMoNbR = FALSE;
	m_b1Cr18Ni9Ti = FALSE;
	m_b1Cr5Mo = FALSE;
	m_b20g = FALSE;
	m_b20MnMo = FALSE;
	m_b20MnMoD = FALSE;
	m_b20MnMoNb = FALSE;
	m_b20R = FALSE;
	m_sRodBrand4 = _T("");
	m_sRodType4 = _T("");
	m_sStickBrand4 = _T("");
	m_sStickType4 = _T("");
	m_sRodBrand5 = _T("");
	m_sRodType5 = _T("");
	m_sStickBrand5 = _T("");
	m_sStickType5 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	init_id_map();
}

void CWeldingRodDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWeldingRodDBDlg)
	DDX_Text(pDX, IDC_EDIT1_RODBRAND, m_sRodBrand1);
	DDX_Text(pDX, IDC_EDIT1_RODTYPE, m_sRodType1);
	DDX_Text(pDX, IDC_EDIT1_STICKBRAND, m_sStickBrand1);
	DDX_Text(pDX, IDC_EDIT1_STICKTYPE, m_sStickType1);
	DDX_Check(pDX, IDC_CHECK_Q235BC, m_bQ235BC);
	DDX_Check(pDX, IDC_CHECK_Q235AF, m_bQ235AF);
	DDX_Check(pDX, IDC_CHECK_1020, m_b1020);
	DDX_Text(pDX, IDC_EDIT2_RODBRAND, m_sRodBrand2);
	DDX_Text(pDX, IDC_EDIT2_RODTYPE, m_sRodType2);
	DDX_Text(pDX, IDC_EDIT2_STICKBRAND, m_sStickBrand2);
	DDX_Text(pDX, IDC_EDIT2_STICKTYPE, m_sStickType2);
	DDX_Text(pDX, IDC_EDIT3_RODBRAND, m_sRodBrand3);
	DDX_Text(pDX, IDC_EDIT3_RODTYPE, m_sRodType3);
	DDX_Text(pDX, IDC_EDIT3_STICKBRAND, m_sStickBrand3);
	DDX_Text(pDX, IDC_EDIT3_STICKTYPE, m_sStickType3);
	DDX_Check(pDX, IDC_CHECK_00Cr17Ni14Mo2, m_b00Cr17Ni14Mo2);
	DDX_Check(pDX, IDC_CHECK_00Cr17Ni14Mo3, m_b00Cr17Ni14Mo3);
	DDX_Check(pDX, IDC_CHECK_00Cr19Ni10, m_b00Cr19Ni10);
	DDX_Check(pDX, IDC_CHECK_00Cr19Ni13Mo3, m_b00Cr19Ni13Mo3);
	DDX_Check(pDX, IDC_CHECK_07MnCrMoVR, m_b07MnCrMoVR);
	DDX_Check(pDX, IDC_CHECK_07MnNiCrMoVDR, m_b07MnNiCrMoVDR);
	DDX_Check(pDX, IDC_CHECK_09MnD, m_b09MnD);
	DDX_Check(pDX, IDC_CHECK_09MnNiDR, m_b09MnNiDR);
	DDX_Check(pDX, IDC_CHECK_0Cr13, m_b0Cr13);
	DDX_Check(pDX, IDC_CHECK_0Cr17Ni12Mo2, m_b0Cr17Ni12Mo2);
	DDX_Check(pDX, IDC_CHECK_0Cr18Ni10Ti, m_b0Cr18Ni10Ti);
	DDX_Check(pDX, IDC_CHECK_0Cr18Ni12Mo2Ti, m_b0Cr18Ni12Mo2Ti);
	DDX_Check(pDX, IDC_CHECK_0Cr18Ni9, m_b0Cr18Ni9);
	DDX_Check(pDX, IDC_CHECK_0Cr19Ni13Mo3, m_b0Cr19Ni13Mo3);
	DDX_Check(pDX, IDC_CHECK_10Ni3MoVD, m_b10Ni3MoVD);
	DDX_Check(pDX, IDC_CHECK_12Cr1MoVG, m_b12Cr1MoVG);
	DDX_Check(pDX, IDC_CHECK_12Cr2Mo1R, m_b12Cr2Mo1R);
	DDX_Check(pDX, IDC_CHECK_12Cr2MoG, m_b12Cr2MoG);
	DDX_Check(pDX, IDC_CHECK_12CrMoG, m_b12CrMoG);
	DDX_Check(pDX, IDC_CHECK_13MnNiMoNbR, m_b13MnNiMoNbR);
	DDX_Check(pDX, IDC_CHECK_14Cr1MoR, m_b14Cr1MoR);
	DDX_Check(pDX, IDC_CHECK_15CrMoGR, m_b15CrMoGR);
	DDX_Check(pDX, IDC_CHECK_15MnNbR, m_b15MnNbR);
	DDX_Check(pDX, IDC_CHECK_15MnNIDR, m_b15MnNIDR);
	DDX_Check(pDX, IDC_CHECK_15MnVR, m_b15MnVR);
	DDX_Check(pDX, IDC_CHECK_16Mn, m_b16Mn);
	DDX_Check(pDX, IDC_CHECK_16MnDR, m_b16MnDR);
	DDX_Check(pDX, IDC_CHECK_16MnR, m_b16MnR);
	DDX_Check(pDX, IDC_CHECK_18MnMoNbR, m_b18MnMoNbR);
	DDX_Check(pDX, IDC_CHECK_1Cr18Ni9Ti, m_b1Cr18Ni9Ti);
	DDX_Check(pDX, IDC_CHECK_1Cr5Mo, m_b1Cr5Mo);
	DDX_Check(pDX, IDC_CHECK_20g, m_b20g);
	DDX_Check(pDX, IDC_CHECK_20MnMo, m_b20MnMo);
	DDX_Check(pDX, IDC_CHECK_20MnMoD, m_b20MnMoD);
	DDX_Check(pDX, IDC_CHECK_20MnMoNb, m_b20MnMoNb);
	DDX_Check(pDX, IDC_CHECK_20R, m_b20R);
	DDX_Text(pDX, IDC_EDIT4_RODBRAND, m_sRodBrand4);
	DDX_Text(pDX, IDC_EDIT4_RODTYPE, m_sRodType4);
	DDX_Text(pDX, IDC_EDIT4_STICKBRAND, m_sStickBrand4);
	DDX_Text(pDX, IDC_EDIT4_STICKTYPE, m_sStickType4);
	DDX_Text(pDX, IDC_EDIT5_RODBRAND, m_sRodBrand5);
	DDX_Text(pDX, IDC_EDIT5_RODTYPE, m_sRodType5);
	DDX_Text(pDX, IDC_EDIT5_STICKBRAND, m_sStickBrand5);
	DDX_Text(pDX, IDC_EDIT5_STICKTYPE, m_sStickType5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWeldingRodDBDlg, CDialog)
	//{{AFX_MSG_MAP(CWeldingRodDBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_Q235AF, OnCheckQ235af)
	ON_BN_CLICKED(IDC_CHECK_1020, OnCheck1020)
	ON_BN_CLICKED(IDC_CHECK_00Cr17Ni14Mo2, OnCHECK00Cr17Ni14Mo2)
	ON_BN_CLICKED(IDC_CHECK_00Cr17Ni14Mo3, OnCHECK00Cr17Ni14Mo3)
	ON_BN_CLICKED(IDC_CHECK_00Cr19Ni10, OnCHECK00Cr19Ni10)
	ON_BN_CLICKED(IDC_CHECK_00Cr19Ni13Mo3, OnCHECK00Cr19Ni13Mo3)
	ON_BN_CLICKED(IDC_CHECK_07MnCrMoVR, OnCHECK07MnCrMoVR)
	ON_BN_CLICKED(IDC_CHECK_07MnNiCrMoVDR, OnCHECK07MnNiCrMoVDR)
	ON_BN_CLICKED(IDC_CHECK_09MnD, OnCHECK09MnD)
	ON_BN_CLICKED(IDC_CHECK_09MnNiDR, OnCHECK09MnNiDR)
	ON_BN_CLICKED(IDC_CHECK_0Cr13, OnCHECK0Cr13)
	ON_BN_CLICKED(IDC_CHECK_0Cr17Ni12Mo2, OnCHECK0Cr17Ni12Mo2)
	ON_BN_CLICKED(IDC_CHECK_0Cr18Ni10Ti, OnCHECK0Cr18Ni10Ti)
	ON_BN_CLICKED(IDC_CHECK_0Cr18Ni12Mo2Ti, OnCHECK0Cr18Ni12Mo2Ti)
	ON_BN_CLICKED(IDC_CHECK_0Cr18Ni9, OnCHECK0Cr18Ni9)
	ON_BN_CLICKED(IDC_CHECK_0Cr19Ni13Mo3, OnCHECK0Cr19Ni13Mo3)
	ON_BN_CLICKED(IDC_CHECK_10Ni3MoVD, OnCHECK10Ni3MoVD)
	ON_BN_CLICKED(IDC_CHECK_12Cr1MoVG, OnCHECK12Cr1MoVG)
	ON_BN_CLICKED(IDC_CHECK_12Cr2Mo1R, OnCHECK12Cr2Mo1R)
	ON_BN_CLICKED(IDC_CHECK_12Cr2MoG, OnCHECK12Cr2MoG)
	ON_BN_CLICKED(IDC_CHECK_12CrMoG, OnCHECK12CrMoG)
	ON_BN_CLICKED(IDC_CHECK_13MnNiMoNbR, OnCHECK13MnNiMoNbR)
	ON_BN_CLICKED(IDC_CHECK_14Cr1MoR, OnCHECK14Cr1MoR)
	ON_BN_CLICKED(IDC_CHECK_15CrMoGR, OnCHECK15CrMoGR)
	ON_BN_CLICKED(IDC_CHECK_15MnNbR, OnCHECK15MnNbR)
	ON_BN_CLICKED(IDC_CHECK_15MnNIDR, OnCHECK15MnNIDR)
	ON_BN_CLICKED(IDC_CHECK_15MnVR, OnCHECK15MnVR)
	ON_BN_CLICKED(IDC_CHECK_16Mn, OnCHECK16Mn)
	ON_BN_CLICKED(IDC_CHECK_16MnDR, OnCHECK16MnDR)
	ON_BN_CLICKED(IDC_CHECK_16MnR, OnCHECK16MnR)
	ON_BN_CLICKED(IDC_CHECK_18MnMoNbR, OnCHECK18MnMoNbR)
	ON_BN_CLICKED(IDC_CHECK_1Cr18Ni9Ti, OnCHECK1Cr18Ni9Ti)
	ON_BN_CLICKED(IDC_CHECK_1Cr5Mo, OnCHECK1Cr5Mo)
	ON_BN_CLICKED(IDC_CHECK_20g, OnCHECK20g)
	ON_BN_CLICKED(IDC_CHECK_20MnMo, OnCHECK20MnMo)
	ON_BN_CLICKED(IDC_CHECK_20MnMoD, OnCHECK20MnMoD)
	ON_BN_CLICKED(IDC_CHECK_20MnMoNb, OnCHECK20MnMoNb)
	ON_BN_CLICKED(IDC_CHECK_20R, OnCheck20r)
	ON_BN_CLICKED(IDC_CHECK_Q235BC, OnCheckQ235bc)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, OnButtonReload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeldingRodDBDlg message handlers

BOOL CWeldingRodDBDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWeldingRodDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
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

void CWeldingRodDBDlg::OnPaint() 
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
HCURSOR CWeldingRodDBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL condition_match(int id, int *p)
{
	if (id == 0)
		return TRUE;

	if (p[0] == id || p[1] == id || p[2] == id)
		return TRUE;

	return FALSE;
}

int Query(void)
{
	int i;
	int con[3];

	for (i=0; i<MAPSIZE; i++)
	{
		con[0] = g_map[i].index1;
		con[1] = g_map[i].index2;
		con[2] = g_map[i].index3;

		if ( condition_match(g_map[i].index1, g_con) == TRUE && \
			 condition_match(g_map[i].index2, g_con) == TRUE && \
			 condition_match(g_map[i].index3, g_con) == TRUE && \
			 condition_match(g_con[0], con) == TRUE && \
			 condition_match(g_con[1], con) == TRUE && \
			 condition_match(g_con[2], con) == TRUE )
			return i;
	}

	return -1;
}

void CWeldingRodDBDlg::show_result(int index)
{

		m_sRodType1    = g_map[index].result[0].field1;
		m_sRodBrand1   = g_map[index].result[0].field2;
		m_sStickType1  = g_map[index].result[0].field3;
		m_sStickBrand1 = g_map[index].result[0].field4;

		m_sRodType2    = g_map[index].result[1].field1;
		m_sRodBrand2   = g_map[index].result[1].field2;
		m_sStickType2  = g_map[index].result[1].field3;
		m_sStickBrand2 = g_map[index].result[1].field4;

		m_sRodType3    = g_map[index].result[2].field1;
		m_sRodBrand3   = g_map[index].result[2].field2;
		m_sStickType3  = g_map[index].result[2].field3;
		m_sStickBrand3 = g_map[index].result[2].field4;

		m_sRodType4    = g_map[index].result[3].field1;
		m_sRodBrand4   = g_map[index].result[3].field2;
		m_sStickType4  = g_map[index].result[3].field3;
		m_sStickBrand4 = g_map[index].result[3].field4;

		m_sRodType5    = g_map[index].result[4].field1;
		m_sRodBrand5   = g_map[index].result[4].field2;
		m_sStickType5  = g_map[index].result[4].field3;
		m_sStickBrand5 = g_map[index].result[4].field4;

		UpdateData(FALSE);
}

void CWeldingRodDBDlg::show_clear()
{
		m_sRodType1    = _T("");
		m_sRodBrand1   = _T("");
		m_sStickType1  = _T("");
		m_sStickBrand1 = _T("");

		m_sRodType2    = _T("");
		m_sRodBrand2   = _T("");
		m_sStickType2  = _T("");
		m_sStickBrand2 = _T("");

		m_sRodType3    = _T("");
		m_sRodBrand3   = _T("");
		m_sStickType3  = _T("");
		m_sStickBrand3 = _T("");

		m_sRodType4    = _T("");
		m_sRodBrand4   = _T("");
		m_sStickType4  = _T("");
		m_sStickBrand4 = _T("");

		m_sRodType5    = _T("");
		m_sRodBrand5   = _T("");
		m_sStickType5  = _T("");
		m_sStickBrand5 = _T("");

		UpdateData(FALSE);
}

void CWeldingRodDBDlg::trigger(BOOL &m, char *name)
{
	int i, ret;

	UpdateData();

	if (m == TRUE)
	{
		for (i=0; i<MAXCONTIATION; i++)
		{
			if (g_con[i]==0)
			{
				g_con[i] = getid(name);
				break;
			}
		}
	}
	else
	{
		for (i=0; i<MAXCONTIATION; i++)
		{
			if (g_con[i]==getid(name))
			{
				g_con[i] = 0;
				break;
			}
		}
	}

	ret = Query();
	if (ret != -1)
		show_result(ret);
	else
		show_clear();
}

void CWeldingRodDBDlg::OnCheckQ235af() 
{
	// TODO: Add your control notification handler code here
	trigger(m_bQ235AF, "Q235AF");
}



void CWeldingRodDBDlg::OnCheck1020() 
{
	// TODO: Add your control notification handler code here
	int i, ret;

	UpdateData();

	if (m_b1020 == TRUE)
	{
		for (i=0; i<MAXCONTIATION; i++)
		{
			if (g_con[i]==0)
			{
				g_con[i] = getid("1020");
				break;
			}
		}
	}
	else
	{
		for (i=0; i<MAXCONTIATION; i++)
		{
			if (g_con[i]==getid("1020"))
			{
				g_con[i] = 0;
				break;
			}
		}
	}

	ret = Query();
	if (ret != -1)
		show_result(ret);
	else
		show_clear();
}



void CWeldingRodDBDlg::OnCHECK00Cr17Ni14Mo2() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b00Cr17Ni14Mo2, "00Cr17Ni14Mo2");
}

void CWeldingRodDBDlg::OnCHECK00Cr17Ni14Mo3() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b00Cr17Ni14Mo3, "00Cr17Ni14Mo3");
}

void CWeldingRodDBDlg::OnCHECK00Cr19Ni10() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b00Cr19Ni10, "00Cr19Ni10");
}

void CWeldingRodDBDlg::OnCHECK00Cr19Ni13Mo3() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b00Cr19Ni13Mo3, "00Cr19Ni13Mo3");
}

void CWeldingRodDBDlg::OnCHECK07MnCrMoVR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b07MnCrMoVR, "07MnCrMoVR");
}

void CWeldingRodDBDlg::OnCHECK07MnNiCrMoVDR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b07MnNiCrMoVDR, "07MnNiCrMoVDR");
}

void CWeldingRodDBDlg::OnCHECK09MnD() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b09MnD, "09MnD");
}

void CWeldingRodDBDlg::OnCHECK09MnNiDR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b09MnNiDR, "09MnNiDR");
}

void CWeldingRodDBDlg::OnCHECK0Cr13() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b0Cr13, "0Cr13");
}

void CWeldingRodDBDlg::OnCHECK0Cr17Ni12Mo2() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b0Cr17Ni12Mo2, "0Cr17Ni12Mo2");
}

void CWeldingRodDBDlg::OnCHECK0Cr18Ni10Ti() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b0Cr18Ni10Ti, "0Cr18Ni10Ti");
}

void CWeldingRodDBDlg::OnCHECK0Cr18Ni12Mo2Ti() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b0Cr18Ni12Mo2Ti, "0Cr18Ni12Mo2Ti");
}

void CWeldingRodDBDlg::OnCHECK0Cr18Ni9() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b0Cr18Ni9, "0Cr18Ni9");
}

void CWeldingRodDBDlg::OnCHECK0Cr19Ni13Mo3() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b0Cr19Ni13Mo3, "0Cr19Ni13Mo3");
}

void CWeldingRodDBDlg::OnCHECK10Ni3MoVD() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b10Ni3MoVD, "10Ni3MoVD");
}

void CWeldingRodDBDlg::OnCHECK12Cr1MoVG() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b12Cr1MoVG, "12Cr1MoVG");
}

void CWeldingRodDBDlg::OnCHECK12Cr2Mo1R() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b12Cr2Mo1R, "12Cr2Mo1R");
}

void CWeldingRodDBDlg::OnCHECK12Cr2MoG() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b12Cr2MoG, "12Cr2MoG");
}

void CWeldingRodDBDlg::OnCHECK12CrMoG() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b12CrMoG, "12CrMoG");
}

void CWeldingRodDBDlg::OnCHECK13MnNiMoNbR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b13MnNiMoNbR, "13MnNiMoNbR");
}

void CWeldingRodDBDlg::OnCHECK14Cr1MoR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b14Cr1MoR, "14Cr1MoR");
}

void CWeldingRodDBDlg::OnCHECK15CrMoGR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b15CrMoGR, "15CrMoGR");
}

void CWeldingRodDBDlg::OnCHECK15MnNbR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b15MnNbR, "15MnNbR");
}

void CWeldingRodDBDlg::OnCHECK15MnNIDR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b15MnNIDR, "15MnNIDR");
}

void CWeldingRodDBDlg::OnCHECK15MnVR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b15MnVR, "15MnVR");
}

void CWeldingRodDBDlg::OnCHECK16Mn() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b16Mn, "16Mn");
}

void CWeldingRodDBDlg::OnCHECK16MnDR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b16MnDR, "16MnDR");
}

void CWeldingRodDBDlg::OnCHECK16MnR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b16MnR, "16MnR");
}

void CWeldingRodDBDlg::OnCHECK18MnMoNbR() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b18MnMoNbR, "18MnMoNbR");
}

void CWeldingRodDBDlg::OnCHECK1Cr18Ni9Ti() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b1Cr18Ni9Ti, "1Cr18Ni9Ti");
}

void CWeldingRodDBDlg::OnCHECK1Cr5Mo() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b1Cr5Mo, "1Cr5Mo");
}

void CWeldingRodDBDlg::OnCHECK20g() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b20g, "20G");
}

void CWeldingRodDBDlg::OnCHECK20MnMo() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b20MnMo, "20MnMo");
}

void CWeldingRodDBDlg::OnCHECK20MnMoD() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b20MnMoD, "20MnMoD");
}

void CWeldingRodDBDlg::OnCHECK20MnMoNb() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b20MnMoNb, "20MnMoNb");
}

void CWeldingRodDBDlg::OnCheck20r() 
{
	// TODO: Add your control notification handler code here
	trigger(m_b20R, "20R");
}

void CWeldingRodDBDlg::OnCheckQ235bc() 
{
	// TODO: Add your control notification handler code here
	trigger(m_bQ235BC, "Q235BC");
}


void CWeldingRodDBDlg::OnButtonReload() 
{
	// TODO: Add your control notification handler code here
	init_id_map();

	m_b00Cr17Ni14Mo2 = FALSE;
	m_b00Cr17Ni14Mo3 = FALSE;
	m_b00Cr19Ni10 = FALSE;
	m_b00Cr19Ni13Mo3 = FALSE;
	m_b07MnCrMoVR = FALSE;
	m_b07MnNiCrMoVDR = FALSE;
	m_b09MnD = FALSE;
	m_b09MnNiDR = FALSE;
	m_b0Cr13 = FALSE;
	m_b0Cr17Ni12Mo2 = FALSE;
	m_b0Cr18Ni10Ti = FALSE;
	m_b0Cr18Ni12Mo2Ti = FALSE;
	m_b0Cr18Ni9 = FALSE;
	m_b0Cr19Ni13Mo3 = FALSE;
	m_b10Ni3MoVD = FALSE;
	m_b12Cr1MoVG = FALSE;
	m_b12Cr2Mo1R = FALSE;
	m_b12Cr2MoG = FALSE;
	m_b12CrMoG = FALSE;
	m_b13MnNiMoNbR = FALSE;
	m_b14Cr1MoR = FALSE;
	m_b15CrMoGR = FALSE;
	m_b15MnNbR = FALSE;
	m_b15MnNIDR = FALSE;
	m_b15MnVR = FALSE;
	m_b16Mn = FALSE;
	m_b16MnDR = FALSE;
	m_b16MnR = FALSE;
	m_b18MnMoNbR = FALSE;
	m_b1Cr18Ni9Ti = FALSE;
	m_b1Cr5Mo = FALSE;
	m_b20g = FALSE;
	m_b20MnMo = FALSE;
	m_b20MnMoD = FALSE;
	m_b20MnMoNb = FALSE;
	m_b20R = FALSE;
	m_b1020 = FALSE;


	show_clear();
}
