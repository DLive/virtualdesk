// virtualdeskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "virtualdesk.h"
#include "virtualdeskDlg.h"
#include "myadsk.h"
#include "myDesk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CvirtualdeskDlg 对话框




CvirtualdeskDlg::CvirtualdeskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvirtualdeskDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvirtualdeskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CvirtualdeskDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SWDESK1, &CvirtualdeskDlg::OnBnClickedSwdesk1)
	ON_BN_CLICKED(IDC_SWDESK2, &CvirtualdeskDlg::OnBnClickedSwdesk2)
	ON_WM_CREATE()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CvirtualdeskDlg 消息处理程序

BOOL CvirtualdeskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CvirtualdeskDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CvirtualdeskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CvirtualdeskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 创建虚拟桌面
void CvirtualdeskDlg::m_CreateDesk(LPARAM lParam,int num)
{
	HWINSTA winsta = GetProcessWindowStation();  
    SetProcessWindowStation(winsta);  
    _TCHAR * desktopname = (_TCHAR *)lParam;  
    HDESK newdesktop = CreateDesktopW(desktopname,NULL,NULL,DF_ALLOWOTHERACCOUNTHOOK,GENERIC_ALL,NULL);
    SetThreadDesktop(newdesktop);  
    STARTUPINFO si;  
    PROCESS_INFORMATION pi;  
    memset(&si,0,sizeof(si));  
    memset(&pi,0,sizeof(pi));  
    si.cb = sizeof(si);  
    si.lpDesktop = desktopname;  
	//si.wShowWindow=SW_SHOW;
	TCHAR _ExplorerPath[250];
	lstrcpy(_ExplorerPath,_T("C:\\WINDOWS\\EXPLORER.exe"));
    if(!CreateProcessW(NULL,_ExplorerPath,NULL,NULL,FALSE,0, NULL, NULL, &si, &m_processInfo[num-1]))
	{
		AfxMessageBox(_T("创建explorer失败"));
	}
    //Sleep(4000);  
    CloseDesktop(newdesktop);  
    CloseWindowStation(winsta);  
}

void WINAPI EnumDesktopCallBack(LPTSTR lpszDesktop,LPARAM lParam)  
{  
    wprintf(L"%s\n",lpszDesktop);  
}  
//BOOL CvirtualdeskDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	m_CreateDesk((LPARAM)_T("deskTop1"));
//	m_CreateDesk((LPARAM)_T("deskTop2"));
//	return CDialog::Create(lpszTemplateName, pParentWnd);
//}

void CvirtualdeskDlg::OnBnClickedSwdesk1()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmyadsk swWall;
	swWall.SetWallPaper(_T("F:\\1.jpg"),0);
}

void CvirtualdeskDlg::OnBnClickedSwdesk2()
{
	// TODO: 在此添加控件通知处理程序代码
	CmyDesk md;
	md.setIcon();
}

int CvirtualdeskDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CreateHotKey(); //注册热键
	// TODO:  在此添加您专用的创建代码
	m_CreateDesk((LPARAM)_T("deskTop1"),1);
	m_CreateDesk((LPARAM)_T("deskTop2"),2);
	m_count=2;
	m_curId=0;

	//HWINSTA winsta = GetProcessWindowStation();  
    //EnumDesktops(winsta,(DESKTOPENUMPROCW)EnumDesktopCallBack,NULL);  
    //CloseWindowStation(winsta);  

	return 0;
}

// 注册热键
void CvirtualdeskDlg::CreateHotKey(void)
{
	if(!RegisterHotKey(this->m_hWnd, 0x3344,MOD_ALT, 'D'))
	{
		AfxMessageBox(_T("注册热键失败"));
	}
	if(!RegisterHotKey(this->m_hWnd, 0x3345,MOD_ALT, 'Q'))
	{
		AfxMessageBox(_T("注册热键失败"));
	}
}
LRESULT CvirtualdeskDlg::OnHotKey(WPARAM wParam,LPARAM lParam) 
{
 if(wParam == 0x3344)
 {
	 SwitchDesk();
 }
 if(wParam==0x3345)
 {
	 HDESK dsk=OpenDesktop(_T("Default"),0,FALSE,GENERIC_ALL);
	 SwitchDesktop(dsk);
	 
	 //关闭explorer进程
	for(int i=0;i<2;i++)
	{
		TerminateProcess(m_processInfo[i].hProcess,1);
	}
	 SendMessage(WM_CLOSE,0,0);
 }
 return true;
}
void CvirtualdeskDlg::OnDestroy()
{
	CDialog::OnDestroy();

    UnregisterHotKey(this->m_hWnd,3344);
	UnregisterHotKey(this->m_hWnd,3345);
	// TODO: 在此处添加消息处理程序代码
}

// 切换桌面
void CvirtualdeskDlg::SwitchDesk(void)
{
	HDESK dsk;
	BOOL ret;
	m_curId++;
	if(m_curId>m_count)
	{
		m_curId=0;
		dsk=OpenDesktop(_T("Default"),0,FALSE,GENERIC_ALL);
		ret=SwitchDesktop(dsk);
		return;
	}
	else
	{
	m_deskName.Format(_T("deskTop%d"),m_curId);
	dsk=OpenDesktop(m_deskName,0,FALSE,GENERIC_ALL);
	}
	if(!dsk)
	{
		printf("打开桌面出错喽");
		return;
	}
	ret=SwitchDesktop(dsk);
	if(!ret)
	{
		printf("切换出错了。你完蛋了");
		return;
	}
	CloseDesktop(dsk);
}
