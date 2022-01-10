// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// ���ֹ���Doc.cpp : CMyDoc ���ʵ��
//

#include "stdafx.h"
#include "���ֹ���.h"

#include "���ֹ���Doc.h"

#include "���ֹ���view.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDoc

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()


// CMyDoc ����/����

CMyDoc::CMyDoc()
: m_bIsUnicodeFile(FALSE)
{
	// TODO: �ڴ����һ���Թ������

}

CMyDoc::~CMyDoc()
{
}

BOOL CMyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


void CMyDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU  )
	{
		CDocument::SetPathName(lpszPathName, bAddToMRU);
		((CMainFrame*) AfxGetMainWnd ())->UpdateMRUFilesList ();
	}

// CMyDoc ���л�

void CMyDoc::Serialize(CArchive& ar)
{
	CMyView * pV=(CMyView * )this->m_viewList.GetHead();
	//pV->SerializeRaw (ar);
	CEdit &edit=pV->GetEditCtrl();
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����		
		CString buf;
		edit.GetWindowText(buf);
		//���ԭ�ļ���unicode���룬ֱ�ӱ���
		if(this->m_bIsUnicodeFile)
		{
			ar.WriteString(buf);
		}
		else//��ԭ���Ķ��ֽ���ʽ�����ļ�����
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
			//��ʾ����ļ�
			CString info,temp;
			temp.LoadString(IDS_FILE_TOOLARGE);
			info.Format(temp,edit.GetLimitText ());
			pV->MessageBox(info,NULL);
			len=sizeof(TCHAR)+edit.GetLimitText ();
		}
		char * buf=new char[len];		
		ar.Read(buf,len-1);
		//����unicodeʱ�����������
		//Ŀǰֻ�ܱ����UNicode�ַ�������
		buf[len-sizeof(TCHAR)]=0;
		buf[len-1]=0;
		//�������unicode�ı����Ƚ���ת��
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


// CMyDoc ���

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


// CMyDoc ����

//BOOL CMyDoc::OnOpenDocument(LPCTSTR lpszPathName)
//{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
//
//	// TODO:  �ڴ������ר�õĴ�������
//
//	return TRUE;
//}
