#pragma once


// CMyLabelSlider

class CMyLabelSlider : public CMFCRibbonSlider
{
	DECLARE_DYNCREATE(CMyLabelSlider)



public:	
	CMyLabelSlider();
	CMyLabelSlider(UINT nID,LPCTSTR label,int width=100);
	virtual ~CMyLabelSlider();

	virtual CSize GetRegularSize(CDC* pDC )
	{
		CSize sz=CMFCRibbonSlider::GetRegularSize(pDC);
		//计算标签的长度,加五位数字的长度()
		CRect rc;
		pDC->DrawText(m_strText,&rc,DT_CALCRECT|DT_NOPREFIX|DT_SINGLELINE|DT_NOCLIP);
		////计算出的位置显示尺寸
		//CString infPos;
		//infPos.Format(L"%d",this->m_nMax);
		//CSize pos=pDC->GetTextExtent(infPos);
		sz.cx+=rc.Width()/*+pos.cx*/;
		sz.cy=max(sz.cy,rc.Height()/2*3);
		
		return sz;
	}
	virtual void OnDraw(CDC * pDC)
	{
		CString inf;
		inf.Format(m_strText,this->GetPos());
		//先输入标签文字
		pDC->DrawText(inf,&m_rect,DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE|DT_NOCLIP);
		CMFCRibbonSlider::OnDraw(pDC);	

	}

	virtual void OnAfterChangeRect(CDC* pDC)
	{
		ASSERT_VALID(this);
		CMFCRibbonSlider::OnAfterChangeRect(pDC);
		//收缩空间
		int margin=m_rect.Width()-m_rectSlider.Width();
		//计算标签所占的区域
		CRect rc(m_rect);
		pDC->DrawText(m_strText,&rc,DT_CALCRECT|DT_NOPREFIX|DT_SINGLELINE);
		////计算出的位置显示尺寸
		//CString infPos;
		//infPos.Format(L"%d",this->m_nMax);
		//CSize pos=pDC->GetTextExtent(infPos);	
		//调整滑块的位置
		int x=m_rect.left+rc.Width()/*+pos.cx*/;
		m_rectSlider.MoveToX(x);
		m_rectSlider.right=rc.right+m_nWidth;
		//收缩一部分
		m_rectSlider.DeflateRect(margin/2,0);
		SetThumbRect();	

	}

	virtual void OnLButtonUp(CPoint point)
	{		
		CMFCRibbonSlider::OnLButtonUp(point);
		//查找快速访问工具栏的按钮，实现同步更新绘制
		CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
		this->GetTopLevelRibbonBar()->GetElementsByID(m_nID,arrBtn);
		for(int n=0;n<arrBtn.GetCount();n++)
		{
			if(arrBtn.GetAt(n)!=NULL&&arrBtn[n]!=this)
			{
				((CMFCRibbonSlider*)arrBtn[n])->SetPos(this->GetPos());
			}
		}
	
	}
	//重新定义范围，主要是为了快速访问工具栏的元素同步显示
	void SetRange(int min,int max)
	{
		CMFCRibbonSlider::SetRange(min,max);
		CMFCRibbonBar* pBar=this->GetTopLevelRibbonBar();
		if(pBar)
		{
			CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
			pBar->GetElementsByID(m_nID,arrBtn);
			for(int n=0;n<arrBtn.GetCount();n++)
			{
				CMFCRibbonSlider * p=(CMFCRibbonSlider *)arrBtn[n];
				if(p!=NULL&&p!=this)
				{
					p->SetRange(min,max);
				}
			}
		}
	}
	void SetPos(int nPos, BOOL bRedraw = TRUE)
	{
		CMFCRibbonSlider::SetPos(nPos,bRedraw);
		CMFCRibbonBar* pBar=this->GetTopLevelRibbonBar();
		if(pBar)
		{
			CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
			pBar->GetElementsByID(m_nID,arrBtn);
			for(int n=0;n<arrBtn.GetCount();n++)
			{
				CMFCRibbonSlider * p=(CMFCRibbonSlider *)arrBtn[n];
				if(p!=NULL&&p!=this)
				{
					p->SetPos(this->GetPos(),1);
				}
			}
		}
	}
	
};


