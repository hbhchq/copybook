// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// 练字工具View.cpp : CMyView 类的实现
//
#include "stdafx.h"
#include "练字工具.h"

#include "练字工具Doc.h"
#include "练字工具View.h"
#include <math.h>
#include "afxwin1.inl"
#include "mainfrm.h"
#include "SampleWnd.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyView

IMPLEMENT_DYNCREATE(CMyView, CEditView)

BEGIN_MESSAGE_MAP(CMyView, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyView::OnFilePrintPreview)
	ON_MESSAGE(WM_DRAW_SAMPLE,&CMyView::OnDrawPaneSample)
//ON_WM_LBUTTONDBLCLK()
ON_CONTROL_REFLECT(EN_CHANGE, &CMyView::OnEnChange)
//ON_WM_CHAR()
ON_UPDATE_COMMAND_UI(ID_TASKPANE_GRID_SPLIT, &CMyView::OnUpdateTaskpaneGridSplit)
ON_COMMAND(ID_TASKPANE_GRID_SPLIT, &CMyView::OnTaskpaneGridSplit)
//ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CMyView 构造/析构

CMyView::CMyView()
{
	// TODO: 在此处添加构造代码

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//去掉水平滚动条
	cs.style&=~WS_HSCROLL;
	cs.style|=WS_VSCROLL|ES_MULTILINE|ES_WANTRETURN;
	return CEditView::PreCreateWindow(cs);
}

// CMyView 绘制

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}


// CMyView 打印


void CMyView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}
//LRESULT CMyView::OnRecalcPage(WPARAM w,LPARAM l)
//{
//	PRINTDLG pd;
//	pd.lStructSize = (DWORD)sizeof(PRINTDLG);
//	BOOL bRet = theApp.GetPrinterDeviceDefaults(&pd);
//	if(bRet)
//	{
//		HDC dc= AfxCreateDC(pd.hDevNames,pd.hDevMode);		
//		CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
//		CRect margin=pMain->GetPageMargin();
//		CCharStyle &chSty=pMain->m_charStyle;
//		//计算打印的页数
//		int wid,hei;
//		wid=::GetDeviceCaps(dc,HORZSIZE)*100-margin.left-margin.right;
//		hei=::GetDeviceCaps(dc,VERTSIZE)*100-margin.top-margin.bottom;
//		////计算文本段落行数
//		this->CalcTxtLines(chSty.m_bHorz?CalcCols(wid):this->CalcRows(hei));
//	}
//	return 1;
//	
//}
BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	BOOL ret=DoPreparePrinting(pInfo);
	//如果不成功直接返回，主要原因可能是没有装打印机
	if(ret==FALSE)return ret;
		//进行注册授权较验
	theApp.m_bLicense=theApp.CheckLicence();
	if(!theApp.m_bLicense)
	{
		CString msg;
		BOOL bValid=msg.LoadString(IDS_DONT_PRINT_MSG);
		ASSERT(bValid);
		MessageBox(msg,0,MB_ICONINFORMATION|MB_OK);
	}
	//进行各种设置数据的更新和较验
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	pMain->UpdateData();
	//注意页面尺寸是毫米单位，需转换
	CSize szPage=pMain->GetPaperSize();
	szPage.cx*=100;szPage.cy*=100;
	BOOL valid=pMain->ValidSetting(szPage);
	if(!valid)
	{
		CString inf;
		BOOL b=inf.LoadString(IDS_SETTING_INVALID);
		ASSERT(b);
		MessageBox(inf,0,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	// 默认准备
	return ret;
}

void CMyView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
		//从框架窗口取回页面设置信息，即页大小和边距
		CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
		CRect margin=pMain->GetPageMargin();
		CCharStyle &chSty=pMain->m_charStyle;
		//计算打印的页数
		int wid,hei;
		wid=pDC ->GetDeviceCaps(HORZSIZE)*100-margin.left-margin.right;
		hei=pDC ->GetDeviceCaps(VERTSIZE)*100-margin.top-margin.bottom;
		////计算文本段落行数
		 this->CalcTxtLines(chSty.m_bHorz?CalcCols(wid):this->CalcRows(hei));
		int pageCount=this->CalcPages(this->CalcRows(hei),CalcCols(wid),chSty.m_bHorz);
		 pInfo->SetMaxPage(pageCount);
		 if(pInfo)
		 {
			 CString inf;
			 CString fmt;fmt.LoadString(IDS_PREVIEW_PAGE_INFOR);
			 inf.Format(fmt,pInfo->m_nCurPage,pageCount);
			 pMain->SetStatusInfor(inf);
		 }
////////////////////////

}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
	// TODO: 添加打印后进行的清理过程
	if(pInfo)
	{
		//打印结束
		CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
		pMain->SetStatusInfor(NULL);
	}
}

void CMyView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMyView 诊断

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyView 消息处理程序

