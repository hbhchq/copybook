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

// ���ֹ���View.h : CMyView ��Ľӿ�
//


#pragma once
#include "setting.h"
#include "mainfrm.h"
#include "afxtempl.h"


//�ı��е������ͳ�����Ϣ����ҪΪ�˴�ӡ��ҳʹ��
struct PosInf
{ 
	//���ַ��������ı��е�����λ��,�س�����Ҳ�������
	UINT firstIndex;
	//���ȣ����ַ�������������\r\n
	UINT length;
	PosInf(){}
	PosInf(UINT idx,UINT len)
	{
		this->firstIndex=idx;
		this->length=len;
	}
	void Set(UINT idx,UINT len)
	{
		this->firstIndex=idx;
		this->length=len;
	}
};
//////����Ķ�����Ϣ
////typedef PosInf ParagInfor;
//��������Ϣ��������ǰ�Ľṹ
typedef PosInf LineInfor;


class CMyView : public CEditView
{
protected: // �������л�����
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// ����
public:
	CMyDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	////afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFilePrintPreview();
	//////���¼����ӡ��ҳ��Ϣ,��Ҫ���������ڴ�ӡԤ��ʱ���޸�����,ˢ�½���ʱ��
	////afx_msg LRESULT OnRecalcPage(WPARAM w,LPARAM l);
	//������������������������
	afx_msg LRESULT OnDrawPaneSample(WPARAM w,LPARAM l);
	DECLARE_MESSAGE_MAP()
public:
	// ���ӡ��ҳ���ı�
	//CString m_strPrintPageTxt;
	//�༭��ͼ�еĴ����ı�������������ҪΪ�����Ч�ʣ�������ӡ��ʹ��
	CString m_strWndTxt;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	////����༭���еĶ�����ı�������Ϣ��ÿ�γ��Ȳ������س�����
	//CArray<ParagInfor,ParagInfor&>m_arrTxtParagInfor;
	//����༭���е��ı��ڴ�ӡʱ�зֳɵ�����Ϣ(���������֣�һ����һ��)�������л��У�ÿ�п��ܳ��Ȳ�һ��
	CArray<LineInfor,LineInfor&>m_arrTxtLineInfor;

	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	// �Ը߶ȣ��ų�ҳ�߾ࣩΪ��������ÿҳ��ʾ����������λͳһΪ0.01����
	int CalcRows(UINT h);
	// ��ҳ��ɴ�ӡ��ȣ��ų�ҳ�߾ࣩΪ������������
	int CalcCols(UINT w);
	//ȡ�ø��ߵ���ʽ
	CGridStyle *  GetGridStyle() const
	{
		CMainFrame *pMF=(CMainFrame *)this->GetParentFrame();
		return &(pMF->m_gridStyle);
	}
	//ȡ�����ֵ���ʽ
	CCharStyle * GetCharStyle() const
	{
		CMainFrame *pMF=(CMainFrame *)this->GetParentFrame();
		return &(pMF->m_charStyle);
	}
	// ͨ�����������������ӡ��ҳ��,ע���Ǻ��Ż����������֣�Ĭ�Ϻ���
	//rowsΪÿҳ������colsΪÿҳ����
	int CalcPages(int rows, int cols,BOOL isHorz=TRUE);
	// �����߻����ɴ�ӡ�ĵķ�Χ����
	void DrawScopeLine(CDC * pDC , int w , int h , CRect  mg);
	//Ϊ�����Ч�ʣ��ڶ��ְ汾����Ҫ�ǻ����㷨��һ����ͬʱ���Ƶ�ǰҳ����ַ�
	void DrawGrid2(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum);

	// ����һ���������ڲ�����,���һ�����ǰһ�����Ӽ�������ߣ���Ҫ�Ǵ����С��м��ʱ�õ�
	void DrawAloneGrid2(CDC* pDC, CRect & r,CRect & oldR,BOOL isHorz);

	
	// // ��ָ����λ�û���һ��������������,
	//void DrawAloneChar(CDC* pDC, CRect & r,TCHAR ch);

//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//
	void DrawGridInside(CDC* pDC, CRect & r);
	//���Ի����ͼ��
	void DrawOwnGridImg(CDC *pDC,CRect &r);

