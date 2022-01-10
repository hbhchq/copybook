// LineButton.cpp : 实现文件
//

#include "stdafx.h"
#include "LineButton.h"

// CLineButton

IMPLEMENT_DYNCREATE(CLineButton, CMFCRibbonButton)
CLineButton::~CLineButton()
{
}
CLineButton::CLineButton()
:CMFCRibbonButton()
{
}


CLineButton::CLineButton(UINT uID,int penStyle,int lineWidth,COLORREF lineColor,CLineButton * parentBtn,CSize size)
:CMFCRibbonButton(uID,_T(""))
,m_nPenStyle(penStyle)
,m_nLineWidth(lineWidth)
,m_nColor(lineColor)
,m_size(size)
,m_pTopParentButton(parentBtn)
,m_bChecked(FALSE)
//,m_bIsDefaultCommand(0),m_bIsDefaultMenuLook(0)
{
	SetDefaultCommand(0);
	SetDefaultMenuLook(0);

}

void CLineButton::OnDraw(  CDC* pDC)
{

	CMFCRibbonButton::OnDraw(pDC);
	
	CRect rc=this->GetRect();
	
		if(HasMenu())	
		{
			rc.DeflateRect(10,0,20,0);
		}
		else
		{
			rc.DeflateRect(15,0,14,0);
		}
	if(IsQATMode())
	{rc.InflateRect(5,0);	}
	CPoint pt(rc.CenterPoint());
	CPen pen(m_nPenStyle,m_nLineWidth,m_nColor);
	CPen * oldPen=pDC->SelectObject(&pen);
	
	pDC->MoveTo(IsChecked ()?rc.left+10:rc.left,pt.y);

	pDC->LineTo(rc.right,pt.y);	
	pDC->SelectObject(oldPen);
	
	

}


void CLineButton::CopyFrom (const CMFCRibbonBaseElement& s)
{
	CMFCRibbonButton::CopyFrom(s);	
	CLineButton & src=(CLineButton &)s;
	this->m_nPenStyle=src.m_nPenStyle;
	this->m_nLineWidth=src.m_nLineWidth;
	this->m_nColor=src.m_nColor;
	this->m_size=src.m_size;
	this->m_bChecked=src.m_bChecked;
	this->m_pTopParentButton=src.m_pTopParentButton;
}




//BEGIN_MESSAGE_MAP(CLineButton, CMFCRibbonButton)
//END_MESSAGE_MAP()



// CLineButton 消息处理程序


