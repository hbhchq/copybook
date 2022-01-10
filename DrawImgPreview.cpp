#include "StdAfx.h"
#include "DrawImgPreview.h"


IMPLEMENT_DYNCREATE(CDrawImgPreview, CMFCRibbonButton)


CDrawImgPreview::CDrawImgPreview(UINT nID)
:CMFCRibbonButton(nID,NULL)
{
}
CDrawImgPreview::CDrawImgPreview(UINT nID,CString strFile)
:CMFCRibbonButton(nID,NULL),m_strImgFile(strFile)
{
	m_Image.Load(strFile);
}

CDrawImgPreview::~CDrawImgPreview(void)
{
	m_Image.Destroy();
}
