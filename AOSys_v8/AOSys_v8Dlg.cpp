
// AOSys_v8Dlg.cpp : ʵ���ļ�
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


//----------------------------------------------------  �ָ���  ----------------------------------------------------//


#pragma region ��ܴ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CAOSys_v8Dlg �Ի��򣬶Ի����ʼ��ֵ
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
	CDialogEx::DoDataExchange(pDX);   // �󶨿ؼ��ĳ�Ա������ؼ�ID
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


// CAOSys_v8Dlg ��Ϣ�������

BOOL CAOSys_v8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//----------------------------------------------------  �ָ���  ----------------------------------------------------//

#pragma region ����TAB�ؼ�


	// ΪTAB�ؼ���ӱ�ǩ
	m_tabDisplay.InsertItem(0, _T("�ӿ׾�ʵʱͼ��"));
	m_tabDisplay.InsertItem(2, _T("���ξ����ƾ���"));
	m_tabDisplay.InsertItem(3, _T("�Ѱ���"));
	m_tabDisplay.InsertItem(4, _T("��������"));



	// ��ÿ���Ի����ʼ��ָ�룬���ָ������ͷţ�����һ��ȫ�ֵ�ָ��ɣ�
	ptr_SubApertureImageDlg = new CSubApertureDlg();
	ptr_DeformMirrorDlg = new CDeformMirrorDlg();
	ptr_DeviationXDlg = new CDeviationXDlg();
	ptr_MiscSettingDlg = new CMiscSettingDlg();



	// ����Ӧ��TAB�ؼ���ǩҳ�ϴ����Ի���
	ptr_SubApertureImageDlg->Create(IDD_DIALOG_SUBAPERTURE, &m_tabDisplay);
	ptr_DeformMirrorDlg->Create(IDD_DIALOG_DMMATRIX, &m_tabDisplay);
	ptr_DeviationXDlg->Create(IDD_DIALOG_DEVIATION_X, &m_tabDisplay);
	ptr_MiscSettingDlg->Create(IDD_DIALOG_MISCSETTING, &m_tabDisplay);


	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С  
	m_tabDisplay.GetClientRect(&tabRect);
	tabRect.left += 0;
	tabRect.right -= 5;
	tabRect.top += 25;
	tabRect.bottom -= 0;


	ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);



#pragma endregion ����TAB�ؼ�



#pragma region ��ʼ��Edit�ؼ�ֵ

	CString str;

	// ��ֱͫ��
	str = TEXT("3");
	GetDlgItem(IDC_EDIT_PUPILDIA_X)->SetWindowText(str);
	str = TEXT("3");
	GetDlgItem(IDC_EDIT_PUPILDIA_Y)->SetWindowText(str);

	// ��ͫ����λ��
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_PUPIL_CENTER_X)->SetWindowText(str);
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_PUPIL_CENTER_Y)->SetWindowText(str);

	// ��ǰ����
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_STA_WAVEFRONT_TYPE)->SetWindowText(str);

	// �Ƿ����ƹ�ͫ
	str = TEXT("1");
	GetDlgItem(IDC_EDIT_STA_PUPIL_LIMIT)->SetWindowText(str);

	// �Ƿ�ȡ��ƽ��б��
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_SHOW_CANCELTILT)->SetWindowText(str);

	// BlackOffset
	str = TEXT("100");
	GetDlgItem(IDC_EDIT_SHOW_BL)->SetWindowText(str);

	// NoiseCut   IDC_EDIT_NC
	str = TEXT("20");
	GetDlgItem(IDC_EDIT_NC)->SetWindowText(str);



	// WFS��DM�������ƫ��λ��
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_COORDMOVE_X)->SetWindowText(str);
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_COORDMOVE_Y)->SetWindowText(str);

	// PID����������
	str = TEXT("1");
	GetDlgItem(IDC_EDIT_SETPID_P)->SetWindowText(str);
	str = TEXT("0.1");
	GetDlgItem(IDC_EDIT_SETPID_I)->SetWindowText(str);
	str = TEXT("0.1");
	GetDlgItem(IDC_EDIT_SETPID_D)->SetWindowText(str);

	// �ӶԻ���Edit�ؼ�Ĭ��ֵ����
	str = TEXT("1000");
	(ptr_MiscSettingDlg->GetDlgItem(IDC_EDIT_SUBDLG_TIMERSETTING))->SetWindowText(str);

	// Ĭ����ת�Ƕ���Ϊ0��
	str = TEXT("0");
	GetDlgItem(IDC_EDIT_SETANGLE)->SetWindowText(str);


#pragma endregion ��ʼ��Edit�ؼ�ֵ



	// ѡ���㷨��combo box
	m_Combo_ChooseAlgo.AddString(L"PID�㷨");
	m_Combo_ChooseAlgo.AddString(L"�ݶ��㷨");
	m_Combo_ChooseAlgo.AddString(L"ֱ��б�ʷ�");
	m_Combo_ChooseAlgo.SetCurSel(2);  // Ĭ���㷨



	// �뾯����صĿؼ���ʼ��
	str = "û�о���";
	SetDlgItemText(IDC_STATIC_SHOW_ERROR, str);



	//----------------------------------------------------  �ָ���  ----------------------------------------------------//


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAOSys_v8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ
HCURSOR CAOSys_v8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma endregion ��ܴ���


//----------------------------------------------------  �ָ���  ----------------------------------------------------//


#pragma region ȫ�ֱ���
//----------------------------------------------------  ȫ�ֱ���  ----------------------------------------------------//

//  ���ṹ��ʵ�������ṹ��Ĭ��Ȩ���ǹ��г�Ա
instr_t				instr;
instr_setup_t		instr_setup;
spotinfo_t			spotinfo;
AOSystemData*		aoSystemData;
AOSystemData		aoSystemData_LOCAL;		// [no use]


//     WFS_32
int               err;
int               selection;

double            expos_act, master_gain_act;
ViInt32		      blackLevelOffsetAct;  // ��ʼֵ����Ϊ50
ViInt32			  NoiseCutAct;


// ����λ��
float             centroid_x[40][50];
float             centroid_y[40][50];

// �ο�λ��
float             reference_x[40][50];
float             reference_y[40][50];


// ȫ�ֱ���
// �Ѱ�����λ�ã�ȫ�ֺ���MeanInterpolation_KillNAN��Ҫʹ�ã�PID�㷨��Ҫʹ��
float             deviation_x[40][50];
float             deviation_y[40][50];

// ȫ�ֱ���������extern
float			  rememberDeviationX[40][50][100]; // ���ڼ�¼ÿ��ʱ���Ѱ�����ֵ
float			  rememberDeviationY[40][50][100]; // ���ڼ�¼ÿ��ʱ���Ѱ�����ֵ


float             wavefront[40][50];
float             Wavefront_Copy[29][29];


ViChar            resourceName[256];
//FILE              *fp;


int iDMVoltage[144];

long int		i_WFS = 0;
int				runWFS = 1;

float			zerWave[144];  // ��ϵĲ�ǰֵ
float*			zerWave_ptr = zerWave;
float			zerWave_ptr29[841];  // 29x29����ʹ�õ�Zernikeһά���
float			zerWave_Matrix[12][12];
float			zerWave_Matrix29[29][29]; // 29x29����ʹ�õ�Zernike��Ͼ���
int				zerCount = 0;
int				zerCount2 = 0;
float			zerWave_Matrix_Temp[12][12];
float			zerWave_Matrix_Temp29[29][29];
float			zerPolyError[12][12];
float			zerPolyError29[29][29];

//## C���ı����𽥷������ã��𽥲���C++���ı���
float			x_cord[144];  // 144��X����
float			y_cord[144];  // 144��Y����
float			x_cord29[841]; // 841��X����
float			y_cord29[841];// 841��Y����


// ��֤���㾫�ȣ�ѡ��double����
double			DM_Stroke_pre1[12][12];  // Ԥ�ȶ����DM���г̾���
double			DM_Stroke_1D[144];	//## �������Ҫ������

double			coeff[3];  // nm - Vӳ��ϵ��
int				DMcount = 0;  // ����������άDM����תΪһάʱ��

ViPReal64*		fitErrMean;
ViPReal64*		fitErrStdev;

float			ZeroBias_float = 0;
float			UnitFactor = 0;

int				gridIndex = 0;  // 0��12x12������1��29x29������



////////////////////////////// PID�㷨��ȫ�ֱ���  //////////////////////////////////
// vector�汾
std::vector<std::vector<double>> pupil;

// zernike15�׵Ļ��׾���
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


// zernike��ϵķ������Ʊ��ξ�
std::vector<std::vector<double>> zernikeMatrix_recon;   // ֻ������ȫ�ֱ�������Ϊ����extern����ʼ��������BOOL CAOSys_v8Dlg::OnInitDialog()������




// ����汾
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




// ����ģʽ�¶���λ�õ�����λ��
// ������ʽ
float			XScale_array[50];
float			YScale_array[40];

std::vector<float> XScale_vector(50);
std::vector<float> YScale_vector(40);

std::vector<std::vector<double>>	lsqA;
std::vector<std::vector<double>>	eff_picked;

BOOL CloseLoopFlag = FALSE;

// ��������ͼ���йصı���
ViUInt8			imageBuf[480 * 480 + 10];  // һά��ʽ
ViPInt32		row_image;
ViPInt32		col_image;
IplImage*		m_img;  // ��ȡͼƬ
BOOL			CMOSImageFlag = TRUE;

// PID��������ȫ�ֱ�������ʽ���ڶ���¼������õ�
double pid_p, pid_i, pid_d;
double DM_PID_P[144];  
double DM_PID_I[144]; 
double DM_PID_D[144];

// �������ƫ��
double coordMoveX;
double coordMoveY;

// �ӶԻ����ȫ�ֱ���
double timerSetterInterval;

int angleRotate;

int chooseAlgoIndex;




////////////////////////////// �ݶ��㷨��ȫ�ֱ���  //////////////////////////////////





////////////////////////////// ֱ��б�ʷ���ȫ�ֱ���  //////////////////////////////////
double bias_initial = 100;   // �����Ӧ������ƫ��������λnm
double impulse_stroke = 2600;  // �����Ӧ�����ĳ��������λnm



////////////////////////////// ���쳣��ص�ȫ�ֱ���  //////////////////////////////////
// �뱨����صı���������д������IDC_STATIC_SHOW_ERROR�ؼ�����ʾ����
CString str_showerror;    // ����״̬���ַ�����ʾ






#pragma endregion ȫ�ֱ���



