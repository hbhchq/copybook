#pragma once


///////////////////////////
//���ֲ������ã�Ϊ�����㷽�㣬�ر��ǻ������ߣ�
//��λͳһ�Բ���0��01����(1/100mm)Ϊ��λ
////////////////////////////
//�����������
typedef enum GRIDCATEGORY
{
	//�ޱ߿��ڲ��ߣ���ֻ�������֣��������
	/*const static int*/ NONE=0,
	//ֻ�к��ߣ�
	ROWLINE=1,
	//ֻ������
	COLLINE=2,
	//�ո��ߣ���ֻ���������ڲ�����
	BORDERLINE=3,
	//"��"�ָ�
	/*const static int*/ TIAN=4,
	//���ס��ָ�
	/*const static int*/ MI=5,
	//�Ź���
	/*const static int*/ JIU=6,
	//���ء��ָ�
	/*const static int*/ HUI=7,
	//"���"��
	/*const static int*/ TIAN_HUI=8,
	//	"�׻�"��
	/*const static int*/ MI_HUI=9


} GridCategory;

//������ʽ
class CGridStyle
{
public:
	CGridStyle(void);
	~CGridStyle(void);
	//����������õ�ע���������ļ�
	void Save();
	//�������ò���
	void Load();
public:
	//��������
	GRIDCATEGORY m_category;
	 //������������ʽ������߾�Ϊʵ�߼�PS_SOLID,
	//��CPen�е�����Ϊ׼,Ĭ��PS_DOT
	 int m_lineType;
	//��������ߴ�ϸ
	int m_borderWidth;
	//�����ڲ��ߴ�ϸ
	int m_lineWidth;
	//���ӱ߳�
	int m_cellLength;
	//�����м��
	int m_rowSpace;
	//�����м��
	int m_colSpace;
	//����ɫ
	COLORREF m_color;
	//��Ϊ���ָ�����ָ���ռ��Χ���ӵı���,׼ȷ˵�ǻ��ָ�߶������ı���,�԰ٷֱȱ�ʾ,ʵ��Ӧ��ʱӦ����100
	int m_HUI_Rate;
	//���ָ�Ŀ���ߵı���,�԰ٷֱȱ�ʾ,ʵ��Ӧ��ʱӦ����100
	int m_HUI_Rate_W_H;
	//���ָ�����ƫ�Ƶľ��룬����Ҫ��һЩ���������ʽ
	int m_offsetY;
	//���Ʒ���,Ĭ������
	BOOL m_bDownward;
	//�Ի����
	BOOL m_bOwnerDraw;
	//�Ի���ӵı���λ�ã���λͼ��ʽ���棬���Ұ�ɫΪ͸��ɫ
	CString m_strDrawFile;
	//����ɫ����͸��ɫ,��������ʾ��ӡ��������
	COLORREF m_clrBackgroud;

};
//�ַ���ʽ
class CCharStyle
{
public:
	CCharStyle(void);
	~CCharStyle(void);	
	//����������õ�ע���������ļ�
	void Save();
	//�������ò���
	void Load();

	//�ִ�С�����ָ߶�
	int m_charHeight;
	//����
	CString m_fontName;
	//�ַ���
	BYTE m_charset;
	//�ַ�����,�Ӵ�FW_BOLD����ͨFW_NORMAL,ϸFW_THIN
	int m_weight;

	//����ɫ
	COLORREF m_color;
	//�����Ƿ�Ϊ����
	BOOL m_bHorz;
	//���������ң������ҵ���
	BOOL m_bLToR;
	//�Ƿ�Ϊ�����֣�Ĭ��Ϊ������
	BOOL m_bHollow;
	//��Ϊ�����֣��Ƿ�Ϊʵ��,Ĭ��Ϊʵ��
	BOOL m_bSolid;
	//�ַ�������ָ�����±��ƾ���
	int m_offsetY;
	//���Ʒ���,Ĭ������
	BOOL m_bDownward;


};

//ҳ���ʽ������
class CPageLayout
{
public:
	//��ӡʱ��ҳ��߾�,Ĭ��2000����20���ף�
	int m_top,m_bottom,m_left,m_right;
	//�Ƿ�ˮƽ����
	BOOL m_bCenter;
	//��ֱ����
	BOOL m_bVCenter;
	//ֽ�ŷ���,Ĭ��FALSE,��Ϊ����
	BOOL m_bLandscape;

	
public :
	CPageLayout()
		:m_top(2000),m_bottom(2000),m_left(2000),m_right(2000)
		,m_bCenter(TRUE),m_bVCenter(TRUE),m_bLandscape(FALSE)
	{  }
	//����������õ�ע���������ļ�
	void Save();
	//�������ò���
	void Load();

};

