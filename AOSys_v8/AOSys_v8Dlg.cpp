
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
	DDX_Text(pDX, IDC_EDIT_STA_GRIDTYPE, m_Edit_Sta_GridType);
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
	ON_BN_CLICKED(IDC_BUTTON_PRE_CALC_LOAD, &CAOSys_v8Dlg::OnBnClickedButtonPreCalcLoad)
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
	m_tabDisplay.InsertItem(1, _T("波前实时重建图像"));
	m_tabDisplay.InsertItem(2, _T("变形镜控制矩阵"));
	m_tabDisplay.InsertItem(3, _T("脱靶量"));
	m_tabDisplay.InsertItem(4, _T("其他设置"));



	// 给每个对话框初始化指针，这个指针如何释放？这是一个全局的指针吧？
	ptr_SubApertureImageDlg = new CSubApertureDlg();
	ptr_ReconWavefrontDlg = new CReconWavefrontDlg();
	ptr_DeformMirrorDlg = new CDeformMirrorDlg();
	ptr_DeviationXDlg = new CDeviationXDlg();
	ptr_MiscSettingDlg = new CMiscSettingDlg();



	// 在响应的TAB控件标签页上创建对话框
	ptr_SubApertureImageDlg->Create(IDD_DIALOG_SUBAPERTURE, &m_tabDisplay);
	ptr_ReconWavefrontDlg->Create(IDD_DIALOG_RECONWAVEFRONT, &m_tabDisplay);
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


	// 根据调整好的tabRect放置m_SubApertureDlg子对话框，并设置为显示   
	ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// 根据调整好的tabRect放置m_ReconWavefontDlg子对话框，并设置为隐藏   
	ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为隐藏 
	ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	// 同理
	ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	// 同理
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
	m_Combo_ChooseAlgo.SetCurSel(2);  // 默认算法选择第一项



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
AOSystemData		aoSystemData_LOCAL;


//     WFS_32
int               err;
int               selection;

double            expos_act, master_gain_act;
ViInt32		      blackLevelOffsetAct;  // 初始值设置为50
ViInt32			  NoiseCutAct;
ViReal64          beam_centroid_x = 0;
ViReal64		  beam_centroid_y = 0;
double            beam_diameter_x = 0;
double			  beam_diameter_y = 0;

// 质心位置
float             centroid_x[40][50];
float             centroid_y[40][50];

// 参考位置
float             reference_x[40][50];
float             reference_y[40][50];


// 脱靶量的位置
float             deviation_x[40][50];
float             deviation_y[40][50];
float			  rememberDeviationX[40][50][100]; // 用于记录每个时刻脱靶量的值
float			  rememberDeviationY[40][50][100]; // 用于记录每个时刻脱靶量的值



float             wavefront[40][50];
float             Wavefront_Copy[29][29];

float             zernike_um[MAX_ZERNIKE_MODES + 1];    // 索引号从1到MAX_ZERNIKE_MODES，这个变量有对应的局部变量，vector版本vector_zernike_um
float             zernike_orders_rms_um[MAX_ZERNIKE_ORDERS + 1]; // index runs from 1 - MAX_ZERNIKE_MODES
double            roc_mm;

int               zernike_order;

double            wavefront_min, wavefront_max, wavefront_diff, wavefront_mean, wavefront_rms, wavefront_weighted_rms;
ViChar            resourceName[256];
FILE              *fp;
//int               key;


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
int				Mapping = 0;

int				gridIndex = 0;  // 0是12x12的网格，1是29x29的网格



#pragma region 波前计算交互数据


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

// zernike拟合后的矩阵，即拟合波前，这个矩阵在12x12网格下要变为一维数据并去掉相应元素后发给DM
std::vector<std::vector<double>> zernikeMatrix_recon;
std::vector<std::vector<double>> zernikeMatrix_recon_rotate;
std::vector<double> zernikeMatrix_recon_ParaCal(144);   //求均值和RMS值用的一维形式




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



// 最终发给变形镜用于闭环的变量
double zernikeMatrix_recon_array[140];




#pragma endregion 波前计算交互数据




// 高速模式下定标位置的坐标位置
// 数组形式
float			XScale_array[50];
float			YScale_array[40];

// 容器形式
std::vector<float> XScale_vector(50);
std::vector<float> YScale_vector(40);

// 将Matlab计算好的CppData与picked读入
std::vector<std::vector<double>>	lsqA;
std::vector<std::vector<double>>	eff_picked;

BOOL CloseLoopFlag = FALSE;

// 下面是与图像有关的变量
ViUInt8			imageBuf[480 * 480 + 10];  // 一维形式
ViPInt32		row_image;
ViPInt32		col_image;
IplImage*		m_img;  // 读取图片
BOOL			CMOSImageFlag = TRUE;

// PID参数，以全局变量的形式，在线程之间交互
double pid_p, pid_i, pid_d;
double DM_PID_P[140];
double DM_PID_I[140];
double DM_PID_D[140];

// 相对坐标偏移
double coordMoveX = 0;
double coordMoveY = 0;

// 子对话框的全局变量
double timerSetterInterval = 0;


int angleRotate = 0;

int chooseAlgoIndex = 2;

////////////////////////////// 梯度函数的全局变量  //////////////////////////////////

double randomMatrix[140];			// 生成的随机矩阵
std::vector<std::vector<double>> zernikeMatrix_recon_ADD; // 加操作的执行量
std::vector<std::vector<double>> zernikeMatrix_recon_MINUS; // 减操作的执行量

// 默认操作发给变形镜
double zernikeMatrix_recon_array_DEFAULT[140];
// 加操作中最终发给变形镜用于闭环的变量，对应zernikeMatrix_recon_array[140]
double zernikeMatrix_recon_array_ADD[140];
// 减操作中最终发给变形镜用于闭环的变量，对应zernikeMatrix_recon_array[140]
double zernikeMatrix_recon_array_MINUS[140];

// 用于存储加操作的波前统计参数
double     wavefront_min_add, wavefront_max_add, wavefront_diff_add, wavefront_mean_add, wavefront_rms_add, wavefront_weighted_rms_add;
// 用于存储减操作的波前统计参数
double     wavefront_min_minus, wavefront_max_minus, wavefront_diff_minus, wavefront_mean_minus, wavefront_rms_minus, wavefront_weighted_rms_minus;




// 与报警相关的变量，如果有错误就在IDC_STATIC_SHOW_ERROR控件上显示出来
BOOL FLAG_NAN = 0;  // 0表示没有NAN数据，1表示有NAN数据
CString str_showerror;    // 用于状态栏字符的显示
double NAN_deviationXY[100][29][29];


double bias_initial = 1200;   // 冲击响应函数的偏置量，单位nm
double impulse_stroke = 1300;  // 冲击响应函数的冲击量，单位nm


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
	coeff[0] = 0.0227;
	coeff[1] = 12.082;
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

#pragma region 将数据发送给DM
	// 这里也许需要一个矩阵旋转的过程




	// 二维vector转为一维vector，删掉4个角上的元素，转为一维数组
	std::vector<double> zernikeMatrix_recon_1d(144);		// 声明并初始化一个一维vector
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			zernikeMatrix_recon_1d[i * 12 + j] = zernikeMatrix_recon[i][j];
	// 要删除4个元素
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin());
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 10);
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 130);
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 140);
	//将140个元素的一维vector转为数组, 删除元素之后的一维vector用于输出到文件
	double zernikeMatrix_recon_array[140] = { 0 };
	for (int i = 0; i < 140; ++i)
	{
		// 正常情况下的计算结果发送给变形镜
		zernikeMatrix_recon_array[i] = zernikeMatrix_recon_array[i] + zernikeMatrix_recon_1d[i] * 500 * 0.2;
		// 测试状态下，将0值发送给变形镜
		//zernikeMatrix_recon_array[i] = 0;
	}


	//## 这里要有一个转换，将vector转换为数组
	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = zernikeMatrix_recon_array;  // dDMDesired的单位是nm
	int status = P_DM_SetSpatialFrame();

	// 将二维和一维的矩阵写入文件
	write_2d_File("D:\\externLib\\AOS\\Output\\Recon_zernikeMatrix2D.txt", zernikeMatrix_recon);
	write_1d_File("D:\\externLib\\AOS\\Output\\Recon_zernikeMatrix1D.txt", zernikeMatrix_recon_1d);

	//## 用完zernikeMatrix_recon，千万要pop，否则数据会一直堆积
	release_2dVector(zernikeMatrix_recon, 12);
	release_1dVector(zernikeMatrix_recon_1d, 140);

#pragma endregion 将数据发送给DM




}// 波前重建模式下控制变形镜



void CAOSys_v8Dlg::OnClickedButtonDmZero()
{

	// 初始化局部变量
	std::vector<double> test_zernikeMatrix_recon_1d(144);
	double test_zernikeMatrix_recon_array[140];
	double generateWavefront[12][12];


	// 产生一个倾斜的基底
	zernike(1, -1, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_02, pupil, coordMoveX, coordMoveY);

	for (int row = 0; row < 12; ++row)
	{
		for (int col = 0; col < 12; ++col)
		{
			generateWavefront[row][col] = zernikeMatrix_02[row][col];
		}
	}


	// 二维数据转为一维数据
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			test_zernikeMatrix_recon_1d[i * 12 + j] = generateWavefront[i][j];

	// 要删除4个元素
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin());
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin() + 10);
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin() + 130);
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin() + 140);

	//将140个元素的一维vector转为数组, 删除元素之后的一维vector用于输出到文件
	for (int i = 0; i < 140; ++i)
	{

		// P环节
		DM_PID_P[i] = DM_PID_P[i] + test_zernikeMatrix_recon_1d[i] * 500 * pid_p;

		test_zernikeMatrix_recon_array[i] = 1200 + DM_PID_P[i];  // P控制

	}




	//## 这里要有一个转换，将vector转换为数组
	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = test_zernikeMatrix_recon_array;
	int status = P_DM_SetSpatialFrame();


	// 将内存中的值刷入EDIT控件显示
	float temp = 0;
	for (int k_index = 0; k_index < 144; ++k_index)
	{
		temp = generateWavefront[k_index / 12][k_index % 12];
		(ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
		SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

	}


}



// 计算Zernike拟合误差
// 选择合适的网格，WFS探测到的波前减去Zernike拟合的波前
void CAOSys_v8Dlg::OnClickedButtonRecZerfiterr()
{
	// 这里拟合误差就是在29x29网格的情况下，将wavefront的测量波前或者Zernike重建波前与我的Zernike重建波前进行做差的过程
	// 这个过程需要我的Zernike拟合波前矩阵进行一定的变换，如转置，旋转等操作

	// 为了满足不同分辨率要求wavefront的尺寸为MAX_SPOTS_Y x MAX_SPOTS_X
	// 为了计算拟合误差，要调整到29 x 29，所以定义了Wavefront_Copy矩阵
	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			Wavefront_Copy[i][j] = wavefront[i][j];
		}
	}



	// 矩阵减法
	for (int i = 0; i < 29; ++i)
		for (int j = 0; j < 29; ++j)
		{
			zerPolyError29[i][j] = Wavefront_Copy[i][j] - zerWave_Matrix29[i][j];
		}

	WFS_WriteWavefrontZernikeError();

	// 将Zernike拟合误差矩阵写入文件
}

// 波前重建模式下  写入文本事件
void CAOSys_v8Dlg::OnClickedButtonRecWrite()
{
	// 将 波前重建模式下 波前重建事件 中全局变量zernikeMatrix_recon的填充值写入文档
	write_2d_File("D:\\externLib\\AOS\\Output\\Recon_zernikeMatrix2D.txt", zernikeMatrix_recon);


	GetDlgItem(IDC_EDIT_STA_WRITE)->SetWindowText(_T("写入成功"));
}  // 波前重建模式下  写入文本事件



//--------------------------  波前校正事件  --------------------------//
// 此阶段需要开启12x12网格

