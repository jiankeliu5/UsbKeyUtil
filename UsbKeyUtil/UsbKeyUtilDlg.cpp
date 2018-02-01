
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
	, v_hardwareSerialNumber(_T(""))
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

EPAS_HANDLE g_hToken = NULL;
EPAS_STATUS retval = FT_SUCCESS;
void CUsbKeyUtilDlg::OnBnClickedstartinit()
{
	// �����ؼ��е����ݱ��浽��Ӧ�ı���   
	UpdateData(TRUE);
	v_maxSoPinRetries = v_maxSoPinRetries + v_maxUserPinRetries;


	printf("Create Context:");
	retval = epas_CreateContext(&g_hToken, 0, EPAS_API_VERSION);
	if (FT_SUCCESS != retval)
	{
		return;
	}
	printf("Open device:");
	retval = epas_OpenDevice(g_hToken, EPAS_OPEN_FIRST, NULL);
	if (FT_SUCCESS != retval)
	{
		return;
	}


	EPAS_ACCESSINFO aInfo = { 0 };
	retval = epas_GetProperty(g_hToken, EPAS_PROP_ACCESSINFO, NULL, &aInfo, sizeof(aInfo));
	if (FT_SUCCESS != retval)
	{
		return;
	}
	v_maxSoPinRetries = aInfo.ucMaxSoPinRetries;
	v_maxUserPinRetries = aInfo.ucMaxUserPinRetries;
	v_soErrorMaxMSg.Format(_T("��ǰ������� ��%d��"), aInfo.ucMaxSoPinRetries-aInfo.ucCurSoPinCounter);
	v_userErrorMaxMSg.Format(_T("��ǰ������� ��%d��"), aInfo.ucMaxUserPinRetries-aInfo.ucCurUserPinCounter);
	long sn[2] = { 0 };
	retval = epas_GetProperty(g_hToken, EPAS_PROP_SERNUM, NULL, sn, sizeof(sn));
	if (FT_SUCCESS != retval)
	{
		return;
	}
	v_hardwareSerialNumber.Format(_T("�豸���кţ�%08lX%08lX"),sn[1],sn[0]); 

	char oldPin[80] = { 0 };
	char newPin[80] = { 0 };


	
//	retval = epas_ChangeCode(
//		g_hToken, EPAS_CHANGE_SO_PIN,
//		(unsigned char*)oldPin,
//		soOldLen,
//		(unsigned char*)newPin,
//		soNewLen);
//	if (FT_SUCCESS != retval)
//	{
//		return;
//	}



	// ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
	UpdateData(FALSE);
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
