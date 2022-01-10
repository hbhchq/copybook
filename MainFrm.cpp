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

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "练字工具.h"
#include <math.h>

#include "MainFrm.h"
#include "mygallery.h"
#include "LineButton.h"
#include "LineColorButton.h"
#include "FontColorButton.h"
#include "CharStyleSample.h"
#include "Chardirectbutton.h"
#include "NumberEdit.h"
#include "MyLabelSlider.h"
#include "DrawImgPreview.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	////ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	////ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_CHAR_STYLE_FONT, &CMainFrame::OnSelCharStyleFont)
	ON_COMMAND(ID_CHAR_STYLE_HEIGHT, &CMainFrame::OnCharStyleHeight)
	//ON_COMMAND(ID_CHAR_STYLE_WEIGHT, &CMainFrame::OnCharStyleWeight)
	//ON_UPDATE_COMMAND_UI(ID_CHAR_STYLE_WEIGHT, &CMainFrame::OnUpdateCharStyleWeight)
	
	ON_COMMAND(ID_CHAR_STYLE_WEIGHT, &CMainFrame::OnCharStyleWeight)
	ON_UPDATE_COMMAND_UI(ID_CHAR_STYLE_WEIGHT, &CMainFrame::OnUpdateCharStyleWeight)
	ON_COMMAND(ID_GRID_CATEGORY, &CMainFrame::OnGridCategory)
	//ON_COMMAND(ID_LINE_STYLE, &CMainFrame::OnGridLineStyle)
	ON_COMMAND_RANGE(ID_LINE_STYLE,ID_LINE_STYLE8,&CMainFrame::OnGridLineStyle)
	ON_COMMAND(ID_LINE_COLOR, &CMainFrame::OnGridLineColor)
	ON_COMMAND(ID_GRID_SIZE, &CMainFrame::OnGridSize)
	ON_COMMAND(ID_GRID_ROWSPACE, &CMainFrame::OnRowSpace)
	ON_COMMAND(ID_GRID_COLSPACE, &CMainFrame::OnColSpace)
	ON_COMMAND(ID_FONT_COLOR, &CMainFrame::OnFontColor)
	ON_COMMAND(ID_FONT_HOLLOW, &CMainFrame::OnFontHollow)

	ON_COMMAND(ID_FONT_SOLID, &CMainFrame::OnFontHollowSolid)
	ON_UPDATE_COMMAND_UI(ID_FONT_SOLID, &CMainFrame::OnUpdateFontHollowSolid)
	ON_UPDATE_COMMAND_UI(ID_FONT_HOLLOW, &CMainFrame::OnUpdateFontHollow)
	ON_COMMAND_RANGE(ID_CHAR_DIRECT,ID_CHAR_DIRECT4, &CMainFrame::OnCharDirect)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CHAR_DIRECT1,ID_CHAR_DIRECT4, &CMainFrame::OnUpdateCharDirectRange)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LINE_STYLE1,ID_LINE_STYLE8, &CMainFrame::OnUpdateLineStyleRange)

	ON_COMMAND(ID_PAGE_MARGIN_TOP, &CMainFrame::OnPageMarginTop)
	ON_COMMAND(ID_PAGE_MARGIN_BOTTOM, &CMainFrame::OnPageMarginBottom)
	ON_COMMAND(ID_PAGE_MARGIN_LEFT, &CMainFrame::OnPageMarginLeft)
	ON_COMMAND(ID_PAGE_MARGIN_RIGHT, &CMainFrame::OnPageMarginRight)
	ON_COMMAND(ID_CENTER_H, &CMainFrame::OnPageCenterH)
	ON_COMMAND(ID_CENTER_V, &CMainFrame::OnPageCenterV)
	ON_UPDATE_COMMAND_UI(ID_CENTER_H, &CMainFrame::OnUpdatePageCenterH)
	ON_UPDATE_COMMAND_UI(ID_CENTER_V, &CMainFrame::OnUpdatePageCenterV)
	ON_COMMAND(ID_PAPER_LANDSCAPE, &CMainFrame::OnPaperLandscape)
	ON_COMMAND(ID_PAPER_PORTRAIT, &CMainFrame::OnPaperPortrait)
	ON_UPDATE_COMMAND_UI(ID_PAPER_PORTRAIT, &CMainFrame::OnUpdatePaperPortrait)
	ON_UPDATE_COMMAND_UI(ID_PAPER_LANDSCAPE, &CMainFrame::OnUpdatePaperLandscape)
	ON_COMMAND(ID_CHAR_OFFSETY, &CMainFrame::OnCharOffsetY)
	ON_COMMAND(ID_HUI_IN_OUT_RATE, &CMainFrame::OnHuiInOutRate)
	ON_COMMAND(ID_HUI_W_H_RATE, &CMainFrame::OnHuiWHRate)
	ON_COMMAND(ID_HUI_OFFSETY, &CMainFrame::OnHuiOffsetY)
//	ON_UPDATE_COMMAND_UI(ID_HUI_IN_OUT_RATE, &CMainFrame::OnUpdateHuiInOutRate)
//	ON_UPDATE_COMMAND_UI(ID_HUI_W_H_RATE, &CMainFrame::OnUpdateHuiWHRate)
//	ON_UPDATE_COMMAND_UI(ID_HUI_OFFSETY, &CMainFrame::OnUpdateHuiOffsetY)
//	ON_UPDATE_COMMAND_UI(ID_CHAR_OFFSETY, &CMainFrame::OnUpdateCharOffsetY)
ON_COMMAND(ID_VIEW_TASKPANE, &CMainFrame::OnViewTaskpane)
ON_UPDATE_COMMAND_UI(ID_VIEW_TASKPANE, &CMainFrame::OnUpdateViewTaskpane)

ON_WM_SHOWWINDOW()
ON_COMMAND(ID_OWNERDRAWGRID, &CMainFrame::OnOwnerDrawGrid)
ON_UPDATE_COMMAND_UI(ID_OWNERDRAWGRID, &CMainFrame::OnUpdateOwnerDrawGrid)
ON_COMMAND(ID_OPENDRAWIMG, &CMainFrame::OnOpenImg)
ON_COMMAND(ID_EDITIMG, &CMainFrame::OnEditImg)
ON_COMMAND(ID_SAVEDRAWIMG, &CMainFrame::OnSaveImg)
ON_UPDATE_COMMAND_UI(ID_SAVEDRAWIMG, &CMainFrame::OnUpdateSaveImg)
ON_COMMAND(ID_OWNERDRAWPREVIEW, &CMainFrame::OnOwnerDrawPreview)
//ON_UPDATE_COMMAND_UI(ID_OWNERDRAWPREVIEW, &CMainFrame::OnUpdateOwnerdrawpreview)
ON_COMMAND(ID_BACKGROUND, &CMainFrame::OnOwnerDrawBackground)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
: m_bRecalcPage(FALSE)
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//////初台化页面设置时的计量单位，统一为100分之1毫米
	////m_dlgPageSet.m_psd .Flags|=PSD_DISABLEPAPER|PSD_INHUNDREDTHSOFMILLIMETERS;
	//////上下左右各两厘米，即2000单位
	////m_dlgPageSet.m_psd.rtMargin=CRect(2000,2000,2000,2000);
	this->LoadSetting();

	
}

