// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// ���ֹ���View.cpp : CMyView ���ʵ��
//
#include "stdafx.h"
#include "���ֹ���.h"

#include "���ֹ���Doc.h"
#include "���ֹ���View.h"
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
	// ��׼��ӡ����
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

// CMyView ����/����

CMyView::CMyView()
{
	// TODO: �ڴ˴���ӹ������

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//ȥ��ˮƽ������
	cs.style&=~WS_HSCROLL;
	cs.style|=WS_VSCROLL|ES_MULTILINE|ES_WANTRETURN;
	return CEditView::PreCreateWindow(cs);
}

// CMyView ����

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMyView ��ӡ


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
//		//�����ӡ��ҳ��
//		int wid,hei;
//		wid=::GetDeviceCaps(dc,HORZSIZE)*100-margin.left-margin.right;
//		hei=::GetDeviceCaps(dc,VERTSIZE)*100-margin.top-margin.bottom;
//		////�����ı���������
//		this->CalcTxtLines(chSty.m_bHorz?CalcCols(wid):this->CalcRows(hei));
//	}
//	return 1;
//	
//}
BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	BOOL ret=DoPreparePrinting(pInfo);
	//������ɹ�ֱ�ӷ��أ���Ҫԭ�������û��װ��ӡ��
	if(ret==FALSE)return ret;
		//����ע����Ȩ����
	theApp.m_bLicense=theApp.CheckLicence();
	if(!theApp.m_bLicense)
	{
		CString msg;
		BOOL bValid=msg.LoadString(IDS_DONT_PRINT_MSG);
		ASSERT(bValid);
		MessageBox(msg,0,MB_ICONINFORMATION|MB_OK);
	}
	//���и����������ݵĸ��ºͽ���
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	pMain->UpdateData();
	//ע��ҳ��ߴ��Ǻ��׵�λ����ת��
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
	// Ĭ��׼��
	return ret;
}

void CMyView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
		//�ӿ�ܴ���ȡ��ҳ��������Ϣ����ҳ��С�ͱ߾�
		CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
		CRect margin=pMain->GetPageMargin();
		CCharStyle &chSty=pMain->m_charStyle;
		//�����ӡ��ҳ��
		int wid,hei;
		wid=pDC ->GetDeviceCaps(HORZSIZE)*100-margin.left-margin.right;
		hei=pDC ->GetDeviceCaps(VERTSIZE)*100-margin.top-margin.bottom;
		////�����ı���������
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
	// TODO: ��Ӵ�ӡ����е��������
	if(pInfo)
	{
		//��ӡ����
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


// CMyView ���

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyView ��Ϣ�������

void CMyView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	//////////
	AdjustMapSpace(pDC);
	//CEditView::OnPrepareDC(pDC, pInfo);
	//�����������Ҳ���õ������̣����ע�͵���ӡ״̬���
	//if(pDC->IsPrinting()) // Is the DC a printer DC.
	//{
		//CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
		//CRect mg=pMain->GetPageMargin();
		//pDC->SetMapMode(/*MM_ANISOTROPIC*/MM_ISOTROPIC);  
		//int xPix=pDC->GetDeviceCaps(HORZRES);
		//int yPix=pDC->GetDeviceCaps(VERTRES);
		//int xMM=pDC->GetDeviceCaps(HORZSIZE); 
		//int yMM=pDC->GetDeviceCaps(VERTSIZE); 
		////���о��з�ʽ����ʱ���õ��ľ���
		//CSize szPrinted;
		//CSize szAdjust(this->CalcAdjustSize(pDC,&szPrinted));
		//
		//if(pMain->m_charStyle.m_bLToR )
		//{
		//	//�൱��һ��λ����0.01����,��ҪΪ�˷�����������
		//	pDC->SetWindowExt(100*xMM,   100*yMM);  
		//	pDC->SetViewportExt(xPix,yPix);  
		//	//����ԭ��λ��
		//	//pDC->SetViewportOrg(mg.left*xPix/(100*xMM),mg.top*yPix/(100*yMM));
		//	//���Ǿ��е���,����ԭ��λ��
		//	pDC->SetViewportOrg((mg.left+szAdjust.cx)*xPix/(100*xMM)
		//		,(mg.top+szAdjust.cy)*yPix/(100*yMM));
		//}
		//else//�ҵ���ԭ���Ƶ��ұ߽��л���
		//{
		//	pDC->SetWindowExt(100*xMM,   100*yMM);  
		//	pDC->SetViewportExt(-xPix,yPix);  
		//	//����ԭ��λ��
		//	//pDC->SetWindowOrg(100*xMM-mg.right,-mg.top);
		//	////////pDC->SetViewportOrg(-(100*xMM-mg.right*xPix)/(100*xMM),mg.top*yPix/(100*yMM));
		//	//���Ǿ��е���,����ԭ��λ��
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
		//���ƴ�ӡ��Χ//////////////////
		//ȡ��ҳ��С�ߴ�
		int pageW=pDC ->GetDeviceCaps(HORZSIZE)*100;
		int pageH=pDC ->GetDeviceCaps(VERTSIZE)*100;
		//�����ӡ�ĸ߶ȺͿ��
		int w=pageW-mg.left-mg.right;
		int h=pageH-mg.top-mg.bottom;	
		if(pInfo->m_bPreview)
		{
			//������ӡ��Χ������Ҫ��ҳ�߾�
			DrawScopeLine(pDC,w,h,mg);
		}

		////���δע������ʾ��ʾ��Ϣ�������ڴ�ӡ��ҳ���ϼ�һˮӡͼ
		if(!theApp.m_bLicense)
		{
			DrawWatermark(pDC,w,h);			
		}
		DrawGrid2(pDC,w,h,pMain->m_gridStyle .m_cellLength
			,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
			,pMain->m_charStyle.m_bHorz,pInfo->m_nCurPage);
		//��ӡҳ������
		this->DrawPageText(pDC,w,h,pMain->m_gridStyle .m_cellLength
			,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
			,pMain->m_charStyle.m_bHorz,pInfo->m_nCurPage,pInfo);


}