//----------------------------------------------------  �ָ���  ----------------------------------------------------//


#pragma region �¼�����


//--------------------------  ȫ���¼�  --------------------------//
// ��ʼ��WFS�豸
// WFS�ֱ��ʣ�480x480����Ӧ���ӿ׾�����Ϊ��29x29
void CAOSys_v8Dlg::OnClickedButtonWfsIni()
{
	WFS_Initialization_Sequence(this);
}

// ��ʼ��DM�豸
// ÿ�δ�һ�ֹ���ģʽ�л�����һ�й���ģʽʱ����Ҫʹ�ô��¼�������ӡ���ǰ̽���¼���ת�롰��ǰ�ؽ��¼���
void CAOSys_v8Dlg::OnClickedButtonDmIni()
{
	// ��ʼ��DM,��ʹ��DM�ĵ�ѹ����Ϊ��
	if (P_AOS_Initialize(0) > 0)
	{
		GetDlgItem(IDC_EDIT_DMSTATUS)->SetWindowText(_T("DM �ѳ�ʼ��"));
	}

	// Ϊ���ݽṹ������һ�����ص�ַ��locally defined memory address��
	P_AOS_GetVarAddress(VAR_DM_DATA, (void**)&aoSystemData);

	// max voltage = 300 V     range of stroke = 0x4000=16384
	// 16384/300 = 54.6
	//## �����������Ӧ��û������
	aoSystemData->Volt.DMVoltageScale = 54.6;

	// ���õ�ѹת�����г̵�ϵ��
	coeff[0] = 0.0413;
	coeff[1] = 3.97;
	coeff[2] = 0;


}