CMainFrame::~CMainFrame()
{
	this->SaveSetting();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	////bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	////ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUS_PANE, strTitlePane1, TRUE), strTitlePane1);
	////m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	//EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 导航窗格将创建在左侧，因此将暂时禁用左侧的停靠:
	//EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);


	if (!CreateTaskPane ())
	{
		TRACE0("Failed to create tasks pane\n");
		return -1;      // fail to create
	}

	// 已创建 Outlook 栏，应允许在左侧停靠。
	m_wndTaskPane.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
	DockPane(&m_wndTaskPane);
	EnableDocking(CBRS_ALIGN_ANY/*CBRS_ALIGN_LEFT*/);
	EnableAutoHidePanes(CBRS_ALIGN_ANY);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// 初始主按钮:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, strTemp, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, strTemp, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, strTemp, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, strTemp, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));
	
	/////////////////////////////////////////////////////////////
	//自定义的设置类别项
	AddGridStyle();
	//增加回字格相应的设置项
	AddHUIGridStyle();
	AddOwnerDrawPage();
	AddCharStyle();
	AddPageLayout();
	//使所有的面板中元素均垂直居中
	for(int n=0;n<this->m_wndRibbonBar.GetCategoryCount();n++)
	{
		CMFCRibbonCategory * cate=m_wndRibbonBar.GetCategory(n);
		for(int i=0;i<cate->GetPanelCount();i++)
		{
			cate->GetPanel(i)->SetJustifyColumns();
			cate->GetPanel(i)->SetCenterColumnVert();
		}
	}
	/////////////////////////////////////
	//////////////////////////////////////////////////////////

	// 为“剪贴板”面板添加“主”类别:
	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// 创建“剪贴板”面板:
	bNameValid = strTemp.LoadString(IDS_RIBBON_CLIPBOARD);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelClipboard = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PASTE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPaste = new CMFCRibbonButton(ID_EDIT_PASTE, strTemp, 0, 0);
	pPanelClipboard->Add(pBtnPaste);

	bNameValid = strTemp.LoadString(IDS_RIBBON_CUT);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_CUT, strTemp, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_COPY);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_COPY, strTemp, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SELECTALL);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_SELECT_ALL, strTemp, -1));

	// 创建和添加“视图”面板:
	bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));

	bNameValid = strTemp.LoadString(IDS_RIBBON_STATUSBAR);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnStatusBar = new CMFCRibbonCheckBox(ID_VIEW_STATUS_BAR, strTemp);
	pPanelView->Add(pBtnStatusBar);
	////bNameValid = strTemp.LoadString(IDS_RIBBON_CAPTIONBAR);
	////ASSERT(bNameValid);
	////CMFCRibbonButton* pBtnCaptionBar = new CMFCRibbonCheckBox(ID_VIEW_CAPTION_BAR, strTemp);
	////pPanelView->Add(pBtnCaptionBar);
