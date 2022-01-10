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

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
//#include "CalendarBar.h"
#include "Resource.h"
#include "setting.h"
#include "TaskPane.h"


//class COutlookBar : public CMFCOutlookBar
//{
//	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
//	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); }
//};

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:
	void UpdateMRUFilesList ()
	{
		m_wndTaskPane.UpdateMRUFilesList();
	}
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CTaskPane			m_wndTaskPane;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	////afx_msg void OnViewCaptionBar();
	////afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();
	////BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth);
	////BOOL CreateCaptionBar();
	BOOL CreateTaskPane ();

	//////int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	//////CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	//////CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	//////CMFCOutlookBarPane*    m_pCurrOutlookPage;
public:
	//取得ribbonbar
	CMFCRibbonBar & GetRibbonBar()const {return (CMFCRibbonBar &) this->m_wndRibbonBar;}
	// 增加格子框线的样式
	void AddGridStyle(void);
	// 增加文字格式
	void AddCharStyle(void);
	//增加页面布局，即页边距，文字方向，居中等
	void AddPageLayout(void );
	//增加回字格的设置
	void AddHUIGridStyle();
	//增加自绘格子的设置
	void AddOwnerDrawPage();
	//格子样式
	CGridStyle m_gridStyle;
	//字符样式
	CCharStyle m_charStyle;
	//页面布局及文字方向
	CPageLayout m_pageLayout;
public:
	//取得页边距
	RECT GetPageMargin();
	CTaskPane * GetTaskPane() {return &this->m_wndTaskPane;}

	afx_msg void OnSelCharStyleFont();
	afx_msg void OnCharStyleHeight();

	afx_msg void OnCharStyleWeight();
	afx_msg void OnUpdateCharStyleWeight(CCmdUI *pCmdUI);

	afx_msg void OnGridCategory();
	afx_msg void OnGridLineStyle(UINT nID);
	afx_msg void OnGridLineColor();
	afx_msg void OnGridSize();
	afx_msg void OnRowSpace();
	afx_msg void OnColSpace();
	afx_msg void OnFontColor();
	afx_msg void OnFontHollow();
	afx_msg void OnFontHollowSolid();
	afx_msg void OnUpdateFontHollowSolid(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFontHollow(CCmdUI *pCmdUI);
	void RedrawCharSample(void);
	afx_msg void OnCharDirect(UINT  nID);
	afx_msg void OnUpdateCharDirectRange(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLineStyleRange(CCmdUI *pCmdUI);
	afx_msg void OnPageMarginTop();
	afx_msg void OnPageMarginBottom();
	afx_msg void OnPageMarginLeft();
	afx_msg void OnPageMarginRight();
	afx_msg void OnPageCenterH();
	afx_msg void OnPageCenterV();
	afx_msg void OnUpdatePageCenterH(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePageCenterV(CCmdUI *pCmdUI);
	// 获取当前使用的打印机的纸张大小,以毫米为单位
	CSize GetPaperSize(void);
	afx_msg void OnPaperLandscape();
	afx_msg void OnPaperPortrait();
	afx_msg void OnUpdatePaperPortrait(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePaperLandscape(CCmdUI *pCmdUI);
	// 当改变了纸张方向后，修改打印机纸张设置，修改页面边距及相应的设置大小范围
	void ModifyPageMargin(BOOL bLandscape);
	//重写数据更新的函数，主要是当修改了设置，而直接点击打印或预览前调用
		void UpdateData();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	// 判断一个给定的命令ID是否在标签中
	BOOL CmdInRibbonTab(UINT id, BOOL bVisibleOnly=TRUE);
	// 对各种字格大小及页面参数的设置进行校验
	bool ValidSetting(CSize szPage);
	afx_msg void OnCharOffsetY();
	afx_msg void OnHuiInOutRate();
	afx_msg void OnHuiWHRate();
	afx_msg void OnHuiOffsetY();
	// 根据文本框中的数值更新字格参数设置中保存的值
	void UpdateGridSize(void);
	afx_msg void OnViewTaskpane();
	afx_msg void OnUpdateViewTaskpane(CCmdUI *pCmdUI);

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	// 从注册表中加载配置
	void LoadSetting(void);
	// 将格子、字符和页面配置保存到注册表中
	void SaveSetting(void);
	// 设置状态条信息，主要是设置打印预览时的页码和页数信息
	void SetStatusInfor(LPCTSTR inf);
	afx_msg void OnOwnerDrawGrid();
	afx_msg void OnUpdateOwnerDrawGrid(CCmdUI *pCmdUI);
	afx_msg void OnOpenImg();
	afx_msg void OnEditImg();
	afx_msg void OnSaveImg();
	afx_msg void OnUpdateSaveImg(CCmdUI *pCmdUI);
	afx_msg void OnOwnerDrawPreview();
//	afx_msg void OnUpdateOwnerdrawpreview(CCmdUI *pCmdUI);
	// 创建新位图，作为自绘格子，可以进一步修改。
	void CreateOwnerDrawBmp(CBitmap * pBmp);
	afx_msg void OnOwnerDrawBackground();
	// 取得自绘格子的图像
	CImage * GetOwnGridImg(void);
	// 指示是否重新计算页码及页数等信息
	BOOL m_bRecalcPage;


};


