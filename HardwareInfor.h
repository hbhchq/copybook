#pragma once
#include "Resource.h"
#include "afxwin.h"


// CHardwareInfor �Ի���

class CHardwareInfor : public CDialog
{
	DECLARE_DYNAMIC(CHardwareInfor)

public:
	CHardwareInfor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHardwareInfor();

// �Ի�������
	enum { IDD = IDD_HARDWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedSave();
	// �������ʶ
	CString m_strComputerID;
	CEdit m_ctlComputerID;
};