// �ر�WFS�豸��DM�豸
// ���ε�������ť�ᵼ�³���رգ���֪��Ϊʲô
void CAOSys_v8Dlg::OnClickedButtonClose()
{
	if (WFS_close(instr.handle) == 0)
	{
		GetDlgItem(IDC_EDIT_WFSSTATUS)->SetWindowText(_T("WFS �ѶϿ�"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_WFSSTATUS)->SetWindowText(_T("WFS δ�ɹ��Ͽ�"));
	}


	if (P_AOS_Close() == 0)
	{
		GetDlgItem(IDC_EDIT_DMSTATUS)->SetWindowText(_T("DM �ѶϿ�"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_DMSTATUS)->SetWindowText(_T("DM δ�ɹ��Ͽ�"));
	}

}


//--------------------------  ��ǰ̽���¼�  --------------------------//
// �˽׶β���Ҫ��������

// ��ʼ��ǰ̽��
void CAOSys_v8Dlg::OnClickedButtonDetDetection()
{
	pThread_DET = new CWinThread();
	pThread_DET->m_bAutoDelete = FALSE;
	pThread_DET = AfxBeginThread(ThreadFunc_WFS_Measurement_DET, this);  // ʹ��thisָ�뽫CAOSys_v7Dlg�ഫ���̺߳���
}

// ����ǰ̽������д���ļ�
void CAOSys_v8Dlg::OnClickedButtonDetWrite()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//--------------------------  ��ǰ�ؽ��¼�  --------------------------//
// �˽׶���Ҫ����29x29����

//## ע�⣬�ڲ�ǰ�ؽ�ģʽ�£�����ǰ�ؽ�����ť�롰����DM����ťҪ�ɶ�ʹ�ã���Ϊ�ڡ���ǰ�ؽ�����ť��zernikeMatrix_reconҪpush_back
//## �����У�Ҫ��Ӧ�İ�zernikeMatrix_recon��zernikeMatrix_recon_1d��������pop_back�ſ��ԣ��������ݶѻ�������޷���ȷ����DM
// ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��¼�
void CAOSys_v8Dlg::OnClickedButtonRecReconstruction()
{
	pThread_REC = new CWinThread();
	pThread_REC->m_bAutoDelete = FALSE;
	pThread_REC = AfxBeginThread(ThreadFunc_WFS_Measurement_REC, this);  // ʹ��thisָ�뽫CAOSys_v7Dlg�ഫ���̺߳���

}  // ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��¼�



//## ע�⣬�ڲ�ǰ�ؽ�ģʽ�£�����ǰ�ؽ�����ť�롰����DM����ťҪ�ɶ�ʹ�ã���Ϊ�ڡ���ǰ�ؽ�����ť��zernikeMatrix_reconҪpush_back
//## �����У�Ҫ��Ӧ�İ�zernikeMatrix_recon��zernikeMatrix_recon_1d��������pop_back�ſ��ԣ��������ݶѻ�������޷���ȷ����DM
// ��ǰ�ؽ�ģʽ�¿��Ʊ��ξ�
void CAOSys_v8Dlg::OnClickedButtonRecConDm()
{


}// ��ǰ�ؽ�ģʽ�¿��Ʊ��ξ�



void CAOSys_v8Dlg::OnClickedButtonDmZero()
{


}



// ����Zernike������
// ѡ����ʵ�����WFS̽�⵽�Ĳ�ǰ��ȥZernike��ϵĲ�ǰ
void CAOSys_v8Dlg::OnClickedButtonRecZerfiterr()
{

}

// ��ǰ�ؽ�ģʽ��  д���ı��¼�
void CAOSys_v8Dlg::OnClickedButtonRecWrite()
{

}  // ��ǰ�ؽ�ģʽ��  д���ı��¼�



//--------------------------  ��ǰУ���¼�  --------------------------//
// �˽׶���Ҫ����12x12����

// ��ʼ�ջ�У����ǰ
void CAOSys_v8Dlg::OnClickedButtonConCloseloop()
{


	// �̵߳Ĳ�������
	int       nPriority = THREAD_PRIORITY_HIGHEST;//Ĭ��ΪTHREAD_PRIORITY_NORMAL
	UINT       nStackSize = 0;//�봴�������̶߳�ջ��С��ͬ
	DWORD       dwCreateFlags = CREATE_SUSPENDED;//CREATE_SUSPENDED ����������߳�

	// �������߳�
	pThread_LOOP = new CWinThread();
	pThread_LOOP->m_bAutoDelete = FALSE;  // ��ֹMFCɾ��CWinThread����
	pThread_LOOP = AfxBeginThread(ThreadFunc_WFS_Measurement_CONLOOP, this,
		nPriority, nStackSize, dwCreateFlags);  // ʹ��thisָ�뽫CAOSys_v7Dlg�ഫ���̺߳���
	pThread_LOOP->ResumeThread();

	DWORD dwExitCode;
	::GetExitCodeThread(pThread_LOOP->m_hThread, &dwExitCode);
	if (!(dwExitCode==STILL_ACTIVE))  // ����̲߳��ڻ����ɾ��
	{
		delete pThread_LOOP;
	}


}

// ����ǰУ������д���ļ�
void CAOSys_v8Dlg::OnClickedButtonConWrite()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//--------------------------  �����¼�  --------------------------//

// ����Ѱ��WFS��DM������λ��
void CAOSys_v8Dlg::OnClickedButtonDmCenterup()
{


}


// �ж��¼�
void CAOSys_v8Dlg::OnBnClickedButtonInterrupt()
{
	CloseLoopFlag = FALSE;
}



// TAB�ؼ�����Ϣ����
void CAOSys_v8Dlg::OnTcnSelchangeTabDisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С  
	m_tabDisplay.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;


	switch (m_tabDisplay.GetCurSel())
	{
	case 0:
		// ���ݵ����õ�tabRect����m_SubApertureDlg�ӶԻ��򣬲�����Ϊ��ʾ   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ���� 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 1:
		// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ���� 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 2:
		// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ��ʾ 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 3:
		// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ��ʾ 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

		break;



	default:
		break;
	}

}



// �����ڴ棬��ʹ������������
void CAOSys_v8Dlg::OnBnClickedButtonReleaseMem()
{
	// TODO: Add your control notification handler code here

	// �������
	if (zernikeMatrix_01.size() > 0)
	{
		// ���С��capacity����reallocate
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

	// �������³�ʼ��PID����
	if (pid_p != 0 || pid_i != 0 || pid_d != 0)
	{
		pid_p = 0;
		pid_i = 0;
		pid_d = 0;
	}



	// �뱨����ص����ݴ���
	BOOL FLAG_NAN = 0;  // 0��ʾû��NAN���ݣ�1��ʾ��NAN����
	str_showerror = "û�о���";
	SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);


}



void CAOSys_v8Dlg::OnBnClickedButtonGearup()
{
	// TODO: Add your control notification handler code here

	//##number 1    ���ò���ʾ��ͫ����ز���
	//��WFS_SetPupil������ʹ��
	GetDlgItem(IDC_EDIT_PUPIL_CENTER_X)->GetWindowText(m_Edit_PupilCenter_X);		// �����ͫ����x����
	instr_setup.pupil_center_x_mm = _ttof(m_Edit_PupilCenter_X);
	(GetDlgItem(IDC_EDIT_PUPIL_CENTER_Y))->GetWindowText(m_Edit_PupilCenter_Y);		// �����ͫ����y����
	instr_setup.pupil_center_y_mm = _ttof(m_Edit_PupilCenter_Y);
	(GetDlgItem(IDC_EDIT_PUPILDIA_X))->GetWindowText(m_Edit_PupilDia_X);			// �����ֱͫ��x
	instr_setup.pupil_dia_x_mm = _ttof(m_Edit_PupilDia_X);
	(GetDlgItem(IDC_EDIT_PUPILDIA_Y))->GetWindowText(m_Edit_PupilDia_Y);			// �����ֱͫ��y
	instr_setup.pupil_dia_y_mm = _ttof(m_Edit_PupilDia_Y);
	WFS_SetPupil(instr.handle, instr_setup.pupil_center_x_mm, instr_setup.pupil_center_y_mm, // ���ù�ͫ
		instr_setup.pupil_dia_x_mm, instr_setup.pupil_dia_y_mm);
	(m_Edit_Sta_PupilCenter_X).Format(_T("%lf"), instr_setup.pupil_center_x_mm);	// �����ͫx����λ�� 
	SetDlgItemTextW(IDC_EDIT_STA_PUPIL_CENTER_X, m_Edit_Sta_PupilCenter_X);
	(m_Edit_Sta_Pupil_Center_Y).Format(_T("%lf"), instr_setup.pupil_center_y_mm);	// �����ͫx����λ��  
	SetDlgItemTextW(IDC_EDIT_STA_PUPIL_CENTER_Y, m_Edit_Sta_Pupil_Center_Y);
	(m_Edit_Sta_PupilDia_X).Format(_T("%lf"), instr_setup.pupil_dia_x_mm);			// �����ͫx����ֱ��  
	SetDlgItemTextW(IDC_EDIT_STA_PUPILDIA_X, m_Edit_Sta_PupilDia_X);
	(m_Edit_Sta_PupilDia_Y).Format(_T("%lf"), instr_setup.pupil_dia_y_mm);			// �����ͫy����ֱ��  
	SetDlgItemTextW(IDC_EDIT_STA_PUPILDIA_Y, m_Edit_Sta_PupilDia_Y);



	//##number2
	// ���ò���ʾ�Ƿ�Ҫcanceltilt
	// ��WFS_CalcSpotToReferenceDeviations������ʹ��
	(GetDlgItem(IDC_EDIT_SHOW_CANCELTILT))->GetWindowTextW(m_Edit_Show_CancelTilt);
	instr_setup.cancel_tilt = _ttoi(m_Edit_Show_CancelTilt);
	if (instr_setup.cancel_tilt == 0)
	{
		(GetDlgItem(IDC_EDIT_STA_CANCELTILT))->SetWindowTextW(_T("δУ����б"));
	}
	else if (instr_setup.cancel_tilt == 1)
	{
		(GetDlgItem(IDC_EDIT_STA_CANCELTILT))->SetWindowTextW(_T("��У����б"));
	}



	//##number3
	// ���ò���ʾ�Ƿ����ƹ�ͫ
	// ��WFS_CalcWavefront������ʹ��
	(GetDlgItem(IDC_EDIT_STA_PUPIL_LIMIT))->GetWindowText(m_Edit_Sta_PupilLimit);
	instr_setup.pupil_circular = _ttoi(m_Edit_Sta_PupilLimit);
	// ��ʾ��������
	if (instr_setup.pupil_circular == 0)
	{
		(GetDlgItem(IDC_EDIT_SHOW_PUPIL_LIMIT))->SetWindowText(_T("�����ƹ�ͫ"));
	}
	else if (instr_setup.pupil_circular == 1)
	{
		(GetDlgItem(IDC_EDIT_SHOW_PUPIL_LIMIT))->SetWindowText(_T("���ƹ�ͫ"));
	}




	//##number4
	// ���ò���ʾ��ǰ����
	// ��WFS_CalcWavefront��ʹ��
	(GetDlgItem(IDC_EDIT_STA_WAVEFRONT_TYPE))->GetWindowText(m_Edit_Sta_WavefrontType);
	instr_setup.wavefront_type = _ttoi(m_Edit_Sta_WavefrontType);
	if (instr_setup.wavefront_type == 0)
	{
		(GetDlgItem(IDC_EDIT_SHOW_WAVEFRONT_TYPE))->SetWindowText(_T("������ǰ"));
	}
	else if (instr_setup.wavefront_type == 1)
	{
		(GetDlgItem(IDC_EDIT_SHOW_WAVEFRONT_TYPE))->SetWindowText(_T("��ϲ�ǰ"));
	}
	else if (instr_setup.wavefront_type == 2)
	{
		(GetDlgItem(IDC_EDIT_SHOW_WAVEFRONT_TYPE))->SetWindowText(_T("��ֲ�ǰ"));
	}



	//##number5
	// ���ò���ʾBlack Offset Levelֵ
	// ��WFS_SetBlackLevelOffset������ʹ��
	(GetDlgItem(IDC_EDIT_SHOW_BL))->GetWindowTextW(m_Edit_Show_BL); // ���ı����ж�ȡBlackOffset��תΪ����
	blackLevelOffsetAct = _ttoi(m_Edit_Show_BL);
	WFS_SetBlackLevelOffset(instr.handle, blackLevelOffsetAct);
	//��������õ�Black Offset Levelֵ��У������ֵ
	WFS_GetBlackLevelOffset(instr.handle, &blackLevelOffsetAct);
	(m_Edit_Sta_BL).Format(_T("%d"), blackLevelOffsetAct);
	SetDlgItemTextW(IDC_EDIT_STA_BL, m_Edit_Sta_BL);



	//##number6
	// ���ò���ʾNoise Cutֵ
	// ��WFS_CutImageNoiseFloor����ͨģʽ����WFS_SetHighspeedMode������ģʽ��������ʹ��
	(GetDlgItem(IDC_EDIT_NC))->GetWindowTextW(m_Edit_SetNoiseCut); // ���ı����ж�ȡBlackOffset��תΪ����
	NoiseCutAct = _ttoi(m_Edit_SetNoiseCut);
	WFS_CutImageNoiseFloor(instr.handle, NoiseCutAct);  // �˺�������ģʽ�²���ʹ��
	//��������õ�Noise Cutֵ��У������ֵ
	(m_Edit_Std_NoiseCut).Format(_T("%d"), NoiseCutAct);
	SetDlgItemTextW(IDC_EDIT_STA_NC, m_Edit_Std_NoiseCut);


	//##number7
	// ���ò���ʾ����ƫ��
	// ��zernike������ʹ��
	GetDlgItem(IDC_EDIT_COORDMOVE_X)->GetWindowTextW(m_Edit_CoordMove_X); // x��������ƫ��
	coordMoveX = _ttoi(m_Edit_CoordMove_X);
	GetDlgItem(IDC_EDIT_COORDMOVE_Y)->GetWindowTextW(m_Edit_CoordMove_Y); // x��������ƫ��
	coordMoveY = _ttoi(m_Edit_CoordMove_Y);


	//## number8
	// ����PID����
	GetDlgItem(IDC_EDIT_SETPID_P)->GetWindowText(m_Edit_SetPID_P);	// ��ȡPID����
	pid_p = _ttof(m_Edit_SetPID_P);
	GetDlgItem(IDC_EDIT_SETPID_I)->GetWindowText(m_Edit_SetPID_I);
	pid_i = _ttof(m_Edit_SetPID_I);
	GetDlgItem(IDC_EDIT_SETPID_D)->GetWindowText(m_Edit_SetPID_D);
	pid_d = _ttof(m_Edit_SetPID_D);
	m_Edit_ShowPID_P.Format(_T("%lf"), pid_p);						// ������õ�PID����
	SetDlgItemTextW(IDC_EDIT_SHOWPID_P, m_Edit_ShowPID_P);
	m_Edit_ShowPID_I.Format(_T("%lf"), pid_i);
	SetDlgItemTextW(IDC_EDIT_SHOWPID_I, m_Edit_ShowPID_I);
	m_Edit_ShowPID_D.Format(_T("%lf"), pid_d);
	SetDlgItemTextW(IDC_EDIT_SHOWPID_D, m_Edit_ShowPID_D);



	// �ӶԻ��������
	(ptr_MiscSettingDlg->GetDlgItem(IDC_EDIT_SUBDLG_TIMERSETTING))->GetWindowTextW(ptr_MiscSettingDlg->m_Edit_TimeSetter); // x��������ƫ��
	timerSetterInterval = _ttoi(ptr_MiscSettingDlg->m_Edit_TimeSetter);


	GetDlgItem(IDC_EDIT_SETANGLE)->GetWindowText(m_Edit_SetAngle);
	angleRotate = _wtoi(m_Edit_SetAngle);




}




void CAOSys_v8Dlg::OnSelchangeComboChoosealgo()
{
	// TODO: Add your control notification handler code here

	chooseAlgoIndex = m_Combo_ChooseAlgo.GetCurSel();
}


// ֱ��б�ʷ���Ԥ�����¼�
void CAOSys_v8Dlg::OnBnClickedButtonPreCalc()
{

	// �̵߳Ĳ�������
	int       nPriority = THREAD_PRIORITY_HIGHEST;//Ĭ��ΪTHREAD_PRIORITY_NORMAL
	UINT       nStackSize = 0;//�봴�������̶߳�ջ��С��ͬ
	DWORD       dwCreateFlags = CREATE_SUSPENDED;//CREATE_SUSPENDED ����������߳�

	// �������߳�
	pThread_PreCalc = new CWinThread();
	pThread_PreCalc->m_bAutoDelete = FALSE;  // ��ֹMFCɾ��CWinThread����
	pThread_PreCalc = AfxBeginThread(ThreadFunc_PreCalculation, this,
		nPriority, nStackSize, dwCreateFlags);  // ʹ��thisָ�뽫CAOSys_v7Dlg�ഫ���̺߳���
	pThread_PreCalc->ResumeThread();

	DWORD dwExitCode;
	::GetExitCodeThread(pThread_PreCalc->m_hThread, &dwExitCode);
	if (!(dwExitCode == STILL_ACTIVE))  // ����̲߳��ڻ����ɾ��
	{
		delete pThread_PreCalc;
	}


}  // �¼�����



#pragma endregion �¼�����


//----------------------------------------------------  �ָ���  ----------------------------------------------------//

#pragma region ȫ�ֺ���

// ����WFS�׳��Ĵ���
void WFS_HandleErrors(int err)
{
	char buf[WFS_ERR_DESCR_BUFFER_SIZE];
	//char*����ת��Ϊ���ֽ����
	WCHAR W_buf[512];

	if (!err) return;

	// ��ô����ַ���
	WFS_error_message(instr.handle, err, buf);

	if (err < 0) // ���ִ���
	{
		long multi_buf = MultiByteToWideChar(CP_ACP, 0, buf, strlen(buf), W_buf, sizeof(W_buf));
		W_buf[multi_buf] = '\0';
		CString buf_change;
		buf_change.Format(_T("%s"), W_buf);

		// �����������message box
		AfxMessageBox(buf_change, MB_OK, 0);

		// ��������ʱ���رճ���
		::MessageBox(NULL, _T("���򽫹ر� ��"), _T("������Ϣ"), MB_OK);
		WFS_close(instr.handle);
		exit(1);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ѡ��WFS�豸
int WFS_SelectInstrument(LPVOID pParam, int* selection, ViChar* resourceName)
{
	// ���Ի������ָ�봫�뺯��
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	int            err, instr_cnt;
	ViInt32        device_id;
	int            in_use;

	char           instr_name[WFS_BUFFER_SIZE];
	char           serNr[WFS_BUFFER_SIZE];
	//char           strg[WFS_BUFFER_SIZE];

	//char*����ת��Ϊ���ֽ����
	//WCHAR W_instr_name[512];
	//WCHAR W_serNr[512];
	//WCHAR W_resourceName[512];

	//## �о�����������Բ���Ҫ��ֱ��ִ��WFS_GetInstrumentListInfo�����в���
	// �ҵ������豸������WFS���豸��Ŀinstr_cnt
	if (err = WFS_GetInstrumentListLen(VI_NULL, (ViInt32*)&instr_cnt))
		WFS_HandleErrors(err);

	if (instr_cnt == 0)  // ���û���ҵ�WFS�豸����ʾWFS�豸û���ҵ�
	{
		::MessageBox(NULL, _T("û���ҵ��κ�WFS ��"), _T("WFS״̬"), MB_OK);
		return -1;  // ֹͣWFS��ʼ������
	}

	// �ҵ��豸device_id��ѯ���Ƿ��ʼ�������û��ʹ�þͷ���in_use״̬��Ϣ��in_use=1ʱ�޷���ʼ��
	// �������һ����Ҫ������Ϊ�˷���ָ��resourceName
	if (err = WFS_GetInstrumentListInfo(VI_NULL, 0, &device_id, (ViInt32*)&in_use, instr_name, serNr, resourceName))
		WFS_HandleErrors(err);

	if (in_use == 0)  // ������豸���Խ��г�ʼ����������豸����Ϣ
	{
		//## WFS_SelectInstrument�µ�����豸�����Ϣ������һ����WFS_GetInstrumentInfo������

		// ����豸����

		// ������к�

		// �����Դ����

		(pW->GetDlgItem(IDC_EDIT_WFSSEL))->SetWindowText(_T("WFS����"));
	}
	else
	{
		(pW->GetDlgItem(IDC_EDIT_WFSSEL))->SetWindowText(_T("WFS��ռ��"));
		return -1;
	}

	// ��Ϊ�豸��WFS10�����ִ�����256��ʮ���ƣ���0x00100��ʮ�����ƣ�
	*selection = DEVICE_OFFSET_WFS10;
	return *selection;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ѡ��MLA
int SlectMLA(int* selection)
{
	// ֻ�з��������ʹ��WFS����
	*selection = 0;
	return *selection;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ʼ��WFS���ܵĺ�����װ������ĺ�����
void WFS_Initialization_Sequence(LPVOID pParam)
{
	// LPVOID��������������������ͣ����ｫthisָ�봫��������������Ҫ��ԭΪ�Ի������ָ��
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;


	//--------------------------------------------------------------------------------
	// �����������ҪĿ���ǵ���WFS_GetInstrumentListLen����豸ID��instr.selected_dev_i������Դ����resourceName��
	// ���߶�ͨ��ָ�봫��
	// ����pW�ֽ��Ի������ָ�밴��LPVOID���ʹ���ȥ
	if (WFS_SelectInstrument(pW, &(instr.selected_dev_id), resourceName) == 0)
	{
		::MessageBox(NULL, _T("û��ѡ���κ��豸��"), _T("����״̬"), MB_OK);
		return;  //��������WFS_Initialization_Sequenceû�з������ͣ����Բ��ù��Ƿ�return TRUE;
	}


	//--------------------------------------------------------------------------------
	// ��ʼ��WFS
	err = WFS_init(resourceName, VI_FALSE, VI_FALSE, &instr.handle); // err==0��ʾִ�гɹ���������VI_SUCCESS��ʾ
	if (err == 0)
	{
		(pW->GetDlgItem(IDC_EDIT_WFSSTATUS))->SetWindowText(_T("WFS �ѳ�ʼ��"));
	}
	else
	{
		WFS_HandleErrors(err);
	}


	//--------------------------------------------------------------------------------
	// ����һ�����躯������ΪThorlabs��MLA�ǿ���װж�ģ�����ÿ�γ�ʼ��Ҫȷ��ѡ����һ��MLA
	if (SlectMLA(&instr.selected_mla) < 0)
	{
		::MessageBox(NULL, _T("û��ѡ���κ�MLA��"), _T("Link Status"), MB_OK);
		return; // program ends here if no instrument selected
	}


	//--------------------------------------------------------------------------------
	// ���÷ֱ��ʣ��ɺ���ֱ�����ã�������ӿ׾���Ŀ
	// �������õķֱ���Ҫ��setpupil�ĳߴ�һ��
	//## ���������������������ڵ������instr.selected_mla��ֵ
	err = WFS_ConfigureCam(instr.handle, SAMPLE_PIXEL_FORMAT, SAMPLE_CAMERA_RESOL_WFS10,
		(ViInt32*)&spotinfo.spots_x, (ViInt32*)&spotinfo.spots_y);
	if (err == 0)
	{
		// ����ֱ��� �޷�����
		(pW->GetDlgItem(IDC_EDIT_STA_RESOLUTION))->SetWindowText(_T("480 X 480"));

		// ����ӿ׾���������WFS_ConfigureCam�����������������ֵ
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


	// ���ò���ʾ���������
	// WFS_SetReferencePlane��WFS_GetReferencePlane������ʹ��
	instr_setup.ref_idx = SAMPLE_REF_PLANE;
	WFS_SetReferencePlane(instr.handle, instr_setup.ref_idx);
	WFS_GetReferencePlane(instr.handle, &instr_setup.ref_idx);
	if (instr_setup.ref_idx == 0)
	{
		(pW->GetDlgItem(IDC_EDIT_STA_CALIBRATION))->SetWindowText(_T("������"));
	}
	else
	{
		(pW->GetDlgItem(IDC_EDIT_STA_CALIBRATION))->SetWindowText(_T("��Զ���"));
	}

	//--------------------------------------------------------------------------------


	// ���ò���ʾ�ع�ʱ��
	WFS_SetExposureTime(instr.handle, 0.18, &expos_act);
	(pW->m_Edit_Sta_Expo).Format(_T("%lf"), expos_act);
	pW->SetDlgItemTextW(IDC_EDIT_STA_EXPO, pW->m_Edit_Sta_Expo);

	// ���ò���ʾ����
	WFS_SetMasterGain(instr.handle, 1.5, &master_gain_act);
	(pW->m_Edit_Sta_Gain).Format(_T("%lf"), master_gain_act);
	pW->SetDlgItemTextW(IDC_EDIT_STA_GAIN, pW->m_Edit_Sta_Gain);



}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ǰ̽��׶ε��̺߳���
UINT ThreadFunc_WFS_Measurement_DET(LPVOID pParam)
{



	// �̺߳�����Ҫһ������ֵ
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��߳�
UINT ThreadFunc_WFS_Measurement_REC(LPVOID pParam)
{


	return 0;
}  // ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��߳�




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ǰ���Ƶ��̺߳���
UINT ThreadFunc_WFS_Measurement_CONLOOP(LPVOID pParam)
{



#pragma region �ݶ��㷨

	// ѡ���ݶ��㷨
	if (chooseAlgoIndex == 1)
	{


#pragma region �߳��еľֲ�����

		// ����ָ��Ի����ָ��
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;


		// Ĭ�ϲ����б��ξ���ִ����
		double zernikeMatrix_recon_array_DEFAULT[140];
		// �Ӳ����б��ξ���ִ����
		double zernikeMatrix_recon_array_ADD[140];
		// �������б��ξ���ִ����
		double zernikeMatrix_recon_array_MINUS[140];

		// Ĭ�ϲ����Ĳ�ǰͳ�Ʋ���
		double     wavefront_min_default, wavefront_max_default, wavefront_diff_default, wavefront_mean_default, wavefront_rms_default, wavefront_weighted_rms_default;
		// �Ӳ����Ĳ�ǰͳ�Ʋ���
		double     wavefront_min_add, wavefront_max_add, wavefront_diff_add, wavefront_mean_add, wavefront_rms_add, wavefront_weighted_rms_add;
		// �������Ĳ�ǰͳ�Ʋ���
		double     wavefront_min_minus, wavefront_max_minus, wavefront_diff_minus, wavefront_mean_minus, wavefront_rms_minus, wavefront_weighted_rms_minus;

		// ���ۺ���ֵ
		double meritFunctionValueDefault = 100;
		double meritFunctionValueAdd = 0;
		double meritFunctionValueMinus = 0;

		// �ݶȷ���
		BOOL DEFAULE_evolve = FALSE;
		BOOL ADD_evolve = FALSE;
		BOOL MINUS_evolve = FALSE;

		double randNum = 50;   // ÿ����Ԫ�Ĳ���ֵ�������������ǰ���������Ҫ��ȡĳ�ֲ��Ըı��������

		// ������ʾCMOSͼ��
		uchar image2DBuf[480][480];  // ��ά��ʽ


		// ��������
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));  // ��ʾͼ��
		CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));  // ��ʾ�Ѱ���
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));  // ��ʾ���ξ���ִ����


		int NAN_counter = 0; // ����NAN���ݵĸ���

		CString gradientDirection;  // ������ʾ�ݶȷ���


		// ���ڼ�¼�ݶ��㷨���ֲ��������ۺ����仯���ݶȷ���
		std::vector<std::vector<double>> gradientMerit_vector;
		gradientMerit_vector.resize(3);  // ������������
		for (int index = 0; index < 3; ++index)
		{
			gradientMerit_vector[index].resize(200);   // ��¼200��������
		}
		std::vector<double> gradientDirection_vector;  // ��¼�ݶ��㷨��ǰ������
		gradientDirection_vector.resize(200);
		int counter_recordMerit = 0;  // ���ڼ�¼���ۺ���ʱ�ļ�����������ջ�֮ǰҪ����
		int counter_recordGradientDirection = 0;    //  ���ڼ�¼�ݶȽ��з���ļ�����������ջ�֮ǰҪ����



		// ���Ѱ�����Ϊ���ۺ�����Ҫ�����ͫ
		// WFS���������꣬�ӿ׾���pitchΪ150um=0.15mm��480x480�ֱ�����Ϊ29x29���ӿ׾�
		float xArray_29[29];
		float yArray_29[29];
		for (int i = 0; i < 29; ++i)
			xArray_29[i] = -2.1 + i * 0.15;
		for (int i = 0; i < 29; ++i)
			yArray_29[i] = -2.1 + i * 0.15;
		// �����ͫ���󣬹�ֱͫ����Ҫ����
		float pupil_deviation[29][29];
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{

				pupil_deviation[row][col] = (float)((sqrt(pow(xArray_29[row], 2) + pow(yArray_29[col], 2)) <= instr_setup.pupil_dia_x_mm / 2) ? 1 : 0);

			}
		}





#pragma endregion �߳��еľֲ�����



		// ���ñ��ξ���������
		zernikeMatrix_recon_array_DEFAULT[65] = 2000;
		zernikeMatrix_recon_array_DEFAULT[66] = 2000;
		zernikeMatrix_recon_array_DEFAULT[77] = 2000;
		zernikeMatrix_recon_array_DEFAULT[78] = 2000;


		// ���͸����ξ�
		DriveDeformMirror_nm(zernikeMatrix_recon_array_DEFAULT);  // �������ξ��˶�

		wait4U(10);  // �ȴ�һ��ʱ��

		Detect_Wavefront2Deviation_Normal();  // ̽�Ⲩǰ������Ѱ���


		// WFS�ؽ���ǰ
		//�����Ѱ����ؽ���ǰ,wavefront����ĵ�λ��um
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

	}  // if�������ݶ��㷨����

#pragma endregion �ݶ��㷨





#pragma region ֱ��б��

	// ֱ��б�ʷ�����ҪԤ��������
	if (chooseAlgoIndex == 2)
	{

		// ����Ԥ��������
		lsqA = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\lsqA.txt");
		eff_picked = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\eff_picked.txt");



#pragma region �߳��еľֲ�����

		// ����ָ��Ի����ָ��
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;
		// ��������,checkbox��������
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));

		// ���ͼ�йصı���,480�ķֱ���
		uchar image2DBuf[480][480];  // ��ά��ʽ

		// ���䲨ǰ��Ч�ӿ׾����Ѱ�����ɵ�һά����
		std::vector<double> lsqy;  // lsqx=lsqA*lsqy
		lsqy.resize(lsqA[0].size());
		int row_effsub;  // ��Ч�����������
		int col_effsub;  // ��Ч�����������

		// ��ǰͳ�Ʋ����ֲ�����
		double wavefront_min_ACEMETHOD;
		double wavefront_max_ACEMETHOD;
		double wavefront_diff_ACEMETHOD;
		double wavefront_mean_ACEMETHOD;
		double wavefront_rms_ACEMETHOD;
		double wavefront_weighted_rms_ACEMETHOD;

		double zernikeMatrix_recon_array_ACEMETHOD[144];   // ������С���˷������ִ����  

		double sum_temp = 0;

		// ֱ�ӻ��ַ��ؽ���ǰ
		float  wavefront_DI[40][50];


		// �Ѱ����ֲ�����
		float	deviation_x_DI[40][50];
		float   deviation_y_DI[40][50];