//任务栏切换按钮
	bNameValid = strTemp.LoadString(IDS_VIEW_TASK_PANE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnTaskpane = new CMFCRibbonCheckBox(ID_VIEW_TASKPANE, strTemp);
	pPanelView->Add(pBtnTaskpane);


	////// 将元素添加到选项卡右侧:
	//////增加语言切换选项
	////bNameValid = strTemp.LoadString(IDS_LANGUAGE);
	////ASSERT(bNameValid);
	////CMFCRibbonButton* pLangButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	////pLangButton->SetMenu(IDR_LANGUAGE, FALSE /* 无默认命令*/, TRUE /* 右对齐*/);
	////m_wndRibbonBar.AddToTabs(pLangButton);
//////////////////////
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* 无默认命令*/, TRUE /* 右对齐*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// 添加快速访问工具栏命令:
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_PREVIEW);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);

	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));

}

//BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
//{
//	CWindowDC dc(NULL);
//
//	bar.SetMode2003();
//
//	BOOL bNameValid;
//	CString strTemp;
//	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
//	ASSERT(bNameValid);
//	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
//	{
//		return FALSE; // 未能创建
//	}
//
//	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();
//
//	if (pOutlookBar == NULL)
//	{
//		ASSERT(FALSE);
//		return FALSE;
//	}
//
//	pOutlookBar->EnableInPlaceEdit(TRUE);
//
//	static UINT uiPageID = 1;
//
//	DWORD dwPaneStyle = AFX_DEFAULT_TOOLBAR_STYLE | CBRS_FLOAT_MULTI;
//
//	// 可浮动，可自动隐藏，可调整大小，但不能关闭
//	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;
//
//	CRect rectDummy(0, 0, 0, 0);
//	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
//
//	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
//	bNameValid = strTemp.LoadString(IDS_FOLDERS);
//	ASSERT(bNameValid);
//	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);
//
//	calendar.Create(rectDummy, &bar, 1201);
//	bNameValid = strTemp.LoadString(IDS_CALENDAR);
//	ASSERT(bNameValid);
//	pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);
//
//	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
//
//	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
//	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
//	pOutlookBar->RecalcLayout();
//
//	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
//	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);
//
//	bar.SetButtonsFont(&afxGlobalData.fontBold);
//
//	return TRUE;
//}
//
//BOOL CMainFrame::CreateCaptionBar()
//{
//	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
//	{
//		TRACE0("未能创建标题栏\n");
//		return FALSE;
//	}
//
//	BOOL bNameValid;
//
//	CString strTemp, strTemp2;
//	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
//	ASSERT(bNameValid);
//	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
//	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
//	ASSERT(bNameValid);
//	m_wndCaptionBar.SetButtonToolTip(strTemp);
//
//	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
//	ASSERT(bNameValid);
//	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);
//
//	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
//	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
//	ASSERT(bNameValid);
//	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
//	ASSERT(bNameValid);
//	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);
//
//	return TRUE;
//}
//
//
//
BOOL CMainFrame::CreateTaskPane ()
{
	CRect rectDummy(0, 0, 300, 700);
	if (!m_wndTaskPane.Create(_T("task pane"), this, rectDummy, TRUE, ID_VIEW_TASKPANE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | AFX_CBRS_CLOSE | AFX_CBRS_FLOAT))
	{
		TRACE0("Failed to create task pane\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{	


	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	//设置图像透明色,主要是ribbon的绘制都是以按钮表面色为透明色的，统一改为白色
	afxGlobalData.clrBtnFace=RGB(255,255,255);
	////////////////////////////////////////////////

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);

			

}

//void CMainFrame::OnViewCaptionBar()
//{
//	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
//	RecalcLayout(FALSE);
//}

//void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
//{
//	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
//}

void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

// 增加格子框线的样式
void CMainFrame::AddGridStyle(void)
{
// 增加格子样式类别:
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_GRID_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pGridStyle = m_wndRibbonBar.AddCategory(strTemp, IDB_GRID_STYLE_SMALL, IDB_GRID_STYLE,CSize(16,16),CSize(48,48));
	//// 创建“格子类型”面板:
	bNameValid = strTemp.LoadString(IDS_GRID_CATEGORY);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanel = pGridStyle->AddPanel(strTemp);
	

	CMFCRibbonGallery *gal=new CMyGallery(ID_GRID_CATEGORY, strTemp, 0, 0, IDB_GRID_CATEGORY2,64);
	gal->SetAlwaysLargeImage();
	gal->SetIconsInRow(5);
	////gal->SetButtonMode();
	pPanel->Add(gal);
	gal->SelectItem(m_gridStyle.m_category);
	//增加自绘格子的复选标志
	bNameValid = strTemp.LoadString(IDS_OWNERDRAW);
	ASSERT(bNameValid);
	CMFCRibbonButton * pDraw=new CMFCRibbonButton(ID_OWNERDRAWGRID,strTemp,2,2);
	pPanel->Add (pDraw);
	pDraw->SetTextAlwaysOnRight();
	////////////////
	//增加线条面板
	bNameValid = strTemp.LoadString(IDS_GRID_LINE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pLinePanel = pGridStyle->AddPanel(strTemp);
	//线条颜色
	CLineColorButton * btnColor=new CLineColorButton(
		ID_LINE_COLOR);
	bNameValid = strTemp.LoadString(IDS_OTHERCOLOR);
	ASSERT(bNameValid);	
	btnColor->EnableOtherButton(strTemp);
	btnColor->SetAlwaysLargeImage();
	btnColor->SetImageIndex(1,FALSE);	
	btnColor->SetColor(m_gridStyle.m_color);
	pLinePanel->Add(btnColor);


	//线条型式
	COLORREF lineColor=m_gridStyle.m_color;
	CLineButton  * btnLine=new CLineButton(ID_LINE_STYLE,m_gridStyle.m_lineType,1,lineColor);
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE1,PS_SOLID,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE2,PS_DASH,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE3,PS_DOT,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE4,PS_DASHDOT,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE5,PS_DASHDOTDOT,1,lineColor,btnLine));
	btnLine->SetAlwaysLargeImage();
	pLinePanel->Add(btnLine);
	//增加格子大小大小,界面显示以MM为单位
	bNameValid = strTemp.LoadString(IDS_GRID_SIZE_SPACE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pSizePanel = pGridStyle->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_GRID_SIZE);
	ASSERT(bNameValid);
	CNumberEdit* gridSize = new CNumberEdit(ID_GRID_SIZE, 40, strTemp, -1);
	//默认8,从1到13毫米高，根据网格自动调整,不超过格子大小
	gridSize->EnableSpinButtons(1, 50);
	CSize szPaper=this->GetPaperSize();
	CRect rcMargin=this->GetPageMargin();
	gridSize->SetMinMax(1,min(szPaper.cx-rcMargin.left/100-rcMargin.right/100
		,szPaper.cy-rcMargin.top/100-rcMargin.bottom/100));
	char sz[10]={0};
	itoa(m_gridStyle.m_cellLength/100,sz,10);
	//gridSize->SetEditText(_T("13"));	
	gridSize->SetEditText(CString(sz));
	pSizePanel->Add(gridSize);	
	//增加格子间隔距离,界面显示以0.1MM为单位
	bNameValid = strTemp.LoadString(IDS_GRID_ROWSPACE);
	ASSERT(bNameValid);
	CNumberEdit* rowS = new CNumberEdit(ID_GRID_ROWSPACE, 40, strTemp, -1);
	rowS->EnableSpinButtons(0, 100);
	rowS->SetMinMax(0,szPaper.cy*10);
	char sz2[10]={0};
	itoa(m_gridStyle.m_rowSpace/10,sz2,10);
	rowS->SetEditText(CString(sz2));
	pSizePanel->Add(rowS);	

	bNameValid = strTemp.LoadString(IDS_GRID_COLSPACE);
	ASSERT(bNameValid);
	CNumberEdit* colS = new CNumberEdit(ID_GRID_COLSPACE, 40, strTemp, -1);
	colS->EnableSpinButtons(0, 100);
	colS->SetMinMax(0,szPaper.cx*10);

	char sz3[10]={0};
	itoa(m_gridStyle.m_colSpace/10,sz3,10);
	colS->SetEditText(CString(sz3));
	pSizePanel->Add(colS);


}

// 增加文字格式
void CMainFrame::AddCharStyle(void)
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_CHAR_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCharStyle = m_wndRibbonBar.AddCategory(strTemp, IDB_CHAR_STYLE, IDB_WRITELARGE);
	//// 创建“字体选择框
	bNameValid = strTemp.LoadString(IDS_CHAR_STYLE_FONT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanel = pCharStyle->AddPanel(strTemp);
	CMFCRibbonFontComboBox* fontSel = new CMFCRibbonFontComboBox(ID_CHAR_STYLE_FONT);
	fontSel->SetFont(m_charStyle.m_fontName);
	bNameValid = strTemp.LoadString(IDS_FONT_NAME);
	ASSERT(bNameValid);
	fontSel->SetText(strTemp);
	fontSel->m_bDrawUsingFont=TRUE;
	pPanel->Add(fontSel);
	//创建字体大小选择
	bNameValid = strTemp.LoadString(IDS_FONT_HEIGTH);
	ASSERT(bNameValid);
	CNumberEdit* fontHei = new CNumberEdit(ID_CHAR_STYLE_HEIGHT, 40, strTemp, -1);
	//默认8,从1到13毫米高，根据网格自动调整,不超过格子大小
	fontHei->EnableSpinButtons(1, 13);
	fontHei->SetMinMax(1,m_gridStyle.m_cellLength/100);
	char sz[10]={0};
	itoa(m_charStyle.m_charHeight/100,sz,10);
	fontHei->SetEditText(CString(sz));
	pPanel->Add(fontHei);
	pPanel->Add(new CMFCRibbonSeparator());
	//字体的粗细
	bNameValid = strTemp.LoadString(IDS_FONT_BOLD);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox *bold=new CMFCRibbonCheckBox(ID_CHAR_STYLE_WEIGHT,strTemp);
	pPanel->Add(bold);
	//文字颜色
	bNameValid = strTemp.LoadString(IDS_FONT_COLOR);
	ASSERT(bNameValid);
	CMFCRibbonColorButton *fontColor=new CFontColorButton(ID_FONT_COLOR,strTemp);
	fontColor->SetColor(m_charStyle.m_color);

	bNameValid = strTemp.LoadString(IDS_OTHERCOLOR);
	ASSERT(bNameValid);	
	fontColor->EnableOtherButton(strTemp);

	pPanel->Add(fontColor);

	pPanel->Add(new CMFCRibbonSeparator());

		//是否空心文字
	bNameValid = strTemp.LoadString(IDS_FONT_HOLLOW);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox *fontHollow=new CMFCRibbonCheckBox(ID_FONT_HOLLOW,strTemp);
	pPanel->Add(fontHollow);	

	//若为空心字，则是否为实线
	bNameValid = strTemp.LoadString(IDS_FONT_SOLID);
	ASSERT(bNameValid);
	CMFCRibbonButton *solid=new CMFCRibbonCheckBox(ID_FONT_SOLID,strTemp);
	pPanel->Add(solid);

	//文字偏移
		pPanel->Add(new CMFCRibbonSeparator());
	bNameValid = strTemp.LoadString(IDS_CHAR_OFFSETY);
	ASSERT(bNameValid);
	CMyLabelSlider * sld=new CMyLabelSlider(ID_CHAR_OFFSETY,strTemp,200);
	sld->SetRange(-m_gridStyle.m_cellLength/20,m_gridStyle.m_cellLength/20);
	int pos=m_charStyle.m_bDownward?m_charStyle.m_offsetY:-m_charStyle.m_offsetY;
	sld->SetPos(pos);
	pPanel->Add(sld);

	//增加字例显示面板
	bNameValid = strTemp.LoadString(IDS_FONT_PREVIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pSamplePanel = pCharStyle->AddPanel(strTemp);
	bNameValid = strTemp.LoadString(IDS_CHAR_SAMPLE);
	ASSERT(bNameValid);

	CCharStyleSample *pSampChar=new CCharStyleSample(strTemp,m_charStyle.m_bHollow
		,m_charStyle.m_color,CSize(80,80),m_charStyle.m_bSolid
		,m_charStyle.m_fontName,m_charStyle.m_weight);
	////bNameValid = strTemp.LoadString(IDS_CHAR_SAMPLE_DES);
	////ASSERT(bNameValid);
	////pSampChar->SetDescription(strTemp);
	pSampChar->SetID(IDS_CHAR_SAMPLE+50000);
	pSamplePanel->Add(pSampChar);
}

//增加页面布局，即页边距，文字方向，居中等
void CMainFrame::AddPageLayout(void )
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_PAGE_LAYOUT);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pPageLayout = m_wndRibbonBar.AddCategory(strTemp, IDB_PAGELAYOUT_SMALL/*IDB_WRITESMALL*/, IDB_PAGE_LAYOUT,CSize(16,16),CSize(36,48));
	//页边距面板
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPage=pPageLayout->AddPanel(strTemp);
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN_TOP);
	ASSERT(bNameValid);
	CNumberEdit* top = new /*CNumberEdit*/
		CNumberEdit(ID_PAGE_MARGIN_TOP, 40, strTemp);
	top->EnableSpinButtons(0, 50);
	CSize szPaper=this->GetPaperSize();
	top->SetMinMax(0,szPaper.cy);
	char cTop[10]={0};
	itoa(m_pageLayout.m_top/100,cTop,10);
	top->SetEditText(CString(cTop));
	pPage->Add(top);
	//下部
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN_BOTTOM);
	ASSERT(bNameValid);
	CNumberEdit* BOTTOM = new CNumberEdit(ID_PAGE_MARGIN_BOTTOM, 40, strTemp, -1);
	BOTTOM->EnableSpinButtons(0, 50);
	BOTTOM->SetMinMax(0,szPaper.cy);

	char cBOTTOM[10]={0};
	itoa(m_pageLayout.m_bottom/100,cBOTTOM,10);
	BOTTOM->SetEditText(CString(cBOTTOM));
	pPage->Add(BOTTOM);
	pPage->AddSeparator();
		//左部
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN_LEFT);
	ASSERT(bNameValid);
	CNumberEdit* LEFT = new CNumberEdit(ID_PAGE_MARGIN_LEFT, 40, strTemp, -1);
	LEFT->EnableSpinButtons(0, 50);
	LEFT->SetMinMax(0,szPaper.cx);
	char cLEFT[10]={0};
	itoa(m_pageLayout.m_left/100,cLEFT,10);
	LEFT->SetEditText(CString(cLEFT));
	pPage->Add(LEFT);
		//右部
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN_RIGHT);
	ASSERT(bNameValid);
	CNumberEdit* RIGHT = new CNumberEdit(ID_PAGE_MARGIN_RIGHT, 40, strTemp, -1);
	RIGHT->EnableSpinButtons(0, 50);
	RIGHT->SetMinMax(0,szPaper.cx);
	char cRIGHT[10]={0};
	itoa(m_pageLayout.m_right/100,cRIGHT,10);
	RIGHT->SetEditText(CString(cRIGHT));
	pPage->Add(RIGHT);
	//水平，垂直居中
	bNameValid = strTemp.LoadString(IDS_PAGE_CENTER);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pCenter=pPageLayout->AddPanel(strTemp);
	//水平居中
	bNameValid = strTemp.LoadString(IDS_PAGE_CENTER_HORZ);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox * pHCenter= new CMFCRibbonCheckBox(ID_CENTER_H,strTemp);
	pCenter->Add(pHCenter);
	//垂直居中
	bNameValid = strTemp.LoadString(IDS_PAGE_CENTER_VERT);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox * pVCenter= new CMFCRibbonCheckBox(ID_CENTER_V,strTemp);
	pCenter->Add(pVCenter);
	//纸张方向
	bNameValid = strTemp.LoadString(IDS_PAPER_ORIENT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPaper = pPageLayout->AddPanel(strTemp);
	//
	bNameValid = strTemp.LoadString(IDS_PAPER_PORTRAIT);
	ASSERT(bNameValid);
	//使用文字方向按钮，以使其可以绘出小图标
	CCharDirectButton * portr=new CCharDirectButton/*CMFCRibbonButton*/(ID_PAPER_PORTRAIT,strTemp,5,5);
	//portr->SetAlwaysLargeImage();
	portr->SetTextAlwaysOnRight();
	portr->SetLargeImgMargin(5,5);
	portr->EnableOwnerFrame(0);
	pPaper->Add(portr);
	bNameValid = strTemp.LoadString(IDS_PAPER_LANDSCAPE);
	ASSERT(bNameValid);
	CCharDirectButton * lands=new CCharDirectButton/*CMFCRibbonButton*/(ID_PAPER_LANDSCAPE,strTemp,6,6);
	//lands->SetAlwaysLargeImage();
	lands->SetTextAlwaysOnRight();
	lands->SetLargeImgMargin(0,12);
	lands->EnableOwnerFrame(0);
	pPaper->Add(lands);
	//////////////////////文字方向面板
	bNameValid = strTemp.LoadString(IDS_CHAR_DIRECT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pDirectPanel = pPageLayout->AddPanel(strTemp);
	bNameValid = strTemp.LoadString(IDS_CHAR_DIRECT);
	ASSERT(bNameValid);
	CMFCRibbonButton * btnDir=(CMFCRibbonButton *) new /*CMFCRibbonButton*/CCharDirectButton(ID_CHAR_DIRECT,strTemp,0,0,1);
	bNameValid = strTemp.LoadString(IDS_CHAR_DIRECT1);
	ASSERT(bNameValid);
	btnDir->AddSubItem(new CCharDirectButton(ID_CHAR_DIRECT1,strTemp,1,1,1));
	bNameValid = strTemp.LoadString(IDS_CHAR_DIRECT2);
	ASSERT(bNameValid);
	btnDir->AddSubItem(new CCharDirectButton(ID_CHAR_DIRECT2,strTemp,2,2,1));
	bNameValid = strTemp.LoadString(IDS_CHAR_DIRECT3);
	ASSERT(bNameValid);
	btnDir->AddSubItem(new CCharDirectButton(ID_CHAR_DIRECT3,strTemp,3,3,1));
	bNameValid = strTemp.LoadString(IDS_CHAR_DIRECT4);
	ASSERT(bNameValid);
	btnDir->AddSubItem(new CCharDirectButton(ID_CHAR_DIRECT4,strTemp,4,4,1));
	btnDir->SetDefaultCommand(0);
	btnDir->SetTextAlwaysOnRight();
	btnDir->SetDefaultMenuLook();
	pDirectPanel->Add(btnDir);
	

}

void CMainFrame::AddHUIGridStyle()
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_HUI_GRID_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pHGrid = m_wndRibbonBar.AddContextCategory(strTemp,strTemp,IDS_HUI_GRID_STYLE,AFX_CategoryColor_Orange, IDB_GRID_HUI_STYLE_SMALL, IDB_GRID_HUI_STYLE,CSize(16,16),CSize(32,32));
	if(m_gridStyle.m_category==GRIDCATEGORY::HUI
		||m_gridStyle.m_category==GRIDCATEGORY::MI_HUI
		||m_gridStyle.m_category==GRIDCATEGORY::TIAN_HUI
		)
		m_wndRibbonBar.ShowContextCategories(IDS_HUI_GRID_STYLE);

	CMFCRibbonPanel *pan= pHGrid->AddPanel(strTemp);
	bNameValid = strTemp.LoadString(IDS_HUI_IN_OUT_RATE);
	ASSERT(bNameValid);
	//内外比率
	CMFCRibbonSlider *pOutRat=new CMyLabelSlider(ID_HUI_IN_OUT_RATE,strTemp,300);
	pOutRat->SetRange(0,100);
	pOutRat->SetPos(m_gridStyle.m_HUI_Rate);
	pan->Add(pOutRat);
	//宽高比例
	bNameValid = strTemp.LoadString(IDS_HUI_W_H_RATE);
	ASSERT(bNameValid);
	CMFCRibbonSlider *pWHRat=new CMyLabelSlider(ID_HUI_W_H_RATE,strTemp,300);
	pWHRat->SetRange(0,1000);
	pWHRat->SetPos(m_gridStyle.m_HUI_Rate_W_H);
	pan->Add(pWHRat);
	//偏移距离
	bNameValid = strTemp.LoadString(IDS_HUI_OFFSETY);
	ASSERT(bNameValid);
	CMFCRibbonSlider *pY=new CMyLabelSlider(ID_HUI_OFFSETY,strTemp,300);
	int gridSize=m_gridStyle.m_cellLength;
	pY->SetRange(-gridSize/20,gridSize/20);
	pY->SetPos(m_gridStyle.m_bDownward ?m_gridStyle.m_offsetY:-m_gridStyle.m_offsetY);
	pan->Add(pY);

}

