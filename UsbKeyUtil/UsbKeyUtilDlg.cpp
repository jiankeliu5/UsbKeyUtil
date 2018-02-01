
// UsbKeyUtilDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UsbKeyUtil.h"
#include "UsbKeyUtilDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;



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
	, v_maxSoPinRetries(15)
	, v_maxUserPinRetries(15)
	, v_soErrorMaxMSg(_T("当前错误次数（0）"))
	, v_userErrorMaxMSg(_T("当前错误次数（0）"))
	, v_hardwareSerialNumber(_T("等待设备连接"))
	, v_soPinOld(_T(""))
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
	DDX_Text(pDX, HardwareSerialNumber, v_hardwareSerialNumber);
	DDX_Text(pDX, soPinOld, v_soPinOld);
	DDV_MaxChars(pDX, v_soPinOld, 15);
}

BEGIN_MESSAGE_MAP(CUsbKeyUtilDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(startInit, &CUsbKeyUtilDlg::OnBnClickedstartinit)
	ON_BN_CLICKED(exitSystem, &CUsbKeyUtilDlg::OnBnClickedexitsystem)
	ON_EN_CHANGE(soPinOld, &CUsbKeyUtilDlg::OnEnChangesopinold)
	ON_EN_CHANGE(soPin, &CUsbKeyUtilDlg::OnEnChangesopin)
	ON_EN_CHANGE(userPin, &CUsbKeyUtilDlg::OnEnChangeuserpin)
	ON_EN_CHANGE(maxSoPinRetries, &CUsbKeyUtilDlg::OnEnChangemaxsopinretries)
	ON_EN_CHANGE(maxUserPinRetries, &CUsbKeyUtilDlg::OnEnChangemaxuserpinretries)
	ON_BN_CLICKED(IDC_BUTTON1, &CUsbKeyUtilDlg::OnBnClickedButton1)
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


//提示错误信息
void ShowErrInfo(EPAS_STATUS retval)
{
	switch (retval)
	{
		//case FT_SUCCESS:
		//printf("Success!\n");
		//return;
	case FT_CANNOT_OPEN_DRIVER:
		AfxMessageBox(_T("Err: 无法打开设备！failed to open the driver!"));
		break;
	case FT_INVALID_DRVR_VERSION:
		AfxMessageBox(_T("Err: 无效的驱动程序版本！Invalid driver version!"));
		break;
	case FT_INVALID_COMMAND:
		AfxMessageBox(_T("Err: 命令无效！Invalid command!"));
		break;
	case FT_ACCESS_DENIED:
		AfxMessageBox(_T("Err: 拒绝访问（密码错误）！access denied!"));
		break;
	case FT_UNIT_NOT_FOUND:
		AfxMessageBox(_T("Err: 请先插入USBKEY设备！unit was not found!"));
		break;
	case FT_DEVICE_REMOVED:
		AfxMessageBox(_T("Err: 该设备被删除！the device was removed!"));
		break;
	case FT_COMMUNICATIONS_ERROR:
		AfxMessageBox(_T("Err: 通讯异常终止！communication terminated abnormally!"));
		break;
	case FT_DIR_NOT_FOUND:
		AfxMessageBox(_T("Err: 该目录没有被发现！The directory was not found!"));
		break;
	case FT_FILE_NOT_FOUND:
		AfxMessageBox(_T("Err: 该文件没有被发现！The file was not found!"));
		break;
	case FT_MEM_CORRUPT:
		AfxMessageBox(_T("Err: 令牌内的内存已损坏！Memory inside the token was corrupted!"));
		break;
	case FT_INTERNAL_HW_ERROR:
		AfxMessageBox(_T("Err: 发生内部硬件错误！Internal hardware error occured!"));
		break;
	case FT_INVALID_RESP_SIZE:
		AfxMessageBox(_T("Err: 从令牌收到的异常响应！Abnormal response received from the token!"));
		break;
	case FT_PIN_EXPIRED:
		AfxMessageBox(_T("Err: PIN重试计数器寄存器返回零！The PIN retry counter register return zero!"));
		break;
	case FT_ALREADY_EXISTS:
		AfxMessageBox(_T("Err: 该项目已经存在！The item already exist!"));
		break;
	case FT_NOT_ENOUGH_MEMORY:
		AfxMessageBox(_T("Err: 内存不足以执行命令！Insufficient memory to perform the command!"));
		break;
	case FT_INVALID_PARAMETER:
		AfxMessageBox(_T("Err: 无效的参数被分配给该功能！Invalid parameter was assigned to the function!"));
		break;
	case FT_INPUT_TOO_LONG:
		AfxMessageBox(_T("Err: 输入数据的长度太长了！The length of the input data is too long!"));
		break;
	case FT_INVALID_FILE_SELECTED:
		AfxMessageBox(_T("Err: 所选文件无效！The selected file is invalid!"));
		break;
	case FT_DEVICE_IN_USE:
		AfxMessageBox(_T("Err: 该设备目前正在被另一个应用程序使用！The device is currently used by another application!"));
		break;
	case FT_INVALID_API_VERSION:
		AfxMessageBox(_T("Err: API库的版本无效！The version of the API library is invalid!"));
		break;
	case FT_TIME_OUT_ERROR:
		AfxMessageBox(_T("Err: 操作超时！The operation time out!"));
		break;
	case FT_ITEM_NOT_FOUND:
		AfxMessageBox(_T("Err: 该项目没有被发现！The item was not found!"));
		break;
	case FT_COMMAND_ABORTED:
		AfxMessageBox(_T("Err: 命令异常中止！Command aborted abnormally!"));
		break;
	case FT_INVALID_STATUS:
		AfxMessageBox(_T("Err: 从令牌收到无效的返回值！Invalid return value received from the token!"));
		break;
	default:
		AfxMessageBox(_T("Err: 发生未知错误！Unknown error occured!"));
		break;
	}
}


EPAS_HANDLE g_hToken = NULL;
EPAS_STATUS retval = FT_SUCCESS;
void CUsbKeyUtilDlg::OnBnClickedstartinit()
{
	// 将各控件中的数据保存到相应的变量   
	UpdateData(TRUE);

	char * oldSoPin;
	LPCTSTR p = v_soPinOld.GetBuffer(0);
	v_soPinOld.ReleaseBuffer();
	oldSoPin = new char[v_soPinOld.GetLength() + 1];
	strcpy_s(oldSoPin, v_soPinOld.GetLength() + 1, CT2CA(p));

	char * newSoPin;
	LPCTSTR p2 = v_soPin.GetBuffer(0);
	v_soPin.ReleaseBuffer();
	newSoPin = new char[v_soPin.GetLength() + 1];
	strcpy_s(newSoPin, v_soPin.GetLength() + 1, CT2CA(p2));

	//修改超级管理员密码
	retval = epas_ChangeCode(
		g_hToken, EPAS_CHANGE_SO_PIN,
		(unsigned char*)oldSoPin,
		strlen(oldSoPin),
		(unsigned char*)newSoPin,
		strlen(newSoPin));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	char tBuf[32] = { 0 };
	tBuf[0] = 1;
	//格式化设备
	retval = epas_SetProperty(g_hToken, EPAS_PROP_INIT_TOKEN, NULL, tBuf, strlen((char*)tBuf));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}


	//解锁设备-并重置用户密码
	char * newUserPin;
	LPCTSTR p3 = v_userPin.GetBuffer(0);
	v_userPin.ReleaseBuffer();
	newUserPin = new char[v_userPin.GetLength() + 1];
	strcpy_s(newUserPin, v_userPin.GetLength() + 1, CT2CA(p3));

	retval = epas_ChangeCode(g_hToken,
		EPAS_UNBLOCK_USER_PIN,
		(unsigned char*)newSoPin,
		strlen(newSoPin),
		(unsigned char*)newUserPin,
		strlen(newUserPin));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//创建目录
	EPAS_DIRINFO di = { 0 };
	di.ulID = 0x1000;
	di.ulFlags = 0;
	//目录名
	char * path = "YH";
	retval = epas_CreateDir(g_hToken, EPAS_CREATE_AUTO_ID, (unsigned char*)path, NULL, &di, sizeof(di));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	//创建文件1
	EPAS_FILEINFO fi1 = { 0 };
	fi1.ulID= 0x1;
	fi1.ulFileSize = 16;
	fi1.ucFileType = EPAS_FILETYPE_MD5;
	fi1.ucReadAccess = EPAS_ACCESS_NONE;
	fi1.ucCryptAccess = EPAS_ACCESS_USER;
	fi1.ucWriteAccess = EPAS_ACCESS_ANYONE;
	retval = epas_CreateFile(g_hToken, 0, &fi1, sizeof(fi1));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	unsigned long ulText_Len = 0;
	unsigned char pucDigest[16] = { 0 };
	unsigned char key1[16] = { 0 };
	unsigned char key2[16] = { 0 };
	//生成密文
	MD5_HMAC(NULL, ulText_Len, (unsigned char*)newSoPin, 4, key1, key2, pucDigest);
	unsigned long ulFileSize = 16;
	unsigned long ulWritten;
	//写文件1
	retval = epas_Write(g_hToken, 0, 0, key1, ulFileSize, &ulWritten);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//创建文件2
	fi1.ulID = 0x2;
	retval = epas_CreateFile(g_hToken, 0, &fi1, sizeof(fi1));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	//写文件2
	retval = epas_Write(g_hToken, 0, 0, key2, ulFileSize, &ulWritten);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//关闭led状态灯
	retval = epas_SetProperty(g_hToken, EPAS_PROP_LED_OFF, NULL, NULL, 0);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//关闭设备
	epas_CloseDevice(g_hToken);
	//删除上下文
	epas_DeleteContext(g_hToken);


	v_soErrorMaxMSg = _T("当前错误次数 （0）");
	v_userErrorMaxMSg= _T("当前错误次数 （0）");
	v_hardwareSerialNumber = _T("等待设备连接");


	// 根据各变量的值更新相应的控件
	UpdateData(FALSE);
	AfxMessageBox(_T("初始化完成！Success！"));
}


