#pragma once
#include "stdafx.h"
#include <fstream>

#include <wincrypt.h>
#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")
//using namespace std;
//����ע����Ȩ������Ҫ�Ƕ�ȡӲ����Ϣ���ͳ�������ʱ����ȨУ��
class CLicense
{
private :
	CStringA m_strLicenseFile;//��Ȩ�ļ�·��
	//����ı�־���������еı�־��һ���������������Ȩ�ļ�����ͨ��
	CStringA m_strFlag;
	//���ģ�����Ȩ�ļ����ܵõ�
	CStringA m_strClearTxt;
	//�ַ�����������Ӳ����Ϣ
	CStringA m_strCPU;//������ID,һ����ͬһ�ͺŵĿ���һ��
	CStringA m_strDisk;//����ϵ�к�,�еĿ���û��
	//����������Ϣ
	CStringA m_strDiskCap;

public:

	//Ĭ�Ϲ��캯������Ҫ�����ڶ�ȡ����Ӳ����Ϣ��������ע��
	CLicense(){}
	//�������Ĺ��캯������Ҫ������У��������Ȩ�ļ���Ϣ
	CLicense(CStringA path,CStringA flag)
		:m_strLicenseFile(path),m_strFlag(flag),m_strClearTxt()
		,m_strCPU(),m_strDisk(),m_strDiskCap()
	{		
	}

	~CLicense(void)
	{
	}
private :
	//������Ȩ�ļ�����
	void Decode()
	{ 
	
	}

