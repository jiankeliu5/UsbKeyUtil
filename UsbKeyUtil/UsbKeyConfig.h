#pragma once


// CUsbKeyConfig 对话框

class CUsbKeyConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CUsbKeyConfig)

public:
	CUsbKeyConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUsbKeyConfig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBKEYUTIL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
