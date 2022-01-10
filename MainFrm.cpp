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

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "���ֹ���.h"
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

// CMainFrame ����/����

CMainFrame::CMainFrame()
: m_bRecalcPage(FALSE)
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//////��̨��ҳ������ʱ�ļ�����λ��ͳһΪ100��֮1����
	////m_dlgPageSet.m_psd .Flags|=PSD_DISABLEPAPER|PSD_INHUNDREDTHSOFMILLIMETERS;
	//////�������Ҹ������ף���2000��λ
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
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	////bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	////ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUS_PANE, strTitlePane1, TRUE), strTitlePane1);
	////m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	//EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �������񽫴�������࣬��˽���ʱ��������ͣ��:
	//EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);


	if (!CreateTaskPane ())
	{
		TRACE0("Failed to create tasks pane\n");
		return -1;      // fail to create
	}

	// �Ѵ��� Outlook ����Ӧ���������ͣ����
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// �������ͼ��:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// ��ʼ����ť:
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
	//�Զ�������������
	AddGridStyle();
	//���ӻ��ָ���Ӧ��������
	AddHUIGridStyle();
	AddOwnerDrawPage();
	AddCharStyle();
	AddPageLayout();
	//ʹ���е������Ԫ�ؾ���ֱ����
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

	// Ϊ�������塱�����ӡ��������:
	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// �����������塱���:
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

	// ��������ӡ���ͼ�����:
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
//�������л���ť
	bNameValid = strTemp.LoadString(IDS_VIEW_TASK_PANE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnTaskpane = new CMFCRibbonCheckBox(ID_VIEW_TASKPANE, strTemp);
	pPanelView->Add(pBtnTaskpane);


	////// ��Ԫ����ӵ�ѡ��Ҳ�:
	//////���������л�ѡ��
	////bNameValid = strTemp.LoadString(IDS_LANGUAGE);
	////ASSERT(bNameValid);
	////CMFCRibbonButton* pLangButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	////pLangButton->SetMenu(IDR_LANGUAGE, FALSE /* ��Ĭ������*/, TRUE /* �Ҷ���*/);
	////m_wndRibbonBar.AddToTabs(pLangButton);
//////////////////////
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* ��Ĭ������*/, TRUE /* �Ҷ���*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// ��ӿ��ٷ��ʹ���������:
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
//		return FALSE; // δ�ܴ���
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
//	// �ɸ��������Զ����أ��ɵ�����С�������ܹر�
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
//		TRACE0("δ�ܴ���������\n");
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


// CMainFrame ���

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


// CMainFrame ��Ϣ�������

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

	//����ͼ��͸��ɫ,��Ҫ��ribbon�Ļ��ƶ����԰�ť����ɫΪ͸��ɫ�ģ�ͳһ��Ϊ��ɫ
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
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // ǿ�ƹرա���ӡԤ����ģʽ
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

// ���Ӹ��ӿ��ߵ���ʽ
void CMainFrame::AddGridStyle(void)
{
// ���Ӹ�����ʽ���:
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_GRID_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pGridStyle = m_wndRibbonBar.AddCategory(strTemp, IDB_GRID_STYLE_SMALL, IDB_GRID_STYLE,CSize(16,16),CSize(48,48));
	//// �������������͡����:
	bNameValid = strTemp.LoadString(IDS_GRID_CATEGORY);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanel = pGridStyle->AddPanel(strTemp);
	

	CMFCRibbonGallery *gal=new CMyGallery(ID_GRID_CATEGORY, strTemp, 0, 0, IDB_GRID_CATEGORY2,64);
	gal->SetAlwaysLargeImage();
	gal->SetIconsInRow(5);
	////gal->SetButtonMode();
	pPanel->Add(gal);
	gal->SelectItem(m_gridStyle.m_category);
	//�����Ի���ӵĸ�ѡ��־
	bNameValid = strTemp.LoadString(IDS_OWNERDRAW);
	ASSERT(bNameValid);
	CMFCRibbonButton * pDraw=new CMFCRibbonButton(ID_OWNERDRAWGRID,strTemp,2,2);
	pPanel->Add (pDraw);
	pDraw->SetTextAlwaysOnRight();
	////////////////
	//�����������
	bNameValid = strTemp.LoadString(IDS_GRID_LINE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pLinePanel = pGridStyle->AddPanel(strTemp);
	//������ɫ
	CLineColorButton * btnColor=new CLineColorButton(
		ID_LINE_COLOR);
	bNameValid = strTemp.LoadString(IDS_OTHERCOLOR);
	ASSERT(bNameValid);	
	btnColor->EnableOtherButton(strTemp);
	btnColor->SetAlwaysLargeImage();
	btnColor->SetImageIndex(1,FALSE);	
	btnColor->SetColor(m_gridStyle.m_color);
	pLinePanel->Add(btnColor);


	//������ʽ
	COLORREF lineColor=m_gridStyle.m_color;
	CLineButton  * btnLine=new CLineButton(ID_LINE_STYLE,m_gridStyle.m_lineType,1,lineColor);
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE1,PS_SOLID,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE2,PS_DASH,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE3,PS_DOT,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE4,PS_DASHDOT,1,lineColor,btnLine));
	btnLine->AddSubItem (new CLineButton(ID_LINE_STYLE5,PS_DASHDOTDOT,1,lineColor,btnLine));
	btnLine->SetAlwaysLargeImage();
	pLinePanel->Add(btnLine);
	//���Ӹ��Ӵ�С��С,������ʾ��MMΪ��λ
	bNameValid = strTemp.LoadString(IDS_GRID_SIZE_SPACE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pSizePanel = pGridStyle->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_GRID_SIZE);
	ASSERT(bNameValid);
	CNumberEdit* gridSize = new CNumberEdit(ID_GRID_SIZE, 40, strTemp, -1);
	//Ĭ��8,��1��13���׸ߣ����������Զ�����,���������Ӵ�С
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
	//���Ӹ��Ӽ������,������ʾ��0.1MMΪ��λ
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

// �������ָ�ʽ
void CMainFrame::AddCharStyle(void)
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_CHAR_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCharStyle = m_wndRibbonBar.AddCategory(strTemp, IDB_CHAR_STYLE, IDB_WRITELARGE);
	//// ����������ѡ���
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
	//���������Сѡ��
	bNameValid = strTemp.LoadString(IDS_FONT_HEIGTH);
	ASSERT(bNameValid);
	CNumberEdit* fontHei = new CNumberEdit(ID_CHAR_STYLE_HEIGHT, 40, strTemp, -1);
	//Ĭ��8,��1��13���׸ߣ����������Զ�����,���������Ӵ�С
	fontHei->EnableSpinButtons(1, 13);
	fontHei->SetMinMax(1,m_gridStyle.m_cellLength/100);
	char sz[10]={0};
	itoa(m_charStyle.m_charHeight/100,sz,10);
	fontHei->SetEditText(CString(sz));
	pPanel->Add(fontHei);
	pPanel->Add(new CMFCRibbonSeparator());
	//����Ĵ�ϸ
	bNameValid = strTemp.LoadString(IDS_FONT_BOLD);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox *bold=new CMFCRibbonCheckBox(ID_CHAR_STYLE_WEIGHT,strTemp);
	pPanel->Add(bold);
	//������ɫ
	bNameValid = strTemp.LoadString(IDS_FONT_COLOR);
	ASSERT(bNameValid);
	CMFCRibbonColorButton *fontColor=new CFontColorButton(ID_FONT_COLOR,strTemp);
	fontColor->SetColor(m_charStyle.m_color);

	bNameValid = strTemp.LoadString(IDS_OTHERCOLOR);
	ASSERT(bNameValid);	
	fontColor->EnableOtherButton(strTemp);

	pPanel->Add(fontColor);

	pPanel->Add(new CMFCRibbonSeparator());

		//�Ƿ��������
	bNameValid = strTemp.LoadString(IDS_FONT_HOLLOW);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox *fontHollow=new CMFCRibbonCheckBox(ID_FONT_HOLLOW,strTemp);
	pPanel->Add(fontHollow);	

	//��Ϊ�����֣����Ƿ�Ϊʵ��
	bNameValid = strTemp.LoadString(IDS_FONT_SOLID);
	ASSERT(bNameValid);
	CMFCRibbonButton *solid=new CMFCRibbonCheckBox(ID_FONT_SOLID,strTemp);
	pPanel->Add(solid);

	//����ƫ��
		pPanel->Add(new CMFCRibbonSeparator());
	bNameValid = strTemp.LoadString(IDS_CHAR_OFFSETY);
	ASSERT(bNameValid);
	CMyLabelSlider * sld=new CMyLabelSlider(ID_CHAR_OFFSETY,strTemp,200);
	sld->SetRange(-m_gridStyle.m_cellLength/20,m_gridStyle.m_cellLength/20);
	int pos=m_charStyle.m_bDownward?m_charStyle.m_offsetY:-m_charStyle.m_offsetY;
	sld->SetPos(pos);
	pPanel->Add(sld);

	//����������ʾ���
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

//����ҳ�沼�֣���ҳ�߾࣬���ַ��򣬾��е�
void CMainFrame::AddPageLayout(void )
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_PAGE_LAYOUT);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pPageLayout = m_wndRibbonBar.AddCategory(strTemp, IDB_PAGELAYOUT_SMALL/*IDB_WRITESMALL*/, IDB_PAGE_LAYOUT,CSize(16,16),CSize(36,48));
	//ҳ�߾����
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
	//�²�
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
		//��
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN_LEFT);
	ASSERT(bNameValid);
	CNumberEdit* LEFT = new CNumberEdit(ID_PAGE_MARGIN_LEFT, 40, strTemp, -1);
	LEFT->EnableSpinButtons(0, 50);
	LEFT->SetMinMax(0,szPaper.cx);
	char cLEFT[10]={0};
	itoa(m_pageLayout.m_left/100,cLEFT,10);
	LEFT->SetEditText(CString(cLEFT));
	pPage->Add(LEFT);
		//�Ҳ�
	bNameValid = strTemp.LoadString(IDS_PAGE_MARGIN_RIGHT);
	ASSERT(bNameValid);
	CNumberEdit* RIGHT = new CNumberEdit(ID_PAGE_MARGIN_RIGHT, 40, strTemp, -1);
	RIGHT->EnableSpinButtons(0, 50);
	RIGHT->SetMinMax(0,szPaper.cx);
	char cRIGHT[10]={0};
	itoa(m_pageLayout.m_right/100,cRIGHT,10);
	RIGHT->SetEditText(CString(cRIGHT));
	pPage->Add(RIGHT);
	//ˮƽ����ֱ����
	bNameValid = strTemp.LoadString(IDS_PAGE_CENTER);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pCenter=pPageLayout->AddPanel(strTemp);
	//ˮƽ����
	bNameValid = strTemp.LoadString(IDS_PAGE_CENTER_HORZ);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox * pHCenter= new CMFCRibbonCheckBox(ID_CENTER_H,strTemp);
	pCenter->Add(pHCenter);
	//��ֱ����
	bNameValid = strTemp.LoadString(IDS_PAGE_CENTER_VERT);
	ASSERT(bNameValid);
	CMFCRibbonCheckBox * pVCenter= new CMFCRibbonCheckBox(ID_CENTER_V,strTemp);
	pCenter->Add(pVCenter);
	//ֽ�ŷ���
	bNameValid = strTemp.LoadString(IDS_PAPER_ORIENT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPaper = pPageLayout->AddPanel(strTemp);
	//
	bNameValid = strTemp.LoadString(IDS_PAPER_PORTRAIT);
	ASSERT(bNameValid);
	//ʹ�����ַ���ť����ʹ����Ի��Сͼ��
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
	//////////////////////���ַ������
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
	//�������
	CMFCRibbonSlider *pOutRat=new CMyLabelSlider(ID_HUI_IN_OUT_RATE,strTemp,300);
	pOutRat->SetRange(0,100);
	pOutRat->SetPos(m_gridStyle.m_HUI_Rate);
	pan->Add(pOutRat);
	//��߱���
	bNameValid = strTemp.LoadString(IDS_HUI_W_H_RATE);
	ASSERT(bNameValid);
	CMFCRibbonSlider *pWHRat=new CMyLabelSlider(ID_HUI_W_H_RATE,strTemp,300);
	pWHRat->SetRange(0,1000);
	pWHRat->SetPos(m_gridStyle.m_HUI_Rate_W_H);
	pan->Add(pWHRat);
	//ƫ�ƾ���
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
	//����Ԥ��Ԫ��
	CDrawImgPreview * pView=new CDrawImgPreview(ID_OWNERDRAWPREVIEW);
	if(m_gridStyle.m_bOwnerDraw)
		pView->SetImage(m_gridStyle.m_strDrawFile);
	pan->Add(pView);
	pan->AddSeparator();
	//���Ӵ򿪣��༭�����水ť
	bNameValid = strTemp.LoadString(IDS_EDITGRIDIMG);
	ASSERT(bNameValid);
	pan->Add(new CMFCRibbonButton(ID_EDITIMG,strTemp));

	bNameValid = strTemp.LoadString(IDS_SAVEGRIDIMG);
	ASSERT(bNameValid);
	pan->Add(new CMFCRibbonButton(ID_SAVEDRAWIMG,strTemp));
	//��ͼ���ļ���
	bNameValid = strTemp.LoadString(IDS_OPENGRIDIMG);
	ASSERT(bNameValid);
	pan->Add(new CMFCRibbonButton(ID_OPENDRAWIMG,strTemp));
	//pan->AddSeparator();
	//͸��ɫ��ѡ��
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
////	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	CNumberEdit * p= (CNumberEdit *)m_wndRibbonBar.FindByID(ID_CHAR_STYLE_HEIGHT,FALSE);
	if(p==NULL)return;
	CString txt=p->GetEditText();
	long n=_tstol(txt);	
	//������ڸ��ӵĳߴ磬������ʾ
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
	// TODO: �ڴ���������������
	CMFCRibbonGallery *gal=(CMFCRibbonGallery *)m_wndRibbonBar.FindByID(ID_GRID_CATEGORY,FALSE);
	if(gal==NULL)return;

	int n=CMFCRibbonGallery::GetLastSelectedItem(ID_GRID_CATEGORY);
	m_gridStyle.m_category=(GRIDCATEGORY)n;

	if((n==GRIDCATEGORY::HUI
		||n==GRIDCATEGORY::MI_HUI
		||n==GRIDCATEGORY::TIAN_HUI)
		&&!this->IsPrintPreview())//���벻�Ǵ�ӡԤ��
	{
		//��ʾʱ��δ�ػ�����ֻ���޸�������ֵ��������ػ�
		m_wndRibbonBar.ShowContextCategories(IDS_HUI_GRID_STYLE);
		this->m_wndRibbonBar.ActivateContextCategory(IDS_HUI_GRID_STYLE);
	}
	else
	{
		m_wndRibbonBar.ShowContextCategories(IDS_HUI_GRID_STYLE,FALSE);
	}
			//�������¼��㲼�֣������ػ�Ҳ������
		m_wndRibbonBar.RecalcLayout();
		m_wndRibbonBar.RedrawWindow();
		m_wndRibbonBar.SendMessage(WM_NCPAINT);


}