// �Ը߶�Ϊ��������ÿҳ��ʾ����������λͳһΪ0.01����
int CMyView::CalcRows(UINT h)
{
	CGridStyle *pGrid=this->GetGridStyle();
	return (h+pGrid->m_rowSpace)/(pGrid->m_cellLength+pGrid->m_rowSpace);
	
}

// ��ҳ����Ϊ������������
int CMyView::CalcCols(UINT w)
{
	CGridStyle *pGrid=this->GetGridStyle();
	return (w+pGrid->m_colSpace)/(pGrid->m_cellLength+pGrid->m_colSpace);
}

	// ͨ�����������������ӡ��ҳ��,ע���Ǻ��Ż����������֣�Ĭ�Ϻ���
	//rowsΪÿҳ������colsΪÿҳ����
int CMyView::CalcPages(int  rows, int cols,BOOL isHorz)
{
	//ÿҳ����
	int linesPerPage=isHorz?rows:cols;
	//������
	int pageLines=this->m_arrTxtLineInfor.GetCount();
	return ceil( (double)pageLines/(double)linesPerPage);
	
}

// �����߻����ɴ�ӡ�ĵķ�Χ����
void CMyView::DrawScopeLine(CDC * pDC , int w , int h , CRect  mg)
{

	//�Թ̶����Ȼ���Χ������
	mg.top=mg.left=mg.right=mg.bottom=1000;
	//���Ȼ�ȡ���е����ľ��룬Ȼ���������
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
		//������ӡ��Χ
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
		//��ԭDC
		pDC->SelectObject(oldP);
		pDC->SetWindowOrg(oldOrg);

}


// // ��ָ����λ�û���һ��������������,
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
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
//	CEditView::OnLButtonDblClk(nFlags, point);
//	//�Ŵ�3��
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
		//����ֱ��
		pDC->MoveTo(r.left+x,r.top);
		pDC->LineTo(r.left+x,r.bottom);
		pDC->MoveTo(r.right -x,r.top);
		pDC->LineTo(r.right -x,r.bottom);
		break;
		}
	case GRIDCATEGORY::HUI://�ظ�
		DrawHui(pDC,r);
		break;
	case GRIDCATEGORY::TIAN_HUI://��ظ�
		DrawShi(pDC,r);
		DrawHui(pDC,r);
		break;
	case GRIDCATEGORY::MI_HUI://�׻ظ�
		DrawShi(pDC,r);
		DrawShi2(pDC,r);
		DrawHui(pDC,r);
		break;

	}
	pDC->SelectObject(oldP);
}