#pragma endregion �߳��еľֲ�����


		// �ջ�
		CloseLoopFlag = TRUE;
		int recordwave_counter = 0;
		while (CloseLoopFlag)
		{

			// ��ͨģʽ��ȡ����λ��
			WFS_TakeSpotfieldImage(instr.handle);
			// ��������λ��
			WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
			// �����Ѱ���
			WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
			// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
			WFS_GetSpotDeviations(instr.handle, *deviation_x_DI, *deviation_y_DI);



#pragma region ȥ���Ѱ����е���Чֵ

			// �Ѱ���Ϊ29x29���߽��������

			deviation_x_DI[0][0] = 0; deviation_x_DI[0][28] = 0; deviation_x_DI[28][0] = 0; deviation_x_DI[28][28] = 0;  // �ĸ�������
			deviation_y_DI[0][0] = 0; deviation_y_DI[0][28] = 0; deviation_y_DI[28][0] = 0; deviation_y_DI[28][28] = 0;  // �ĸ�������

			// ����������������
			for (int col = 1; col < 28; ++col)  // ��0��
			{
				deviation_x_DI[0][col] = 0;
				deviation_y_DI[0][col] = 0;
			}
			for (int col = 1; col < 28; ++col)  // ��28��
			{
				deviation_x_DI[28][col] = 0;
				deviation_y_DI[28][col] = 0;
			}
			for (int row = 1; row < 28; ++row)  // ��0��
			{
				deviation_x_DI[row][0] = 0;
				deviation_y_DI[row][0] = 0;
			}
			for (int row = 1; row < 28; ++row)  // ��28��
			{
				deviation_x_DI[row][28] = 0;
				deviation_y_DI[row][28] = 0;
			}


			// ���м�����ݽ���ƽ����ֵ
			for (int row = 1; row < 28; ++row)  // �ճ�����������
			{
				for (int col = 1; col < 28; ++col) // �ճ�����������
				{

					// �ж�x����
					if (_isnan(deviation_x_DI[row][col]))
					{
						// ���з�ʽ
						//  x x x
						//  x o x
						//  x x x

						if (_isnan(deviation_x_DI[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
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
							// ���з�ʽ
							//  x x x
							//  x o x
							//  x x x

							int mean_counter = 0;  // ��Чֵ����
							float mean_value = 0;  // ��Чֵ�ĺ�

							if (!_isnan(deviation_x_DI[row - 1][col - 1]))  // ����
							{
								mean_value = mean_value + deviation_x_DI[row - 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row - 1][col])) // ����
							{
								mean_value = mean_value + deviation_x_DI[row - 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row - 1][col + 1])) // ����
							{
								mean_value = mean_value + deviation_x_DI[row - 1][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row][col - 1])) // ����
							{
								mean_value = mean_value + deviation_x_DI[row][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row][col + 1])) // ����
							{
								mean_value = mean_value + deviation_x_DI[row][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row + 1][col - 1])) // ����
							{
								mean_value = mean_value + deviation_x_DI[row + 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row + 1][col]))  // ����
							{
								mean_value = mean_value + deviation_x_DI[row + 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_x_DI[row + 1][col + 1]))  // ����
							{
								mean_value = mean_value + deviation_x_DI[row + 1][col + 1];
								mean_counter++;
							}

							deviation_x_DI[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

						}


					}  // x�������



					// �ж�y����
					if (_isnan(deviation_y_DI[row][col]))
					{

						// ���з�ʽ
						//  x x x
						//  x o x
						//  x x x

						if (_isnan(deviation_y_DI[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
							_isnan(deviation_y_DI[row - 1][col]) &&
							_isnan(deviation_y_DI[row - 1][col + 1]) &&
							_isnan(deviation_y_DI[row][col - 1]) &&
							_isnan(deviation_y_DI[row][col + 1]) &&
							_isnan(deviation_y_DI[row + 1][col - 1]) &&
							_isnan(deviation_y_DI[row + 1][col]) &&
							_isnan(deviation_y_DI[row + 1][col + 1]))
						{

							deviation_y_DI[row][col] = 0;
						} // ǿ���������
						else
						{
							// ���з�ʽ
							//  x x x
							//  x o x
							//  x x x

							int mean_counter = 0;  // ��Чֵ����
							float mean_value = 0;  // ��Чֵ�ĺ�

							if (!_isnan(deviation_y_DI[row - 1][col - 1]))  // ����
							{
								mean_value = mean_value + deviation_y_DI[row - 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row - 1][col])) // ����
							{
								mean_value = mean_value + deviation_y_DI[row - 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row - 1][col + 1])) // ����
							{
								mean_value = mean_value + deviation_y_DI[row - 1][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row][col - 1])) // ����
							{
								mean_value = mean_value + deviation_y_DI[row][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row][col + 1])) // ����
							{
								mean_value = mean_value + deviation_y_DI[row][col + 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row + 1][col - 1])) // ����
							{
								mean_value = mean_value + deviation_y_DI[row + 1][col - 1];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row + 1][col]))  // ����
							{
								mean_value = mean_value + deviation_y_DI[row + 1][col];
								mean_counter++;
							}
							if (!_isnan(deviation_y_DI[row + 1][col + 1]))  // ����
							{
								mean_value = mean_value + deviation_y_DI[row + 1][col + 1];
								mean_counter++;
							}

							deviation_y_DI[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

						}  // ��������Чֵ��ֵ����

					} // y�������

				}
			}  // ��Чֵ��������

