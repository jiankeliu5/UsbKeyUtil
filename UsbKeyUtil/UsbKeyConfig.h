#pragma once


// CUsbKeyConfig �Ի���

class CUsbKeyConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CUsbKeyConfig)

public:
	CUsbKeyConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUsbKeyConfig();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBKEYUTIL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