void CMainFrame::OnGridLineStyle(UINT nID)
{
	// TODO: �ڴ���������������
		CLineButton * pBtn=(CLineButton * )this->m_wndRibbonBar.FindByID(nID/*ID_LINE_STYLE*/,FALSE);
		if(pBtn==NULL)return ;
		m_gridStyle.m_lineType=pBtn->GetPenStyle();
			//���¿��ٷ��ʹ���������ϵİ�ťͼ��
	CLineButton * pLineBtn=(CLineButton * )this->m_wndRibbonBar.FindByID(ID_LINE_STYLE,FALSE);
	pLineBtn->SetPen(m_gridStyle.m_lineType,m_gridStyle.m_lineWidth,m_gridStyle.m_color);

}

void CMainFrame::OnGridLineColor()
{
	// TODO: �ڴ���������������
	CLineColorButton * pBtn=(CLineColorButton * )this->m_wndRibbonBar.FindByID(ID_LINE_COLOR,FALSE);
	if(pBtn==NULL)return ;

	m_gridStyle.m_color=pBtn->GetColor();
	//��������ϵ��������͵���ɫ
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
	// TODO: �ڴ���������������
	UpdateGridSize();
	//���׵�λ��ֵ
	long n=m_gridStyle .m_cellLength/100;
	//�����ַ��߶ȿ�
	CNumberEdit * pCharH=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_CHAR_STYLE_HEIGHT,FALSE);
	pCharH->EnableSpinButtons(1,n);
	pCharH->SetMinMax(1,m_gridStyle.m_cellLength/100);
	//������ֵΪ�ָ�Ļƽ�ָ���,�������ֱ����пհף���������
	CString fontH;
	fontH.Format(L"%d",(long)(n*3/4));
	pCharH->SetEditText(fontH);
	m_charStyle.m_charHeight=(long)(n*3/4)*100;
	//�������ֺͻ��ָ��ڸ���ƫ�Ƶ����Χ
	CMyLabelSlider * charOffset=(CMyLabelSlider * )m_wndRibbonBar.FindByID(ID_CHAR_OFFSETY,FALSE);
	CMyLabelSlider * gridOffset=(CMyLabelSlider * )m_wndRibbonBar.FindByID(ID_HUI_OFFSETY,FALSE);
	int gridSize=m_gridStyle.m_cellLength;
	charOffset->SetRange(-gridSize/20,gridSize/20);
	gridOffset->SetRange(-gridSize/20,gridSize/20);
	//�ж���ǰ�趨��λ���Ƿ񳬳���Χ��������ֱ�ӻ�ԭ
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
	// TODO: �ڴ���������������
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_GRID_ROWSPACE,FALSE);
	if(p==NULL)return ;
	CString txt(p->GetEditText());
	long n=_tstol(txt);	
	m_gridStyle.m_rowSpace=n*10;
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnColSpace()
{
	// TODO: �ڴ���������������
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_GRID_COLSPACE,FALSE);
	if(p==NULL)return ;
	CString txt(p->GetEditText());
	long n=_tstol(txt);	
	m_gridStyle.m_colSpace=n*10;
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnFontColor()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	CMFCRibbonCheckBox * p=(CMFCRibbonCheckBox * )this->m_wndRibbonBar.FindByID(ID_FONT_SOLID,FALSE);
	if(p==NULL)return ;
	m_charStyle .m_bSolid=!m_charStyle .m_bSolid;
	RedrawCharSample();

}

