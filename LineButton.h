#pragma once


// CLineButton

class CLineButton : public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CLineButton)

public:
	CLineButton();
	CLineButton(UINT uID,int penStyle=PS_SOLID,int lineWidth=1,COLORREF lineColor=RGB(0,0,0),CLineButton * parentBtn=NULL,CSize size=CSize(160,35));

	virtual ~CLineButton();
	virtual void CopyFrom (const CMFCRibbonBaseElement& s);
	virtual BOOL HasMenu() const 
	{ 
		return this->GetSubItems().GetCount()>0;
	}
	virtual void OnDraw(CDC* pDC);

	virtual void OnClick(CPoint point)
	{
		CString inf;
		inf.Format(L"Onclick,linewidth: %d,check: %d\n",this->GetLineWidth(),this->GetCheck());
		TRACE(inf);
		//取父元素
		CLineButton * parent=this->GetTopParentButton();
		if(parent)
		{
			parent->SetPen(this->m_nPenStyle,m_nLineWidth,m_nColor);
			this->SetCheck();
		}
		CMFCRibbonButton::OnClick(point);
	}



	virtual void OnShowPopupMenu()
	{
		ASSERT_VALID(this);

		if (IsDroppedDown())
		{
			// if the button already has a menu, don't create another one!
			return;
		}

		CWnd* pWndParent = GetParentWnd();
		if (pWndParent->GetSafeHwnd() == NULL)
		{
			ASSERT(FALSE);
			return;
		}

		CMFCRibbonBar* pTopLevelRibbon = GetTopLevelRibbonBar();
		if (pTopLevelRibbon->GetSafeHwnd() == NULL)
		{
			ASSERT(FALSE);
			return;
		}

		CMFCRibbonBaseElement::OnShowPopupMenu();

		const BOOL bIsRTL = (pTopLevelRibbon->GetExStyle() & WS_EX_LAYOUTRTL);

		CWnd* pWndOwner = pTopLevelRibbon->GetSafeOwner();

		if (m_arSubItems.GetSize() > 0)
		{
			if (m_bIsWindowsMenu)
			{
				FillWindowList();
			}

			//--------------------------------
			// Build popup menu from subitems:
			//--------------------------------
			CMFCRibbonPanelMenu* pMenu = new CMFCRibbonPanelMenu(pTopLevelRibbon, m_arSubItems);

			pMenu->SetParentRibbonElement(this);

			pMenu->SetMenuMode(0);

			BOOL bIsPopupDefaultMenuLook = IsPopupDefaultMenuLook();

			for (int i = 0; bIsPopupDefaultMenuLook && i < m_arSubItems.GetSize(); i++)
			{
				ASSERT_VALID(m_arSubItems [i]);

				if (!m_arSubItems [i]->IsDefaultMenuLook())
				{
					bIsPopupDefaultMenuLook = FALSE;
				}
			}

			pMenu->SetDefaultMenuLook(bIsPopupDefaultMenuLook);

			if (m_pOriginal != NULL && m_pOriginal->GetParentPanel() != NULL && m_pOriginal->GetParentPanel()->IsMainPanel())
			{
				pMenu->SetDefaultMenuLook(FALSE);
			}

			CRect rectBtn = GetRect();
			pWndParent->ClientToScreen(&rectBtn);

			int x = m_bRightAlignMenu || bIsRTL ? rectBtn.right : rectBtn.left;

			int y = rectBtn.bottom;

			if (m_bCreatedFromMenu && m_bRightAlignMenu && !bIsRTL)
			{
				pMenu->SetRightAlign();
			}

			if (IsMenuMode())
			{
				x = bIsRTL ? rectBtn.left : rectBtn.right;
				y = rectBtn.top;
			}

			CRect rectMenuLocation;
			rectMenuLocation.SetRectEmpty();

			CMFCRibbonPanel* pPanel = GetParentPanel();

			if (pPanel != NULL &&
				pPanel->GetPreferedMenuLocation(rectMenuLocation))
			{
				pWndParent->ClientToScreen(&rectMenuLocation);

				x = bIsRTL ? rectMenuLocation.right : rectMenuLocation.left;
				y = rectMenuLocation.top;

				pMenu->SetPreferedSize(rectMenuLocation.Size());
				pMenu->SetDefaultMenuLook(FALSE);
			}

			pMenu->Create(pWndOwner, x, y, (HMENU) NULL);

			SetDroppedDown(pMenu);

			return;
		}


	}





	virtual CSize GetRegularSize(CDC* pDC )
	{
		return m_size;
	}
	virtual CSize GetImageSize(RibbonImageType type) const
	{
		return IsQATMode()?CSize(48,15):CSize(0,0);
	}

	void SetCheck(BOOL bCheck=1){this->m_bChecked=bCheck;/*Redraw();*/}
	//设置按钮尺寸
	void SetSize(CSize & size)
	{	
		m_size=size;
	}
	void SetPen(int penStyle,int width,COLORREF color)
	{
		m_nPenStyle=penStyle;
		m_nLineWidth=width;
		m_nColor=color;
		this->Redraw();	
	}
protected:
	//线类型，默认为PS_SOLID
	int m_nPenStyle;
	//线宽度
	int m_nLineWidth;
	//线颜色
	COLORREF m_nColor;
	//按钮大小
	CSize m_size;
	//顶端父按钮，即显示在窗口界面中的按钮
	CLineButton * m_pTopParentButton;
	BOOL m_bChecked;
	//DECLARE_MESSAGE_MAP()
public:
	int GetPenStyle() const{return m_nPenStyle;}
	int GetLineWidth(){return m_nLineWidth;}
	int GetColor() {return m_nColor;}
	BOOL GetCheck() const{return this->m_bChecked;}
	void SetColor(COLORREF color){SetPen(this->m_nPenStyle,m_nLineWidth ,color);}
	CLineButton * GetTopParentButton() const{return this->m_pTopParentButton;}
	void SetTopParentButton(CLineButton * pBtn)
	{
		this->m_pTopParentButton=pBtn;
	}
};