void CMyView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	//////////
	AdjustMapSpace(pDC);
	//CEditView::OnPrepareDC(pDC, pInfo);
	//在样例描绘中也会用到本过程，因此注释掉打印状态检测
	//if(pDC->IsPrinting()) // Is the DC a printer DC.
	//{
		//CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
		//CRect mg=pMain->GetPageMargin();
		//pDC->SetMapMode(/*MM_ANISOTROPIC*/MM_ISOTROPIC);  
		//int xPix=pDC->GetDeviceCaps(HORZRES);
		//int yPix=pDC->GetDeviceCaps(VERTRES);
		//int xMM=pDC->GetDeviceCaps(HORZSIZE); 
		//int yMM=pDC->GetDeviceCaps(VERTSIZE); 
		////进行居中方式调整时需用到的距离
		//CSize szPrinted;
		//CSize szAdjust(this->CalcAdjustSize(pDC,&szPrinted));
		//
		//if(pMain->m_charStyle.m_bLToR )
		//{
		//	//相当于一单位就是0.01毫米,主要为了方便线条绘制
		//	pDC->SetWindowExt(100*xMM,   100*yMM);  
		//	pDC->SetViewportExt(xPix,yPix);  
		//	//重设原点位置
		//	//pDC->SetViewportOrg(mg.left*xPix/(100*xMM),mg.top*yPix/(100*yMM));
		//	//考虑居中调整,重设原点位置
		//	pDC->SetViewportOrg((mg.left+szAdjust.cx)*xPix/(100*xMM)
		//		,(mg.top+szAdjust.cy)*yPix/(100*yMM));
		//}
		//else//右到左，原点移到右边进行绘制
		//{
		//	pDC->SetWindowExt(100*xMM,   100*yMM);  
		//	pDC->SetViewportExt(-xPix,yPix);  
		//	//重设原点位置
		//	//pDC->SetWindowOrg(100*xMM-mg.right,-mg.top);
		//	////////pDC->SetViewportOrg(-(100*xMM-mg.right*xPix)/(100*xMM),mg.top*yPix/(100*yMM));
		//	//考虑居中调整,重设原点位置
		//	pDC->SetWindowOrg(100*xMM-mg.right-szAdjust.cx,-mg.top-szAdjust.cy);
		//	
		//}
	//}
}


void CMyView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
		CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
		CCharStyle & sty=pMain->m_charStyle;

		CRect mg=pMain->GetPageMargin();
		//绘制打印范围//////////////////
		//取得页大小尺寸
		int pageW=pDC ->GetDeviceCaps(HORZSIZE)*100;
		int pageH=pDC ->GetDeviceCaps(VERTSIZE)*100;
		//计算打印的高度和宽度
		int w=pageW-mg.left-mg.right;
		int h=pageH-mg.top-mg.bottom;	
		if(pInfo->m_bPreview)
		{
			//画出打印范围区域，主要是页边距
			DrawScopeLine(pDC,w,h,mg);
		}

		////如果未注册则显示提示信息，并且在打印的页面上加一水印图
		if(!theApp.m_bLicense)
		{
			DrawWatermark(pDC,w,h);			
		}
		DrawGrid2(pDC,w,h,pMain->m_gridStyle .m_cellLength
			,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
			,pMain->m_charStyle.m_bHorz,pInfo->m_nCurPage);
		//打印页面文字
		this->DrawPageText(pDC,w,h,pMain->m_gridStyle .m_cellLength
			,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
			,pMain->m_charStyle.m_bHorz,pInfo->m_nCurPage,pInfo);


}


// 以高度为参数计算每页显示的行数，单位统一为0.01毫米
int CMyView::CalcRows(UINT h)
{
	CGridStyle *pGrid=this->GetGridStyle();
	return (h+pGrid->m_rowSpace)/(pGrid->m_cellLength+pGrid->m_rowSpace);
	
}

// 以页面宽度为参数计算列数
int CMyView::CalcCols(UINT w)
{
	CGridStyle *pGrid=this->GetGridStyle();
	return (w+pGrid->m_colSpace)/(pGrid->m_cellLength+pGrid->m_colSpace);
}

	// 通过行数列数计算而打印的页数,注意是横排还是竖排文字，默认横排
	//rows为每页行数，cols为每页列数
int CMyView::CalcPages(int  rows, int cols,BOOL isHorz)
{
	//每页行数
	int linesPerPage=isHorz?rows:cols;
	//总行数
	int pageLines=this->m_arrTxtLineInfor.GetCount();
	return ceil( (double)pageLines/(double)linesPerPage);
	
}

// 用虚线画出可打印的的范围区域
void CMyView::DrawScopeLine(CDC * pDC , int w , int h , CRect  mg)
{

	//以固定长度画范围限制线
	mg.top=mg.left=mg.right=mg.bottom=1000;
	//首先获取居中调整的距离，然后调整坐标
	CSize sz=this->CalcAdjustSize(pDC);
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CPoint newOrg;
	CPoint oldOrg=pDC->GetWindowOrg ();
	if(pMain->m_charStyle.m_bLToR)
	{
		newOrg.x=sz.cx;
		newOrg.y=sz.cy;
	}
	else
	{
		newOrg.x=oldOrg.x+sz.cx;
		newOrg.y=oldOrg.y+sz.cy;
	}
	pDC->SetWindowOrg(newOrg);
		//画出打印范围
		CPen pen(PS_SOLID,1,RGB(192,192,192));
		CPen * oldP=pDC->SelectObject(&pen);
		pDC->MoveTo(0,0);pDC->LineTo(-mg.left,0);
		pDC->MoveTo(0,0);pDC->LineTo(0,-mg.top);

		pDC->MoveTo(0,h);pDC->LineTo(0,h+mg.bottom);
		pDC->MoveTo(0,h);pDC->LineTo(-mg.left,h);

		pDC->MoveTo(w,0);pDC->LineTo(w+mg.right,0);
		pDC->MoveTo(w,0);pDC->LineTo(w,-mg.top);

		pDC->MoveTo(w,h);pDC->LineTo(w+mg.right,h);
		pDC->MoveTo(w,h);pDC->LineTo(w,h+mg.bottom);

		//pDC->Rectangle(0,0,w,h);	
		//还原DC
		pDC->SelectObject(oldP);
		pDC->SetWindowOrg(oldOrg);

}