void CMainFrame::OnUpdateFontHollowSolid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	m_charStyle.m_bHorz=(nID==ID_CHAR_DIRECT1||nID==ID_CHAR_DIRECT2);
	m_charStyle.m_bLToR=(nID==ID_CHAR_DIRECT1||nID==ID_CHAR_DIRECT3);
	m_bRecalcPage=TRUE;


}

void CMainFrame::OnUpdateCharDirectRange(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	UINT id=pCmdUI->m_nID;
	////CMFCRibbonButton * p=(CMFCRibbonButton *)m_wndRibbonBar.FindByID(id,FALSE);
	////CString txt(p->GetText());
	////CString selTxt(txt+L"��");

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
	// TODO: �ڴ������������û����洦��������
	UINT id=pCmdUI->m_nID;
	CLineButton * btn=(CLineButton *)m_wndRibbonBar.FindByID(id,FALSE);
		if(btn==NULL)return ;
	pCmdUI->SetCheck(btn->GetPenStyle()==m_gridStyle.m_lineType);
}




//BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	BOOL  ret= CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
//	//���´�ӡԤ��,��������ӡԤ�������ǩ
//	if(nID>ID_COMMAND_MIN&&nID<ID_COMMAND_MAX
//		&&nCode==CN_COMMAND
//		&&this->m_wndRibbonBar.FindByID(nID,0)
//		&&!m_wndRibbonBar.GetCategory(0)->FindByData(nID)//���ڴ�ӡԤ����
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
	// TODO: �ڴ���������������
	CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_TOP,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_top=n*100;
	m_bRecalcPage=TRUE;

}

