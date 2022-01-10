#pragma once


// CMsgBox

class CMsgBox : public CWnd
{
	DECLARE_DYNAMIC(CMsgBox)

public:
	CMsgBox():CWnd(){}
	//���ڵĹ��캯����ptTarget��Ŀ�꣬��ͷָ��λ��
	//ptBegin�ַ���ʾ���ִ��ڣ�Բ�Ǿ������򣩵���ʼλ��
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
	//��Ϊ��Ļ����ϵ
	CPoint m_ptTarget;
	CPoint m_ptBegin;
protected:
	DECLARE_MESSAGE_MAP()
	//���ڵ�����
	CRgn m_rgn;
	//������Ϣ��ʾ�ľ�������
	CRect m_rect;
	//������Ϣ���ڵ���ʾ������һ���������ͼ��
	void CalcWindowRgn();
public:
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//��ʾ��Ϣ����
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