// 开始闭环校正波前
void CAOSys_v8Dlg::OnClickedButtonConCloseloop()
{

	// 如果是PID算法，那么就计算基底
	if (chooseAlgoIndex == 0)
	{

#pragma region 产生基底


		zernike(0, 0, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_01, pupil, coordMoveX, coordMoveY);
		zernike(1, -1, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_02, pupil, coordMoveX, coordMoveY);
		zernike(1, 1, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_03, pupil, coordMoveX, coordMoveY);
		zernike(2, -2, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_04, pupil, coordMoveX, coordMoveY);
		zernike(2, 0, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_05, pupil, coordMoveX, coordMoveY);
		zernike(2, 2, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_06, pupil, coordMoveX, coordMoveY);
		zernike(3, -3, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_07, pupil, coordMoveX, coordMoveY);
		zernike(3, -1, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_08, pupil, coordMoveX, coordMoveY);
		zernike(3, 1, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_09, pupil, coordMoveX, coordMoveY);
		zernike(3, 3, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_10, pupil, coordMoveX, coordMoveY);
		zernike(4, -4, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_11, pupil, coordMoveX, coordMoveY);
		zernike(4, -2, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_12, pupil, coordMoveX, coordMoveY);
		zernike(4, 0, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_13, pupil, coordMoveX, coordMoveY);
		zernike(4, 2, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_14, pupil, coordMoveX, coordMoveY);
		zernike(4, 4, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_15, pupil, coordMoveX, coordMoveY);



#pragma endregion 产生基底

	}


	// 线程的参数设置
	int       nPriority = THREAD_PRIORITY_HIGHEST;//默认为THREAD_PRIORITY_NORMAL
	UINT       nStackSize = 0;//与创建它的线程堆栈大小相同
	DWORD       dwCreateFlags = CREATE_SUSPENDED;//CREATE_SUSPENDED 创建后挂起线程

	// 创建新线程
	pThread_LOOP = new CWinThread();
	pThread_LOOP->m_bAutoDelete = FALSE;
	pThread_LOOP = AfxBeginThread(ThreadFunc_WFS_Measurement_CONLOOP, this,
		nPriority, nStackSize, dwCreateFlags);  // 使用this指针将CAOSys_v7Dlg类传入线程函数
	pThread_LOOP->ResumeThread();


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
	// 将DM_CenterUp.txt文件读入到内存
	if ((fp = fopen("D:\\externLib\\AOS\\conDM\\DM_CenterUp.txt", "rt")) == NULL)
	{
		::MessageBox(NULL, _T("不能打开文件！"), _T("Status"), MB_OK);
	}
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
			fscanf(fp, "%f", &zerWave_Matrix[i][j]);
		fscanf(fp, "\n");
	}
	fclose(fp);

	// 把矩阵校验一下
	DM_WriteCheckZernikeMatrix();

#pragma region mapping   //这一部分的代码要修改，系统确定了，坐标关系也就确定了
	Mapping = 0;
	if (Mapping == 0)
	{
		// 左右翻转
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[i][11 - j] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("左右翻转"));
	}
	else if (Mapping == 1)
	{
		// 上下翻转
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[11 - i][j] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("上下翻转"));
	}
	else if (Mapping == 2)
	{
		// 转置
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[j][i] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("转置"));
	}
	else if (Mapping == 3)
	{
		// 顺时针转动90度
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[j][11 - i] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("顺时针转动90度"));
	}
	else if (Mapping == 4)
	{
		// 顺时针转动180度
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[11 - i][11 - j] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("顺时针转动180度"));
	}
	else if (Mapping == 5)
	{
		// 顺时针转动270度, 这个结果看起来不错
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[11 - j][i] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("顺时针转动270度"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("非法映射"));
	}
#pragma endregion mapping

	// 将转置后的矩阵写入文件
	DM_WriteTransposeMatrix();


	// 将二维矩阵zerWave_Matrix，根据手册中的DM Actuator Map转换为一维的数据，长度为140
	// 得到可以写入DM的Stroke数组DM_Stroke_1D
	// 输出信息：
	//			DM_Stroke_1D[144]

	for (int j = 1; j < 11; ++j)
	{
		DM_Stroke_1D[j] = zerWave_Matrix[0][j];
	}
	DMcount = 0;
	for (int i = 1; i < 11; ++i)
		for (int j = 0; j < 12; ++j)
		{
			DM_Stroke_1D[11 + DMcount] = zerWave_Matrix_Temp[i][j];
			++DMcount;
		}
	for (int j = 1; j < 11; ++j)
	{
		DM_Stroke_1D[131 + j - 1] = zerWave_Matrix_Temp[11][j];  // 这个向量就是可以直接写入DM的一维驱动器行程的控制量
	}

	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = DM_Stroke_1D;
	int status = P_DM_SetSpatialFrame();

	DM_Write1DMatrix();
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
		// 根据调整好的tabRect放置m_ReconWavefontDlg子对话框，并设置为隐藏   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
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
		// 根据调整好的tabRect放置m_androidDlg子对话框，并设置为显示   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为隐藏 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 2:
		// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为隐藏   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为显示 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 3:
		// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为隐藏   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_DeformMirrorDlg子对话框，并设置为显示 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 同理
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// 同理
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 4:
		// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为隐藏   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
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

	// 弹出基底
	if (zernikeMatrix_01.size() > 0)
	{
		release_2dVector(zernikeMatrix_01, 12);
		release_2dVector(zernikeMatrix_02, 12);
		release_2dVector(zernikeMatrix_03, 12);
		release_2dVector(zernikeMatrix_04, 12);
		release_2dVector(zernikeMatrix_05, 12);
		release_2dVector(zernikeMatrix_06, 12);
		release_2dVector(zernikeMatrix_07, 12);
		release_2dVector(zernikeMatrix_08, 12);
		release_2dVector(zernikeMatrix_09, 12);
		release_2dVector(zernikeMatrix_10, 12);
		release_2dVector(zernikeMatrix_11, 12);
		release_2dVector(zernikeMatrix_12, 12);
		release_2dVector(zernikeMatrix_13, 12);
		release_2dVector(zernikeMatrix_14, 12);
		release_2dVector(zernikeMatrix_15, 12);

	}

	// 弹出重新初始化PID参数
	if (pid_p != 0 || pid_i != 0 || pid_d != 0)
	{
		pid_p = 0;
		pid_i = 0;
		pid_d = 0;
	}

	for (int i = 0; i < 140; ++i)  // 程序结束置零
	{
		zernikeMatrix_recon_array[i] = 0;
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


	for (int i = 0; i < 140; ++i)  // 程序结束置零
	{
		zernikeMatrix_recon_array[i] = 1200;
	}


	// 子对话框的设置
	(ptr_MiscSettingDlg->GetDlgItem(IDC_EDIT_SUBDLG_TIMERSETTING))->GetWindowTextW(ptr_MiscSettingDlg->m_Edit_TimeSetter); // x方向坐标偏移
	timerSetterInterval = _ttoi(ptr_MiscSettingDlg->m_Edit_TimeSetter);


	GetDlgItem(IDC_EDIT_SETANGLE)->GetWindowText(m_Edit_SetAngle);
	angleRotate = _wtoi(m_Edit_SetAngle);


	// 将预处理的数据载入，即Matlab求逆数据




}




void CAOSys_v8Dlg::OnSelchangeComboChoosealgo()
{
	// TODO: Add your control notification handler code here

	chooseAlgoIndex = m_Combo_ChooseAlgo.GetCurSel();
}


// 直接斜率法的预处理事件
void CAOSys_v8Dlg::OnBnClickedButtonPreCalc()
{
	// 将140个DM驱动器单元依次发给变形镜，WFS获得响应的波前
	double DM_PreCalc[140];  // 必须是double，否则aoSystemData->dDMDesired = DM_PreCalc;不好强转
	float  deviation_x_PreCalc[40][50];  // x方向脱靶量，单位像素
	float  deviation_y_PreCalc[40][50];  // y方向脱靶量，单位像素
	std::vector<std::vector<double>> deviation_x_nm_PreCalc;  // x方向斜坡数据，单位nm
	std::vector<std::vector<double>> deviation_y_nm_PreCalc;   // y方向斜坡数据，单位nm

	// 初始化容器
	init_2dVector(deviation_x_nm_PreCalc, 29, 29);
	init_2dVector(deviation_y_nm_PreCalc, 29, 29);


	// 用于保存文件的std::string
	// 尽量少用CString，而多用标准库中的std::string
	std::string fileFullPath, filenamePrefix, finenameSuffix;
	std::string indexCString, XdeviCString, YdeviCString;
	std::string statusCString;

	XdeviCString = "XDevi";
	YdeviCString = "YDevi";
	filenamePrefix = "D:\\externLib\\AOS\\Output\\PreCalc\\in\\";
	finenameSuffix = ".txt";

	// 用于在状态栏显示
	CString indexCString_forreal;

	// WFS像素大小4.65um，用于将单位从pixel转换为nm
	float  unitCoeff = 1; 

	for (int index = 0; index < 140; ++index)
	{
		// 依次更改变形镜
		for (int i = 0; i < 140; ++i)
		{
			DM_PreCalc[i] = bias_initial;
		}
		DM_PreCalc[index] = bias_initial + impulse_stroke;

		// 驱动DM
		P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
		aoSystemData->dDMDesired = DM_PreCalc;
		int status = P_DM_SetSpatialFrame();


		//WFS探测到的波前分别保存至文件
		// 普通模式下，获取子孔径阵列的图片
		WFS_TakeSpotfieldImage(instr.handle);
		// 根据图片计算质心位置
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
		// 计算脱靶量
		WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
		// 获得脱靶量，单位是像素
		WFS_GetSpotDeviations(instr.handle, *deviation_x_PreCalc, *deviation_y_PreCalc);

		// 更换数据类型
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{
				deviation_x_nm_PreCalc[row][col] = deviation_x_PreCalc[row][col] * unitCoeff;
				deviation_y_nm_PreCalc[row][col] = deviation_y_PreCalc[row][col] * unitCoeff;
			}
		} 

		// int类型转换为std::string类型
		IntToString(indexCString, index);
		


#pragma region 等待时间

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
		} while (nTime_dmwait < 300);


#pragma endregion 等待时间




		// 将x脱靶量写入文件
		fileFullPath = filenamePrefix + XdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_x_nm_PreCalc);
		// 将y脱靶量写入文件
		fileFullPath = filenamePrefix + YdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_y_nm_PreCalc);


		indexCString_forreal.Format(_T("%d"), index);
		str_showerror = _T("预处理数据：  ") + indexCString_forreal;
		SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

	}


	str_showerror = _T("预处理完毕");
	SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

	// 用完容器要释放
	release_2dVector(deviation_x_nm_PreCalc, 29);
	release_2dVector(deviation_y_nm_PreCalc, 29);

}


// 将Matlab的预处理数据载入，用于从脱靶量直接获得变形镜的执行量
void CAOSys_v8Dlg::OnBnClickedButtonPreCalcLoad()
{

	// 将Matlab计算好的lsqA与eff_picked读入
	// 例如，有效子孔径点个数为609,那么，lsqA的维数就应该是140*1218
	lsqA = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\lsqA.txt");
	// 由于eff_picked要作为索引项，因此要将其转换为const int类型
	// 例如，有效子孔径点个数为609，eff_picked当时初始化为841*2的矩阵，第610个为[0,0]，611起到后面都是未定义的值，在这之前是有效子孔径的位置信息
	eff_picked = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\eff_picked.txt");
	// 注意eff_picked.size()表示行数，eff_picked[0].size()表示列数
	// 例如eff_picked有609个子孔径点的索引号，那么就是609x2的一个矩阵，那么eff_picked.size()=609，eff_picked[0].size()=2

	//// eff_picked做索引号举例如下：
	//// MyMat_double类型的数据做索引
	//lsqA[eff_picked[2][0]][eff_picked[2][1]];
	//// vector<vector<double>>类型的数据做索引和上面是一样的
	//zernikeMatrix_15[eff_picked[2][0]][eff_picked[2][1]];
	//// float(POD)类型数据就要强转了！
	//wavefront[(int)eff_picked[2][0]][(int)eff_picked[2][1]];

}


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
	char           strg[WFS_BUFFER_SIZE];

	//char*类型转换为多字节输出
	WCHAR W_instr_name[512];
	WCHAR W_serNr[512];
	WCHAR W_resourceName[512];

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

#pragma region 线程中的局部变量

	// 几个指向对话框的指针
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	// 与绘图有关的变量
	uchar image2DBuf[480][480];  // 二维形式


	// 几个开关,checkbox用作开关
	CButton* modeSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_MODESWITCH));
	CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
	CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));