void CMainFrame::OnPageMarginBottom()
{
	// TODO: �ڴ���������������
		CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_BOTTOM,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_bottom=n*100;
	m_bRecalcPage=TRUE;
}

void CMainFrame::OnPageMarginLeft()
{
	// TODO: �ڴ���������������
		CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_LEFT,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_left=n*100;
	m_bRecalcPage=TRUE;
}

void CMainFrame::OnPageMarginRight()
{
	// TODO: �ڴ���������������
		CNumberEdit * p=(CNumberEdit * )this->m_wndRibbonBar.FindByID(ID_PAGE_MARGIN_RIGHT,FALSE);
	if(p==NULL)return ;
	CString txt=p->GetEditText();
	long n=_tstol(txt);		
	this->m_pageLayout .m_right=n*100;
	m_bRecalcPage=TRUE;
}

void CMainFrame::OnPageCenterH()
{
	// TODO: �ڴ���������������
	m_pageLayout.m_bCenter=!m_pageLayout.m_bCenter;
}

void CMainFrame::OnPageCenterV()
{
	// TODO: �ڴ���������������
	m_pageLayout.m_bVCenter=!m_pageLayout.m_bVCenter;

}

void CMainFrame::OnUpdatePageCenterH(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_pageLayout.m_bCenter);
}

