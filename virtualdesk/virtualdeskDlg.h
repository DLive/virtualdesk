// virtualdeskDlg.h : ͷ�ļ�
//

#pragma once


// CvirtualdeskDlg �Ի���
class CvirtualdeskDlg : public CDialog
{
// ����
public:
	CvirtualdeskDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIRTUALDESK_DIALOG };
	int m_curId;
	int m_count;
	CString m_deskName;
	PROCESS_INFORMATION m_processInfo[2];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ������������
	void m_CreateDesk(LPARAM lParam,int num);
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnBnClickedSwdesk1();
	afx_msg void OnBnClickedSwdesk2();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	// ע���ȼ�
	void CreateHotKey(void);
	afx_msg void OnDestroy();
	// �л�����
	void SwitchDesk(void);
};