	//Ϊ��ȫ׼ȷ���Ի���ģʽ������
	void DrawRect(CDC* pDC, CRect & rc)
	{
		pDC->MoveTo(rc.TopLeft());
		pDC->LineTo(rc.right,rc.top);
		pDC->LineTo (rc.BottomRight());
		pDC->LineTo(rc.left,rc.bottom);
		pDC->LineTo(rc.TopLeft());
	}
	//����ʮ����
	void DrawShi(CDC* pDC, CRect & r)
	{
		CPoint p=r.CenterPoint();
		pDC->MoveTo(r.left,p.y);
		pDC->LineTo(r.right,p.y);
		pDC->MoveTo(p.x,r.top);
		pDC->LineTo(p.x,r.bottom);
	}
	//���Խ�ʮ����
	void DrawShi2(CDC* pDC, CRect & r)
	{
		pDC->MoveTo(r.TopLeft());
		pDC->LineTo(r.BottomRight());
		pDC->MoveTo (r.right,r.top);
		pDC->LineTo(r.left,r.bottom);
	}
	//����������
	void DrawHui(CDC* pDC, CRect & r)
	{
		CGridStyle *sty=this->GetGridStyle();
		//������ָ�ĸ����
		int h=sty->m_HUI_Rate<100?r.Height()*sty->m_HUI_Rate/100:r.Height();		
		int w=h*sty->m_HUI_Rate_W_H/100;
		if(w>r.Width())w=r.Width();
		//����������
		int deflatX=(r.Width()-w)/2;
		int deflatY=(r.Height()-h)/2;
		CRect rcInside(r);
		rcInside.DeflateRect(deflatX,deflatY);
		//����ƫ��
		rcInside.OffsetRect(0,sty->m_bDownward?sty->m_offsetY:-sty->m_offsetY);

		//////����ƫ��,������Ĭ�Ͼ�������µ�ƫ��
		////int offY=(r.Height()-h)/2;
		////offY=sty->m_bDownward?offY+sty->m_offsetY:offY-sty->m_offsetY;
		////int offX=(r.Width()-w)/2;
		////CPoint p1(r.TopLeft()),p2(r.TopLeft());
		////p2.Offset(w,h);		
		////CRect rc(p1,p2);
		////rc.OffsetRect(offX,offY);
		//����У�飬�����Ƴ��������
		if(rcInside.top<r.top)rcInside.top=r.top;
		if(rcInside.bottom>r.bottom)rcInside.bottom=r.bottom;
		DrawRect(pDC,rcInside);
	}
	//// ���������
	//void DrawHollowChar(CDC* pDC, CRect & r,TCHAR ch);
	//// ����������ʽ��ʼ���������DC����
	//void InitTextOut(CDC* pDC, CCharStyle & sty,COLORREF oldTxtClr,CFont * oldFont,CBrush * oldBruFill, CPen * oldPen);
	////��ԭ�������ʱDC����
	//void RestoreTextOut(CDC * pDC,COLORREF oldTxtClr,CFont * oldFont,CBrush * oldBruFill, CPen * oldPen);


	//// ����ó���ͼ�б༭���ı��еĶ�����
	//int GetParagCount(void){return m_arrTxtParagInfor.GetCount();}
	//// ���ݶ���������������ַ������������س����з�
	//UINT GetParagLen(int paragIdx){return m_arrTxtParagInfor.GetAt(paragIdx).length;}
	//// ���ݶ���������������������ַ��������ı��е�����������س����з�
	//UINT GetParagFirstIndex(int paragIdx){return m_arrTxtParagInfor.GetAt(paragIdx).firstIndex;}

	//// ����༭�����ı��Ķ��䣬�����浽��Ա������
	//void CalcTxtParag(void);
	// ����ʵ����Ҫ��ӡ���з�ʽ��ӡ��������ľ��룬����������һ��ľ����2,������Ա���ӡ�ߴ�
	CSize CalcAdjustSize(CDC * pDC,CSize *szPrinted=0);
	// �ڸ����ľ��������ھ�������ַ�
	void DrawCenterChar(CDC * pDC, CRect & rc, TCHAR ch);
	//�������������Ӽ��������
	void DrawConnectLine(CDC * pDC,CRect & r, CRect & oldR, BOOL bHorz,CGridStyle &gridSty);
	// ����༭�����ı������зֵ�λ����Ϣ,��Ϣ�����ڳ�Ա�����У�����������
	int CalcTxtLines(int lineLen);
	// ���ַ������м�ĳλ�ÿ�ʼ�����ַ�����������ڲ�����ʼλ�õ�λ��������δ�ҵ�����-1
	int FindCh(LPCTSTR begin , int count , TCHAR ch);
	//// ����������λ�ü����е��ַ�λ������������ַ�,lineIdx,Ϊ��ǰҳ����������charPosΪ���е�����
	//TCHAR GetPrintChar(int pageNum,int pageLines,int lineIdx, int charPos);
	// ����ҳ�����ҳ�����������
	void DrawPageText(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum, CPrintInfo* pInfo);
protected:
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	// ��������Ԥ�����ڳߴ磬��ֱ��ת����0.01����Ϊ��λ��ֵ
	CSize CalcSampleWndSize(int *w=NULL,int *h=NULL);
	// ������ӡԤ�����ں�����Ԥ�����ڵ�����ӳ��ռ�
	void AdjustMapSpace(CDC* pDC);
	afx_msg void OnEnChange();
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	virtual void OnInitialUpdate();
	BOOL CreateFont(CCharStyle & sty,CFont *pFont);
	afx_msg void OnUpdateTaskpaneGridSplit(CCmdUI *pCmdUI);
	//bool m_bSplitGrid;
	// �����ָ��з���,���ָ�ֳ�ʮ�ȷ�
	void DrawGridSplitLine(CDC * pDC, CRect & rc);
	afx_msg void OnTaskpaneGridSplit();
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	// ����û�н���ע����Ȩʹ�õ��û����������ϻ�һˮӡ��
	void DrawWatermark(CDC * pDC, int w, int h);
	// ��ˮӡλͼ���о�����
	void MirrorBmp(CBitmap * pBmp);
};

#ifndef _DEBUG  // ���ֹ���2View.cpp �еĵ��԰汾
inline CMyDoc* CMyView::GetDocument() const
   { return reinterpret_cast<CMyDoc*>(m_pDocument); }
#endif