// // 在指定的位置绘制一个个单独的文字,
//void CMyView::DrawAloneChar(CDC* pDC, CRect & r,TCHAR ch)
//{
//
//	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
//	CCharStyle & sty=pMain->m_charStyle;
//	if(sty.m_bHollow)
//	{
//		this->DrawHollowChar(pDC,r,ch);
//	}
//	else
//	{
//		pDC->SetBkMode(TRANSPARENT);
//		//pDC->DrawText(&ch,1,&r,DT_SINGLELINE |DT_CENTER|DT_VCENTER);
//		this->DrawCenterChar(pDC,r,ch);
//	}
//}
//
//void CMyView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值	
//	CEditView::OnLButtonDblClk(nFlags, point);
//	//放大3倍
//	
//}







void CMyView::DrawGridInside(CDC* pDC, CRect & r)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CGridStyle &sty=pMain->m_gridStyle;
	CPen pen(sty.m_lineType,sty.m_lineWidth,sty.m_color);
	CPen *oldP=pDC->SelectObject(&pen);
	switch(sty.m_category)
	{
	case GRIDCATEGORY::TIAN:
		DrawShi(pDC,r);
		break;

	case GRIDCATEGORY::MI:
		DrawShi(pDC,r);
		DrawShi2(pDC,r);
		break;

	case GRIDCATEGORY::JIU:
		{
		int x=r.Width()/3;
		int y=r.Height()/3;
		pDC->MoveTo(r.left,r.top+y);
		pDC->LineTo(r.right,r.top+y);
		pDC->MoveTo(r.left,r.bottom-y);
		pDC->LineTo(r.right,r.bottom-y);
		//画垂直线
		pDC->MoveTo(r.left+x,r.top);
		pDC->LineTo(r.left+x,r.bottom);
		pDC->MoveTo(r.right -x,r.top);
		pDC->LineTo(r.right -x,r.bottom);
		break;
		}
	case GRIDCATEGORY::HUI://回格
		DrawHui(pDC,r);
		break;
	case GRIDCATEGORY::TIAN_HUI://田回格
		DrawShi(pDC,r);
		DrawHui(pDC,r);
		break;
	case GRIDCATEGORY::MI_HUI://米回格
		DrawShi(pDC,r);
		DrawShi2(pDC,r);
		DrawHui(pDC,r);
		break;

	}
	pDC->SelectObject(oldP);
}

//// 输出空心字
//void CMyView::DrawHollowChar(CDC* pDC,CRect & r,TCHAR ch)
//{
//	pDC->BeginPath();
//	pDC->SetBkMode(TRANSPARENT);
//	//pDC->DrawText(&ch,1,&r,DT_SINGLELINE |DT_CENTER|DT_VCENTER);
//	this->DrawCenterChar(pDC,r,ch);
//	pDC->EndPath();
//	pDC->StrokeAndFillPath();
//}
//
//// 根据文字样式初始化文字输出DC环境
//void CMyView::InitTextOut(CDC* pDC, CCharStyle & sty,COLORREF oldTxtClr,CFont * oldFont,CBrush * oldBruFill, CPen * oldPen)
//{
//	//设置文字对齐方式
//	pDC->SetTextAlign(TA_CENTER|TA_TOP);
//	pDC->SetBkMode(TRANSPARENT);
//	//初始化字体
//	CFont font;
//	VERIFY(font.CreateFont(
//		sty.m_charHeight,                        // nHeight,取绝对高度不要外部空白
//		0,                         // nWidth
//		0,                         // nEscapement
//		0,                         // nOrientation
//		sty.m_weight,                 // nWeight
//		FALSE,                     // bItalic
//		FALSE,                     // bUnderline
//		0,                         // cStrikeOut
//		sty.m_charset,              // nCharSet
//		OUT_DEFAULT_PRECIS,        // nOutPrecision
//		CLIP_DEFAULT_PRECIS,       // nClipPrecision
//		DEFAULT_QUALITY,           // nQuality
//		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
//		sty.m_fontName)); 
//
//	oldFont=pDC->SelectObject(&font);
//	font.Detach();	
//	if(!sty.m_bHollow)
//	{
//		pDC->SetTextColor(sty.m_color);		
//	}
//	else//空心字绘制比较复杂
//	{
//		//空心字线型的样式
//		DWORD penstyle=PS_GEOMETRIC;
//		if(sty.m_bSolid)
//			penstyle|=PS_SOLID;
//		else
//			penstyle|=PS_DOT;
//
//		//输出空心字用到的笔,刷子定义
//		LOGBRUSH lb;
//		lb.lbStyle    =      BS_SOLID ;
//		lb.lbColor    =      sty.m_color;
//		lb.lbHatch    =      0 ;
//		CPen *pen=new CPen(penstyle,1,&lb);
//		//设置绘字的画笔
//		oldPen=pDC->SelectObject(pen);
//		pen->Detach();
//		delete pen;
//		//空心字填充刷
//		CBrush *bruFill=new CBrush(pDC->GetBkColor());
//		oldBruFill=pDC->SelectObject(bruFill);	
//		bruFill->Detach(); 
//		delete bruFill;
//	}
//
//}

