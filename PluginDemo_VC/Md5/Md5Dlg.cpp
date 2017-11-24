
// Md5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Md5.h"
#include "Md5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib, "../debug/MFCDLL.lib")
_declspec(dllimport)CString GetMd5D(CString strMd5);

// CMd5Dlg 对话框



CMd5Dlg::CMd5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMd5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMd5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMd5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMd5Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMd5Dlg 消息处理程序

BOOL CMd5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMd5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMd5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMd5Dlg::OnBnClickedButton1()
{
	CString strMd5;
	GetDlgItemText(IDC_EDIT_MD5, strMd5);

	int iMd5 = strMd5.GetLength();
	if ( iMd5 != 16 && iMd5 != 32 )
	{
		MessageBox(_T("请输入16或32位的MD5字符串"));
		return;
	}

	CString MD5 = GetMd5D(strMd5);
	SetDlgItemText(IDC_EDIT_MD5D, MD5);
}
