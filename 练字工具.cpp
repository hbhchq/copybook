// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// ���ֹ���.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "���ֹ���.h"
#include "MainFrm.h"

#include "���ֹ���Doc.h"
#include "���ֹ���View.h"
#include "license.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMyApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CMyApp ����
const CString CMyApp::s_strLicenceFlag=L"Copybook";
CMyApp::CMyApp()
: m_bLicense(false)
, m_strLicenceFile(_T(""))
{

	m_bHiColorIcons = TRUE;
	
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMyApp ����

CMyApp theApp;


// CMyApp ��ʼ��

BOOL CMyApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//��ΪӢ�İ��ΪCalligraphyCopy
	SetRegistryKey(_T("HCHQ"));
	LoadStdProfileSettings(16);  // ���ر�׼ INI �ļ�ѡ��

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMyView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	//������Ϣ������ɳ�ʼ�����񴰸�Ĳ���
	m_pMainWnd->PostMessage(WM_SHOWWINDOW,1);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CHardwareInfor m_dlgHardwareInfor;
// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLicense();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMachineId();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(ID_LICENSE, &CAboutDlg::OnBnClickedLicense)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MACHINE_ID, &CAboutDlg::OnBnClickedMachineId)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMyApp �Զ������/���淽��

void CMyApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMyApp::LoadCustomState()
{
	//m_strLicenceFile
////////LANG_CHINESE_SIMPLIFIED 
	m_strLicenceFile=GetString(_T("LicenceFile"));
	m_bLicense=this->CheckLicence();
	
}

void CMyApp::SaveCustomState()
{
	WriteString(_T("LicenceFile"),m_strLicenceFile);

}

// CMyApp ��Ϣ�������




void CAboutDlg::OnBnClickedLicense()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString	strFilter = L"Licence File|*.bin|All File|*.*||";
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST,strFilter);
	if(IDOK==dlg.DoModal())
	{
		CString oldLicFl=theApp.m_strLicenceFile;
		theApp.m_strLicenceFile =dlg.GetPathName();
		//���н��鿴�Ƿ�Ϊ��ȷ����Ȩ�ļ����������ѽ�����浽������
		bool oldStat=theApp.m_bLicense;
		theApp.m_bLicense=theApp.CheckLicence ();
		//���ע�᲻�ɹ��ָ�ԭ״
		if(!theApp.m_bLicense)theApp.m_strLicenceFile=oldLicFl;
		BOOL bValid;
		CString inf;
		bValid=inf.LoadString(theApp.m_bLicense?IDS_REGISTER_OK:IDS_REGISTER_FAIL);
		ASSERT(bValid);
		MessageBox(inf,0,MB_ICONINFORMATION|MB_OK);
		if(oldStat!=theApp.m_bLicense)
		{
			//������Ȩ��Ϣ��ʾ
			BOOL bValid;
			CString inf;
			bValid=inf.LoadString(theApp.m_bLicense?IDS_HAS_LICENCE:IDS_NO_LICENCE);
			ASSERT(bValid);
			this->SetDlgItemText(IDC_LICENSE_INFOR,inf);
		}

	}

}



void CAboutDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnClose();
	this->OnOK();
}

// ��Ȩ���֤����
bool CMyApp::CheckLicence(void)
{
	CLicense lic(CStringA(theApp.m_strLicenceFile),CStringA(CMyApp::s_strLicenceFlag));
	return lic.Check()==1;
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//����Ѿ�ע�ᣬ��ʾ������ע�����Ϣ��������ʾ��ע��������Ϣ
	BOOL bValid;
	CString inf;
	bValid=inf.LoadString(theApp.m_bLicense?IDS_HAS_LICENCE:IDS_NO_LICENCE);
	ASSERT(bValid);
	this->SetDlgItemText(IDC_LICENSE_INFOR,inf);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAboutDlg::OnBnClickedMachineId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_dlgHardwareInfor.GetSafeHwnd())
		m_dlgHardwareInfor.Create(m_dlgHardwareInfor.IDD,this);
	//�޸Ĵ��ڵĸ߶�
	CRect rc,rcInfor;
	this->GetWindowRect(&rc);
	m_dlgHardwareInfor.GetWindowRect(&rcInfor);
	BOOL bShow=m_dlgHardwareInfor.IsWindowVisible();
	UINT show=(bShow?SW_HIDE:SW_SHOW);
	CPoint pt(rc.left,rc.bottom);
	ScreenToClient(&pt);
	rc.bottom=bShow?rc.bottom-rcInfor.Height():rc.bottom+rcInfor.Height();
	this->MoveWindow(&rc);
	m_dlgHardwareInfor.MoveWindow(pt.x,pt.y,rc.Width(),rcInfor.Height());
	m_dlgHardwareInfor.ShowWindow(show);
	//��ǰ���ɼ�������ʾ��ʶ���ڣ�ȡ�����Ա�ʶ�������ı�����
	if(!bShow)
	{
		CLicense lic;
		m_dlgHardwareInfor.m_strComputerID=lic.GetComputerID();
		m_dlgHardwareInfor.UpdateData(0);
	}
}