//
// 计算实际需要打印居中方式打印，需调整的距离，即减除不足一格的距离除2,输出可以被打印尺寸
CSize CMyView::CalcAdjustSize(CDC * pDC,CSize *szPrinted)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CRect mg=pMain->GetPageMargin();
	//取得页大小尺寸，转化为0.01毫米
	int pageW=pDC ->GetDeviceCaps(HORZSIZE)*100;
	int pageH=pDC ->GetDeviceCaps(VERTSIZE)*100;
	///////////如果是预览界面，页面尺寸必须重新计算
	if(!pDC->IsPrinting())
	{
		this->CalcSampleWndSize(&pageW,&pageH);
	}
	///////////////////////////////////////////////
	//计算打印的高度和宽度
	int w=pageW-mg.left-mg.right;
	int h=pageH-mg.top-mg.bottom;	
	//计算实际打印的行数与列数
	int rows=this->CalcRows(h);
	int cols=this->CalcCols(w);
	CGridStyle &gridSty=pMain->m_gridStyle;
	CPageLayout &pageSet=pMain->m_pageLayout;
	//实际打印字格所用到的尺寸，不足一格的距离进行调整，以使居中打印
	int cx=(gridSty.m_cellLength+gridSty.m_colSpace)*cols-gridSty.m_colSpace;
	int cy=(gridSty.m_cellLength+gridSty.m_rowSpace)*rows-gridSty.m_rowSpace;
	//根据当前定义的居中模式进行调整
	int x=0,y=0;
	if(pageSet.m_bCenter) x=(w-cx)/2;
	if(pageSet.m_bVCenter) y=(h-cy)/2;
	if(szPrinted)
	{
		szPrinted->cx=w;
		szPrinted->cy=h;
	}
	return CSize(x,y);
}

// 在给定的矩形区域内居中输出字符
void CMyView::DrawCenterChar(CDC * pDC, CRect & rc, TCHAR ch)
{
 	CCharStyle * sty=this->GetCharStyle();
	//drawText从右到左输入文字时有问题
	////int y=rc.top;
	CSize sz=pDC->GetTextExtent(&ch,1);
	int deflateY=(rc.Height()-sz.cy)/2;
	CRect rcActual(rc);
	rcActual.DeflateRect(0,deflateY);
	//////根据设置调整字符的上下偏移量
	rcActual.OffsetRect(0,sty->m_bDownward?sty->m_offsetY:-sty->m_offsetY);
	pDC->TextOut(rcActual.CenterPoint().x,rcActual.top,&ch,1);
}

//为了提高效率，第二种版本，
void CMyView::DrawGrid2(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum)
{
	if(w<=0||h<=0)return;
	int rows=this->CalcRows(h);
	int cols=this->CalcCols(w);
	//计算条数
	int linesCount=isHorz?rows:cols;
	//每条的格子数
	int cellsCount=isHorz?cols:rows;
	//上一格子矩形
	CRect rcOld(0,0,size,size);
	//正进行绘制的格子矩形
	CRect rc(rcOld);
	//画出整个页面的外框线,采用格子的3倍线宽
	//外框线为实线
	CGridStyle *sty=this->GetGridStyle();
	CPen pen(PS_SOLID,sty->m_borderWidth*3,sty->m_color);
	CPen * oldP=pDC->SelectObject(&pen);
	CPoint endPagePt(cols*(size+cSpc)-cSpc,rows*(size+rSpc)-rSpc);
	CRect rcFrm(rc.TopLeft(),endPagePt);
	//rcFrm.InflateRect(sty->m_borderWidth*2,sty->m_borderWidth*2);
	this->DrawRect(pDC,rcFrm);
	//恢复先前的笔
	pDC->SelectObject(oldP);

	for(int ln=0;ln<linesCount;ln++)
	{
		//更新排格子的起点
		int lnOffsetX=ln*(size+cSpc);
		int lnOffsetY=ln*(size+rSpc);
		if(isHorz)rcOld.MoveToY(lnOffsetY);
		else rcOld.MoveToX(lnOffsetX);
		rc=rcOld;
		//绘制一排格子
		for(int i=0;i<cellsCount;i++)
		{
			int x=i*(size+cSpc);
			int y=i*(size+rSpc);
			if(isHorz)rc.MoveToX(x);
			else rc.MoveToY(y);
			if(i==0)rcOld=rc;
			this->DrawAloneGrid2(pDC,rc,rcOld,isHorz);
			rcOld=rc;
		}

	}

}

// 绘制一个个单格及内部线条,并且画出与前一个格子间的连接线，主要是存在行、列间距时用到
void CMyView::DrawAloneGrid2(CDC* pDC, CRect & r,CRect & oldR,BOOL isHorz)
{

	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CGridStyle &sty=pMain->m_gridStyle;
	//外框线为实线
	CPen pen(PS_SOLID,sty.m_borderWidth,sty.m_color);
	CPen * oldP=pDC->SelectObject(&pen);
	//若两格子不重叠并且不交叉并且未换行，先画新老两格的连接线，
	DrawConnectLine(pDC,r,oldR,isHorz,sty);
	switch(sty.m_category)
	{
	case GRIDCATEGORY::NONE://无边框格线，即不打格
		break;
	case GRIDCATEGORY::ROWLINE:
		pDC->MoveTo(r.TopLeft());
		pDC->LineTo(r.right+1,r.top);
		pDC->MoveTo(r.BottomRight());
		pDC->LineTo(r.left-1,r.bottom);
		break;
	case GRIDCATEGORY::COLLINE:
		pDC->MoveTo(r.TopLeft());
		pDC->LineTo(r.left,r.bottom+1);
		pDC->MoveTo(r.BottomRight());
		pDC->LineTo(r.right,r.top-1);
		break;
	default:
		//画格子内线段，先画内线，以免回字格看不到外格子//
		DrawGridInside(pDC,r);
		//画格子外框,直接画矩形框线不能重合，只能画线
		//pDC->Rectangle(r.left,r.top,r.right+1,r.bottom+1);
		DrawRect(pDC,r);
	}
	pDC->SelectObject(oldP );
	//画自绘格子图像
	if(sty.m_bOwnerDraw)
		DrawOwnGridImg(pDC,r);
	//绘制十等分线
	CPen penInside(sty.m_lineType,sty.m_lineWidth,sty.m_color);
	oldP=pDC->SelectObject(&penInside);
	//如果是预览窗口可以画十等分线，以观察笔画结构位置
	if(pMain->GetTaskPane()->m_bSplitGrid&&!pMain->IsPrintPreview())
		DrawGridSplitLine(pDC,r);
	pDC->SelectObject(oldP );


}
void CMyView::DrawConnectLine(CDC * pDC,CRect & r, CRect & oldR, BOOL isHorz,CGridStyle &gridSty)
{
	//无边框格线，也不画连接线
	if(gridSty.m_category==GRIDCATEGORY::NONE)return ;
	//若两格子不重叠并且有间距,画连接线，要考虑是否只画行线或列线的情况
	if(r!=oldR&&isHorz&&gridSty.m_colSpace>0
		&&gridSty.m_category!=GRIDCATEGORY::NONE
		&&gridSty.m_category!=GRIDCATEGORY::COLLINE
		)
	{
		pDC->MoveTo(oldR.BottomRight());
		pDC->LineTo(r.right ,r.bottom);
		pDC->MoveTo(r.TopLeft());
		pDC->LineTo(oldR.left,oldR.top);
	}
	if(r!=oldR&&!isHorz&&gridSty.m_rowSpace>0	
		&&gridSty.m_category!=GRIDCATEGORY::NONE
		&&gridSty.m_category!=GRIDCATEGORY::ROWLINE
		)
	{
		pDC->MoveTo(oldR.BottomRight());
		pDC->LineTo(r.right ,r.bottom);
		pDC->MoveTo(r.TopLeft());
		pDC->LineTo(oldR.left,oldR.top);
	}

}

