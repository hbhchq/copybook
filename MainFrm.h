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

// MainFrm.h : CMainFrame ��Ľӿ�
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
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:
	void UpdateMRUFilesList ()
	{
		m_wndTaskPane.UpdateMRUFilesList();
	}
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CTaskPane			m_wndTaskPane;

// ���ɵ���Ϣӳ�亯��
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
	//ȡ��ribbonbar
	CMFCRibbonBar & GetRibbonBar()const {return (CMFCRibbonBar &) this->m_wndRibbonBar;}
	// ���Ӹ��ӿ��ߵ���ʽ
	void AddGridStyle(void);
	// �������ָ�ʽ
	void AddCharStyle(void);
	//����ҳ�沼�֣���ҳ�߾࣬���ַ��򣬾��е�
	void AddPageLayout(void );
	//���ӻ��ָ������
	void AddHUIGridStyle();
	//�����Ի���ӵ�����
	void AddOwnerDrawPage();
	//������ʽ
	CGridStyle m_gridStyle;
	//�ַ���ʽ
	CCharStyle m_charStyle;
	//ҳ�沼�ּ����ַ���
	CPageLayout m_pageLayout;
public:
	//ȡ��ҳ�߾�
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
	// ��ȡ��ǰʹ�õĴ�ӡ����ֽ�Ŵ�С,�Ժ���Ϊ��λ
	CSize GetPaperSize(void);
	afx_msg void OnPaperLandscape();
	afx_msg void OnPaperPortrait();
	afx_msg void OnUpdatePaperPortrait(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePaperLandscape(CCmdUI *pCmdUI);
	// ���ı���ֽ�ŷ�����޸Ĵ�ӡ��ֽ�����ã��޸�ҳ��߾༰��Ӧ�����ô�С��Χ
	void ModifyPageMargin(BOOL bLandscape);
	//��д���ݸ��µĺ�������Ҫ�ǵ��޸������ã���ֱ�ӵ����ӡ��Ԥ��ǰ����
		void UpdateData();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	// �ж�һ������������ID�Ƿ��ڱ�ǩ��
	BOOL CmdInRibbonTab(UINT id, BOOL bVisibleOnly=TRUE);
	// �Ը����ָ��С��ҳ����������ý���У��
	bool ValidSetting(CSize szPage);
	afx_msg void OnCharOffsetY();
	afx_msg void OnHuiInOutRate();
	afx_msg void OnHuiWHRate();
	afx_msg void OnHuiOffsetY();
	// �����ı����е���ֵ�����ָ���������б����ֵ
	void UpdateGridSize(void);
	afx_msg void OnViewTaskpane();
	afx_msg void OnUpdateViewTaskpane(CCmdUI *pCmdUI);

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	// ��ע����м�������
	void LoadSetting(void);
	// �����ӡ��ַ���ҳ�����ñ��浽ע�����
	void SaveSetting(void);
	// ����״̬����Ϣ����Ҫ�����ô�ӡԤ��ʱ��ҳ���ҳ����Ϣ
	void SetStatusInfor(LPCTSTR inf);
	afx_msg void OnOwnerDrawGrid();
	afx_msg void OnUpdateOwnerDrawGrid(CCmdUI *pCmdUI);
	afx_msg void OnOpenImg();
	afx_msg void OnEditImg();
	afx_msg void OnSaveImg();
	afx_msg void OnUpdateSaveImg(CCmdUI *pCmdUI);
	afx_msg void OnOwnerDrawPreview();
//	afx_msg void OnUpdateOwnerdrawpreview(CCmdUI *pCmdUI);
	// ������λͼ����Ϊ�Ի���ӣ����Խ�һ���޸ġ�
	void CreateOwnerDrawBmp(CBitmap * pBmp);
	afx_msg void OnOwnerDrawBackground();
	// ȡ���Ի���ӵ�ͼ��
	CImage * GetOwnGridImg(void);
	// ָʾ�Ƿ����¼���ҳ�뼰ҳ������Ϣ
	BOOL m_bRecalcPage;


};


