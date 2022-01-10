// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// 练字工具.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "练字工具.h"
#include "MainFrm.h"

#include "练字工具Doc.h"
#include "练字工具View.h"
#include "license.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMyApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CMyApp 构造
const CString CMyApp::s_strLicenceFlag=L"Copybook";
CMyApp::CMyApp()
: m_bLicense(false)
, m_strLicenceFile(_T(""))
{

	m_bHiColorIcons = TRUE;
	
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CMyApp 对象

CMyApp theApp;


// CMyApp 初始化

BOOL CMyApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//若为英文版改为CalligraphyCopy
	SetRegistryKey(_T("HCHQ"));
	LoadStdProfileSettings(16);  // 加载标准 INI 文件选项

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMyView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	//发送消息，以完成初始化任务窗格的操作
	m_pMainWnd->PostMessage(WM_SHOWWINDOW,1);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CHardwareInfor m_dlgHardwareInfor;
// 实现
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

// 用于运行对话框的应用程序命令
void CMyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMyApp 自定义加载/保存方法

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

// CMyApp 消息处理程序




void CAboutDlg::OnBnClickedLicense()
{
	// TODO: 在此添加控件通知处理程序代码
	CString	strFilter = L"Licence File|*.bin|All File|*.*||";
	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST,strFilter);
	if(IDOK==dlg.DoModal())
	{
		CString oldLicFl=theApp.m_strLicenceFile;
		theApp.m_strLicenceFile =dlg.GetPathName();
		//进行较验看是否为正确的授权文件，并将较难结果保存到变量中
		bool oldStat=theApp.m_bLicense;
		theApp.m_bLicense=theApp.CheckLicence ();
		//如果注册不成功恢复原状
		if(!theApp.m_bLicense)theApp.m_strLicenceFile=oldLicFl;
		BOOL bValid;
		CString inf;
		bValid=inf.LoadString(theApp.m_bLicense?IDS_REGISTER_OK:IDS_REGISTER_FAIL);
		ASSERT(bValid);
		MessageBox(inf,0,MB_ICONINFORMATION|MB_OK);
		if(oldStat!=theApp.m_bLicense)
		{
			//更改授权信息显示
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();
	this->OnOK();
}

// 授权许可证较验
bool CMyApp::CheckLicence(void)
{
	CLicense lic(CStringA(theApp.m_strLicenceFile),CStringA(CMyApp::s_strLicenceFlag));
	return lic.Check()==1;
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//如果已经注册，显示的是已注册的信息，否则显示需注册的相关信息
	BOOL bValid;
	CString inf;
	bValid=inf.LoadString(theApp.m_bLicense?IDS_HAS_LICENCE:IDS_NO_LICENCE);
	ASSERT(bValid);
	this->SetDlgItemText(IDC_LICENSE_INFOR,inf);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAboutDlg::OnBnClickedMachineId()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_dlgHardwareInfor.GetSafeHwnd())
		m_dlgHardwareInfor.Create(m_dlgHardwareInfor.IDD,this);
	//修改窗口的高度
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
	//当前不可见，将显示标识窗口，取出电脑标识，赋予文本框中
	if(!bShow)
	{
		CLicense lic;
		m_dlgHardwareInfor.m_strComputerID=lic.GetComputerID();
		m_dlgHardwareInfor.UpdateData(0);
	}
}
