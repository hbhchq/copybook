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

// 练字工具.h : 练字工具 应用程序的主头文件
//
#pragma once
#include "HardwareInfor.h"

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMyApp:
// 有关此类的实现，请参阅 练字工具.cpp
//

class CMyApp : public CWinAppEx
{	
	DECLARE_MESSAGE_MAP()

public:
	CMyApp();
//程序标志性字段,常量,授权文件标志名称
	static const CString s_strLicenceFlag;

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	//是否授权，程序运行中实时进行检测，此处只是显示时指示
	bool m_bLicense;
	//授权的文件路径，程序运行中实时检测注册情况时用到这个参数，平时保存到注册表中
	CString  m_strLicenceFile;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	
	// 授权许可证较验
	bool CheckLicence(void);
};

extern CMyApp theApp;
