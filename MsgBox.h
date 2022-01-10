#pragma once


// CMsgBox

class CMsgBox : public CWnd
{
	DECLARE_DYNAMIC(CMsgBox)

public:
	CMsgBox():CWnd(){}
	//窗口的构造函数，ptTarget，目标，箭头指向位置
	//ptBegin字符显示部分窗口（圆角矩形区域）的起始位置
	CMsgBox(LPCTSTR msg,CPoint ptTarget,CPoint ptBegin);
	void Set(LPCTSTR msg,CPoint ptTarget,CPoint ptBegin);
	void SetMessage(LPCTSTR msg){this->m_strMessage=msg;}
	void SetPosition(CPoint ptTarget,CPoint ptBegin)
	{
		m_ptTarget=(ptTarget);
		m_ptBegin=(ptBegin);
	}

	virtual ~CMsgBox();
	CString m_strMessage;
	//均为屏幕坐标系
	CPoint m_ptTarget;
	CPoint m_ptBegin;
protected:
	DECLARE_MESSAGE_MAP()
	//窗口的区域
	CRgn m_rgn;
	//文字消息显示的矩形区域
	CRect m_rect;
	//计算消息窗口的显示区域，是一个不规则的图形
	void CalcWindowRgn();
public:
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//显示消息窗口
	void ShowMessage(BOOL bShow=TRUE);
protected:
	////virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL CreateWnd();
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