// 计算编辑框中文本按行切分的位置信息,信息保存在成员变量中，返回总行数
int CMyView::CalcTxtLines(int lineLen)
{
	//若多次打开，需更新
	this->m_arrTxtLineInfor.RemoveAll();
	if(lineLen<1)return 0;
	CEdit & edit=GetEditCtrl();
	//计算行时，取出所有的字符串以利于后面反复输出时循环调用
	edit.GetWindowText(m_strWndTxt);	
	if(m_strWndTxt.IsEmpty())return 0;
	//字符在整个字串中的位置索引，包括\r\n
	int idx=0;

	LPCTSTR pszTxt=(LPCTSTR)m_strWndTxt;
	int txtLen=m_strWndTxt.GetLength();
	LineInfor inf(idx,lineLen);
	//是否最后加一空行标志
	BOOL bAddBlank=FALSE;
	while(idx<txtLen)
	{
		//安全起见，分析个数，特别是字串结尾时
		int sz=(idx+lineLen<txtLen?lineLen:txtLen-idx);
		//查找\r或\n;
		int posR=FindCh(pszTxt+idx,sz,L'\r');
		//TCHAR * pR=StrChr(pszTmp,L'\r');
		//判断实际行的长度，有回车，长度只到回车前，无则为实际行长
		int lenActual=(posR==-1?sz:posR);
		//必须调整尺寸和下次分行的位置
		inf.Set(idx,lenActual);
		this->m_arrTxtLineInfor.Add(inf);
		//考虑回车与换行总是一起的
		idx+=(posR==-1?lenActual:lenActual+2);

	}
	//如果最后一行为空的换行,并且已经分好的行信息中将已经包括了\n，加一行
	if(*(pszTxt+txtLen-1)==L'\n')
	{
		int lastLineCharIdx=m_arrTxtLineInfor.GetAt(m_arrTxtLineInfor.GetCount()-1).firstIndex;
		int l=txtLen-lastLineCharIdx;
		if(l>=lineLen)//肯定包括了最后回车，则少计一行
		{
			inf.Set(idx,0);
			m_arrTxtLineInfor.Add(inf);
		}
	}

#ifdef DEBUG/////////////////////
	//显示所有的段落信息
	for(int n=0;n<m_arrTxtLineInfor.GetCount();n++)
	{
		LineInfor it=m_arrTxtLineInfor.GetAt(n);
		TRACE3("lineIdx=%d,firstindex=%d;len=%d\n",n,it.firstIndex,it.length);
	}
#endif////////////////////////////
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	pMain->m_bRecalcPage=FALSE;
	return m_arrTxtLineInfor.GetCount();
}

// 从字符串的中间某位置开始查找字符，返回相对于查找起始位置的位置索引，未找到返回-1
int CMyView::FindCh(LPCTSTR begin , int count , TCHAR ch)
{
	for(int n=0;n<count;n++)
	{
		if(*(begin+n)==ch)
			return n;
	}
	return -1;
}

////// 根据条索引位置及条中的字符位置求需输出的字符,lineIdx,为当前页的行索引，charPos为行中的索引
////TCHAR CMyView::GetPrintChar(int pageNum,int pageLines,int lineIdx, int charPos)
////{
////	int firstLineIdx=(pageNum-1)*pageLines;
////	//在所页行中的索引位置
////	int lineIdxInAll=firstLineIdx+lineIdx;
////	ASSERT(lineIdxInAll>=0);
////	//如果文字输出全部结束，只需画空表格
////	if(lineIdxInAll>=m_arrTxtLineInfor.GetCount())
////		return  TCHAR(0);
////	LineInfor ln=m_arrTxtLineInfor.GetAt(lineIdxInAll);
////	if(charPos>=ln.length)//空白行，一般为段落结尾
////	{
////		return TCHAR(0);
////	}
////	int index=ln.firstIndex+charPos;
////	CString &txt=m_strWndTxt;
////	return txt.GetAt(index);
////}