#pragma endregion 线程中的局部变量



#pragma region 闭环前的参数设置


	if (modeSwitch->GetCheck() == 1)
	{
		//## 设置WFS为高速模式，这个函数只需要设置一次，如果勾选高速模式，那么就调用一下这个函数
		WFS_SetHighspeedMode(instr.handle, OPTION_HIGHSPEED, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);
	}
	else
	{
		// 关闭高速模式
		WFS_SetHighspeedMode(instr.handle, 0, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);

	}

#pragma endregion 闭环前的参数设置



#pragma region 计算质心位置

	// 第一步：计算质心位置
	// 首先判断是用普通模式获得质心位置还是用高速模式获得质心位置
	// 高速模式速度快，但是没有图像显示
	// 普通模式速度慢，但是有图像显示
	if (modeSwitch->GetCheck() == 1)   // 高速模式DSP计算质心，USB cable不传输图像
	{
		// 高速模式获取质心位置
		WFS_GetStatus(instr.handle, &instr.status);
		std::bitset<32> judge = instr.status & (WFS_STATBIT_HSP | WFS_STATBIT_SPC | WFS_STATBIT_PUD | WFS_STATBIT_CFG);
		if (judge == 0x2700)
		{
		}
		else
		{
			::MessageBox(NULL, _T("不是高速模式！"), _T("Status"), MB_OK);
		}

		// 检查当前是否为高速模式，这个函数貌似无法检测到底是不是高速模式
		err = WFS_CheckHighspeedCentroids(instr.handle);
		if (err == 0)
		{
		}
		else
		{
			WFS_HandleErrors(err);
		}


		// 调用下面的函数，就能保证每次DSP计算完，每次循环的时候都会将新数据刷新至内存中，还可以用于图形显示
		WFS_TakeSpotfieldImage(instr.handle);

	}



	else   // 普通模式通过图像处理的方法获得质心位置，USB cable传输图像
	{
		// 普通模式获取质心位置
		WFS_TakeSpotfieldImage(instr.handle);
		// 计算质心位置
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);



#pragma region 显示子孔径图像

		if (subApertureImageSwitch->GetCheck() == 1)
		{

			// 将图像刷入内存
			WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
			// 将图像由一维转为二维，下面的转换经过验证是正确的
			for (int row = 0; row < 480; ++row)
				for (int col = 0; col < 480; ++col)
				{
					image2DBuf[row][col] = imageBuf[480 * row + col];
				}
			//----------------------------------------------------------//
			//## 监测通道
			(pW->m_Edit_Sta_Watch).Format(_T("%u"), sizeof(image2DBuf));
			pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);
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
		else
		{
			if (CMOSImageFlag == TRUE)
			{
				pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
			}
			CMOSImageFlag = FALSE;  // 设置标志
		}


#pragma endregion 显示子孔径图像



	}

#pragma endregion 计算质心位置



#pragma region 计算脱靶量

	// 第二步：计算脱靶量
	// 计算脱靶量
	WFS_CalcSpotToReferenceDeviations(instr.handle, 1);
	// 获取质心位置
	//WFS_GetSpotCentroids(instr.handle, *centroid_x, *centroid_y);
	// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
	WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);

	CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));
	if (deviationSwitch->GetCheck() == 1) // 显示脱靶量
	{
		pW->ptr_DeviationXDlg->ShowDeviationX();
	}

#pragma endregion 计算脱靶量



#pragma region 获得波前统计信息

	//根据脱靶量重建波前
	WFS_CalcWavefront(instr.handle, instr_setup.wavefront_type, instr_setup.pupil_circular, *wavefront);
	WFS_WriteCalcWavefront();  //  输出波前到WFS_CalcWavefront.txt


	// 获得波前统计信息 
	//wavefront_diff=wavefront_max-wavefront_min，这个就是光瞳内的PV值
	err = WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
		&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);
	if (err == 0)
	{
		// 显示PV值
		(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
		pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);

		// 显示RMS值
		(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
		pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);

	}
	else
	{
		WFS_HandleErrors(err);
	}

#pragma endregion 获得波前统计信息

	// 线程函数需要一个返回值
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//## 注意，在波前重建模式下，“波前重建”按钮与“控制DM”按钮要成对使用，因为在“波前重建”按钮中zernikeMatrix_recon要push_back
//## 而在中，要对应的把zernikeMatrix_recon与zernikeMatrix_recon_1d两个变量pop_back才可以，否则数据堆积，造成无法正确控制DM
// 波前重建模式下 波前重建线程
UINT ThreadFunc_WFS_Measurement_REC(LPVOID pParam)
{
	// 这个线程函数的作用：探测波前，并使用最小二乘法，将波前重建，然后根据需要选择是否进行保存


#pragma region 线程中的局部变量

	// 几个指向对话框的指针
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	// 与绘图有关的变量
	uchar image2DBuf[480][480];  // 二维形式


	// 几个开关,checkbox用作开关
	CButton* modeSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_MODESWITCH));
	CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
	CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));

#pragma endregion 线程中的局部变量



#pragma region 闭环前的参数设置


	if (modeSwitch->GetCheck() == 1)
	{
		//## 设置WFS为高速模式，这个函数只需要设置一次，如果勾选高速模式，那么就调用一下这个函数
		WFS_SetHighspeedMode(instr.handle, OPTION_HIGHSPEED, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);
	}
	else
	{
		// 关闭高速模式
		WFS_SetHighspeedMode(instr.handle, 0, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);

	}

#pragma endregion 闭环前的参数设置



#pragma region 计算质心位置

	// 第一步：计算质心位置
	// 首先判断是用普通模式获得质心位置还是用高速模式获得质心位置
	// 高速模式速度快，但是没有图像显示
	// 普通模式速度慢，但是有图像显示
	if (modeSwitch->GetCheck() == 1)   // 高速模式DSP计算质心，USB cable不传输图像
	{
		// 高速模式获取质心位置

		// 检查是否为高速模式，进行位运算判断运行状态
		// 正常情况下，这里instr.status返回的是0x2700,说明是：
		//		0x00000100  WFS_STATBIT_CFG  Camera is ConFiGured
		//		0x00000200  WFS_STATBIT_PUD  PUpil is Defined
		//		0x00000400  WFS_STATBIT_SPC  No.of Spots or Pupil Changed
		//		0x00002000  WFS_STATBIT_HSP  Camera is in HighSPeed Mode
		WFS_GetStatus(instr.handle, &instr.status);
		std::bitset<32> judge = instr.status & (WFS_STATBIT_HSP | WFS_STATBIT_SPC | WFS_STATBIT_PUD | WFS_STATBIT_CFG);
		if (judge == 0x2700)
		{
		}
		else
		{
			::MessageBox(NULL, _T("不是高速模式！"), _T("Status"), MB_OK);
		}
		// 报错0x1792
		//0x00000002  WFS_STATBIT_PTH  Power Too High(cam saturated)
		//0x00000010  WFS_STATBIT_SCL  Spot Contrast too Low
		//0x00000080  WFS_STATBIT_ATR  Camera is still Awaiting a TRigger
		//0x00000100  WFS_STATBIT_CFG  Camera is ConFiGured
		//0x00000200  WFS_STATBIT_PUD  PUpil is Defined
		//0x00000400  WFS_STATBIT_SPC  No.of Spots or Pupil Changed
		//0x00001000  WFS_STATBIT_URF  No User ReFerence available



		// 检查当前是否为高速模式，这个函数貌似无法检测到底是不是高速模式
		err = WFS_CheckHighspeedCentroids(instr.handle);
		if (err == 0)
		{
		}
		else
		{
			WFS_HandleErrors(err);
		}


		// 调用下面的函数，就能保证每次DSP计算完，每次循环的时候都会将新数据刷新至内存中，还可以用于图形显示
		WFS_TakeSpotfieldImage(instr.handle);

	}



	else   // 普通模式通过图像处理的方法获得质心位置，USB cable传输图像
	{
		// 普通模式获取质心位置
		WFS_TakeSpotfieldImage(instr.handle);
		// 计算质心位置
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);



#pragma region 显示子孔径图像

		if (subApertureImageSwitch->GetCheck() == 1)
		{

			// 将图像刷入内存
			WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
			// 将图像由一维转为二维，下面的转换经过验证是正确的
			for (int row = 0; row < 480; ++row)
				for (int col = 0; col < 480; ++col)
				{
					image2DBuf[row][col] = imageBuf[480 * row + col];
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
		else
		{
			if (CMOSImageFlag == TRUE)
			{
				pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
			}
			CMOSImageFlag = FALSE;  // 设置标志
		}


#pragma endregion 显示子孔径图像



	}

#pragma endregion 计算质心位置



#pragma region 计算脱靶量

	// 第二步：计算脱靶量
	// 计算脱靶量
	WFS_CalcSpotToReferenceDeviations(instr.handle, 0);
	// 获取质心位置
	//WFS_GetSpotCentroids(instr.handle, *centroid_x, *centroid_y);
	// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
	WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);

	CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));
	if (deviationSwitch->GetCheck() == 1) // 显示脱靶量
	{
		pW->ptr_DeviationXDlg->ShowDeviationX();
	}

#pragma endregion 计算脱靶量



#pragma region 内置函数求zernike系数

	zernike_order = 4; // 0 ： zernike order auto
	WFS_ZernikeLsf(instr.handle, (ViInt32*)&zernike_order, zernike_um, zernike_orders_rms_um, &roc_mm);

#pragma endregion 内置函数求zernike系数



#pragma region 获得波前统计信息

	//根据脱靶量重建波前
	err = WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);
	WFS_WriteCalcWavefront();  //  输出波前到WFS_CalcWavefront.txt


	// 获得波前统计信息 
	//wavefront_diff=wavefront_max-wavefront_min，这个就是光瞳内的PV值
	err = WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
		&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);
	if (err == 0)
	{
		// 显示PV值
		(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
		pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);

		// 显示RMS值
		(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
		pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);

	}
	else
	{
		WFS_HandleErrors(err);
	}

#pragma endregion 获得波前统计信息



#pragma region 重建波前矩阵

	//------ 重建波前
	// 对应float	zernike_um[MAX_ZERNIKE_MODES + 1]的容器变量，vector_zernike_um是局部变量
	std::vector<double> vector_zernike_um;  // 15个zernike系数
	for (int i = 1; i <= 15; ++i)		// 一维数组转换为一维vector
		vector_zernike_um.push_back(zernike_um[i]);

	// 初始化二维重建波前数据矩阵
	init_2dVector(zernikeMatrix_recon, 12, 12);


	// 下面进行数乘和矩阵相加的运算，得到重建的zernike拟合的波前
	for (int row = 0; row < 12; ++row)
		for (int col = 0; col < 12; ++col)
		{
			zernikeMatrix_recon[row][col] =
				vector_zernike_um[0] * zernikeMatrix_01[row][col] +
				vector_zernike_um[1] * zernikeMatrix_02[row][col] +
				vector_zernike_um[2] * zernikeMatrix_03[row][col] +
				vector_zernike_um[3] * zernikeMatrix_04[row][col] +
				vector_zernike_um[4] * zernikeMatrix_05[row][col] +
				vector_zernike_um[5] * zernikeMatrix_06[row][col] +
				vector_zernike_um[6] * zernikeMatrix_07[row][col] +
				vector_zernike_um[7] * zernikeMatrix_08[row][col] +
				vector_zernike_um[8] * zernikeMatrix_09[row][col] +
				vector_zernike_um[9] * zernikeMatrix_10[row][col] +
				vector_zernike_um[10] * zernikeMatrix_11[row][col] +
				vector_zernike_um[11] * zernikeMatrix_12[row][col] +
				vector_zernike_um[12] * zernikeMatrix_13[row][col] +
				vector_zernike_um[13] * zernikeMatrix_14[row][col] +
				vector_zernike_um[14] * zernikeMatrix_15[row][col];
		}