#pragma endregion ȥ���Ѱ����е���Чֵ




#pragma region ��ʾ�ӿ׾�ͼ��

			if (subApertureImageSwitch->GetCheck() == 1)  // ��ʾWFS��ʵʱͼ��
			{

				// ��ͼ��ˢ���ڴ�
				WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
				// ��ͼ����һάתΪ��ά�������ת��������֤����ȷ��
				for (int row = 0; row < 480; ++row)
				{
					for (int col = 0; col < 480; ++col)
					{
						image2DBuf[row][col] = imageBuf[480 * row + col];
					}
				}
				//----------------------------------------------------------//
				////## ���ͨ��
				//(pW->m_Edit_Sta_Watch).Format(_T("%u"), sizeof(image2DBuf));
				//pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);
				//----------------------------------------------------------//
				// ֮ǰʹ��cvCreateImage���cvReleaseImageʹ�ã������ڴ�й¶
				// ����cvCreateImageHeader��cvReleaseImageHeader�ɶ�ʹ�ã�������ڴ�й¶
				m_img = cvCreateImageHeader(cvSize(480, 480), 8, 1);
				cvSetData(m_img, image2DBuf, 480); // ��һ���������ڴ棬Ӧ����ͨ��cvReleaseImageHeader�ͷŵ�


				// ������TAB�ؼ����ӿ׾���ǩҳ�ϵĶԻ����ϵ�pic�ؼ���ʾ�ӿ׾���ʵʱͼ��
				// ptr_SubApertureImageDlg��pW�ĳ�Ա
				pW->ptr_SubApertureImageDlg->ShowSubApertuerImageFrame();

				// ���ñ�־
				if (CMOSImageFlag == FALSE)
					CMOSImageFlag = TRUE;

			}
			else  // ��ʾû��ͼ��
			{
				if (CMOSImageFlag == TRUE)
				{
					pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
				}
				CMOSImageFlag = FALSE;  // ���ñ�־
			}