void CMainFrame::OnUpdatePageCenterV(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_pageLayout.m_bVCenter);
}

	//ȡ��ҳ�߾�
	RECT CMainFrame::GetPageMargin()
	{
		return CRect(m_pageLayout.m_left, m_pageLayout.m_top,m_pageLayout.m_right,m_pageLayout.m_bottom);
	}
// ��ȡ��ǰʹ�õĴ�ӡ����ֽ�Ŵ�С,�Ժ���Ϊ��λ,��δװ��ӡ����Ĭ�ϰ�A4ֽ�Ŵ���
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
		//���ݲ��������е�ֽ�ŷ����޸Ĵ�ӡ����ֽ�ŷ���?
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
	// TODO: �ڴ���������������
	m_pageLayout.m_bLandscape=FALSE;
	//�޸�ҳ��߾�����
	ModifyPageMargin(FALSE);
	m_bRecalcPage=TRUE;
	
}

void CMainFrame::OnPaperLandscape()
{
	// TODO: �ڴ���������������
	m_pageLayout.m_bLandscape=TRUE;
		//�޸�ҳ��߾�����
	ModifyPageMargin(TRUE);
	m_bRecalcPage=TRUE;


}

void CMainFrame::OnUpdatePaperPortrait(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(this->IsPrintPreview())
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->SetCheck(!m_pageLayout.m_bLandscape);
	//�޸�ҳ��߾�����
	ModifyPageMargin(m_pageLayout.m_bLandscape);


}