// 根据页码绘制页面的所有文字
void CMyView::DrawPageText(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum, CPrintInfo* pInfo)
{
	if(w<=0||h<=0)return;
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CCharStyle & sty=pMain->m_charStyle;
	//设置文字对齐方式
	pDC->SetTextAlign(TA_CENTER|TA_TOP);
	pDC->SetBkMode(TRANSPARENT);
	CFont font;
	CPen pen;
	this->CreateFont(sty,&font);
	CFont *oldFont=pDC->SelectObject(&font);
	CPen  *oldPen=NULL;
	COLORREF oldClr=pDC->GetTextColor();
	CBrush *oldBru=(CBrush *)pDC->SelectStockObject(WHITE_BRUSH);
	pen.CreatePen(sty.m_bSolid?PS_SOLID:PS_DOT,1,sty.m_color);
	//输出文字时全部按路径处理，不以单个字符画路径
	if(sty.m_bHollow)
	{	
		oldPen=pDC->SelectObject(&pen);
		//////////开始路径绘制/////
		pDC->BeginPath();
	}
	else
	{
		pDC->SetTextColor(sty.m_color);
	}
	///////////////////////////////////
	int rows=this->CalcRows(h);
	int cols=this->CalcCols(w);
	//////////////////////////////////////////////
	//为了防止预览时，同步修改各项设置,出现错误，每次重新计算分页信息
	//if(pMain->m_bRecalcPage)
	//{
		CalcTxtLines(isHorz?cols:rows);
		int pageCount=this->CalcPages(rows,cols,isHorz);
		if(pInfo)	pInfo->SetMaxPage(pageCount);
		pMain->m_bRecalcPage=FALSE;
	//}
	//设置状态栏信息
	if(pInfo)
	{
		CString inf;
		CString fmt;fmt.LoadString(IDS_PREVIEW_PAGE_INFOR);
		inf.Format(fmt,pInfo->m_nCurPage,pInfo->GetMaxPage());
		pMain->SetStatusInfor(inf);
	}
	////////////////////////////////////
	//计算条数
	int linesCount=isHorz?rows:cols;
	//上一格子矩形
	CRect rcOld(0,0,size,size);
	//正进行绘制的格子矩形
	CRect rc(rcOld);
	//字符行相关属性
	int charLnFirst=(pageNum-1)*linesCount;
	int charLnLast=(pageNum)*linesCount;//不包括末行自身
	if(charLnLast>=m_arrTxtLineInfor.GetCount())
		charLnLast=m_arrTxtLineInfor.GetCount();
	//当前页需输出文字的行数
	int drawLnCount=charLnLast-charLnFirst;
	for(int ln=0;ln<drawLnCount;ln++)
	{
		//更新排格子的起点
		int lnOffsetX=ln*(size+cSpc);
		int lnOffsetY=ln*(size+rSpc);
		if(isHorz)rcOld.MoveToY(lnOffsetY);
		else rcOld.MoveToX(lnOffsetX);
		rc=rcOld;
		//绘制一排字符
		LineInfor lnInf=m_arrTxtLineInfor.GetAt(ln+charLnFirst);
			//每条的格子数
		int cellsCount=isHorz?cols:rows;
		ASSERT(lnInf.length<=cellsCount);
		for(int i=0;i<lnInf.length;i++)
		{
			int x=i*(size+cSpc);
			int y=i*(size+rSpc);
			if(isHorz)rc.MoveToX(x);
			else rc.MoveToY(y);
			if(i==0)rcOld=rc;
			int chPos=lnInf.firstIndex+i;
			this->DrawCenterChar(pDC,rc,m_strWndTxt.GetAt(chPos));
			//this->DrawAloneChar(pDC,rc,m_strWndTxt.GetAt(chPos));
			rcOld=rc;
		}

	}
	if(sty.m_bHollow)//路径绘制结束
	{
		pDC->EndPath();
		pDC->StrokeAndFillPath();
	}
	//文字输出结束，恢复DC环境
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldBru);
	if(sty.m_bHollow)pDC->SelectObject(oldPen);
	else pDC->SetTextColor(oldClr);
}

	//绘制任务栏窗格中字贴样例
LRESULT CMyView::OnDrawPaneSample(WPARAM wPara,LPARAM l)
{
	CSampleWnd * pWnd=(CSampleWnd*)wPara;//任务空格窗口，绘制前先调整大小
	//pWnd->SetWindowPos(&CWnd::wndTop,0,0,500,500,SWP_NOMOVE);
	CClientDC dc(pWnd);	
	CDC *pDC=&dc;	
	//调整绘制窗口的坐标系统映射空间
	this->AdjustMapSpace(pDC);
	/////////////////
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CCharStyle & sty=pMain->m_charStyle;
	CRect mg=pMain->GetPageMargin();
	//根据样例窗口的大小，求出其实际绘制的大小，即转成百分之一MM
	CSize szPage=this->CalcSampleWndSize();
	int pageW=szPage.cx;
	int pageH=szPage.cy;
	//计算可以打印的高度和宽度
	int w=pageW-mg.left-mg.right;
	int h=pageH-mg.top-mg.bottom;		
	pMain->m_bRecalcPage=TRUE;
	//画出打印范围区域，主要是页边距
	DrawScopeLine(pDC,w,h,mg);
	if(w<0||h<0)return 0;
	DrawGrid2(pDC,w,h,pMain->m_gridStyle .m_cellLength
		,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
		,pMain->m_charStyle.m_bHorz,1);
	//打印页面文字
	this->DrawPageText(pDC,w,h,pMain->m_gridStyle .m_cellLength
		,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
		,pMain->m_charStyle.m_bHorz,1,NULL);
#ifdef DEBUG
	DrawWatermark(pDC,w,h);
#endif
	return 1;
}

