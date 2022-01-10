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

// 练字工具View.h : CMyView 类的接口
//


#pragma once
#include "setting.h"
#include "mainfrm.h"
#include "afxtempl.h"


//文本中的索引和长度信息，主要为了打印分页使用
struct PosInf
{ 
	//首字符在整个文本中的索引位置,回车换行也参与计数
	UINT firstIndex;
	//长度，即字符个数，不包括\r\n
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
//////定义的段落信息
////typedef PosInf ParagInfor;
//定义行信息，仍用以前的结构
typedef PosInf LineInfor;


class CMyView : public CEditView
{
protected: // 仅从序列化创建
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// 属性
public:
	CMyDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	////afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFilePrintPreview();
	//////重新计算打印分页信息,主要是用于正在打印预览时，修改设置,刷新界面时用
	////afx_msg LRESULT OnRecalcPage(WPARAM w,LPARAM l);
	//绘制任务栏窗格中字贴样例
	afx_msg LRESULT OnDrawPaneSample(WPARAM w,LPARAM l);
	DECLARE_MESSAGE_MAP()
public:
	// 需打印的页的文本
	//CString m_strPrintPageTxt;
	//编辑视图中的窗口文本，保存下来主要为了提高效率，以利打印进使用
	CString m_strWndTxt;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	////保存编辑框中的段落的文本长度信息，每段长度不包括回车换行
	//CArray<ParagInfor,ParagInfor&>m_arrTxtParagInfor;
	//保存编辑框中的文本在打印时切分成的条信息(若竖排文字，一列算一条)，由于有换行，每行可能长度不一样
	CArray<LineInfor,LineInfor&>m_arrTxtLineInfor;

	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	// 以高度（排除页边距）为参数计算每页显示的行数，单位统一为0.01毫米
	int CalcRows(UINT h);
	// 以页面可打印宽度（排除页边距）为参数计算列数
	int CalcCols(UINT w);
	//取得格线的样式
	CGridStyle *  GetGridStyle() const
	{
		CMainFrame *pMF=(CMainFrame *)this->GetParentFrame();
		return &(pMF->m_gridStyle);
	}
	//取得文字的样式
	CCharStyle * GetCharStyle() const
	{
		CMainFrame *pMF=(CMainFrame *)this->GetParentFrame();
		return &(pMF->m_charStyle);
	}
	// 通过行数列数计算而打印的页数,注意是横排还是竖排文字，默认横排
	//rows为每页行数，cols为每页列数
	int CalcPages(int rows, int cols,BOOL isHorz=TRUE);
	// 用虚线画出可打印的的范围区域
	void DrawScopeLine(CDC * pDC , int w , int h , CRect  mg);
	//为了提高效率，第二种版本，主要是绘制算法不一样，同时绘制当前页面的字符
	void DrawGrid2(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum);

	// 绘制一个个单格及内部线条,并且画出与前一个格子间的连接线，主要是存在行、列间距时用到
	void DrawAloneGrid2(CDC* pDC, CRect & r,CRect & oldR,BOOL isHorz);

	
	// // 在指定的位置绘制一个个单独的文字,
	//void DrawAloneChar(CDC* pDC, CRect & r,TCHAR ch);

//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//
	void DrawGridInside(CDC* pDC, CRect & r);
	//画自绘格子图像
	void DrawOwnGridImg(CDC *pDC,CRect &r);

