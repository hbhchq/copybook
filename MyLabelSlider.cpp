// MyLabelSlider.cpp : 实现文件
//

#include "stdafx.h"
#include "练字工具.h"
#include "MyLabelSlider.h"


// CMyLabelSlider

IMPLEMENT_DYNCREATE(CMyLabelSlider, CMFCRibbonSlider)

CMyLabelSlider::CMyLabelSlider()
:CMFCRibbonSlider()
{

}
CMyLabelSlider::CMyLabelSlider(UINT nID,LPCTSTR label,int width)
:CMFCRibbonSlider(nID,width)
{
	m_strText=label;
	
}


CMyLabelSlider::~CMyLabelSlider()
{
}