void CMainFrame::OnUpdatePaperLandscape(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		if(this->IsPrintPreview())
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->SetCheck(m_pageLayout.m_bLandscape);
	//�޸�ҳ��߾�����
	ModifyPageMargin(m_pageLayout.m_bLandscape);

}


// ���ı���ֽ�ŷ�����޸Ĵ�ӡ��ֽ�����ã��޸�ҳ��߾༰��Ӧ�����ô�С��Χ
void CMainFrame::ModifyPageMargin(BOOL bLandscape)
{
	//��ȡ��ǰ�Ĵ�ӡ��ֽ�ŷ�������
	PRINTDLG pd;
	pd.lStructSize = (DWORD)sizeof(PRINTDLG);
	BOOL bRet = theApp.GetPrinterDeviceDefaults(&pd);
	if(bRet)
	{
		// protect memory handle with ::GlobalLock and ::GlobalUnlock
		DEVMODE FAR *pDevMode = (DEVMODE FAR *)::GlobalLock(pd.hDevMode);
		// �������ͬ������Ҫ���д���
		BOOL bSwap=(bLandscape!=(pDevMode->dmOrientation==DMORIENT_LANDSCAPE));
		//�޸Ĵ�ӡҪ��ֽ�ŷ���
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
			//�ұ��£������
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
	// TODO: �ڴ����ר�ô����/����û���
	BOOL ret= CFrameWndEx::OnCommand(wParam, lParam);
	UINT nID=LOWORD(wParam);

	MSG * pMsg=AfxGetCurrentMessage();
	//���´�ӡԤ��,��������ӡԤ�������ǩ
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

//��д���ݸ��µĺ�������Ҫ�ǵ��޸������ã���ֱ�ӵ����ӡ��Ԥ��ǰ����
void CMainFrame::UpdateData( )
{
	BOOL ret=0;
	const AFX_MSGMAP* msgMap=this->GetMessageMap();
	const AFX_MSGMAP_ENTRY * entry=msgMap->lpEntries;
	//AfxSig_end��Ϣѭ��������־,���ú�����������Ϣ�������������ø���
	//ֻ���¼�����������ģ���Ҫ��Ϊ�����ü�������
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
				//����Ǹ����ָ��С������ֱ�ӵ��ã�Ҫ�������⴦�������������ö�������
				if(this->*entry->pfn==&CMainFrame::OnGridSize)
					UpdateGridSize();
				else
					(this->*entry->pfn)();
			}
			
		}
	}	
}


