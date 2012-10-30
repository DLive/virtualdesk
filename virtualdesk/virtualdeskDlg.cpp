// virtualdeskDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "virtualdesk.h"
#include "virtualdeskDlg.h"
#include "myadsk.h"
#include "myDesk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CvirtualdeskDlg �Ի���




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


// CvirtualdeskDlg ��Ϣ�������

BOOL CvirtualdeskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CvirtualdeskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CvirtualdeskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ������������
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
		AfxMessageBox(_T("����explorerʧ��"));
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
//	// TODO: �ڴ����ר�ô����/����û���
//	m_CreateDesk((LPARAM)_T("deskTop1"));
//	m_CreateDesk((LPARAM)_T("deskTop2"));
//	return CDialog::Create(lpszTemplateName, pParentWnd);
//}

void CvirtualdeskDlg::OnBnClickedSwdesk1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Cmyadsk swWall;
	swWall.SetWallPaper(_T("F:\\1.jpg"),0);
}

void CvirtualdeskDlg::OnBnClickedSwdesk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CmyDesk md;
	md.setIcon();
}

int CvirtualdeskDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CreateHotKey(); //ע���ȼ�
	// TODO:  �ڴ������ר�õĴ�������
	m_CreateDesk((LPARAM)_T("deskTop1"),1);
	m_CreateDesk((LPARAM)_T("deskTop2"),2);
	m_count=2;
	m_curId=0;

	//HWINSTA winsta = GetProcessWindowStation();  
    //EnumDesktops(winsta,(DESKTOPENUMPROCW)EnumDesktopCallBack,NULL);  
    //CloseWindowStation(winsta);  

	return 0;
}

// ע���ȼ�
void CvirtualdeskDlg::CreateHotKey(void)
{
	if(!RegisterHotKey(this->m_hWnd, 0x3344,MOD_ALT, 'D'))
	{
		AfxMessageBox(_T("ע���ȼ�ʧ��"));
	}
	if(!RegisterHotKey(this->m_hWnd, 0x3345,MOD_ALT, 'Q'))
	{
		AfxMessageBox(_T("ע���ȼ�ʧ��"));
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
	 
	 //�ر�explorer����
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
	// TODO: �ڴ˴������Ϣ����������
}

// �л�����
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
		printf("����������");
		return;
	}
	ret=SwitchDesktop(dsk);
	if(!ret)
	{
		printf("�л������ˡ����군��");
		return;
	}
	CloseDesktop(dsk);
}