	//��ȡ������Ӳ����Ϣ����Ҫ�Ǵ�������ʶ��Ӳ��ϵ�к�,��������־һ�𴮳�һ���ַ���
	HRESULT ReadHardwareInf()
	{
		//��������Ա�������
		m_strCPU.Empty();
		m_strDisk.Empty();
		m_strDiskCap.Empty();
		////////////////////////
		HRESULT hres;
		// Step 1: --------------------------------------------------
		// Initialize COM. �Ѿ���MyApp�г�ʼ����------------------------------------------
		//hres =  CoInitializeEx(0, COINIT_APARTMENTTHREADED/*COINIT_MULTITHREADED*/); 
		//if (FAILED(hres))
		//{  
		//	////WriteLog( L"COM��������ʼ��ʧ��!");   
		//	//MessageBox(hDlg,L"COM��������ʼ��ʧ��!",L"����",MB_OK|MB_ICONERROR);
		//	return hres;                  // Program has failed.
		//}

		// Step 2: --------------------------------------------------
		// Set general COM security levels --------------------------
		// Note: If you are using Windows 2000, you need to specify -
		// the default authentication credentials for a user by using
		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		// parameter of CoInitializeSecurity ------------------------

		//hres =  CoInitializeSecurity(
		//	NULL, 
		//	-1,                          // COM authentication
		//	NULL,                        // Authentication services
		//	NULL,                        // Reserved
		//	RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		//	RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		//	NULL,                        // Authentication info
		//	EOAC_NONE,                   // Additional capabilities 
		//	NULL                         // Reserved
		//	);


		//if (FAILED(hres))
		//{
		//	////WriteLog( L"COM�������ȫ��ʼ��ʧ��!");  
		//	//MessageBox(hDlg,L"COM�������ȫ��ʼ��ʧ��!",L"����",MB_OK|MB_ICONERROR);
		//	CoUninitialize();
		//	return hres;                  // Program has failed.
		//}

		// Step 3: ---------------------------------------------------
		// Obtain the initial locator to WMI -------------------------

		IWbemLocator *pLoc = NULL;

		hres = CoCreateInstance(
			CLSID_WbemLocator,             
			0, 
			CLSCTX_INPROC_SERVER, 
			IID_IWbemLocator, (LPVOID *) &pLoc);

		if (FAILED(hres))
		{
			////WriteLog( L"COM�������IWbemLocator����ʧ��!");
			//MessageBox(hDlg,L"COM�������IWbemLocator����ʧ��!",L"����",MB_OK|MB_ICONERROR);
			CoUninitialize();
			return hres;                  // Program has failed.
		}

		// Step 4: -----------------------------------------------------
		// Connect to WMI through the IWbemLocator::ConnectServer method

		IWbemServices *pSvc = NULL;

		// Connect to the root\cimv2 namespace with
		// the current user and obtain pointer pSvc
		// to make IWbemServices calls.
		hres = pLoc->ConnectServer(
			_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (e.g. Kerberos)
			0,                       // Context object 
			&pSvc                    // pointer to IWbemServices proxy
			);

		if (FAILED(hres))
		{
			////WriteLog( L"��������WMI����!����WMI�����Ƿ��������С�");
			//////MessageBox(hDlg,L"��������WMI����!����WMI�����Ƿ��������С�",L"����",MB_OK|MB_ICONERROR);
			pLoc->Release();     
			CoUninitialize();
			return hres;                  // Program has failed.
		}



		// Step 5: --------------------------------------------------
		// Set security levels on the proxy -------------------------

		hres = CoSetProxyBlanket(
			pSvc,                        // Indicates the proxy to set
			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
			NULL,                        // Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
			NULL,                        // client identity
			EOAC_NONE                    // proxy capabilities 
			);

		if (FAILED(hres))
		{
			//////WriteLog( L"���ִ�������WMI�����Ƿ��������С�");
			////////MessageBox(hDlg,L"���ִ�������WMI�����Ƿ��������С�",L"����",MB_OK|MB_ICONERROR);
			pSvc->Release();
			pLoc->Release();     
			CoUninitialize();
			return hres;                  // Program has failed.
		}

		// Step 6: --------------------------------------------------
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"), 
			bstr_t("SELECT * FROM win32_processor"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			//////WriteLog( L"���ִ�������WMI�����Ƿ��������С�");
			//////MessageBox(hDlg,L"���ִ�������WMI�����Ƿ��������С�",L"����",MB_OK|MB_ICONERROR);
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return hres;                  // Program has failed.
		}

		// Step 7: -------------------------------------------------
		// Get the data from the query in step 6 -------------------

		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		if (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);
			if(SUCCEEDED(hr))
			{
				VARIANT vtProp;				
				hr = pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);        
				this->m_strCPU=(vtProp.vt ==VT_BSTR)
					?CStringA(vtProp.bstrVal):"01234567890";
				VariantClear(&vtProp);
				pclsObj->Release();

			}
		}
		//��ȡӲ����Ϣ
		pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"), 
			bstr_t("SELECT * FROM win32_DiskDrive"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			////WriteLog( L"���ִ�������WMI�����Ƿ��������С�");
			//////MessageBox(hDlg,L"���ִ�������WMI�����Ƿ��������С�",L"����",MB_OK|MB_ICONERROR);
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return hres;                  // Program has failed.
		}

		// Step 7: -------------------------------------------------
		// Get the data from the query in step 6 -------------------

		pclsObj=NULL;
		uReturn = 0;

		if (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);
			if(SUCCEEDED(hr))
			{
				VARIANT vtProp;
				// Get the value of the Name property
				hr = pclsObj->Get(L"Model", 0, &vtProp, 0, 0); 
				m_strDiskCap.Append(CStringA(vtProp.bstrVal));
				hr = pclsObj->Get(L"Size", 0, &vtProp, 0, 0);        
				m_strDiskCap+=  CStringA(vtProp) ; 
				hr = pclsObj->Get(L"SectorsPerTrack", 0, &vtProp, 0, 0);        
				m_strDiskCap+=   CStringA(vtProp) ;
				hr = pclsObj->Get(L"TotalCylinders", 0, &vtProp, 0, 0);        
				m_strDiskCap+=   CStringA(vtProp) ;            
				hr = pclsObj->Get(L"TotalHeads", 0, &vtProp, 0, 0);        
				m_strDiskCap+=   CStringA(vtProp) ;           
				hr = pclsObj->Get(L"TotalSectors", 0, &vtProp, 0, 0);        
				m_strDiskCap+=   CStringA(vtProp) ;    
				hr = pclsObj->Get(L"TotalTracks", 0, &vtProp, 0, 0);        
				m_strDiskCap+=   CStringA(vtProp) ;         
				hr = pclsObj->Get(L"TracksPerCylinder", 0, &vtProp, 0, 0);        
				m_strDiskCap+=   CStringA(vtProp) ;         
				

				VariantClear(&vtProp);
				pclsObj->Release();

			}
		}	

		//��winxp,��win2003ϵͳ��windows2000��֧��Win32_PhysicalMedia,���õ�"2000sn"
		/////////////////////////////////////////////////////////////////
		pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"), 
			bstr_t("SELECT * FROM Win32_PhysicalMedia"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			////WriteLog( L"���ִ�������WMI�����Ƿ��������С�");
			//////MessageBox(hDlg,L"���ִ�������WMI�����Ƿ��������С�",L"����",MB_OK|MB_ICONERROR);
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return hres;                  // Program has failed.
		}

		// Step 7: -------------------------------------------------
		// Get the data from the query in step 6 -------------------

		pclsObj=NULL;
		uReturn = 0;

		if (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);
			if(SUCCEEDED(hr))
			{
				VARIANT vtProp;
				hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0); 
				this->m_strDisk=(vtProp.vt ==VT_BSTR)
					?CStringA( vtProp.bstrVal):"01234567890" ;
				VariantClear(&vtProp);
				pclsObj->Release();

			}
			else
			{
				this->m_strDisk=CStringA("2000sn");
			}
		}	
		// Cleanup
		// ========
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();

		//CoUninitialize();//��MyApp���Ѿ������
		return S_OK;   
	}
public:

	//����Ƿ�ͨ����Ȩ��֤,1Ϊͨ����0��ͨ����-1�����������Ҳ��ͨ��
	//���ļ����ܺ����ProcessorID,DiskSN,diskcapֵ�Ƿ񱥺�
	int Check()
	{
		return 1;
	}

	//ȡ�û�����ʶ��cpu+disk+diskcap��������һ���ַ���,�м�����ַ����������������
	CString GetComputerID()
	{
		if(ReadHardwareInf()!=S_OK)
		{
			CString strTemp;
			BOOL bValid=strTemp.LoadString(IDS_WMI_MSG);
			AfxMessageBox(strTemp,MB_ICONINFORMATION|MB_OK);
			return CString();//���ɹ���������wmi����δ����
		}
		
		return CString(m_strCPU+"-"+m_strDisk+"-"+m_strDiskCap);
	}
};
