#pragma once

//类型前置申明
////class CMainFrame;
////class  CMyView;
// CSampleWnd
class CSampleWnd : public CWnd
{
	DECLARE_DYNAMIC(CSampleWnd)

protected:
	BOOL m_bZoom;
public:
	CSampleWnd();
	virtual ~CSampleWnd();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DrawSample(CDC * pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