void CMainFrame::AddOwnerDrawPage()
{	
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_OWNERDRAWGRID);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pPage = m_wndRibbonBar.AddContextCategory(strTemp,strTemp,IDS_OWNERDRAWGRID,AFX_CategoryColor_Green, IDB_BACKCOLOR_SMALL, IDB_BACKCOLOR,CSize(16,16),CSize(32,32));
	if(m_gridStyle.m_bOwnerDraw)
		m_wndRibbonBar.ShowContextCategories(IDS_OWNERDRAWGRID);
	CMFCRibbonPanel *pan= pPage->AddPanel(strTemp);
	//增加预览元素
	CDrawImgPreview * pView=new CDrawImgPreview(ID_OWNERDRAWPREVIEW);
	if(m_gridStyle.m_bOwnerDraw)
		pView->SetImage(m_gridStyle.m_strDrawFile);
	pan->Add(pView);
	pan->AddSeparator();
	//增加打开，编辑，保存按钮
	bNameValid = strTemp.LoadString(IDS_EDITGRIDIMG);
	ASSERT(bNameValid);
	pan->Add(new CMFCRibbonButton(ID_EDITIMG,strTemp));

	bNameValid = strTemp.LoadString(IDS_SAVEGRIDIMG);
	ASSERT(bNameValid);
	pan->Add(new CMFCRibbonButton(ID_SAVEDRAWIMG,strTemp));
	//打开图像文件，
	bNameValid = strTemp.LoadString(IDS_OPENGRIDIMG);
	ASSERT(bNameValid);
	pan->Add(new CMFCRibbonButton(ID_OPENDRAWIMG,strTemp));
	//pan->AddSeparator();
	//透明色的选择
	bNameValid = strTemp.LoadString(IDS_SELECTBACKGROUND);
	ASSERT(bNameValid);
	CMFCRibbonPanel *pan2= pPage->AddPanel(strTemp);

	CMFCRibbonColorButton *pClrBtn=new CMFCRibbonColorButton(ID_BACKGROUND,strTemp,FALSE,0,0);
	bNameValid = strTemp.LoadString(IDS_NOBACKCOLOR);
	ASSERT(bNameValid);
	pClrBtn->EnableAutomaticButton(strTemp, (COLORREF)-1, TRUE, NULL, FALSE /* Bottom */);
	
	bNameValid = strTemp.LoadString(IDS_OTHERCOLOR);
	ASSERT(bNameValid);	
	pClrBtn->EnableOtherButton(strTemp);
	//pClrBtn->SetColumns(10);
	pClrBtn->SetColor(m_gridStyle.m_clrBackgroud);
	//pClrBtn->SetButtonMode(FALSE);
	pClrBtn->SetDefaultCommand(FALSE);
	pan2->Add(pClrBtn);
}

