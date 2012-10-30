// myadsk.cpp : ʵ���ļ�
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


// Cmyadsk ��Ա����
BOOL Cmyadsk::SetWallPaper(LPWSTR strPicFile, DWORD dwStyle)
{
  HRESULT hr;
  IActiveDesktop* pIAD;
	//�����ӿڵ�ʵ��
  hr = CoCreateInstance ( CLSID_ActiveDesktop,  NULL, CLSCTX_INPROC_SERVER,       
              IID_IActiveDesktop, (void**) &pIAD );
  if(!SUCCEEDED(hr)) return FALSE;
  //���ļ�����Ϊ���ַ���,����IActiveDesktop::SetWallpaper��Ҫ��
  //WCHAR   wszWallpaper [MAX_PATH];
  //LPTSTR lpStr = strPicFile.GetBuffer(strPicFile.GetLength() );
  //MultiByteToWideChar(CP_ACP, 0, lpStr, -1, wszWallpaper, MAX_PATH);
  //strPicFile.ReleaseBuffer();
  //����ǽֽ
  hr = pIAD->SetWallpaper(strPicFile, 0);
  if(!SUCCEEDED(hr)) return FALSE;
  //����ǽֽ����ʽ
  WALLPAPEROPT wpo;
  wpo.dwSize = sizeof(wpo);
  wpo.dwStyle = dwStyle;
  hr = pIAD->SetWallpaperOptions(&wpo, 0);
  if(!SUCCEEDED(hr)) return FALSE;
  //Ӧ��ǽֽ������
  hr = pIAD->ApplyChanges(AD_APPLY_ALL);
  if(!SUCCEEDED(hr)) return FALSE;
  //��ȡǽֽ���ļ�������ӡ��debug������
  //LPWSTR aa;
  //hr = pIAD->GetWallpaper(aa, MAX_PATH, 0);
  //CString strFile = aa;
  //TRACE(strFile); //�������λͼ�Ļ�,�����������벻���ķ���
  //�ͷŽӿڵ�ʵ��
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
  //�����ӿڵ�ʵ��
  hr = CoCreateInstance ( CLSID_ActiveDesktop,  NULL, CLSCTX_INPROC_SERVER,       
              IID_IActiveDesktop, (void**) &pIAD );
  COMPONENTSOPT comp;
  comp.dwSize = sizeof(comp);
  //���û�ر�active desktop
  //comp.fActiveDesktop = bEnable;
  hr = pIAD->GetDesktopItemOptions(&comp, 0);
  if(comp.fActiveDesktop)
	  return TRUE;
  else
	  return FALSE;
  //�ͷŽӿڵ�ʵ��
  pIAD->Release();
  return TRUE;
}