	//为完全准确，以画线模式画矩形
	void DrawRect(CDC* pDC, CRect & rc)
	{
		pDC->MoveTo(rc.TopLeft());
		pDC->LineTo(rc.right,rc.top);
		pDC->LineTo (rc.BottomRight());
		pDC->LineTo(rc.left,rc.bottom);
		pDC->LineTo(rc.TopLeft());
	}
	//画正十字线
	void DrawShi(CDC* pDC, CRect & r)
	{
		CPoint p=r.CenterPoint();
		pDC->MoveTo(r.left,p.y);
		pDC->LineTo(r.right,p.y);
		pDC->MoveTo(p.x,r.top);
		pDC->LineTo(p.x,r.bottom);
	}
	//画对角十字线
	void DrawShi2(CDC* pDC, CRect & r)
	{
		pDC->MoveTo(r.TopLeft());
		pDC->LineTo(r.BottomRight());
		pDC->MoveTo (r.right,r.top);
		pDC->LineTo(r.left,r.bottom);
	}
	//画回字内线
	void DrawHui(CDC* pDC, CRect & r)
	{
		CGridStyle *sty=this->GetGridStyle();
		//计算回字格的高与宽
		int h=sty->m_HUI_Rate<100?r.Height()*sty->m_HUI_Rate/100:r.Height();		
		int w=h*sty->m_HUI_Rate_W_H/100;
		if(w>r.Width())w=r.Width();
		//计算收缩量
		int deflatX=(r.Width()-w)/2;
		int deflatY=(r.Height()-h)/2;
		CRect rcInside(r);
		rcInside.DeflateRect(deflatX,deflatY);
		//计算偏移
		rcInside.OffsetRect(0,sty->m_bDownward?sty->m_offsetY:-sty->m_offsetY);

		//////计算偏移,首先是默认居中情况下的偏移
		////int offY=(r.Height()-h)/2;
		////offY=sty->m_bDownward?offY+sty->m_offsetY:offY-sty->m_offsetY;
		////int offX=(r.Width()-w)/2;
		////CPoint p1(r.TopLeft()),p2(r.TopLeft());
		////p2.Offset(w,h);		
		////CRect rc(p1,p2);
		////rc.OffsetRect(offX,offY);
		//进行校验，以免移出外面格子
		if(rcInside.top<r.top)rcInside.top=r.top;
		if(rcInside.bottom>r.bottom)rcInside.bottom=r.bottom;
		DrawRect(pDC,rcInside);
	}
	//// 输出空心字
	//void DrawHollowChar(CDC* pDC, CRect & r,TCHAR ch);
	//// 根据文字样式初始化文字输出DC环境
	//void InitTextOut(CDC* pDC, CCharStyle & sty,COLORREF oldTxtClr,CFont * oldFont,CBrush * oldBruFill, CPen * oldPen);
	////还原文字输出时DC环境
	//void RestoreTextOut(CDC * pDC,COLORREF oldTxtClr,CFont * oldFont,CBrush * oldBruFill, CPen * oldPen);


	//// 计算得出视图中编辑框文本中的段落数
	//int GetParagCount(void){return m_arrTxtParagInfor.GetCount();}
	//// 根据段落索引，计算出字符数，不包括回车换行符
	//UINT GetParagLen(int paragIdx){return m_arrTxtParagInfor.GetAt(paragIdx).length;}
	//// 根据段落索引，计算出段落首字符在整个文本中的索引，计算回车换行符
	//UINT GetParagFirstIndex(int paragIdx){return m_arrTxtParagInfor.GetAt(paragIdx).firstIndex;}

	//// 计算编辑框中文本的段落，并保存到成员变量中
	//void CalcTxtParag(void);
	// 计算实际需要打印居中方式打印，需调整的距离，即减除不足一格的距离除2,输出可以被打印尺寸
	CSize CalcAdjustSize(CDC * pDC,CSize *szPrinted=0);
	// 在给定的矩形区域内居中输出字符
	void DrawCenterChar(CDC * pDC, CRect & rc, TCHAR ch);
	//画出相邻两格子间的连接线
	void DrawConnectLine(CDC * pDC,CRect & r, CRect & oldR, BOOL bHorz,CGridStyle &gridSty);
	// 计算编辑框中文本按行切分的位置信息,信息保存在成员变量中，返回总行数
	int CalcTxtLines(int lineLen);
	// 从字符串的中间某位置开始查找字符，返回相对于查找起始位置的位置索引，未找到返回-1
	int FindCh(LPCTSTR begin , int count , TCHAR ch);
	//// 根据条索引位置及条中的字符位置求需输出的字符,lineIdx,为当前页的行索引，charPos为行中的索引
	//TCHAR GetPrintChar(int pageNum,int pageLines,int lineIdx, int charPos);
	// 根据页码绘制页面的所有文字
	void DrawPageText(CDC * pDC , int w , int h,int size,int rSpc,int cSpc ,BOOL isHorz,int pageNum, CPrintInfo* pInfo);
protected:
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	// 计算样例预览窗口尺寸，并直接转化成0.01毫米为单位的值
	CSize CalcSampleWndSize(int *w=NULL,int *h=NULL);
	// 调整打印预览窗口和样例预览窗口的坐标映射空间
	void AdjustMapSpace(CDC* pDC);
	afx_msg void OnEnChange();
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	virtual void OnInitialUpdate();
	BOOL CreateFont(CCharStyle & sty,CFont *pFont);
	afx_msg void OnUpdateTaskpaneGridSplit(CCmdUI *pCmdUI);
	//bool m_bSplitGrid;
	// 绘制字格切分线,将字格分成十等分
	void DrawGridSplitLine(CDC * pDC, CRect & rc);
	afx_msg void OnTaskpaneGridSplit();
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	// 对于没有进行注册授权使用的用户，在字贴上画一水印。
	void DrawWatermark(CDC * pDC, int w, int h);
	// 将水印位图进行镜像处理
	void MirrorBmp(CBitmap * pBmp);
};

#ifndef _DEBUG  // 练字工具2View.cpp 中的调试版本
inline CMyDoc* CMyView::GetDocument() const
   { return reinterpret_cast<CMyDoc*>(m_pDocument); }
#endif