#pragma endregion 重建波前矩阵




	return 0;
}  // 波前重建模式下 波前重建线程




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 波前控制的线程函数
UINT ThreadFunc_WFS_Measurement_CONLOOP(LPVOID pParam)
{


#pragma region PID算法

	// PID算法
	if (chooseAlgoIndex == 0)
	{


#pragma region 线程中的局部变量

		// 几个指向对话框的指针
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;


		// 用于计算帧率的时间变量
		double t_interval_2nd = 0; // 循环所用时间
		LARGE_INTEGER nStartCounter_2nd;  // 开始计算次数
		LARGE_INTEGER nFrequency_2nd;   // 每秒次数
		LARGE_INTEGER nStopCounter_2nd;  // 终止计算次数


		double frameRate = 0;  // 帧率
		int looptime = 0;


		// 与绘图有关的变量
		uchar image2DBuf[480][480];  // 二维形式


		// 几个开关,checkbox用作开关
		CButton* modeSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_MODESWITCH));
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
		CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));
		CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));



		for (int index = 0; index < 140; ++index)
		{
			DM_PID_P[index] = 1200;
		}



		// 初始化两个坐标数组，在这里调整WFS与DM的相对坐标
		// DM的物理坐标，变形镜的pitch为400um=0.4mm，一共12个单元
		double xArray_Mode[12];
		double yArray_Mode[12];
		for (int i = 0; i < 12; ++i)
			xArray_Mode[i] = -2.4 + i * 0.4;
		for (int i = 0; i < 12; ++i)
			yArray_Mode[i] = -2.4 + i * 0.4;


		int NAN_counter = 0; // 计算NAN数据的个数


#pragma endregion 线程中的局部变量



#pragma region 闭环前的参数设置



		// 高速模式与普通模式的预设
		if (modeSwitch->GetCheck() == 1)
		{
			//## 设置WFS为高速模式，这个函数只需要设置一次，如果勾选高速模式，那么就调用一下这个函数
			WFS_SetHighspeedMode(instr.handle, 1, 0, NoiseCutAct, 0);
		}
		else
		{
			// 关闭高速模式
			WFS_SetHighspeedMode(instr.handle, 0, 0, NoiseCutAct, 0);

		}

#pragma endregion 闭环前的参数设置



		// 闭环
		CloseLoopFlag = TRUE;
		int count_devi = 0;  // 记录每个时刻的脱靶量
		while (CloseLoopFlag)
		{

#pragma region 计时器开始
			//新计时器开始
			LARGE_INTEGER nStartCounter_test;
			LARGE_INTEGER nFrequency_test;
			double nTime_test = 0; // 记录时间

			::QueryPerformanceCounter(&nStartCounter_test);
			::QueryPerformanceFrequency(&nFrequency_test);
#pragma endregion 计时器开始



#pragma region 帧率显示
			// 帧率---起始部分
			::QueryPerformanceCounter(&nStartCounter_2nd);
			::QueryPerformanceFrequency(&nFrequency_2nd);

#pragma endregion 帧率显示



#pragma region 计算质心位置

			// 第一步：计算质心位置
			// 首先判断是用普通模式获得质心位置还是用高速模式获得质心位置
			// 高速模式速度快，但是没有图像显示
			// 普通模式速度慢，但是有图像显示
			if (modeSwitch->GetCheck() == 1)   // 高速模式DSP计算质心，USB cable不传输图像
			{
				// 高速模式获取质心位置

				// 检查是否为高速模式，进行位运算判断运行状态
				// 正常情况下，这里instr.status返回的是0x2700,说明是：
				//		0x00000100  WFS_STATBIT_CFG  Camera is ConFiGured
				//		0x00000200  WFS_STATBIT_PUD  PUpil is Defined
				//		0x00000400  WFS_STATBIT_SPC  No.of Spots or Pupil Changed
				//		0x00002000  WFS_STATBIT_HSP  Camera is in HighSPeed Mode
				WFS_GetStatus(instr.handle, &instr.status);
				std::bitset<32> judge = instr.status & (WFS_STATBIT_HSP | WFS_STATBIT_SPC | WFS_STATBIT_PUD | WFS_STATBIT_CFG);
				if (judge == 0x2700)
				{
				}
				else
				{
					::MessageBox(NULL, _T("不是高速模式！"), _T("Status"), MB_OK);
					break;
				}
				// 报错0x1792
				//0x00000002  WFS_STATBIT_PTH  Power Too High(cam saturated)
				//0x00000010  WFS_STATBIT_SCL  Spot Contrast too Low
				//0x00000080  WFS_STATBIT_ATR  Camera is still Awaiting a TRigger
				//0x00000100  WFS_STATBIT_CFG  Camera is ConFiGured
				//0x00000200  WFS_STATBIT_PUD  PUpil is Defined
				//0x00000400  WFS_STATBIT_SPC  No.of Spots or Pupil Changed
				//0x00001000  WFS_STATBIT_URF  No User ReFerence available



				// 检查当前是否为高速模式，这个函数貌似无法检测到底是不是高速模式
				err = WFS_CheckHighspeedCentroids(instr.handle);
				if (err == 0)
				{
				}
				else
				{
					WFS_HandleErrors(err);
				}


				// 调用下面的函数，就能保证每次DSP计算完，每次循环的时候都会将新数据刷新至内存中，还可以用于图形显示
				WFS_TakeSpotfieldImage(instr.handle);

			}



			else   // 普通模式通过图像处理的方法获得质心位置，USB cable传输图像
			{
				// 普通模式获取质心位置
				WFS_TakeSpotfieldImage(instr.handle);
				// 计算质心位置
				WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);



#pragma region 显示子孔径图像

				if (subApertureImageSwitch->GetCheck() == 1)
				{

					// 将图像刷入内存
					WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
					// 将图像由一维转为二维，下面的转换经过验证是正确的
					for (int row = 0; row < 480; ++row)
						for (int col = 0; col < 480; ++col)
						{
							image2DBuf[row][col] = imageBuf[480 * row + col];
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
				else
				{
					if (CMOSImageFlag == TRUE)
					{
						pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
					}
					CMOSImageFlag = FALSE;  // 设置标志
				}


#pragma endregion 显示子孔径图像



			}

#pragma endregion 计算质心位置



#pragma region 计算脱靶量

			// 第二步：计算脱靶量
			// 计算脱靶量
			WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
			// 获取质心位置
			WFS_GetSpotCentroids(instr.handle, *centroid_x, *centroid_y);
			// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
			WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);
			//## 监测通道
			//(pW->m_Edit_Sta_Watch).Format(_T("%lf"), deviation_x[14][14]);
			//pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);



#pragma region 复杂的无效数据处理办法

			for (int row = 1; row < 28; ++row)  // 空出最上下两行
			{
				for (int col = 1; col < 28; ++col) // 空出最左右两列
				{

					// 判断x方向
					if (_isnan(deviation_x[row][col]))
					{
						++NAN_counter;
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
							str_showerror = "警报：PID算法  X方向脱靶量  过多无效数据！ 无效数据已置零！";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

							str_showerror = "警报：PID算法  X方向脱靶量  无效数据已被插值";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

						}


					}  // x方向结束



					// 判断y方向
					if (_isnan(deviation_y[row][col]))
					{
						++NAN_counter;

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
							str_showerror = "警报：PID算法  Y方向脱靶量  过多无效数据！ 无效数据已置零！";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

							str_showerror = "警报：PID算法  Y方向脱靶量  无效数据已被插值";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

						}  // 对中心无效值插值结束

					} // y方向结束

				}
			}  // 无效值遍历结束

#pragma endregion 复杂的无效数据处理办法


			//
			//#pragma region 简单处理无效数据的方法
			//
			//			NAN_counter = 0;
			//			for (int row = 0; row < 29; ++row)
			//			{
			//				for (int col = 0; col < 29; ++col)
			//				{
			//					if (_isnan(deviation_x[row][col]))
			//					{
			//						++NAN_counter; // 计数器加一
			//						FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
			//						str_showerror = "警报：PID算法  X脱靶量  中出现NAN数据！";
			//						pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
			//
			//						deviation_x[row][col] = 0;
			//
			//					}
			//					if (_isnan(deviation_y[row][col]))
			//					{
			//						++NAN_counter; // 计数器加一
			//						FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
			//						str_showerror = "警报：PID算法  Y脱靶量  中出现NAN数据！";
			//						pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
			//
			//
			//						deviation_y[row][col] = 0;
			//					}
			//				}
			//			}  // 无效值遍历结束
			//
			//#pragma endregion 简单处理无效数据的方法
			//


			// 显示无效点的个数
			(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
			pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);




			if (deviationSwitch->GetCheck() == 1) // 显示脱靶量，单位是pixel
			{
				pW->ptr_DeviationXDlg->ShowDeviationX();
			}

			// 记录每次循环的脱靶量
			if (pW->ptr_MiscSettingDlg->m_Check_SubDlg_RemeberDevi.GetCheck() == 1)
			{
				// 显示一个动态的省略号
				if (0 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("数据记录中"));
				}
				if (1 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("数据记录中."));
				}
				if (2 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("数据记录中.."));
				}
				if (3 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("数据记录中..."));
				}


				// 将脱靶量记录到三维数组中
				for (int row = 0; row < 29; ++row)
					for (int col = 0; col < 29; ++col)
					{
						rememberDeviationX[row][col][count_devi] = deviation_x[row][col];
						rememberDeviationY[row][col][count_devi] = deviation_y[row][col];
					}


				++count_devi; // 计数器要自加


				if (100 == count_devi)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("数据已满，请中断点击保存！"));
					pW->ptr_MiscSettingDlg->m_Check_SubDlg_RemeberDevi.SetCheck(BST_UNCHECKED); // 取消check，这样下次循环就不进入if语句
				}

			}



#pragma endregion 计算脱靶量



#pragma region 内置函数求zernike系数

			// 拟合zernike系数
			zernike_order = 4; // 0 ： zernike order auto
			WFS_ZernikeLsf(instr.handle, (ViInt32*)&zernike_order, zernike_um, zernike_orders_rms_um, &roc_mm);


			// 显示zernike系数
			CString showZernike;
			for (int index = 0; index < 15; ++index)
			{
				showZernike.Format(_T("%lf"), zernike_um[index + 1]);
				pW->SetDlgItemText(IDC_STATIC_SHOW_ZER1 + index, showZernike);

			}


			//// 记录zernike系数
			//std::vector<double> zernike_um_save(15);
			//for (int index = 0; index < 15;++index)
			//{
			//	zernike_um_save[index] = (double)zernike_um[index + 1];
			//}
			//write_1d_File("D:\\WorkSpace\\Matlab\\N1_Temp\\zernike_um_save.txt", zernike_um_save);

			//// 将zernike_um数重新赋值
			//for (int index = 0; index < 15;++index)
			//{
			//zernike_um[0] = -0.45;
			//zernike_um[1] = 0.837;
			//zernike_um[2] = 0.068;
			//zernike_um[3] = 0.03;
			//zernike_um[4] = -0.561;
			//zernike_um[5] = 0.112;
			//zernike_um[6] = -0.009;
			//zernike_um[7] = 0.048;
			//zernike_um[8] = -0.006;
			//zernike_um[9] = -0.029;
			//zernike_um[10] = -0.015;
			//zernike_um[11] = -0.015;
			//zernike_um[12] = -0.006;
			//zernike_um[13] = -0.009;
			//zernike_um[14] = -0.007;
			//}


#pragma endregion 内置函数求zernike系数



