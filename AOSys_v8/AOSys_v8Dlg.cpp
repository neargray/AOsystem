
// AOSys_v8Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"

#include "AOSys_v8.h"
#include "AOSys_v8Dlg.h"
#include "AOSystem_DataStructures.h"
#include "AOSdllImport.h"
#include "macroExtern.h"
#include "zernike.h"
#include <vector>
#include <string>		
#include <fstream>		
#include <iomanip>	
#include <cstdlib>	
#include <iostream>
#include "assert.h"		
#include <bitset>		
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


//----------------------------------------------------  分割线  ----------------------------------------------------//


#pragma region 框架代码

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAOSys_v8Dlg 对话框，对话框初始化值
CAOSys_v8Dlg::CAOSys_v8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAOSys_v8Dlg::IDD, pParent)
	, m_Edit_Sta_WfsName(_T(""))
	, m_Eit_Sta_WfsSN(_T(""))
	, m_Edit_Sta_RscName(_T(""))
	, m_Edit_Sta_Expo(_T(""))
	, m_Edit_Sta_Gain(_T(""))
	, m_Edit_Sta_BL(_T(""))
	, m_Edit_Manufacture(_T(""))
	, m_Edit_CMOSSN(_T(""))
	, m_Edit_Sta_Calibration(_T(""))
	, m_Edit_Sta_Resolution(_T(""))
	, m_Edit_Sta_SubApture(_T(""))
	, m_Edit_Sta_SubApture_Y(_T(""))
	, m_Edit_Sta_PupilDia_X(_T(""))
	, m_Edit_Sta_PupilDia_Y(_T(""))
	, m_Edit_Sta_PupilCenter_X(_T(""))
	, m_Edit_Sta_Pupil_Center_Y(_T(""))
	, m_Edit_WFSStatus(_T(""))
	, m_Edit_DMStatus(_T(""))
	, m_Edit_WFSSel(_T(""))
	, m_Edit_Grid_Index(_T(""))
	, m_Edit_Sta_Write(_T(""))
	, m_Edit_Sta_BeamCen_X(_T(""))
	, m_Edit_Sta_BeamCen_Y(_T(""))
	, m_Edit_Sta_BeamDia_X(_T(""))
	, m_Edit_Sta_BeamDia_Y(_T(""))
	, m_Edit_Sta_WavefrontType(_T(""))
	, m_Edit_Sta_PupilLimit(_T(""))
	, m_Edit_Sta_PV(_T(""))
	, m_Edit_Sta_Frame(_T(""))
	, m_Edit_Sta_RMS(_T(""))
	, m_Edit_Show_PupilLimit(_T(""))
	, m_Edit_Show_WavefrontType(_T(""))
	, m_Edit_PupilCenter_X(_T(""))
	, m_Edit_PupilCenter_Y(_T(""))
	, m_Edit_PupilDia_X(_T(""))
	, m_Edit_PupilDia_Y(_T(""))
	, m_Edit_Show_BL(_T(""))
	, m_Edit_Show_CancelTilt(_T(""))
	, m_Edit_Sta_CancelTilt(_T(""))
	, m_Edit_Sta_GridType(_T(""))
	, m_Edit_Sta_Map(_T(""))
	, m_Edit_Sta_Time(_T(""))
	, m_Edit_Sta_Watch(_T(""))
	, m_Edit_SetNoiseCut(_T(""))
	, m_Edit_Std_NoiseCut(_T(""))
	, m_Edit_CoordMove_X(_T(""))
	, m_Edit_CoordMove_Y(_T(""))
	, m_Edit_ShowPID_I(_T(""))
	, m_Edit_ShowPID_D(_T(""))
	, m_Edit_ShowPID_P(_T(""))
	, m_Edit_SetPID_D(_T(""))
	, m_Edit_SetPID_I(_T(""))
	, m_Edit_SetPID_P(_T(""))
	, m_Edit_SetAngle(_T(""))
	, m_Edit_ShowMerit(_T(""))
	, m_Edit_Show_NewTimer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAOSys_v8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);   // 绑定控件的成员变量与控件ID
	DDX_Text(pDX, IDC_EDIT_STA_EXPO, m_Edit_Sta_Expo);
	DDX_Text(pDX, IDC_EDIT_STA_GAIN, m_Edit_Sta_Gain);
	DDX_Text(pDX, IDC_EDIT_STA_BL, m_Edit_Sta_BL);
	DDX_Text(pDX, IDC_EDIT_STA_CALIBRATION, m_Edit_Sta_Calibration);
	DDX_Text(pDX, IDC_EDIT_STA_RESOLUTION, m_Edit_Sta_Resolution);
	DDX_Text(pDX, IDC_EDIT_STA_SUBAPTURE, m_Edit_Sta_SubApture);
	DDX_Text(pDX, IDC_EDIT_STA_SUBAPTURE_Y, m_Edit_Sta_SubApture_Y);
	DDX_Text(pDX, IDC_EDIT_STA_PUPILDIA_X, m_Edit_Sta_PupilDia_X);
	DDX_Text(pDX, IDC_EDIT_STA_PUPILDIA_Y, m_Edit_Sta_PupilDia_Y);
	DDX_Text(pDX, IDC_EDIT_STA_PUPIL_CENTER_X, m_Edit_Sta_PupilCenter_X);
	DDX_Text(pDX, IDC_EDIT_STA_PUPIL_CENTER_Y, m_Edit_Sta_Pupil_Center_Y);
	DDX_Text(pDX, IDC_EDIT_WFSSTATUS, m_Edit_WFSStatus);
	DDX_Text(pDX, IDC_EDIT_DMSTATUS, m_Edit_DMStatus);
	DDX_Text(pDX, IDC_EDIT_WFSSEL, m_Edit_WFSSel);
	DDX_Text(pDX, IDC_EDIT_STA_WRITE, m_Edit_Sta_Write);
	DDX_Text(pDX, IDC_EDIT_STA_WAVEFRONT_TYPE, m_Edit_Sta_WavefrontType);
	DDX_Text(pDX, IDC_EDIT_STA_PUPIL_LIMIT, m_Edit_Sta_PupilLimit);
	DDX_Text(pDX, IDC_EDIT_STA_PV, m_Edit_Sta_PV);
	DDX_Text(pDX, IDC_EDIT_STA_FRAME, m_Edit_Sta_Frame);
	DDX_Text(pDX, IDC_EDIT_STA_RMS, m_Edit_Sta_RMS);
	DDX_Text(pDX, IDC_EDIT_SHOW_PUPIL_LIMIT, m_Edit_Show_PupilLimit);
	DDX_Text(pDX, IDC_EDIT_SHOW_WAVEFRONT_TYPE, m_Edit_Show_WavefrontType);
	DDX_Text(pDX, IDC_EDIT_PUPIL_CENTER_X, m_Edit_PupilCenter_X);
	DDX_Text(pDX, IDC_EDIT_PUPIL_CENTER_Y, m_Edit_PupilCenter_Y);
	DDX_Text(pDX, IDC_EDIT_PUPILDIA_X, m_Edit_PupilDia_X);
	DDX_Text(pDX, IDC_EDIT_PUPILDIA_Y, m_Edit_PupilDia_Y);
	DDX_Text(pDX, IDC_EDIT_SHOW_BL, m_Edit_Show_BL);
	DDX_Text(pDX, IDC_EDIT_SHOW_CANCELTILT, m_Edit_Show_CancelTilt);
	DDX_Text(pDX, IDC_EDIT_STA_CANCELTILT, m_Edit_Sta_CancelTilt);
	DDX_Text(pDX, IDC_EDIT_STA_TIME, m_Edit_Sta_Time);
	DDX_Text(pDX, IDC_EDIT_STA_WATCH, m_Edit_Sta_Watch);
	DDX_Control(pDX, IDC_TAB_DISPLAY, m_tabDisplay);
	DDX_Text(pDX, IDC_EDIT_NC, m_Edit_SetNoiseCut);
	DDX_Text(pDX, IDC_EDIT_STA_NC, m_Edit_Std_NoiseCut);
	DDX_Text(pDX, IDC_EDIT_COORDMOVE_X, m_Edit_CoordMove_X);
	DDX_Text(pDX, IDC_EDIT_COORDMOVE_Y, m_Edit_CoordMove_Y);
	DDX_Text(pDX, IDC_EDIT_SHOWPID_I, m_Edit_ShowPID_I);
	DDX_Text(pDX, IDC_EDIT_SHOWPID_D, m_Edit_ShowPID_D);
	DDX_Text(pDX, IDC_EDIT_SHOWPID_P, m_Edit_ShowPID_P);
	DDX_Text(pDX, IDC_EDIT_SETPID_D, m_Edit_SetPID_D);
	DDX_Text(pDX, IDC_EDIT_SETPID_I, m_Edit_SetPID_I);
	DDX_Text(pDX, IDC_EDIT_SETPID_P, m_Edit_SetPID_P);
	DDX_Text(pDX, IDC_EDIT_SETANGLE, m_Edit_SetAngle);
	DDX_Control(pDX, IDC_COMBO_CHOOSEALGO, m_Combo_ChooseAlgo);
	DDX_Text(pDX, IDC_EDIT_SHOWMERIT, m_Edit_ShowMerit);
	DDX_Text(pDX, IDC_EDIT_SHOW_NEWTIMER, m_Edit_Show_NewTimer);
}

BEGIN_MESSAGE_MAP(CAOSys_v8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_WFS_INI, &CAOSys_v8Dlg::OnClickedButtonWfsIni)
	ON_BN_CLICKED(IDC_BUTTON_DM_INI, &CAOSys_v8Dlg::OnClickedButtonDmIni)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CAOSys_v8Dlg::OnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_DET_DETECTION, &CAOSys_v8Dlg::OnClickedButtonDetDetection)
	ON_BN_CLICKED(IDC_BUTTON_DET_WRITE, &CAOSys_v8Dlg::OnClickedButtonDetWrite)
	ON_BN_CLICKED(IDC_BUTTON_REC_RECONSTRUCTION, &CAOSys_v8Dlg::OnClickedButtonRecReconstruction)
	ON_BN_CLICKED(IDC_BUTTON_REC_WRITE, &CAOSys_v8Dlg::OnClickedButtonRecWrite)
	ON_BN_CLICKED(IDC_BUTTON_CON_CLOSELOOP, &CAOSys_v8Dlg::OnClickedButtonConCloseloop)
	ON_BN_CLICKED(IDC_BUTTON_CON_WRITE, &CAOSys_v8Dlg::OnClickedButtonConWrite)
	ON_BN_CLICKED(IDC_BUTTON_REC_ZERFITERR, &CAOSys_v8Dlg::OnClickedButtonRecZerfiterr)
	ON_BN_CLICKED(IDC_BUTTON_REC_CON_DM, &CAOSys_v8Dlg::OnClickedButtonRecConDm)
	ON_BN_CLICKED(IDC_BUTTON_DM_ZERO, &CAOSys_v8Dlg::OnClickedButtonDmZero)
	ON_BN_CLICKED(IDC_BUTTON_DM_CENTERUP, &CAOSys_v8Dlg::OnClickedButtonDmCenterup)
	ON_BN_CLICKED(IDC_BUTTON_INTERRUPT, &CAOSys_v8Dlg::OnBnClickedButtonInterrupt)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DISPLAY, &CAOSys_v8Dlg::OnTcnSelchangeTabDisplay)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE_MEM, &CAOSys_v8Dlg::OnBnClickedButtonReleaseMem)
	ON_BN_CLICKED(IDC_BUTTON_GEARUP, &CAOSys_v8Dlg::OnBnClickedButtonGearup)
	ON_CBN_SELCHANGE(IDC_COMBO_CHOOSEALGO, &CAOSys_v8Dlg::OnSelchangeComboChoosealgo)
	ON_BN_CLICKED(IDC_BUTTON_PRE_CALC, &CAOSys_v8Dlg::OnBnClickedButtonPreCalc)

END_MESSAGE_MAP()


// CAOSys_v8Dlg 消息处理程序

BOOL CAOSys_v8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//----------------------------------------------------  分割线  ----------------------------------------------------//