// 计算样例预览窗口尺寸，并直接转化成0.01毫米为单位的值
CSize CMyView::CalcSampleWndSize(int *wid,int *hei)
{	
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CRect rc;
	pMain->GetTaskPane()->GetSampleWnd()->GetWindowRect(&rc);
	HDC hDC=::GetDC(pMain->GetTaskPane()->GetSampleWnd()->GetSafeHwnd());
	int xPix=GetDeviceCaps(hDC,HORZRES);
	int yPix=GetDeviceCaps(hDC,VERTRES);
	int xMM=GetDeviceCaps(hDC,HORZSIZE); 
	int yMM=GetDeviceCaps(hDC,VERTSIZE);
	int w=rc.Width()*xMM*100/xPix;
	int h=rc.Height()*yMM*100/yPix;
	if(wid)*wid=w;
	if(hei)*hei=h;	
	::ReleaseDC(pMain->GetTaskPane()->GetSampleWnd()->GetSafeHwnd(),hDC);
	return CSize(w,h);
}

// 调整打印预览窗口和样例预览窗口的坐标映射空间
void CMyView::AdjustMapSpace(CDC* pDC)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CRect mg=pMain->GetPageMargin();
	//实际的打印或屏幕空间
	int xPix=pDC->GetDeviceCaps(HORZRES);
	int yPix=pDC->GetDeviceCaps(VERTRES);
	int xMM=pDC->GetDeviceCaps(HORZSIZE); 
	int yMM=pDC->GetDeviceCaps(VERTSIZE); 
	//计算坐标系窗口空间的大小,默认为打印或屏幕的大小转化成0.01MM为单位
	int wndW=xMM*100;
	int wndH=yMM*100;
	//如果不是打印，则计算窗口空间的逻辑尺寸
	if(!pDC->IsPrinting())	CalcSampleWndSize(&wndW,&wndH);
	////////计算坐标映射视口空间大小,如果是打印，则不用计算
	int viewportW=xPix;
	int viewportH=yPix;
	if(!pDC->IsPrinting())//不是打印进行计算调整
	{
		CRect rcViewport;
		pMain->GetTaskPane()->GetSampleWnd()->GetClientRect(&rcViewport);	
		viewportW=rcViewport.Width();
		viewportH=rcViewport.Height();
	}
	//进行居中方式调整时需用到的距离
	CSize szPrinted;
	CSize szAdjust(this->CalcAdjustSize(pDC,&szPrinted));
	pDC->SetMapMode(MM_ANISOTROPIC/*MM_ISOTROPIC*/);  
	//设置坐标空间窗口范围
	pDC->SetWindowExt(wndW, wndH);  
	BOOL bLTR=pMain->m_charStyle.m_bLToR;//从左到右方向或反向显示
	pDC->SetViewportExt(bLTR?viewportW:-viewportW,viewportH);  
	if(bLTR )
	{
		//考虑居中调整,重设原点位置
		pDC->SetViewportOrg((mg.left+szAdjust.cx)*viewportW/wndW
			,(mg.top+szAdjust.cy)*viewportH/wndH);
	}
	else//右到左，原点移到右边进行绘制
	{
		////////pDC->SetViewportOrg(-(100*xMM-mg.right*xPix)/(100*xMM),mg.top*yPix/(100*yMM));
		//考虑居中调整,重设原点位置
		pDC->SetWindowOrg(wndW-mg.right-szAdjust.cx,-mg.top-szAdjust.cy);

	}
}

void CMyView::OnEnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CEditView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	pMain->GetTaskPane()->GetSampleWnd()->Invalidate();
	this->GetDocument ()->SetModifiedFlag();

}


//void CMyView::OnInitialUpdate()
//{
//	CEditView::OnInitialUpdate();
//	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
//	pMain->ShowPane(pMain->GetTaskPane(),TRUE,0,1);
//	pMain->GetTaskPane()->CollapseAllGroups(0);
//	pMain->GetTaskPane()->GetSampleWnd()->Invalidate();
//	// TODO: 在此添加专用代码和/或调用基类
//}

BOOL CMyView::CreateFont(CCharStyle & sty,CFont *pFont)
{
	BOOL ret=FALSE;
	VERIFY(ret=pFont->CreateFont(
		sty.m_charHeight,                        // nHeight,取绝对高度不要外部空白
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		sty.m_weight,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		sty.m_charset,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		sty.m_fontName)); 
	return ret;
}



void CMyView::OnUpdateTaskpaneGridSplit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strTmp;
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	bool bSplit=pMain->GetTaskPane()->m_bSplitGrid;
	UINT strID=bSplit?IDS_TASKPANE_GRIDSPLIT2:IDS_TASKPANE_GRIDSPLIT;
	BOOL bValid=strTmp.LoadString(strID);
	ASSERT(bValid);
	pCmdUI->SetText(strTmp);
}

// 绘制字格切分线,将字格分成十等分
void CMyView::DrawGridSplitLine(CDC * pDC, CRect & rc)
{
	float wSpace=rc.Width()/10;
	float hSpace=rc.Height()/10;
	for(int n=1;n<10;n++)
	{
		int x=rc.left+n*wSpace;
		int y=rc.top+n*hSpace;
		pDC->MoveTo(x,rc.top);
		pDC->LineTo(x,rc.bottom);
		pDC->MoveTo(rc.left,y);
		pDC->LineTo(rc.right,y);
	}
}

void CMyView::OnTaskpaneGridSplit()
{
	//不能删除否则命令不起用
}