// �ж�һ������������ID�Ƿ��ڱ�ǩ��
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

// �Ը����ָ��С��ҳ����������ý���У��
bool CMainFrame::ValidSetting(CSize szPage)
{
	CRect rc=this->GetPageMargin();
	//ҳ�����ò��Ϸ�
	if(rc.left+rc.right>=szPage.cx
		||rc.top+rc.bottom>=szPage.cy)
	{
		return false;
	}
	//�ָ�����̫��һҳֽ�ݲ���һ���ָ�
	int minPrintScope=min(szPage.cx-(rc.left+rc.right),szPage.cy-(rc.top+rc.bottom));
	if(m_gridStyle.m_cellLength>minPrintScope)
		return false;
//////////////ͨ������///////////
	return true;
}

void CMainFrame::OnCharOffsetY()
{
	// TODO: �ڴ���������������
	CMFCRibbonSlider * p=(CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_CHAR_OFFSETY,FALSE);
	int pos=p->GetPos()*10;
	m_charStyle.m_bDownward=pos>=0;
	m_charStyle.m_offsetY=abs(pos);
}

void CMainFrame::OnHuiInOutRate()
{
	// TODO: �ڴ���������������
	CMFCRibbonSlider * p=(CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_HUI_IN_OUT_RATE,FALSE);
	int pos=p->GetPos();
	m_gridStyle.m_HUI_Rate=pos;
	TRACE1("pos%d\n",p->GetPos());
}

