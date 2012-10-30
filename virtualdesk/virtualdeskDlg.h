// virtualdeskDlg.h : 头文件
//

#pragma once


// CvirtualdeskDlg 对话框
class CvirtualdeskDlg : public CDialog
{
// 构造
public:
	CvirtualdeskDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIRTUALDESK_DIALOG };
	int m_curId;
	int m_count;
	CString m_deskName;
	PROCESS_INFORMATION m_processInfo[2];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 创建虚拟桌面
	void m_CreateDesk(LPARAM lParam,int num);
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnBnClickedSwdesk1();
	afx_msg void OnBnClickedSwdesk2();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	// 注册热键
	void CreateHotKey(void);
	afx_msg void OnDestroy();
	// 切换桌面
	void SwitchDesk(void);
};