//// ���������
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
//// ����������ʽ��ʼ���������DC����
//void CMyView::InitTextOut(CDC* pDC, CCharStyle & sty,COLORREF oldTxtClr,CFont * oldFont,CBrush * oldBruFill, CPen * oldPen)
//{
//	//�������ֶ��뷽ʽ
//	pDC->SetTextAlign(TA_CENTER|TA_TOP);
//	pDC->SetBkMode(TRANSPARENT);
//	//��ʼ������
//	CFont font;
//	VERIFY(font.CreateFont(
//		sty.m_charHeight,                        // nHeight,ȡ���Ը߶Ȳ�Ҫ�ⲿ�հ�
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
//	else//�����ֻ��ƱȽϸ���
//	{
//		//���������͵���ʽ
//		DWORD penstyle=PS_GEOMETRIC;
//		if(sty.m_bSolid)
//			penstyle|=PS_SOLID;
//		else
//			penstyle|=PS_DOT;
//
//		//����������õ��ı�,ˢ�Ӷ���
//		LOGBRUSH lb;
//		lb.lbStyle    =      BS_SOLID ;
//		lb.lbColor    =      sty.m_color;
//		lb.lbHatch    =      0 ;
//		CPen *pen=new CPen(penstyle,1,&lb);
//		//���û��ֵĻ���
//		oldPen=pDC->SelectObject(pen);
//		pen->Detach();
//		delete pen;
//		//���������ˢ
//		CBrush *bruFill=new CBrush(pDC->GetBkColor());
//		oldBruFill=pDC->SelectObject(bruFill);	
//		bruFill->Detach(); 
//		delete bruFill;
//	}
//
//}

//
// ����ʵ����Ҫ��ӡ���з�ʽ��ӡ��������ľ��룬����������һ��ľ����2,������Ա���ӡ�ߴ�
CSize CMyView::CalcAdjustSize(CDC * pDC,CSize *szPrinted)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CRect mg=pMain->GetPageMargin();
	//ȡ��ҳ��С�ߴ磬ת��Ϊ0.01����
	int pageW=pDC ->GetDeviceCaps(HORZSIZE)*100;
	int pageH=pDC ->GetDeviceCaps(VERTSIZE)*100;
	///////////�����Ԥ�����棬ҳ��ߴ�������¼���
	if(!pDC->IsPrinting())
	{
		this->CalcSampleWndSize(&pageW,&pageH);
	}
	///////////////////////////////////////////////
	//�����ӡ�ĸ߶ȺͿ��
	int w=pageW-mg.left-mg.right;
	int h=pageH-mg.top-mg.bottom;	
	//����ʵ�ʴ�ӡ������������
	int rows=this->CalcRows(h);
	int cols=this->CalcCols(w);
	CGridStyle &gridSty=pMain->m_gridStyle;
	CPageLayout &pageSet=pMain->m_pageLayout;
	//ʵ�ʴ�ӡ�ָ����õ��ĳߴ磬����һ��ľ�����е�������ʹ���д�ӡ
	int cx=(gridSty.m_cellLength+gridSty.m_colSpace)*cols-gridSty.m_colSpace;
	int cy=(gridSty.m_cellLength+gridSty.m_rowSpace)*rows-gridSty.m_rowSpace;
	//���ݵ�ǰ����ľ���ģʽ���е���
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