////void CMainFrame::OnFilePageSetup()
////{
////	// TODO: 在此添加命令处理程序代码
////	PRINTDLG pd;
////	 pd.lStructSize = (DWORD)sizeof(PRINTDLG);
////	 BOOL bRet = theApp.GetPrinterDeviceDefaults(&pd);
////	 if(bRet)
////	 {
////	    // protect memory handle with ::GlobalLock and ::GlobalUnlock
////	    DEVMODE FAR *pDevMode = (DEVMODE FAR *)::GlobalLock(pd.hDevMode);
////	    // set orientation to landscape
////	    pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
////
////	HDC dc= AfxCreateDC(pd.hDevNames,pd.hDevMode);
////	int w=::GetDeviceCaps(dc,HORZSIZE);
////	int h=::GetDeviceCaps(dc,VERTSIZE);
////	    ::GlobalUnlock(pd.hDevMode);
////	 }
///////////////////////////
////	//CPageSetupDialog &dlg=this->m_dlgPageSet;
////	//if(dlg.DoModal()==IDOK)
////	//{
////	//	dlg.GetPaperSize();
////	//}
////	
////}

void CMainFrame::OnSelCharStyleFont()
{
	CMFCRibbonFontComboBox* pFontCombo = DYNAMIC_DOWNCAST(CMFCRibbonFontComboBox, m_wndRibbonBar.FindByID(ID_CHAR_STYLE_FONT,FALSE));
	if (pFontCombo == NULL)
	{
		return;
	}
	const CMFCFontInfo* pDesc = pFontCombo->GetFontDesc();
	ASSERT_VALID(pDesc);
	ASSERT(pDesc->m_strName.GetLength() < LF_FACESIZE);
	this->m_charStyle.m_fontName=pDesc->m_strName;
	this->m_charStyle.m_charset=pDesc->m_nCharSet;

	RedrawCharSample();

	
}

void CMainFrame::OnCharStyleHeight()
{
	// TODO: 在此添加命令处理程序代码
	CNumberEdit * p= (CNumberEdit *)m_wndRibbonBar.FindByID(ID_CHAR_STYLE_HEIGHT,FALSE);
	if(p==NULL)return;
	CString txt=p->GetEditText();
	long n=_tstol(txt);	
	//如果大于格子的尺寸，进行提示
	if(n*100>m_gridStyle.m_cellLength)
	{
		CString strTemp;
		BOOL bNameValid = strTemp.LoadString(IDS_CHAR_HEIGHT_SCOPE);
		ASSERT(bNameValid);
		if(IDOK==MessageBox(strTemp,0,MB_OKCANCEL|MB_ICONQUESTION))
		{
			goto end;
		}
		else
		{
			CString h;
			h.Format(L"%d",m_charStyle.m_charHeight/100);
			p->SetEditText(h);
			return;
		}
	}
end:
	m_charStyle.m_charHeight=n*100;

}


void CMainFrame::OnCharStyleWeight()
{
	m_charStyle.m_weight=(m_charStyle.m_weight==FW_BOLD?FW_NORMAL:FW_BOLD);
		RedrawCharSample();


}

void CMainFrame::OnUpdateCharStyleWeight(CCmdUI *pCmdUI)
{
	int chk=m_charStyle.m_weight==FW_BOLD?BST_CHECKED:BST_UNCHECKED;
	pCmdUI->SetCheck(chk);
}

void CMainFrame::OnGridCategory()
{
	// TODO: 在此添加命令处理程序代码
	CMFCRibbonGallery *gal=(CMFCRibbonGallery *)m_wndRibbonBar.FindByID(ID_GRID_CATEGORY,FALSE);
	if(gal==NULL)return;

	int n=CMFCRibbonGallery::GetLastSelectedItem(ID_GRID_CATEGORY);
	m_gridStyle.m_category=(GRIDCATEGORY)n;

	if((n==GRIDCATEGORY::HUI
		||n==GRIDCATEGORY::MI_HUI
		||n==GRIDCATEGORY::TIAN_HUI)
		&&!this->IsPrintPreview())//必须不是打印预览
	{
		//显示时并未重绘条，只是修改了属性值，因此需重画
		m_wndRibbonBar.ShowContextCategories(IDS_HUI_GRID_STYLE);
		this->m_wndRibbonBar.ActivateContextCategory(IDS_HUI_GRID_STYLE);
	}
	else
	{
		m_wndRibbonBar.ShowContextCategories(IDS_HUI_GRID_STYLE,FALSE);
	}
			//必须重新计算布局，否则重画也无作用
		m_wndRibbonBar.RecalcLayout();
		m_wndRibbonBar.RedrawWindow();
		m_wndRibbonBar.SendMessage(WM_NCPAINT);


}



void CMainFrame::OnGridLineStyle(UINT nID)
{
	// TODO: 在此添加命令处理程序代码
		CLineButton * pBtn=(CLineButton * )this->m_wndRibbonBar.FindByID(nID/*ID_LINE_STYLE*/,FALSE);
		if(pBtn==NULL)return ;
		m_gridStyle.m_lineType=pBtn->GetPenStyle();
			//更新快速访问工具条面板上的按钮图标
	CLineButton * pLineBtn=(CLineButton * )this->m_wndRibbonBar.FindByID(ID_LINE_STYLE,FALSE);
	pLineBtn->SetPen(m_gridStyle.m_lineType,m_gridStyle.m_lineWidth,m_gridStyle.m_color);

}

void CMainFrame::OnGridLineColor()
{
	// TODO: 在此添加命令处理程序代码
	CLineColorButton * pBtn=(CLineColorButton * )this->m_wndRibbonBar.FindByID(ID_LINE_COLOR,FALSE);
	if(pBtn==NULL)return ;

	m_gridStyle.m_color=pBtn->GetColor();
	//更新面板上的线条类型的颜色
	CLineButton * pLineBtn=(CLineButton * )this->m_wndRibbonBar.FindByID(ID_LINE_STYLE,FALSE);
	pLineBtn->SetColor(m_gridStyle.m_color);
	for(int n=0;n<pLineBtn->GetSubItems().GetCount();n++)
	{
		CLineButton * it=(CLineButton *)pLineBtn->GetSubItems().GetAt(n);
		it->SetColor(m_gridStyle.m_color);
	}
}




