
// UsbKeyUtilDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UsbKeyUtil.h"
#include "UsbKeyUtilDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUsbKeyUtilDlg 对话框

BEGIN_DHTML_EVENT_MAP(CUsbKeyUtilDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CUsbKeyUtilDlg::CUsbKeyUtilDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_USBKEYUTIL_DIALOG, IDR_HTML_USBKEYUTIL_DIALOG, pParent)
	, v_soPin(_T(""))
	, v_userPin(_T(""))
	, v_maxSoPinRetries(0)
	, v_maxUserPinRetries(0)
	, v_soErrorMaxMSg(_T("当前错误次数（0）"))
	, v_userErrorMaxMSg(_T("当前错误次数（0）"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsbKeyUtilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_Text(pDX, soPin, v_soPin);
	DDV_MaxChars(pDX, v_soPin, 15);

	DDX_Text(pDX, userPin, v_userPin);
	DDV_MaxChars(pDX, v_userPin, 15);


	DDX_Text(pDX, maxSoPinRetries, v_maxSoPinRetries);
	DDV_MinMaxInt(pDX, v_maxSoPinRetries, 1, 15);

	DDX_Text(pDX, maxUserPinRetries, v_maxUserPinRetries);
	DDV_MinMaxInt(pDX, v_maxUserPinRetries, 1, 15);
	DDX_Text(pDX, soErrorMaxMsg, v_soErrorMaxMSg);
	DDX_Text(pDX, userErrorMaxMsg, v_userErrorMaxMSg);
}

BEGIN_MESSAGE_MAP(CUsbKeyUtilDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(startInit, &CUsbKeyUtilDlg::OnBnClickedstartinit)
END_MESSAGE_MAP()


// CUsbKeyUtilDlg 消息处理程序

BOOL CUsbKeyUtilDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUsbKeyUtilDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUsbKeyUtilDlg::OnPaint()
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
		CDHtmlDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUsbKeyUtilDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CUsbKeyUtilDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CUsbKeyUtilDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}








void CUsbKeyUtilDlg::OnBnClickedstartinit()
{
	// 将各控件中的数据保存到相应的变量   
	UpdateData(TRUE);
	v_maxSoPinRetries = v_maxSoPinRetries + v_maxUserPinRetries;
	v_soErrorMaxMSg = "当前错误次数（2）";
	v_userErrorMaxMSg = "当前错误次数（3）";



	// 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
	UpdateData(FALSE);
	OnCancel();
}
