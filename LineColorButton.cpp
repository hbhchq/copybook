// LineColorButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���ֹ���.h"
#include "LineColorButton.h"


// CLineColorButton

IMPLEMENT_DYNCREATE(CLineColorButton, CMFCRibbonColorButton)

CLineColorButton::CLineColorButton(UINT nID, COLORREF color,CSize size)
:CMFCRibbonColorButton(nID,NULL,FALSE,-1,-1)
,m_size(size)
{
	SetDefaultCommand(0);
	

}

CLineColorButton::~CLineColorButton()
{
}




// CLineColorButton ��Ϣ�������


