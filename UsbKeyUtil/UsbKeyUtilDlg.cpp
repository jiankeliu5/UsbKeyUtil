
// UsbKeyUtilDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUsbKeyUtilDlg �Ի���

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
	, v_soErrorMaxMSg(_T("��ǰ���������0��"))
	, v_userErrorMaxMSg(_T("��ǰ���������0��"))
	, v_hardwareSerialNumber(_T("�ȴ��豸����"))
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


// CUsbKeyUtilDlg ��Ϣ�������

BOOL CUsbKeyUtilDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUsbKeyUtilDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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


//��ʾ������Ϣ
void ShowErrInfo(EPAS_STATUS retval)
{
	switch (retval)
	{
		//case FT_SUCCESS:
		//printf("Success!\n");
		//return;
	case FT_CANNOT_OPEN_DRIVER:
		AfxMessageBox(_T("Err: �޷����豸��failed to open the driver!"));
		break;
	case FT_INVALID_DRVR_VERSION:
		AfxMessageBox(_T("Err: ��Ч����������汾��Invalid driver version!"));
		break;
	case FT_INVALID_COMMAND:
		AfxMessageBox(_T("Err: ������Ч��Invalid command!"));
		break;
	case FT_ACCESS_DENIED:
		AfxMessageBox(_T("Err: �ܾ����ʣ�������󣩣�access denied!"));
		break;
	case FT_UNIT_NOT_FOUND:
		AfxMessageBox(_T("Err: ���Ȳ���USBKEY�豸��unit was not found!"));
		break;
	case FT_DEVICE_REMOVED:
		AfxMessageBox(_T("Err: ���豸��ɾ����the device was removed!"));
		break;
	case FT_COMMUNICATIONS_ERROR:
		AfxMessageBox(_T("Err: ͨѶ�쳣��ֹ��communication terminated abnormally!"));
		break;
	case FT_DIR_NOT_FOUND:
		AfxMessageBox(_T("Err: ��Ŀ¼û�б����֣�The directory was not found!"));
		break;
	case FT_FILE_NOT_FOUND:
		AfxMessageBox(_T("Err: ���ļ�û�б����֣�The file was not found!"));
		break;
	case FT_MEM_CORRUPT:
		AfxMessageBox(_T("Err: �����ڵ��ڴ����𻵣�Memory inside the token was corrupted!"));
		break;
	case FT_INTERNAL_HW_ERROR:
		AfxMessageBox(_T("Err: �����ڲ�Ӳ������Internal hardware error occured!"));
		break;
	case FT_INVALID_RESP_SIZE:
		AfxMessageBox(_T("Err: �������յ����쳣��Ӧ��Abnormal response received from the token!"));
		break;
	case FT_PIN_EXPIRED:
		AfxMessageBox(_T("Err: PIN���Լ������Ĵ��������㣡The PIN retry counter register return zero!"));
		break;
	case FT_ALREADY_EXISTS:
		AfxMessageBox(_T("Err: ����Ŀ�Ѿ����ڣ�The item already exist!"));
		break;
	case FT_NOT_ENOUGH_MEMORY:
		AfxMessageBox(_T("Err: �ڴ治����ִ�����Insufficient memory to perform the command!"));
		break;
	case FT_INVALID_PARAMETER:
		AfxMessageBox(_T("Err: ��Ч�Ĳ�����������ù��ܣ�Invalid parameter was assigned to the function!"));
		break;
	case FT_INPUT_TOO_LONG:
		AfxMessageBox(_T("Err: �������ݵĳ���̫���ˣ�The length of the input data is too long!"));
		break;
	case FT_INVALID_FILE_SELECTED:
		AfxMessageBox(_T("Err: ��ѡ�ļ���Ч��The selected file is invalid!"));
		break;
	case FT_DEVICE_IN_USE:
		AfxMessageBox(_T("Err: ���豸Ŀǰ���ڱ���һ��Ӧ�ó���ʹ�ã�The device is currently used by another application!"));
		break;
	case FT_INVALID_API_VERSION:
		AfxMessageBox(_T("Err: API��İ汾��Ч��The version of the API library is invalid!"));
		break;
	case FT_TIME_OUT_ERROR:
		AfxMessageBox(_T("Err: ������ʱ��The operation time out!"));
		break;
	case FT_ITEM_NOT_FOUND:
		AfxMessageBox(_T("Err: ����Ŀû�б����֣�The item was not found!"));
		break;
	case FT_COMMAND_ABORTED:
		AfxMessageBox(_T("Err: �����쳣��ֹ��Command aborted abnormally!"));
		break;
	case FT_INVALID_STATUS:
		AfxMessageBox(_T("Err: �������յ���Ч�ķ���ֵ��Invalid return value received from the token!"));
		break;
	default:
		AfxMessageBox(_T("Err: ����δ֪����Unknown error occured!"));
		break;
	}
}