#pragma region 设置TAB控件


	// 为TAB控件添加标签
	m_tabDisplay.InsertItem(0, _T("子孔径实时图像"));
	m_tabDisplay.InsertItem(2, _T("变形镜控制矩阵"));
	m_tabDisplay.InsertItem(3, _T("脱靶量"));
	m_tabDisplay.InsertItem(4, _T("其他设置"));



	// 给每个对话框初始化指针，这个指针如何释放？这是一个全局的指针吧？
	ptr_SubApertureImageDlg = new CSubApertureDlg();
	ptr_DeformMirrorDlg = new CDeformMirrorDlg();
	ptr_DeviationXDlg = new CDeviationXDlg();
	ptr_MiscSettingDlg = new CMiscSettingDlg();



	// 在响应的TAB控件标签页上创建对话框
	ptr_SubApertureImageDlg->Create(IDD_DIALOG_SUBAPERTURE, &m_tabDisplay);
	ptr_DeformMirrorDlg->Create(IDD_DIALOG_DMMATRIX, &m_tabDisplay);
	ptr_DeviationXDlg->Create(IDD_DIALOG_DEVIATION_X, &m_tabDisplay);
	ptr_MiscSettingDlg->Create(IDD_DIALOG_MISCSETTING, &m_tabDisplay);


	// 调整tabRect，使其覆盖范围适合放置标签页   
	CRect tabRect;   // 标签控件客户区的位置和大小  
	m_tabDisplay.GetClientRect(&tabRect);
	tabRect.left += 0;
	tabRect.right -= 5;
	tabRect.top += 25;
	tabRect.bottom -= 0;


	ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);



#pragma endregion 设置TAB控件



#pragma region 初始化Edit控件值

	CString str;

	// 光瞳直径
	str = TEXT("3");
	GetDlgItem(IDC_EDIT_PUPILDIA_X)->SetWindowText(str);
	str = TEXT("3");
	GetDlgItem(IDC_EDIT_PUPILDIA_Y)->SetWindowText(str);

	// 光瞳中心位置
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_PUPIL_CENTER_X)->SetWindowText(str);
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_PUPIL_CENTER_Y)->SetWindowText(str);

	// 波前类型
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_STA_WAVEFRONT_TYPE)->SetWindowText(str);

	// 是否限制光瞳
	str = TEXT("1");
	GetDlgItem(IDC_EDIT_STA_PUPIL_LIMIT)->SetWindowText(str);

	// 是否取消平均斜率
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_SHOW_CANCELTILT)->SetWindowText(str);

	// BlackOffset
	str = TEXT("100");
	GetDlgItem(IDC_EDIT_SHOW_BL)->SetWindowText(str);

	// NoiseCut   IDC_EDIT_NC
	str = TEXT("20");
	GetDlgItem(IDC_EDIT_NC)->SetWindowText(str);



	// WFS与DM坐标相对偏移位置
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_COORDMOVE_X)->SetWindowText(str);
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_COORDMOVE_Y)->SetWindowText(str);

	// PID参数的设置
	str = TEXT("1");
	GetDlgItem(IDC_EDIT_SETPID_P)->SetWindowText(str);
	str = TEXT("0.1");
	GetDlgItem(IDC_EDIT_SETPID_I)->SetWindowText(str);
	str = TEXT("0.1");
	GetDlgItem(IDC_EDIT_SETPID_D)->SetWindowText(str);

	// 子对话框Edit控件默认值设置
	str = TEXT("1000");
	(ptr_MiscSettingDlg->GetDlgItem(IDC_EDIT_SUBDLG_TIMERSETTING))->SetWindowText(str);

	// 默认旋转角度设为0度
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_SETANGLE)->SetWindowText(str);


#pragma endregion 初始化Edit控件值



	// 选择算法的combo box
	m_Combo_ChooseAlgo.AddString(L"PID算法");
	m_Combo_ChooseAlgo.AddString(L"梯度算法");
	m_Combo_ChooseAlgo.AddString(L"直接斜率法");
	m_Combo_ChooseAlgo.SetCurSel(2);  // 默认算法



	// 与警报相关的控件初始化
	str = "没有警报";
	SetDlgItemText(IDC_STATIC_SHOW_ERROR, str);



	//----------------------------------------------------  分割线  ----------------------------------------------------//


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAOSys_v8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAOSys_v8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示
HCURSOR CAOSys_v8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma endregion 框架代码


//----------------------------------------------------  分割线  ----------------------------------------------------//


#pragma region 全局变量
//----------------------------------------------------  全局变量  ----------------------------------------------------//

//  将结构体实例化，结构体默认权限是公有成员
instr_t				instr;
instr_setup_t		instr_setup;
spotinfo_t			spotinfo;
AOSystemData*		aoSystemData;
AOSystemData		aoSystemData_LOCAL;		// [no use]


//     WFS_32
int               err;
int               selection;

double            expos_act, master_gain_act;
ViInt32		      blackLevelOffsetAct;  // 初始值设置为50
ViInt32			  NoiseCutAct;


// 质心位置
float             centroid_x[40][50];
float             centroid_y[40][50];

// 参考位置
float             reference_x[40][50];
float             reference_y[40][50];


// 全局变量
// 脱靶量的位置，全局函数MeanInterpolation_KillNAN需要使用，PID算法需要使用
float             deviation_x[40][50];
float             deviation_y[40][50];

// 全局变量，用于extern
float			  rememberDeviationX[40][50][100]; // 用于记录每个时刻脱靶量的值
float			  rememberDeviationY[40][50][100]; // 用于记录每个时刻脱靶量的值


float             wavefront[40][50];
float             Wavefront_Copy[29][29];


ViChar            resourceName[256];
//FILE              *fp;


int iDMVoltage[144];

long int		i_WFS = 0;
int				runWFS = 1;

float			zerWave[144];  // 拟合的波前值
float*			zerWave_ptr = zerWave;
float			zerWave_ptr29[841];  // 29x29网格使用的Zernike一维拟合
float			zerWave_Matrix[12][12];
float			zerWave_Matrix29[29][29]; // 29x29网格使用的Zernike拟合矩阵
int				zerCount = 0;
int				zerCount2 = 0;
float			zerWave_Matrix_Temp[12][12];
float			zerWave_Matrix_Temp29[29][29];
float			zerPolyError[12][12];
float			zerPolyError29[29][29];

//## C风格的变量逐渐废弃不用，逐渐采用C++风格的变量
float			x_cord[144];  // 144个X坐标
float			y_cord[144];  // 144个Y坐标
float			x_cord29[841]; // 841个X坐标
float			y_cord29[841];// 841个Y坐标


// 保证计算精度，选择double类型
double			DM_Stroke_pre1[12][12];  // 预先定义的DM的行程矩阵
double			DM_Stroke_1D[144];	//## 这个变量要被废弃

double			coeff[3];  // nm - V映射系数
int				DMcount = 0;  // 计数器：二维DM数据转为一维时用

ViPReal64*		fitErrMean;
ViPReal64*		fitErrStdev;

float			ZeroBias_float = 0;
float			UnitFactor = 0;

int				gridIndex = 0;  // 0是12x12的网格，1是29x29的网格



////////////////////////////// PID算法的全局变量  //////////////////////////////////
// vector版本
std::vector<std::vector<double>> pupil;

// zernike15阶的基底矩阵
std::vector<std::vector<double>> zernikeMatrix_01;
std::vector<std::vector<double>> zernikeMatrix_02;
std::vector<std::vector<double>> zernikeMatrix_03;
std::vector<std::vector<double>> zernikeMatrix_04;
std::vector<std::vector<double>> zernikeMatrix_05;
std::vector<std::vector<double>> zernikeMatrix_06;
std::vector<std::vector<double>> zernikeMatrix_07;
std::vector<std::vector<double>> zernikeMatrix_08;
std::vector<std::vector<double>> zernikeMatrix_09;
std::vector<std::vector<double>> zernikeMatrix_10;
std::vector<std::vector<double>> zernikeMatrix_11;
std::vector<std::vector<double>> zernikeMatrix_12;
std::vector<std::vector<double>> zernikeMatrix_13;
std::vector<std::vector<double>> zernikeMatrix_14;
std::vector<std::vector<double>> zernikeMatrix_15;


// zernike拟合的方法控制变形镜
std::vector<std::vector<double>> zernikeMatrix_recon;   // 只能用作全局变量，因为子类extern，初始化放置于BOOL CAOSys_v8Dlg::OnInitDialog()函数中




// 数组版本
double pupil_portal[12][12];

double zernikeMatrix_01_portal[12][12];
double zernikeMatrix_02_portal[12][12];
double zernikeMatrix_03_portal[12][12];
double zernikeMatrix_04_portal[12][12];
double zernikeMatrix_05_portal[12][12];
double zernikeMatrix_06_portal[12][12];
double zernikeMatrix_07_portal[12][12];
double zernikeMatrix_08_portal[12][12];
double zernikeMatrix_09_portal[12][12];
double zernikeMatrix_10_portal[12][12];
double zernikeMatrix_11_portal[12][12];
double zernikeMatrix_12_portal[12][12];
double zernikeMatrix_13_portal[12][12];
double zernikeMatrix_14_portal[12][12];
double zernikeMatrix_15_portal[12][12];

double zernikeMatrix_recon_portal[12][12];




// 高速模式下定标位置的坐标位置
// 数组形式
float			XScale_array[50];
float			YScale_array[40];

std::vector<float> XScale_vector(50);
std::vector<float> YScale_vector(40);

std::vector<std::vector<double>>	lsqA;
std::vector<std::vector<double>>	eff_picked;

BOOL CloseLoopFlag = FALSE;

// 下面是与图像有关的变量
ViUInt8			imageBuf[480 * 480 + 10];  // 一维形式
ViPInt32		row_image;
ViPInt32		col_image;
IplImage*		m_img;  // 读取图片
BOOL			CMOSImageFlag = TRUE;

// PID参数，以全局变量的形式，在多个事件中有用到
double pid_p, pid_i, pid_d;
double DM_PID_P[144];  
double DM_PID_I[144]; 
double DM_PID_D[144];

// 相对坐标偏移
double coordMoveX;
double coordMoveY;

// 子对话框的全局变量
double timerSetterInterval;

int angleRotate;

int chooseAlgoIndex;




////////////////////////////// 梯度算法的全局变量  //////////////////////////////////





////////////////////////////// 直接斜率法的全局变量  //////////////////////////////////
double bias_initial = 100;   // 冲击响应函数的偏置量，单位nm
double impulse_stroke = 2600;  // 冲击响应函数的冲击量，单位nm



////////////////////////////// 与异常相关的全局变量  //////////////////////////////////
// 与报警相关的变量，如果有错误就在IDC_STATIC_SHOW_ERROR控件上显示出来
CString str_showerror;    // 用于状态栏字符的显示






#pragma endregion 全局变量



//----------------------------------------------------  分割线  ----------------------------------------------------//


#pragma region 事件代码


//--------------------------  全局事件  --------------------------//
// 初始化WFS设备
// WFS分辨率：480x480，对应的子孔径阵列为：29x29
void CAOSys_v8Dlg::OnClickedButtonWfsIni()
{
	WFS_Initialization_Sequence(this);
}

// 初始化DM设备
// 每次从一种工作模式切换到另一中工作模式时，需要使用此事件，比如从“波前探测事件”转入“波前重建事件”
void CAOSys_v8Dlg::OnClickedButtonDmIni()
{
	// 初始化DM,会使得DM的电压更改为零
	if (P_AOS_Initialize(0) > 0)
	{
		GetDlgItem(IDC_EDIT_DMSTATUS)->SetWindowText(_T("DM 已初始化"));
	}

	// 为数据结构体设置一个本地地址（locally defined memory address）
	P_AOS_GetVarAddress(VAR_DM_DATA, (void**)&aoSystemData);

	// max voltage = 300 V     range of stroke = 0x4000=16384
	// 16384/300 = 54.6
	//## 这个参数现在应该没有用了
	aoSystemData->Volt.DMVoltageScale = 54.6;

	// 设置电压转换到行程的系数
	coeff[0] = 0.0413;
	coeff[1] = 3.97;
	coeff[2] = 0;


}



