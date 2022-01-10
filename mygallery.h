class CMyGallery:public CMFCRibbonGallery
{
public :
	DECLARE_DYNCREATE(CMyGallery)
	CMyGallery():CMFCRibbonGallery()
	{
		//m_nPanelColumns=7;
	}
	CMyGallery(UINT nID, LPCTSTR lpszText, int nSmallImageIndex, int nLargeImageIndex, UINT uiImagesPaletteResID = 0, int cxPaletteImage = 0)
		:CMFCRibbonGallery( nID,  lpszText,  nSmallImageIndex,  nLargeImageIndex,  uiImagesPaletteResID , cxPaletteImage )
	{
		//m_nPanelColumns=7;
	}
	virtual ~CMyGallery()
	{
		/*~CMFCRibbonGallery();*/
	}
	virtual CSize GetRegularSize(CDC* pDC)
	{
		CSize ret= CMFCRibbonGallery::GetRegularSize(pDC);
		CSize sz=GetIconSize();
		//默认为6个图标的大小,改为自己的图标个数的大小目前设为5个显示
		//4为图标之间的空白
		ret.cx-=sz.cx-4/*nImageMargin*/;
		return ret;
	}
	virtual void OnDrawPaletteIcon(CDC* pDC, CRect rectIcon, int nIconIndex, CMFCRibbonGalleryIcon* pIcon, COLORREF clrText)
	{
		CMFCRibbonGallery::OnDrawPaletteIcon(pDC,rectIcon,nIconIndex,pIcon,clrText);
		//因为在英文操作系统下没有钩字符显示，不用特别绘制
		////int selIdx=CMFCRibbonGallery::GetSelectedItem();
		//////如果是选中的种类，左上角画一钩"√"
		////if(selIdx==nIconIndex)
		////{
		////	CRect rc(rectIcon);
		////	//rc.DeflateRect(10,10);
		////	CFont font;
		////	HGDIOBJ hSysFont =::GetStockObject(SYSTEM_FONT);
		////	font.Attach(hSysFont);
		////	LOGFONT logFont;
		////	font.GetLogFont(&logFont);
		////	font.Detach();
		////	::DeleteObject(hSysFont);
		////	font.CreatePointFont(logFont.lfHeight*12/*200*/,logFont.lfFaceName/*L"system"*/,pDC);
		////	pDC->SetTextColor(/*afxGlobalData.clrBtnHilite*/RGB(255,0,0));
		////	CGdiObject *oldGDI= pDC->SelectObject(&font);
		////	TCHAR ch=L'√';
		////	pDC->TextOutW(rc.CenterPoint().x,rc.CenterPoint().y,&ch,1);
		////	pDC->SelectObject(oldGDI);		

		////}
	}
	virtual void OnClickPaletteIcon(CMFCRibbonGalleryIcon * pIcon)
	{
		CMFCRibbonGallery::OnClickPaletteIcon(pIcon);
		//若存在快速访问工具栏的按钮，实现同步更新绘制
		CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
		this->GetTopLevelRibbonBar()->GetElementsByID(m_nID,arrBtn);
		for(int n=0;n<arrBtn.GetCount();n++)
		{
			if(arrBtn.GetAt(n)!=NULL&&arrBtn[n]!=this)
			{//另一个副本对象,
				CMyGallery* cpy=(CMyGallery*)arrBtn[n];					
				if(!cpy->IsQATMode())
				{
					cpy->SelectItem(cpy->GetLastSelectedItem(cpy->GetID()));
					//cpy->Redraw();
				}
			}
		}
	}

};