//void CMyView::OnShowWindow(BOOL bShow, UINT nStatus)
//{
//	CEditView::OnShowWindow(bShow, nStatus);
//	//CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();	
//	//if(!pMain->IsPrintPreview())
//	//	pMain->SetStatusInfor(NULL);
//
//}
//画自绘格子图像
void CMyView::DrawOwnGridImg(CDC *pDC,CRect &r)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CImage *pImg=pMain->GetOwnGridImg();
	if(pImg->IsNull())
		return;
	CGridStyle &sty=pMain->m_gridStyle;
	//将绘制的格子缩一线宽
	CRect rc(r);
	rc.left+=sty.m_borderWidth;
	rc.top+=sty.m_borderWidth;
	//sty.m_borderWidth
	if(sty.m_clrBackgroud!=-1)
	{
		//SHADEBLENDCAPS 
		if(!pImg->TransparentBlt(pDC->GetSafeHdc(),rc,sty.m_clrBackgroud))
		{
			pImg->Draw(pDC->GetSafeHdc(),rc,CRect(0,0,pImg->GetWidth(),pImg->GetHeight()));
		}

	}
	else//未设置透明色或有alpha通道的位图，直接绘制
	{
		pImg->Draw(pDC->GetSafeHdc(),rc,CRect(0,0,pImg->GetWidth(),pImg->GetHeight()));
	}
}
// 对于没有进行注册授权使用的用户，在字贴上画一水印。
void CMyView::DrawWatermark(CDC * pDC, int w, int h)
{
	//许多打印机不支持水印打印，直接绘网格线
	CBrush grayBru(HS_DIAGCROSS,RGB(150,150,150));
	int Len=(w<h?w:h)*3/5;
	CGdiObject * oldBru=pDC->SelectObject(&grayBru);
	pDC->Rectangle (&CRect(0,0,Len,Len));
	pDC->SelectObject (oldBru);
	/////////////
//////生成水印图片
////	CString inf1;
////	BOOL bValid=inf1.LoadString(IDS_WATERMARK);
////	ASSERT(bValid);
////	//CClientDC dc(this);
////	//先在内存中生成一个位图
////	CRect rcBmp(0,0,800,800);
////	CDC memDC;
////	memDC.CreateCompatibleDC(pDC);
////	CBitmap bmp;
////	bmp.CreateCompatibleBitmap(pDC,rcBmp.Width(),rcBmp.Height());
////	////bmp.CreateBitmap (rcBmp.Width(),rcBmp.Height(),1,16,NULL);
////	CBitmap * oldBmp=memDC.SelectObject(&bmp);
////	//先将位图真上灰色背景
////	//CRect rc(0,0,w,h);
////	CRect &rc=rcBmp;
////	CBrush grayBru(HS_DIAGCROSS,RGB(0,0,0));
////	memDC.FillRect(&rc,&grayBru);
////	//输出提示信息
////	memDC.SetBkMode(TRANSPARENT   );
////	CFont font;CString fontName;
////	pDC->GetTextFace(fontName);
////	font.CreatePointFont(700,fontName);
////	CFont *oldFont=memDC.SelectObject (&font);
////	memDC.DrawText(inf1,&rc,DT_WORDBREAK|DT_CENTER);
////	memDC.SelectObject (oldFont);
////	//选择出位图,恢复DC原状态,好在下一步进行镜像转换
////	memDC.SelectObject(oldBmp);
////	
////
////	//半透明绘图
////	BLENDFUNCTION blend;
////	blend.BlendOp = AC_SRC_OVER; 
////	blend.BlendFlags = 0; 
////	blend.AlphaFormat = 0; 
////	blend.SourceConstantAlpha =80 /*253*/; 
////
////	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
////	if(!pMain->m_charStyle .m_bLToR)//先做镜像处理	
////	{
////		MirrorBmp(&bmp);		
////	}
////	oldBmp=memDC.SelectObject (&bmp);
////
////
////	//调整位置，绘制水印
////	int Len=(w<h?w:h)*4/5;
////	if(!pDC->AlphaBlend(0,0,Len,Len,
////		&memDC,0,0,rcBmp.Width(),rcBmp.Height(),blend))
////	{
////		//如果失败，直接绘制一个图像
////		pDC->FillRect(&CRect(0,0,Len/2,Len/2),&grayBru);
////	}
////	memDC.SelectObject(oldBmp);	
////	//////////////////////////
////#ifdef DEBUG///////////////
////	CImage img;
////	img.Attach((HBITMAP)bmp.Detach ()); 
////	img.Save (L"a2.bmp");
////#endif
}

// 将水印位图进行镜像处理
void CMyView::MirrorBmp(CBitmap * pBmp)
{
	////BITMAP BMP;
	////pBmp->GetBitmap (&BMP);
	////int w=BMP.bmWidth;
	////int h=BMP.bmHeight;
	////CDC memDC,memDC2;
	////memDC.CreateCompatibleDC(NULL);
	////memDC2.CreateCompatibleDC(NULL);
	////memDC2.SetMapMode (MM_ISOTROPIC );
	////memDC2.SetWindowExt(w,h);
	////memDC2.SetViewportExt (-w,h);
	////memDC2.SetWindowOrg(w,0);
	////CBitmap * oldBmp=memDC.SelectObject (pBmp);
	////CBitmap bmp;
	//////bmp.CreateCompatibleBitmap(&dc,w,h);
	////bmp.CreateBitmapIndirect (&BMP);
	////CBitmap * oldBmp2=memDC2.SelectObject(&bmp);
	////memDC2.StretchBlt (0,0,w,h,&memDC,0,0,w,h,SRCCOPY);
	////memDC.SelectObject(oldBmp);
	////memDC2.SelectObject (oldBmp2);
	////pBmp->DeleteObject ();
	////pBmp->Attach (bmp.Detach ());

	
}
