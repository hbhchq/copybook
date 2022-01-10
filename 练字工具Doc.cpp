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

// 练字工具Doc.cpp : CMyDoc 类的实现
//

#include "stdafx.h"
#include "练字工具.h"

#include "练字工具Doc.h"

#include "练字工具view.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDoc

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()


// CMyDoc 构造/析构

CMyDoc::CMyDoc()
: m_bIsUnicodeFile(FALSE)
{
	// TODO: 在此添加一次性构造代码

}

CMyDoc::~CMyDoc()
{
}

BOOL CMyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


void CMyDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU  )
	{
		CDocument::SetPathName(lpszPathName, bAddToMRU);
		((CMainFrame*) AfxGetMainWnd ())->UpdateMRUFilesList ();
	}

// CMyDoc 序列化

void CMyDoc::Serialize(CArchive& ar)
{
	CMyView * pV=(CMyView * )this->m_viewList.GetHead();
	//pV->SerializeRaw (ar);
	CEdit &edit=pV->GetEditCtrl();
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码		
		CString buf;
		edit.GetWindowText(buf);
		//如果原文件是unicode编码，直接保存
		if(this->m_bIsUnicodeFile)
		{
			ar.WriteString(buf);
		}
		else//按原来的多字节形式保存文件内容
		{
			int l=buf.GetLength()*2+1;
			char * szBuf=new char[l];
			ZeroMemory(szBuf,l);
			WideCharToMultiByte( CP_ACP, 0, buf,
				-1, szBuf,   
				l,NULL,NULL );
			ar.Write(szBuf,strlen(szBuf));
			delete []szBuf;
		}
		this->SetModifiedFlag(FALSE);
	}
	else
	{
		
		ULONGLONG len=sizeof(TCHAR)+ar.GetFile()->GetLength ();
		if(len>sizeof(TCHAR)+(ULONGLONG) edit.GetLimitText ())
		{
			//提示拆分文件
			CString info,temp;
			temp.LoadString(IDS_FILE_TOOLARGE);
			info.Format(temp,edit.GetLimitText ());
			pV->MessageBox(info,NULL);
			len=sizeof(TCHAR)+edit.GetLimitText ();
		}
		char * buf=new char[len];		
		ar.Read(buf,len-1);
		//处理unicode时编译程序的情况
		//目前只能编译成UNicode字符集程序
		buf[len-sizeof(TCHAR)]=0;
		buf[len-1]=0;
		//如果不是unicode文本，先进行转换
		this->m_bIsUnicodeFile=::IsTextUnicode(buf,len,0);
		if(!m_bIsUnicodeFile)
		{
			//WCHAR * wszBuf=new WCHAR[len*2];
			//ZeroMemory(wszBuf,len*2);
			//MultiByteToWideChar( CP_ACP, 0, buf,
			//	strlen(buf)+1, wszBuf,   
			//	len*2/sizeof(wszBuf[0]) );
			//edit.SetWindowTextW(wszBuf);
			//delete []wszBuf;			
			edit.SetWindowTextW(CStringW(buf));

		}
		else
		{
			edit.SetWindowText((LPCTSTR)buf);
		}
		delete []buf;
	}
}


// CMyDoc 诊断

#ifdef _DEBUG
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyDoc 命令

//BOOL CMyDoc::OnOpenDocument(LPCTSTR lpszPathName)
//{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return TRUE;
//}