#pragma endregion ��ʾ�ӿ׾�ͼ��


			// ֱ�ӻ��ַ��ؽ���ǰ
			WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront_DI);
			
			
			//// ��¼��ǰ��Ϣ
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




			// ����ֱ�ӻ��ַ��õ��Ĳ�ǰ���㲨ǰͳ�Ʋ���
			WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min_ACEMETHOD, &wavefront_max_ACEMETHOD,
				&wavefront_diff_ACEMETHOD, &wavefront_mean_ACEMETHOD, &wavefront_rms_ACEMETHOD, &wavefront_weighted_rms_ACEMETHOD);
			pW->Show_PVRMS(wavefront_diff_ACEMETHOD, wavefront_rms_ACEMETHOD);


			// ����õ�ʵʱ��ǰ�Ѱ�������Ϊһά����
			for (int subapture_counter = 0; subapture_counter < eff_picked.size(); ++subapture_counter)
			{

				row_effsub = eff_picked[subapture_counter][0] - 1;
				col_effsub = eff_picked[subapture_counter][1] - 1;
				// ���Ѱ����ĵ�λ��pixelתΪnm��һ�����ش�С9.9um
				lsqy[2 * subapture_counter] = deviation_x_DI[row_effsub][col_effsub];  // ��ѹ��X����
				lsqy[2 * subapture_counter + 1] = deviation_y_DI[row_effsub][col_effsub];  // ��ѹ��y����

			}	
			// ��¼����֮�������
			//write_1d_File("D:\\externLib\\AOS\\Output\\DEBUG_REARRANGE_deviation_x.txt", lsqy);


			// �������������Ԫ��ִ����
			std::vector <int>::size_type row_num;  // ����
			std::vector <int>::size_type col_num;  // ����
			row_num = lsqA.size();
			col_num = lsqA[0].size();
			for (int row = 0; row < row_num; row++)
			{
				sum_temp = 0;
				for (int col = 0; col < col_num; col++)
				{
					sum_temp = sum_temp + lsqA[row][col] * lsqy[col];
				}

				zernikeMatrix_recon_array_ACEMETHOD[row] = sum_temp * impulse_stroke;  // �õ��ĵ�λ��nm
			}

			// �������ξ�
			P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
			aoSystemData->dDMDesired = zernikeMatrix_recon_array_ACEMETHOD;
			int status = P_DM_SetSpatialFrame();


			// ѡ���Ƿ���ʾִ����(ֱ��б�ʷ�)
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

			wait4U(1500);  // �ȴ�һ��ʱ��

		}  // �ջ�����

	} // if������ֱ��б�ʷ�����



#pragma endregion ֱ��б��
	  


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// �˳��߳�
	return 0;

} // �߳̽���

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ԥ�����̺߳���
UINT ThreadFunc_PreCalculation(LPVOID pParam)
{

#pragma region �ֲ�����

	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	// ��̬�����ļ���Ҫ��std::string����
	std::string fileFullPath, filenamePrefix, finenameSuffix;
	std::string indexCString, XdeviCString, YdeviCString;
	std::string statusCString;

	XdeviCString = "XDevi";
	YdeviCString = "YDevi";
	filenamePrefix = "D:\\externLib\\AOS\\Output\\PreCalc\\in\\";
	finenameSuffix = ".txt";

	// ������״̬����ʾ
	CString indexCString_forreal;


	// ��144��DM��������Ԫ���η������ξ���WFS�����Ӧ�Ĳ�ǰ
	double DM_PreCalc[144];  // ������double������aoSystemData->dDMDesired = DM_PreCalc;����ǿת
	float  deviation_x_PreCalc[40][50];  // x�����Ѱ�������λ����
	float  deviation_y_PreCalc[40][50];  // y�����Ѱ�������λ����
	std::vector<std::vector<double>> deviation_x_nm_PreCalc;  // x����б�����ݣ���λnm
	std::vector<std::vector<double>> deviation_y_nm_PreCalc;   // y����б�����ݣ���λnm
	// Ϊ���������ڴ�ռ�
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


	// �ؽ���ǰ�õ��ı���
	float   wavefront_Impulse[40][50];
	std::vector<std::vector<double>> wavefront_Impulse_Vector; // ���ڱ������ݵ�����
	// Ϊ���������ڴ�ռ�
	wavefront_Impulse_Vector.resize(29); // ������
	for (int index = 0; index < 29; ++index)
	{
		wavefront_Impulse_Vector[index].resize(29);  // ������
	}

	// zernike�ؽ���Ҫ�ı���
	ViInt32		zernike_order_Impulse = 4;
	float		zernike_um_Impulse[16];  // 0Ϊ�������ݣ�1~15Ϊzernikeϵ��
	float		zernike_orders_rms_um_Impulse[11];
	double		roc_mm_Impulse;

	// WFS���ش�С4.65um�����ڽ���λ��pixelת��Ϊnm
	float  unitCoeff = 1;


	// zernike�ؽ�ʱҪ�������
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

	// ����ֱ��б�ʷ�Ԥ�����н���ǰ��Ϣд���ļ���
	std::vector<std::vector<double>> zernikeMatrix_recon_ACEMETHOD_PreCalc;
	zernikeMatrix_recon_ACEMETHOD_PreCalc.resize(29);  // ���������·����ڴ�ռ�
	for (int index = 0; index < 29; ++index)
	{
		zernikeMatrix_recon_ACEMETHOD_PreCalc[index].resize(29);
	}

#pragma endregion �ֲ�����



	for (int index = 0; index < 144; ++index)
	{
		// int����ת��Ϊstd::string���ͣ����ڱ����ļ�ʹ��
		IntToString(indexCString, index);


		// ���θ��ı��ξ�
		for (int i = 0; i < 144; ++i)
		{
			DM_PreCalc[i] = bias_initial;
		}
		DM_PreCalc[index] = bias_initial + impulse_stroke;

		// ����DM
		P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
		aoSystemData->dDMDesired = DM_PreCalc;
		int status = P_DM_SetSpatialFrame();

		// ��ͨģʽ��ȡ����λ��
		WFS_TakeSpotfieldImage(instr.handle);
		// ��������λ��
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
		// �����Ѱ���
		WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
		// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
		WFS_GetSpotDeviations(instr.handle, *deviation_x_PreCalc, *deviation_y_PreCalc);


#pragma region ȥ���Ѱ����е���Чֵ



		// �Ѱ���Ϊ29x29���߽��������

		deviation_x_PreCalc[0][0] = 0; deviation_x_PreCalc[0][28] = 0; deviation_x_PreCalc[28][0] = 0; deviation_x_PreCalc[28][28] = 0;  // �ĸ�������
		deviation_y_PreCalc[0][0] = 0; deviation_y_PreCalc[0][28] = 0; deviation_y_PreCalc[28][0] = 0; deviation_y_PreCalc[28][28] = 0;  // �ĸ�������

		// ����������������
		for (int col = 1; col < 28; ++col)  // ��0��
		{
			deviation_x_PreCalc[0][col] = 0;
			deviation_y_PreCalc[0][col] = 0;
		}
		for (int col = 1; col < 28; ++col)  // ��28��
		{
			deviation_x_PreCalc[28][col] = 0;
			deviation_y_PreCalc[28][col] = 0;
		}
		for (int row = 1; row < 28; ++row)  // ��0��
		{
			deviation_x_PreCalc[row][0] = 0;
			deviation_y_PreCalc[row][0] = 0;
		}
		for (int row = 1; row < 28; ++row)  // ��28��
		{
			deviation_x_PreCalc[row][28] = 0;
			deviation_y_PreCalc[row][28] = 0;
		}


		// ���м�����ݽ���ƽ����ֵ
		for (int row = 1; row < 28; ++row)  // �ճ�����������
		{
			for (int col = 1; col < 28; ++col) // �ճ�����������
			{

				// �ж�x����
				if (_isnan(deviation_x_PreCalc[row][col]))
				{
					// ���з�ʽ
					//  x x x
					//  x o x
					//  x x x

					if (_isnan(deviation_x_PreCalc[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
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
						// ���з�ʽ
						//  x x x
						//  x o x
						//  x x x

						int mean_counter = 0;  // ��Чֵ����
						float mean_value = 0;  // ��Чֵ�ĺ�

						if (!_isnan(deviation_x_PreCalc[row - 1][col - 1]))  // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row - 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row - 1][col])) // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row - 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row - 1][col + 1])) // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row - 1][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row][col - 1])) // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row][col + 1])) // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row + 1][col - 1])) // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row + 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row + 1][col]))  // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row + 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_x_PreCalc[row + 1][col + 1]))  // ����
						{
							mean_value = mean_value + deviation_x_PreCalc[row + 1][col + 1];
							mean_counter++;
						}

						deviation_x_PreCalc[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

					}


				}  // x�������



				// �ж�y����
				if (_isnan(deviation_y_PreCalc[row][col]))
				{

					// ���з�ʽ
					//  x x x
					//  x o x
					//  x x x

					if (_isnan(deviation_y_PreCalc[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
						_isnan(deviation_y_PreCalc[row - 1][col]) &&
						_isnan(deviation_y_PreCalc[row - 1][col + 1]) &&
						_isnan(deviation_y_PreCalc[row][col - 1]) &&
						_isnan(deviation_y_PreCalc[row][col + 1]) &&
						_isnan(deviation_y_PreCalc[row + 1][col - 1]) &&
						_isnan(deviation_y_PreCalc[row + 1][col]) &&
						_isnan(deviation_y_PreCalc[row + 1][col + 1]))
					{

						deviation_y_PreCalc[row][col] = 0;
					} // ǿ���������
					else
					{
						// ���з�ʽ
						//  x x x
						//  x o x
						//  x x x

						int mean_counter = 0;  // ��Чֵ����
						float mean_value = 0;  // ��Чֵ�ĺ�

						if (!_isnan(deviation_y_PreCalc[row - 1][col - 1]))  // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row - 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row - 1][col])) // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row - 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row - 1][col + 1])) // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row - 1][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row][col - 1])) // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row][col + 1])) // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row][col + 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row + 1][col - 1])) // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row + 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row + 1][col]))  // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row + 1][col];
							mean_counter++;
						}
						if (!_isnan(deviation_y_PreCalc[row + 1][col + 1]))  // ����
						{
							mean_value = mean_value + deviation_y_PreCalc[row + 1][col + 1];
							mean_counter++;
						}

						deviation_y_PreCalc[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

					}  // ��������Чֵ��ֵ����

				} // y�������

			}
		}  // ��Чֵ��������


#pragma endregion ȥ���Ѱ����е���Чֵ


		// �����������ͣ�������д���ļ�
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{
				deviation_x_nm_PreCalc[row][col] = deviation_x_PreCalc[row][col] * unitCoeff;
				deviation_y_nm_PreCalc[row][col] = deviation_y_PreCalc[row][col] * unitCoeff;
			}
		}


#pragma region ֱ�ӻ��ַ��ؽ�Impulse��ǰ

		// ͨ���Ѱ�������ֱ�ӻ��ַ�������ؽ���ǰ
		WFS_CalcWavefront(instr.handle, 0, 0, *wavefront_Impulse);


#pragma region ȥ��ֱ�ӻ��ַ��ؽ���ǰ����Чֵ

		// �Ѱ���Ϊ29x29���߽��������
		wavefront_Impulse[0][0] = 0; wavefront_Impulse[0][28] = 0; wavefront_Impulse[28][0] = 0; wavefront_Impulse[28][28] = 0;  // �ĸ�������

		// ����������������
		for (int col = 1; col < 28; ++col)  // ��0��
		{
			wavefront_Impulse[0][col] = 0;
		}
		for (int col = 1; col < 28; ++col)  // ��28��
		{
			wavefront_Impulse[28][col] = 0;
		}
		for (int row = 1; row < 28; ++row)  // ��0��
		{
			wavefront_Impulse[row][0] = 0;
		}
		for (int row = 1; row < 28; ++row)  // ��28��
		{
			wavefront_Impulse[row][28] = 0;
		}


		// ���м�����ݽ���ƽ����ֵ
		for (int row = 1; row < 28; ++row)  // �ճ�����������
		{
			for (int col = 1; col < 28; ++col) // �ճ�����������
			{

				if (_isnan(wavefront_Impulse[row][col]))
				{
					// ���з�ʽ
					//  x x x
					//  x o x
					//  x x x

					if (_isnan(wavefront_Impulse[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
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
						// ���з�ʽ
						//  x x x
						//  x o x
						//  x x x

						int mean_counter = 0;  // ��Чֵ����
						float mean_value = 0;  // ��Чֵ�ĺ�

						if (!_isnan(wavefront_Impulse[row - 1][col - 1]))  // ����
						{
							mean_value = mean_value + wavefront_Impulse[row - 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row - 1][col])) // ����
						{
							mean_value = mean_value + wavefront_Impulse[row - 1][col];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row - 1][col + 1])) // ����
						{
							mean_value = mean_value + wavefront_Impulse[row - 1][col + 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row][col - 1])) // ����
						{
							mean_value = mean_value + wavefront_Impulse[row][col - 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row][col + 1])) // ����
						{
							mean_value = mean_value + wavefront_Impulse[row][col + 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row + 1][col - 1])) // ����
						{
							mean_value = mean_value + wavefront_Impulse[row + 1][col - 1];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row + 1][col]))  // ����
						{
							mean_value = mean_value + wavefront_Impulse[row + 1][col];
							mean_counter++;
						}
						if (!_isnan(wavefront_Impulse[row + 1][col + 1]))  // ����
						{
							mean_value = mean_value + wavefront_Impulse[row + 1][col + 1];
							mean_counter++;
						}

						wavefront_Impulse[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

					}


				}

			}
		}  // ��Чֵ��������

#pragma endregion ȥ��ֱ�ӻ��ַ��ؽ���ǰ����Чֵ


		// �����鸳ֵ������
		for (int row = 0; row < 29;++row)
		{
			for (int col = 0; col < 29;++col)
			{

				wavefront_Impulse_Vector[row][col] = wavefront_Impulse[row][col];

			}
		}
		fileFullPath = filenamePrefix + "ImpulseWavefrontDirect" + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, wavefront_Impulse_Vector);  // ��¼ֱ�ӻ��ַ��ؽ��Ĳ�ǰ