void CMainFrame::OnGridSize()
{
	// TODO: 在此添加命令处理程序代码
	UpdateGridSize();
	//毫米单位的值
	long n=m_gridStyle .m_cellLength/100;
	//查找字符高度框
	CNumberEdit * pCharH=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_CHAR_STYLE_HEIGHT,FALSE);
	pCharH->EnableSpinButtons(1,n);
	pCharH->SetMinMax(1,m_gridStyle.m_cellLength/100);
	//设置其值为字格的黄金分割率,由于文字本身有空白，加上舍入
	CString fontH;
	fontH.Format(L"%d",(long)(n*3/4));
	pCharH->SetEditText(fontH);
	m_charStyle.m_charHeight=(long)(n*3/4)*100;
	//设置文字和回字格内格子偏移的最大范围
	CMyLabelSlider * charOffset=(CMyLabelSlider * )m_wndRibbonBar.FindByID(ID_CHAR_OFFSETY,FALSE);
	CMyLabelSlider * gridOffset=(CMyLabelSlider * )m_wndRibbonBar.FindByID(ID_HUI_OFFSETY,FALSE);
	int gridSize=m_gridStyle.m_cellLength;
	charOffset->SetRange(-gridSize/20,gridSize/20);
	gridOffset->SetRange(-gridSize/20,gridSize/20);
	//判断先前设定的位置是否超出范围，若超出直接还原
	if(charOffset->GetPos()>gridSize/20||charOffset->GetPos()<-gridSize/20)
	{
		charOffset->SetPos(0);
		m_charStyle.m_offsetY=0;
	}
	if(gridOffset->GetPos()>gridSize/20||gridOffset->GetPos()<-gridSize/20)
	{
		gridOffset->SetPos(0);
		m_gridStyle.m_offsetY=0;
	}
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnRowSpace()
{
	// TODO: 在此添加命令处理程序代码
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_GRID_ROWSPACE,FALSE);
	if(p==NULL)return ;
	CString txt(p->GetEditText());
	long n=_tstol(txt);	
	m_gridStyle.m_rowSpace=n*10;
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnColSpace()
{
	// TODO: 在此添加命令处理程序代码
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_GRID_COLSPACE,FALSE);
	if(p==NULL)return ;
	CString txt(p->GetEditText());
	long n=_tstol(txt);	
	m_gridStyle.m_colSpace=n*10;
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnFontColor()
{
	// TODO: 在此添加命令处理程序代码
	CFontColorButton * p=(CFontColorButton * )this->m_wndRibbonBar.FindByID(ID_FONT_COLOR,FALSE);
	if(p==NULL)return ;
	m_charStyle .m_color=p->GetColor();

	RedrawCharSample();

}

void CMainFrame::OnFontHollow()
{
	m_charStyle .m_bHollow=!m_charStyle .m_bHollow;
		RedrawCharSample();

}


void CMainFrame::OnFontHollowSolid()
{
	// TODO: 在此添加命令处理程序代码
	CMFCRibbonCheckBox * p=(CMFCRibbonCheckBox * )this->m_wndRibbonBar.FindByID(ID_FONT_SOLID,FALSE);
	if(p==NULL)return ;
	m_charStyle .m_bSolid=!m_charStyle .m_bSolid;
	RedrawCharSample();

}

void CMainFrame::OnUpdateFontHollowSolid(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(m_charStyle.m_bHollow);
	if(m_charStyle.m_bHollow)
	{
		pCmdUI->SetCheck(m_charStyle.m_bSolid);
	}
	else
	{
	}
}

void CMainFrame::OnUpdateFontHollow(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_charStyle.m_bHollow);

}

void CMainFrame::RedrawCharSample(void)
{
	
		CCharStyleSample * samp=(CCharStyleSample * )m_wndRibbonBar.FindByID(IDS_CHAR_SAMPLE+50000,FALSE);
		//m_wndRibbonBar.GetCategory(1)->GetPanel(1)->GetElement(0);
		samp->SetCharStyle(m_charStyle);
}

void CMainFrame::OnCharDirect(UINT  nID)
{
	// TODO: 在此添加命令处理程序代码
	m_charStyle.m_bHorz=(nID==ID_CHAR_DIRECT1||nID==ID_CHAR_DIRECT2);
	m_charStyle.m_bLToR=(nID==ID_CHAR_DIRECT1||nID==ID_CHAR_DIRECT3);
	m_bRecalcPage=TRUE;


}

void CMainFrame::OnUpdateCharDirectRange(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	UINT id=pCmdUI->m_nID;
	////CMFCRibbonButton * p=(CMFCRibbonButton *)m_wndRibbonBar.FindByID(id,FALSE);
	////CString txt(p->GetText());
	////CString selTxt(txt+L"√");

	switch(id)
	{
	case ID_CHAR_DIRECT1:
		pCmdUI->SetCheck(m_charStyle.m_bHorz&&m_charStyle.m_bLToR);
		break;
	case ID_CHAR_DIRECT2:
		pCmdUI->SetCheck(m_charStyle.m_bHorz&&!m_charStyle.m_bLToR);
		break;
	case ID_CHAR_DIRECT3:
		pCmdUI->SetCheck(!m_charStyle.m_bHorz&&m_charStyle.m_bLToR);
		break;
	case ID_CHAR_DIRECT4:
		pCmdUI->SetCheck(!m_charStyle.m_bHorz&&!m_charStyle.m_bLToR);
		break;
	}

}

void CMainFrame::OnUpdateLineStyleRange(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	UINT id=pCmdUI->m_nID;
	CLineButton * btn=(CLineButton *)m_wndRibbonBar.FindByID(id,FALSE);
		if(btn==NULL)return ;
	pCmdUI->SetCheck(btn->GetPenStyle()==m_gridStyle.m_lineType);
}




//BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	BOOL  ret= CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
//	//更新打印预览,不包括打印预览本身标签
//	if(nID>ID_COMMAND_MIN&&nID<ID_COMMAND_MAX
//		&&nCode==CN_COMMAND
//		&&this->m_wndRibbonBar.FindByID(nID,0)
//		&&!m_wndRibbonBar.GetCategory(0)->FindByData(nID)//不在打印预览中
//		&&IsPrintPreview())
//	{ 
//		CMFCRibbonBaseElement *ele=m_wndRibbonBar.FindByID(nID,0);
//		if(ele->IsKindOf(RUNTIME_CLASS(CMFCRibbonButton)))
//		{
//		TRACE2("MSG=%d,code=%d\n",nID,nCode);
//		this->Invalidate();
//		}
//	}
//	return ret;
//}

void CMainFrame::OnPageMarginTop()
{
	// TODO: 在此添加命令处理程序代码
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_TOP,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_top=n*100;
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnPageMarginBottom()
{
	// TODO: 在此添加命令处理程序代码
		CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_BOTTOM,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_bottom=n*100;
	m_bRecalcPage=TRUE;
}

void CMainFrame::OnPageMarginLeft()
{
	// TODO: 在此添加命令处理程序代码
		CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_LEFT,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_left=n*100;
	m_bRecalcPage=TRUE;
}

void CMainFrame::OnPageMarginRight()
{
	// TODO: 在此添加命令处理程序代码
		CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_RIGHT,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_right=n*100;
	m_bRecalcPage=TRUE;
}

void CMainFrame::OnPageCenterH()
{
	// TODO: 在此添加命令处理程序代码
	m_pageLayout.m_bCenter=!m_pageLayout.m_bCenter;
}

void CMainFrame::OnPageCenterV()
{
	// TODO: 在此添加命令处理程序代码
	m_pageLayout.m_bVCenter=!m_pageLayout.m_bVCenter;

}

void CMainFrame::OnUpdatePageCenterH(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_pageLayout.m_bCenter);
}

void CMainFrame::OnUpdatePageCenterV(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_pageLayout.m_bVCenter);
}

	//取得页边距
	RECT CMainFrame::GetPageMargin()
	{
		return CRect(m_pageLayout.m_left, m_pageLayout.m_top,m_pageLayout.m_right,m_pageLayout.m_bottom);
	}
// 获取当前使用的打印机的纸张大小,以毫米为单位,若未装打印机，默认按A4纸张处理
CSize CMainFrame::GetPaperSize(void)
{
	CSize sz;
	if(m_pageLayout .m_bLandscape)sz.SetSize(297,210);
	else sz.SetSize(210,279);
	PRINTDLG pd;
	pd.lStructSize = (DWORD)sizeof(PRINTDLG);
	BOOL bRet = theApp.GetPrinterDeviceDefaults(&pd);
	if(bRet)
	{
		// protect memory handle with ::GlobalLock and ::GlobalUnlock
		DEVMODE FAR *pDevMode = (DEVMODE FAR *)::GlobalLock(pd.hDevMode);
		//根据布局设置中的纸张方向修改打印机的纸张方向?
		pDevMode->dmOrientation =m_pageLayout.m_bLandscape? DMORIENT_LANDSCAPE:DMORIENT_PORTRAIT;
		::GlobalUnlock(pd.hDevMode);

		HDC dc= AfxCreateDC(pd.hDevNames,pd.hDevMode);
		sz.cx=::GetDeviceCaps(dc,HORZSIZE);
		sz.cy=::GetDeviceCaps(dc,VERTSIZE);
	}
	return sz;
}

void CMainFrame::OnPaperPortrait()
{
	// TODO: 在此添加命令处理程序代码
	m_pageLayout.m_bLandscape=FALSE;
	//修改页面边距设置
	ModifyPageMargin(FALSE);
	m_bRecalcPage=TRUE;
	
}

