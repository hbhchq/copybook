#pragma once


// CCharDirectButton
//ֽ�ŷ����л���ťҲ�ô��������ʾ
///��Ҫ��Ϊ�˸��ݴ�ͼ�����Сͼ��

class CCharDirectButton : public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CCharDirectButton)

protected:
	//��ͼ�����Χ�Ŀհ�����,����ͼ��ʱֻ����ʵ�ʴ�С���֣���Χ�Ŀհ׳���
	CSize m_szLargeImgMargin;
	//ѡ�л��Ƿ�ӻ�һ�����ݵ����,Ĭ�ϻ�һ���
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

	//����ͼ����Ҫ�Ǹ��ݴ�ͼ�����Ż���Сͼ��////////
	virtual void DrawImage(CDC* pDC, RibbonImageType type, CRect rectImage)
	{
		if(type==RibbonImageType::RibbonImageLarge)
		{
			CMFCRibbonButton::DrawImage(pDC,type,rectImage);
		}	
		//�����Сͼ�꣬����ͼ����С��ʾ
		if(/*this->IsQATMode()*/type==RibbonImageType::RibbonImageSmall)
		{

			CImage image;
			image.LoadFromResource(AfxGetInstanceHandle(),IDB_PAGE_LAYOUT);
			int idx=this->m_nSmallImageIndex;			
			CSize szImg(image.GetWidth()/7,image.GetHeight());
			CRect rSrc,rDes(rectImage);
			rSrc.SetRect(idx*szImg.cx,0,(idx+1)*szImg.cx,szImg.cy);	
			//��Դͼ����ʵ�ʳߴ�΢��
			rSrc.DeflateRect(m_szLargeImgMargin.cx,m_szLargeImgMargin.cy);
			//�������Ŀ��λ��
			if((float)rSrc.Height()/rSrc.Width()>(float)rDes.Height()/rDes.Width())//Ŀ��λ��ˮƽ��������
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

