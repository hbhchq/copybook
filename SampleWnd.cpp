// SampleWnd.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "练字工具.h"
#include "SampleWnd.h"
#include "MainFrm.h"
////#include "练字工具View.h"
#include "TaskPane.h"


// CSampleWnd

IMPLEMENT_DYNAMIC(CSampleWnd, CWnd)

CSampleWnd::CSampleWnd()
:m_bZoom(TRUE)
{

}

CSampleWnd::~CSampleWnd()
{
}


BEGIN_MESSAGE_MAP(CSampleWnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
//	ON_WM_PAINT()
ON_WM_WINDOWPOSCHANGED()
ON_WM_PAINT()
ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CSampleWnd 消息处理程序



BOOL CSampleWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//return CWnd::OnEraseBkgnd(pDC);
	//建立白刷
	CBrush bru;
	bru.CreateStockObject(WHITE_BRUSH);
	CRect rc;this->GetClientRect(&rc);
	pDC->FillRect(&rc,&bru);
	return TRUE;
}

void CSampleWnd::DrawSample(CDC * pDC)
{
	CRect rc;this->GetWindowRect(&rc);
	if(rc.Height()<1||rc.Width()<1)return ;
	//因为所有的绘制函数在视图类CMyview中，直接发送消息请求绘制就行了
	//直接传窗口指针
	CFrameWnd *p=(CFrameWnd *)AfxGetMainWnd();
	if(p==NULL)return;
	CWnd *pWnd=p->GetActiveView();
	if(pWnd&&::IsWindow(pWnd->m_hWnd)&&pWnd->IsWindowVisible())
		pWnd->SendMessage(WM_DRAW_SAMPLE,(WPARAM)this);	
	//修改缩放标志
	m_bZoom=TRUE;
}

int CSampleWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CSampleWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//#ifdef _DEBUG
	if(m_bZoom)//放大
	{
		CRect rc;
		this->GetClientRect(&rc);
		CDC *pDC=this->GetDC();//当前窗口DC
		CDC &dc=*pDC;
		//放大2倍
		CDC   memDC;   
		CBitmap   memBit;                       
		memDC.CreateCompatibleDC(&dc);   
		memBit.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());   
		CBitmap   *pOldBit   =   memDC.SelectObject(&memBit); 
		memDC.BitBlt(0,0,rc.Width(),rc.Height(),pDC,0,0,SRCCOPY );
		CClientDC dcClient(this);
		//放大的区域
		CRect rcSrc(point,point);
		rcSrc.InflateRect(rc.Width()/2,rc.Height()/2);
		//将目标区域放大
		CRect rcDest(point,point);
		rcDest.InflateRect(rc.Width(),rc.Height());
		dcClient.StretchBlt(rcDest.left,rcDest.top,rcDest.Width(),rcDest.Height(),&memDC,rcSrc.left,rcSrc.top,rcSrc.Width(),rcSrc.Height(),SRCCOPY );
		memDC.SelectObject(pOldBit);
		m_bZoom=FALSE;

		
	}
	else
	{
		Invalidate();
		m_bZoom=TRUE;
	}
//#endif
	CWnd::OnLButtonDown(nFlags, point);
}


void CSampleWnd::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CWnd::OnWindowPosChanged(lpwndpos);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CRect rcPane;
	CTaskPane * pParent=(CTaskPane * )this->GetParent();
	pParent->GetWindowRect(&rcPane);
	int space=rcPane.bottom-rcWnd.bottom-30;
	rcWnd.bottom+=space;	
	pParent->SetWindowHeight (GetSafeHwnd(),rcWnd.Height());

}

void CSampleWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()	
	DrawSample(&dc);

}

BOOL CSampleWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	UINT cur=m_bZoom?IDC_ZOOMOUT:IDC_ZOOMIN;
	::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(cur)));
	return TRUE;
	//return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