void CMainFrame::OnPaperLandscape()
{
	// TODO: 在此添加命令处理程序代码
	m_pageLayout.m_bLandscape=TRUE;
		//修改页面边距设置
	ModifyPageMargin(TRUE);
	m_bRecalcPage=TRUE;


}

void CMainFrame::OnUpdatePaperPortrait(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(this->IsPrintPreview())
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->SetCheck(!m_pageLayout.m_bLandscape);
	//修改页面边距设置
	ModifyPageMargin(m_pageLayout.m_bLandscape);


}

void CMainFrame::OnUpdatePaperLandscape(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
		if(this->IsPrintPreview())
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->SetCheck(m_pageLayout.m_bLandscape);
	//修改页面边距设置
	ModifyPageMargin(m_pageLayout.m_bLandscape);

}


// 当改变了纸张方向后，修改打印机纸张设置，修改页面边距及相应的设置大小范围
void CMainFrame::ModifyPageMargin(BOOL bLandscape)
{
	//获取当前的打印机纸张方向设置
	PRINTDLG pd;
	pd.lStructSize = (DWORD)sizeof(PRINTDLG);
	BOOL bRet = theApp.GetPrinterDeviceDefaults(&pd);
	if(bRet)
	{
		// protect memory handle with ::GlobalLock and ::GlobalUnlock
		DEVMODE FAR *pDevMode = (DEVMODE FAR *)::GlobalLock(pd.hDevMode);
		// 如果方向不同，则需要进行处理
		BOOL bSwap=(bLandscape!=(pDevMode->dmOrientation==DMORIENT_LANDSCAPE));
		//修改打印要的纸张方向
		pDevMode->dmOrientation =bLandscape? DMORIENT_LANDSCAPE:DMORIENT_PORTRAIT;

		if(bSwap)
		{
			CNumberEdit * pT=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_TOP,FALSE);
			CNumberEdit * pB=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_BOTTOM,FALSE);
			CNumberEdit * pL=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_LEFT,FALSE);
			CNumberEdit * pR=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_RIGHT,FALSE);

			CString oldT=pT->GetEditText();
			CString oldB=pB->GetEditText();
			CString oldL=pL->GetEditText();
			CString oldR=pR->GetEditText();
			//右变下，左变上
			pT->SetEditText(oldL);
			pB->SetEditText(oldR);
			pL->SetEditText(oldT);
			pR->SetEditText(oldB);

			CSize sz=this->GetPaperSize();
			pT->SetMinMax(0,sz.cy);
			pB->SetMinMax(0,sz.cy);
			pL->SetMinMax(0,sz.cx);
			pR->SetMinMax(0,sz.cx);
		}
		::GlobalUnlock(pd.hDevMode);

	}


}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL ret= CFrameWndEx::OnCommand(wParam, lParam);
	UINT nID=LOWORD(wParam);

	MSG * pMsg=AfxGetCurrentMessage();
	//更新打印预览,不包括打印预览本身标签
	if(	ID_APP_EXIT!=nID
		&&::IsWindow(this->GetSafeHwnd())
		&&this->m_wndRibbonBar.FindByID(nID,0)
		/*&&IsPrintPreview()*/)
	{ 

		if(pMsg &&(pMsg->message==WM_COMMAND
			||pMsg->message==WM_LBUTTONUP))
		{
			if(IsPrintPreview())
			{
				this->GetActiveView()->Invalidate();
			}
			else if(m_wndTaskPane.GetSampleWnd()->IsWindowVisible())
			{
				m_wndTaskPane.GetSampleWnd()->Invalidate();
			}
		}
	}
	return ret;
}

//重写数据更新的函数，主要是当修改了设置，而直接点击打印或预览前调用
void CMainFrame::UpdateData( )
{
	BOOL ret=0;
	const AFX_MSGMAP* msgMap=this->GetMessageMap();
	const AFX_MSGMAP_ENTRY * entry=msgMap->lpEntries;
	//AfxSig_end消息循环结束标志,利用函数的命令消息处理函数进行设置更新
	//只更新几个数据输入的，主要因为可以用键盘输入
	for(;entry->nSig!=AfxSig_end;entry++)
	{
		if(entry->nSig==AfxSigCmd_v
			&&entry->nMessage==WM_COMMAND
			&& entry->nCode==CN_COMMAND)
		{
			UINT id=entry->nID;
			CMFCRibbonBaseElement *el=m_wndRibbonBar.FindByID(id,FALSE);
			if(el&&CmdInRibbonTab(id,0)
				&&CString(L"CNumberEdit")==el->GetRuntimeClass()->m_lpszClassName)
			{
				TRACE1("CLASSNAME:%S",el->GetRuntimeClass()->m_lpszClassName);
				TRACE2(" id:%d;code:%d \n",id,entry->nCode);
				//如果是更新字格大小，不能直接调用，要进行特殊处理，否则其他设置都被重设
				if(this->*entry->pfn==&CMainFrame::OnGridSize)
					UpdateGridSize();
				else
					(this->*entry->pfn)();
			}
			
		}
	}	
}


// 判断一个给定的命令ID是否在标签中
BOOL CMainFrame::CmdInRibbonTab(UINT id, BOOL bVisibleOnly)
{
	int cou=m_wndRibbonBar.GetCategoryCount();
	for(int n=0;n<cou;n++)
	{
		CMFCRibbonCategory * pCat= m_wndRibbonBar.GetCategory(n);
		if(pCat->FindByID(id,bVisibleOnly))
			return TRUE;
	}
	return FALSE;
}

// 对各种字格大小及页面参数的设置进行校验
bool CMainFrame::ValidSetting(CSize szPage)
{
	CRect rc=this->GetPageMargin();
	//页面设置不合法
	if(rc.left+rc.right>=szPage.cx
		||rc.top+rc.bottom>=szPage.cy)
	{
		return false;
	}
	//字格设置太大，一页纸容不下一个字格
	int minPrintScope=min(szPage.cx-(rc.left+rc.right),szPage.cy-(rc.top+rc.bottom));
	if(m_gridStyle.m_cellLength>minPrintScope)
		return false;
//////////////通过较验///////////
	return true;
}

void CMainFrame::OnCharOffsetY()
{
	// TODO: 在此添加命令处理程序代码
	CMFCRibbonSlider * p=(CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_CHAR_OFFSETY,FALSE);
	int pos=p->GetPos()*10;
	m_charStyle.m_bDownward=pos>=0;
	m_charStyle.m_offsetY=abs(pos);
}

void CMainFrame::OnHuiInOutRate()
{
	// TODO: 在此添加命令处理程序代码
	CMFCRibbonSlider * p=(CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_HUI_IN_OUT_RATE,FALSE);
	int pos=p->GetPos();
	m_gridStyle.m_HUI_Rate=pos;
	TRACE1("pos%d\n",p->GetPos());
}

void CMainFrame::OnHuiWHRate()
{
	// TODO: 在此添加命令处理程序代码
		CMFCRibbonSlider * p=(CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_HUI_W_H_RATE,FALSE);
	m_gridStyle.m_HUI_Rate_W_H=p->GetPos();

}

void CMainFrame::OnHuiOffsetY()
{
	CMFCRibbonSlider * p=(CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_HUI_OFFSETY,FALSE);
	int pos=p->GetPos()*10;
	m_gridStyle.m_bDownward=(pos>=0);
	m_gridStyle.m_offsetY=abs(pos);
}

// 根据文本框中的数值更新字格参数设置中保存的值
void CMainFrame::UpdateGridSize(void)
{
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_GRID_SIZE,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);	
	if(n==0)
	{
		CString  oldV;
		oldV.Format(L"%d",m_gridStyle.m_cellLength/100 );
		p->SetEditText(oldV);
		return;
	}
	m_gridStyle.m_cellLength=n*100;
}

void CMainFrame::OnViewTaskpane()
{
	//m_wndTaskPane.ShowWindow(m_wndTaskPane.IsVisible() ? SW_HIDE : SW_SHOW);
	BOOL bShow=(m_wndTaskPane.IsVisible() ? SW_HIDE : SW_SHOW);
	this->ShowPane(&m_wndTaskPane,bShow,0,1);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewTaskpane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPane.IsVisible());

}

