
// UsbKeyUtilDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CUsbKeyUtilDlg �Ի���
class CUsbKeyUtilDlg : public CDHtmlDialog
{
// ����
public:
	CUsbKeyUtilDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBKEYUTIL_DIALOG, IDH = IDR_HTML_USBKEYUTIL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
