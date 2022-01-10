#include "StdAfx.h"
#include "Setting.h"
#include "练字工具.h"


CGridStyle::CGridStyle(void)
:m_category(TIAN), m_lineType(PS_DOT),
m_borderWidth(10),m_lineWidth(1),
m_cellLength(1300),
m_rowSpace(0),m_colSpace(0),
m_color(RGB(255,0,0)),
m_HUI_Rate(70),m_HUI_Rate_W_H(100),
m_offsetY(0),m_bDownward(TRUE),
m_bOwnerDraw(0),m_strDrawFile(),
m_clrBackgroud(RGB(255,255,255))
{

}

CGridStyle::~CGridStyle(void)
{
}



CCharStyle::CCharStyle(void)
:m_charHeight(800), m_fontName(L"")/*楷体*/
,m_color(RGB(0,0,0))/*黑字以免打印不清晰*/
, m_bHorz(TRUE),m_bLToR(TRUE)
,m_bHollow(1),m_bSolid(TRUE)
,m_weight(FW_NORMAL),
m_offsetY(0),m_bDownward(TRUE)
{
}

CCharStyle::~CCharStyle(void)
{
}


//保存参数设置到注册表或配置文件
void CGridStyle::Save()
{
	CString oldBaseReg=theApp.GetRegistryBase();
	theApp.SetRegistryBase(_T("Settings\\GridStyle"));

	theApp.WriteInt(_T("category"),m_category);
	theApp.WriteInt(_T("lineType"),m_lineType);
	theApp.WriteInt(_T("borderWidth"),m_borderWidth);
	theApp.WriteInt(_T("lineWidth"),m_lineWidth);
	theApp.WriteInt(_T("cellLength"),m_cellLength);
	theApp.WriteInt(_T("rowSpace"),m_rowSpace);
	theApp.WriteInt(_T("colSpace"),m_colSpace);
	theApp.WriteInt(_T("color"),m_color);
	theApp.WriteInt(_T("HUI_Rate"),m_HUI_Rate);
	theApp.WriteInt(_T("HUI_Rate_W_H"),m_HUI_Rate_W_H);
	theApp.WriteInt(_T("offsetY"),m_offsetY);
	theApp.WriteInt(_T("bDownward"),m_bDownward);
	theApp.WriteInt(_T("bOwnerDraw"),m_bOwnerDraw);
	theApp.WriteInt(_T("clrBackgroud"),m_clrBackgroud);
	theApp.WriteString(_T("strDrawFile"),m_strDrawFile);

	//恢复老
	theApp.SetRegistryBase(oldBaseReg);

	
}
//加载配置参数
void CGridStyle::Load()
{
	CString oldBaseReg=theApp.GetRegistryBase();
	theApp.SetRegistryBase(_T("Settings\\GridStyle"));

	m_category=(GRIDCATEGORY)theApp.GetInt(_T("category"),m_category);
	m_lineType=theApp.GetInt(_T("lineType"),m_lineType);
	m_borderWidth=theApp.GetInt(_T("borderWidth"),m_borderWidth);
	m_lineWidth=theApp.GetInt(_T("lineWidth"),m_lineWidth);
	m_cellLength=theApp.GetInt(_T("cellLength"),m_cellLength);
	m_rowSpace=theApp.GetInt(_T("rowSpace"),m_rowSpace);
	m_colSpace=theApp.GetInt(_T("colSpace"),m_colSpace);
	m_color=theApp.GetInt(_T("color"),m_color);
	m_HUI_Rate=theApp.GetInt(_T("HUI_Rate"),m_HUI_Rate);
	m_HUI_Rate_W_H=theApp.GetInt(_T("HUI_Rate_W_H"),m_HUI_Rate_W_H);
	m_offsetY=theApp.GetInt(_T("offsetY"),m_offsetY);
	m_bDownward=theApp.GetInt(_T("bDownward"),m_bDownward);
	m_bOwnerDraw=theApp.GetInt(_T("bOwnerDraw"),m_bOwnerDraw);
	m_clrBackgroud=theApp.GetInt(_T("clrBackgroud"),m_clrBackgroud);
	m_strDrawFile=theApp.GetString(_T("strDrawFile"),m_strDrawFile);

	//恢复老
	theApp.SetRegistryBase(oldBaseReg);

}

