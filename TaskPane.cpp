#include "StdAfx.h"
#include "TaskPane.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPane

BEGIN_MESSAGE_MAP(CTaskPane, CMFCTasksPane)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPane construction/destruction

CTaskPane::CTaskPane()
: m_bSplitGrid(false)
{
	m_nDocumentsGroup = -1;
}

CTaskPane::~CTaskPane()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTaskPane message handlers

int CTaskPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;


	CString strTmp;
	BOOL bValid=strTmp.LoadString(IDS_TASKPANE_OPENFILE);
	ASSERT(bValid);

	HICON hIcon=	::LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_TASKPANE_OPENFILE));
	m_nDocumentsGroup = AddGroup (strTmp, FALSE, TRUE,hIcon);

	// Add MRU list:
	AddMRUFilesList (m_nDocumentsGroup,8);
	bValid=strTmp.LoadString(IDS_TASKPANE_MOREFILE);
	ASSERT(bValid);
	AddTask (m_nDocumentsGroup, strTmp, 0, ID_FILE_OPEN);

	bValid=strTmp.LoadString(IDS_TASKPANE_COPYBOOK);
	ASSERT(bValid);
	m_nSampleGroup = AddGroup (strTmp);

	//增加十等分字格  
	bValid=strTmp.LoadString(IDS_TASKPANE_GRIDSPLIT);
	ASSERT(bValid);
	this->AddTask(m_nSampleGroup,strTmp,0,ID_TASKPANE_GRID_SPLIT);

	if(this->CreateSampleWnd())
		this->AddWindow(m_nSampleGroup,m_wndSample.GetSafeHwnd(),400);
	return 0;
}

void CTaskPane::UpdateMRUFilesList ()
{
	AddMRUFilesList (m_nDocumentsGroup,8);
	RedrawWindow ();
}

//void CTaskPane::UpdateToolbar ()
//{
//	m_wndToolBar.RedrawWindow ();
//}

//BOOL CTaskPane::CreateTreeControl()
//{
//	CRect rectDummy (0, 0, 0, 0);
//	const DWORD dwTreeStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
//		TVS_LINESATROOT | TVS_HASBUTTONS;
//
//	if(!m_wndTree.Create (dwTreeStyle, rectDummy, this, (UINT)-1))
//	{
//		TRACE0("Failed to create the custom window\n");
//		return FALSE;
//	}
//
//	m_wndTree.ModifyStyleEx (0, WS_EX_CLIENTEDGE);
//
//	HTREEITEM hRoot = m_wndTree.InsertItem (_T("Folders"));
//
//	m_wndTree.InsertItem (_T("Folder 1"), hRoot);
//	m_wndTree.InsertItem (_T("Folder 2"), hRoot);
//	m_wndTree.InsertItem (_T("Folder 3"), hRoot);
//	m_wndTree.InsertItem (_T("Folder 4"), hRoot);
//
//	m_wndTree.Expand (hRoot, TVE_EXPAND);
//
//	m_wndTree.RedrawWindow ();
//	return TRUE;
//}
//
BOOL CTaskPane::CreateSampleWnd()
{
	CRect rectDummy (0, 0, 0, 0);
	DWORD dwStyle = WS_CHILD | WS_VISIBLE|WS_BORDER /*|WS_HSCROLL|WS_VSCROLL*/;


	if (!m_wndSample.Create (NULL,NULL,dwStyle, rectDummy, this, (UINT)-1))
	{
		TRACE0("Failed to create the   window\n");
		return FALSE;
	}

	//m_wndSample.ModifyStyleEx (0, WS_EX_CLIENTEDGE);
	
	return TRUE;
}


void CTaskPane::OnShowWindow(BOOL bShow, UINT nStatus)
{
	//CMFCTasksPane::OnShowWindow(bShow, nStatus);		
	//修改其中的空白距离,以使预览空间大一些
	this->SetHorzMargin(0);
	this->SetVertMargin(0);
	this->SetGroupVertOffset (3);
	this->SetTasksIconVertOffset (3);
	this->SetTasksHorzOffset (3);	

	if(bShow)
	{
		CString strTmp;
		BOOL bValid=strTmp.LoadString(IDS_VIEW_TASK_PANE);
		ASSERT(bValid);
		this->SetWindowText(strTmp);

	}

	// TODO: 在此处添加消息处理程序代码
}

void CTaskPane::OnSize(UINT nType, int cx, int cy)
{

	CMFCTasksPane::OnSize(nType, cx, cy);
	CRect rcWnd;
	m_wndSample.GetWindowRect(&rcWnd);
	CRect rcPane;
	this->GetWindowRect(&rcPane);
	CMFCTasksPaneTaskGroup * pGrp=this->GetTaskGroup(m_nSampleGroup);	
	int space=rcPane.bottom-rcWnd.bottom-30;
	rcWnd.bottom+=space;	
	this->SetWindowHeight (m_nSampleGroup ,m_wndSample.GetSafeHwnd(),rcWnd.Height());

}


void CTaskPane::OnClickTask(int nGroupNumber, int nTaskNumber, UINT uiCommandID, DWORD dwUserData)
	{
		CMFCTasksPane::OnClickTask(nGroupNumber, nTaskNumber, uiCommandID, dwUserData);
		if(nGroupNumber==this->m_nDocumentsGroup)
		{
			this->CollapseGroup(m_nDocumentsGroup);
		}

		if(uiCommandID==ID_TASKPANE_GRID_SPLIT)
		{
			m_bSplitGrid=!m_bSplitGrid;
			//更新其文字标签消息
			CString strTmp;
			UINT strID=m_bSplitGrid?IDS_TASKPANE_GRIDSPLIT2:IDS_TASKPANE_GRIDSPLIT;
			BOOL bValid=strTmp.LoadString(strID);
			ASSERT(bValid);
			this->GetTask(m_nSampleGroup,nTaskNumber)->m_strName=strTmp;
			this->UpdateCaption();
			this->m_wndSample.Invalidate();
		}
	
	}