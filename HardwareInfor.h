#pragma once
#include "Resource.h"
#include "afxwin.h"


// CHardwareInfor 对话框

class CHardwareInfor : public CDialog
{
	DECLARE_DYNAMIC(CHardwareInfor)

public:
	CHardwareInfor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHardwareInfor();

// 对话框数据
	enum { IDD = IDD_HARDWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedSave();
	// 计算机标识
	CString m_strComputerID;
	CEdit m_ctlComputerID;
};
