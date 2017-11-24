// MFCDLL.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "MFCDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import "C:\\Windows\\System32\\WinHttpCom.dll" no_namespace
//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCDLLApp

BEGIN_MESSAGE_MAP(CMFCDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFCDLLApp 构造

CMFCDLLApp::CMFCDLLApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMFCDLLApp 对象

CMFCDLLApp theApp;


// CMFCDLLApp 初始化

BOOL CMFCDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


CString GetMidStrByLAndR(CString& strSrc, CString strLeft, CString strRight)
{
	CString strRet;
	int eIndxBegin = strSrc.Find(strLeft);
	if (eIndxBegin != -1)
	{
		eIndxBegin += strLeft.GetLength();
		int eIndxEnd = strSrc.Find(strRight, eIndxBegin);
		if (eIndxEnd != -1)
		{
			strRet += strSrc.Mid(eIndxBegin, eIndxEnd-eIndxBegin);
			return strRet;
			
		}
	}
	return strRet;
}


CString GetMd5D(CString strMd5)
{
	CoInitialize(NULL);
	IWinHttpRequestPtr pHttp = NULL;
	HRESULT hr = pHttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}

	CString strGetMd5;
	strGetMd5.Format(_T("http://md5.syue.com/ShowMD5Info.asp?GetType=ShowInfo&no-cache=0.2149362659992714&md5_str=%s&_="), strMd5);
	pHttp->Open(_T("GET"), strGetMd5.AllocSysString());
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}
	pHttp->SetRequestHeader(_T("Referer"), _T("http://md5.syue.com/"));
	pHttp->Send();
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}

	_variant_t varRspBody = pHttp->GetResponseBody();
	ULONG dataLen = varRspBody.parray->rgsabound[0].cElements;
	char *pContenBuffer = (char *)varRspBody.parray->pvData;
	CString strContenBuffer;
	strContenBuffer = pContenBuffer;
	CString MD5 = GetMidStrByLAndR(strContenBuffer, _T("height:25px\">"), _T("</span"));
	return MD5;
}