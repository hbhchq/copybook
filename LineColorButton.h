#pragma once


// CLineColorButton

class CLineColorButton : public CMFCRibbonColorButton
{
	DECLARE_DYNCREATE(CLineColorButton)
protected:
	CSize m_size;
public:
	CLineColorButton():CMFCRibbonColorButton(){}
	CLineColorButton(UINT nID, COLORREF color = RGB(0, 0, 0),CSize size=CSize(160,35));
	virtual ~CLineColorButton();
	virtual CSize GetRegularSize(CDC* pDC )
	{
		return this->m_size;
	}

	virtual void OnDraw(CDC* pDC)
	{

		CMFCRibbonColorButton::OnDraw(pDC);
		if(IsQATMode())return;
		CRect rc=this->GetRect();		
		rc.DeflateRect(6,5,20,5);
		//减图像尺寸
		rc.left+=this->GetImageSize(RibbonImageSmall).cx+2;
		CBrush brs(this->GetColor());
		pDC->FillRect(&rc,&brs);		

	}
	//virtual void DrawImage(CDC* pDC, RibbonImageType type, CRect rectImage)
	//{
	//	CMFCRibbonButton::DrawImage( pDC, type,  rectImage);
	//	//加一虚、一实两条两条按颜色画出的线条
	//	CPen pen(PS_SOLID,2,this->GetColor());
	//	CPen * oldPen=pDC->SelectObject(&pen);
	//	pDC->MoveTo(rectImage.left,rectImage.bottom-this->m_szMargin.cy-3);
	//	pDC->LineTo(rectImage.right,rectImage.bottom-this->m_szMargin.cy-3);
	//	CPen pen2(PS_DASHDOT,2,this->GetColor());
	//	pDC->SelectObject(&pen2);
	//	pDC->MoveTo(rectImage.left,rectImage.bottom-this->m_szMargin.cy+2);
	//	pDC->LineTo(rectImage.right,rectImage.bottom-this->m_szMargin.cy+2);
	//	pDC->SelectObject(oldPen);

	//}

	virtual void CopyFrom(const CMFCRibbonBaseElement& src)
	{
		CMFCRibbonColorButton::CopyFrom(src);
		CLineColorButton & s=(CLineColorButton &)src;
		this->m_size=s.m_size;
	}

};


