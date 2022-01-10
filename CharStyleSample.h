#pragma once
#include "setting.h"

// CCharStyleSample

class CCharStyleSample : public CMFCRibbonLabel
{
	DECLARE_DYNCREATE(CCharStyleSample)
protected:
	CSize m_size;
	COLORREF m_color;
	BOOL m_bHollow;
	CString m_label;
	BOOL m_bSolid;
	CString m_fontName;
	int m_nBold;//字符加粗显示,默认普通模式显示
public:
	COLORREF GetColor()const{return m_color;}
	void SetColor(COLORREF color) {m_color=color;Redraw();}
	void SetHollow(BOOL ho=TRUE){this->m_bHollow=ho;Redraw();}
	BOOL GetHollow()const {return m_bHollow;}
	void SetSolid(BOOL bSolid=TRUE){m_bSolid=bSolid;Redraw();}
	void SetFont(CString & fontName){this->m_fontName=fontName;Redraw();}
	void SetBold(int bold){this->m_nBold=bold;Redraw();}
	void SetCharStyle(CCharStyle &style)
	{
		this->m_color=style.m_color;
		m_bHollow=style.m_bHollow;
		m_bSolid=style.m_bSolid;
		m_fontName=style.m_fontName;
		m_nBold=style.m_weight;
		Redraw();
	}
public:
	CCharStyleSample();
	CCharStyleSample(LPCTSTR pszText,BOOL bHollow=FALSE,COLORREF color=RGB(255,0,0),CSize size=CSize(250,80),BOOL bSolid=TRUE,CString fontName=L"system",int nBold=FW_NORMAL)
		:CMFCRibbonLabel (L""/*pszText*/)
		,m_size(size),m_color(color),m_bHollow(bHollow)
		,m_label(pszText),m_bSolid(bSolid)
		,m_fontName(fontName),m_nBold(nBold)
	{
		
	}
	virtual ~CCharStyleSample();

	virtual CSize GetRegularSize(CDC* pDC )
	{
		//CSize sz=CMFCRibbonButton::GetRegularSize(pDC);
		CSize sz=pDC->GetTextExtent(m_label);
		sz.cx+=15;sz.cy+=3;
		CSize retSz(max(sz.cx,m_size.cx),max(sz.cy,m_size.cy));
		return retSz;
	}
	virtual void OnDraw(CDC* pDC)
	{
		CMFCRibbonButton::OnDraw(pDC);
		CRect rc=this->GetRect();		
		//初始化字体
		CFont font;
		VERIFY(font.CreateFont(
			80,                        // nHeight,取绝对高度不要外部空白
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			m_nBold,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			DEFAULT_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			m_fontName)); 	
		CFont *oldFont=pDC->SelectObject(&font);
		//按颜色、是否为中空心字状态输出按钮文字		
		if(m_bHollow)
		{
			pDC->BeginPath();
			pDC->SetBkMode(TRANSPARENT);
			CPen pen(this->m_bSolid?PS_SOLID:PS_DOT,1,this->GetColor());
			////CPen pen(PS_SOLID,1,GetColor());
			CPen * oldPen=pDC->SelectObject(&pen);
			//pDC->TextOutW(rc.left,rc.top,this->m_label);	
			pDC->DrawText(this->m_label,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

			pDC->EndPath();
			pDC->StrokeAndFillPath();
			pDC->SelectObject(oldPen);
		}
		else
		{		
			DWORD oldColor=pDC->GetTextColor();
			pDC->SetTextColor(this->GetColor());
			//pDC->TextOutW(rc.left,rc.top,this->m_label);
			pDC->DrawText(this->m_label,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

			pDC->SetTextColor(oldColor);
		}
		pDC->SelectObject(oldFont);

	}

	virtual void CopyFrom(const CMFCRibbonBaseElement& src)
	{
		CMFCRibbonButton::CopyFrom(src);
		CCharStyleSample & s=(CCharStyleSample &)src;
		this->m_size=s.m_size;
		this->m_color=s.m_color;
		this->m_bHollow=s.m_bHollow;
		this->m_label=s.m_label;
		m_bSolid=s.m_bSolid;
		m_fontName=s.m_fontName;
		m_nBold=s.m_nBold;
	}
};