// 关闭WFS设备和DM设备
// 两次点击这个按钮会导致程序关闭，不知道为什么
void CAOSys_v8Dlg::OnClickedButtonClose()
{
	if (WFS_close(instr.handle) == 0)
	{
		GetDlgItem(IDC_EDIT_WFSSTATUS)->SetWindowText(_T("WFS 已断开"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_WFSSTATUS)->SetWindowText(_T("WFS 未成功断开"));
	}


	if (P_AOS_Close() == 0)
	{
		GetDlgItem(IDC_EDIT_DMSTATUS)->SetWindowText(_T("DM 已断开"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_DMSTATUS)->SetWindowText(_T("DM 未成功断开"));
	}

}


//--------------------------  波前探测事件  --------------------------//
// 此阶段不需要开启网格

// 开始波前探测
void CAOSys_v8Dlg::OnClickedButtonDetDetection()
{
	pThread_DET = new CWinThread();
	pThread_DET->m_bAutoDelete = FALSE;
	pThread_DET = AfxBeginThread(ThreadFunc_WFS_Measurement_DET, this);  // 使用this指针将CAOSys_v7Dlg类传入线程函数
}

// 将波前探测数据写入文件
void CAOSys_v8Dlg::OnClickedButtonDetWrite()
{
	// TODO:  在此添加控件通知处理程序代码
}


//--------------------------  波前重建事件  --------------------------//
// 此阶段需要开启29x29网格

//## 注意，在波前重建模式下，“波前重建”按钮与“控制DM”按钮要成对使用，因为在“波前重建”按钮中zernikeMatrix_recon要push_back
//## 而在中，要对应的把zernikeMatrix_recon与zernikeMatrix_recon_1d两个变量pop_back才可以，否则数据堆积，造成无法正确控制DM
// 波前重建模式下 波前重建事件
void CAOSys_v8Dlg::OnClickedButtonRecReconstruction()
{
	pThread_REC = new CWinThread();
	pThread_REC->m_bAutoDelete = FALSE;
	pThread_REC = AfxBeginThread(ThreadFunc_WFS_Measurement_REC, this);  // 使用this指针将CAOSys_v7Dlg类传入线程函数

}  // 波前重建模式下 波前重建事件



//## 注意，在波前重建模式下，“波前重建”按钮与“控制DM”按钮要成对使用，因为在“波前重建”按钮中zernikeMatrix_recon要push_back
//## 而在中，要对应的把zernikeMatrix_recon与zernikeMatrix_recon_1d两个变量pop_back才可以，否则数据堆积，造成无法正确控制DM
// 波前重建模式下控制变形镜
void CAOSys_v8Dlg::OnClickedButtonRecConDm()
{


}// 波前重建模式下控制变形镜



void CAOSys_v8Dlg::OnClickedButtonDmZero()
{


}



// 计算Zernike拟合误差
// 选择合适的网格，WFS探测到的波前减去Zernike拟合的波前
void CAOSys_v8Dlg::OnClickedButtonRecZerfiterr()
{

}

// 波前重建模式下  写入文本事件
void CAOSys_v8Dlg::OnClickedButtonRecWrite()
{

}  // 波前重建模式下  写入文本事件



//--------------------------  波前校正事件  --------------------------//
// 此阶段需要开启12x12网格

// 开始闭环校正波前
void CAOSys_v8Dlg::OnClickedButtonConCloseloop()
{


	// 线程的参数设置
	int       nPriority = THREAD_PRIORITY_HIGHEST;//默认为THREAD_PRIORITY_NORMAL
	UINT       nStackSize = 0;//与创建它的线程堆栈大小相同
	DWORD       dwCreateFlags = CREATE_SUSPENDED;//CREATE_SUSPENDED 创建后挂起线程

	// 创建新线程
	pThread_LOOP = new CWinThread();
	pThread_LOOP->m_bAutoDelete = FALSE;  // 防止MFC删除CWinThread对象
	pThread_LOOP = AfxBeginThread(ThreadFunc_WFS_Measurement_CONLOOP, this,
		nPriority, nStackSize, dwCreateFlags);  // 使用this指针将CAOSys_v7Dlg类传入线程函数
	pThread_LOOP->ResumeThread();

	DWORD dwExitCode;
	::GetExitCodeThread(pThread_LOOP->m_hThread, &dwExitCode);
	if (!(dwExitCode==STILL_ACTIVE))  // 如果线程不在活动，则删除
	{
		delete pThread_LOOP;
	}


}

// 将波前校正数据写入文件
void CAOSys_v8Dlg::OnClickedButtonConWrite()
{
	// TODO:  在此添加控件通知处理程序代码
}


//--------------------------  其它事件  --------------------------//

// 用于寻找WFS与DM的中心位置
void CAOSys_v8Dlg::OnClickedButtonDmCenterup()
{


}


// 中断事件
void CAOSys_v8Dlg::OnBnClickedButtonInterrupt()
{
	CloseLoopFlag = FALSE;
}



// TAB控件的消息函数
void CAOSys_v8Dlg::OnTcnSelchangeTabDisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	// 调整tabRect，使其覆盖范围适合放置标签页   
	CRect tabRect;   // 标签控件客户区的位置和大小  
	m_tabDisplay.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;


	switch (m_tabDisplay.GetCurSel())
	{
	case 0:
		// 根据调整好的tabRect放置m_SubApertureDlg子对话框，并设置为显示   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为隐藏 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 1:
		// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为隐藏   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为隐藏 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 2:
		// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为隐藏   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为显示 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 3:
		// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为隐藏   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为显示 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

		break;



	default:
		break;
	}

}



// 清理内存，以使程序连续运行
void CAOSys_v8Dlg::OnBnClickedButtonReleaseMem()
{
	// TODO: Add your control notification handler code here

	// 清理基底
	if (zernikeMatrix_01.size() > 0)
	{
		// 如果小于capacity，则不reallocate
		zernikeMatrix_01.clear();
		zernikeMatrix_02.clear();
		zernikeMatrix_03.clear();
		zernikeMatrix_04.clear();
		zernikeMatrix_05.clear();
		zernikeMatrix_06.clear();
		zernikeMatrix_07.clear();
		zernikeMatrix_08.clear();
		zernikeMatrix_09.clear();
		zernikeMatrix_10.clear();
		zernikeMatrix_11.clear();
		zernikeMatrix_12.clear();
		zernikeMatrix_13.clear();
		zernikeMatrix_14.clear();
		zernikeMatrix_15.clear();
	}

	// 弹出重新初始化PID参数
	if (pid_p != 0 || pid_i != 0 || pid_d != 0)
	{
		pid_p = 0;
		pid_i = 0;
		pid_d = 0;
	}



	// 与报警相关的内容处理
	BOOL FLAG_NAN = 0;  // 0表示没有NAN数据，1表示有NAN数据
	str_showerror = "没有警报";
	SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);


}



void CAOSys_v8Dlg::OnBnClickedButtonGearup()
{
	// TODO: Add your control notification handler code here

	//##number 1    设置并显示光瞳的相关参数
	//在WFS_SetPupil函数中使用
	GetDlgItem(IDC_EDIT_PUPIL_CENTER_X)->GetWindowText(m_Edit_PupilCenter_X);		// 输入光瞳中心x坐标
	instr_setup.pupil_center_x_mm = _ttof(m_Edit_PupilCenter_X);
	(GetDlgItem(IDC_EDIT_PUPIL_CENTER_Y))->GetWindowText(m_Edit_PupilCenter_Y);		// 输入光瞳中心y坐标
	instr_setup.pupil_center_y_mm = _ttof(m_Edit_PupilCenter_Y);
	(GetDlgItem(IDC_EDIT_PUPILDIA_X))->GetWindowText(m_Edit_PupilDia_X);			// 输入光瞳直径x
	instr_setup.pupil_dia_x_mm = _ttof(m_Edit_PupilDia_X);
	(GetDlgItem(IDC_EDIT_PUPILDIA_Y))->GetWindowText(m_Edit_PupilDia_Y);			// 输入光瞳直径y
	instr_setup.pupil_dia_y_mm = _ttof(m_Edit_PupilDia_Y);
	WFS_SetPupil(instr.handle, instr_setup.pupil_center_x_mm, instr_setup.pupil_center_y_mm, // 设置光瞳
		instr_setup.pupil_dia_x_mm, instr_setup.pupil_dia_y_mm);
	(m_Edit_Sta_PupilCenter_X).Format(_T("%lf"), instr_setup.pupil_center_x_mm);	// 输出光瞳x方向位置 
	SetDlgItemTextW(IDC_EDIT_STA_PUPIL_CENTER_X, m_Edit_Sta_PupilCenter_X);
	(m_Edit_Sta_Pupil_Center_Y).Format(_T("%lf"), instr_setup.pupil_center_y_mm);	// 输出光瞳x方向位置  
	SetDlgItemTextW(IDC_EDIT_STA_PUPIL_CENTER_Y, m_Edit_Sta_Pupil_Center_Y);
	(m_Edit_Sta_PupilDia_X).Format(_T("%lf"), instr_setup.pupil_dia_x_mm);			// 输出光瞳x方向直径  
	SetDlgItemTextW(IDC_EDIT_STA_PUPILDIA_X, m_Edit_Sta_PupilDia_X);
	(m_Edit_Sta_PupilDia_Y).Format(_T("%lf"), instr_setup.pupil_dia_y_mm);			// 输出光瞳y方向直径  
	SetDlgItemTextW(IDC_EDIT_STA_PUPILDIA_Y, m_Edit_Sta_PupilDia_Y);



	//##number2
	// 设置并显示是否要canceltilt
	// 在WFS_CalcSpotToReferenceDeviations函数中使用
	(GetDlgItem(IDC_EDIT_SHOW_CANCELTILT))->GetWindowTextW(m_Edit_Show_CancelTilt);
	instr_setup.cancel_tilt = _ttoi(m_Edit_Show_CancelTilt);
	if (instr_setup.cancel_tilt == 0)
	{
		(GetDlgItem(IDC_EDIT_STA_CANCELTILT))->SetWindowTextW(_T("未校正倾斜"));
	}
	else if (instr_setup.cancel_tilt == 1)
	{
		(GetDlgItem(IDC_EDIT_STA_CANCELTILT))->SetWindowTextW(_T("已校正倾斜"));
	}



	//##number3
	// 设置并显示是否限制光瞳
	// 在WFS_CalcWavefront函数中使用
	(GetDlgItem(IDC_EDIT_STA_PUPIL_LIMIT))->GetWindowText(m_Edit_Sta_PupilLimit);
	instr_setup.pupil_circular = _ttoi(m_Edit_Sta_PupilLimit);
	// 显示设置内容
	if (instr_setup.pupil_circular == 0)
	{
		(GetDlgItem(IDC_EDIT_SHOW_PUPIL_LIMIT))->SetWindowText(_T("不限制光瞳"));
	}
	else if (instr_setup.pupil_circular == 1)
	{
		(GetDlgItem(IDC_EDIT_SHOW_PUPIL_LIMIT))->SetWindowText(_T("限制光瞳"));
	}




	//##number4
	// 设置并显示波前类型
	// 在WFS_CalcWavefront中使用
	(GetDlgItem(IDC_EDIT_STA_WAVEFRONT_TYPE))->GetWindowText(m_Edit_Sta_WavefrontType);
	instr_setup.wavefront_type = _ttoi(m_Edit_Sta_WavefrontType);
	if (instr_setup.wavefront_type == 0)
	{
		(GetDlgItem(IDC_EDIT_SHOW_WAVEFRONT_TYPE))->SetWindowText(_T("测量波前"));
	}
	else if (instr_setup.wavefront_type == 1)
	{
		(GetDlgItem(IDC_EDIT_SHOW_WAVEFRONT_TYPE))->SetWindowText(_T("拟合波前"));
	}
	else if (instr_setup.wavefront_type == 2)
	{
		(GetDlgItem(IDC_EDIT_SHOW_WAVEFRONT_TYPE))->SetWindowText(_T("差分波前"));
	}



	//##number5
	// 设置并显示Black Offset Level值
	// 在WFS_SetBlackLevelOffset函数中使用
	(GetDlgItem(IDC_EDIT_SHOW_BL))->GetWindowTextW(m_Edit_Show_BL); // 从文本框中读取BlackOffset，转为整型
	blackLevelOffsetAct = _ttoi(m_Edit_Show_BL);
	WFS_SetBlackLevelOffset(instr.handle, blackLevelOffsetAct);
	//输出所设置的Black Offset Level值，校验输入值
	WFS_GetBlackLevelOffset(instr.handle, &blackLevelOffsetAct);
	(m_Edit_Sta_BL).Format(_T("%d"), blackLevelOffsetAct);
	SetDlgItemTextW(IDC_EDIT_STA_BL, m_Edit_Sta_BL);



	//##number6
	// 设置并显示Noise Cut值
	// 在WFS_CutImageNoiseFloor（普通模式），WFS_SetHighspeedMode（高速模式）函数中使用
	(GetDlgItem(IDC_EDIT_NC))->GetWindowTextW(m_Edit_SetNoiseCut); // 从文本框中读取BlackOffset，转为整型
	NoiseCutAct = _ttoi(m_Edit_SetNoiseCut);
	WFS_CutImageNoiseFloor(instr.handle, NoiseCutAct);  // 此函数高速模式下不能使用
	//输出所设置的Noise Cut值，校验输入值
	(m_Edit_Std_NoiseCut).Format(_T("%d"), NoiseCutAct);
	SetDlgItemTextW(IDC_EDIT_STA_NC, m_Edit_Std_NoiseCut);


	//##number7
	// 设置并显示坐标偏移
	// 在zernike函数中使用
	GetDlgItem(IDC_EDIT_COORDMOVE_X)->GetWindowTextW(m_Edit_CoordMove_X); // x方向坐标偏移
	coordMoveX = _ttoi(m_Edit_CoordMove_X);
	GetDlgItem(IDC_EDIT_COORDMOVE_Y)->GetWindowTextW(m_Edit_CoordMove_Y); // x方向坐标偏移
	coordMoveY = _ttoi(m_Edit_CoordMove_Y);


	//## number8
	// 设置PID参数
	GetDlgItem(IDC_EDIT_SETPID_P)->GetWindowText(m_Edit_SetPID_P);	// 获取PID设置
	pid_p = _ttof(m_Edit_SetPID_P);
	GetDlgItem(IDC_EDIT_SETPID_I)->GetWindowText(m_Edit_SetPID_I);
	pid_i = _ttof(m_Edit_SetPID_I);
	GetDlgItem(IDC_EDIT_SETPID_D)->GetWindowText(m_Edit_SetPID_D);
	pid_d = _ttof(m_Edit_SetPID_D);
	m_Edit_ShowPID_P.Format(_T("%lf"), pid_p);						// 输出设置的PID参数
	SetDlgItemTextW(IDC_EDIT_SHOWPID_P, m_Edit_ShowPID_P);
	m_Edit_ShowPID_I.Format(_T("%lf"), pid_i);
	SetDlgItemTextW(IDC_EDIT_SHOWPID_I, m_Edit_ShowPID_I);
	m_Edit_ShowPID_D.Format(_T("%lf"), pid_d);
	SetDlgItemTextW(IDC_EDIT_SHOWPID_D, m_Edit_ShowPID_D);



	// 子对话框的设置
	(ptr_MiscSettingDlg->GetDlgItem(IDC_EDIT_SUBDLG_TIMERSETTING))->GetWindowTextW(ptr_MiscSettingDlg->m_Edit_TimeSetter); // x方向坐标偏移
	timerSetterInterval = _ttoi(ptr_MiscSettingDlg->m_Edit_TimeSetter);


	GetDlgItem(IDC_EDIT_SETANGLE)->GetWindowText(m_Edit_SetAngle);
	angleRotate = _wtoi(m_Edit_SetAngle);




}




