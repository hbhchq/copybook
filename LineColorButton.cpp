// LineColorButton.cpp : 实现文件
//

#include "stdafx.h"
#include "练字工具.h"
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




// CLineColorButton 消息处理程序


