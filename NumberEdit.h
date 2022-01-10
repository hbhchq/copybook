#pragma once

#include "NumberRichEditCtrl.h"


// CNumberEdit

class CNumberEdit : public CMFCRibbonEdit
{
	friend class CNumberRichEditCtrl;
	DECLARE_DYNCREATE(CNumberEdit)
public:
	//最大值范围，即使手工输入也不能超过
	int m_nMaxVal;
	//最小值范围，即使手工输入也不能超过
	int m_nMinVal;


public:
	CNumberEdit();
	CNumberEdit(UINT nID, int nWidth, LPCTSTR lpszLabel = NULL,int nImg=-1)
		:CMFCRibbonEdit(nID,  nWidth, lpszLabel ,  -1)
		,m_nMaxVal(INT_MAX),m_nMinVal(INT_MIN)
	{
	}
	virtual BOOL CanBeAddedToQuickAccessToolBar() const{return FALSE;}
	//自定义的设置最大，最小值的函数
	void SetMax(int val)
	{
		SetMinMax(m_nMinVal,val);
	}
	void SetMin(int val)
	{		
		SetMinMax(val,m_nMaxVal);
	}
	void SetMinMax(int min,int max)
	{
		m_nMinVal=min;
		m_nMaxVal=max;
		SyncScope();
	}
	void EnableSpinButtons(int nMin, int nMax)
	{
		CMFCRibbonEdit::EnableSpinButtons(nMin, nMax);
		CMFCRibbonBar* pBar=this->GetTopLevelRibbonBar();
		if(pBar)
		{
			CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
			pBar->GetElementsByID(m_nID,arrBtn);
			for(int n=0;n<arrBtn.GetCount();n++)
			{
				CMFCRibbonEdit * p=(CMFCRibbonEdit *)arrBtn[n];
				if(p!=NULL&&p!=this)
				{
					p->EnableSpinButtons(nMin,nMax);
				}
			}
		}
	}

	////根据CSize结构来设置最大最小值
	//void SetScopeBySize(CSize & sz)
	//{
	//	m_nMinVal=sz.cx<=sz.cy?sz.cx:sz.cy;
	//	m_nMaxVal=sz.cx>=sz.cy?sz.cx:sz.cy;
	//}
	//获取编辑框控件
	CRichEditCtrl * GetEditCtrl() const
	{
		return (CRichEditCtrl *)m_pWndEdit;
	}
	virtual CMFCRibbonRichEditCtrl* CreateEdit(CWnd* pWndParent, DWORD dwEditStyle)
	{
		dwEditStyle|=ES_NUMBER;
		//CMFCRibbonRichEditCtrl* ctrl= CNumberEdit::CreateEdit(pWndParent,dwEditStyle);
		ASSERT_VALID(this);
		ASSERT_VALID(pWndParent);

		CNumberRichEditCtrl/*CMFCRibbonRichEditCtrl*/* pWndEdit = new CNumberRichEditCtrl/*CMFCRibbonRichEditCtrl*/(*this);

		if (!pWndEdit->Create(dwEditStyle, CRect(0, 0, 0, 0), pWndParent, m_nID))
		{
			delete pWndEdit;
			return NULL;
		}

		if (m_bHasSpinButtons)
		{
			CreateSpinButton(pWndEdit, pWndParent);
		}

		return pWndEdit;
		
	}

	virtual void CopyFrom(const CMFCRibbonBaseElement& src)
	{
		CMFCRibbonEdit::CopyFrom(src);
		CNumberEdit & s=(CNumberEdit &)src;
		this->m_nMaxVal=s.m_nMaxVal;
		this->m_nMinVal=s.m_nMinVal;
	}	

private:
	//主要是可能有快速访问工具栏时，同步更新
	void SyncScope(void)
	{
		CMFCRibbonBar* pBar=this->GetTopLevelRibbonBar();
		if(pBar)
		{
			CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
			pBar->GetElementsByID(m_nID,arrBtn);
			for(int n=0;n<arrBtn.GetCount();n++)
			{
				CNumberEdit * p=(CNumberEdit *)arrBtn[n];
				if(p!=NULL&&p!=this)
				{

					p->m_nMinVal=this->m_nMinVal;
					p->m_nMaxVal=this->m_nMaxVal;
				}
			}
		}

	}

};