void CAOSys_v8Dlg::OnSelchangeComboChoosealgo()
{
	// TODO: Add your control notification handler code here

	chooseAlgoIndex = m_Combo_ChooseAlgo.GetCurSel();
}


// 直接斜率法的预处理事件
void CAOSys_v8Dlg::OnBnClickedButtonPreCalc()
{

	// 线程的参数设置
	int       nPriority = THREAD_PRIORITY_HIGHEST;//默认为THREAD_PRIORITY_NORMAL
	UINT       nStackSize = 0;//与创建它的线程堆栈大小相同
	DWORD       dwCreateFlags = CREATE_SUSPENDED;//CREATE_SUSPENDED 创建后挂起线程

	// 创建新线程
	pThread_PreCalc = new CWinThread();
	pThread_PreCalc->m_bAutoDelete = FALSE;  // 防止MFC删除CWinThread对象
	pThread_PreCalc = AfxBeginThread(ThreadFunc_PreCalculation, this,
		nPriority, nStackSize, dwCreateFlags);  // 使用this指针将CAOSys_v7Dlg类传入线程函数
	pThread_PreCalc->ResumeThread();

	DWORD dwExitCode;
	::GetExitCodeThread(pThread_PreCalc->m_hThread, &dwExitCode);
	if (!(dwExitCode == STILL_ACTIVE))  // 如果线程不在活动，则删除
	{
		delete pThread_PreCalc;
	}


}  // 事件结束



#pragma endregion 事件代码


//----------------------------------------------------  分割线  ----------------------------------------------------//

#pragma region 全局函数

// 处理WFS抛出的错误
void WFS_HandleErrors(int err)
{
	char buf[WFS_ERR_DESCR_BUFFER_SIZE];
	//char*类型转换为多字节输出
	WCHAR W_buf[512];

	if (!err) return;

	// 获得错误字符串
	WFS_error_message(instr.handle, err, buf);

	if (err < 0) // 出现错误
	{
		long multi_buf = MultiByteToWideChar(CP_ACP, 0, buf, strlen(buf), W_buf, sizeof(W_buf));
		W_buf[multi_buf] = '\0';
		CString buf_change;
		buf_change.Format(_T("%s"), W_buf);

		// 输出带变量的message box
		AfxMessageBox(buf_change, MB_OK, 0);

		// 出现问题时，关闭程序
		::MessageBox(NULL, _T("程序将关闭 ！"), _T("错误信息"), MB_OK);
		WFS_close(instr.handle);
		exit(1);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 选择WFS设备
int WFS_SelectInstrument(LPVOID pParam, int* selection, ViChar* resourceName)
{
	// 将对话框类的指针传入函数
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	int            err, instr_cnt;
	ViInt32        device_id;
	int            in_use;

	char           instr_name[WFS_BUFFER_SIZE];
	char           serNr[WFS_BUFFER_SIZE];
	//char           strg[WFS_BUFFER_SIZE];

	//char*类型转换为多字节输出
	//WCHAR W_instr_name[512];
	//WCHAR W_serNr[512];
	//WCHAR W_resourceName[512];

	//## 感觉这个函数可以不需要，直接执行WFS_GetInstrumentListInfo看看行不行
	// 找到空闲设备，返回WFS的设备数目instr_cnt
	if (err = WFS_GetInstrumentListLen(VI_NULL, (ViInt32*)&instr_cnt))
		WFS_HandleErrors(err);

	if (instr_cnt == 0)  // 如果没有找到WFS设备，提示WFS设备没有找到
	{
		::MessageBox(NULL, _T("没有找到任何WFS ！"), _T("WFS状态"), MB_OK);
		return -1;  // 停止WFS初始化过程
	}

	// 找到设备device_id，询问是否初始化，如果没有使用就返回in_use状态信息，in_use=1时无法初始化
	// 这个函数一个主要功能是为了返回指针resourceName
	if (err = WFS_GetInstrumentListInfo(VI_NULL, 0, &device_id, (ViInt32*)&in_use, instr_name, serNr, resourceName))
		WFS_HandleErrors(err);

	if (in_use == 0)  // 如果该设备可以进行初始化，就输出设备的信息
	{
		//## WFS_SelectInstrument下的输出设备相关信息，另外一处在WFS_GetInstrumentInfo函数下

		// 输出设备名称

		// 输出序列号

		// 输出资源名称

		(pW->GetDlgItem(IDC_EDIT_WFSSEL))->SetWindowText(_T("WFS可用"));
	}
	else
	{
		(pW->GetDlgItem(IDC_EDIT_WFSSEL))->SetWindowText(_T("WFS被占用"));
		return -1;
	}

	// 因为设备是WFS10，数字代码是256（十进制）或0x00100（十六进制）
	*selection = DEVICE_OFFSET_WFS10;
	return *selection;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 选择MLA
int SlectMLA(int* selection)
{
	// 只有返回零才能使得WFS运行
	*selection = 0;
	return *selection;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 将初始化WFS功能的函数封装在下面的函数中
void WFS_Initialization_Sequence(LPVOID pParam)
{
	// LPVOID可以用来传递任意简单类型，这里将this指针传进来，下面的语句要还原为对话框类的指针
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;


	//--------------------------------------------------------------------------------
	// 这个函数的主要目的是调用WFS_GetInstrumentListLen获得设备ID（instr.selected_dev_i）与资源名（resourceName）
	// 二者都通过指针传递
	// 这里pW又将对话框类的指针按照LPVOID类型传进去
	if (WFS_SelectInstrument(pW, &(instr.selected_dev_id), resourceName) == 0)
	{
		::MessageBox(NULL, _T("没有选择任何设备！"), _T("连接状态"), MB_OK);
		return;  //这里由于WFS_Initialization_Sequence没有返回类型，所以不用管是否return TRUE;
	}


	//--------------------------------------------------------------------------------
	// 初始化WFS
	err = WFS_init(resourceName, VI_FALSE, VI_FALSE, &instr.handle); // err==0表示执行成功，可以用VI_SUCCESS表示
	if (err == 0)
	{
		(pW->GetDlgItem(IDC_EDIT_WFSSTATUS))->SetWindowText(_T("WFS 已初始化"));
	}
	else
	{
		WFS_HandleErrors(err);
	}


	//--------------------------------------------------------------------------------
	// 这是一个必需函数，因为Thorlabs的MLA是可以装卸的，所以每次初始化要确定选择哪一块MLA
	if (SlectMLA(&instr.selected_mla) < 0)
	{
		::MessageBox(NULL, _T("没有选择任何MLA。"), _T("Link Status"), MB_OK);
		return; // program ends here if no instrument selected
	}


	//--------------------------------------------------------------------------------
	// 设置分辨率（由函数直接设置），获得子孔径数目
	// 这里配置的分辨率要和setpupil的尺寸一致
	//## 这个函数的最后两项依赖于第三项和instr.selected_mla的值
	err = WFS_ConfigureCam(instr.handle, SAMPLE_PIXEL_FORMAT, SAMPLE_CAMERA_RESOL_WFS10,
		(ViInt32*)&spotinfo.spots_x, (ViInt32*)&spotinfo.spots_y);
	if (err == 0)
	{
		// 输出分辨率 无法更改
		(pW->GetDlgItem(IDC_EDIT_STA_RESOLUTION))->SetWindowText(_T("480 X 480"));

		// 输出子孔径阵列数，WFS_ConfigureCam的最后两个参数返回值
		(pW->m_Edit_Sta_SubApture).Format(_T("%d"), spotinfo.spots_x);
		pW->SetDlgItemTextW(IDC_EDIT_STA_SUBAPTURE, pW->m_Edit_Sta_SubApture);
		(pW->m_Edit_Sta_SubApture_Y).Format(_T("%d"), spotinfo.spots_y);
		pW->SetDlgItemTextW(IDC_EDIT_STA_SUBAPTURE_Y, pW->m_Edit_Sta_SubApture_Y);
	}
	else
	{
		WFS_HandleErrors(err);
	}

	//--------------------------------------------------------------------------------


	// 设置并显示定标的类型
	// WFS_SetReferencePlane与WFS_GetReferencePlane函数中使用
	instr_setup.ref_idx = SAMPLE_REF_PLANE;
	WFS_SetReferencePlane(instr.handle, instr_setup.ref_idx);
	WFS_GetReferencePlane(instr.handle, &instr_setup.ref_idx);
	if (instr_setup.ref_idx == 0)
	{
		(pW->GetDlgItem(IDC_EDIT_STA_CALIBRATION))->SetWindowText(_T("物理定标"));
	}
	else
	{
		(pW->GetDlgItem(IDC_EDIT_STA_CALIBRATION))->SetWindowText(_T("相对定标"));
	}

	//--------------------------------------------------------------------------------


	// 设置并显示曝光时间
	WFS_SetExposureTime(instr.handle, 0.18, &expos_act);
	(pW->m_Edit_Sta_Expo).Format(_T("%lf"), expos_act);
	pW->SetDlgItemTextW(IDC_EDIT_STA_EXPO, pW->m_Edit_Sta_Expo);

	// 设置并显示增益
	WFS_SetMasterGain(instr.handle, 1.5, &master_gain_act);
	(pW->m_Edit_Sta_Gain).Format(_T("%lf"), master_gain_act);
	pW->SetDlgItemTextW(IDC_EDIT_STA_GAIN, pW->m_Edit_Sta_Gain);



}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 声明波前探测阶段的线程函数
UINT ThreadFunc_WFS_Measurement_DET(LPVOID pParam)
{



	// 线程函数需要一个返回值
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 波前重建模式下 波前重建线程
UINT ThreadFunc_WFS_Measurement_REC(LPVOID pParam)
{


	return 0;
}  // 波前重建模式下 波前重建线程




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 波前控制的线程函数
UINT ThreadFunc_WFS_Measurement_CONLOOP(LPVOID pParam)
{



#pragma region 梯度算法

	// 选择梯度算法
	if (chooseAlgoIndex == 1)
	{


#pragma region 线程中的局部变量

		// 几个指向对话框的指针
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;


		// 默认操作中变形镜的执行量
		double zernikeMatrix_recon_array_DEFAULT[140];
		// 加操作中变形镜的执行量
		double zernikeMatrix_recon_array_ADD[140];
		// 减操作中变形镜的执行量
		double zernikeMatrix_recon_array_MINUS[140];

		// 默认操作的波前统计参数
		double     wavefront_min_default, wavefront_max_default, wavefront_diff_default, wavefront_mean_default, wavefront_rms_default, wavefront_weighted_rms_default;
		// 加操作的波前统计参数
		double     wavefront_min_add, wavefront_max_add, wavefront_diff_add, wavefront_mean_add, wavefront_rms_add, wavefront_weighted_rms_add;
		// 减操作的波前统计参数
		double     wavefront_min_minus, wavefront_max_minus, wavefront_diff_minus, wavefront_mean_minus, wavefront_rms_minus, wavefront_weighted_rms_minus;

		// 评价函数值
		double meritFunctionValueDefault = 100;
		double meritFunctionValueAdd = 0;
		double meritFunctionValueMinus = 0;

		// 梯度方向
		BOOL DEFAULE_evolve = FALSE;
		BOOL ADD_evolve = FALSE;
		BOOL MINUS_evolve = FALSE;

		double randNum = 50;   // 每个单元的步进值，如果发生不能前进的情况，要采取某种策略改变这个步长

		// 用于显示CMOS图像
		uchar image2DBuf[480][480];  // 二维形式


		// 几个开关
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));  // 显示图像
		CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));  // 显示脱靶量
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));  // 显示变形镜的执行量


		int NAN_counter = 0; // 计算NAN数据的个数

		CString gradientDirection;  // 用于显示梯度方向


		// 用于记录梯度算法三种操作的评价函数变化和梯度方向
		std::vector<std::vector<double>> gradientMerit_vector;
		gradientMerit_vector.resize(3);  // 保存三个操作
		for (int index = 0; index < 3; ++index)
		{
			gradientMerit_vector[index].resize(200);   // 记录200个采样点
		}
		std::vector<double> gradientDirection_vector;  // 记录梯度算法的前进方向
		gradientDirection_vector.resize(200);
		int counter_recordMerit = 0;  // 用于记录评价函数时的计数器，进入闭环之前要置零
		int counter_recordGradientDirection = 0;    //  用于记录梯度进行方向的计数器，进入闭环之前要置零



		// 以脱靶量作为评价函数，要计算光瞳
		// WFS的物理坐标，子孔径的pitch为150um=0.15mm，480x480分辨率下为29x29个子孔径
		float xArray_29[29];
		float yArray_29[29];
		for (int i = 0; i < 29; ++i)
			xArray_29[i] = -2.1 + i * 0.15;
		for (int i = 0; i < 29; ++i)
			yArray_29[i] = -2.1 + i * 0.15;
		// 计算光瞳矩阵，光瞳直径需要设置
		float pupil_deviation[29][29];
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{

				pupil_deviation[row][col] = (float)((sqrt(pow(xArray_29[row], 2) + pow(yArray_29[col], 2)) <= instr_setup.pupil_dia_x_mm / 2) ? 1 : 0);

			}
		}