//保存参数设置到注册表或配置文件
void CCharStyle::Save()
{
	CString oldBaseReg=theApp.GetRegistryBase();
	theApp.SetRegistryBase(_T("Settings\\CharStyle"));

	theApp.WriteInt(_T("charHeight"),m_charHeight);
	theApp.WriteString(_T("fontName"),m_fontName);
	theApp.WriteInt(_T("charset"),m_charset);
	theApp.WriteInt(_T("weight"),m_weight);
	theApp.WriteInt(_T("color"),m_color);
	theApp.WriteInt(_T("bHorz"),m_bHorz);
	theApp.WriteInt(_T("bLToR"),m_bLToR);
	theApp.WriteInt(_T("bHollow"),m_bHollow);
	theApp.WriteInt(_T("bSolid"),m_bSolid);
	theApp.WriteInt(_T("offsetY"),m_offsetY);
	theApp.WriteInt(_T("bDownward"),m_bDownward);

	//恢复老
	theApp.SetRegistryBase(oldBaseReg);
}
//加载配置参数
void CCharStyle::Load()
{
	CString oldBaseReg=theApp.GetRegistryBase();
	theApp.SetRegistryBase(_T("Settings\\CharStyle"));

	m_charHeight=theApp.GetInt(_T("charHeight"),m_charHeight);
	m_fontName=theApp.GetString(_T("fontName"),m_fontName);
	m_charset=theApp.GetInt(_T("charset"),m_charset);
	m_weight=theApp.GetInt(_T("weight"),m_weight);
	m_color=theApp.GetInt(_T("color"),m_color);
	m_bHorz=theApp.GetInt(_T("bHorz"),m_bHorz);
	m_bLToR=theApp.GetInt(_T("bLToR"),m_bLToR);
	m_bHollow=theApp.GetInt(_T("bHollow"),m_bHollow);
	m_bSolid=theApp.GetInt(_T("bSolid"),m_bSolid);
	m_offsetY=theApp.GetInt(_T("offsetY"),m_offsetY);
	m_bDownward=theApp.GetInt(_T("bDownward"),m_bDownward);


	//恢复老
	theApp.SetRegistryBase(oldBaseReg);

}

//保存参数设置到注册表或配置文件
void CPageLayout::Save()
{	
	CString oldBaseReg=theApp.GetRegistryBase();
	theApp.SetRegistryBase(_T("Settings\\PageLayout"));

	theApp.WriteInt(_T("top"),m_top);
	theApp.WriteInt(_T("bottom"),m_bottom);
	theApp.WriteInt(_T("left"),m_left);
	theApp.WriteInt(_T("right"),m_right);
	theApp.WriteInt(_T("bCenter"),m_bCenter);
	theApp.WriteInt(_T("bVCenter"),m_bVCenter);
	theApp.WriteInt(_T("bLandscape"),m_bLandscape);

	//恢复老
	theApp.SetRegistryBase(oldBaseReg);
}
//加载配置参数
void CPageLayout::Load()
{
	CString oldBaseReg=theApp.GetRegistryBase();
	theApp.SetRegistryBase(_T("Settings\\PageLayout"));

	m_top=theApp.GetInt(_T("top"),m_top);
	m_bottom=theApp.GetInt(_T("bottom"),m_bottom);
	m_left=theApp.GetInt(_T("left"),m_left);
	m_right=theApp.GetInt(_T("right"),m_right);
	m_bCenter=theApp.GetInt(_T("bCenter"),m_bCenter);
	m_bVCenter=theApp.GetInt(_T("bVCenter"),m_bVCenter);
	m_bLandscape=theApp.GetInt(_T("bLandscape"),m_bLandscape);

	//恢复老
	theApp.SetRegistryBase(oldBaseReg);

}