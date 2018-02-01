// UsbKeyConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "UsbKeyUtil.h"
#include "UsbKeyConfig.h"
#include "afxdialogex.h"


// CUsbKeyConfig 对话框

IMPLEMENT_DYNAMIC(CUsbKeyConfig, CDialogEx)

CUsbKeyConfig::CUsbKeyConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USBKEYUTIL_DIALOG, pParent)
{

}

CUsbKeyConfig::~CUsbKeyConfig()
{
}

void CUsbKeyConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUsbKeyConfig, CDialogEx)
END_MESSAGE_MAP()


// CUsbKeyConfig 消息处理程序