#pragma endregion 线程中的局部变量



		// 设置变形镜的驱动量
		zernikeMatrix_recon_array_DEFAULT[65] = 2000;
		zernikeMatrix_recon_array_DEFAULT[66] = 2000;
		zernikeMatrix_recon_array_DEFAULT[77] = 2000;
		zernikeMatrix_recon_array_DEFAULT[78] = 2000;


		// 发送给变形镜
		DriveDeformMirror_nm(zernikeMatrix_recon_array_DEFAULT);  // 驱动变形镜运动

		wait4U(10);  // 等待一段时间

		Detect_Wavefront2Deviation_Normal();  // 探测波前，获得脱靶量


		// WFS重建波前
		//根据脱靶量重建波前,wavefront数组的单位是um
		WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);

		std::vector<std::vector<double>> wavefront_vector;
		wavefront_vector.resize(29);
		for (int index = 0; index < 29; ++index)
		{
			wavefront_vector[index].resize(29);
		}
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{
				wavefront_vector[row][col] = wavefront[row][col];
			}
		}

		write_2d_File("D:\\externLib\\AOS\\Output\\StrokeWavefrontRecon.txt", wavefront_vector);


		int a = 0;

	}  // if结束，梯度算法结束

#pragma endregion 梯度算法





#pragma region 直接斜率

	// 直接斜率法，需要预处理数据
	if (chooseAlgoIndex == 2)
	{

		// 载入预处理数据
		lsqA = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\lsqA.txt");
		eff_picked = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\eff_picked.txt");



#pragma region 线程中的局部变量

		// 几个指向对话框的指针
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;
		// 几个开关,checkbox用作开关
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));

		// 与绘图有关的变量,480的分辨率
		uchar image2DBuf[480][480];  // 二维形式

		// 畸变波前有效子孔径的脱靶量组成的一维向量
		std::vector<double> lsqy;  // lsqx=lsqA*lsqy
		lsqy.resize(lsqA[0].size());
		int row_effsub;  // 有效点的行索引号
		int col_effsub;  // 有效点的列索引号

		// 波前统计参数局部变量
		double wavefront_min_ACEMETHOD;
		double wavefront_max_ACEMETHOD;
		double wavefront_diff_ACEMETHOD;
		double wavefront_mean_ACEMETHOD;
		double wavefront_rms_ACEMETHOD;
		double wavefront_weighted_rms_ACEMETHOD;

		double zernikeMatrix_recon_array_ACEMETHOD[144];   // 保存最小二乘法计算的执行量  

		double sum_temp = 0;

		// 直接积分法重建波前
		float  wavefront_DI[40][50];


		// 脱靶量局部变量
		float	deviation_x_DI[40][50];
		float   deviation_y_DI[40][50];


#pragma endregion 线程中的局部变量


		// 闭环
		CloseLoopFlag = TRUE;
		int recordwave_counter = 0;
		while (CloseLoopFlag)
		{

			// 普通模式获取质心位置
			WFS_TakeSpotfieldImage(instr.handle);
			// 计算质心位置
			WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
			// 计算脱靶量
			WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
			// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
			WFS_GetSpotDeviations(instr.handle, *deviation_x_DI, *deviation_y_DI);



#pragma region 去除脱靶量中的无效值

			// 脱靶量为29x29，边界采用置零

			deviation_x_DI[0][0] = 0; deviation_x_DI[0][28] = 0; deviation_x_DI[28][0] = 0; deviation_x_DI[28][28] = 0;  // 四个角置零
			deviation_y_DI[0][0] = 0; deviation_y_DI[0][28] = 0; deviation_y_DI[28][0] = 0; deviation_y_DI[28][28] = 0;  // 四个角置零

			// 最外面四条边置零
			for (int col = 1; col < 28; ++col)  // 第0行
			{
				deviation_x_DI[0][col] = 0;
				deviation_y_DI[0][col] = 0;
			}
			for (int col = 1; col < 28; ++col)  // 第28行
			{
				deviation_x_DI[28][col] = 0;
				deviation_y_DI[28][col] = 0;
			}
			for (int row = 1; row < 28; ++row)  // 第0列
			{
				deviation_x_DI[row][0] = 0;
				deviation_y_DI[row][0] = 0;
			}
			for (int row = 1; row < 28; ++row)  // 第28列
			{
				deviation_x_DI[row][28] = 0;
				deviation_y_DI[row][28] = 0;
			}


			// 对中间的数据进行平均插值
			for (int row = 1; row < 28; ++row)  // 空出最上下两行
			{
				for (int col = 1; col < 28; ++col) // 空出最左右两列
				{

					// 判断x方向
					if (_isnan(deviation_x_DI[row][col]))
					{
						// 排列方式
						//  x x x
						//  x o x
						//  x x x

						if (_isnan(deviation_x_DI[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
							_isnan(deviation_x_DI[row - 1][col]) &&
							_isnan(deviation_x_DI[row - 1][col + 1]) &&
							_isnan(deviation_x_DI[row][col - 1]) &&
							_isnan(deviation_x_DI[row][col + 1]) &&
							_isnan(deviation_x_DI[row + 1][col - 1]) &&
							_isnan(deviation_x_DI[row + 1][col]) &&
							_isnan(deviation_x_DI[row + 1][col + 1]))
						{
							deviation_x_DI[row][col] = 0;
						}
						else
						{
							// 排列方式
							//  x x x
							//  x o x
							//  x x x

							int mean_counter = 0;  // 有效值个数
							float mean_value = 0;  // 有效值的和

							if (!_isnan(deviation_x_DI[row - 1][col - 1]))  // 上左
							{
								mean_value = mean_value + deviation_x_DI[row - 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row - 1][col])) // 上中
							{
								mean_value = mean_value + deviation_x_DI[row - 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row - 1][col + 1])) // 上右
							{
								mean_value = mean_value + deviation_x_DI[row - 1][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row][col - 1])) // 中左
							{
								mean_value = mean_value + deviation_x_DI[row][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row][col + 1])) // 中右
							{
								mean_value = mean_value + deviation_x_DI[row][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row + 1][col - 1])) // 下左
							{
								mean_value = mean_value + deviation_x_DI[row + 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row + 1][col]))  // 下中
							{
								mean_value = mean_value + deviation_x_DI[row + 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row + 1][col + 1]))  // 下右
							{
								mean_value = mean_value + deviation_x_DI[row + 1][col + 1];
								mean_counter++;
							}

							deviation_x_DI[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

						}


					}  // x方向结束



					// 判断y方向
					if (_isnan(deviation_y_DI[row][col]))
					{

						// 排列方式
						//  x x x
						//  x o x
						//  x x x

						if (_isnan(deviation_y_DI[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
							_isnan(deviation_y_DI[row - 1][col]) &&
							_isnan(deviation_y_DI[row - 1][col + 1]) &&
							_isnan(deviation_y_DI[row][col - 1]) &&
							_isnan(deviation_y_DI[row][col + 1]) &&
							_isnan(deviation_y_DI[row + 1][col - 1]) &&
							_isnan(deviation_y_DI[row + 1][col]) &&
							_isnan(deviation_y_DI[row + 1][col + 1]))
						{

							deviation_y_DI[row][col] = 0;
						} // 强制置零结束
						else
						{
							// 排列方式
							//  x x x
							//  x o x
							//  x x x

							int mean_counter = 0;  // 有效值个数
							float mean_value = 0;  // 有效值的和

							if (!_isnan(deviation_y_DI[row - 1][col - 1]))  // 上左
							{
								mean_value = mean_value + deviation_y_DI[row - 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row - 1][col])) // 上中
							{
								mean_value = mean_value + deviation_y_DI[row - 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row - 1][col + 1])) // 上右
							{
								mean_value = mean_value + deviation_y_DI[row - 1][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row][col - 1])) // 中左
							{
								mean_value = mean_value + deviation_y_DI[row][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row][col + 1])) // 中右
							{
								mean_value = mean_value + deviation_y_DI[row][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row + 1][col - 1])) // 下左
							{
								mean_value = mean_value + deviation_y_DI[row + 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row + 1][col]))  // 下中
							{
								mean_value = mean_value + deviation_y_DI[row + 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row + 1][col + 1]))  // 下右
							{
								mean_value = mean_value + deviation_y_DI[row + 1][col + 1];
								mean_counter++;
							}

							deviation_y_DI[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

						}  // 对中心无效值插值结束

					} // y方向结束

				}
			}  // 无效值遍历结束

#pragma endregion 去除脱靶量中的无效值




#pragma region 显示子孔径图像

			if (subApertureImageSwitch->GetCheck() == 1)  // 显示WFS的实时图像
			{

				// 将图像刷入内存
				WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
				// 将图像由一维转为二维，下面的转换经过验证是正确的
				for (int row = 0; row < 480; ++row)
				{
					for (int col = 0; col < 480; ++col)
					{
						image2DBuf[row][col] = imageBuf[480 * row + col];
					}
				}
				//----------------------------------------------------------//
				////## 监测通道
				//(pW->m_Edit_Sta_Watch).Format(_T("%u"), sizeof(image2DBuf));
				//pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);
				//----------------------------------------------------------//
				// 之前使用cvCreateImage配合cvReleaseImage使用，总是内存泄露
				// 现在cvCreateImageHeader与cvReleaseImageHeader成对使用，解决了内存泄露
				m_img = cvCreateImageHeader(cvSize(480, 480), 8, 1);
				cvSetData(m_img, image2DBuf, 480); // 这一句申请了内存，应该是通过cvReleaseImageHeader释放的


				// 用于在TAB控件上子孔径标签页上的对话框上的pic控件显示子孔径的实时图像
				// ptr_SubApertureImageDlg是pW的成员
				pW->ptr_SubApertureImageDlg->ShowSubApertuerImageFrame();

				// 设置标志
				if (CMOSImageFlag == FALSE)
					CMOSImageFlag = TRUE;

			}
			else  // 显示没有图像
			{
				if (CMOSImageFlag == TRUE)
				{
					pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
				}
				CMOSImageFlag = FALSE;  // 设置标志
			}


