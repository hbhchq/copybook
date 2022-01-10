// HardwareInfor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���ֹ���.h"
#include "HardwareInfor.h"


// CHardwareInfor �Ի���

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


// CHardwareInfor ��Ϣ�������

void CHardwareInfor::OnBnClickedCopy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//��ΪASCII���ı�д���ļ�
		this->UpdateData();
		CStringA buf(m_strComputerID);
		fl.Write(buf.GetBuffer(buf.GetLength()),buf.GetLength());
		buf.ReleaseBuffer();
	}}