void CMainFrame::OnHuiWHRate()
{
	// TODO: �ڴ���������������
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

// �����ı����е���ֵ�����ָ���������б����ֵ
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
	
	//����������ʾ��չ��
	if(bShow)
	{
		ShowPane(GetTaskPane(),TRUE,0,1);
		GetTaskPane()->CollapseAllGroups(0);
		GetTaskPane()->GetSampleWnd()->Invalidate();
		//��ʾ�Ƿ�ע��
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


// ��ע����м�������
void CMainFrame::LoadSetting(void)
{
	this->m_gridStyle.Load();
	this->m_charStyle.Load();
	this->m_pageLayout.Load();
}

// �����ӡ��ַ���ҳ�����ñ��浽ע�����
void CMainFrame::SaveSetting(void)
{
	this->m_gridStyle.Save();
	this->m_charStyle.Save();
	this->m_pageLayout.Save();
}

// ����״̬����Ϣ����Ҫ�����ô�ӡԤ��ʱ��ҳ���ҳ����Ϣ
void CMainFrame::SetStatusInfor(LPCTSTR inf)
{
	//this->m_wndStatusBar.GetElement(0)->SetText(inf);
	m_wndStatusBar.SetInformation(inf);
}

void CMainFrame::OnOwnerDrawGrid()
{
	// TODO: �ڴ���������������
	m_gridStyle.m_bOwnerDraw=!m_gridStyle.m_bOwnerDraw;
	if(m_gridStyle.m_bOwnerDraw
		&&!this->IsPrintPreview())//���벻�Ǵ�ӡԤ��
	{
		//��ʾʱ��δ�ػ�����ֻ���޸�������ֵ��������ػ�
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
	//�������¼��㲼�֣������ػ�Ҳ������
	m_wndRibbonBar.RecalcLayout();
	m_wndRibbonBar.RedrawWindow();
	m_wndRibbonBar.SendMessage(WM_NCPAINT);
}

void CMainFrame::OnUpdateOwnerDrawGrid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_gridStyle.m_bOwnerDraw);
}

void CMainFrame::OnOpenImg()
{
	// TODO: �ڴ���������������
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	if(!m_gridStyle.m_strDrawFile.IsEmpty())
	{
		CString strTemp;
		BOOL bValid=strTemp.LoadString(IDS_OWNGRIDSELECTMSG);
		ASSERT(bValid);
		//��ʾָ����ȡ��ָ��
		UINT idSel=MessageBox(strTemp,0,MB_ICONQUESTION|MB_YESNOCANCEL);
		if(idSel==IDNO)//ȡ��ָ��
		{
			m_gridStyle.m_strDrawFile.Empty();
			pV->SetImage(m_gridStyle.m_strDrawFile);
			return ;
		}
		if(idSel==IDCANCEL)return ;//�����κδ���
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
	// TODO: �ڴ���������������
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	CBitmap bmp;	
	CImage *img=pV->GetImage();
	//���ͼ��̫���ӣ��������޸�
	if((HBITMAP)(*img)!=NULL
		&&(img->GetWidth()>100||img->GetHeight()>100
		||img->GetBPP()<4))
	{
		CString msg;
		BOOL bValid=msg.LoadString(IDS_IMGTOOLARGE);
		ASSERT(bValid);
		MessageBox(msg);
		return ;//ֱ�ӷ��أ��������κδ���
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ������������û����洦��������
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	CImage * img=pV->GetImage();

	pCmdUI->Enable(m_gridStyle.m_bOwnerDraw&&!img->IsNull());
}

void CMainFrame::OnOwnerDrawPreview()
{
	// TODO: �ڴ���������������
	OnEditImg();
}


// ������λͼ����Ϊ�Ի���ӣ����Խ�һ���޸ġ�
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
	// TODO: �ڴ���������������
	CMFCRibbonColorButton * pBk=(CMFCRibbonColorButton *)m_wndRibbonBar.FindByID(ID_BACKGROUND,FALSE);
	m_gridStyle.m_clrBackgroud=pBk->GetColor();
}

// ȡ���Ի���ӵ�ͼ��
CImage * CMainFrame::GetOwnGridImg(void)
{
	CDrawImgPreview * pV=(CDrawImgPreview *)m_wndRibbonBar.FindByID(ID_OWNERDRAWPREVIEW,FALSE);
	return pV->GetImage();
}