#pragma endregion 显示子孔径图像


			// 直接积分法重建波前
			WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront_DI);
			
			
			//// 记录波前信息
			//std::vector<std::vector<double>>  wavefront_DI_vector;
			//wavefront_DI_vector.resize(29);
			//for (int index = 0; index < 29;++index)
			//{
			//	wavefront_DI_vector[index].resize(29);
			//}
			//for (int row = 0; row < 29;++row)
			//{
			//	for (int col = 0; col < 29;++col)
			//	{
			//		wavefront_DI_vector[row][col] = wavefront_DI[row][col];
			//	}
			//}

			//std::string fileFullPath, filenamePrefix, finenameSuffix;
			//std::string statusCString;
			//std::string recordwave;

			//filenamePrefix = "D:\\externLib\\AOS\\Output\\";
			//finenameSuffix = ".txt";

			//IntToString(recordwave, recordwave_counter);
			//++recordwave_counter;

			//fileFullPath = filenamePrefix + "recordwave_" + recordwave + finenameSuffix;
			//write_2d_File(fileFullPath, wavefront_DI_vector);




			// 根据直接积分法得到的波前计算波前统计参数
			WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min_ACEMETHOD, &wavefront_max_ACEMETHOD,
				&wavefront_diff_ACEMETHOD, &wavefront_mean_ACEMETHOD, &wavefront_rms_ACEMETHOD, &wavefront_weighted_rms_ACEMETHOD);
			pW->Show_PVRMS(wavefront_diff_ACEMETHOD, wavefront_rms_ACEMETHOD);


			// 将测得的实时波前脱靶量重排为一维向量
			for (int subapture_counter = 0; subapture_counter < eff_picked.size(); ++subapture_counter)
			{

				row_effsub = eff_picked[subapture_counter][0] - 1;
				col_effsub = eff_picked[subapture_counter][1] - 1;
				// 将脱靶量的单位从pixel转为nm，一个像素大小9.9um
				lsqy[2 * subapture_counter] = deviation_x_DI[row_effsub][col_effsub];  // 先压入X方向
				lsqy[2 * subapture_counter + 1] = deviation_y_DI[row_effsub][col_effsub];  // 再压入y方向

			}	
			// 记录重排之后的数据
			//write_1d_File("D:\\externLib\\AOS\\Output\\DEBUG_REARRANGE_deviation_x.txt", lsqy);


			// 计算各个驱动单元的执行量
			std::vector <int>::size_type row_num;  // 行数
			std::vector <int>::size_type col_num;  // 列数
			row_num = lsqA.size();
			col_num = lsqA[0].size();
			for (int row = 0; row < row_num; row++)
			{
				sum_temp = 0;
				for (int col = 0; col < col_num; col++)
				{
					sum_temp = sum_temp + lsqA[row][col] * lsqy[col];
				}

				zernikeMatrix_recon_array_ACEMETHOD[row] = sum_temp * impulse_stroke;  // 得到的单位是nm
			}

			// 驱动变形镜
			P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
			aoSystemData->dDMDesired = zernikeMatrix_recon_array_ACEMETHOD;
			int status = P_DM_SetSpatialFrame();


			// 选择是否显示执行量(直接斜率法)
			float temp;
			if (showExecuDist->GetCheck() == 1)
			{

				for (int k_index = 0; k_index < 144; ++k_index)
				{
					temp = zernikeMatrix_recon_array_ACEMETHOD[k_index];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
			}

			wait4U(1500);  // 等待一定时间

		}  // 闭环结束

	} // if结束，直接斜率法结束



#pragma endregion 直接斜率
	  


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 退出线程
	return 0;

} // 线程结束

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 预计算线程函数
UINT ThreadFunc_PreCalculation(LPVOID pParam)
{

#pragma region 局部变量

	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	// 动态保存文件需要的std::string变量
	std::string fileFullPath, filenamePrefix, finenameSuffix;
	std::string indexCString, XdeviCString, YdeviCString;
	std::string statusCString;

	XdeviCString = "XDevi";
	YdeviCString = "YDevi";
	filenamePrefix = "D:\\externLib\\AOS\\Output\\PreCalc\\in\\";
	finenameSuffix = ".txt";

	// 用于在状态栏显示
	CString indexCString_forreal;


	// 将144个DM驱动器单元依次发给变形镜，WFS获得响应的波前
	double DM_PreCalc[144];  // 必须是double，否则aoSystemData->dDMDesired = DM_PreCalc;不好强转
	float  deviation_x_PreCalc[40][50];  // x方向脱靶量，单位像素
	float  deviation_y_PreCalc[40][50];  // y方向脱靶量，单位像素
	std::vector<std::vector<double>> deviation_x_nm_PreCalc;  // x方向斜坡数据，单位nm
	std::vector<std::vector<double>> deviation_y_nm_PreCalc;   // y方向斜坡数据，单位nm
	// 为容器分配内存空间
	deviation_x_nm_PreCalc.resize(29);
	for (int index = 0; index < 29;++index)
	{
		deviation_x_nm_PreCalc[index].resize(29);
	}
	deviation_y_nm_PreCalc.resize(29);
	for (int index = 0; index < 29; ++index)
	{
		deviation_y_nm_PreCalc[index].resize(29);
	}


	// 重建波前用到的变量
	float   wavefront_Impulse[40][50];
	std::vector<std::vector<double>> wavefront_Impulse_Vector; // 用于保存数据的容器
	// 为容器分配内存空间
	wavefront_Impulse_Vector.resize(29); // 分配行
	for (int index = 0; index < 29; ++index)
	{
		wavefront_Impulse_Vector[index].resize(29);  // 分配列
	}

	// zernike重建需要的变量
	ViInt32		zernike_order_Impulse = 4;
	float		zernike_um_Impulse[16];  // 0为额外数据，1~15为zernike系数
	float		zernike_orders_rms_um_Impulse[11];
	double		roc_mm_Impulse;

	// WFS像素大小4.65um，用于将单位从pixel转换为nm
	float  unitCoeff = 1;


	// zernike重建时要计算基底
	zernike(0, 0, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_01, pupil, coordMoveX, coordMoveY);
	zernike(1, -1, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_02, pupil, coordMoveX, coordMoveY);
	zernike(1, 1, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_03, pupil, coordMoveX, coordMoveY);
	zernike(2, -2, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_04, pupil, coordMoveX, coordMoveY);
	zernike(2, 0, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_05, pupil, coordMoveX, coordMoveY);
	zernike(2, 2, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_06, pupil, coordMoveX, coordMoveY);
	zernike(3, -3, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_07, pupil, coordMoveX, coordMoveY);
	zernike(3, -1, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_08, pupil, coordMoveX, coordMoveY);
	zernike(3, 1, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_09, pupil, coordMoveX, coordMoveY);
	zernike(3, 3, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_10, pupil, coordMoveX, coordMoveY);
	zernike(4, -4, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_11, pupil, coordMoveX, coordMoveY);
	zernike(4, -2, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_12, pupil, coordMoveX, coordMoveY);
	zernike(4, 0, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_13, pupil, coordMoveX, coordMoveY);
	zernike(4, 2, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_14, pupil, coordMoveX, coordMoveY);
	zernike(4, 4, 29, instr_setup.pupil_dia_x_mm, zernikeMatrix_15, pupil, coordMoveX, coordMoveY);

	// 用于直接斜率法预计算中将波前信息写入文件中
	std::vector<std::vector<double>> zernikeMatrix_recon_ACEMETHOD_PreCalc;
	zernikeMatrix_recon_ACEMETHOD_PreCalc.resize(29);  // 给变量重新分配内存空间
	for (int index = 0; index < 29; ++index)
	{
		zernikeMatrix_recon_ACEMETHOD_PreCalc[index].resize(29);
	}

#pragma endregion 局部变量



	for (int index = 0; index < 144; ++index)
	{
		// int类型转换为std::string类型，用于保存文件使用
		IntToString(indexCString, index);


		// 依次更改变形镜
		for (int i = 0; i < 144; ++i)
		{
			DM_PreCalc[i] = bias_initial;
		}
		DM_PreCalc[index] = bias_initial + impulse_stroke;

		// 驱动DM
		P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
		aoSystemData->dDMDesired = DM_PreCalc;
		int status = P_DM_SetSpatialFrame();

		// 普通模式获取质心位置
		WFS_TakeSpotfieldImage(instr.handle);
		// 计算质心位置
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
		// 计算脱靶量
		WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
		// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
		WFS_GetSpotDeviations(instr.handle, *deviation_x_PreCalc, *deviation_y_PreCalc);


#pragma region 去掉脱靶量中的无效值



		// 脱靶量为29x29，边界采用置零

		deviation_x_PreCalc[0][0] = 0; deviation_x_PreCalc[0][28] = 0; deviation_x_PreCalc[28][0] = 0; deviation_x_PreCalc[28][28] = 0;  // 四个角置零
		deviation_y_PreCalc[0][0] = 0; deviation_y_PreCalc[0][28] = 0; deviation_y_PreCalc[28][0] = 0; deviation_y_PreCalc[28][28] = 0;  // 四个角置零

		// 最外面四条边置零
		for (int col = 1; col < 28; ++col)  // 第0行
		{
			deviation_x_PreCalc[0][col] = 0;
			deviation_y_PreCalc[0][col] = 0;
		}
		for (int col = 1; col < 28; ++col)  // 第28行
		{
			deviation_x_PreCalc[28][col] = 0;
			deviation_y_PreCalc[28][col] = 0;
		}
		for (int row = 1; row < 28; ++row)  // 第0列
		{
			deviation_x_PreCalc[row][0] = 0;
			deviation_y_PreCalc[row][0] = 0;
		}
		for (int row = 1; row < 28; ++row)  // 第28列
		{
			deviation_x_PreCalc[row][28] = 0;
			deviation_y_PreCalc[row][28] = 0;
		}


		// 对中间的数据进行平均插值
		for (int row = 1; row < 28; ++row)  // 空出最上下两行
		{
			for (int col = 1; col < 28; ++col) // 空出最左右两列
			{

				// 判断x方向
				if (_isnan(deviation_x_PreCalc[row][col]))
				{
					// 排列方式
					//  x x x
					//  x o x
					//  x x x

					if (_isnan(deviation_x_PreCalc[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
						_isnan(deviation_x_PreCalc[row - 1][col]) &&
						_isnan(deviation_x_PreCalc[row - 1][col + 1]) &&
						_isnan(deviation_x_PreCalc[row][col - 1]) &&
						_isnan(deviation_x_PreCalc[row][col + 1]) &&
						_isnan(deviation_x_PreCalc[row + 1][col - 1]) &&
						_isnan(deviation_x_PreCalc[row + 1][col]) &&
						_isnan(deviation_x_PreCalc[row + 1][col + 1]))
					{
						deviation_x_PreCalc[row][col] = 0;
					}
					else
					{
						// 排列方式
						//  x x x
						//  x o x
						//  x x x

						int mean_counter = 0;  // 有效值个数
						float mean_value = 0;  // 有效值的和

						if (!_isnan(deviation_x_PreCalc[row - 1][col - 1]))  // 上左
						{
							mean_value = mean_value + deviation_x_PreCalc[row - 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row - 1][col])) // 上中
						{
							mean_value = mean_value + deviation_x_PreCalc[row - 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row - 1][col + 1])) // 上右
						{
							mean_value = mean_value + deviation_x_PreCalc[row - 1][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row][col - 1])) // 中左
						{
							mean_value = mean_value + deviation_x_PreCalc[row][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row][col + 1])) // 中右
						{
							mean_value = mean_value + deviation_x_PreCalc[row][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row + 1][col - 1])) // 下左
						{
							mean_value = mean_value + deviation_x_PreCalc[row + 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row + 1][col]))  // 下中
						{
							mean_value = mean_value + deviation_x_PreCalc[row + 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row + 1][col + 1]))  // 下右
						{
							mean_value = mean_value + deviation_x_PreCalc[row + 1][col + 1];
							mean_counter++;
						}

						deviation_x_PreCalc[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

					}


				}  // x方向结束



				// 判断y方向
				if (_isnan(deviation_y_PreCalc[row][col]))
				{

					// 排列方式
					//  x x x
					//  x o x
					//  x x x

					if (_isnan(deviation_y_PreCalc[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
						_isnan(deviation_y_PreCalc[row - 1][col]) &&
						_isnan(deviation_y_PreCalc[row - 1][col + 1]) &&
						_isnan(deviation_y_PreCalc[row][col - 1]) &&
						_isnan(deviation_y_PreCalc[row][col + 1]) &&
						_isnan(deviation_y_PreCalc[row + 1][col - 1]) &&
						_isnan(deviation_y_PreCalc[row + 1][col]) &&
						_isnan(deviation_y_PreCalc[row + 1][col + 1]))
					{

						deviation_y_PreCalc[row][col] = 0;
					} // 强制置零结束
					else
					{
						// 排列方式
						//  x x x
						//  x o x
						//  x x x

						int mean_counter = 0;  // 有效值个数
						float mean_value = 0;  // 有效值的和

						if (!_isnan(deviation_y_PreCalc[row - 1][col - 1]))  // 上左
						{
							mean_value = mean_value + deviation_y_PreCalc[row - 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row - 1][col])) // 上中
						{
							mean_value = mean_value + deviation_y_PreCalc[row - 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row - 1][col + 1])) // 上右
						{
							mean_value = mean_value + deviation_y_PreCalc[row - 1][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row][col - 1])) // 中左
						{
							mean_value = mean_value + deviation_y_PreCalc[row][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row][col + 1])) // 中右
						{
							mean_value = mean_value + deviation_y_PreCalc[row][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row + 1][col - 1])) // 下左
						{
							mean_value = mean_value + deviation_y_PreCalc[row + 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row + 1][col]))  // 下中
						{
							mean_value = mean_value + deviation_y_PreCalc[row + 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row + 1][col + 1]))  // 下右
						{
							mean_value = mean_value + deviation_y_PreCalc[row + 1][col + 1];
							mean_counter++;
						}

						deviation_y_PreCalc[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

					}  // 对中心无效值插值结束

				} // y方向结束

			}
		}  // 无效值遍历结束


