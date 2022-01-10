#pragma once


// CCharDirectButton
//纸张方向切换按钮也用此类进行显示
///主要是为了根据大图标绘制小图标

class CCharDirectButton : public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CCharDirectButton)

protected:
	//大图标的周围的空白区域,绘制图标时只用其实际大小部分，周围的空白除掉
	CSize m_szLargeImgMargin;
	//选中基是否加画一个下陷的外框,默认画一外框
	BOOL m_bOwnerFrame;
public:
	CCharDirectButton();
	virtual ~CCharDirectButton();
	CCharDirectButton(UINT nID,LPCTSTR lpszText, int nSmallImageIndex = -1, int nLargeImageIndex = -1, BOOL bAlwaysShowDescription = FALSE)
		:CMFCRibbonButton(nID, lpszText, nSmallImageIndex,  nLargeImageIndex , bAlwaysShowDescription )
	,m_szLargeImgMargin(0,0),m_bOwnerFrame(1)
	{
		
	}
	void SetLargeImgMargin(int hMargin,int vMargin)
	{
		this->m_szLargeImgMargin.SetSize(hMargin,vMargin);
	}
	void EnableOwnerFrame(BOOL bOwnerFrame){m_bOwnerFrame=bOwnerFrame;}
	virtual void CopyFrom (const CMFCRibbonBaseElement&src)
	{
		CMFCRibbonButton::CopyFrom(src);
		CCharDirectButton & s=(CCharDirectButton&) src;
		this->m_szLargeImgMargin=s.m_szLargeImgMargin;
		this->m_bOwnerFrame=s.m_bOwnerFrame;

	}

	//绘制图像，主要是根据大图标缩放绘制小图标////////
	virtual void DrawImage(CDC* pDC, RibbonImageType type, CRect rectImage)
	{
		if(type==RibbonImageType::RibbonImageLarge)
		{
			CMFCRibbonButton::DrawImage(pDC,type,rectImage);
		}	
		//如果是小图标，将大图标缩小显示
		if(/*this->IsQATMode()*/type==RibbonImageType::RibbonImageSmall)
		{

			CImage image;
			image.LoadFromResource(AfxGetInstanceHandle(),IDB_PAGE_LAYOUT);
			int idx=this->m_nSmallImageIndex;			
			CSize szImg(image.GetWidth()/7,image.GetHeight());
			CRect rSrc,rDes(rectImage);
			rSrc.SetRect(idx*szImg.cx,0,(idx+1)*szImg.cx,szImg.cy);	
			//将源图根据实际尺寸微调
			rSrc.DeflateRect(m_szLargeImgMargin.cx,m_szLargeImgMargin.cy);
			//计算调整目标位置
			if((float)rSrc.Height()/rSrc.Width()>(float)rDes.Height()/rDes.Width())//目标位置水平方向收缩
			{
				rDes.DeflateRect((rectImage.Width()-rectImage.Height()*rSrc.Width()/rSrc.Height())/2
					,0);
			}
			else if((float)rSrc.Height()/(float)rSrc.Width()<rDes.Height()/rDes.Width())
			{
				rDes.DeflateRect(0
					,(rectImage.Height()-rectImage.Width()*rSrc.Height()/rSrc.Width())/2);
			}
			if(this->IsDisabled())
			{
				image.AlphaBlend(pDC->GetSafeHdc(),rDes,rSrc,100);  
			}
			else
			{
				image.Draw(pDC->GetSafeHdc(),rDes,rSrc);
			}
		}
		if(this->IsChecked()&&m_bOwnerFrame)
		{
			CRect rc(rectImage);//=this->GetRect();		
			rc.InflateRect(1,1);
			////afxGlobalData.clrBtnHilite;
			//CBrush bru(afxGlobalData.clrActiveBorder/*RGB(255,0,0)*/);
			//pDC->FrameRect(&rc,&bru);
			pDC->Draw3dRect(&rc,afxGlobalData.clrBarDkShadow,afxGlobalData.clrActiveCaption);
			rc.InflateRect(1,1);
			pDC->Draw3dRect(&rc,afxGlobalData.clrBarDkShadow,afxGlobalData.clrActiveCaption);
		}
		
	}
};

