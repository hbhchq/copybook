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
		//�����ǩ�ĳ���,����λ���ֵĳ���()
		CRect rc;
		pDC->DrawText(m_strText,&rc,DT_CALCRECT|DT_NOPREFIX|DT_SINGLELINE|DT_NOCLIP);
		////�������λ����ʾ�ߴ�
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
		//�������ǩ����
		pDC->DrawText(inf,&m_rect,DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE|DT_NOCLIP);
		CMFCRibbonSlider::OnDraw(pDC);	

	}

	virtual void OnAfterChangeRect(CDC* pDC)
	{
		ASSERT_VALID(this);
		CMFCRibbonSlider::OnAfterChangeRect(pDC);
		//�����ռ�
		int margin=m_rect.Width()-m_rectSlider.Width();
		//�����ǩ��ռ������
		CRect rc(m_rect);
		pDC->DrawText(m_strText,&rc,DT_CALCRECT|DT_NOPREFIX|DT_SINGLELINE);
		////�������λ����ʾ�ߴ�
		//CString infPos;
		//infPos.Format(L"%d",this->m_nMax);
		//CSize pos=pDC->GetTextExtent(infPos);	
		//���������λ��
		int x=m_rect.left+rc.Width()/*+pos.cx*/;
		m_rectSlider.MoveToX(x);
		m_rectSlider.right=rc.right+m_nWidth;
		//����һ����
		m_rectSlider.DeflateRect(margin/2,0);
		SetThumbRect();	

	}

	virtual void OnLButtonUp(CPoint point)
	{		
		CMFCRibbonSlider::OnLButtonUp(point);
		//���ҿ��ٷ��ʹ������İ�ť��ʵ��ͬ�����»���
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
	//���¶��巶Χ����Ҫ��Ϊ�˿��ٷ��ʹ�������Ԫ��ͬ����ʾ
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