#pragma endregion 去掉脱靶量中的无效值


		// 更换数据类型，可用于写入文件
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{
				deviation_x_nm_PreCalc[row][col] = deviation_x_PreCalc[row][col] * unitCoeff;
				deviation_y_nm_PreCalc[row][col] = deviation_y_PreCalc[row][col] * unitCoeff;
			}
		}


#pragma region 直接积分法重建Impulse波前

		// 通过脱靶量，由直接积分法，获得重建波前
		WFS_CalcWavefront(instr.handle, 0, 0, *wavefront_Impulse);


#pragma region 去掉直接积分法重建波前的无效值

		// 脱靶量为29x29，边界采用置零
		wavefront_Impulse[0][0] = 0; wavefront_Impulse[0][28] = 0; wavefront_Impulse[28][0] = 0; wavefront_Impulse[28][28] = 0;  // 四个角置零

		// 最外面四条边置零
		for (int col = 1; col < 28; ++col)  // 第0行
		{
			wavefront_Impulse[0][col] = 0;
		}
		for (int col = 1; col < 28; ++col)  // 第28行
		{
			wavefront_Impulse[28][col] = 0;
		}
		for (int row = 1; row < 28; ++row)  // 第0列
		{
			wavefront_Impulse[row][0] = 0;
		}
		for (int row = 1; row < 28; ++row)  // 第28列
		{
			wavefront_Impulse[row][28] = 0;
		}


		// 对中间的数据进行平均插值
		for (int row = 1; row < 28; ++row)  // 空出最上下两行
		{
			for (int col = 1; col < 28; ++col) // 空出最左右两列
			{

				if (_isnan(wavefront_Impulse[row][col]))
				{
					// 排列方式
					//  x x x
					//  x o x
					//  x x x

					if (_isnan(wavefront_Impulse[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
						_isnan(wavefront_Impulse[row - 1][col]) &&
						_isnan(wavefront_Impulse[row - 1][col + 1]) &&
						_isnan(wavefront_Impulse[row][col - 1]) &&
						_isnan(wavefront_Impulse[row][col + 1]) &&
						_isnan(wavefront_Impulse[row + 1][col - 1]) &&
						_isnan(wavefront_Impulse[row + 1][col]) &&
						_isnan(wavefront_Impulse[row + 1][col + 1]))
					{
						wavefront_Impulse[row][col] = 0;
					}
					else
					{
						// 排列方式
						//  x x x
						//  x o x
						//  x x x

						int mean_counter = 0;  // 有效值个数
						float mean_value = 0;  // 有效值的和

						if (!_isnan(wavefront_Impulse[row - 1][col - 1]))  // 上左
						{
							mean_value = mean_value + wavefront_Impulse[row - 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row - 1][col])) // 上中
						{
							mean_value = mean_value + wavefront_Impulse[row - 1][col];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row - 1][col + 1])) // 上右
						{
							mean_value = mean_value + wavefront_Impulse[row - 1][col + 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row][col - 1])) // 中左
						{
							mean_value = mean_value + wavefront_Impulse[row][col - 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row][col + 1])) // 中右
						{
							mean_value = mean_value + wavefront_Impulse[row][col + 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row + 1][col - 1])) // 下左
						{
							mean_value = mean_value + wavefront_Impulse[row + 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row + 1][col]))  // 下中
						{
							mean_value = mean_value + wavefront_Impulse[row + 1][col];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row + 1][col + 1]))  // 下右
						{
							mean_value = mean_value + wavefront_Impulse[row + 1][col + 1];
							mean_counter++;
						}

						wavefront_Impulse[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

					}


				}

			}
		}  // 无效值遍历结束

#pragma endregion 去掉直接积分法重建波前的无效值


		// 将数组赋值给容器
		for (int row = 0; row < 29;++row)
		{
			for (int col = 0; col < 29;++col)
			{

				wavefront_Impulse_Vector[row][col] = wavefront_Impulse[row][col];

			}
		}
		fileFullPath = filenamePrefix + "ImpulseWavefrontDirect" + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, wavefront_Impulse_Vector);  // 记录直接积分法重建的波前

#pragma endregion 直接积分法重建Impulse波前


#pragma region zernike拟合法重建Impulse波前

		// 通过脱靶量，由Zernike拟合法，获得重建波前
		WFS_ZernikeLsf(instr.handle, &zernike_order_Impulse, zernike_um_Impulse, zernike_orders_rms_um_Impulse, &roc_mm_Impulse);

		// 根据zernike系数重建波前
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{
				zernikeMatrix_recon_ACEMETHOD_PreCalc[row][col] =
					zernike_um_Impulse[1] * zernikeMatrix_01[row][col] +
					zernike_um_Impulse[2] * zernikeMatrix_02[row][col] +
					zernike_um_Impulse[3] * zernikeMatrix_03[row][col] +
					zernike_um_Impulse[4] * zernikeMatrix_04[row][col] +
					zernike_um_Impulse[5] * zernikeMatrix_05[row][col] +
					zernike_um_Impulse[6] * zernikeMatrix_06[row][col] +
					zernike_um_Impulse[7] * zernikeMatrix_07[row][col] +
					zernike_um_Impulse[8] * zernikeMatrix_08[row][col] +
					zernike_um_Impulse[9] * zernikeMatrix_09[row][col] +
					zernike_um_Impulse[10] * zernikeMatrix_10[row][col] +
					zernike_um_Impulse[11] * zernikeMatrix_11[row][col] +
					zernike_um_Impulse[12] * zernikeMatrix_12[row][col] +
					zernike_um_Impulse[13] * zernikeMatrix_13[row][col] +
					zernike_um_Impulse[14] * zernikeMatrix_14[row][col] +
					zernike_um_Impulse[15] * zernikeMatrix_15[row][col];
			}

		}

		fileFullPath = filenamePrefix + "ImpulseWavefrontZernike" + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, zernikeMatrix_recon_ACEMETHOD_PreCalc);  // 记录zernike拟合法重建的波前


#pragma endregion zernike拟合法重建Impulse波前


		wait4U(300); // 延迟300ms


		// 将x脱靶量写入文件
		fileFullPath = filenamePrefix + XdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_x_nm_PreCalc);
		// 将y脱靶量写入文件
		fileFullPath = filenamePrefix + YdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_y_nm_PreCalc);


		indexCString_forreal.Format(_T("%d"), index);
		str_showerror = _T("预处理数据：  ") + indexCString_forreal;
		pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

	}  // 遍历完毕所有变形镜单元的脉冲函数


	str_showerror = _T("预处理完毕");
	pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);


	return 0;

}  // 预处理线程函数结束

////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region

// C风格的方式记录矩阵和向量

// 将质心位置写入文件
int WFS_WriteSpotCentroids()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_SpotCentroids_X.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_SpotCentroids_X文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", centroid_x[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);


	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_SpotCentroids_Y.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_SpotCentroids_Y文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}
	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", centroid_y[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;
}




int WFS_WriteCalcReconstrDeviations()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_CalcReconstrDeviations.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_CalcReconstrDeviations文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	fprintf(fp, "fitErrMean：  %lf \n", fitErrMean);
	fprintf(fp, "fitErrStdev： %lf \n", fitErrStdev);

	fclose(fp);

	return 0;
}



// 将当前的Zernike矩阵写入文件
int WFS_WriteZernikeMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_WriteZernikeMatrix.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_WriteZernikeMatrix文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", zerWave_Matrix29[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;

}


// 将wavefront与zerWave_Matrix29矩阵的减法结果写入文件
int WFS_WriteWavefrontZernikeError()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_WavefrontZernikeError.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_WavefrontZernikeError文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", zerPolyError29[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;

}



// 用于静态校正波前时，校验matlab计算的zernike拟合矩阵
int DM_WriteCheckZernikeMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\conDM\\DM_CheckZernikeMatrix.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开DM_CheckZernikeMatrix文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			fprintf(fp, "%f", zerWave_Matrix[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;

}


// 用于将操作后的矩阵写入文件
int DM_WriteTransposeMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\conDM\\DM_TransposeZernikeMatrix.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开DM_TransposeZernikeMatrix文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			fprintf(fp, "%f", zerWave_Matrix_Temp[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;

}


// 用于将一维的数组写入文件，即写入变形镜的一维数组
int DM_Write1DMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\DM_1DArray.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开DM_1DArray文件 ！"), _T("Writing Status"), MB_OK);
		return -1;
	}

	for (int i = 0; i < MAX_ZERNIKE_MODES + 1; ++i)
	{
		fprintf(fp, "%f", DM_Stroke_1D[i]);  // 144个元素
		fputc('\n', fp);
	}
	fclose(fp);


	return 0;
}

#pragma endregion 




#pragma region mapping   

// 这里分为普通版本和vector版本

// 矩阵转置
int MatrixTranspose(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12网格
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[j][i] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29网格
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[j][i] = matrixIn[i][j];
	}

	return 0;
}

// 矩阵左右翻转
int MatrixFlipLeftRight(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12网格
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[i][11 - j] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29网格
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[i][28 - j] = matrixIn[i][j];
	}

	return 0;
}

// 矩阵上下翻转
int MatrixFlipUpDown(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12网格
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[11 - i][j] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29网格
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[28 - i][j] = matrixIn[i][j];
	}

	return 0;
}

// 矩阵顺时针旋转90度=上下翻转后转置
int MatrixRotate90(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12网格
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[j][11 - i] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29网格
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[j][28 - i] = matrixIn[i][j];
	}

	return 0;
}

// 矩阵顺时针旋转180度=左右翻转后上下翻转
int MatrixRotate180(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12网格
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[11 - i][11 - j] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29网格
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[28 - i][28 - j] = matrixIn[i][j];
	}

	return 0;
}

// 矩阵顺时针旋转270度=作于翻转后再转置
int MatrixRotate270(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12网格
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[11 - j][i] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29网格
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[28 - j][i] = matrixIn[i][j];
	}

	return 0;
}

// 下面是vector版本的矩阵旋转
int MatrixRotate90_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[j][11 - i] = matrixIn[i][j];

	return 0;

}

int MatrixRotate180_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[11 - i][11 - j] = matrixIn[i][j];

	return 0;
}

int MatrixRotate270_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[11 - j][i] = matrixIn[i][j];

	return 0;
}

int MatrixRotate0_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[i][j] = matrixIn[i][j];

	return 0;
}

int MatrixFlipUpDown_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	// 上下翻转
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[11 - i][j] = matrixIn[i][j];

	return 0;
}

int MatrixFlipLeftRight_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	// 左右翻转
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[i][11 - j] = matrixIn[i][j];

	return 0;
}



#pragma endregion mapping


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 以下是新版的写入文件的函数，主要特征是使用了std::vector容器，希望能够逐步代替之前的C风格的全局函数

// 写入一维数据
// 适用于所有算法
int write_1d_File(const std::string& filename, std::vector<double>& array_1d)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out);
	std::vector<double>::iterator iter;


	if (!file)
	{
		std::cerr << "无法打开要写入的文件！\"" << filename << "\"" << std::endl;
		exit(EXIT_FAILURE);
	}

	for (iter = array_1d.begin(); iter != array_1d.end(); ++iter)
	{
		file << *iter << std::endl;
	}

	return 1;
}


// 写入二维数据
// 适用于所有算法
int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out);

	std::vector<std::vector<double>>::iterator iter_row;	
	std::vector<double>::iterator iter_col;			


	if (!file)
	{
		std::cerr << "无法打开要写入的文件！\"" << filename << "\"" << std::endl;
		exit(EXIT_FAILURE);
	}

	for (iter_row = array_2d.begin(); iter_row < array_2d.end(); ++iter_row)
	{
		for (iter_col = (*iter_row).begin(); iter_col < (*iter_row).end(); ++iter_col)
		{
			file << *iter_col << "   ";
		}
		file << std::endl;
	}

	return 1;
}


