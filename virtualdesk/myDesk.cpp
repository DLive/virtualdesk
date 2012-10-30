// myDesk.cpp : 实现文件
//

#include "stdafx.h"
#include "virtualdesk.h"
#include "myDesk.h"


// CmyDesk

CmyDesk::CmyDesk()
{
}

CmyDesk::~CmyDesk()
{
}


// CmyDesk 成员函数

void CmyDesk::setIcon(void)
{
	HWND  hwndParent = ::FindWindow( _T("Progman"), _T("Program Manager" )); 
    HWND  hwndSHELLDLL_DefView = ::FindWindowEx( hwndParent, NULL, _T("SHELLDLL_DefView"), NULL ); 
    HWND  hwndSysListView32 = ::FindWindowEx( hwndSHELLDLL_DefView, NULL, _T("SysListView32"), _T("FolderView") );
	(CWnd::FromHandle(hwndSHELLDLL_DefView))->MoveWindow(-100,-100,800,800,1);
	/*LVBKIMAGE lv;
	
	ZeroMemory(&lv,sizeof(lv));
	lv.ulFlags=LVBKIF_SOURCE_URL|LVBKIF_STYLE_TILE;
	lv.pszImage=_T("F:\\2.jpg");
	lv.xOffsetPercent=0;
	lv.yOffsetPercent=0;
	lv.cchImageMax=sizeof(lv.pszImage);
	ListView_SetBkImage(hwndSysListView32,&lv);*/
}