// �ڸ����ľ��������ھ�������ַ�
void CMyView::DrawCenterChar(CDC * pDC, CRect & rc, TCHAR ch)
{
 	CCharStyle * sty=this->GetCharStyle();
	//drawText���ҵ�����������ʱ������
	////int y=rc.top;
	CSize sz=pDC->GetTextExtent(&ch,1);
	int deflateY=(rc.Height()-sz.cy)/2;
	CRect rcActual(rc);
	rcActual.DeflateRect(0,deflateY);
	//////�������õ����ַ�������ƫ����
	rcActual.OffsetRect(0,sty->m_bDownward?sty->m_offsetY:-sty->m_offsetY);
	pDC->TextOut(rcActual.CenterPoint().x,rcActual.top,&ch,1);
}

//Ϊ�����Ч�ʣ��ڶ��ְ汾��
void CMyView::DrawGrid2(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum)
{
	if(w<=0||h<=0)return;
	int rows=this->CalcRows(h);
	int cols=this->CalcCols(w);
	//��������
	int linesCount=isHorz?rows:cols;
	//ÿ���ĸ�����
	int cellsCount=isHorz?cols:rows;
	//��һ���Ӿ���
	CRect rcOld(0,0,size,size);
	//�����л��Ƶĸ��Ӿ���
	CRect rc(rcOld);
	//��������ҳ��������,���ø��ӵ�3���߿�
	//�����Ϊʵ��
	CGridStyle *sty=this->GetGridStyle();
	CPen pen(PS_SOLID,sty->m_borderWidth*3,sty->m_color);
	CPen * oldP=pDC->SelectObject(&pen);
	CPoint endPagePt(cols*(size+cSpc)-cSpc,rows*(size+rSpc)-rSpc);
	CRect rcFrm(rc.TopLeft(),endPagePt);
	//rcFrm.InflateRect(sty->m_borderWidth*2,sty->m_borderWidth*2);
	this->DrawRect(pDC,rcFrm);
	//�ָ���ǰ�ı�
	pDC->SelectObject(oldP);

	for(int ln=0;ln<linesCount;ln++)
	{
		//�����Ÿ��ӵ����
		int lnOffsetX=ln*(size+cSpc);
		int lnOffsetY=ln*(size+rSpc);
		if(isHorz)rcOld.MoveToY(lnOffsetY);
		else rcOld.MoveToX(lnOffsetX);
		rc=rcOld;
		//����һ�Ÿ���
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

// ����һ���������ڲ�����,���һ�����ǰһ�����Ӽ�������ߣ���Ҫ�Ǵ����С��м��ʱ�õ�
void CMyView::DrawAloneGrid2(CDC* pDC, CRect & r,CRect & oldR,BOOL isHorz)
{

	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CGridStyle &sty=pMain->m_gridStyle;
	//�����Ϊʵ��
	CPen pen(PS_SOLID,sty.m_borderWidth,sty.m_color);
	CPen * oldP=pDC->SelectObject(&pen);
	//�������Ӳ��ص����Ҳ����沢��δ���У��Ȼ���������������ߣ�
	DrawConnectLine(pDC,r,oldR,isHorz,sty);
	switch(sty.m_category)
	{
	case GRIDCATEGORY::NONE://�ޱ߿���ߣ��������
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
		//���������߶Σ��Ȼ����ߣ�������ָ񿴲��������//
		DrawGridInside(pDC,r);
		//���������,ֱ�ӻ����ο��߲����غϣ�ֻ�ܻ���
		//pDC->Rectangle(r.left,r.top,r.right+1,r.bottom+1);
		DrawRect(pDC,r);
	}
	pDC->SelectObject(oldP );
	//���Ի����ͼ��
	if(sty.m_bOwnerDraw)
		DrawOwnGridImg(pDC,r);
	//����ʮ�ȷ���
	CPen penInside(sty.m_lineType,sty.m_lineWidth,sty.m_color);
	oldP=pDC->SelectObject(&penInside);
	//�����Ԥ�����ڿ��Ի�ʮ�ȷ��ߣ��Թ۲�ʻ��ṹλ��
	if(pMain->GetTaskPane()->m_bSplitGrid&&!pMain->IsPrintPreview())
		DrawGridSplitLine(pDC,r);
	pDC->SelectObject(oldP );


}
void CMyView::DrawConnectLine(CDC * pDC,CRect & r, CRect & oldR, BOOL isHorz,CGridStyle &gridSty)
{
	//�ޱ߿���ߣ�Ҳ����������
	if(gridSty.m_category==GRIDCATEGORY::NONE)return ;
	//�������Ӳ��ص������м��,�������ߣ�Ҫ�����Ƿ�ֻ�����߻����ߵ����
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

// ����༭�����ı������зֵ�λ����Ϣ,��Ϣ�����ڳ�Ա�����У�����������
int CMyView::CalcTxtLines(int lineLen)
{
	//����δ򿪣������
	this->m_arrTxtLineInfor.RemoveAll();
	if(lineLen<1)return 0;
	CEdit & edit=GetEditCtrl();
	//������ʱ��ȡ�����е��ַ��������ں��淴�����ʱѭ������
	edit.GetWindowText(m_strWndTxt);	
	if(m_strWndTxt.IsEmpty())return 0;
	//�ַ��������ִ��е�λ������������\r\n
	int idx=0;

	LPCTSTR pszTxt=(LPCTSTR)m_strWndTxt;
	int txtLen=m_strWndTxt.GetLength();
	LineInfor inf(idx,lineLen);
	//�Ƿ�����һ���б�־
	BOOL bAddBlank=FALSE;
	while(idx<txtLen)
	{
		//��ȫ����������������ر����ִ���βʱ
		int sz=(idx+lineLen<txtLen?lineLen:txtLen-idx);
		//����\r��\n;
		int posR=FindCh(pszTxt+idx,sz,L'\r');
		//TCHAR * pR=StrChr(pszTmp,L'\r');
		//�ж�ʵ���еĳ��ȣ��лس�������ֻ���س�ǰ������Ϊʵ���г�
		int lenActual=(posR==-1?sz:posR);
		//��������ߴ���´η��е�λ��
		inf.Set(idx,lenActual);
		this->m_arrTxtLineInfor.Add(inf);
		//���ǻس��뻻������һ���
		idx+=(posR==-1?lenActual:lenActual+2);

	}
	//������һ��Ϊ�յĻ���,�����Ѿ��ֺõ�����Ϣ�н��Ѿ�������\n����һ��
	if(*(pszTxt+txtLen-1)==L'\n')
	{
		int lastLineCharIdx=m_arrTxtLineInfor.GetAt(m_arrTxtLineInfor.GetCount()-1).firstIndex;
		int l=txtLen-lastLineCharIdx;
		if(l>=lineLen)//�϶����������س������ټ�һ��
		{
			inf.Set(idx,0);
			m_arrTxtLineInfor.Add(inf);
		}
	}

#ifdef DEBUG/////////////////////
	//��ʾ���еĶ�����Ϣ
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

// ���ַ������м�ĳλ�ÿ�ʼ�����ַ�����������ڲ�����ʼλ�õ�λ��������δ�ҵ�����-1
int CMyView::FindCh(LPCTSTR begin , int count , TCHAR ch)
{
	for(int n=0;n<count;n++)
	{
		if(*(begin+n)==ch)
			return n;
	}
	return -1;
}

////// ����������λ�ü����е��ַ�λ������������ַ�,lineIdx,Ϊ��ǰҳ����������charPosΪ���е�����
////TCHAR CMyView::GetPrintChar(int pageNum,int pageLines,int lineIdx, int charPos)
////{
////	int firstLineIdx=(pageNum-1)*pageLines;
////	//����ҳ���е�����λ��
////	int lineIdxInAll=firstLineIdx+lineIdx;
////	ASSERT(lineIdxInAll>=0);
////	//����������ȫ��������ֻ�軭�ձ��
////	if(lineIdxInAll>=m_arrTxtLineInfor.GetCount())
////		return  TCHAR(0);
////	LineInfor ln=m_arrTxtLineInfor.GetAt(lineIdxInAll);
////	if(charPos>=ln.length)//�հ��У�һ��Ϊ�����β
////	{
////		return TCHAR(0);
////	}
////	int index=ln.firstIndex+charPos;
////	CString &txt=m_strWndTxt;
////	return txt.GetAt(index);
////}

// ����ҳ�����ҳ�����������
void CMyView::DrawPageText(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum, CPrintInfo* pInfo)
{
	if(w<=0||h<=0)return;
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CCharStyle & sty=pMain->m_charStyle;
	//�������ֶ��뷽ʽ
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
	//�������ʱȫ����·���������Ե����ַ���·��
	if(sty.m_bHollow)
	{	
		oldPen=pDC->SelectObject(&pen);
		//////////��ʼ·������/////
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
	//Ϊ�˷�ֹԤ��ʱ��ͬ���޸ĸ�������,���ִ���ÿ�����¼����ҳ��Ϣ
	//if(pMain->m_bRecalcPage)
	//{
		CalcTxtLines(isHorz?cols:rows);
		int pageCount=this->CalcPages(rows,cols,isHorz);
		if(pInfo)	pInfo->SetMaxPage(pageCount);
		pMain->m_bRecalcPage=FALSE;
	//}
	//����״̬����Ϣ
	if(pInfo)
	{
		CString inf;
		CString fmt;fmt.LoadString(IDS_PREVIEW_PAGE_INFOR);
		inf.Format(fmt,pInfo->m_nCurPage,pInfo->GetMaxPage());
		pMain->SetStatusInfor(inf);
	}
	////////////////////////////////////
	//��������
	int linesCount=isHorz?rows:cols;
	//��һ���Ӿ���
	CRect rcOld(0,0,size,size);
	//�����л��Ƶĸ��Ӿ���
	CRect rc(rcOld);
	//�ַ����������
	int charLnFirst=(pageNum-1)*linesCount;
	int charLnLast=(pageNum)*linesCount;//������ĩ������
	if(charLnLast>=m_arrTxtLineInfor.GetCount())
		charLnLast=m_arrTxtLineInfor.GetCount();
	//��ǰҳ��������ֵ�����
	int drawLnCount=charLnLast-charLnFirst;
	for(int ln=0;ln<drawLnCount;ln++)
	{
		//�����Ÿ��ӵ����
		int lnOffsetX=ln*(size+cSpc);
		int lnOffsetY=ln*(size+rSpc);
		if(isHorz)rcOld.MoveToY(lnOffsetY);
		else rcOld.MoveToX(lnOffsetX);
		rc=rcOld;
		//����һ���ַ�
		LineInfor lnInf=m_arrTxtLineInfor.GetAt(ln+charLnFirst);
			//ÿ���ĸ�����
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
	if(sty.m_bHollow)//·�����ƽ���
	{
		pDC->EndPath();
		pDC->StrokeAndFillPath();
	}
	//��������������ָ�DC����
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldBru);
	if(sty.m_bHollow)pDC->SelectObject(oldPen);
	else pDC->SetTextColor(oldClr);
}

	//������������������������
LRESULT CMyView::OnDrawPaneSample(WPARAM wPara,LPARAM l)
{
	CSampleWnd * pWnd=(CSampleWnd*)wPara;//����ո񴰿ڣ�����ǰ�ȵ�����С
	//pWnd->SetWindowPos(&CWnd::wndTop,0,0,500,500,SWP_NOMOVE);
	CClientDC dc(pWnd);	
	CDC *pDC=&dc;	
	//�������ƴ��ڵ�����ϵͳӳ��ռ�
	this->AdjustMapSpace(pDC);
	/////////////////
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CCharStyle & sty=pMain->m_charStyle;
	CRect mg=pMain->GetPageMargin();
	//�����������ڵĴ�С�������ʵ�ʻ��ƵĴ�С����ת�ɰٷ�֮һMM
	CSize szPage=this->CalcSampleWndSize();
	int pageW=szPage.cx;
	int pageH=szPage.cy;
	//������Դ�ӡ�ĸ߶ȺͿ��
	int w=pageW-mg.left-mg.right;
	int h=pageH-mg.top-mg.bottom;		
	pMain->m_bRecalcPage=TRUE;
	//������ӡ��Χ������Ҫ��ҳ�߾�
	DrawScopeLine(pDC,w,h,mg);
	if(w<0||h<0)return 0;
	DrawGrid2(pDC,w,h,pMain->m_gridStyle .m_cellLength
		,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
		,pMain->m_charStyle.m_bHorz,1);
	//��ӡҳ������
	this->DrawPageText(pDC,w,h,pMain->m_gridStyle .m_cellLength
		,pMain->m_gridStyle.m_rowSpace,pMain->m_gridStyle.m_colSpace
		,pMain->m_charStyle.m_bHorz,1,NULL);
#ifdef DEBUG
	DrawWatermark(pDC,w,h);
#endif
	return 1;
}

// ��������Ԥ�����ڳߴ磬��ֱ��ת����0.01����Ϊ��λ��ֵ
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

// ������ӡԤ�����ں�����Ԥ�����ڵ�����ӳ��ռ�
void CMyView::AdjustMapSpace(CDC* pDC)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CRect mg=pMain->GetPageMargin();
	//ʵ�ʵĴ�ӡ����Ļ�ռ�
	int xPix=pDC->GetDeviceCaps(HORZRES);
	int yPix=pDC->GetDeviceCaps(VERTRES);
	int xMM=pDC->GetDeviceCaps(HORZSIZE); 
	int yMM=pDC->GetDeviceCaps(VERTSIZE); 
	//��������ϵ���ڿռ�Ĵ�С,Ĭ��Ϊ��ӡ����Ļ�Ĵ�Сת����0.01MMΪ��λ
	int wndW=xMM*100;
	int wndH=yMM*100;
	//������Ǵ�ӡ������㴰�ڿռ���߼��ߴ�
	if(!pDC->IsPrinting())	CalcSampleWndSize(&wndW,&wndH);
	////////��������ӳ���ӿڿռ��С,����Ǵ�ӡ�����ü���
	int viewportW=xPix;
	int viewportH=yPix;
	if(!pDC->IsPrinting())//���Ǵ�ӡ���м������
	{
		CRect rcViewport;
		pMain->GetTaskPane()->GetSampleWnd()->GetClientRect(&rcViewport);	
		viewportW=rcViewport.Width();
		viewportH=rcViewport.Height();
	}
	//���о��з�ʽ����ʱ���õ��ľ���
	CSize szPrinted;
	CSize szAdjust(this->CalcAdjustSize(pDC,&szPrinted));
	pDC->SetMapMode(MM_ANISOTROPIC/*MM_ISOTROPIC*/);  
	//��������ռ䴰�ڷ�Χ
	pDC->SetWindowExt(wndW, wndH);  
	BOOL bLTR=pMain->m_charStyle.m_bLToR;//�����ҷ��������ʾ
	pDC->SetViewportExt(bLTR?viewportW:-viewportW,viewportH);  
	if(bLTR )
	{
		//���Ǿ��е���,����ԭ��λ��
		pDC->SetViewportOrg((mg.left+szAdjust.cx)*viewportW/wndW
			,(mg.top+szAdjust.cy)*viewportH/wndH);
	}
	else//�ҵ���ԭ���Ƶ��ұ߽��л���
	{
		////////pDC->SetViewportOrg(-(100*xMM-mg.right*xPix)/(100*xMM),mg.top*yPix/(100*yMM));
		//���Ǿ��е���,����ԭ��λ��
		pDC->SetWindowOrg(wndW-mg.right-szAdjust.cx,-mg.top-szAdjust.cy);

	}
}

void CMyView::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEditView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO: �ڴ����ר�ô����/����û���
//}

BOOL CMyView::CreateFont(CCharStyle & sty,CFont *pFont)
{
	BOOL ret=FALSE;
	VERIFY(ret=pFont->CreateFont(
		sty.m_charHeight,                        // nHeight,ȡ���Ը߶Ȳ�Ҫ�ⲿ�հ�
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
	// TODO: �ڴ������������û����洦��������
	CString strTmp;
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	bool bSplit=pMain->GetTaskPane()->m_bSplitGrid;
	UINT strID=bSplit?IDS_TASKPANE_GRIDSPLIT2:IDS_TASKPANE_GRIDSPLIT;
	BOOL bValid=strTmp.LoadString(strID);
	ASSERT(bValid);
	pCmdUI->SetText(strTmp);
}

// �����ָ��з���,���ָ�ֳ�ʮ�ȷ�
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
	//����ɾ�������������
}

//void CMyView::OnShowWindow(BOOL bShow, UINT nStatus)
//{
//	CEditView::OnShowWindow(bShow, nStatus);
//	//CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();	
//	//if(!pMain->IsPrintPreview())
//	//	pMain->SetStatusInfor(NULL);
//
//}
//���Ի����ͼ��
void CMyView::DrawOwnGridImg(CDC *pDC,CRect &r)
{
	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
	CImage *pImg=pMain->GetOwnGridImg();
	if(pImg->IsNull())
		return;
	CGridStyle &sty=pMain->m_gridStyle;
	//�����Ƶĸ�����һ�߿�
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
	else//δ����͸��ɫ����alphaͨ����λͼ��ֱ�ӻ���
	{
		pImg->Draw(pDC->GetSafeHdc(),rc,CRect(0,0,pImg->GetWidth(),pImg->GetHeight()));
	}
}
// ����û�н���ע����Ȩʹ�õ��û����������ϻ�һˮӡ��
void CMyView::DrawWatermark(CDC * pDC, int w, int h)
{
	//����ӡ����֧��ˮӡ��ӡ��ֱ�ӻ�������
	CBrush grayBru(HS_DIAGCROSS,RGB(150,150,150));
	int Len=(w<h?w:h)*3/5;
	CGdiObject * oldBru=pDC->SelectObject(&grayBru);
	pDC->Rectangle (&CRect(0,0,Len,Len));
	pDC->SelectObject (oldBru);
	/////////////
//////����ˮӡͼƬ
////	CString inf1;
////	BOOL bValid=inf1.LoadString(IDS_WATERMARK);
////	ASSERT(bValid);
////	//CClientDC dc(this);
////	//�����ڴ�������һ��λͼ
////	CRect rcBmp(0,0,800,800);
////	CDC memDC;
////	memDC.CreateCompatibleDC(pDC);
////	CBitmap bmp;
////	bmp.CreateCompatibleBitmap(pDC,rcBmp.Width(),rcBmp.Height());
////	////bmp.CreateBitmap (rcBmp.Width(),rcBmp.Height(),1,16,NULL);
////	CBitmap * oldBmp=memDC.SelectObject(&bmp);
////	//�Ƚ�λͼ���ϻ�ɫ����
////	//CRect rc(0,0,w,h);
////	CRect &rc=rcBmp;
////	CBrush grayBru(HS_DIAGCROSS,RGB(0,0,0));
////	memDC.FillRect(&rc,&grayBru);
////	//�����ʾ��Ϣ
////	memDC.SetBkMode(TRANSPARENT   );
////	CFont font;CString fontName;
////	pDC->GetTextFace(fontName);
////	font.CreatePointFont(700,fontName);
////	CFont *oldFont=memDC.SelectObject (&font);
////	memDC.DrawText(inf1,&rc,DT_WORDBREAK|DT_CENTER);
////	memDC.SelectObject (oldFont);
////	//ѡ���λͼ,�ָ�DCԭ״̬,������һ�����о���ת��
////	memDC.SelectObject(oldBmp);
////	
////
////	//��͸����ͼ
////	BLENDFUNCTION blend;
////	blend.BlendOp = AC_SRC_OVER; 
////	blend.BlendFlags = 0; 
////	blend.AlphaFormat = 0; 
////	blend.SourceConstantAlpha =80 /*253*/; 
////
////	CMainFrame * pMain=(CMainFrame * )this->GetParentFrame ();
////	if(!pMain->m_charStyle .m_bLToR)//����������	
////	{
////		MirrorBmp(&bmp);		
////	}
////	oldBmp=memDC.SelectObject (&bmp);
////
////
////	//����λ�ã�����ˮӡ
////	int Len=(w<h?w:h)*4/5;
////	if(!pDC->AlphaBlend(0,0,Len,Len,
////		&memDC,0,0,rcBmp.Width(),rcBmp.Height(),blend))
////	{
////		//���ʧ�ܣ�ֱ�ӻ���һ��ͼ��
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

// ��ˮӡλͼ���о�����
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