// 适用于所有算法
MyMat_double inputMatrix(const std::string& filename)
{
	// 要打开的文件
	std::ifstream inputMatrixfile(filename);
	// 返回的二维vector矩阵
	MyMat_double inputMatrixMatrix;

	std::istringstream istr;
	std::string str;  // 应该是按行读入的数据
	std::vector<double> tmpvec;

	// 读入数据
	while (getline(inputMatrixfile, str))
	{
		istr.str(str);
		double tmp;
		while (istr >> tmp)
		{
			tmpvec.push_back(tmp);
		}
		inputMatrixMatrix.push_back(tmpvec);
		tmpvec.clear();
		istr.clear();
	}
	inputMatrixfile.close();


	return inputMatrixMatrix;
}


// 适用于所有算法
int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col)
{
	std::vector<double> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// 重载版本
// 适用于所有算法
int init_2dVector(std::vector<std::vector<int>>&vectordata, const int row, const int col)
{
	std::vector<int> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// 释放二维vector数据
// 适用于所有算法
int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// 重载版本
// 适用于所有算法
int release_2dVector(std::vector<std::vector<int>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// 一维vector初始化
// 适用于所有算法
int init_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.push_back(0);

	return 0;

}

// 释放一维vector数据
// 适用于所有算法
int release_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;

}




// 用于等待一定时间的函数，输入时间单位ms
// 适用于所有算法
int wait4U(int time_milliseconds) 
{

	//新计时器开始
	LARGE_INTEGER nStartCounter_dmwait;
	LARGE_INTEGER nFrequency_dmwait;
	double nTime_dmwait = 0; // 记录时间

	::QueryPerformanceCounter(&nStartCounter_dmwait);
	::QueryPerformanceFrequency(&nFrequency_dmwait);


	do
	{
		LARGE_INTEGER nStopCounter_dmwait;
		::QueryPerformanceCounter(&nStopCounter_dmwait);
		nTime_dmwait = 1000 * ((double)nStopCounter_dmwait.QuadPart - (double)nStartCounter_dmwait.QuadPart) / (double)nFrequency_dmwait.QuadPart;    // 单位 ms
	} while (nTime_dmwait < time_milliseconds);


	return 0;  // 成功返回0
}



// 用于驱动变形镜的函数，单位是nm
// 适用于所有算法
int DriveDeformMirror_nm(double(&executeStroke)[140])
{

	// 将执行量发送给变形镜，驱动其运动
	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = executeStroke;
	P_DM_SetSpatialFrame();   // 按照nm单位驱动变形镜，但是这个驱动行程的分辨率是多少？


	return 0;  // 成功返回0

}


// 用于探测波前的脱靶量(仅适用于普通模式)
// 适用于所有算法
int Detect_Wavefront2Deviation_Normal()
{

	// 普通模式获取质心位置
	WFS_TakeSpotfieldImage(instr.handle);

	// 计算质心位置
	WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);

	// 计算脱靶量
	WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);

	// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
	WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);


	return 0;

}

// 用于直接处理脱靶量，保证处理后的数据没有无效值，适用于普通模式与高速模式，输入可能包含无效值的脱靶量，输出全部有效的脱靶量
// 用于所有算法
int MeanInterpolation_KillNAN()
{

	// 脱靶量为29x29，边界采用置零

	deviation_x[0][0] = 0; deviation_x[0][28] = 0; deviation_x[28][0] = 0; deviation_x[28][28] = 0;  // 四个角置零
	deviation_y[0][0] = 0; deviation_y[0][28] = 0; deviation_y[28][0] = 0; deviation_y[28][28] = 0;  // 四个角置零

	// 最外面四条边置零
	for (int col = 1; col < 28; ++col)  // 第0行
	{
		deviation_x[0][col] = 0;
		deviation_y[0][col] = 0;
	}
	for (int col = 1; col < 28; ++col)  // 第28行
	{
		deviation_x[28][col] = 0;
		deviation_y[28][col] = 0;
	}
	for (int row = 1; row < 28; ++row)  // 第0列
	{
		deviation_x[row][0] = 0;
		deviation_y[row][0] = 0;
	}
	for (int row = 1; row < 28; ++row)  // 第28列
	{
		deviation_x[row][28] = 0;
		deviation_y[row][28] = 0;
	}


	// 对中间的数据进行平均插值
	for (int row = 1; row < 28; ++row)  // 空出最上下两行
	{
		for (int col = 1; col < 28; ++col) // 空出最左右两列
		{

			// 判断x方向
			if (_isnan(deviation_x[row][col]))
			{
				// 排列方式
				//  x x x
				//  x o x
				//  x x x

				if (_isnan(deviation_x[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
					_isnan(deviation_x[row - 1][col]) &&
					_isnan(deviation_x[row - 1][col + 1]) &&
					_isnan(deviation_x[row][col - 1]) &&
					_isnan(deviation_x[row][col + 1]) &&
					_isnan(deviation_x[row + 1][col - 1]) &&
					_isnan(deviation_x[row + 1][col]) &&
					_isnan(deviation_x[row + 1][col + 1]))
				{
					deviation_x[row][col] = 0;
				}
				else
				{
					// 排列方式
					//  x x x
					//  x o x
					//  x x x

					int mean_counter = 0;  // 有效值个数
					float mean_value = 0;  // 有效值的和

					if (!_isnan(deviation_x[row - 1][col - 1]))  // 上左
					{
						mean_value = mean_value + deviation_x[row - 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row - 1][col])) // 上中
					{
						mean_value = mean_value + deviation_x[row - 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row - 1][col + 1])) // 上右
					{
						mean_value = mean_value + deviation_x[row - 1][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row][col - 1])) // 中左
					{
						mean_value = mean_value + deviation_x[row][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row][col + 1])) // 中右
					{
						mean_value = mean_value + deviation_x[row][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row + 1][col - 1])) // 下左
					{
						mean_value = mean_value + deviation_x[row + 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row + 1][col]))  // 下中
					{
						mean_value = mean_value + deviation_x[row + 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row + 1][col + 1]))  // 下右
					{
						mean_value = mean_value + deviation_x[row + 1][col + 1];
						mean_counter++;
					}

					deviation_x[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

				}


			}  // x方向结束



			// 判断y方向
			if (_isnan(deviation_y[row][col]))
			{

				// 排列方式
				//  x x x
				//  x o x
				//  x x x

				if (_isnan(deviation_y[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
					_isnan(deviation_y[row - 1][col]) &&
					_isnan(deviation_y[row - 1][col + 1]) &&
					_isnan(deviation_y[row][col - 1]) &&
					_isnan(deviation_y[row][col + 1]) &&
					_isnan(deviation_y[row + 1][col - 1]) &&
					_isnan(deviation_y[row + 1][col]) &&
					_isnan(deviation_y[row + 1][col + 1]))
				{

					deviation_y[row][col] = 0;
				} // 强制置零结束
				else
				{
					// 排列方式
					//  x x x
					//  x o x
					//  x x x

					int mean_counter = 0;  // 有效值个数
					float mean_value = 0;  // 有效值的和

					if (!_isnan(deviation_y[row - 1][col - 1]))  // 上左
					{
						mean_value = mean_value + deviation_y[row - 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row - 1][col])) // 上中
					{
						mean_value = mean_value + deviation_y[row - 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row - 1][col + 1])) // 上右
					{
						mean_value = mean_value + deviation_y[row - 1][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row][col - 1])) // 中左
					{
						mean_value = mean_value + deviation_y[row][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row][col + 1])) // 中右
					{
						mean_value = mean_value + deviation_y[row][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row + 1][col - 1])) // 下左
					{
						mean_value = mean_value + deviation_y[row + 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row + 1][col]))  // 下中
					{
						mean_value = mean_value + deviation_y[row + 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row + 1][col + 1]))  // 下右
					{
						mean_value = mean_value + deviation_y[row + 1][col + 1];
						mean_counter++;
					}

					deviation_y[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值

				}  // 对中心无效值插值结束

			} // y方向结束

		}
	}  // 无效值遍历结束

	return 0;
}


// 计算并返回评价函数，评价函数的计算方式是：x与y方向的脱靶量平方相加，最后开根号得到
// 仅在梯度算法中使用
double CalcMeritFunc_SquareDevi()
{

	double meritTemp = 0;
	for (int row = 0; row < 29; ++row)
	{
		for (int col = 0; col < 29; ++col)
		{

			meritTemp = meritTemp + pow(deviation_x[row][col], 2) + pow(deviation_y[row][col], 2);

		}
	}
	return sqrt(meritTemp);

}




#pragma endregion 全局函数



//----------------------------------------------------    ----------------------------------------------------//






#pragma region 封装为成员函数

// 封装为类的成员函数，显示PV值与RMS以及评价函数
// 仅在梯度算法中使用
int CAOSys_v8Dlg::Show_MeritPVRMS(double merit, double PV, double RMS)
{

	// 显示评价函数值
	m_Edit_ShowMerit.Format(_T("%lf"), merit);
	SetDlgItemTextW(IDC_EDIT_SHOWMERIT, m_Edit_ShowMerit);

	// 显示PV
	m_Edit_Sta_PV.Format(_T("%lf"), PV);
	SetDlgItemTextW(IDC_EDIT_STA_PV, m_Edit_Sta_PV);

	// 显示RMS
	m_Edit_Sta_RMS.Format(_T("%lf"), RMS);
	SetDlgItemTextW(IDC_EDIT_STA_RMS, m_Edit_Sta_RMS);


	return 0;
}


// 定时器，起到延时作用
// 可以用于所有算法
int CAOSys_v8Dlg::Timer_SetTimer(double settimer)
{

	//-----------------------------------------------------
	//计时器开始
	LARGE_INTEGER nStartCounter_wait;
	LARGE_INTEGER nFrequency_wait;
	double nTime_wait = 0; // 记录时间
	::QueryPerformanceCounter(&nStartCounter_wait);
	::QueryPerformanceFrequency(&nFrequency_wait);
	//-----------------------------------------------------

	if (ptr_MiscSettingDlg->m_Check_SubDlg_TimeSetter.GetCheck() == 1)  // 选择是否进行计时
	{

		do
		{

			//-----------------------------------------------------
			// 计时器结束
			LARGE_INTEGER nStopCounter_wait;
			::QueryPerformanceCounter(&nStopCounter_wait);
			nTime_wait = 1000 * ((double)nStopCounter_wait.QuadPart - (double)nStartCounter_wait.QuadPart) / (double)nFrequency_wait.QuadPart;    // 单位 ms
			//显示计时器
			m_Edit_Show_NewTimer.Format(_T("%lf"), nTime_wait);
			SetDlgItemText(IDC_EDIT_SHOW_NEWTIMER, m_Edit_Show_NewTimer);
			//-----------------------------------------------------


		} while (nTime_wait < settimer);


	}
	else
	{
		// 没有定时，不执行
	}


	return 0;
}



// 用于旋转12x12网格的矩阵
// 适用于所有算法
int CAOSys_v8Dlg::rotateMatrix_12vector(int angle, std::vector<std::vector<double>>& origin, std::vector<std::vector<double>>& modified)
{

	// 矩阵旋转功能
	if (90 == angle)  // 顺时针旋转90度，下面都是顺时针
	{
		MatrixRotate90_vector(modified, origin);
	}
	else if (180 == angle)
	{
		MatrixRotate180_vector(modified, origin);
	}
	else if (270 == angle)
	{
		MatrixRotate270_vector(modified, origin);
	}
	else if (1 == angle)   // 上下翻转
	{
		MatrixFlipUpDown_vector(modified, origin);
	}
	else if (2 == angle) // 左右翻转
	{
		MatrixFlipLeftRight_vector(modified, origin);
	}
	else if (3 == angle)  // 上下翻转后左右翻转
	{
		MatrixFlipUpDown_vector(modified, origin);
		MatrixFlipLeftRight_vector(modified, origin);
	}
	else
	{
		// 默认
		MatrixRotate0_vector(modified, origin);
	}


	return 0;
}




int CAOSys_v8Dlg::Show_PVRMS(double PV, double RMS)
{
	// 显示PV
	m_Edit_Sta_PV.Format(_T("%lf"), PV);
	SetDlgItemTextW(IDC_EDIT_STA_PV, m_Edit_Sta_PV);

	// 显示RMS
	m_Edit_Sta_RMS.Format(_T("%lf"), RMS);
	SetDlgItemTextW(IDC_EDIT_STA_RMS, m_Edit_Sta_RMS);

	return 0;
}


#pragma endregion 封装为成员函数
