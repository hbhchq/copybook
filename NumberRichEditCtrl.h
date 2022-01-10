#pragma once
#include "MsgBox.h"


//class CMsgBox;
//��������Ribbon�ؼ��еĿؼ�����
class CNumberRichEditCtrl : public CMFCRibbonRichEditCtrl
{
	friend class CNumberEdit;


// Construction
public:
	CNumberRichEditCtrl(CMFCRibbonEdit& edit)
		:CMFCRibbonRichEditCtrl(edit)
	{}
	//�����ַ����룬ֻ������������
	afx_msg void OnChar( UINT nChar,  UINT nRepCnt,  UINT nFlags  );
	//������ݴ������õ������Сֵ����ָ�����ǰ����ֵ
	afx_msg void OnChange();

// Overrides
public:
		//////���˵�ճ������
		////virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg LRESULT OnPaste(WPARAM, LPARAM);
protected:
	//{{AFX_MSG(CMFCRibbonRichEditCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//����һ����עʽ��Ϣ��ʾ����
	CMsgBox m_wndMsg;

public:
	static BOOL IsNumber(LPSTR str);
//	afx_msg void OnUniChar(UINT Char, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnSetfocus();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};