// FontColorButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���ֹ���.h"
#include "FontColorButton.h"


// CFontColorButton

IMPLEMENT_DYNCREATE(CFontColorButton, CMFCRibbonColorButton)

CFontColorButton::CFontColorButton()
:CMFCRibbonColorButton()
{

}
CFontColorButton::CFontColorButton(UINT nID,LPCTSTR strText,COLORREF color,CSize size)
:CMFCRibbonColorButton(nID,L""/*strText*/,-1,color)
,m_size(size),m_label(strText)
{
	SetDefaultCommand(0);

}

CFontColorButton::~CFontColorButton()
{
}





