#pragma once


// CFontColorButton

class CFontColorButton : public CMFCRibbonColorButton
{
	DECLARE_DYNCREATE(CFontColorButton)
protected:
	CSize m_size;
	CString m_label;
public:
	CFontColorButton();
	CFontColorButton(UINT nID,LPCTSTR strText,COLORREF color=RGB(255,0,0),CSize size=CSize(0,0));
	virtual ~CFontColorButton();
	virtual CSize GetImageSize(RibbonImageType type) const
	{
		return CSize(16,16);
	}
virtual CSize GetRegularSize(CDC* pDC )
	{ 
		//CSize sz=CMFCRibbonColorButton::GetRegularSize(pDC);
		//sz.cx+=sz.cy;
		//return sz;
		//计算标签尺寸
		CSize sz=pDC->GetOutputTextExtent(m_label);
		//sz.cx+=10;sz.cy+=3;
		sz.cx+=m_szMargin.cx*2;
		sz.cy+=m_szMargin.cy*2;
		//加上前面颜色块的尺寸
		sz.cx+=sz.cy;
		//////if(HasMenu())sz.cx+=20;		
		CSize retSz(max(sz.cx,m_size.cx),max(sz.cy,m_size.cy));
		return retSz;
	}

virtual void DrawImage(CDC* pDC, RibbonImageType type, CRect rectImage)
{
	//CMFCRibbonButton::DrawImage(pDC,type,rectImage);

	CBrush brs(this->GetColor());
	CRect rc(rectImage);
	rc.OffsetRect(m_rect.left-rc.left+3,-3);
	rc.bottom=this->m_rect.bottom;
	DWORD oldColor=pDC->GetTextColor();
	pDC->SetTextColor(this->GetColor());
	////pDC->FrameRect(&rc,NULL);
	pDC->DrawText(L"A",&rc,DT_CENTER|DT_TOP/*|DT_SINGLELINE*/);
	pDC->SetTextColor(oldColor);
	//下面画一颜色块
	rc.top=rc.bottom-9;
	rc.bottom=rc.top+7;
	if(type==RibbonImageType::RibbonImageSmall)
	{
		rc.DeflateRect(0,2);
	}
	pDC->FillRect(&rc,&brs);
}

//virtual int DrawRibbonText(CDC* pDC, const CString& strText, CRect rectText, UINT uiDTFlags, COLORREF clrText = (COLORREF)-1)
//{
//	//改用自定义的颜色绘制文本
//	return CMFCRibbonButton::DrawRibbonText(pDC,strText,rectText,uiDTFlags,GetColor()/*clrText*/);
//}

	virtual void OnDraw(CDC* pDC)
	{
		CMFCRibbonColorButton::OnDraw(pDC);
		if(this->IsQATMode())return ;
		CRect rc=this->GetRect();		
		rc.DeflateRect(4,3,15,3);
		//CBrush brs(this->GetColor());
		CRect rcBox(rc.left,rc.top,rc.left+rc.Height(),rc.bottom);
		//pDC->FillRect(&rcBox,&brs);
		//按颜色输出按钮文字
		//DWORD oldColor=pDC->GetTextColor();
		//pDC->SetTextColor(this->GetColor());
		//CRect rcTxt(rc.right+1,rc.top,this->GetRect().right-20,rc.bottom);
		//pDC->DrawText(this->m_label,&rcTxt,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		pDC->TextOutW(rcBox.right+3,rc.top-2,m_label);
		//pDC->SetTextColor(oldColor);

	}

	virtual void CopyFrom(const CMFCRibbonBaseElement& src)
	{
		CMFCRibbonColorButton::CopyFrom(src);
		CFontColorButton & s=(CFontColorButton &)src;
		this->m_size=s.m_size;
		m_label=s.m_label;
	}

};