void CUsbKeyUtilDlg::OnBnClickedexitsystem()
{
	OnCancel();
}


void CUsbKeyUtilDlg::OnEnChangesopinold()
{
	UpdateData(TRUE);
}


void CUsbKeyUtilDlg::OnEnChangesopin()
{
	UpdateData(TRUE);
}


void CUsbKeyUtilDlg::OnEnChangeuserpin()
{
	UpdateData(TRUE);
}


void CUsbKeyUtilDlg::OnEnChangemaxsopinretries()
{
	UpdateData(TRUE);
}


void CUsbKeyUtilDlg::OnEnChangemaxuserpinretries()
{
	UpdateData(TRUE);
}




//打开设备
void CUsbKeyUtilDlg::OnBnClickedButton1()
{

	//创建上下文
	retval = epas_CreateContext(&g_hToken, 0, EPAS_API_VERSION);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	//打开设备
	retval = epas_OpenDevice(g_hToken, EPAS_OPEN_FIRST, NULL);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//取得设备信息
	EPAS_ACCESSINFO aInfo = { 0 };
	retval = epas_GetProperty(g_hToken, EPAS_PROP_ACCESSINFO, NULL, &aInfo, sizeof(aInfo));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	v_maxSoPinRetries = aInfo.ucMaxSoPinRetries;
	v_maxUserPinRetries = aInfo.ucMaxUserPinRetries;
	v_soErrorMaxMSg.Format(_T("当前错误次数 （%d）"), aInfo.ucMaxSoPinRetries - aInfo.ucCurSoPinCounter);
	v_userErrorMaxMSg.Format(_T("当前错误次数 （%d）"), aInfo.ucMaxUserPinRetries - aInfo.ucCurUserPinCounter);
	long sn[2] = { 0 };
	retval = epas_GetProperty(g_hToken, EPAS_PROP_SERNUM, NULL, sn, sizeof(sn));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	v_hardwareSerialNumber.Format(_T("设备已连接！设备序列号（ %08lX%08lX ）"), sn[1], sn[0]);

	//打开led状态灯
	retval = epas_SetProperty(g_hToken, EPAS_PROP_LED_ON, NULL, NULL, 0);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	UpdateData(False);


	//::MessageBox(NULL, _T("XXX"), _T("警告"), MB_OK);
}



