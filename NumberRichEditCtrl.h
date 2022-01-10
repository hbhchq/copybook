#pragma once
#include "MsgBox.h"


//class CMsgBox;
//被包含在Ribbon控件中的控件窗口
class CNumberRichEditCtrl : public CMFCRibbonRichEditCtrl
{
	friend class CNumberEdit;


// Construction
public:
	CNumberRichEditCtrl(CMFCRibbonEdit& edit)
		:CMFCRibbonRichEditCtrl(edit)
	{}
	//过滤字符输入，只接受数字输入
	afx_msg void OnChar( UINT nChar,  UINT nRepCnt,  UINT nFlags  );
	//如果数据大于设置的最大最小值，则恢复到以前的老值
	afx_msg void OnChange();

// Overrides
public:
		//////过滤掉粘贴功能
		////virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg LRESULT OnPaste(WPARAM, LPARAM);
protected:
	//{{AFX_MSG(CMFCRibbonRichEditCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//定义一个标注式消息提示窗口
	CMsgBox m_wndMsg;

public:
	static BOOL IsNumber(LPSTR str);
//	afx_msg void OnUniChar(UINT Char, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnSetfocus();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};