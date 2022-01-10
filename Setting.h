#pragma once


///////////////////////////
//各种参数设置，为主计算方便，特别是画格子线，
//单位统一以采用0。01毫米(1/100mm)为单位
////////////////////////////
//定义格子种类
typedef enum GRIDCATEGORY
{
	//无边框及内部线，即只输入文字，而不打格
	/*const static int*/ NONE=0,
	//只有横线，
	ROWLINE=1,
	//只有列线
	COLLINE=2,
	//空格线，即只有外框而无内部线条
	BORDERLINE=3,
	//"田"字格
	/*const static int*/ TIAN=4,
	//“米”字格
	/*const static int*/ MI=5,
	//九宫格
	/*const static int*/ JIU=6,
	//“回”字格
	/*const static int*/ HUI=7,
	//"田回"格
	/*const static int*/ TIAN_HUI=8,
	//	"米回"格
	/*const static int*/ MI_HUI=9


} GridCategory;

//格线样式
class CGridStyle
{
public:
	CGridStyle(void);
	~CGridStyle(void);
	//保存参数设置到注册表或配置文件
	void Save();
	//加载配置参数
	void Load();
public:
	//格子种类
	GRIDCATEGORY m_category;
	 //格子内线型样式，外框线均为实线即PS_SOLID,
	//以CPen中的线型为准,默认PS_DOT
	 int m_lineType;
	//格子外框线粗细
	int m_borderWidth;
	//格子内部线粗细
	int m_lineWidth;
	//格子边长
	int m_cellLength;
	//格子行间距
	int m_rowSpace;
	//格子列间距
	int m_colSpace;
	//线颜色
	COLORREF m_color;
	//若为回字格，则回字格所占外围格子的比例,准确说是回字格高度与外格的比例,以百分比表示,实际应用时应除以100
	int m_HUI_Rate;
	//回字格的宽与高的比例,以百分比表示,实际应用时应除以100
	int m_HUI_Rate_W_H;
	//回字格上下偏移的距离，这主要是一些特殊字体格式
	int m_offsetY;
	//编移方向,默认向下
	BOOL m_bDownward;
	//自绘格子
	BOOL m_bOwnerDraw;
	//自绘格子的保存位置，以位图形式保存，并且白色为透明色
	CString m_strDrawFile;
	//背景色，即透明色,将不会显示打印在字贴上
	COLORREF m_clrBackgroud;

};
//字符样式
class CCharStyle
{
public:
	CCharStyle(void);
	~CCharStyle(void);	
	//保存参数设置到注册表或配置文件
	void Save();
	//加载配置参数
	void Load();

	//字大小，即字高度
	int m_charHeight;
	//字体
	CString m_fontName;
	//字符集
	BYTE m_charset;
	//字符重量,加粗FW_BOLD，普通FW_NORMAL,细FW_THIN
	int m_weight;

	//字颜色
	COLORREF m_color;
	//文字是否为横排
	BOOL m_bHorz;
	//文字是左到右，还是右到左
	BOOL m_bLToR;
	//是否为空心字，默认为空心字
	BOOL m_bHollow;
	//或为空心字，是否为实线,默认为实线
	BOOL m_bSolid;
	//字符相对于字格的上下编移距离
	int m_offsetY;
	//编移方向,默认向下
	BOOL m_bDownward;


};

//页面版式及布局
class CPageLayout
{
public:
	//打印时的页面边距,默认2000（即20毫米）
	int m_top,m_bottom,m_left,m_right;
	//是否水平居中
	BOOL m_bCenter;
	//垂直居中
	BOOL m_bVCenter;
	//纸张方向,默认FALSE,即为纵向
	BOOL m_bLandscape;

	
public :
	CPageLayout()
		:m_top(2000),m_bottom(2000),m_left(2000),m_right(2000)
		,m_bCenter(TRUE),m_bVCenter(TRUE),m_bLandscape(FALSE)
	{  }
	//保存参数设置到注册表或配置文件
	void Save();
	//加载配置参数
	void Load();

};