#pragma region 重建波前矩阵


			// 初始化二维重建波前数据矩阵
			init_2dVector(zernikeMatrix_recon, 12, 12);


			// 下面进行数乘和矩阵相加的运算，得到重建的zernike拟合的波前
			for (int row = 0; row < 12; ++row)
				for (int col = 0; col < 12; ++col)
				{
					zernikeMatrix_recon[row][col] =   // zernikeMatrix_recon在本程序中是一个全局数组，类外调用已经使用extern声明
						zernike_um[1] * zernikeMatrix_01[row][col] +
						zernike_um[2] * zernikeMatrix_02[row][col] +
						zernike_um[3] * zernikeMatrix_03[row][col] +
						zernike_um[4] * zernikeMatrix_04[row][col] +
						zernike_um[5] * zernikeMatrix_05[row][col] +
						zernike_um[6] * zernikeMatrix_06[row][col] +
						zernike_um[7] * zernikeMatrix_07[row][col] +
						zernike_um[8] * zernikeMatrix_08[row][col] +
						zernike_um[9] * zernikeMatrix_09[row][col] +
						zernike_um[10] * zernikeMatrix_10[row][col] +
						zernike_um[11] * zernikeMatrix_11[row][col] +
						zernike_um[12] * zernikeMatrix_12[row][col] +
						zernike_um[13] * zernikeMatrix_13[row][col] +
						zernike_um[14] * zernikeMatrix_14[row][col] +
						zernike_um[15] * zernikeMatrix_15[row][col];
				}  // 到此为止，vector_zernike_um就用完了，因此，一定要弹出才可以

			write_2d_File("D:\\WorkSpace\\Matlab\\N1_Temp\\zernikeMatrix_recon.txt", zernikeMatrix_recon);


			// 二维数组转一维数组，为了排序进行计算PV和RMS
			int temp_counter = 0;
			for (int row = 0; row < 12; ++row)
			{
				for (int col = 0; col < 12; ++col)
				{
					// 提取光瞳内的数据
					if (sqrt(pow(xArray_Mode[row], 2) + pow(yArray_Mode[col], 2)) <= (instr_setup.pupil_dia_x_mm) / 2)
					{
						zernikeMatrix_recon_ParaCal[temp_counter] = zernikeMatrix_recon[row][col];
						++temp_counter;
					}

				}
			}



#pragma endregion 重建波前矩阵



#pragma region 波前统计参数

			// sort会重新按照由小到大的顺序重新覆盖zernikeMatrix_recon_ParaCal
			sort(zernikeMatrix_recon_ParaCal.begin(), zernikeMatrix_recon_ParaCal.end());
			int index_end = zernikeMatrix_recon_ParaCal.size() - 1;

			// 求均值
			wavefront_mean = 0;
			for (int index = 0; index < index_end + 1; ++index)
			{
				wavefront_mean = wavefront_mean + zernikeMatrix_recon_ParaCal[index];
			}
			wavefront_mean = wavefront_mean / 144;


			// PV值
			wavefront_diff = zernikeMatrix_recon_ParaCal[index_end] - zernikeMatrix_recon_ParaCal[0];

			// RMS值
			wavefront_rms = 0;
			for (int index = 0; index < index_end + 1; ++index)
			{
				wavefront_rms = wavefront_rms + pow(zernikeMatrix_recon_ParaCal[index], 2);
			}
			wavefront_rms = sqrt(wavefront_rms / (index_end - 1));


			// 显示PV值
			(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
			pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);
			// 显示RMS值
			(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
			pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);

#pragma endregion 波前统计参数



#pragma region 将数据发送给DM

			// 矩阵旋转功能
			// 初始化用于保存旋转后的数据二维向量
			init_2dVector(zernikeMatrix_recon_rotate, 12, 12);
			if (90 == angleRotate)  // 顺时针旋转90度，下面都是顺时针
			{
				MatrixRotate90_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (180 == angleRotate)
			{
				MatrixRotate180_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (270 == angleRotate)
			{
				MatrixRotate270_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (1 == angleRotate)   // 上下翻转
			{
				MatrixFlipUpDown_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (2 == angleRotate) // 左右翻转
			{
				MatrixFlipLeftRight_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (3 == angleRotate)  // 上下翻转后左右翻转
			{
				MatrixFlipUpDown_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
				MatrixFlipLeftRight_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else
			{
				// 默认
				MatrixRotate0_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}



			// 初始化一个用于中转的一维vector
			std::vector<double> zernikeMatrix_recon_1d(144);

			// 二维数据转为一维数据
			for (int i = 0; i < 12; ++i)
				for (int j = 0; j < 12; ++j)
					zernikeMatrix_recon_1d[i * 12 + j] = zernikeMatrix_recon_rotate[i][j];


			// 要删除4个元素
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin());
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 10);
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 130);
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 140);

			//将140个元素的一维vector转为数组, 删除元素之后的一维vector用于输出到文件
			double tempIncrease = 0;
			for (int i = 0; i < 140; ++i)
			{

				// P环节
				tempIncrease = zernikeMatrix_recon_1d[i] * 500 * pid_p;

				//if (tempIncrease > 50)
				//{
				//	tempIncrease = 50;
				//}
				//if (tempIncrease < -50)
				//{
				//	tempIncrease = -50;
				//}


				DM_PID_P[i] = DM_PID_P[i] + tempIncrease;
				// 发给变形镜  
				zernikeMatrix_recon_array[i] = DM_PID_P[i];
				
				//zernikeMatrix_recon_array[i] = tempIncrease + 1200;


				 //变形镜没有校准 用于比对zernike系数
				//zernikeMatrix_recon_array[i] = 0;

			}


			// 量程范围控制
			for (int index = 0; index < 140; ++index)
			{
				if (zernikeMatrix_recon_array[index] < 0)
				{
					zernikeMatrix_recon_array[index] = 0;
				}
				if (zernikeMatrix_recon_array[index] > 3000)
				{
					zernikeMatrix_recon_array[index] = 3000;
				}
			}


			P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
			aoSystemData->dDMDesired = zernikeMatrix_recon_array;
			int status = P_DM_SetSpatialFrame();

			write_2d_File("D:\\WorkSpace\\Matlab\\N1_Temp\\send2DMflip.txt", zernikeMatrix_recon_rotate);



			// 选择是否显示执行量(PID算法)
			float temp;
			if (showExecuDist->GetCheck() == 1)
			{

				for (int k_index = 1; k_index < 11; ++k_index)
				{
					temp = zernikeMatrix_recon_array[k_index - 1];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
				for (int k_index = 12; k_index < 132; ++k_index)
				{
					temp = zernikeMatrix_recon_array[k_index - 2];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
				for (int k_index = 133; k_index < 143; ++k_index)
				{
					temp = zernikeMatrix_recon_array[k_index - 3];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
			}






#pragma endregion 将数据发送给DM



			if (pW->ptr_MiscSettingDlg->m_Check_SubDlg_TimeSetter.GetCheck() == 1)  // 选择是否进行计时
			{

				do
				{

#pragma region 计时器结束

					LARGE_INTEGER nStopCounter_test;
					::QueryPerformanceCounter(&nStopCounter_test);
					nTime_test = 1000 * ((double)nStopCounter_test.QuadPart - (double)nStartCounter_test.QuadPart) / (double)nFrequency_test.QuadPart;    // 单位 ms

					//显示计时器
					pW->m_Edit_Sta_Time.Format(_T("%lf"), nTime_test);
					pW->SetDlgItemText(IDC_EDIT_STA_TIME, pW->m_Edit_Sta_Time);

#pragma endregion 计时器结束


				} while (nTime_test < timerSetterInterval);


#pragma region 帧率显示

				//-----------------------------------------//
				// 帧率---终止部分
				::QueryPerformanceCounter(&nStopCounter_2nd);
				// 时间间隔，单位s
				t_interval_2nd = (double)(nStopCounter_2nd.QuadPart - nStartCounter_2nd.QuadPart) / (double)nFrequency_2nd.QuadPart;
				frameRate = (double)1 / t_interval_2nd;  // WFS的刷新频率，也是闭环的频率，单位Hz
				pW->m_Edit_Sta_Frame.Format(_T("%lf"), frameRate);
				pW->SetDlgItemText(IDC_EDIT_STA_FRAME, pW->m_Edit_Sta_Frame);
				//-----------------------------------------//

#pragma endregion 帧率显示



			}
			else
			{

#pragma region 计时器结束

				LARGE_INTEGER nStopCounter_test;
				::QueryPerformanceCounter(&nStopCounter_test);
				nTime_test = 1000 * ((double)nStopCounter_test.QuadPart - (double)nStartCounter_test.QuadPart) / (double)nFrequency_test.QuadPart;    // 单位 ms

				//显示计时器
				pW->m_Edit_Sta_Time.Format(_T("%lf"), nTime_test);
				pW->SetDlgItemText(IDC_EDIT_STA_TIME, pW->m_Edit_Sta_Time);

#pragma endregion 计时器结束


#pragma region 帧率显示

				//-----------------------------------------//
				// 帧率---终止部分
				::QueryPerformanceCounter(&nStopCounter_2nd);
				// 时间间隔，单位s
				t_interval_2nd = (double)(nStopCounter_2nd.QuadPart - nStartCounter_2nd.QuadPart) / (double)nFrequency_2nd.QuadPart;
				frameRate = (double)1 / t_interval_2nd;  // WFS的刷新频率，也是闭环的频率，单位Hz
				pW->m_Edit_Sta_Frame.Format(_T("%lf"), frameRate);
				pW->SetDlgItemText(IDC_EDIT_STA_FRAME, pW->m_Edit_Sta_Frame);
				//-----------------------------------------//

#pragma endregion 帧率显示


			}



			// 释放未旋转的二维向量
			release_2dVector(zernikeMatrix_recon, 12);
			// 一旦用完zernikeMatrix_recon_rotate，立即弹出全部数据
			release_2dVector(zernikeMatrix_recon_rotate, 12);


		}  // 闭环while结束

	}// if结束，PID算法结束

#pragma endregion PID算法


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region 梯度算法

	// 选择梯度算法
	if (chooseAlgoIndex == 1)
	{


#pragma region 线程中的局部变量

		// 几个指向对话框的指针
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

		// 与绘图有关的变量
		uchar image2DBuf[480][480];  // 二维形式
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));  // 显示图像
		CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));  // 显示脱靶量
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));


		// 评价函数值
		double meritFunctionValue = 100;			// 当前循环的评价函数值
		double meritFunctionValueAdd = 0;		// 给变形镜施加“加随机矩阵”后的评价函数值
		double meritFunctionValueMinus = 0;		// 给变形镜施加“减随机矩阵”后的评价函数值


		int NAN_counter = 0; // 计算NAN数据的个数

		// 用于计算帧率的时间变量
		double t_interval_2nd = 0; // 循环所用时间
		LARGE_INTEGER nStartCounter_2nd;  // 开始计算次数
		LARGE_INTEGER nFrequency_2nd;   // 每秒次数
		LARGE_INTEGER nStopCounter_2nd;  // 终止计算次数
		double frameRate = 0;  // 帧率



		// 以脱靶量作为评价函数，要计算光瞳
		// WFS的物理坐标，子孔径的pitch为150um=0.15mm，480x480分辨率下为29x29个子孔径
		float xArray_29[29];
		float yArray_29[29];
		for (int i = 0; i < 29; ++i)
			xArray_29[i] = -2.1 + i * 0.15;
		for (int i = 0; i < 29; ++i)
			yArray_29[i] = -2.1 + i * 0.15;
		// 计算光瞳矩阵
		float pupil_deviation[29][29];
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{

				pupil_deviation[row][col] = (float)((sqrt(pow(xArray_29[row], 2) + pow(yArray_29[col], 2)) <= instr_setup.pupil_dia_x_mm / 2) ? 1 : 0);

			}
		}

		// 用于存储光瞳限制的deviation矩阵
		float deviation_x_pupil[29][29];
		float deviation_y_pupil[29][29];




