// NuberEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "练字工具.h"
#include "NumberEdit.h"

// CNumberEdit

IMPLEMENT_DYNCREATE(CNumberEdit, CMFCRibbonEdit)

CNumberEdit::CNumberEdit()
:CMFCRibbonEdit(),m_nMaxVal(INT_MAX),m_nMinVal(INT_MIN)
{
	
}