#pragma endregion ֱ�ӻ��ַ��ؽ�Impulse��ǰ


#pragma region zernike��Ϸ��ؽ�Impulse��ǰ

		// ͨ���Ѱ�������Zernike��Ϸ�������ؽ���ǰ
		WFS_ZernikeLsf(instr.handle, &zernike_order_Impulse, zernike_um_Impulse, zernike_orders_rms_um_Impulse, &roc_mm_Impulse);

		// ����zernikeϵ���ؽ���ǰ
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
		write_2d_File(fileFullPath, zernikeMatrix_recon_ACEMETHOD_PreCalc);  // ��¼zernike��Ϸ��ؽ��Ĳ�ǰ


#pragma endregion zernike��Ϸ��ؽ�Impulse��ǰ


		wait4U(300); // �ӳ�300ms


		// ��x�Ѱ���д���ļ�
		fileFullPath = filenamePrefix + XdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_x_nm_PreCalc);
		// ��y�Ѱ���д���ļ�
		fileFullPath = filenamePrefix + YdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_y_nm_PreCalc);


		indexCString_forreal.Format(_T("%d"), index);
		str_showerror = _T("Ԥ�������ݣ�  ") + indexCString_forreal;
		pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

	}  // ����������б��ξ���Ԫ�����庯��


	str_showerror = _T("Ԥ�������");
	pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);


	return 0;

}  // Ԥ�����̺߳�������

////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region

// C���ķ�ʽ��¼���������

// ������λ��д���ļ�
int WFS_WriteSpotCentroids()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_SpotCentroids_X.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_SpotCentroids_X�ļ� ��"), _T("д��״̬"), MB_OK);
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
		::MessageBox(NULL, _T("�޷���WFS_SpotCentroids_Y�ļ� ��"), _T("д��״̬"), MB_OK);
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
		::MessageBox(NULL, _T("�޷���WFS_CalcReconstrDeviations�ļ� ��"), _T("д��״̬"), MB_OK);
		return -1;
	}

	fprintf(fp, "fitErrMean��  %lf \n", fitErrMean);
	fprintf(fp, "fitErrStdev�� %lf \n", fitErrStdev);

	fclose(fp);

	return 0;
}



// ����ǰ��Zernike����д���ļ�
int WFS_WriteZernikeMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_WriteZernikeMatrix.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_WriteZernikeMatrix�ļ� ��"), _T("д��״̬"), MB_OK);
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


// ��wavefront��zerWave_Matrix29����ļ������д���ļ�
int WFS_WriteWavefrontZernikeError()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_WavefrontZernikeError.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_WavefrontZernikeError�ļ� ��"), _T("д��״̬"), MB_OK);
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



// ���ھ�̬У����ǰʱ��У��matlab�����zernike��Ͼ���
int DM_WriteCheckZernikeMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\conDM\\DM_CheckZernikeMatrix.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���DM_CheckZernikeMatrix�ļ� ��"), _T("д��״̬"), MB_OK);
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


// ���ڽ�������ľ���д���ļ�
int DM_WriteTransposeMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\conDM\\DM_TransposeZernikeMatrix.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���DM_TransposeZernikeMatrix�ļ� ��"), _T("д��״̬"), MB_OK);
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


// ���ڽ�һά������д���ļ�����д����ξ���һά����
int DM_Write1DMatrix()
{
	FILE  *fp;

	fp = fopen("D:\\externLib\\AOS\\Output\\DM_1DArray.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���DM_1DArray�ļ� ��"), _T("Writing Status"), MB_OK);
		return -1;
	}

	for (int i = 0; i < MAX_ZERNIKE_MODES + 1; ++i)
	{
		fprintf(fp, "%f", DM_Stroke_1D[i]);  // 144��Ԫ��
		fputc('\n', fp);
	}
	fclose(fp);


	return 0;
}

#pragma endregion 




#pragma region mapping   

// �����Ϊ��ͨ�汾��vector�汾

// ����ת��
int MatrixTranspose(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12����
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[j][i] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29����
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[j][i] = matrixIn[i][j];
	}

	return 0;
}

// �������ҷ�ת
int MatrixFlipLeftRight(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12����
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[i][11 - j] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29����
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[i][28 - j] = matrixIn[i][j];
	}

	return 0;
}

// �������·�ת
int MatrixFlipUpDown(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12����
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[11 - i][j] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29����
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[28 - i][j] = matrixIn[i][j];
	}

	return 0;
}

// ����˳ʱ����ת90��=���·�ת��ת��
int MatrixRotate90(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12����
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[j][11 - i] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29����
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[j][28 - i] = matrixIn[i][j];
	}

	return 0;
}

// ����˳ʱ����ת180��=���ҷ�ת�����·�ת
int MatrixRotate180(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12����
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[11 - i][11 - j] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29����
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[28 - i][28 - j] = matrixIn[i][j];
	}

	return 0;
}

// ����˳ʱ����ת270��=���ڷ�ת����ת��
int MatrixRotate270(int gridIndex, float** matrixOut, float** matrixIn)
{
	if (gridIndex == 0) // 12x12����
	{
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				matrixOut[11 - j][i] = matrixIn[i][j];
	}
	else if (gridIndex == 1)  // 29x29����
	{
		for (int i = 0; i < 29; ++i)
			for (int j = 0; j < 29; ++j)
				matrixOut[28 - j][i] = matrixIn[i][j];
	}

	return 0;
}

// ������vector�汾�ľ�����ת
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
	// ���·�ת
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[11 - i][j] = matrixIn[i][j];

	return 0;
}

int MatrixFlipLeftRight_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn)
{
	// ���ҷ�ת
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			matrixOut[i][11 - j] = matrixIn[i][j];

	return 0;
}



#pragma endregion mapping


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������°��д���ļ��ĺ�������Ҫ������ʹ����std::vector������ϣ���ܹ��𲽴���֮ǰ��C����ȫ�ֺ���

// д��һά����
// �����������㷨
int write_1d_File(const std::string& filename, std::vector<double>& array_1d)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out);
	std::vector<double>::iterator iter;


	if (!file)
	{
		std::cerr << "�޷���Ҫд����ļ���\"" << filename << "\"" << std::endl;
		exit(EXIT_FAILURE);
	}

	for (iter = array_1d.begin(); iter != array_1d.end(); ++iter)
	{
		file << *iter << std::endl;
	}

	return 1;
}


