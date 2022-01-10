#pragma once

class CDrawImgPreview :
	public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CDrawImgPreview)
protected:
	CImage m_Image;
	CString m_strImgFile;
	COLORREF m_clrTansparent;
public:
	CDrawImgPreview(void){}
	CDrawImgPreview(UINT nID);
	CDrawImgPreview(UINT nID,CString strFileName);
	virtual ~CDrawImgPreview(void);
	CImage * GetImage(){return &m_Image;}
	void SetImage(CString fileName,COLORREF color=RGB(255,255,255))
	{
		if(!m_Image.IsNull())
		{
			m_Image.Destroy();
		}
		m_strImgFile=fileName;
		m_Image.Load(fileName);
		m_clrTansparent=color;
		this->SyncImgFile();
		this->Redraw();
	}

	void SetBmp(CBitmap * bmp)
	{
		if(!m_Image.IsNull())
		{
			m_Image.Destroy();
		}
		m_strImgFile.Empty();
		HBITMAP hbmp=(HBITMAP)::CopyImage((HBITMAP)bmp->GetSafeHandle(),IMAGE_BITMAP,0,0,0);
		m_Image.Attach((HBITMAP)hbmp);
		this->SyncBmp(bmp);
		this->Redraw();
	}


protected:

	virtual void CopyFrom(const CMFCRibbonBaseElement& src)
	{
		CMFCRibbonButton::CopyFrom(src);
		CDrawImgPreview & s=(CDrawImgPreview & )src;
		this->m_strImgFile=s.m_strImgFile;
		this->m_clrTansparent=s.m_clrTansparent;
		HRESULT res=this->m_Image.Load(m_strImgFile);
		if(!SUCCEEDED(res)&&!s.GetImage()->IsNull())
		{
			CImage * pImg=s.GetImage();
			HBITMAP hbmp=(HBITMAP)::CopyImage((HBITMAP)(* pImg),IMAGE_BITMAP,0,0,0);
			m_Image.Attach(hbmp);
		}
	}
	virtual CSize GetRegularSize(CDC* pDC)
	{
		if(this->IsQATMode())
			return CMFCRibbonButton::GetRegularSize(pDC);
		return CSize(80,80);
	}

	virtual CSize GetCompactSize(CDC* pDC)
	{
		return CMFCRibbonButton::GetCompactSize(pDC);
	}
	////virtual CSize GetIntermediateSize(CDC* pDC)
	////{
	////	return CSize(16,15);
	////}

	virtual void OnDraw(CDC* pDC)
	{
		CRect rcFrm(m_rect);
		////pDC->Draw3dRect(&rcFrm,RGB(250,250,250),RGB(128,128,128));
		rcFrm.InflateRect(1,1);
		pDC->Draw3dRect(&rcFrm,RGB(200,200,200),RGB(128,128,128));

		if((HBITMAP)m_Image==NULL)
		{
			return ;
		}
		//if((m_Image.GetBPP()==4||m_Image.GetBPP()==8)
		//	&&m_clrTansparent<m_Image.GetMaxColorTableEntries()
		//	&&m_clr>-1)
		//{
		//	m_Image.SetTransparentColor(m_clrTansparent);
		//}
		CRect rc(0,0,m_Image.GetWidth(),m_Image.GetHeight());
		m_Image.Draw(pDC->GetSafeHdc(),this->m_rect,rc);

	}	

	//同步图像文件名的问题,即同一ID控件有多个对象实例存在
	//主要是可能有快速访问工具栏时，同步更新
	void SyncImgFile(void)
	{
		CMFCRibbonBar* pBar=this->GetTopLevelRibbonBar();
		if(pBar)
		{
			CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
			pBar->GetElementsByID(m_nID,arrBtn);
			for(int n=0;n<arrBtn.GetCount();n++)
			{
				CDrawImgPreview * p=(CDrawImgPreview *)arrBtn[n];
				if(p!=NULL&&p!=this)
				{
					//同步文件名和透明色
					p->m_strImgFile=this->m_strImgFile;
					p->m_clrTansparent=this->m_clrTansparent;
					//重新加载图像文件
					if(!p->m_Image.IsNull())
						p->m_Image.Destroy();
					p->m_Image.Load(p->m_strImgFile);
					p->Redraw();
				}
			}
		}

	}

	void SyncBmp(CBitmap * pBmp)
	{
		CMFCRibbonBar* pBar=this->GetTopLevelRibbonBar();
		if(pBar)
		{
			CArray<CMFCRibbonBaseElement*,CMFCRibbonBaseElement*>arrBtn;
			pBar->GetElementsByID(m_nID,arrBtn);
			for(int n=0;n<arrBtn.GetCount();n++)
			{
				CDrawImgPreview * p=(CDrawImgPreview *)arrBtn[n];
				if(p!=NULL&&p!=this)
				{
					//重新加载图像文件
					if(!m_Image.IsNull())
					{
						p->m_Image.Destroy();
					}
					p->m_strImgFile.Empty();
					HBITMAP hbmp=(HBITMAP)::CopyImage((HBITMAP)pBmp->GetSafeHandle(),IMAGE_BITMAP,0,0,0);
					p->m_Image.Attach((HBITMAP)hbmp);
					p->Redraw();
				}
			}
		}

	}
};
