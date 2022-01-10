#include "StdAfx.h"
#include "练字工具.h"
//#include "MsgBox.h"

#include "NumberRichEditCtrl.h"
#include "NumberEdit.h"
#include "resource.h"
#include <imm.h>
#pragma comment ( lib , "imm32.lib" )
BEGIN_MESSAGE_MAP(CNumberRichEditCtrl, CMFCRibbonRichEditCtrl)
	ON_WM_CHAR()	
	ON_CONTROL_REFLECT(EN_CHANGE, &CNumberRichEditCtrl::OnChange)
//	ON_MESSAGE(WM_PASTE,&CNumberRichEditCtrl::OnPaste)
//	ON_WM_UNICHAR()
ON_WM_KEYDOWN()
ON_CONTROL_REFLECT(EN_SETFOCUS, &CNumberRichEditCtrl::OnEnSetfocus)
ON_WM_CREATE()
ON_WM_SETFOCUS()
END_MESSAGE_MAP()

//过滤字符输入，只接受数字输入
void CNumberRichEditCtrl::OnChar( UINT nChar,  UINT nRepCnt,  UINT nFlags  )
{
	if(nChar>='0'&&nChar<='9')
	{
		CMFCRibbonRichEditCtrl::OnChar(nChar,nRepCnt,nFlags);
	}

}

////如果数据大于设置的最大最小值，则恢复到以前的老值
void CNumberRichEditCtrl::OnChange()
{
	CNumberEdit &edit=(CNumberEdit &)this->m_edit;
	CString newTxt;
	this->GetWindowText(newTxt);
	long n=_tstol(newTxt);	
	//判断打印机设备是否正常
	PRINTDLG pd;
	pd.lStructSize = (DWORD)sizeof(PRINTDLG);
	BOOL bRet = theApp.GetPrinterDeviceDefaults(&pd);
	if(!bRet)
		goto end ;//没有打印机或有问题，不作较验

	if(newTxt.IsEmpty()||n>edit.m_nMaxVal||n<edit.m_nMinVal)
	{
		//恢复到以前的老值,如果老值本身为空，设为旋钮最小值
		if(m_strOldText.IsEmpty())
		{
			CString min;
			min.Format(L"%d",edit.m_nMin);
			this->SetWindowTextW(min);

		}
		else
		{
			this->SetWindowTextW(m_strOldText);
		}
		//给出提示信息
		CString msg;
		BOOL bValid=msg.LoadString(IDS_NUMBER_SCOPE_MSG);
		ASSERT(bValid);
		CString inf;
		inf.Format(msg,edit.m_nMinVal,edit.m_nMaxVal);
		//MessageBox(inf,0,MB_OK|MB_ICONINFORMATION);
		//::SetFocus(this->GetSafeHwnd());
		//this->SetSel(0,-1);
		////////////////
		//设置提示窗口的位置
		CRect rc;
		this->GetWindowRect(&rc);
		CPoint target(rc.left+2,rc.bottom-2),beg(rc.left-rc.Height()*3,rc.bottom+rc.Height()*5);
		m_wndMsg.Set(inf,target,beg);
		m_wndMsg.ShowMessage();
	}
end:	CMFCRibbonRichEditCtrl::OnChange();
}

//过滤粘贴功能
LRESULT CNumberRichEditCtrl::OnPaste(WPARAM w, LPARAM l)
{
	if (!IsClipboardFormatAvailable(CF_TEXT)) 
		return -1; 
	if (!::OpenClipboard(this->GetSafeHwnd())) 
		return -1; 
	HGLOBAL hglb = GetClipboardData(CF_TEXT); 
	if (hglb != NULL) 
	{ 
		LPSTR  lptstr = (LPSTR)GlobalLock(hglb); 
		if(lptstr!=NULL)
		{
			if(IsNumber(lptstr))
			{
				//SetWindowText(CString(lptstr));
				this->Paste();
			}

			GlobalUnlock(hglb); 

		}


	}
	::CloseClipboard();
	return 0;
	//return this->DefWindowProc(WM_PASTE,w,l);
}
BOOL CNumberRichEditCtrl::IsNumber(LPSTR str)
{
	for(;(*str);str++)
	{
		if(*str<'0'||*str>'9')
			return FALSE;
	}
	return TRUE;
}



void CNumberRichEditCtrl::OnEnSetfocus()
{
	//移走所有的输入法，只能输入英文和数据
	HIMC  hIMC = ImmAssociateContext(this->GetSafeHwnd(), NULL);

}

int CNumberRichEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCRibbonRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	//// 创建成功后，设置提示窗口的位置
	//CRect rc;
	//this->GetWindowRect(&rc);
	//CPoint target(rc.left+2,rc.bottom-2),beg(rc.left-rc.Height(),rc.bottom+rc.Height());

	//m_wndMsg.Set(target,beg);

	return 0;
}

void CNumberRichEditCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CMFCRibbonRichEditCtrl::OnSetFocus(pOldWnd);
	this->SetSel(0,-1);
	// TODO: 在此处添加消息处理程序代码
}
