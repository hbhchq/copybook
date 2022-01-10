// MsgBox.cpp : 实现文件
//

#include "stdafx.h"
#include "MsgBox.h"


// CMsgBox

IMPLEMENT_DYNAMIC(CMsgBox, CWnd)

CMsgBox::CMsgBox(LPCTSTR msg,CPoint ptTarget,CPoint ptBegin )
:CWnd(),m_strMessage(msg),m_ptTarget(ptTarget),m_ptBegin(ptBegin)
{

}

void CMsgBox::Set(LPCTSTR msg,CPoint ptTarget,CPoint ptBegin)
{
	m_strMessage=(msg);
	m_ptTarget=(ptTarget);
	m_ptBegin=(ptBegin);
}


CMsgBox::~CMsgBox()
{
	//销毁窗口
	::DestroyWindow(this->Detach());
	//this->m_rgn.DeleteObject();

}


BEGIN_MESSAGE_MAP(CMsgBox, CWnd)
	//ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CMsgBox 消息处理程序



//int CMsgBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CWnd::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码	
//	return 0;
//}



void  CMsgBox::CalcWindowRgn()
{
	//窗口必须已经创建
	ASSERT(this->GetSafeHwnd());
	CClientDC dc(this);
	//计算消息显示的区域
	CRect rc,rcTxt;
	this->GetClientRect(&rcTxt);
	dc.DrawText(m_strMessage,&rcTxt,DT_CALCRECT|DT_NOPREFIX|DT_NOCLIP|DT_VCENTER );
	this->GetWindowRect(&rc);
	CSize szChar=dc.GetTextExtent(L"0",1);
	rc.SetRect(rc.left-2,rc.top,rc.left+rcTxt.Width()+szChar.cy,m_ptBegin.y+rcTxt.Height()+szChar.cy);
	//调整窗口尺寸和位置
	this->MoveWindow(&rc);

	this->GetClientRect(&rc);
	//屏幕坐标转成消息窗口客户区的坐标
	CPoint ptBegin(m_ptBegin),ptTarget(m_ptTarget);
	ScreenToClient(&ptBegin);
	ScreenToClient(&ptTarget);

	CPoint b(ptBegin),c(ptBegin);//除目标点外，三角形的另两点,纵坐标同左端起始点
	b.x=ptBegin.x+(ptTarget.x-ptBegin.x)/2;
	c.x=ptBegin.x+(ptTarget.x-ptBegin.x);
	//消息文本显示区域	
	m_rect.SetRect(ptBegin.x ,ptBegin.y
		,rc.right,rc.bottom);
	//居中调整
	m_rect.left+=(m_rect.Width()-rcTxt.Width())/2;
	m_rect.top+=(m_rect.Height()-rcTxt.Height())/2;
	//计算窗口区域
	POINT pts[]={ptTarget,b,c};
	CRgn rgn1;rgn1.CreatePolygonRgn(pts,3,ALTERNATE);
	CRgn rgn2;rgn2.CreateRoundRectRgn(ptBegin.x+1,ptBegin.y,rc.right-1,rc.bottom,3,3);
	m_rgn.CreateRectRgn(1,1,1,1);
	m_rgn.CombineRgn(&rgn1,&rgn2,RGN_OR );
	//设置窗口区域
	this->SetWindowRgn(m_rgn,1);
}


void CMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
	{
		this->KillTimer(1);
		this->ShowMessage(FALSE);
	}
	CWnd::OnTimer(nIDEvent);
}



void CMsgBox::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	this->ShowMessage(FALSE);
	this->KillTimer(1);
}

void CMsgBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowMessage(FALSE);
	this->KillTimer(1);

	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CMsgBox::CreateWnd()
{
	HINSTANCE hinstance=AfxGetInstanceHandle();
	WNDCLASSEX wcx; 

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	//CBrush bru(afxGlobalData.clrBarHilite);
	wcx.cbSize = sizeof(wcx);          // size of structure 
	wcx.style = CS_DBLCLKS/*|CS_HREDRAW |	CS_VREDRAW*/;                    // redraw if size changes 
	wcx.lpfnWndProc = ::DefWindowProc;     // points to window procedure 
	wcx.cbClsExtra = 0;                // no extra class memory 
	wcx.cbWndExtra = 0;                // no extra window memory 
	wcx.hInstance = hinstance;         // handle to instance 
	wcx.hIcon = NULL;              // predefined app. icon 
	wcx.hCursor = NULL;                    // predefined arrow 
	wcx.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH/*LTGRAY_BRUSH*/);   //(HBRUSH)bru.Detach();    background brush 
	wcx.lpszMenuName =  NULL;    // name of menu resource 
	wcx.lpszClassName = L"MESSAGEBOXCLASS";  // name of window class 
	wcx.hIconSm = NULL; // small class icon 
	if(!RegisterClassEx(&wcx)&&ERROR_CLASS_ALREADY_EXISTS!=::GetLastError())
	{
		return FALSE; 
	}
	HWND hwnd; 
	// Create the window.  
	hwnd = CreateWindow( 
		L"MESSAGEBOXCLASS",   // name of window class 
		0,            // title-bar string 
		WS_BORDER|/*WS_CHILD*/WS_POPUP, // top-level window 
		m_ptBegin.x/*CW_USEDEFAULT*/,       // default horizontal position 
		m_ptTarget.y/*CW_USEDEFAULT*/,       // default vertical position 
		100/*CW_USEDEFAULT*/,       // default width 
		10/*CW_USEDEFAULT*/,       // default height 
		(HWND) AfxGetMainWnd()->GetSafeHwnd()/*NULL*/,         // no owner window 
		(HMENU) NULL,        // use class menu 
		hinstance,           // handle to application instance 
		(LPVOID) NULL);      // no window-creation data 

	if (hwnd) 
	{
		//this->Attach(hwnd);
		this->SubclassWindow(hwnd);
		//去除任务栏图标显示
		this->ModifyStyleEx(WS_EX_APPWINDOW,0);
		return TRUE; 
	}
	else
	{
		return FALSE; 
	}

}


BOOL CMsgBox::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//BOOL ret=CWnd::OnEraseBkgnd(pDC);
	CBrush bru(afxGlobalData.clrBarLight);
	HRGN hRgn=::CreateRectRgn(1,1,1,1);
	this->GetWindowRgn(hRgn);
	FillRgn(pDC->GetSafeHdc(),hRgn,(HBRUSH)bru.GetSafeHandle());
	//绘制窗口边界，输出文字消息
	CClientDC dc(this);
	//CBrush bru2(afxGlobalData.clrActiveBorder);
	::OffsetRgn(hRgn,-1,-1);
	::FrameRgn(dc.GetSafeHdc(),hRgn,(HBRUSH)/*bru2*/afxGlobalData.brHilite.GetSafeHandle(),1,1);
	::DeleteObject(hRgn);
	dc.SetBkMode(TRANSPARENT );
	dc.DrawText(m_strMessage,&this->m_rect,/*DT_NOCLIP|*/DT_NOPREFIX/*|DT_CALCRECT*/|DT_VCENTER/*|DT_CENTER*/);
	/////////////////
	return 1;
	//return ret;
}
//void CMsgBox::OnPaint()
//{
//	CClientDC dc(this); // device context for painting
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CWnd::OnPaint()
//	CBrush bru(afxGlobalData.clrActiveBorder);
//	HRGN hRgn=::CreateRectRgn(1,1,1,1);
//	this->GetWindowRgn(hRgn);
//	::OffsetRgn(hRgn,-1,-1);
//	::FrameRgn(dc.GetSafeHdc(),hRgn,(HBRUSH)bru.GetSafeHandle(),1,1);
//	::DeleteObject(hRgn);
//	dc.SetBkMode(TRANSPARENT );
//	dc.DrawText(m_strMessage,&this->m_rect,/*DT_NOCLIP|*/DT_NOPREFIX/*|DT_CALCRECT*/|DT_VCENTER/*|DT_CENTER*/);
//}
//
//
//显示消息窗口
void CMsgBox::ShowMessage(BOOL bShow)
{
	if(this->GetSafeHwnd()==NULL)
	{
		CRect rc(m_ptBegin.x ,m_ptTarget.y,m_ptBegin.x+50 ,m_ptTarget.y+10);
		if(!//this->Create(NULL,NULL,WS_POPUP|WS_BORDER,rc)
			this->CreateWnd()
			)
			return ;
	}
	//
	if(bShow)
	{
		int x=m_ptBegin.x;
		int y=m_ptTarget.y;
		this->SetWindowPos(&CWnd::wndTop,x,y,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
		//计算并设置窗口区域
		if(m_rgn.GetSafeHandle()==NULL)
			this->CalcWindowRgn();	
		Invalidate();
		//窗口创建完成后，启用计时器，10秒后关闭窗口
		this->SetTimer(1,10000,NULL);
	}
	else
	{
		this->ShowWindow(SW_HIDE);
		this->KillTimer(1);
	}

}

