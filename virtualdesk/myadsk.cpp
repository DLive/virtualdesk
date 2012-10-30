// myadsk.cpp : 实现文件
//

#include "stdafx.h"
#include "virtualdesk.h"
#include "myadsk.h"
#include <shlobj.h>

// Cmyadsk

Cmyadsk::Cmyadsk()
{
}

Cmyadsk::~Cmyadsk()
{
}


// Cmyadsk 成员函数
BOOL Cmyadsk::SetWallPaper(LPWSTR strPicFile, DWORD dwStyle)
{
  HRESULT hr;
  IActiveDesktop* pIAD;
	//创建接口的实例
  hr = CoCreateInstance ( CLSID_ActiveDesktop,  NULL, CLSCTX_INPROC_SERVER,       
              IID_IActiveDesktop, (void**) &pIAD );
  if(!SUCCEEDED(hr)) return FALSE;
  //将文件名改为宽字符串,这是IActiveDesktop::SetWallpaper的要求
  //WCHAR   wszWallpaper [MAX_PATH];
  //LPTSTR lpStr = strPicFile.GetBuffer(strPicFile.GetLength() );
  //MultiByteToWideChar(CP_ACP, 0, lpStr, -1, wszWallpaper, MAX_PATH);
  //strPicFile.ReleaseBuffer();
  //设置墙纸
  hr = pIAD->SetWallpaper(strPicFile, 0);
  if(!SUCCEEDED(hr)) return FALSE;
  //设置墙纸的样式
  WALLPAPEROPT wpo;
  wpo.dwSize = sizeof(wpo);
  wpo.dwStyle = dwStyle;
  hr = pIAD->SetWallpaperOptions(&wpo, 0);
  if(!SUCCEEDED(hr)) return FALSE;
  //应用墙纸的设置
  hr = pIAD->ApplyChanges(AD_APPLY_ALL);
  if(!SUCCEEDED(hr)) return FALSE;
  //读取墙纸的文件名并打印在debug窗口内
  //LPWSTR aa;
  //hr = pIAD->GetWallpaper(aa, MAX_PATH, 0);
  //CString strFile = aa;
  //TRACE(strFile); //如果不用位图的话,这里有你意想不到的发现
  //释放接口的实例
  pIAD->Release();
  CoFreeUnusedLibraries();     
  CoUninitialize();
  return TRUE;
}
// Active check
BOOL Cmyadsk::CheckEnableActive(void)
{
  HRESULT hr;
  IActiveDesktop* pIAD;
  //创建接口的实例
  hr = CoCreateInstance ( CLSID_ActiveDesktop,  NULL, CLSCTX_INPROC_SERVER,       
              IID_IActiveDesktop, (void**) &pIAD );
  COMPONENTSOPT comp;
  comp.dwSize = sizeof(comp);
  //启用或关闭active desktop
  //comp.fActiveDesktop = bEnable;
  hr = pIAD->GetDesktopItemOptions(&comp, 0);
  if(comp.fActiveDesktop)
	  return TRUE;
  else
	  return FALSE;
  //释放接口的实例
  pIAD->Release();
  return TRUE;
}