EPAS_HANDLE g_hToken = NULL;
EPAS_STATUS retval = FT_SUCCESS;
void CUsbKeyUtilDlg::OnBnClickedstartinit()
{
	// �����ؼ��е����ݱ��浽��Ӧ�ı���   
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

	//�޸ĳ�������Ա����
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
	//��ʽ���豸
	retval = epas_SetProperty(g_hToken, EPAS_PROP_INIT_TOKEN, NULL, tBuf, strlen((char*)tBuf));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}


	//�����豸-�������û�����
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

	//����Ŀ¼
	EPAS_DIRINFO di = { 0 };
	di.ulID = 0x1000;
	di.ulFlags = 0;
	//Ŀ¼��
	char * path = "YH";
	retval = epas_CreateDir(g_hToken, EPAS_CREATE_AUTO_ID, (unsigned char*)path, NULL, &di, sizeof(di));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	//�����ļ�1
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
	//��������
	MD5_HMAC(NULL, ulText_Len, (unsigned char*)newSoPin, 4, key1, key2, pucDigest);
	unsigned long ulFileSize = 16;
	unsigned long ulWritten;
	//д�ļ�1
	retval = epas_Write(g_hToken, 0, 0, key1, ulFileSize, &ulWritten);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//�����ļ�2
	fi1.ulID = 0x2;
	retval = epas_CreateFile(g_hToken, 0, &fi1, sizeof(fi1));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	//д�ļ�2
	retval = epas_Write(g_hToken, 0, 0, key2, ulFileSize, &ulWritten);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//�ر�led״̬��
	retval = epas_SetProperty(g_hToken, EPAS_PROP_LED_OFF, NULL, NULL, 0);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//�ر��豸
	epas_CloseDevice(g_hToken);
	//ɾ��������
	epas_DeleteContext(g_hToken);


	v_soErrorMaxMSg = _T("��ǰ������� ��0��");
	v_userErrorMaxMSg= _T("��ǰ������� ��0��");
	v_hardwareSerialNumber = _T("�ȴ��豸����");


	// ���ݸ�������ֵ������Ӧ�Ŀؼ�
	UpdateData(FALSE);
	AfxMessageBox(_T("��ʼ����ɣ�Success��"));
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




//���豸
void CUsbKeyUtilDlg::OnBnClickedButton1()
{

	//����������
	retval = epas_CreateContext(&g_hToken, 0, EPAS_API_VERSION);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	//���豸
	retval = epas_OpenDevice(g_hToken, EPAS_OPEN_FIRST, NULL);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}

	//ȡ���豸��Ϣ
	EPAS_ACCESSINFO aInfo = { 0 };
	retval = epas_GetProperty(g_hToken, EPAS_PROP_ACCESSINFO, NULL, &aInfo, sizeof(aInfo));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	v_maxSoPinRetries = aInfo.ucMaxSoPinRetries;
	v_maxUserPinRetries = aInfo.ucMaxUserPinRetries;
	v_soErrorMaxMSg.Format(_T("��ǰ������� ��%d��"), aInfo.ucMaxSoPinRetries - aInfo.ucCurSoPinCounter);
	v_userErrorMaxMSg.Format(_T("��ǰ������� ��%d��"), aInfo.ucMaxUserPinRetries - aInfo.ucCurUserPinCounter);
	long sn[2] = { 0 };
	retval = epas_GetProperty(g_hToken, EPAS_PROP_SERNUM, NULL, sn, sizeof(sn));
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	v_hardwareSerialNumber.Format(_T("�豸�����ӣ��豸���кţ� %08lX%08lX ��"), sn[1], sn[0]);

	//��led״̬��
	retval = epas_SetProperty(g_hToken, EPAS_PROP_LED_ON, NULL, NULL, 0);
	if (FT_SUCCESS != retval)
	{
		ShowErrInfo(retval);
		return;
	}
	UpdateData(False);


	//::MessageBox(NULL, _T("XXX"), _T("����"), MB_OK);
}