void CMainFrame::OnShowWindow(BOOL bShow,UINT nStatus)
{
	
	//将任务窗栏显示并展开
	if(bShow)
	{
		ShowPane(GetTaskPane(),TRUE,0,1);
		GetTaskPane()->CollapseAllGroups(0);
		GetTaskPane()->GetSampleWnd()->Invalidate();
		//提示是否注册
		if(!theApp.m_bLicense)
		{
			//IDS_REGISTER_PROMPT
			CString inf;
			BOOL bValid=inf.LoadString(IDS_REGISTER_PROMPT);
			ASSERT(bValid);
			if(IDYES==AfxMessageBox (inf,MB_YESNO |MB_ICONQUESTION))
			{
				theApp.OnAppAbout();
			}

		}
	}
}


// 从注册表中加载配置
void CMainFrame::LoadSetting(void)
{
	this->m_gridStyle.Load();
	this->m_charStyle.Load();
	this->m_pageLayout.Load();
}

// 将格子、字符和页面配置保存到注册表中
void CMainFrame::SaveSetting(void)
{
	this->m_gridStyle.Save();
	this->m_charStyle.Save();
	this->m_pageLayout.Save();
}

// 设置状态条信息，主要是设置打印预览时的页码和页数信息
void CMainFrame::SetStatusInfor(LPCTSTR inf)
{
	//this->m_wndStatusBar.GetElement(0)->SetText(inf);
	m_wndStatusBar.SetInformation(inf);
}

void CMainFrame::OnOwnerDrawGrid()
{
	// TODO: 在此添加命令处理程序代码
	m_gridStyle.m_bOwnerDraw=!m_gridStyle.m_bOwnerDraw;
	if(m_gridStyle.m_bOwnerDraw
		&&!this->IsPrintPreview())//必须不是打印预览
	{
		//显示时并未重绘条，只是修改了属性值，因此需重画
		m_wndRibbonBar.ShowContextCategories(IDS_OWNERDRAWGRID);
		this->m_wndRibbonBar.ActivateContextCategory(IDS_OWNERDRAWGRID);
		CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
		if(pV->GetImage()->IsNull()&&!m_gridStyle.m_strDrawFile.IsEmpty())
			pV->SetImage(m_gridStyle.m_strDrawFile);
	}
	else
	{
		m_wndRibbonBar.ShowContextCategories(IDS_OWNERDRAWGRID,FALSE);
	}
	//必须重新计算布局，否则重画也无作用
	m_wndRibbonBar.RecalcLayout();
	m_wndRibbonBar.RedrawWindow();
	m_wndRibbonBar.SendMessage(WM_NCPAINT);
}

void CMainFrame::OnUpdateOwnerDrawGrid(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_gridStyle.m_bOwnerDraw);
}

void CMainFrame::OnOpenImg()
{
	// TODO: 在此添加命令处理程序代码
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	if(!m_gridStyle.m_strDrawFile.IsEmpty())
	{
		CString strTemp;
		BOOL bValid=strTemp.LoadString(IDS_OWNGRIDSELECTMSG);
		ASSERT(bValid);
		//提示指定或取消指定
		UINT idSel=MessageBox(strTemp,0,MB_ICONQUESTION|MB_YESNOCANCEL);
		if(idSel==IDNO)//取消指定
		{
			m_gridStyle.m_strDrawFile.Empty();
			pV->SetImage(m_gridStyle.m_strDrawFile);
			return ;
		}
		if(idSel==IDCANCEL)return ;//不做任何处理
	}
	CString	strFilter = L"Bitmap image|*.bmp|JPEG image|*.jpg|GIF image|*.gif|PNG image|*.png||";

	CFileDialog dlg(TRUE,0,0,OFN_FILEMUSTEXIST,strFilter);
	if(dlg.DoModal()==IDOK)
	{
		m_gridStyle.m_strDrawFile=dlg.GetPathName();
		pV->SetImage(dlg.GetPathName());
	}
}


void CMainFrame::OnEditImg()
{
	// TODO: 在此添加命令处理程序代码
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	CBitmap bmp;	
	CImage *img=pV->GetImage();
	//如果图像太复杂，不进行修改
	if((HBITMAP)(*img)!=NULL
		&&(img->GetWidth()>100||img->GetHeight()>100
		||img->GetBPP()<4))
	{
		CString msg;
		BOOL bValid=msg.LoadString(IDS_IMGTOOLARGE);
		ASSERT(bValid);
		MessageBox(msg);
		return ;//直接返回，不进行任何处理
	}	

	int w=(HBITMAP)(*img)?img->GetWidth():48;
	int h=(HBITMAP)(*img)?img->GetHeight():48;
	int bpp=(HBITMAP)(*img)?img->GetBPP():8;

	CDC memDC;
	if((HBITMAP)(*img)!=NULL)
	{
		//memDC.CreateCompatibleDC(CDC::FromHandle(img->GetDC()));
		//img->ReleaseDC();
		//bmp.CreateCompatibleBitmap(CDC::FromHandle(img->GetDC())/*&memDC*/,w,h);	
		//img->ReleaseDC();
		//CBitmap* oldBmp=memDC.SelectObject(&bmp);
		//img->Draw(memDC,0,0);
		//memDC.SelectObject(oldBmp);
		HBITMAP hbmp=(HBITMAP)::CopyImage((HBITMAP)(*img)/*pBitmap->GetSafeHandle()*/,IMAGE_BITMAP,0,0,0);
		bmp.Attach(hbmp);
		
	}
	else
	{
		CreateOwnerDrawBmp(&bmp);
	}
	///////////
	CMFCImageEditorDialog dlg(&bmp, this);
	if(dlg.DoModal()==IDOK)
	{
		pV->SetBmp(&bmp);
	}
}

void CMainFrame::OnSaveImg()
{
	// TODO: 在此添加命令处理程序代码
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	CImage * img=pV->GetImage();
	CString	strFilter = L"Bitmap image|*.bmp|JPEG image|*.jpg|GIF image|*.gif|PNG image|*.png||";

	CFileDialog dlg(FALSE,L"bmp",L"owngrid.bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter);
	if(dlg.DoModal()==IDOK)
	{
		img->Save(dlg.GetPathName());	
	}
}

void CMainFrame::OnUpdateSaveImg(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	CImage * img=pV->GetImage();

	pCmdUI->Enable(m_gridStyle.m_bOwnerDraw&&!img->IsNull());
}

void CMainFrame::OnOwnerDrawPreview()
{
	// TODO: 在此添加命令处理程序代码
	OnEditImg();
}


// 创建新位图，作为自绘格子，可以进一步修改。
void CMainFrame::CreateOwnerDrawBmp(CBitmap * pBmp)
{
	CClientDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc/*NULL*/);
	pBmp->CreateCompatibleBitmap(&dc,48,48);
	CBitmap* oldBmp=memDC.SelectObject(pBmp);
	CRect rcBmp(0,0,48,48);
	CBrush whiteBru(RGB(255,255,255));
	memDC.FillRect(&rcBmp, &whiteBru/*&afxGlobalData.brBtnFace*/);
	rcBmp.DeflateRect(8,8);
	CBrush * oldBru=(CBrush * )memDC.SelectStockObject(NULL_BRUSH);
	CPen pen(PS_DOT,1,RGB(255,0,0));
	////CPen * oldPen=memDC.SelectObject(&pen);
	////memDC.Ellipse(&rcBmp);
	////memDC.SelectObject(oldPen);
	memDC.SelectObject(oldBmp);
	memDC.SelectObject(oldBru);
	
	m_gridStyle.m_clrBackgroud=RGB(255,255,255);
	CMFCRibbonColorButton * pBk=(CMFCRibbonColorButton *)m_wndRibbonBar.FindByID(ID_BACKGROUND,FALSE);
	pBk->SetColor(m_gridStyle.m_clrBackgroud);

}

void CMainFrame::OnOwnerDrawBackground()
{
	// TODO: 在此添加命令处理程序代码
	CMFCRibbonColorButton * pBk=(CMFCRibbonColorButton *)m_wndRibbonBar.FindByID(ID_BACKGROUND,FALSE);
	m_gridStyle.m_clrBackgroud=pBk->GetColor();
}

// 取得自绘格子的图像
CImage * CMainFrame::GetOwnGridImg(void)
{
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	return pV->GetImage();
}
