
// UsbKeyUtilDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CUsbKeyUtilDlg 对话框
class CUsbKeyUtilDlg : public CDHtmlDialog
{
// 构造
public:
	CUsbKeyUtilDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBKEYUTIL_DIALOG, IDH = IDR_HTML_USBKEYUTIL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:

	afx_msg void OnBnClickedstartinit();
	CString v_soPin;
	CString v_userPin;
	int v_maxSoPinRetries;
	int v_maxUserPinRetries;
	CString v_soErrorMaxMSg;
	CString v_userErrorMaxMSg;
};
