// HardwareInfor.cpp : 实现文件
//

#include "stdafx.h"
#include "练字工具.h"
#include "HardwareInfor.h"


// CHardwareInfor 对话框

IMPLEMENT_DYNAMIC(CHardwareInfor, CDialog)

CHardwareInfor::CHardwareInfor(CWnd* pParent /*=NULL*/)
	: CDialog(CHardwareInfor::IDD, pParent)
	, m_strComputerID(_T(""))
{

}

CHardwareInfor::~CHardwareInfor()
{
}

void CHardwareInfor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strComputerID);
	DDX_Control(pDX, IDC_EDIT1, m_ctlComputerID);
}


BEGIN_MESSAGE_MAP(CHardwareInfor, CDialog)
	ON_BN_CLICKED(IDC_COPY, &CHardwareInfor::OnBnClickedCopy)
	ON_BN_CLICKED(IDC_SAVE, &CHardwareInfor::OnBnClickedSave)
END_MESSAGE_MAP()


// CHardwareInfor 消息处理程序

void CHardwareInfor::OnBnClickedCopy()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctlComputerID.SetSel(0,-1);
	m_ctlComputerID.Copy();
	m_ctlComputerID.SetSel(0,0);

}

void CHardwareInfor::OnBnClickedSave()
{
	CString	strFilter = L"Text File|*.txt|All File|*.*||";
	CFileDialog dlg(FALSE,L"txt",0,OFN_OVERWRITEPROMPT,strFilter);
	if(IDOK==dlg.DoModal())
	{
		CString path (dlg.GetPathName());
		CFile fl(path,CFile::modeCreate|CFile::modeWrite);
		//作为ASCII码文本写入文件
		this->UpdateData();
		CStringA buf(m_strComputerID);
		fl.Write(buf.GetBuffer(buf.GetLength()),buf.GetLength());
		buf.ReleaseBuffer();
	}}