#pragma endregion 线程中的局部变量




		// 最终执行量的初始值
		for (int index = 0; index < 140; ++index)
		{
			zernikeMatrix_recon_array_DEFAULT[index] = 1200;
		}





		// 闭环循环
		CloseLoopFlag = TRUE;
		while (CloseLoopFlag)
		{

			// 显示三个评价函数值
			CString showMerit;

			showMerit.Format(_T("%lf"), meritFunctionValueAdd);
			pW->SetDlgItemText(IDC_STATIC_SHOW1, showMerit);

			showMerit.Format(_T("%lf"), meritFunctionValueMinus);
			pW->SetDlgItemText(IDC_STATIC_SHOW2, showMerit);

			showMerit.Format(_T("%lf"), meritFunctionValue);
			pW->SetDlgItemText(IDC_STATIC_SHOW3, showMerit);



#pragma region 计时器开始
			//新计时器开始
			LARGE_INTEGER nStartCounter_test;
			LARGE_INTEGER nFrequency_test;
			double nTime_test = 0; // 记录时间

			::QueryPerformanceCounter(&nStartCounter_test);
			::QueryPerformanceFrequency(&nFrequency_test);
#pragma endregion 计时器开始



#pragma region 帧率显示
			// 帧率---起始部分
			::QueryPerformanceCounter(&nStartCounter_2nd);
			::QueryPerformanceFrequency(&nFrequency_2nd);

#pragma endregion 帧率显示




			// 初始化一个用于中转的一维vector，这种形式的初始化不用释放,每次循环都要初始化一次，因为每次循环都要删除4个元素
			std::vector<double> zernikeMatrix_recon_1d_add(144);  //因为会删掉四个元素，所以要给加减操作分别设置一个
			std::vector<double> zernikeMatrix_recon_1d_minus(144);  //因为会删掉四个元素，所以要给加减操作分别设置一个
			std::vector<double> zernikeMatrix_recon_1d_default(144);  // 默认操作


			// 随机矩阵     (double)rand() / 32768.0 - 0.5   范围 -0.5 0.5
			// 每次while循环中，随机矩阵保持不变
			for (int index = 0; index < 140; ++index)
			{
				randomMatrix[index] = ((double)rand() / 32768.0 - 0.5) * 50;
			}


			// 一次while循环包括两次计算，第一次为加操作，第二次为减操作
			// 通过遍历两次操作，获取评价函数值，用于下一步的判决
			for (int count = 0; count < 2; ++count)
			{

#pragma region 加操作

				if (count == 0)  // 减随机变量
				{


#pragma region 整理发送给变形镜

					for (int index = 0; index < 140; ++index)
					{
						zernikeMatrix_recon_array_ADD[index] = zernikeMatrix_recon_array_DEFAULT[index] + randomMatrix[index];
					}

					//## 这里要有一个转换，将vector转换为数组
					P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
					aoSystemData->dDMDesired = zernikeMatrix_recon_array_ADD;
					int status = P_DM_SetSpatialFrame();

#pragma endregion 整理发送给变形镜


#pragma region 变形镜等待时间

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
					} while (nTime_dmwait < 10);


#pragma endregion 变形镜等待时间




#pragma region 波前探测
					// 普通模式获取质心位置
					WFS_TakeSpotfieldImage(instr.handle);
					// 计算质心位置
					WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);


#pragma region 显示子孔径图像

					if (subApertureImageSwitch->GetCheck() == 1)
					{

						// 将图像刷入内存
						WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
						// 将图像由一维转为二维，下面的转换经过验证是正确的
						for (int row = 0; row < 480; ++row)
							for (int col = 0; col < 480; ++col)
							{
								image2DBuf[row][col] = imageBuf[480 * row + col];
							}
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
					else
					{
						if (CMOSImageFlag == TRUE)
						{
							pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
						}
						CMOSImageFlag = FALSE;  // 设置标志
					}


#pragma endregion 显示子孔径图像



					// 计算脱靶量
					WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
					// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
					WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);


#pragma region 复杂的无效数据处理办法

					for (int row = 1; row < 28; ++row)  // 空出最上下两行
					{
						for (int col = 1; col < 28; ++col) // 空出最左右两列
						{

							// 判断x方向
							if (_isnan(deviation_x[row][col]))
							{
								++NAN_counter;
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
									str_showerror = "警报：梯度算法  加操作  X方向脱靶量  过多无效数据！ 无效数据已置零！";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "警报：梯度算法  加操作  X方向脱靶量  无效数据已被插值";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}


							}  // x方向结束



							// 判断y方向
							if (_isnan(deviation_y[row][col]))
							{
								++NAN_counter;

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
									str_showerror = "警报：梯度算法  加操作  Y方向脱靶量  过多无效数据！ 无效数据已置零！";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "警报：梯度算法  加操作  Y方向脱靶量  无效数据已被插值";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}  // 对中心无效值插值结束

							} // y方向结束

						}
					}  // 无效值遍历结束

#pragma endregion 复杂的无效数据处理办法


					//
					//#pragma region 简单处理无效数据的方法
					//
					//					NAN_counter = 0;
					//					for (int row = 0; row < 29; ++row)
					//					{
					//						for (int col = 0; col < 29; ++col)
					//						{
					//							if (_isnan(deviation_x[row][col]))
					//							{
					//								++NAN_counter; // 计数器加一
					//								FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
					//								str_showerror = "警报：梯度算法  加操作  X脱靶量  中出现NAN数据！";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//								deviation_x[row][col] = 0;
					//
					//							}
					//							if (_isnan(deviation_y[row][col]))
					//							{
					//								++NAN_counter; // 计数器加一
					//								FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
					//								str_showerror = "警报：梯度算法  加操作  Y脱靶量  中出现NAN数据！";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//
					//								deviation_y[row][col] = 0;
					//							}
					//						}
					//					}  // 无效值遍历结束
					//
					//#pragma endregion 简单处理无效数据的方法
					//


					// 显示无效点的个数
					(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
					pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);




					//根据脱靶量重建波前,wavefront数组的单位是um
					WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);


					// 在梯度算法中，使用直接积分法获得波前，但是不排除其中有无效值，如果出现无效值会导致根据波前信息计算的评价函数也会是无效值
					// 因此，在这里，对于无效值要做置零处理
					for (int row = 0; row < 29; ++row) // 因为不需要插值，因此这里的遍历范围是全部的子孔径
					{
						for (int col = 0; col < 29; ++col)
						{
							if (_isnan(wavefront[row][col]))
							{
								wavefront[row][col] = 0;
							}
						}
					} // 无效值遍历结束



					// 波前统计信息
					WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min_add, &wavefront_max_add,
						&wavefront_diff_add, &wavefront_mean_add, &wavefront_rms_add, &wavefront_weighted_rms_add);


#pragma endregion 波前探测


#pragma region 计算评价函数

					double meritTemp = 0;
					for (int row = 0; row < 29; ++row)
					{
						for (int col = 0; col < 29; ++col)
						{

							deviation_x_pupil[row][col] = deviation_x[row][col] * pupil_deviation[row][col];
							deviation_y_pupil[row][col] = deviation_y[row][col] * pupil_deviation[row][col];

							if (_isnan(deviation_x_pupil[row][col]))
							{
								deviation_x_pupil[row][col] = 0;
							}
							if (_isnan(deviation_y_pupil[row][col]))
							{
								deviation_y_pupil[row][col] = 0;
							}

							meritTemp = meritTemp + pow(deviation_x_pupil[row][col], 2) + pow(deviation_y_pupil[row][col], 2);

						}
					}
					meritFunctionValueAdd = sqrt(meritTemp);


#pragma endregion 计算评价函数

				}//if结束  加操作结束

#pragma endregion 加操作


#pragma region 减操作


				if (count == 1)
				{

#pragma region 整理发送给变形镜


					for (int index = 0; index < 140; ++index)
					{
						zernikeMatrix_recon_array_MINUS[index] = zernikeMatrix_recon_array_DEFAULT[index] - randomMatrix[index];
					}



					//## 这里要有一个转换，将vector转换为数组
					P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
					aoSystemData->dDMDesired = zernikeMatrix_recon_array_MINUS;
					int status = P_DM_SetSpatialFrame();

#pragma endregion 整理发送给变形镜


#pragma region 变形镜等待时间

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
					} while (nTime_dmwait < 10);


#pragma endregion 变形镜等待时间


#pragma region 波前探测
					// 普通模式获取质心位置
					WFS_TakeSpotfieldImage(instr.handle);
					// 计算质心位置
					WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);

					// 计算脱靶量
					WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
					// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
					WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);





#pragma region 复杂的无效数据处理办法

					for (int row = 1; row < 28; ++row)  // 空出最上下两行
					{
						for (int col = 1; col < 28; ++col) // 空出最左右两列
						{

							// 判断x方向
							if (_isnan(deviation_x[row][col]))
							{
								++NAN_counter;
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
									str_showerror = "警报：梯度算法  减操作  X方向脱靶量  过多无效数据！ 无效数据已置零！";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "警报：梯度算法  减操作  X方向脱靶量  无效数据已被插值";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}


							}  // x方向结束



							// 判断y方向
							if (_isnan(deviation_y[row][col]))
							{
								++NAN_counter;

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
									str_showerror = "警报：梯度算法  减操作  Y方向脱靶量  过多无效数据！ 无效数据已置零！";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "警报：梯度算法  减操作  Y方向脱靶量  无效数据已被插值";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}  // 对中心无效值插值结束

							} // y方向结束

						}
					}  // 无效值遍历结束

#pragma endregion 复杂的无效数据处理办法


					//
					//#pragma region 简单处理无效数据的方法
					//
					//					NAN_counter = 0;
					//					for (int row = 0; row < 29; ++row)
					//					{
					//						for (int col = 0; col < 29; ++col)
					//						{
					//							if (_isnan(deviation_x[row][col]))
					//							{
					//								++NAN_counter; // 计数器加一
					//								FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
					//								str_showerror = "警报：梯度算法  减操作  X脱靶量  中出现NAN数据！";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//								deviation_x[row][col] = 0;
					//
					//							}
					//							if (_isnan(deviation_y[row][col]))
					//							{
					//								++NAN_counter; // 计数器加一
					//								FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
					//								str_showerror = "警报：梯度算法  减操作  Y脱靶量  中出现NAN数据！";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//
					//								deviation_y[row][col] = 0;
					//							}
					//						}
					//					}  // 无效值遍历结束
					//
					//#pragma endregion 简单处理无效数据的方法
					//


					// 显示无效点的个数
					(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
					pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);





					//根据脱靶量重建波前,wavefront数组的单位是um
					WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);


					// 在梯度算法中，使用直接积分法获得波前，但是不排除其中有无效值，如果出现无效值会导致根据波前信息计算的评价函数也会是无效值
					// 因此，在这里，对于无效值要做置零处理
					for (int row = 0; row < 29; ++row) // 因为不需要插值，因此这里的遍历范围是全部的子孔径
					{
						for (int col = 0; col < 29; ++col)
						{
							if (_isnan(wavefront[row][col]))
							{
								wavefront[row][col] = 0;
							}
						}
					} // 无效值遍历结束


					// 减操作的波前统计信息
					WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min_minus, &wavefront_max_minus,
						&wavefront_diff_minus, &wavefront_mean_minus, &wavefront_rms_minus, &wavefront_weighted_rms_minus);

#pragma endregion 波前探测


#pragma region 计算评价函数

					double meritTemp = 0;
					for (int row = 0; row < 29; ++row)
					{
						for (int col = 0; col < 29; ++col)
						{

							deviation_x_pupil[row][col] = deviation_x[row][col] * pupil_deviation[row][col];
							deviation_y_pupil[row][col] = deviation_y[row][col] * pupil_deviation[row][col];

							if (_isnan(deviation_x_pupil[row][col]))
							{
								deviation_x_pupil[row][col] = 0;
							}
							if (_isnan(deviation_y_pupil[row][col]))
							{
								deviation_y_pupil[row][col] = 0;
							}

							meritTemp = meritTemp + pow(deviation_x_pupil[row][col], 2) + pow(deviation_y_pupil[row][col], 2);

						}
					}
					meritFunctionValueMinus = sqrt(meritTemp);

#pragma endregion 计算评价函数


				}//if结束 减操作结束

