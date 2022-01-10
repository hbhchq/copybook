#pragma once
#include "SampleWnd.h"


class CTaskPane : public CMFCTasksPane
{
	friend class CMyView;
	friend class CMainFrame;
// Construction
public:
	CTaskPane();
	
 ////Attributes
	////int	m_nUserColorGroup;
	////int	m_nUserColorTask;

protected:
	int	m_nDocumentsGroup;
	int m_nSampleGroup;

	//CFont		m_Font;
	//CTreeCtrl	m_wndTree;
 	CSampleWnd m_wndSample;//ÑùÀý´°¿Ú

// Operations
public:
	//void UpdateMRUFilesList ();
	//void UpdateToolbar ();
	CSampleWnd * GetSampleWnd() {return &m_wndSample;}
	// Overrides
	void UpdateMRUFilesList ();
public:

protected:
	//BOOL CreateTreeControl();
	BOOL CreateSampleWnd();

// Implementation
public:
	virtual ~CTaskPane();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnClickTask(int nGroupNumber, int nTaskNumber, UINT uiCommandID, DWORD dwUserData);


protected:
	bool m_bSplitGrid;
};
