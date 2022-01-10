#pragma once
#include "stdafx.h"
#include <fstream>

#include <wincrypt.h>
#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")
//using namespace std;
//进行注册授权管理，主要是读取硬件信息，和程序运行时的授权校验
class CLicense
{
private :
	CStringA m_strLicenseFile;//授权文件路径
	//软件的标志，各程序中的标志不一样，以免各程序授权文件可以通用
	CStringA m_strFlag;
	//明文，从授权文件解密得到
	CStringA m_strClearTxt;
	//字符串，读出的硬件信息
	CStringA m_strCPU;//处理器ID,一批或同一型号的可能一样
	CStringA m_strDisk;//磁盘系列号,有的可能没有
	//其他磁盘信息
	CStringA m_strDiskCap;

public:

	//默认构造函数，主要是用于读取机器硬件信息，以用于注册
	CLicense(){}
	//带参数的构造函数，主要是用于校验程序的授权文件信息
	CLicense(CStringA path,CStringA flag)
		:m_strLicenseFile(path),m_strFlag(flag),m_strClearTxt()
		,m_strCPU(),m_strDisk(),m_strDiskCap()
	{		
	}

	~CLicense(void)
	{
	}
private :
	//解密授权文件内容
	void Decode()
	{ 
	
	}

	//读取机器的硬件信息，主要是处理器标识和硬盘系列号,将与程序标志一起串成一个字符串
	HRESULT ReadHardwareInf()
	{
		//将几个成员变量清空
		m_strCPU.Empty();
		m_strDisk.Empty();
		m_strDiskCap.Empty();
		////////////////////////
		HRESULT hres;
		// Step 1: --------------------------------------------------
		// Initialize COM. 已经在MyApp中初始化过------------------------------------------
		//hres =  CoInitializeEx(0, COINIT_APARTMENTTHREADED/*COINIT_MULTITHREADED*/); 
		//if (FAILED(hres))
		//{  
		//	////WriteLog( L"COM组件服务初始化失败!");   
		//	//MessageBox(hDlg,L"COM组件服务初始化失败!",L"错误",MB_OK|MB_ICONERROR);
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
		//	////WriteLog( L"COM组件服务安全初始化失败!");  
		//	//MessageBox(hDlg,L"COM组件服务安全初始化失败!",L"错误",MB_OK|MB_ICONERROR);
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
			////WriteLog( L"COM组件对象IWbemLocator创建失败!");
			//MessageBox(hDlg,L"COM组件对象IWbemLocator创建失败!",L"错误",MB_OK|MB_ICONERROR);
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
			////WriteLog( L"不能连接WMI服务!请检查WMI服务是否正常运行。");
			//////MessageBox(hDlg,L"不能连接WMI服务!请检查WMI服务是否正常运行。",L"错误",MB_OK|MB_ICONERROR);
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
			//////WriteLog( L"出现错误，请检查WMI服务是否正常运行。");
			////////MessageBox(hDlg,L"出现错误，请检查WMI服务是否正常运行。",L"错误",MB_OK|MB_ICONERROR);
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
			//////WriteLog( L"出现错误，请检查WMI服务是否正常运行。");
			//////MessageBox(hDlg,L"出现错误，请检查WMI服务是否正常运行。",L"错误",MB_OK|MB_ICONERROR);
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
		//读取硬盘信息
		pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"), 
			bstr_t("SELECT * FROM win32_DiskDrive"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			////WriteLog( L"出现错误，请检查WMI服务是否正常运行。");
			//////MessageBox(hDlg,L"出现错误，请检查WMI服务是否正常运行。",L"错误",MB_OK|MB_ICONERROR);
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

		//是winxp,和win2003系统，windows2000不支持Win32_PhysicalMedia,将得到"2000sn"
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
			////WriteLog( L"出现错误，请检查WMI服务是否正常运行。");
			//////MessageBox(hDlg,L"出现错误，请检查WMI服务是否正常运行。",L"错误",MB_OK|MB_ICONERROR);
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

		//CoUninitialize();//在MyApp中已经处理过
		return S_OK;   
	}
public:

	//检测是否通过授权验证,1为通过，0不通过，-1其他程序错误，也不通过
	//将文件解密后对照ProcessorID,DiskSN,diskcap值是否饱含
	int Check()
	{
		return 1;
	}

	//取得机器标识，cpu+disk+diskcap串起来的一个字符串,中间加连字符串起来，以免出错
	CString GetComputerID()
	{
		if(ReadHardwareInf()!=S_OK)
		{
			CString strTemp;
			BOOL bValid=strTemp.LoadString(IDS_WMI_MSG);
			AfxMessageBox(strTemp,MB_ICONINFORMATION|MB_OK);
			return CString();//不成功，可能是wmi服务未开启
		}
		
		return CString(m_strCPU+"-"+m_strDisk+"-"+m_strDiskCap);
	}
};
