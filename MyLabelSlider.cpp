// MyLabelSlider.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���ֹ���.h"
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