#pragma endregion 减操作


				//
				//#pragma region 默认操作
				//				if (count == 2)
				//				{
				//
				//
				//
				//#pragma region 整理发送给变形镜
				//
				//
				//					//## 这里要有一个转换，将vector转换为数组
				//					P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
				//					aoSystemData->dDMDesired = zernikeMatrix_recon_array_DEFAULT;
				//					int status = P_DM_SetSpatialFrame();
				//
				//#pragma endregion 整理发送给变形镜
				//
				//
				//#pragma region 变形镜等待时间
				//
				//					//新计时器开始
				//					LARGE_INTEGER nStartCounter_dmwait;
				//					LARGE_INTEGER nFrequency_dmwait;
				//					double nTime_dmwait = 0; // 记录时间
				//
				//					::QueryPerformanceCounter(&nStartCounter_dmwait);
				//					::QueryPerformanceFrequency(&nFrequency_dmwait);
				//
				//
				//					do
				//					{
				//						LARGE_INTEGER nStopCounter_dmwait;
				//						::QueryPerformanceCounter(&nStopCounter_dmwait);
				//						nTime_dmwait = 1000 * ((double)nStopCounter_dmwait.QuadPart - (double)nStartCounter_dmwait.QuadPart) / (double)nFrequency_dmwait.QuadPart;    // 单位 ms
				//					} while (nTime_dmwait < 10);
				//
				//
				//#pragma endregion 变形镜等待时间
				//
				//
				//#pragma region 波前探测
				//					// 普通模式获取质心位置
				//					WFS_TakeSpotfieldImage(instr.handle);
				//					// 计算质心位置
				//					WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
				//
				//					// 计算脱靶量
				//					WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
				//					// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
				//					WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);
				//
				//
				//#pragma region 复杂的无效数据处理办法
				//
				//					NAN_counter = 0;
				//					for (int row = 1; row < 28; ++row)  // 空出最上下两行
				//					{
				//						for (int col = 1; col < 28; ++col) // 空出最左右两列
				//						{
				//
				//							// 判断x方向
				//							if (_isnan(deviation_x[row][col]))
				//							{
				//								++NAN_counter;
				//								// 排列方式
				//								//  x x x
				//								//  x o x
				//								//  x x x
				//
				//								if (_isnan(deviation_x[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
				//									_isnan(deviation_x[row - 1][col]) &&
				//									_isnan(deviation_x[row - 1][col + 1]) &&
				//									_isnan(deviation_x[row][col - 1]) &&
				//									_isnan(deviation_x[row][col + 1]) &&
				//									_isnan(deviation_x[row + 1][col - 1]) &&
				//									_isnan(deviation_x[row + 1][col]) &&
				//									_isnan(deviation_x[row + 1][col + 1]))
				//								{
				//									str_showerror = "警报：梯度算法  默认操作  X方向脱靶量  过多无效数据！ 无效数据已置零！";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//									deviation_x[row][col] = 0;
				//								}
				//								else
				//								{
				//									// 排列方式
				//									//  x x x
				//									//  x o x
				//									//  x x x
				//
				//									int mean_counter = 0;  // 有效值个数
				//									float mean_value = 0;  // 有效值的和
				//
				//									if (!_isnan(deviation_x[row - 1][col - 1]))  // 上左
				//									{
				//										mean_value = mean_value + deviation_x[row - 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row - 1][col])) // 上中
				//									{
				//										mean_value = mean_value + deviation_x[row - 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row - 1][col + 1])) // 上右
				//									{
				//										mean_value = mean_value + deviation_x[row - 1][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row][col - 1])) // 中左
				//									{
				//										mean_value = mean_value + deviation_x[row][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row][col + 1])) // 中右
				//									{
				//										mean_value = mean_value + deviation_x[row][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row + 1][col - 1])) // 下左
				//									{
				//										mean_value = mean_value + deviation_x[row + 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row + 1][col]))  // 下中
				//									{
				//										mean_value = mean_value + deviation_x[row + 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row + 1][col + 1]))  // 下右
				//									{
				//										mean_value = mean_value + deviation_x[row + 1][col + 1];
				//										mean_counter++;
				//									}
				//
				//									deviation_x[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值
				//
				//									str_showerror = "警报：梯度算法  默认操作  X方向脱靶量  无效数据已被插值";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//								}
				//
				//
				//							}  // x方向结束
				//
				//
				//
				//							// 判断y方向
				//							if (_isnan(deviation_y[row][col]))
				//							{
				//								++NAN_counter;
				//
				//								// 排列方式
				//								//  x x x
				//								//  x o x
				//								//  x x x
				//
				//								if (_isnan(deviation_y[row - 1][col - 1]) &&   // 如果无效点周围8各点都是无效值，那么此点脱靶量置零
				//									_isnan(deviation_y[row - 1][col]) &&
				//									_isnan(deviation_y[row - 1][col + 1]) &&
				//									_isnan(deviation_y[row][col - 1]) &&
				//									_isnan(deviation_y[row][col + 1]) &&
				//									_isnan(deviation_y[row + 1][col - 1]) &&
				//									_isnan(deviation_y[row + 1][col]) &&
				//									_isnan(deviation_y[row + 1][col + 1]))
				//								{
				//									str_showerror = "警报：梯度算法  默认操作  Y方向脱靶量  过多无效数据！ 无效数据已置零！";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//									deviation_y[row][col] = 0;
				//								} // 强制置零结束
				//								else
				//								{
				//									// 排列方式
				//									//  x x x
				//									//  x o x
				//									//  x x x
				//
				//									int mean_counter = 0;  // 有效值个数
				//									float mean_value = 0;  // 有效值的和
				//
				//									if (!_isnan(deviation_y[row - 1][col - 1]))  // 上左
				//									{
				//										mean_value = mean_value + deviation_y[row - 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row - 1][col])) // 上中
				//									{
				//										mean_value = mean_value + deviation_y[row - 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row - 1][col + 1])) // 上右
				//									{
				//										mean_value = mean_value + deviation_y[row - 1][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row][col - 1])) // 中左
				//									{
				//										mean_value = mean_value + deviation_y[row][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row][col + 1])) // 中右
				//									{
				//										mean_value = mean_value + deviation_y[row][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row + 1][col - 1])) // 下左
				//									{
				//										mean_value = mean_value + deviation_y[row + 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row + 1][col]))  // 下中
				//									{
				//										mean_value = mean_value + deviation_y[row + 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row + 1][col + 1]))  // 下右
				//									{
				//										mean_value = mean_value + deviation_y[row + 1][col + 1];
				//										mean_counter++;
				//									}
				//
				//									deviation_y[row][col] = mean_value / mean_counter;  // 利用无效值周围的有效值的平均值给无效值赋值
				//
				//									str_showerror = "警报：梯度算法  默认操作  Y方向脱靶量  无效数据已被插值";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//								}  // 对中心无效值插值结束
				//
				//							} // y方向结束
				//
				//						}
				//					}  // 无效值遍历结束
				//
				//#pragma endregion 复杂的无效数据处理办法
				//
				//					//
				//					//#pragma region 简单处理无效数据的方法
				//					//
				//					//					NAN_counter = 0;
				//					//					for (int row = 0; row < 29; ++row)
				//					//					{
				//					//						for (int col = 0; col < 29; ++col)
				//					//						{
				//					//							if (_isnan(deviation_x[row][col]))
				//					//							{
				//					//								++NAN_counter; // 计数器加一
				//					//								FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
				//					//								str_showerror = "警报：梯度算法  默认操作  X脱靶量  中出现NAN数据！";
				//					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//					//
				//					//								deviation_x[row][col] = 0;
				//					//
				//					//							}
				//					//							if (_isnan(deviation_y[row][col]))
				//					//							{
				//					//								++NAN_counter; // 计数器加一
				//					//								FLAG_NAN = 1;  // 将标志位赋值为1，表示存在NAN数据
				//					//								str_showerror = "警报：梯度算法  默认操作  Y脱靶量  中出现NAN数据！";
				//					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//					//
				//					//
				//					//								deviation_y[row][col] = 0;
				//					//							}
				//					//						}
				//					//					}  // 无效值遍历结束
				//					//
				//					//#pragma endregion 简单处理无效数据的方法
				//					//
				//
				//
				//					// 显示无效点的个数
				//					(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
				//					pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);
				//
				//
				//
				//
				//
				//
				//					//根据脱靶量重建波前,wavefront数组的单位是um
				//					WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);
				//
				//
				//					// 在梯度算法中，使用直接积分法获得波前，但是不排除其中有无效值，如果出现无效值会导致根据波前信息计算的评价函数也会是无效值
				//					// 因此，在这里，对于无效值要做置零处理
				//					for (int row = 0; row < 29; ++row) // 因为不需要插值，因此这里的遍历范围是全部的子孔径
				//					{
				//						for (int col = 0; col < 29; ++col)
				//						{
				//							if (_isnan(wavefront[row][col]))
				//							{
				//								wavefront[row][col] = 0;
				//							}
				//						}
				//					} // 无效值遍历结束
				//
				//
				//
				//					// 减操作的波前统计信息
				//					WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
				//						&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);
				//
				//#pragma endregion 波前探测
				//
				//
				//#pragma region 计算评价函数
				//
				//
				//					double meritTemp = 0;
				//					for (int row = 0; row < 29; ++row)
				//					{
				//						for (int col = 0; col < 29; ++col)
				//						{
				//							deviation_x_pupil[row][col] = deviation_x[row][col] * pupil_deviation[row][col];
				//							deviation_y_pupil[row][col] = deviation_y[row][col] * pupil_deviation[row][col];
				//
				//							meritTemp = meritTemp + pow(deviation_x_pupil[row][col], 2) + pow(deviation_y_pupil[row][col], 2);
				//
				//						}
				//					}
				//					meritFunctionValue = sqrt(meritTemp);
				//
				//
				//#pragma endregion 计算评价函数
				//
				//
				//				}
				//
				//
				//
				//
				//
				//
				//#pragma endregion 默认操作
				//


			}//for结束


#pragma region 判决显示部分

			// 判断部分，选择最终向哪个方向进化，从而确定下一次while循环的起始执行量值
			// 做一些显示任务
			if (meritFunctionValueAdd < (meritFunctionValue))
			{
				meritFunctionValue = meritFunctionValueAdd;

				// 将加操作的执行量作为下次循环的初始值
				for (int index = 0; index < 140; ++index)
				{
					zernikeMatrix_recon_array_DEFAULT[index] = zernikeMatrix_recon_array_ADD[index];
				}

			}
			else if (meritFunctionValueMinus < (meritFunctionValue))
			{

				meritFunctionValue = meritFunctionValueMinus;
				// 将减操作的执行量作为下次循环的初始值
				for (int index = 0; index < 140; ++index)
				{
					zernikeMatrix_recon_array_DEFAULT[index] = zernikeMatrix_recon_array_MINUS[index];
				}

			}