// д���ά����
// �����������㷨
int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out);

	std::vector<std::vector<double>>::iterator iter_row;	
	std::vector<double>::iterator iter_col;			


	if (!file)
	{
		std::cerr << "�޷���Ҫд����ļ���\"" << filename << "\"" << std::endl;
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


// �����������㷨
MyMat_double inputMatrix(const std::string& filename)
{
	// Ҫ�򿪵��ļ�
	std::ifstream inputMatrixfile(filename);
	// ���صĶ�άvector����
	MyMat_double inputMatrixMatrix;

	std::istringstream istr;
	std::string str;  // Ӧ���ǰ��ж��������
	std::vector<double> tmpvec;

	// ��������
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


// �����������㷨
int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col)
{
	std::vector<double> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// ���ذ汾
// �����������㷨
int init_2dVector(std::vector<std::vector<int>>&vectordata, const int row, const int col)
{
	std::vector<int> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// �ͷŶ�άvector����
// �����������㷨
int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// ���ذ汾
// �����������㷨
int release_2dVector(std::vector<std::vector<int>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// һάvector��ʼ��
// �����������㷨
int init_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.push_back(0);

	return 0;

}

// �ͷ�һάvector����
// �����������㷨
int release_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;

}




// ���ڵȴ�һ��ʱ��ĺ���������ʱ�䵥λms
// �����������㷨
int wait4U(int time_milliseconds) 
{

	//�¼�ʱ����ʼ
	LARGE_INTEGER nStartCounter_dmwait;
	LARGE_INTEGER nFrequency_dmwait;
	double nTime_dmwait = 0; // ��¼ʱ��

	::QueryPerformanceCounter(&nStartCounter_dmwait);
	::QueryPerformanceFrequency(&nFrequency_dmwait);


	do
	{
		LARGE_INTEGER nStopCounter_dmwait;
		::QueryPerformanceCounter(&nStopCounter_dmwait);
		nTime_dmwait = 1000 * ((double)nStopCounter_dmwait.QuadPart - (double)nStartCounter_dmwait.QuadPart) / (double)nFrequency_dmwait.QuadPart;    // ��λ ms
	} while (nTime_dmwait < time_milliseconds);


	return 0;  // �ɹ�����0
}



// �����������ξ��ĺ�������λ��nm
// �����������㷨
int DriveDeformMirror_nm(double(&executeStroke)[140])
{

	// ��ִ�������͸����ξ����������˶�
	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = executeStroke;
	P_DM_SetSpatialFrame();   // ����nm��λ�������ξ���������������г̵ķֱ����Ƕ��٣�


	return 0;  // �ɹ�����0

}


// ����̽�Ⲩǰ���Ѱ���(����������ͨģʽ)
// �����������㷨
int Detect_Wavefront2Deviation_Normal()
{

	// ��ͨģʽ��ȡ����λ��
	WFS_TakeSpotfieldImage(instr.handle);

	// ��������λ��
	WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);

	// �����Ѱ���
	WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);

	// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
	WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);


	return 0;

}

// ����ֱ�Ӵ����Ѱ�������֤����������û����Чֵ����������ͨģʽ�����ģʽ��������ܰ�����Чֵ���Ѱ��������ȫ����Ч���Ѱ���
// ���������㷨
int MeanInterpolation_KillNAN()
{

	// �Ѱ���Ϊ29x29���߽��������

	deviation_x[0][0] = 0; deviation_x[0][28] = 0; deviation_x[28][0] = 0; deviation_x[28][28] = 0;  // �ĸ�������
	deviation_y[0][0] = 0; deviation_y[0][28] = 0; deviation_y[28][0] = 0; deviation_y[28][28] = 0;  // �ĸ�������

	// ����������������
	for (int col = 1; col < 28; ++col)  // ��0��
	{
		deviation_x[0][col] = 0;
		deviation_y[0][col] = 0;
	}
	for (int col = 1; col < 28; ++col)  // ��28��
	{
		deviation_x[28][col] = 0;
		deviation_y[28][col] = 0;
	}
	for (int row = 1; row < 28; ++row)  // ��0��
	{
		deviation_x[row][0] = 0;
		deviation_y[row][0] = 0;
	}
	for (int row = 1; row < 28; ++row)  // ��28��
	{
		deviation_x[row][28] = 0;
		deviation_y[row][28] = 0;
	}


	// ���м�����ݽ���ƽ����ֵ
	for (int row = 1; row < 28; ++row)  // �ճ�����������
	{
		for (int col = 1; col < 28; ++col) // �ճ�����������
		{

			// �ж�x����
			if (_isnan(deviation_x[row][col]))
			{
				// ���з�ʽ
				//  x x x
				//  x o x
				//  x x x

				if (_isnan(deviation_x[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
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
					// ���з�ʽ
					//  x x x
					//  x o x
					//  x x x

					int mean_counter = 0;  // ��Чֵ����
					float mean_value = 0;  // ��Чֵ�ĺ�

					if (!_isnan(deviation_x[row - 1][col - 1]))  // ����
					{
						mean_value = mean_value + deviation_x[row - 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row - 1][col])) // ����
					{
						mean_value = mean_value + deviation_x[row - 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row - 1][col + 1])) // ����
					{
						mean_value = mean_value + deviation_x[row - 1][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row][col - 1])) // ����
					{
						mean_value = mean_value + deviation_x[row][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row][col + 1])) // ����
					{
						mean_value = mean_value + deviation_x[row][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row + 1][col - 1])) // ����
					{
						mean_value = mean_value + deviation_x[row + 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row + 1][col]))  // ����
					{
						mean_value = mean_value + deviation_x[row + 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_x[row + 1][col + 1]))  // ����
					{
						mean_value = mean_value + deviation_x[row + 1][col + 1];
						mean_counter++;
					}

					deviation_x[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

				}


			}  // x�������



			// �ж�y����
			if (_isnan(deviation_y[row][col]))
			{

				// ���з�ʽ
				//  x x x
				//  x o x
				//  x x x

				if (_isnan(deviation_y[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
					_isnan(deviation_y[row - 1][col]) &&
					_isnan(deviation_y[row - 1][col + 1]) &&
					_isnan(deviation_y[row][col - 1]) &&
					_isnan(deviation_y[row][col + 1]) &&
					_isnan(deviation_y[row + 1][col - 1]) &&
					_isnan(deviation_y[row + 1][col]) &&
					_isnan(deviation_y[row + 1][col + 1]))
				{

					deviation_y[row][col] = 0;
				} // ǿ���������
				else
				{
					// ���з�ʽ
					//  x x x
					//  x o x
					//  x x x

					int mean_counter = 0;  // ��Чֵ����
					float mean_value = 0;  // ��Чֵ�ĺ�

					if (!_isnan(deviation_y[row - 1][col - 1]))  // ����
					{
						mean_value = mean_value + deviation_y[row - 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row - 1][col])) // ����
					{
						mean_value = mean_value + deviation_y[row - 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row - 1][col + 1])) // ����
					{
						mean_value = mean_value + deviation_y[row - 1][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row][col - 1])) // ����
					{
						mean_value = mean_value + deviation_y[row][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row][col + 1])) // ����
					{
						mean_value = mean_value + deviation_y[row][col + 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row + 1][col - 1])) // ����
					{
						mean_value = mean_value + deviation_y[row + 1][col - 1];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row + 1][col]))  // ����
					{
						mean_value = mean_value + deviation_y[row + 1][col];
						mean_counter++;
					}
					if (!_isnan(deviation_y[row + 1][col + 1]))  // ����
					{
						mean_value = mean_value + deviation_y[row + 1][col + 1];
						mean_counter++;
					}

					deviation_y[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ

				}  // ��������Чֵ��ֵ����

			} // y�������

		}
	}  // ��Чֵ��������

	return 0;
}


// ���㲢�������ۺ��������ۺ����ļ��㷽ʽ�ǣ�x��y������Ѱ���ƽ����ӣ���󿪸��ŵõ�
// �����ݶ��㷨��ʹ��
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




#pragma endregion ȫ�ֺ���



//----------------------------------------------------    ----------------------------------------------------//






#pragma region ��װΪ��Ա����

// ��װΪ��ĳ�Ա��������ʾPVֵ��RMS�Լ����ۺ���
// �����ݶ��㷨��ʹ��
int CAOSys_v8Dlg::Show_MeritPVRMS(double merit, double PV, double RMS)
{

	// ��ʾ���ۺ���ֵ
	m_Edit_ShowMerit.Format(_T("%lf"), merit);
	SetDlgItemTextW(IDC_EDIT_SHOWMERIT, m_Edit_ShowMerit);

	// ��ʾPV
	m_Edit_Sta_PV.Format(_T("%lf"), PV);
	SetDlgItemTextW(IDC_EDIT_STA_PV, m_Edit_Sta_PV);

	// ��ʾRMS
	m_Edit_Sta_RMS.Format(_T("%lf"), RMS);
	SetDlgItemTextW(IDC_EDIT_STA_RMS, m_Edit_Sta_RMS);


	return 0;
}


// ��ʱ��������ʱ����
// �������������㷨
int CAOSys_v8Dlg::Timer_SetTimer(double settimer)
{

	//-----------------------------------------------------
	//��ʱ����ʼ
	LARGE_INTEGER nStartCounter_wait;
	LARGE_INTEGER nFrequency_wait;
	double nTime_wait = 0; // ��¼ʱ��
	::QueryPerformanceCounter(&nStartCounter_wait);
	::QueryPerformanceFrequency(&nFrequency_wait);
	//-----------------------------------------------------

	if (ptr_MiscSettingDlg->m_Check_SubDlg_TimeSetter.GetCheck() == 1)  // ѡ���Ƿ���м�ʱ
	{

		do
		{

			//-----------------------------------------------------
			// ��ʱ������
			LARGE_INTEGER nStopCounter_wait;
			::QueryPerformanceCounter(&nStopCounter_wait);
			nTime_wait = 1000 * ((double)nStopCounter_wait.QuadPart - (double)nStartCounter_wait.QuadPart) / (double)nFrequency_wait.QuadPart;    // ��λ ms
			//��ʾ��ʱ��
			m_Edit_Show_NewTimer.Format(_T("%lf"), nTime_wait);
			SetDlgItemText(IDC_EDIT_SHOW_NEWTIMER, m_Edit_Show_NewTimer);
			//-----------------------------------------------------


		} while (nTime_wait < settimer);


	}
	else
	{
		// û�ж�ʱ����ִ��
	}


	return 0;
}



// ������ת12x12����ľ���
// �����������㷨
int CAOSys_v8Dlg::rotateMatrix_12vector(int angle, std::vector<std::vector<double>>& origin, std::vector<std::vector<double>>& modified)
{

	// ������ת����
	if (90 == angle)  // ˳ʱ����ת90�ȣ����涼��˳ʱ��
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
	else if (1 == angle)   // ���·�ת
	{
		MatrixFlipUpDown_vector(modified, origin);
	}
	else if (2 == angle) // ���ҷ�ת
	{
		MatrixFlipLeftRight_vector(modified, origin);
	}
	else if (3 == angle)  // ���·�ת�����ҷ�ת
	{
		MatrixFlipUpDown_vector(modified, origin);
		MatrixFlipLeftRight_vector(modified, origin);
	}
	else
	{
		// Ĭ��
		MatrixRotate0_vector(modified, origin);
	}


	return 0;
}




int CAOSys_v8Dlg::Show_PVRMS(double PV, double RMS)
{
	// ��ʾPV
	m_Edit_Sta_PV.Format(_T("%lf"), PV);
	SetDlgItemTextW(IDC_EDIT_STA_PV, m_Edit_Sta_PV);

	// ��ʾRMS
	m_Edit_Sta_RMS.Format(_T("%lf"), RMS);
	SetDlgItemTextW(IDC_EDIT_STA_RMS, m_Edit_Sta_RMS);

	return 0;
}


#pragma endregion ��װΪ��Ա����
