// virtualdesk.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CvirtualdeskApp:
// �йش����ʵ�֣������ virtualdesk.cpp
//

class CvirtualdeskApp : public CWinApp
{
public:
	CvirtualdeskApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CvirtualdeskApp theApp;