#pragma endregion 判决显示部分


			// 显示减操作的评价函数值
			(pW->m_Edit_ShowMerit).Format(_T("%lf"), meritFunctionValue);
			pW->SetDlgItemTextW(IDC_EDIT_SHOWMERIT, pW->m_Edit_ShowMerit);
			// 显示减操作的波前统计信息
			(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff_minus);
			pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);
			(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms_minus);
			pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);


			// 选择是否显示执行量(梯度算法)
			float temp;
			if (showExecuDist->GetCheck() == 1)
			{

				for (int k_index = 1; k_index < 11; ++k_index)
				{
					temp = zernikeMatrix_recon_array_DEFAULT[k_index - 1];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
				for (int k_index = 12; k_index < 132; ++k_index)
				{
					temp = zernikeMatrix_recon_array_DEFAULT[k_index - 2];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
				for (int k_index = 133; k_index < 143; ++k_index)
				{
					temp = zernikeMatrix_recon_array_DEFAULT[k_index - 3];
					(pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
					pW->ptr_DeformMirrorDlg->SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, pW->ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

				}
			}




#pragma region 新增计时器开始
			//新计时器开始
			LARGE_INTEGER nStartCounter_wait;
			LARGE_INTEGER nFrequency_wait;
			double nTime_wait = 0; // 记录时间

			::QueryPerformanceCounter(&nStartCounter_wait);
			::QueryPerformanceFrequency(&nFrequency_wait);
#pragma endregion 新增计时器开始


			if (pW->ptr_MiscSettingDlg->m_Check_SubDlg_TimeSetter.GetCheck() == 1)  // 选择是否进行计时
			{

				do
				{

#pragma region 新增计时器结束

					LARGE_INTEGER nStopCounter_wait;
					::QueryPerformanceCounter(&nStopCounter_wait);
					nTime_wait = 1000 * ((double)nStopCounter_wait.QuadPart - (double)nStartCounter_wait.QuadPart) / (double)nFrequency_wait.QuadPart;    // 单位 ms

					//显示计时器
					pW->m_Edit_Show_NewTimer.Format(_T("%lf"), nTime_wait);
					pW->SetDlgItemText(IDC_EDIT_SHOW_NEWTIMER, pW->m_Edit_Show_NewTimer);

#pragma endregion 新增计时器结束

				} while (nTime_wait < timerSetterInterval);



			}
			else
			{
				// 没有定时，不执行
			}




#pragma region 计时器结束

			LARGE_INTEGER nStopCounter_test;
			::QueryPerformanceCounter(&nStopCounter_test);
			nTime_test = 1000 * ((double)nStopCounter_test.QuadPart - (double)nStartCounter_test.QuadPart) / (double)nFrequency_test.QuadPart;    // 单位 ms

			//显示计时器
			pW->m_Edit_Sta_Time.Format(_T("%lf"), nTime_test);
			pW->SetDlgItemText(IDC_EDIT_STA_TIME, pW->m_Edit_Sta_Time);

#pragma endregion 计时器结束


#pragma region 帧率显示

			//-----------------------------------------//
			// 帧率---终止部分
			::QueryPerformanceCounter(&nStopCounter_2nd);
			// 时间间隔，单位s
			t_interval_2nd = (double)(nStopCounter_2nd.QuadPart - nStartCounter_2nd.QuadPart) / (double)nFrequency_2nd.QuadPart;
			frameRate = (double)1 / t_interval_2nd;  // WFS的刷新频率，也是闭环的频率，单位Hz
			pW->m_Edit_Sta_Frame.Format(_T("%lf"), frameRate);
			pW->SetDlgItemText(IDC_EDIT_STA_FRAME, pW->m_Edit_Sta_Frame);
			//-----------------------------------------//

#pragma endregion 帧率显示


		}  // while循环结束



	}  // if结束，梯度算法结束

#pragma endregion 梯度算法


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region 直接斜率

	// 直接斜率法，需要预处理数据
	if (chooseAlgoIndex == 2)
	{

#pragma region 载入预处理数据
		
		// 注意，不需要压栈，也就不需要弹出栈


		// 将Matlab计算好的lsqA与eff_picked读入
		// 例如，有效子孔径点个数为609,那么，lsqA的维数就应该是140*610
		lsqA = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\lsqA.txt");
		// 由于eff_picked要作为索引项，因此要将其转换为const int类型
		// 例如，有效子孔径点个数为609，eff_picked当时初始化为841*2的矩阵，第610个为[0,0]，611起到后面都是未定义的值，在这之前是有效子孔径的位置信息
		eff_picked = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\eff_picked.txt");
		// 注意eff_picked.size()表示行数，eff_picked[0].size()表示列数
		// 例如eff_picked有609个子孔径点的索引号，那么就是609x2的一个矩阵，那么eff_picked.size()=609，eff_picked[0].size()=2

		//// eff_picked做索引号举例如下：
		//// MyMat_double类型的数据做索引
		//lsqA[eff_picked[2][0]][eff_picked[2][1]];
		//// vector<vector<double>>类型的数据做索引和上面是一样的
		//zernikeMatrix_15[eff_picked[2][0]][eff_picked[2][1]];
		//// float(POD)类型数据就要强转了！
		//wavefront[(int)eff_picked[2][0]][(int)eff_picked[2][1]];

#pragma endregion 载入预处理数据


#pragma region 线程中的局部变量

		// 几个指向对话框的指针
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

		// 与绘图有关的变量
		uchar image2DBuf[480][480];  // 二维形式


		// 几个开关,checkbox用作开关
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
		CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));

		std::vector<double> lsqy;  // lsqx=lsqA*lsqy
		lsqy.resize(610);  // 给容器分配内存空间
		int row_effsub;  // 有效点的行索引号
		int col_effsub;  // 有效点的列索引号

		double zernikeMatrix_recon_array_ACEMETHOD[140];   // 保存最小二乘法计算的执行量


#pragma endregion 线程中的局部变量




		// 闭环
		CloseLoopFlag = TRUE;
		while (CloseLoopFlag)
		{

#pragma region 计算质心位置

			// 第一步：计算质心位置
			// 普通模式获取质心位置
			WFS_TakeSpotfieldImage(instr.handle);
			// 计算质心位置
			WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);


#pragma region 显示子孔径图像

			if (subApertureImageSwitch->GetCheck() == 1)
			{

				// 将图像刷入内存
				WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
				// 将图像由一维转为二维，下面的转换经过验证是正确的
				for (int row = 0; row < 480; ++row)
					for (int col = 0; col < 480; ++col)
					{
						image2DBuf[row][col] = imageBuf[480 * row + col];
					}

				m_img = cvCreateImageHeader(cvSize(480, 480), 8, 1);
				cvSetData(m_img, image2DBuf, 480); // 这一句申请了内存，应该是通过cvReleaseImageHeader释放的


				// 用于在TAB控件上子孔径标签页上的对话框上的pic控件显示子孔径的实时图像
				// ptr_SubApertureImageDlg是pW的成员
				pW->ptr_SubApertureImageDlg->ShowSubApertuerImageFrame();

				// 设置标志
				if (CMOSImageFlag == FALSE)
					CMOSImageFlag = TRUE;

			}
			else
			{
				if (CMOSImageFlag == TRUE)
				{
					pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
				}
				CMOSImageFlag = FALSE;  // 设置标志
			}


#pragma endregion 显示子孔径图像



#pragma endregion 计算质心位置


#pragma region 计算脱靶量

			// 第二步：计算脱靶量
			// 计算脱靶量
			WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
			// 获取脱靶量，用于下面转换为斜坡数据，这里需要进行单位转换，WFS_GetSpotDeviations得到的单位是pixels
			WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);


			// 记录重排前的数据
// 			fp = fopen("D:\\externLib\\AOS\\Output\\DEBUG_ORIGIN_deviation_x.txt", "w");
// 			if (!fp)
// 			{
// 				::MessageBox(NULL, _T("无法打开WFS_SpotCentroids_X文件 ！"), _T("写入状态"), MB_OK);
// 				return -1;
// 			}
// 
// 			for (int i = 0; i < 29; ++i)
// 			{
// 				for (int j = 0; j < 29; ++j)
// 				{
// 					fprintf(fp, "%f", deviation_x[i][j]);
// 					fprintf(fp, "\t\t");
// 				}
// 				fputc('\n', fp);
// 			}
// 
// 			fclose(fp);
			


#pragma endregion 计算脱靶量



#pragma region 波前统计参数

			WFS_CalcWavefront(instr.handle, instr_setup.wavefront_type, instr_setup.pupil_circular, *wavefront);
			WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
				&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);

			// 显示PV值
			(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
			pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);

			// 显示RMS值
			(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
			pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);


#pragma endregion 波前统计参数



#pragma region 重排矩阵

			int subapture_counter = 0; // 每次循环计数器都要置零
			// 按照与lsqA一致的有效点顺序压栈

			for (int subapture_counter = 0; subapture_counter < 305; ++subapture_counter)
			{

				row_effsub = eff_picked[subapture_counter][0] - 1;
				col_effsub = eff_picked[subapture_counter][1] - 1;
				// 将脱靶量的单位从pixel转为nm，一个像素大小9.9um
				lsqy[2 * subapture_counter] = deviation_x[row_effsub][col_effsub];  // 先压入X方向
				lsqy[2 * subapture_counter + 1] = deviation_y[row_effsub][col_effsub];  // 再压入y方向

			}
			// 记录重排之后的数据
// 			write_1d_File("D:\\externLib\\AOS\\Output\\DEBUG_REARRANGE_deviation_x.txt",lsqy);



#pragma endregion 重排矩阵


#pragma region 计算执行量

			double sum_temp = 0;
			std::vector <int>::size_type row_num;
			std::vector <int>::size_type col_num;
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



			// 记录执行量
			fp = fopen("D:\\externLib\\AOS\\Output\\DEBUG_DM_Stroke.txt", "w");
			if (!fp)
			{
				::MessageBox(NULL, _T("无法打开WFS_ZernikeCoeff文件 ！"), _T("Writing Status"), MB_OK);
				return -1;
			}

			for (int i = 0; i < 140 + 1; ++i)
			{
				fprintf(fp, "%f", zernikeMatrix_recon_array_ACEMETHOD[i]);
				fputc('\n', fp);
			}
			fclose(fp);



#pragma endregion 计算执行量



#pragma region 发给变形镜

			//## 这里要有一个转换，将vector转换为数组
			P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
			aoSystemData->dDMDesired = zernikeMatrix_recon_array_ACEMETHOD;
			int status = P_DM_SetSpatialFrame();

#pragma endregion 发给变形镜






#pragma region 等待时间

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
			} while (nTime_dmwait < 2000);


#pragma endregion 等待时间



		}  // 闭环结束





	} // if结束，直接斜率法结束



#pragma endregion 直接斜率
	  


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 退出线程
	return 0;

} // 线程结束

////////////////////////////////////////////////////////////////////////////////////////////////////////////




#pragma region //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数（11个函数）
// 将当前计算的SPOT中心位置写入文件
int WFS_WriteSpotCentroids()
{
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WFS_WriteSpotDeviations()
{
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_SpotDeviations_X.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_SpotDeviations_X文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", deviation_x[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);


	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_SpotDeviations_Y.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_SpotDeviations_Y文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}
	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", deviation_y[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WFS_WriteZernikeLsf()
{
	// 将Zernike系数写入文件
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_ZernikeCoeff.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_ZernikeCoeff文件 ！"), _T("Writing Status"), MB_OK);
		return -1;
	}

	for (int i = 0; i < MAX_ZERNIKE_MODES + 1; ++i)
	{
		fprintf(fp, "%f", zernike_um[i]);
		fputc('\n', fp);
	}
	fclose(fp);

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_Zernike_RMS_ROC.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_Zernike_RMS_ROC文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	fprintf(fp, "zernike_orders_rms_um：\n");

	for (int i = 0; i < MAX_ZERNIKE_ORDERS + 1; ++i)
	{
		fprintf(fp, "%f", zernike_orders_rms_um[i]);
		fputc('\n', fp);
	}


	fprintf(fp, "\n");
	fprintf(fp, "roc_mm： %lf", roc_mm);


	fclose(fp);

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 将当前zernike多项式得到的spot deviations拟合信息写入文件
int WFS_WriteCalcReconstrDeviations()
{
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 将spot deviations得到的波前信息写入文件
int WFS_WriteCalcWavefront()
{
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_CalcWavefront.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_CalcWavefront文件 ！"), _T("写入状态"), MB_OK);
	}

	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			fprintf(fp, "%f", wavefront[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 将波前的统计信息写入文件
int WFS_WriteCalcWavefrontStatistics()
{
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_CalcWavefrontStatistics.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开WFS_CalcWavefrontStatistics文件 ！"), _T("写入状态"), MB_OK);
		return -1;
	}

	fprintf(fp, "wavefront_min：  %lf \n", wavefront_min);
	fprintf(fp, "wavefront_max： %lf \n", wavefront_max);
	fprintf(fp, "wavefront_diff： %lf \n", wavefront_diff);
	fprintf(fp, "wavefront_mean： %lf \n", wavefront_mean);
	fprintf(fp, "wavefront_rms： %lf \n", wavefront_rms);
	fprintf(fp, "wavefront_weighted_rms： %lf \n", wavefront_weighted_rms);


	fclose(fp);

	return 0;
}


// 将当前的Zernike矩阵写入文件
int WFS_WriteZernikeMatrix()
{
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
	fp = fopen("D:\\externLib\\AOS\\Output\\DM_1DArray.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开DM_1DArray文件 ！"), _T("Writing Status"), MB_OK);
		return -1;
	}

	for (int i = 0; i < MAX_ZERNIKE_MODES + 1; ++i)
	{
		fprintf(fp, "%f", DM_Stroke_1D[i]);
		fputc('\n', fp);
	}
	fclose(fp);


}

#pragma endregion //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数




#pragma region mapping   // 这段代码要简化
////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


// 写入二维数据，第一次能够成功索引二维vector，挺不容易的！
int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out);

	std::vector<std::vector<double>>::iterator iter_row;		// 定义row方向的迭代器
	std::vector<double>::iterator iter_col;				// 定义col方向的迭代器


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



// 使用流的概念读取文件中的矩阵
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


int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col)
{
	std::vector<double> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// 重载版本
int init_2dVector(std::vector<std::vector<int>>&vectordata, const int row, const int col)
{
	std::vector<int> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// 释放二维vector数据
int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// 重载版本
int release_2dVector(std::vector<std::vector<int>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// 一维vector初始化
int init_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.push_back(0);

	return 0;

}

// 释放一维vector数据
int release_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;

}


#pragma endregion 全局函数



//----------------------------------------------------  分割线  ----------------------------------------------------//






