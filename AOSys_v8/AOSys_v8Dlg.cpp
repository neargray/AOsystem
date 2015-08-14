
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
	m_tabDisplay.InsertItem(1, _T("��ǰʵʱ�ؽ�ͼ��"));
	m_tabDisplay.InsertItem(2, _T("���ξ����ƾ���"));
	m_tabDisplay.InsertItem(3, _T("�Ѱ���"));
	m_tabDisplay.InsertItem(4, _T("��������"));



	// ��ÿ���Ի����ʼ��ָ�룬���ָ������ͷţ�����һ��ȫ�ֵ�ָ��ɣ�
	ptr_SubApertureImageDlg = new CSubApertureDlg();
	ptr_ReconWavefrontDlg = new CReconWavefrontDlg();
	ptr_DeformMirrorDlg = new CDeformMirrorDlg();
	ptr_DeviationXDlg = new CDeviationXDlg();
	ptr_MiscSettingDlg = new CMiscSettingDlg();



	// ����Ӧ��TAB�ؼ���ǩҳ�ϴ����Ի���
	ptr_SubApertureImageDlg->Create(IDD_DIALOG_SUBAPERTURE, &m_tabDisplay);
	ptr_ReconWavefrontDlg->Create(IDD_DIALOG_RECONWAVEFRONT, &m_tabDisplay);
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


	// ���ݵ����õ�tabRect����m_SubApertureDlg�ӶԻ��򣬲�����Ϊ��ʾ   
	ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// ���ݵ����õ�tabRect����m_ReconWavefontDlg�ӶԻ��򣬲�����Ϊ����   
	ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ���� 
	ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	// ͬ��
	ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	// ͬ��
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
	m_Combo_ChooseAlgo.SetCurSel(2);  // Ĭ���㷨ѡ���һ��



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
AOSystemData		aoSystemData_LOCAL;


//     WFS_32
int               err;
int               selection;

double            expos_act, master_gain_act;
ViInt32		      blackLevelOffsetAct;  // ��ʼֵ����Ϊ50
ViInt32			  NoiseCutAct;
ViReal64          beam_centroid_x = 0;
ViReal64		  beam_centroid_y = 0;
double            beam_diameter_x = 0;
double			  beam_diameter_y = 0;

// ����λ��
float             centroid_x[40][50];
float             centroid_y[40][50];

// �ο�λ��
float             reference_x[40][50];
float             reference_y[40][50];


// �Ѱ�����λ��
float             deviation_x[40][50];
float             deviation_y[40][50];
float			  rememberDeviationX[40][50][100]; // ���ڼ�¼ÿ��ʱ���Ѱ�����ֵ
float			  rememberDeviationY[40][50][100]; // ���ڼ�¼ÿ��ʱ���Ѱ�����ֵ



float             wavefront[40][50];
float             Wavefront_Copy[29][29];

float             zernike_um[MAX_ZERNIKE_MODES + 1];    // �����Ŵ�1��MAX_ZERNIKE_MODES����������ж�Ӧ�ľֲ�������vector�汾vector_zernike_um
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
int				Mapping = 0;

int				gridIndex = 0;  // 0��12x12������1��29x29������



#pragma region ��ǰ���㽻������


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

// zernike��Ϻ�ľ��󣬼���ϲ�ǰ�����������12x12������Ҫ��Ϊһά���ݲ�ȥ����ӦԪ�غ󷢸�DM
std::vector<std::vector<double>> zernikeMatrix_recon;
std::vector<std::vector<double>> zernikeMatrix_recon_rotate;
std::vector<double> zernikeMatrix_recon_ParaCal(144);   //���ֵ��RMSֵ�õ�һά��ʽ




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



// ���շ������ξ����ڱջ��ı���
double zernikeMatrix_recon_array[140];




#pragma endregion ��ǰ���㽻������




// ����ģʽ�¶���λ�õ�����λ��
// ������ʽ
float			XScale_array[50];
float			YScale_array[40];

// ������ʽ
std::vector<float> XScale_vector(50);
std::vector<float> YScale_vector(40);

// ��Matlab����õ�CppData��picked����
std::vector<std::vector<double>>	lsqA;
std::vector<std::vector<double>>	eff_picked;

BOOL CloseLoopFlag = FALSE;

// ��������ͼ���йصı���
ViUInt8			imageBuf[480 * 480 + 10];  // һά��ʽ
ViPInt32		row_image;
ViPInt32		col_image;
IplImage*		m_img;  // ��ȡͼƬ
BOOL			CMOSImageFlag = TRUE;

// PID��������ȫ�ֱ�������ʽ�����߳�֮�佻��
double pid_p, pid_i, pid_d;
double DM_PID_P[140];
double DM_PID_I[140];
double DM_PID_D[140];

// �������ƫ��
double coordMoveX = 0;
double coordMoveY = 0;

// �ӶԻ����ȫ�ֱ���
double timerSetterInterval = 0;


int angleRotate = 0;

int chooseAlgoIndex = 2;

////////////////////////////// �ݶȺ�����ȫ�ֱ���  //////////////////////////////////

double randomMatrix[140];			// ���ɵ��������
std::vector<std::vector<double>> zernikeMatrix_recon_ADD; // �Ӳ�����ִ����
std::vector<std::vector<double>> zernikeMatrix_recon_MINUS; // ��������ִ����

// Ĭ�ϲ����������ξ�
double zernikeMatrix_recon_array_DEFAULT[140];
// �Ӳ��������շ������ξ����ڱջ��ı�������ӦzernikeMatrix_recon_array[140]
double zernikeMatrix_recon_array_ADD[140];
// �����������շ������ξ����ڱջ��ı�������ӦzernikeMatrix_recon_array[140]
double zernikeMatrix_recon_array_MINUS[140];

// ���ڴ洢�Ӳ����Ĳ�ǰͳ�Ʋ���
double     wavefront_min_add, wavefront_max_add, wavefront_diff_add, wavefront_mean_add, wavefront_rms_add, wavefront_weighted_rms_add;
// ���ڴ洢�������Ĳ�ǰͳ�Ʋ���
double     wavefront_min_minus, wavefront_max_minus, wavefront_diff_minus, wavefront_mean_minus, wavefront_rms_minus, wavefront_weighted_rms_minus;




// �뱨����صı���������д������IDC_STATIC_SHOW_ERROR�ؼ�����ʾ����
BOOL FLAG_NAN = 0;  // 0��ʾû��NAN���ݣ�1��ʾ��NAN����
CString str_showerror;    // ����״̬���ַ�����ʾ
double NAN_deviationXY[100][29][29];


double bias_initial = 1200;   // �����Ӧ������ƫ��������λnm
double impulse_stroke = 1300;  // �����Ӧ�����ĳ��������λnm


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
	coeff[0] = 0.0227;
	coeff[1] = 12.082;
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

#pragma region �����ݷ��͸�DM
	// ����Ҳ����Ҫһ��������ת�Ĺ���




	// ��άvectorתΪһάvector��ɾ��4�����ϵ�Ԫ�أ�תΪһά����
	std::vector<double> zernikeMatrix_recon_1d(144);		// ��������ʼ��һ��һάvector
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			zernikeMatrix_recon_1d[i * 12 + j] = zernikeMatrix_recon[i][j];
	// Ҫɾ��4��Ԫ��
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin());
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 10);
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 130);
	zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 140);
	//��140��Ԫ�ص�һάvectorתΪ����, ɾ��Ԫ��֮���һάvector����������ļ�
	double zernikeMatrix_recon_array[140] = { 0 };
	for (int i = 0; i < 140; ++i)
	{
		// ��������µļ��������͸����ξ�
		zernikeMatrix_recon_array[i] = zernikeMatrix_recon_array[i] + zernikeMatrix_recon_1d[i] * 500 * 0.2;
		// ����״̬�£���0ֵ���͸����ξ�
		//zernikeMatrix_recon_array[i] = 0;
	}


	//## ����Ҫ��һ��ת������vectorת��Ϊ����
	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = zernikeMatrix_recon_array;  // dDMDesired�ĵ�λ��nm
	int status = P_DM_SetSpatialFrame();

	// ����ά��һά�ľ���д���ļ�
	write_2d_File("D:\\externLib\\AOS\\Output\\Recon_zernikeMatrix2D.txt", zernikeMatrix_recon);
	write_1d_File("D:\\externLib\\AOS\\Output\\Recon_zernikeMatrix1D.txt", zernikeMatrix_recon_1d);

	//## ����zernikeMatrix_recon��ǧ��Ҫpop���������ݻ�һֱ�ѻ�
	release_2dVector(zernikeMatrix_recon, 12);
	release_1dVector(zernikeMatrix_recon_1d, 140);

#pragma endregion �����ݷ��͸�DM




}// ��ǰ�ؽ�ģʽ�¿��Ʊ��ξ�



void CAOSys_v8Dlg::OnClickedButtonDmZero()
{

	// ��ʼ���ֲ�����
	std::vector<double> test_zernikeMatrix_recon_1d(144);
	double test_zernikeMatrix_recon_array[140];
	double generateWavefront[12][12];


	// ����һ����б�Ļ���
	zernike(1, -1, 12, instr_setup.pupil_dia_x_mm, zernikeMatrix_02, pupil, coordMoveX, coordMoveY);

	for (int row = 0; row < 12; ++row)
	{
		for (int col = 0; col < 12; ++col)
		{
			generateWavefront[row][col] = zernikeMatrix_02[row][col];
		}
	}


	// ��ά����תΪһά����
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			test_zernikeMatrix_recon_1d[i * 12 + j] = generateWavefront[i][j];

	// Ҫɾ��4��Ԫ��
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin());
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin() + 10);
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin() + 130);
	test_zernikeMatrix_recon_1d.erase(test_zernikeMatrix_recon_1d.begin() + 140);

	//��140��Ԫ�ص�һάvectorתΪ����, ɾ��Ԫ��֮���һάvector����������ļ�
	for (int i = 0; i < 140; ++i)
	{

		// P����
		DM_PID_P[i] = DM_PID_P[i] + test_zernikeMatrix_recon_1d[i] * 500 * pid_p;

		test_zernikeMatrix_recon_array[i] = 1200 + DM_PID_P[i];  // P����

	}




	//## ����Ҫ��һ��ת������vectorת��Ϊ����
	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = test_zernikeMatrix_recon_array;
	int status = P_DM_SetSpatialFrame();


	// ���ڴ��е�ֵˢ��EDIT�ؼ���ʾ
	float temp = 0;
	for (int k_index = 0; k_index < 144; ++k_index)
	{
		temp = generateWavefront[k_index / 12][k_index % 12];
		(ptr_DeformMirrorDlg->m_Edit_DM[k_index]).Format(_T("%lf"), temp);
		SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, ptr_DeformMirrorDlg->m_Edit_DM[k_index]);

	}


}



// ����Zernike������
// ѡ����ʵ�����WFS̽�⵽�Ĳ�ǰ��ȥZernike��ϵĲ�ǰ
void CAOSys_v8Dlg::OnClickedButtonRecZerfiterr()
{
	// ���������������29x29���������£���wavefront�Ĳ�����ǰ����Zernike�ؽ���ǰ���ҵ�Zernike�ؽ���ǰ��������Ĺ���
	// ���������Ҫ�ҵ�Zernike��ϲ�ǰ�������һ���ı任����ת�ã���ת�Ȳ���

	// Ϊ�����㲻ͬ�ֱ���Ҫ��wavefront�ĳߴ�ΪMAX_SPOTS_Y x MAX_SPOTS_X
	// Ϊ�˼��������Ҫ������29 x 29�����Զ�����Wavefront_Copy����
	for (int i = 0; i < 29; ++i)
	{
		for (int j = 0; j < 29; ++j)
		{
			Wavefront_Copy[i][j] = wavefront[i][j];
		}
	}



	// �������
	for (int i = 0; i < 29; ++i)
		for (int j = 0; j < 29; ++j)
		{
			zerPolyError29[i][j] = Wavefront_Copy[i][j] - zerWave_Matrix29[i][j];
		}

	WFS_WriteWavefrontZernikeError();

	// ��Zernike���������д���ļ�
}

// ��ǰ�ؽ�ģʽ��  д���ı��¼�
void CAOSys_v8Dlg::OnClickedButtonRecWrite()
{
	// �� ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��¼� ��ȫ�ֱ���zernikeMatrix_recon�����ֵд���ĵ�
	write_2d_File("D:\\externLib\\AOS\\Output\\Recon_zernikeMatrix2D.txt", zernikeMatrix_recon);


	GetDlgItem(IDC_EDIT_STA_WRITE)->SetWindowText(_T("д��ɹ�"));
}  // ��ǰ�ؽ�ģʽ��  д���ı��¼�



//--------------------------  ��ǰУ���¼�  --------------------------//
// �˽׶���Ҫ����12x12����

// ��ʼ�ջ�У����ǰ
void CAOSys_v8Dlg::OnClickedButtonConCloseloop()
{

	// �����PID�㷨����ô�ͼ������
	if (chooseAlgoIndex == 0)
	{

#pragma region ��������


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



#pragma endregion ��������

	}


	// �̵߳Ĳ�������
	int       nPriority = THREAD_PRIORITY_HIGHEST;//Ĭ��ΪTHREAD_PRIORITY_NORMAL
	UINT       nStackSize = 0;//�봴�������̶߳�ջ��С��ͬ
	DWORD       dwCreateFlags = CREATE_SUSPENDED;//CREATE_SUSPENDED ����������߳�

	// �������߳�
	pThread_LOOP = new CWinThread();
	pThread_LOOP->m_bAutoDelete = FALSE;
	pThread_LOOP = AfxBeginThread(ThreadFunc_WFS_Measurement_CONLOOP, this,
		nPriority, nStackSize, dwCreateFlags);  // ʹ��thisָ�뽫CAOSys_v7Dlg�ഫ���̺߳���
	pThread_LOOP->ResumeThread();


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
	// ��DM_CenterUp.txt�ļ����뵽�ڴ�
	if ((fp = fopen("D:\\externLib\\AOS\\conDM\\DM_CenterUp.txt", "rt")) == NULL)
	{
		::MessageBox(NULL, _T("���ܴ��ļ���"), _T("Status"), MB_OK);
	}
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
			fscanf(fp, "%f", &zerWave_Matrix[i][j]);
		fscanf(fp, "\n");
	}
	fclose(fp);

	// �Ѿ���У��һ��
	DM_WriteCheckZernikeMatrix();

#pragma region mapping   //��һ���ֵĴ���Ҫ�޸ģ�ϵͳȷ���ˣ������ϵҲ��ȷ����
	Mapping = 0;
	if (Mapping == 0)
	{
		// ���ҷ�ת
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[i][11 - j] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("���ҷ�ת"));
	}
	else if (Mapping == 1)
	{
		// ���·�ת
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[11 - i][j] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("���·�ת"));
	}
	else if (Mapping == 2)
	{
		// ת��
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[j][i] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("ת��"));
	}
	else if (Mapping == 3)
	{
		// ˳ʱ��ת��90��
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[j][11 - i] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("˳ʱ��ת��90��"));
	}
	else if (Mapping == 4)
	{
		// ˳ʱ��ת��180��
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[11 - i][11 - j] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("˳ʱ��ת��180��"));
	}
	else if (Mapping == 5)
	{
		// ˳ʱ��ת��270��, ����������������
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				zerWave_Matrix_Temp[11 - j][i] = zerWave_Matrix[i][j];
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("˳ʱ��ת��270��"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_STA_MAPTYPE)->SetWindowText(_T("�Ƿ�ӳ��"));
	}
#pragma endregion mapping

	// ��ת�ú�ľ���д���ļ�
	DM_WriteTransposeMatrix();


	// ����ά����zerWave_Matrix�������ֲ��е�DM Actuator Mapת��Ϊһά�����ݣ�����Ϊ140
	// �õ�����д��DM��Stroke����DM_Stroke_1D
	// �����Ϣ��
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
		DM_Stroke_1D[131 + j - 1] = zerWave_Matrix_Temp[11][j];  // ����������ǿ���ֱ��д��DM��һά�������г̵Ŀ�����
	}

	P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
	aoSystemData->dDMDesired = DM_Stroke_1D;
	int status = P_DM_SetSpatialFrame();

	DM_Write1DMatrix();
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
		// ���ݵ����õ�tabRect����m_ReconWavefontDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
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
		// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ��ʾ   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ���� 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 2:
		// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ��ʾ 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 3:
		// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_DeformMirrorDlg�ӶԻ��򣬲�����Ϊ��ʾ 
		ptr_DeformMirrorDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ͬ��
		ptr_DeviationXDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		// ͬ��
		ptr_MiscSettingDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;

	case 4:
		// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_SubApertureImageDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����   
		ptr_ReconWavefrontDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
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

	// ��������
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

	// �������³�ʼ��PID����
	if (pid_p != 0 || pid_i != 0 || pid_d != 0)
	{
		pid_p = 0;
		pid_i = 0;
		pid_d = 0;
	}

	for (int i = 0; i < 140; ++i)  // �����������
	{
		zernikeMatrix_recon_array[i] = 0;
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


	for (int i = 0; i < 140; ++i)  // �����������
	{
		zernikeMatrix_recon_array[i] = 1200;
	}


	// �ӶԻ��������
	(ptr_MiscSettingDlg->GetDlgItem(IDC_EDIT_SUBDLG_TIMERSETTING))->GetWindowTextW(ptr_MiscSettingDlg->m_Edit_TimeSetter); // x��������ƫ��
	timerSetterInterval = _ttoi(ptr_MiscSettingDlg->m_Edit_TimeSetter);


	GetDlgItem(IDC_EDIT_SETANGLE)->GetWindowText(m_Edit_SetAngle);
	angleRotate = _wtoi(m_Edit_SetAngle);


	// ��Ԥ������������룬��Matlab��������




}




void CAOSys_v8Dlg::OnSelchangeComboChoosealgo()
{
	// TODO: Add your control notification handler code here

	chooseAlgoIndex = m_Combo_ChooseAlgo.GetCurSel();
}


// ֱ��б�ʷ���Ԥ�����¼�
void CAOSys_v8Dlg::OnBnClickedButtonPreCalc()
{
	// ��140��DM��������Ԫ���η������ξ���WFS�����Ӧ�Ĳ�ǰ
	double DM_PreCalc[140];  // ������double������aoSystemData->dDMDesired = DM_PreCalc;����ǿת
	float  deviation_x_PreCalc[40][50];  // x�����Ѱ�������λ����
	float  deviation_y_PreCalc[40][50];  // y�����Ѱ�������λ����
	std::vector<std::vector<double>> deviation_x_nm_PreCalc;  // x����б�����ݣ���λnm
	std::vector<std::vector<double>> deviation_y_nm_PreCalc;   // y����б�����ݣ���λnm

	// ��ʼ������
	init_2dVector(deviation_x_nm_PreCalc, 29, 29);
	init_2dVector(deviation_y_nm_PreCalc, 29, 29);


	// ���ڱ����ļ���std::string
	// ��������CString�������ñ�׼���е�std::string
	std::string fileFullPath, filenamePrefix, finenameSuffix;
	std::string indexCString, XdeviCString, YdeviCString;
	std::string statusCString;

	XdeviCString = "XDevi";
	YdeviCString = "YDevi";
	filenamePrefix = "D:\\externLib\\AOS\\Output\\PreCalc\\in\\";
	finenameSuffix = ".txt";

	// ������״̬����ʾ
	CString indexCString_forreal;

	// WFS���ش�С4.65um�����ڽ���λ��pixelת��Ϊnm
	float  unitCoeff = 1; 

	for (int index = 0; index < 140; ++index)
	{
		// ���θ��ı��ξ�
		for (int i = 0; i < 140; ++i)
		{
			DM_PreCalc[i] = bias_initial;
		}
		DM_PreCalc[index] = bias_initial + impulse_stroke;

		// ����DM
		P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
		aoSystemData->dDMDesired = DM_PreCalc;
		int status = P_DM_SetSpatialFrame();


		//WFS̽�⵽�Ĳ�ǰ�ֱ𱣴����ļ�
		// ��ͨģʽ�£���ȡ�ӿ׾����е�ͼƬ
		WFS_TakeSpotfieldImage(instr.handle);
		// ����ͼƬ��������λ��
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
		// �����Ѱ���
		WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
		// ����Ѱ�������λ������
		WFS_GetSpotDeviations(instr.handle, *deviation_x_PreCalc, *deviation_y_PreCalc);

		// ������������
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{
				deviation_x_nm_PreCalc[row][col] = deviation_x_PreCalc[row][col] * unitCoeff;
				deviation_y_nm_PreCalc[row][col] = deviation_y_PreCalc[row][col] * unitCoeff;
			}
		} 

		// int����ת��Ϊstd::string����
		IntToString(indexCString, index);
		


#pragma region �ȴ�ʱ��

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
		} while (nTime_dmwait < 300);


#pragma endregion �ȴ�ʱ��




		// ��x�Ѱ���д���ļ�
		fileFullPath = filenamePrefix + XdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_x_nm_PreCalc);
		// ��y�Ѱ���д���ļ�
		fileFullPath = filenamePrefix + YdeviCString + "_" + indexCString + finenameSuffix;
		write_2d_File(fileFullPath, deviation_y_nm_PreCalc);


		indexCString_forreal.Format(_T("%d"), index);
		str_showerror = _T("Ԥ�������ݣ�  ") + indexCString_forreal;
		SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

	}


	str_showerror = _T("Ԥ�������");
	SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

	// ��������Ҫ�ͷ�
	release_2dVector(deviation_x_nm_PreCalc, 29);
	release_2dVector(deviation_y_nm_PreCalc, 29);

}


// ��Matlab��Ԥ�����������룬���ڴ��Ѱ���ֱ�ӻ�ñ��ξ���ִ����
void CAOSys_v8Dlg::OnBnClickedButtonPreCalcLoad()
{

	// ��Matlab����õ�lsqA��eff_picked����
	// ���磬��Ч�ӿ׾������Ϊ609,��ô��lsqA��ά����Ӧ����140*1218
	lsqA = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\lsqA.txt");
	// ����eff_pickedҪ��Ϊ��������Ҫ����ת��Ϊconst int����
	// ���磬��Ч�ӿ׾������Ϊ609��eff_picked��ʱ��ʼ��Ϊ841*2�ľ��󣬵�610��Ϊ[0,0]��611�𵽺��涼��δ�����ֵ������֮ǰ����Ч�ӿ׾���λ����Ϣ
	eff_picked = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\eff_picked.txt");
	// ע��eff_picked.size()��ʾ������eff_picked[0].size()��ʾ����
	// ����eff_picked��609���ӿ׾���������ţ���ô����609x2��һ��������ôeff_picked.size()=609��eff_picked[0].size()=2

	//// eff_picked�������ž������£�
	//// MyMat_double���͵�����������
	//lsqA[eff_picked[2][0]][eff_picked[2][1]];
	//// vector<vector<double>>���͵�������������������һ����
	//zernikeMatrix_15[eff_picked[2][0]][eff_picked[2][1]];
	//// float(POD)�������ݾ�Ҫǿת�ˣ�
	//wavefront[(int)eff_picked[2][0]][(int)eff_picked[2][1]];

}


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
	char           strg[WFS_BUFFER_SIZE];

	//char*����ת��Ϊ���ֽ����
	WCHAR W_instr_name[512];
	WCHAR W_serNr[512];
	WCHAR W_resourceName[512];

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

#pragma region �߳��еľֲ�����

	// ����ָ��Ի����ָ��
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	// ���ͼ�йصı���
	uchar image2DBuf[480][480];  // ��ά��ʽ


	// ��������,checkbox��������
	CButton* modeSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_MODESWITCH));
	CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
	CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));


#pragma endregion �߳��еľֲ�����



#pragma region �ջ�ǰ�Ĳ�������


	if (modeSwitch->GetCheck() == 1)
	{
		//## ����WFSΪ����ģʽ���������ֻ��Ҫ����һ�Σ������ѡ����ģʽ����ô�͵���һ���������
		WFS_SetHighspeedMode(instr.handle, OPTION_HIGHSPEED, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);
	}
	else
	{
		// �رո���ģʽ
		WFS_SetHighspeedMode(instr.handle, 0, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);

	}

#pragma endregion �ջ�ǰ�Ĳ�������



#pragma region ��������λ��

	// ��һ������������λ��
	// �����ж�������ͨģʽ�������λ�û����ø���ģʽ�������λ��
	// ����ģʽ�ٶȿ죬����û��ͼ����ʾ
	// ��ͨģʽ�ٶ�����������ͼ����ʾ
	if (modeSwitch->GetCheck() == 1)   // ����ģʽDSP�������ģ�USB cable������ͼ��
	{
		// ����ģʽ��ȡ����λ��
		WFS_GetStatus(instr.handle, &instr.status);
		std::bitset<32> judge = instr.status & (WFS_STATBIT_HSP | WFS_STATBIT_SPC | WFS_STATBIT_PUD | WFS_STATBIT_CFG);
		if (judge == 0x2700)
		{
		}
		else
		{
			::MessageBox(NULL, _T("���Ǹ���ģʽ��"), _T("Status"), MB_OK);
		}

		// ��鵱ǰ�Ƿ�Ϊ����ģʽ���������ò���޷���⵽���ǲ��Ǹ���ģʽ
		err = WFS_CheckHighspeedCentroids(instr.handle);
		if (err == 0)
		{
		}
		else
		{
			WFS_HandleErrors(err);
		}


		// ��������ĺ��������ܱ�֤ÿ��DSP�����꣬ÿ��ѭ����ʱ�򶼻Ὣ������ˢ�����ڴ��У�����������ͼ����ʾ
		WFS_TakeSpotfieldImage(instr.handle);

	}



	else   // ��ͨģʽͨ��ͼ����ķ����������λ�ã�USB cable����ͼ��
	{
		// ��ͨģʽ��ȡ����λ��
		WFS_TakeSpotfieldImage(instr.handle);
		// ��������λ��
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);



#pragma region ��ʾ�ӿ׾�ͼ��

		if (subApertureImageSwitch->GetCheck() == 1)
		{

			// ��ͼ��ˢ���ڴ�
			WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
			// ��ͼ����һάתΪ��ά�������ת��������֤����ȷ��
			for (int row = 0; row < 480; ++row)
				for (int col = 0; col < 480; ++col)
				{
					image2DBuf[row][col] = imageBuf[480 * row + col];
				}
			//----------------------------------------------------------//
			//## ���ͨ��
			(pW->m_Edit_Sta_Watch).Format(_T("%u"), sizeof(image2DBuf));
			pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);
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
		else
		{
			if (CMOSImageFlag == TRUE)
			{
				pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
			}
			CMOSImageFlag = FALSE;  // ���ñ�־
		}


#pragma endregion ��ʾ�ӿ׾�ͼ��



	}

#pragma endregion ��������λ��



#pragma region �����Ѱ���

	// �ڶ����������Ѱ���
	// �����Ѱ���
	WFS_CalcSpotToReferenceDeviations(instr.handle, 1);
	// ��ȡ����λ��
	//WFS_GetSpotCentroids(instr.handle, *centroid_x, *centroid_y);
	// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
	WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);

	CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));
	if (deviationSwitch->GetCheck() == 1) // ��ʾ�Ѱ���
	{
		pW->ptr_DeviationXDlg->ShowDeviationX();
	}

#pragma endregion �����Ѱ���



#pragma region ��ò�ǰͳ����Ϣ

	//�����Ѱ����ؽ���ǰ
	WFS_CalcWavefront(instr.handle, instr_setup.wavefront_type, instr_setup.pupil_circular, *wavefront);
	WFS_WriteCalcWavefront();  //  �����ǰ��WFS_CalcWavefront.txt


	// ��ò�ǰͳ����Ϣ 
	//wavefront_diff=wavefront_max-wavefront_min��������ǹ�ͫ�ڵ�PVֵ
	err = WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
		&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);
	if (err == 0)
	{
		// ��ʾPVֵ
		(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
		pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);

		// ��ʾRMSֵ
		(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
		pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);

	}
	else
	{
		WFS_HandleErrors(err);
	}

#pragma endregion ��ò�ǰͳ����Ϣ

	// �̺߳�����Ҫһ������ֵ
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//## ע�⣬�ڲ�ǰ�ؽ�ģʽ�£�����ǰ�ؽ�����ť�롰����DM����ťҪ�ɶ�ʹ�ã���Ϊ�ڡ���ǰ�ؽ�����ť��zernikeMatrix_reconҪpush_back
//## �����У�Ҫ��Ӧ�İ�zernikeMatrix_recon��zernikeMatrix_recon_1d��������pop_back�ſ��ԣ��������ݶѻ�������޷���ȷ����DM
// ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��߳�
UINT ThreadFunc_WFS_Measurement_REC(LPVOID pParam)
{
	// ����̺߳��������ã�̽�Ⲩǰ����ʹ����С���˷�������ǰ�ؽ���Ȼ�������Ҫѡ���Ƿ���б���


#pragma region �߳��еľֲ�����

	// ����ָ��Ի����ָ��
	CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

	// ���ͼ�йصı���
	uchar image2DBuf[480][480];  // ��ά��ʽ


	// ��������,checkbox��������
	CButton* modeSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_MODESWITCH));
	CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
	CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));

#pragma endregion �߳��еľֲ�����



#pragma region �ջ�ǰ�Ĳ�������


	if (modeSwitch->GetCheck() == 1)
	{
		//## ����WFSΪ����ģʽ���������ֻ��Ҫ����һ�Σ������ѡ����ģʽ����ô�͵���һ���������
		WFS_SetHighspeedMode(instr.handle, OPTION_HIGHSPEED, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);
	}
	else
	{
		// �رո���ģʽ
		WFS_SetHighspeedMode(instr.handle, 0, OPTION_HS_ADAPT_CENTR, NoiseCutAct, OPTION_ALLOW_AUTOEXPOS);

	}

#pragma endregion �ջ�ǰ�Ĳ�������



#pragma region ��������λ��

	// ��һ������������λ��
	// �����ж�������ͨģʽ�������λ�û����ø���ģʽ�������λ��
	// ����ģʽ�ٶȿ죬����û��ͼ����ʾ
	// ��ͨģʽ�ٶ�����������ͼ����ʾ
	if (modeSwitch->GetCheck() == 1)   // ����ģʽDSP�������ģ�USB cable������ͼ��
	{
		// ����ģʽ��ȡ����λ��

		// ����Ƿ�Ϊ����ģʽ������λ�����ж�����״̬
		// ��������£�����instr.status���ص���0x2700,˵���ǣ�
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
			::MessageBox(NULL, _T("���Ǹ���ģʽ��"), _T("Status"), MB_OK);
		}
		// ����0x1792
		//0x00000002  WFS_STATBIT_PTH  Power Too High(cam saturated)
		//0x00000010  WFS_STATBIT_SCL  Spot Contrast too Low
		//0x00000080  WFS_STATBIT_ATR  Camera is still Awaiting a TRigger
		//0x00000100  WFS_STATBIT_CFG  Camera is ConFiGured
		//0x00000200  WFS_STATBIT_PUD  PUpil is Defined
		//0x00000400  WFS_STATBIT_SPC  No.of Spots or Pupil Changed
		//0x00001000  WFS_STATBIT_URF  No User ReFerence available



		// ��鵱ǰ�Ƿ�Ϊ����ģʽ���������ò���޷���⵽���ǲ��Ǹ���ģʽ
		err = WFS_CheckHighspeedCentroids(instr.handle);
		if (err == 0)
		{
		}
		else
		{
			WFS_HandleErrors(err);
		}


		// ��������ĺ��������ܱ�֤ÿ��DSP�����꣬ÿ��ѭ����ʱ�򶼻Ὣ������ˢ�����ڴ��У�����������ͼ����ʾ
		WFS_TakeSpotfieldImage(instr.handle);

	}



	else   // ��ͨģʽͨ��ͼ����ķ����������λ�ã�USB cable����ͼ��
	{
		// ��ͨģʽ��ȡ����λ��
		WFS_TakeSpotfieldImage(instr.handle);
		// ��������λ��
		WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);



#pragma region ��ʾ�ӿ׾�ͼ��

		if (subApertureImageSwitch->GetCheck() == 1)
		{

			// ��ͼ��ˢ���ڴ�
			WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
			// ��ͼ����һάתΪ��ά�������ת��������֤����ȷ��
			for (int row = 0; row < 480; ++row)
				for (int col = 0; col < 480; ++col)
				{
					image2DBuf[row][col] = imageBuf[480 * row + col];
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
		else
		{
			if (CMOSImageFlag == TRUE)
			{
				pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
			}
			CMOSImageFlag = FALSE;  // ���ñ�־
		}


#pragma endregion ��ʾ�ӿ׾�ͼ��



	}

#pragma endregion ��������λ��



#pragma region �����Ѱ���

	// �ڶ����������Ѱ���
	// �����Ѱ���
	WFS_CalcSpotToReferenceDeviations(instr.handle, 0);
	// ��ȡ����λ��
	//WFS_GetSpotCentroids(instr.handle, *centroid_x, *centroid_y);
	// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
	WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);

	CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));
	if (deviationSwitch->GetCheck() == 1) // ��ʾ�Ѱ���
	{
		pW->ptr_DeviationXDlg->ShowDeviationX();
	}

#pragma endregion �����Ѱ���



#pragma region ���ú�����zernikeϵ��

	zernike_order = 4; // 0 �� zernike order auto
	WFS_ZernikeLsf(instr.handle, (ViInt32*)&zernike_order, zernike_um, zernike_orders_rms_um, &roc_mm);

#pragma endregion ���ú�����zernikeϵ��



#pragma region ��ò�ǰͳ����Ϣ

	//�����Ѱ����ؽ���ǰ
	err = WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);
	WFS_WriteCalcWavefront();  //  �����ǰ��WFS_CalcWavefront.txt


	// ��ò�ǰͳ����Ϣ 
	//wavefront_diff=wavefront_max-wavefront_min��������ǹ�ͫ�ڵ�PVֵ
	err = WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
		&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);
	if (err == 0)
	{
		// ��ʾPVֵ
		(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
		pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);

		// ��ʾRMSֵ
		(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
		pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);

	}
	else
	{
		WFS_HandleErrors(err);
	}

#pragma endregion ��ò�ǰͳ����Ϣ



#pragma region �ؽ���ǰ����

	//------ �ؽ���ǰ
	// ��Ӧfloat	zernike_um[MAX_ZERNIKE_MODES + 1]������������vector_zernike_um�Ǿֲ�����
	std::vector<double> vector_zernike_um;  // 15��zernikeϵ��
	for (int i = 1; i <= 15; ++i)		// һά����ת��Ϊһάvector
		vector_zernike_um.push_back(zernike_um[i]);

	// ��ʼ����ά�ؽ���ǰ���ݾ���
	init_2dVector(zernikeMatrix_recon, 12, 12);


	// ����������˺;�����ӵ����㣬�õ��ؽ���zernike��ϵĲ�ǰ
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

#pragma endregion �ؽ���ǰ����




	return 0;
}  // ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��߳�




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ǰ���Ƶ��̺߳���
UINT ThreadFunc_WFS_Measurement_CONLOOP(LPVOID pParam)
{


#pragma region PID�㷨

	// PID�㷨
	if (chooseAlgoIndex == 0)
	{


#pragma region �߳��еľֲ�����

		// ����ָ��Ի����ָ��
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;


		// ���ڼ���֡�ʵ�ʱ�����
		double t_interval_2nd = 0; // ѭ������ʱ��
		LARGE_INTEGER nStartCounter_2nd;  // ��ʼ�������
		LARGE_INTEGER nFrequency_2nd;   // ÿ�����
		LARGE_INTEGER nStopCounter_2nd;  // ��ֹ�������


		double frameRate = 0;  // ֡��
		int looptime = 0;


		// ���ͼ�йصı���
		uchar image2DBuf[480][480];  // ��ά��ʽ


		// ��������,checkbox��������
		CButton* modeSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_MODESWITCH));
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
		CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));
		CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));



		for (int index = 0; index < 140; ++index)
		{
			DM_PID_P[index] = 1200;
		}



		// ��ʼ�������������飬���������WFS��DM���������
		// DM���������꣬���ξ���pitchΪ400um=0.4mm��һ��12����Ԫ
		double xArray_Mode[12];
		double yArray_Mode[12];
		for (int i = 0; i < 12; ++i)
			xArray_Mode[i] = -2.4 + i * 0.4;
		for (int i = 0; i < 12; ++i)
			yArray_Mode[i] = -2.4 + i * 0.4;


		int NAN_counter = 0; // ����NAN���ݵĸ���


#pragma endregion �߳��еľֲ�����



#pragma region �ջ�ǰ�Ĳ�������



		// ����ģʽ����ͨģʽ��Ԥ��
		if (modeSwitch->GetCheck() == 1)
		{
			//## ����WFSΪ����ģʽ���������ֻ��Ҫ����һ�Σ������ѡ����ģʽ����ô�͵���һ���������
			WFS_SetHighspeedMode(instr.handle, 1, 0, NoiseCutAct, 0);
		}
		else
		{
			// �رո���ģʽ
			WFS_SetHighspeedMode(instr.handle, 0, 0, NoiseCutAct, 0);

		}

#pragma endregion �ջ�ǰ�Ĳ�������



		// �ջ�
		CloseLoopFlag = TRUE;
		int count_devi = 0;  // ��¼ÿ��ʱ�̵��Ѱ���
		while (CloseLoopFlag)
		{

#pragma region ��ʱ����ʼ
			//�¼�ʱ����ʼ
			LARGE_INTEGER nStartCounter_test;
			LARGE_INTEGER nFrequency_test;
			double nTime_test = 0; // ��¼ʱ��

			::QueryPerformanceCounter(&nStartCounter_test);
			::QueryPerformanceFrequency(&nFrequency_test);
#pragma endregion ��ʱ����ʼ



#pragma region ֡����ʾ
			// ֡��---��ʼ����
			::QueryPerformanceCounter(&nStartCounter_2nd);
			::QueryPerformanceFrequency(&nFrequency_2nd);

#pragma endregion ֡����ʾ



#pragma region ��������λ��

			// ��һ������������λ��
			// �����ж�������ͨģʽ�������λ�û����ø���ģʽ�������λ��
			// ����ģʽ�ٶȿ죬����û��ͼ����ʾ
			// ��ͨģʽ�ٶ�����������ͼ����ʾ
			if (modeSwitch->GetCheck() == 1)   // ����ģʽDSP�������ģ�USB cable������ͼ��
			{
				// ����ģʽ��ȡ����λ��

				// ����Ƿ�Ϊ����ģʽ������λ�����ж�����״̬
				// ��������£�����instr.status���ص���0x2700,˵���ǣ�
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
					::MessageBox(NULL, _T("���Ǹ���ģʽ��"), _T("Status"), MB_OK);
					break;
				}
				// ����0x1792
				//0x00000002  WFS_STATBIT_PTH  Power Too High(cam saturated)
				//0x00000010  WFS_STATBIT_SCL  Spot Contrast too Low
				//0x00000080  WFS_STATBIT_ATR  Camera is still Awaiting a TRigger
				//0x00000100  WFS_STATBIT_CFG  Camera is ConFiGured
				//0x00000200  WFS_STATBIT_PUD  PUpil is Defined
				//0x00000400  WFS_STATBIT_SPC  No.of Spots or Pupil Changed
				//0x00001000  WFS_STATBIT_URF  No User ReFerence available



				// ��鵱ǰ�Ƿ�Ϊ����ģʽ���������ò���޷���⵽���ǲ��Ǹ���ģʽ
				err = WFS_CheckHighspeedCentroids(instr.handle);
				if (err == 0)
				{
				}
				else
				{
					WFS_HandleErrors(err);
				}


				// ��������ĺ��������ܱ�֤ÿ��DSP�����꣬ÿ��ѭ����ʱ�򶼻Ὣ������ˢ�����ڴ��У�����������ͼ����ʾ
				WFS_TakeSpotfieldImage(instr.handle);

			}



			else   // ��ͨģʽͨ��ͼ����ķ����������λ�ã�USB cable����ͼ��
			{
				// ��ͨģʽ��ȡ����λ��
				WFS_TakeSpotfieldImage(instr.handle);
				// ��������λ��
				WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);



#pragma region ��ʾ�ӿ׾�ͼ��

				if (subApertureImageSwitch->GetCheck() == 1)
				{

					// ��ͼ��ˢ���ڴ�
					WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
					// ��ͼ����һάתΪ��ά�������ת��������֤����ȷ��
					for (int row = 0; row < 480; ++row)
						for (int col = 0; col < 480; ++col)
						{
							image2DBuf[row][col] = imageBuf[480 * row + col];
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
				else
				{
					if (CMOSImageFlag == TRUE)
					{
						pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
					}
					CMOSImageFlag = FALSE;  // ���ñ�־
				}


#pragma endregion ��ʾ�ӿ׾�ͼ��



			}

#pragma endregion ��������λ��



#pragma region �����Ѱ���

			// �ڶ����������Ѱ���
			// �����Ѱ���
			WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
			// ��ȡ����λ��
			WFS_GetSpotCentroids(instr.handle, *centroid_x, *centroid_y);
			// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
			WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);
			//## ���ͨ��
			//(pW->m_Edit_Sta_Watch).Format(_T("%lf"), deviation_x[14][14]);
			//pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);



#pragma region ���ӵ���Ч���ݴ���취

			for (int row = 1; row < 28; ++row)  // �ճ�����������
			{
				for (int col = 1; col < 28; ++col) // �ճ�����������
				{

					// �ж�x����
					if (_isnan(deviation_x[row][col]))
					{
						++NAN_counter;
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
							str_showerror = "������PID�㷨  X�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

							str_showerror = "������PID�㷨  X�����Ѱ���  ��Ч�����ѱ���ֵ";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

						}


					}  // x�������



					// �ж�y����
					if (_isnan(deviation_y[row][col]))
					{
						++NAN_counter;

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
							str_showerror = "������PID�㷨  Y�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

							str_showerror = "������PID�㷨  Y�����Ѱ���  ��Ч�����ѱ���ֵ";
							pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

						}  // ��������Чֵ��ֵ����

					} // y�������

				}
			}  // ��Чֵ��������

#pragma endregion ���ӵ���Ч���ݴ���취


			//
			//#pragma region �򵥴�����Ч���ݵķ���
			//
			//			NAN_counter = 0;
			//			for (int row = 0; row < 29; ++row)
			//			{
			//				for (int col = 0; col < 29; ++col)
			//				{
			//					if (_isnan(deviation_x[row][col]))
			//					{
			//						++NAN_counter; // ��������һ
			//						FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
			//						str_showerror = "������PID�㷨  X�Ѱ���  �г���NAN���ݣ�";
			//						pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
			//
			//						deviation_x[row][col] = 0;
			//
			//					}
			//					if (_isnan(deviation_y[row][col]))
			//					{
			//						++NAN_counter; // ��������һ
			//						FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
			//						str_showerror = "������PID�㷨  Y�Ѱ���  �г���NAN���ݣ�";
			//						pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
			//
			//
			//						deviation_y[row][col] = 0;
			//					}
			//				}
			//			}  // ��Чֵ��������
			//
			//#pragma endregion �򵥴�����Ч���ݵķ���
			//


			// ��ʾ��Ч��ĸ���
			(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
			pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);




			if (deviationSwitch->GetCheck() == 1) // ��ʾ�Ѱ�������λ��pixel
			{
				pW->ptr_DeviationXDlg->ShowDeviationX();
			}

			// ��¼ÿ��ѭ�����Ѱ���
			if (pW->ptr_MiscSettingDlg->m_Check_SubDlg_RemeberDevi.GetCheck() == 1)
			{
				// ��ʾһ����̬��ʡ�Ժ�
				if (0 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("���ݼ�¼��"));
				}
				if (1 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("���ݼ�¼��."));
				}
				if (2 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("���ݼ�¼��.."));
				}
				if (3 == count_devi % 4)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("���ݼ�¼��..."));
				}


				// ���Ѱ�����¼����ά������
				for (int row = 0; row < 29; ++row)
					for (int col = 0; col < 29; ++col)
					{
						rememberDeviationX[row][col][count_devi] = deviation_x[row][col];
						rememberDeviationY[row][col][count_devi] = deviation_y[row][col];
					}


				++count_devi; // ������Ҫ�Լ�


				if (100 == count_devi)
				{
					(pW->ptr_MiscSettingDlg->GetDlgItem(IDC_STATIC_REMEMBER_STATE))->
						SetWindowText(_T("�������������жϵ�����棡"));
					pW->ptr_MiscSettingDlg->m_Check_SubDlg_RemeberDevi.SetCheck(BST_UNCHECKED); // ȡ��check�������´�ѭ���Ͳ�����if���
				}

			}



#pragma endregion �����Ѱ���



#pragma region ���ú�����zernikeϵ��

			// ���zernikeϵ��
			zernike_order = 4; // 0 �� zernike order auto
			WFS_ZernikeLsf(instr.handle, (ViInt32*)&zernike_order, zernike_um, zernike_orders_rms_um, &roc_mm);


			// ��ʾzernikeϵ��
			CString showZernike;
			for (int index = 0; index < 15; ++index)
			{
				showZernike.Format(_T("%lf"), zernike_um[index + 1]);
				pW->SetDlgItemText(IDC_STATIC_SHOW_ZER1 + index, showZernike);

			}


			//// ��¼zernikeϵ��
			//std::vector<double> zernike_um_save(15);
			//for (int index = 0; index < 15;++index)
			//{
			//	zernike_um_save[index] = (double)zernike_um[index + 1];
			//}
			//write_1d_File("D:\\WorkSpace\\Matlab\\N1_Temp\\zernike_um_save.txt", zernike_um_save);

			//// ��zernike_um�����¸�ֵ
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


#pragma endregion ���ú�����zernikeϵ��



#pragma region �ؽ���ǰ����


			// ��ʼ����ά�ؽ���ǰ���ݾ���
			init_2dVector(zernikeMatrix_recon, 12, 12);


			// ����������˺;�����ӵ����㣬�õ��ؽ���zernike��ϵĲ�ǰ
			for (int row = 0; row < 12; ++row)
				for (int col = 0; col < 12; ++col)
				{
					zernikeMatrix_recon[row][col] =   // zernikeMatrix_recon�ڱ���������һ��ȫ�����飬��������Ѿ�ʹ��extern����
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
				}  // ����Ϊֹ��vector_zernike_um�������ˣ���ˣ�һ��Ҫ�����ſ���

			write_2d_File("D:\\WorkSpace\\Matlab\\N1_Temp\\zernikeMatrix_recon.txt", zernikeMatrix_recon);


			// ��ά����תһά���飬Ϊ��������м���PV��RMS
			int temp_counter = 0;
			for (int row = 0; row < 12; ++row)
			{
				for (int col = 0; col < 12; ++col)
				{
					// ��ȡ��ͫ�ڵ�����
					if (sqrt(pow(xArray_Mode[row], 2) + pow(yArray_Mode[col], 2)) <= (instr_setup.pupil_dia_x_mm) / 2)
					{
						zernikeMatrix_recon_ParaCal[temp_counter] = zernikeMatrix_recon[row][col];
						++temp_counter;
					}

				}
			}



#pragma endregion �ؽ���ǰ����



#pragma region ��ǰͳ�Ʋ���

			// sort�����°�����С�����˳�����¸���zernikeMatrix_recon_ParaCal
			sort(zernikeMatrix_recon_ParaCal.begin(), zernikeMatrix_recon_ParaCal.end());
			int index_end = zernikeMatrix_recon_ParaCal.size() - 1;

			// ���ֵ
			wavefront_mean = 0;
			for (int index = 0; index < index_end + 1; ++index)
			{
				wavefront_mean = wavefront_mean + zernikeMatrix_recon_ParaCal[index];
			}
			wavefront_mean = wavefront_mean / 144;


			// PVֵ
			wavefront_diff = zernikeMatrix_recon_ParaCal[index_end] - zernikeMatrix_recon_ParaCal[0];

			// RMSֵ
			wavefront_rms = 0;
			for (int index = 0; index < index_end + 1; ++index)
			{
				wavefront_rms = wavefront_rms + pow(zernikeMatrix_recon_ParaCal[index], 2);
			}
			wavefront_rms = sqrt(wavefront_rms / (index_end - 1));


			// ��ʾPVֵ
			(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
			pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);
			// ��ʾRMSֵ
			(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
			pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);

#pragma endregion ��ǰͳ�Ʋ���



#pragma region �����ݷ��͸�DM

			// ������ת����
			// ��ʼ�����ڱ�����ת������ݶ�ά����
			init_2dVector(zernikeMatrix_recon_rotate, 12, 12);
			if (90 == angleRotate)  // ˳ʱ����ת90�ȣ����涼��˳ʱ��
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
			else if (1 == angleRotate)   // ���·�ת
			{
				MatrixFlipUpDown_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (2 == angleRotate) // ���ҷ�ת
			{
				MatrixFlipLeftRight_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else if (3 == angleRotate)  // ���·�ת�����ҷ�ת
			{
				MatrixFlipUpDown_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
				MatrixFlipLeftRight_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}
			else
			{
				// Ĭ��
				MatrixRotate0_vector(zernikeMatrix_recon_rotate, zernikeMatrix_recon);
			}



			// ��ʼ��һ��������ת��һάvector
			std::vector<double> zernikeMatrix_recon_1d(144);

			// ��ά����תΪһά����
			for (int i = 0; i < 12; ++i)
				for (int j = 0; j < 12; ++j)
					zernikeMatrix_recon_1d[i * 12 + j] = zernikeMatrix_recon_rotate[i][j];


			// Ҫɾ��4��Ԫ��
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin());
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 10);
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 130);
			zernikeMatrix_recon_1d.erase(zernikeMatrix_recon_1d.begin() + 140);

			//��140��Ԫ�ص�һάvectorתΪ����, ɾ��Ԫ��֮���һάvector����������ļ�
			double tempIncrease = 0;
			for (int i = 0; i < 140; ++i)
			{

				// P����
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
				// �������ξ�  
				zernikeMatrix_recon_array[i] = DM_PID_P[i];
				
				//zernikeMatrix_recon_array[i] = tempIncrease + 1200;


				 //���ξ�û��У׼ ���ڱȶ�zernikeϵ��
				//zernikeMatrix_recon_array[i] = 0;

			}


			// ���̷�Χ����
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



			// ѡ���Ƿ���ʾִ����(PID�㷨)
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






#pragma endregion �����ݷ��͸�DM



			if (pW->ptr_MiscSettingDlg->m_Check_SubDlg_TimeSetter.GetCheck() == 1)  // ѡ���Ƿ���м�ʱ
			{

				do
				{

#pragma region ��ʱ������

					LARGE_INTEGER nStopCounter_test;
					::QueryPerformanceCounter(&nStopCounter_test);
					nTime_test = 1000 * ((double)nStopCounter_test.QuadPart - (double)nStartCounter_test.QuadPart) / (double)nFrequency_test.QuadPart;    // ��λ ms

					//��ʾ��ʱ��
					pW->m_Edit_Sta_Time.Format(_T("%lf"), nTime_test);
					pW->SetDlgItemText(IDC_EDIT_STA_TIME, pW->m_Edit_Sta_Time);

#pragma endregion ��ʱ������


				} while (nTime_test < timerSetterInterval);


#pragma region ֡����ʾ

				//-----------------------------------------//
				// ֡��---��ֹ����
				::QueryPerformanceCounter(&nStopCounter_2nd);
				// ʱ��������λs
				t_interval_2nd = (double)(nStopCounter_2nd.QuadPart - nStartCounter_2nd.QuadPart) / (double)nFrequency_2nd.QuadPart;
				frameRate = (double)1 / t_interval_2nd;  // WFS��ˢ��Ƶ�ʣ�Ҳ�Ǳջ���Ƶ�ʣ���λHz
				pW->m_Edit_Sta_Frame.Format(_T("%lf"), frameRate);
				pW->SetDlgItemText(IDC_EDIT_STA_FRAME, pW->m_Edit_Sta_Frame);
				//-----------------------------------------//

#pragma endregion ֡����ʾ



			}
			else
			{

#pragma region ��ʱ������

				LARGE_INTEGER nStopCounter_test;
				::QueryPerformanceCounter(&nStopCounter_test);
				nTime_test = 1000 * ((double)nStopCounter_test.QuadPart - (double)nStartCounter_test.QuadPart) / (double)nFrequency_test.QuadPart;    // ��λ ms

				//��ʾ��ʱ��
				pW->m_Edit_Sta_Time.Format(_T("%lf"), nTime_test);
				pW->SetDlgItemText(IDC_EDIT_STA_TIME, pW->m_Edit_Sta_Time);

#pragma endregion ��ʱ������


#pragma region ֡����ʾ

				//-----------------------------------------//
				// ֡��---��ֹ����
				::QueryPerformanceCounter(&nStopCounter_2nd);
				// ʱ��������λs
				t_interval_2nd = (double)(nStopCounter_2nd.QuadPart - nStartCounter_2nd.QuadPart) / (double)nFrequency_2nd.QuadPart;
				frameRate = (double)1 / t_interval_2nd;  // WFS��ˢ��Ƶ�ʣ�Ҳ�Ǳջ���Ƶ�ʣ���λHz
				pW->m_Edit_Sta_Frame.Format(_T("%lf"), frameRate);
				pW->SetDlgItemText(IDC_EDIT_STA_FRAME, pW->m_Edit_Sta_Frame);
				//-----------------------------------------//

#pragma endregion ֡����ʾ


			}



			// �ͷ�δ��ת�Ķ�ά����
			release_2dVector(zernikeMatrix_recon, 12);
			// һ������zernikeMatrix_recon_rotate����������ȫ������
			release_2dVector(zernikeMatrix_recon_rotate, 12);


		}  // �ջ�while����

	}// if������PID�㷨����

#pragma endregion PID�㷨


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region �ݶ��㷨

	// ѡ���ݶ��㷨
	if (chooseAlgoIndex == 1)
	{


#pragma region �߳��еľֲ�����

		// ����ָ��Ի����ָ��
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

		// ���ͼ�йصı���
		uchar image2DBuf[480][480];  // ��ά��ʽ
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));  // ��ʾͼ��
		CButton* deviationSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_DEVIATIONSWITCH));  // ��ʾ�Ѱ���
		CButton* showExecuDist = (CButton*)(pW->GetDlgItem(IDC_CHECK_SHOW_EXECDIST));


		// ���ۺ���ֵ
		double meritFunctionValue = 100;			// ��ǰѭ�������ۺ���ֵ
		double meritFunctionValueAdd = 0;		// �����ξ�ʩ�ӡ���������󡱺�����ۺ���ֵ
		double meritFunctionValueMinus = 0;		// �����ξ�ʩ�ӡ���������󡱺�����ۺ���ֵ


		int NAN_counter = 0; // ����NAN���ݵĸ���

		// ���ڼ���֡�ʵ�ʱ�����
		double t_interval_2nd = 0; // ѭ������ʱ��
		LARGE_INTEGER nStartCounter_2nd;  // ��ʼ�������
		LARGE_INTEGER nFrequency_2nd;   // ÿ�����
		LARGE_INTEGER nStopCounter_2nd;  // ��ֹ�������
		double frameRate = 0;  // ֡��



		// ���Ѱ�����Ϊ���ۺ�����Ҫ�����ͫ
		// WFS���������꣬�ӿ׾���pitchΪ150um=0.15mm��480x480�ֱ�����Ϊ29x29���ӿ׾�
		float xArray_29[29];
		float yArray_29[29];
		for (int i = 0; i < 29; ++i)
			xArray_29[i] = -2.1 + i * 0.15;
		for (int i = 0; i < 29; ++i)
			yArray_29[i] = -2.1 + i * 0.15;
		// �����ͫ����
		float pupil_deviation[29][29];
		for (int row = 0; row < 29; ++row)
		{
			for (int col = 0; col < 29; ++col)
			{

				pupil_deviation[row][col] = (float)((sqrt(pow(xArray_29[row], 2) + pow(yArray_29[col], 2)) <= instr_setup.pupil_dia_x_mm / 2) ? 1 : 0);

			}
		}

		// ���ڴ洢��ͫ���Ƶ�deviation����
		float deviation_x_pupil[29][29];
		float deviation_y_pupil[29][29];




#pragma endregion �߳��еľֲ�����




		// ����ִ�����ĳ�ʼֵ
		for (int index = 0; index < 140; ++index)
		{
			zernikeMatrix_recon_array_DEFAULT[index] = 1200;
		}





		// �ջ�ѭ��
		CloseLoopFlag = TRUE;
		while (CloseLoopFlag)
		{

			// ��ʾ�������ۺ���ֵ
			CString showMerit;

			showMerit.Format(_T("%lf"), meritFunctionValueAdd);
			pW->SetDlgItemText(IDC_STATIC_SHOW1, showMerit);

			showMerit.Format(_T("%lf"), meritFunctionValueMinus);
			pW->SetDlgItemText(IDC_STATIC_SHOW2, showMerit);

			showMerit.Format(_T("%lf"), meritFunctionValue);
			pW->SetDlgItemText(IDC_STATIC_SHOW3, showMerit);



#pragma region ��ʱ����ʼ
			//�¼�ʱ����ʼ
			LARGE_INTEGER nStartCounter_test;
			LARGE_INTEGER nFrequency_test;
			double nTime_test = 0; // ��¼ʱ��

			::QueryPerformanceCounter(&nStartCounter_test);
			::QueryPerformanceFrequency(&nFrequency_test);
#pragma endregion ��ʱ����ʼ



#pragma region ֡����ʾ
			// ֡��---��ʼ����
			::QueryPerformanceCounter(&nStartCounter_2nd);
			::QueryPerformanceFrequency(&nFrequency_2nd);

#pragma endregion ֡����ʾ




			// ��ʼ��һ��������ת��һάvector��������ʽ�ĳ�ʼ�������ͷ�,ÿ��ѭ����Ҫ��ʼ��һ�Σ���Ϊÿ��ѭ����Ҫɾ��4��Ԫ��
			std::vector<double> zernikeMatrix_recon_1d_add(144);  //��Ϊ��ɾ���ĸ�Ԫ�أ�����Ҫ���Ӽ������ֱ�����һ��
			std::vector<double> zernikeMatrix_recon_1d_minus(144);  //��Ϊ��ɾ���ĸ�Ԫ�أ�����Ҫ���Ӽ������ֱ�����һ��
			std::vector<double> zernikeMatrix_recon_1d_default(144);  // Ĭ�ϲ���


			// �������     (double)rand() / 32768.0 - 0.5   ��Χ -0.5 0.5
			// ÿ��whileѭ���У�������󱣳ֲ���
			for (int index = 0; index < 140; ++index)
			{
				randomMatrix[index] = ((double)rand() / 32768.0 - 0.5) * 50;
			}


			// һ��whileѭ���������μ��㣬��һ��Ϊ�Ӳ������ڶ���Ϊ������
			// ͨ���������β�������ȡ���ۺ���ֵ��������һ�����о�
			for (int count = 0; count < 2; ++count)
			{

#pragma region �Ӳ���

				if (count == 0)  // ���������
				{


#pragma region �����͸����ξ�

					for (int index = 0; index < 140; ++index)
					{
						zernikeMatrix_recon_array_ADD[index] = zernikeMatrix_recon_array_DEFAULT[index] + randomMatrix[index];
					}

					//## ����Ҫ��һ��ת������vectorת��Ϊ����
					P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
					aoSystemData->dDMDesired = zernikeMatrix_recon_array_ADD;
					int status = P_DM_SetSpatialFrame();

#pragma endregion �����͸����ξ�


#pragma region ���ξ��ȴ�ʱ��

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
					} while (nTime_dmwait < 10);


#pragma endregion ���ξ��ȴ�ʱ��




#pragma region ��ǰ̽��
					// ��ͨģʽ��ȡ����λ��
					WFS_TakeSpotfieldImage(instr.handle);
					// ��������λ��
					WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);


#pragma region ��ʾ�ӿ׾�ͼ��

					if (subApertureImageSwitch->GetCheck() == 1)
					{

						// ��ͼ��ˢ���ڴ�
						WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
						// ��ͼ����һάתΪ��ά�������ת��������֤����ȷ��
						for (int row = 0; row < 480; ++row)
							for (int col = 0; col < 480; ++col)
							{
								image2DBuf[row][col] = imageBuf[480 * row + col];
							}
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
					else
					{
						if (CMOSImageFlag == TRUE)
						{
							pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
						}
						CMOSImageFlag = FALSE;  // ���ñ�־
					}


#pragma endregion ��ʾ�ӿ׾�ͼ��



					// �����Ѱ���
					WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
					// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
					WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);


#pragma region ���ӵ���Ч���ݴ���취

					for (int row = 1; row < 28; ++row)  // �ճ�����������
					{
						for (int col = 1; col < 28; ++col) // �ճ�����������
						{

							// �ж�x����
							if (_isnan(deviation_x[row][col]))
							{
								++NAN_counter;
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
									str_showerror = "�������ݶ��㷨  �Ӳ���  X�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "�������ݶ��㷨  �Ӳ���  X�����Ѱ���  ��Ч�����ѱ���ֵ";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}


							}  // x�������



							// �ж�y����
							if (_isnan(deviation_y[row][col]))
							{
								++NAN_counter;

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
									str_showerror = "�������ݶ��㷨  �Ӳ���  Y�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "�������ݶ��㷨  �Ӳ���  Y�����Ѱ���  ��Ч�����ѱ���ֵ";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}  // ��������Чֵ��ֵ����

							} // y�������

						}
					}  // ��Чֵ��������

#pragma endregion ���ӵ���Ч���ݴ���취


					//
					//#pragma region �򵥴�����Ч���ݵķ���
					//
					//					NAN_counter = 0;
					//					for (int row = 0; row < 29; ++row)
					//					{
					//						for (int col = 0; col < 29; ++col)
					//						{
					//							if (_isnan(deviation_x[row][col]))
					//							{
					//								++NAN_counter; // ��������һ
					//								FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
					//								str_showerror = "�������ݶ��㷨  �Ӳ���  X�Ѱ���  �г���NAN���ݣ�";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//								deviation_x[row][col] = 0;
					//
					//							}
					//							if (_isnan(deviation_y[row][col]))
					//							{
					//								++NAN_counter; // ��������һ
					//								FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
					//								str_showerror = "�������ݶ��㷨  �Ӳ���  Y�Ѱ���  �г���NAN���ݣ�";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//
					//								deviation_y[row][col] = 0;
					//							}
					//						}
					//					}  // ��Чֵ��������
					//
					//#pragma endregion �򵥴�����Ч���ݵķ���
					//


					// ��ʾ��Ч��ĸ���
					(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
					pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);




					//�����Ѱ����ؽ���ǰ,wavefront����ĵ�λ��um
					WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);


					// ���ݶ��㷨�У�ʹ��ֱ�ӻ��ַ���ò�ǰ�����ǲ��ų���������Чֵ�����������Чֵ�ᵼ�¸��ݲ�ǰ��Ϣ��������ۺ���Ҳ������Чֵ
					// ��ˣ������������ЧֵҪ�����㴦��
					for (int row = 0; row < 29; ++row) // ��Ϊ����Ҫ��ֵ���������ı�����Χ��ȫ�����ӿ׾�
					{
						for (int col = 0; col < 29; ++col)
						{
							if (_isnan(wavefront[row][col]))
							{
								wavefront[row][col] = 0;
							}
						}
					} // ��Чֵ��������



					// ��ǰͳ����Ϣ
					WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min_add, &wavefront_max_add,
						&wavefront_diff_add, &wavefront_mean_add, &wavefront_rms_add, &wavefront_weighted_rms_add);


#pragma endregion ��ǰ̽��


#pragma region �������ۺ���

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


#pragma endregion �������ۺ���

				}//if����  �Ӳ�������

#pragma endregion �Ӳ���


#pragma region ������


				if (count == 1)
				{

#pragma region �����͸����ξ�


					for (int index = 0; index < 140; ++index)
					{
						zernikeMatrix_recon_array_MINUS[index] = zernikeMatrix_recon_array_DEFAULT[index] - randomMatrix[index];
					}



					//## ����Ҫ��һ��ת������vectorת��Ϊ����
					P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
					aoSystemData->dDMDesired = zernikeMatrix_recon_array_MINUS;
					int status = P_DM_SetSpatialFrame();

#pragma endregion �����͸����ξ�


#pragma region ���ξ��ȴ�ʱ��

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
					} while (nTime_dmwait < 10);


#pragma endregion ���ξ��ȴ�ʱ��


#pragma region ��ǰ̽��
					// ��ͨģʽ��ȡ����λ��
					WFS_TakeSpotfieldImage(instr.handle);
					// ��������λ��
					WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);

					// �����Ѱ���
					WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
					// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
					WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);





#pragma region ���ӵ���Ч���ݴ���취

					for (int row = 1; row < 28; ++row)  // �ճ�����������
					{
						for (int col = 1; col < 28; ++col) // �ճ�����������
						{

							// �ж�x����
							if (_isnan(deviation_x[row][col]))
							{
								++NAN_counter;
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
									str_showerror = "�������ݶ��㷨  ������  X�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "�������ݶ��㷨  ������  X�����Ѱ���  ��Ч�����ѱ���ֵ";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}


							}  // x�������



							// �ж�y����
							if (_isnan(deviation_y[row][col]))
							{
								++NAN_counter;

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
									str_showerror = "�������ݶ��㷨  ������  Y�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

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

									str_showerror = "�������ݶ��㷨  ������  Y�����Ѱ���  ��Ч�����ѱ���ֵ";
									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);

								}  // ��������Чֵ��ֵ����

							} // y�������

						}
					}  // ��Чֵ��������

#pragma endregion ���ӵ���Ч���ݴ���취


					//
					//#pragma region �򵥴�����Ч���ݵķ���
					//
					//					NAN_counter = 0;
					//					for (int row = 0; row < 29; ++row)
					//					{
					//						for (int col = 0; col < 29; ++col)
					//						{
					//							if (_isnan(deviation_x[row][col]))
					//							{
					//								++NAN_counter; // ��������һ
					//								FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
					//								str_showerror = "�������ݶ��㷨  ������  X�Ѱ���  �г���NAN���ݣ�";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//								deviation_x[row][col] = 0;
					//
					//							}
					//							if (_isnan(deviation_y[row][col]))
					//							{
					//								++NAN_counter; // ��������һ
					//								FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
					//								str_showerror = "�������ݶ��㷨  ������  Y�Ѱ���  �г���NAN���ݣ�";
					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
					//
					//
					//								deviation_y[row][col] = 0;
					//							}
					//						}
					//					}  // ��Чֵ��������
					//
					//#pragma endregion �򵥴�����Ч���ݵķ���
					//


					// ��ʾ��Ч��ĸ���
					(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
					pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);





					//�����Ѱ����ؽ���ǰ,wavefront����ĵ�λ��um
					WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);


					// ���ݶ��㷨�У�ʹ��ֱ�ӻ��ַ���ò�ǰ�����ǲ��ų���������Чֵ�����������Чֵ�ᵼ�¸��ݲ�ǰ��Ϣ��������ۺ���Ҳ������Чֵ
					// ��ˣ������������ЧֵҪ�����㴦��
					for (int row = 0; row < 29; ++row) // ��Ϊ����Ҫ��ֵ���������ı�����Χ��ȫ�����ӿ׾�
					{
						for (int col = 0; col < 29; ++col)
						{
							if (_isnan(wavefront[row][col]))
							{
								wavefront[row][col] = 0;
							}
						}
					} // ��Чֵ��������


					// �������Ĳ�ǰͳ����Ϣ
					WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min_minus, &wavefront_max_minus,
						&wavefront_diff_minus, &wavefront_mean_minus, &wavefront_rms_minus, &wavefront_weighted_rms_minus);

#pragma endregion ��ǰ̽��


#pragma region �������ۺ���

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

#pragma endregion �������ۺ���


				}//if���� ����������

#pragma endregion ������


				//
				//#pragma region Ĭ�ϲ���
				//				if (count == 2)
				//				{
				//
				//
				//
				//#pragma region �����͸����ξ�
				//
				//
				//					//## ����Ҫ��һ��ת������vectorת��Ϊ����
				//					P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
				//					aoSystemData->dDMDesired = zernikeMatrix_recon_array_DEFAULT;
				//					int status = P_DM_SetSpatialFrame();
				//
				//#pragma endregion �����͸����ξ�
				//
				//
				//#pragma region ���ξ��ȴ�ʱ��
				//
				//					//�¼�ʱ����ʼ
				//					LARGE_INTEGER nStartCounter_dmwait;
				//					LARGE_INTEGER nFrequency_dmwait;
				//					double nTime_dmwait = 0; // ��¼ʱ��
				//
				//					::QueryPerformanceCounter(&nStartCounter_dmwait);
				//					::QueryPerformanceFrequency(&nFrequency_dmwait);
				//
				//
				//					do
				//					{
				//						LARGE_INTEGER nStopCounter_dmwait;
				//						::QueryPerformanceCounter(&nStopCounter_dmwait);
				//						nTime_dmwait = 1000 * ((double)nStopCounter_dmwait.QuadPart - (double)nStartCounter_dmwait.QuadPart) / (double)nFrequency_dmwait.QuadPart;    // ��λ ms
				//					} while (nTime_dmwait < 10);
				//
				//
				//#pragma endregion ���ξ��ȴ�ʱ��
				//
				//
				//#pragma region ��ǰ̽��
				//					// ��ͨģʽ��ȡ����λ��
				//					WFS_TakeSpotfieldImage(instr.handle);
				//					// ��������λ��
				//					WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);
				//
				//					// �����Ѱ���
				//					WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
				//					// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
				//					WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);
				//
				//
				//#pragma region ���ӵ���Ч���ݴ���취
				//
				//					NAN_counter = 0;
				//					for (int row = 1; row < 28; ++row)  // �ճ�����������
				//					{
				//						for (int col = 1; col < 28; ++col) // �ճ�����������
				//						{
				//
				//							// �ж�x����
				//							if (_isnan(deviation_x[row][col]))
				//							{
				//								++NAN_counter;
				//								// ���з�ʽ
				//								//  x x x
				//								//  x o x
				//								//  x x x
				//
				//								if (_isnan(deviation_x[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
				//									_isnan(deviation_x[row - 1][col]) &&
				//									_isnan(deviation_x[row - 1][col + 1]) &&
				//									_isnan(deviation_x[row][col - 1]) &&
				//									_isnan(deviation_x[row][col + 1]) &&
				//									_isnan(deviation_x[row + 1][col - 1]) &&
				//									_isnan(deviation_x[row + 1][col]) &&
				//									_isnan(deviation_x[row + 1][col + 1]))
				//								{
				//									str_showerror = "�������ݶ��㷨  Ĭ�ϲ���  X�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//									deviation_x[row][col] = 0;
				//								}
				//								else
				//								{
				//									// ���з�ʽ
				//									//  x x x
				//									//  x o x
				//									//  x x x
				//
				//									int mean_counter = 0;  // ��Чֵ����
				//									float mean_value = 0;  // ��Чֵ�ĺ�
				//
				//									if (!_isnan(deviation_x[row - 1][col - 1]))  // ����
				//									{
				//										mean_value = mean_value + deviation_x[row - 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row - 1][col])) // ����
				//									{
				//										mean_value = mean_value + deviation_x[row - 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row - 1][col + 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_x[row - 1][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row][col - 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_x[row][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row][col + 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_x[row][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row + 1][col - 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_x[row + 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row + 1][col]))  // ����
				//									{
				//										mean_value = mean_value + deviation_x[row + 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_x[row + 1][col + 1]))  // ����
				//									{
				//										mean_value = mean_value + deviation_x[row + 1][col + 1];
				//										mean_counter++;
				//									}
				//
				//									deviation_x[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ
				//
				//									str_showerror = "�������ݶ��㷨  Ĭ�ϲ���  X�����Ѱ���  ��Ч�����ѱ���ֵ";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//								}
				//
				//
				//							}  // x�������
				//
				//
				//
				//							// �ж�y����
				//							if (_isnan(deviation_y[row][col]))
				//							{
				//								++NAN_counter;
				//
				//								// ���з�ʽ
				//								//  x x x
				//								//  x o x
				//								//  x x x
				//
				//								if (_isnan(deviation_y[row - 1][col - 1]) &&   // �����Ч����Χ8���㶼����Чֵ����ô�˵��Ѱ�������
				//									_isnan(deviation_y[row - 1][col]) &&
				//									_isnan(deviation_y[row - 1][col + 1]) &&
				//									_isnan(deviation_y[row][col - 1]) &&
				//									_isnan(deviation_y[row][col + 1]) &&
				//									_isnan(deviation_y[row + 1][col - 1]) &&
				//									_isnan(deviation_y[row + 1][col]) &&
				//									_isnan(deviation_y[row + 1][col + 1]))
				//								{
				//									str_showerror = "�������ݶ��㷨  Ĭ�ϲ���  Y�����Ѱ���  ������Ч���ݣ� ��Ч���������㣡";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//									deviation_y[row][col] = 0;
				//								} // ǿ���������
				//								else
				//								{
				//									// ���з�ʽ
				//									//  x x x
				//									//  x o x
				//									//  x x x
				//
				//									int mean_counter = 0;  // ��Чֵ����
				//									float mean_value = 0;  // ��Чֵ�ĺ�
				//
				//									if (!_isnan(deviation_y[row - 1][col - 1]))  // ����
				//									{
				//										mean_value = mean_value + deviation_y[row - 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row - 1][col])) // ����
				//									{
				//										mean_value = mean_value + deviation_y[row - 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row - 1][col + 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_y[row - 1][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row][col - 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_y[row][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row][col + 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_y[row][col + 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row + 1][col - 1])) // ����
				//									{
				//										mean_value = mean_value + deviation_y[row + 1][col - 1];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row + 1][col]))  // ����
				//									{
				//										mean_value = mean_value + deviation_y[row + 1][col];
				//										mean_counter++;
				//									}
				//									if (!_isnan(deviation_y[row + 1][col + 1]))  // ����
				//									{
				//										mean_value = mean_value + deviation_y[row + 1][col + 1];
				//										mean_counter++;
				//									}
				//
				//									deviation_y[row][col] = mean_value / mean_counter;  // ������Чֵ��Χ����Чֵ��ƽ��ֵ����Чֵ��ֵ
				//
				//									str_showerror = "�������ݶ��㷨  Ĭ�ϲ���  Y�����Ѱ���  ��Ч�����ѱ���ֵ";
				//									pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//
				//								}  // ��������Чֵ��ֵ����
				//
				//							} // y�������
				//
				//						}
				//					}  // ��Чֵ��������
				//
				//#pragma endregion ���ӵ���Ч���ݴ���취
				//
				//					//
				//					//#pragma region �򵥴�����Ч���ݵķ���
				//					//
				//					//					NAN_counter = 0;
				//					//					for (int row = 0; row < 29; ++row)
				//					//					{
				//					//						for (int col = 0; col < 29; ++col)
				//					//						{
				//					//							if (_isnan(deviation_x[row][col]))
				//					//							{
				//					//								++NAN_counter; // ��������һ
				//					//								FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
				//					//								str_showerror = "�������ݶ��㷨  Ĭ�ϲ���  X�Ѱ���  �г���NAN���ݣ�";
				//					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//					//
				//					//								deviation_x[row][col] = 0;
				//					//
				//					//							}
				//					//							if (_isnan(deviation_y[row][col]))
				//					//							{
				//					//								++NAN_counter; // ��������һ
				//					//								FLAG_NAN = 1;  // ����־λ��ֵΪ1����ʾ����NAN����
				//					//								str_showerror = "�������ݶ��㷨  Ĭ�ϲ���  Y�Ѱ���  �г���NAN���ݣ�";
				//					//								pW->SetDlgItemText(IDC_STATIC_SHOW_ERROR, str_showerror);
				//					//
				//					//
				//					//								deviation_y[row][col] = 0;
				//					//							}
				//					//						}
				//					//					}  // ��Чֵ��������
				//					//
				//					//#pragma endregion �򵥴�����Ч���ݵķ���
				//					//
				//
				//
				//					// ��ʾ��Ч��ĸ���
				//					(pW->m_Edit_Sta_Watch).Format(_T("%d"), NAN_counter);
				//					pW->SetDlgItemTextW(IDC_EDIT_STA_WATCH, pW->m_Edit_Sta_Watch);
				//
				//
				//
				//
				//
				//
				//					//�����Ѱ����ؽ���ǰ,wavefront����ĵ�λ��um
				//					WFS_CalcWavefront(instr.handle, 0, instr_setup.pupil_circular, *wavefront);
				//
				//
				//					// ���ݶ��㷨�У�ʹ��ֱ�ӻ��ַ���ò�ǰ�����ǲ��ų���������Чֵ�����������Чֵ�ᵼ�¸��ݲ�ǰ��Ϣ��������ۺ���Ҳ������Чֵ
				//					// ��ˣ������������ЧֵҪ�����㴦��
				//					for (int row = 0; row < 29; ++row) // ��Ϊ����Ҫ��ֵ���������ı�����Χ��ȫ�����ӿ׾�
				//					{
				//						for (int col = 0; col < 29; ++col)
				//						{
				//							if (_isnan(wavefront[row][col]))
				//							{
				//								wavefront[row][col] = 0;
				//							}
				//						}
				//					} // ��Чֵ��������
				//
				//
				//
				//					// �������Ĳ�ǰͳ����Ϣ
				//					WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
				//						&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);
				//
				//#pragma endregion ��ǰ̽��
				//
				//
				//#pragma region �������ۺ���
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
				//#pragma endregion �������ۺ���
				//
				//
				//				}
				//
				//
				//
				//
				//
				//
				//#pragma endregion Ĭ�ϲ���
				//


			}//for����


#pragma region �о���ʾ����

			// �жϲ��֣�ѡ���������ĸ�����������Ӷ�ȷ����һ��whileѭ������ʼִ����ֵ
			// ��һЩ��ʾ����
			if (meritFunctionValueAdd < (meritFunctionValue))
			{
				meritFunctionValue = meritFunctionValueAdd;

				// ���Ӳ�����ִ������Ϊ�´�ѭ���ĳ�ʼֵ
				for (int index = 0; index < 140; ++index)
				{
					zernikeMatrix_recon_array_DEFAULT[index] = zernikeMatrix_recon_array_ADD[index];
				}

			}
			else if (meritFunctionValueMinus < (meritFunctionValue))
			{

				meritFunctionValue = meritFunctionValueMinus;
				// ����������ִ������Ϊ�´�ѭ���ĳ�ʼֵ
				for (int index = 0; index < 140; ++index)
				{
					zernikeMatrix_recon_array_DEFAULT[index] = zernikeMatrix_recon_array_MINUS[index];
				}

			}


#pragma endregion �о���ʾ����


			// ��ʾ�����������ۺ���ֵ
			(pW->m_Edit_ShowMerit).Format(_T("%lf"), meritFunctionValue);
			pW->SetDlgItemTextW(IDC_EDIT_SHOWMERIT, pW->m_Edit_ShowMerit);
			// ��ʾ�������Ĳ�ǰͳ����Ϣ
			(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff_minus);
			pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);
			(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms_minus);
			pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);


			// ѡ���Ƿ���ʾִ����(�ݶ��㷨)
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




#pragma region ������ʱ����ʼ
			//�¼�ʱ����ʼ
			LARGE_INTEGER nStartCounter_wait;
			LARGE_INTEGER nFrequency_wait;
			double nTime_wait = 0; // ��¼ʱ��

			::QueryPerformanceCounter(&nStartCounter_wait);
			::QueryPerformanceFrequency(&nFrequency_wait);
#pragma endregion ������ʱ����ʼ


			if (pW->ptr_MiscSettingDlg->m_Check_SubDlg_TimeSetter.GetCheck() == 1)  // ѡ���Ƿ���м�ʱ
			{

				do
				{

#pragma region ������ʱ������

					LARGE_INTEGER nStopCounter_wait;
					::QueryPerformanceCounter(&nStopCounter_wait);
					nTime_wait = 1000 * ((double)nStopCounter_wait.QuadPart - (double)nStartCounter_wait.QuadPart) / (double)nFrequency_wait.QuadPart;    // ��λ ms

					//��ʾ��ʱ��
					pW->m_Edit_Show_NewTimer.Format(_T("%lf"), nTime_wait);
					pW->SetDlgItemText(IDC_EDIT_SHOW_NEWTIMER, pW->m_Edit_Show_NewTimer);

#pragma endregion ������ʱ������

				} while (nTime_wait < timerSetterInterval);



			}
			else
			{
				// û�ж�ʱ����ִ��
			}




#pragma region ��ʱ������

			LARGE_INTEGER nStopCounter_test;
			::QueryPerformanceCounter(&nStopCounter_test);
			nTime_test = 1000 * ((double)nStopCounter_test.QuadPart - (double)nStartCounter_test.QuadPart) / (double)nFrequency_test.QuadPart;    // ��λ ms

			//��ʾ��ʱ��
			pW->m_Edit_Sta_Time.Format(_T("%lf"), nTime_test);
			pW->SetDlgItemText(IDC_EDIT_STA_TIME, pW->m_Edit_Sta_Time);

#pragma endregion ��ʱ������


#pragma region ֡����ʾ

			//-----------------------------------------//
			// ֡��---��ֹ����
			::QueryPerformanceCounter(&nStopCounter_2nd);
			// ʱ��������λs
			t_interval_2nd = (double)(nStopCounter_2nd.QuadPart - nStartCounter_2nd.QuadPart) / (double)nFrequency_2nd.QuadPart;
			frameRate = (double)1 / t_interval_2nd;  // WFS��ˢ��Ƶ�ʣ�Ҳ�Ǳջ���Ƶ�ʣ���λHz
			pW->m_Edit_Sta_Frame.Format(_T("%lf"), frameRate);
			pW->SetDlgItemText(IDC_EDIT_STA_FRAME, pW->m_Edit_Sta_Frame);
			//-----------------------------------------//

#pragma endregion ֡����ʾ


		}  // whileѭ������



	}  // if�������ݶ��㷨����

#pragma endregion �ݶ��㷨


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region ֱ��б��

	// ֱ��б�ʷ�����ҪԤ��������
	if (chooseAlgoIndex == 2)
	{

#pragma region ����Ԥ��������
		
		// ע�⣬����Ҫѹջ��Ҳ�Ͳ���Ҫ����ջ


		// ��Matlab����õ�lsqA��eff_picked����
		// ���磬��Ч�ӿ׾������Ϊ609,��ô��lsqA��ά����Ӧ����140*610
		lsqA = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\lsqA.txt");
		// ����eff_pickedҪ��Ϊ��������Ҫ����ת��Ϊconst int����
		// ���磬��Ч�ӿ׾������Ϊ609��eff_picked��ʱ��ʼ��Ϊ841*2�ľ��󣬵�610��Ϊ[0,0]��611�𵽺��涼��δ�����ֵ������֮ǰ����Ч�ӿ׾���λ����Ϣ
		eff_picked = inputMatrix("D:\\externLib\\AOS\\Output\\PreCalc\\out\\eff_picked.txt");
		// ע��eff_picked.size()��ʾ������eff_picked[0].size()��ʾ����
		// ����eff_picked��609���ӿ׾���������ţ���ô����609x2��һ��������ôeff_picked.size()=609��eff_picked[0].size()=2

		//// eff_picked�������ž������£�
		//// MyMat_double���͵�����������
		//lsqA[eff_picked[2][0]][eff_picked[2][1]];
		//// vector<vector<double>>���͵�������������������һ����
		//zernikeMatrix_15[eff_picked[2][0]][eff_picked[2][1]];
		//// float(POD)�������ݾ�Ҫǿת�ˣ�
		//wavefront[(int)eff_picked[2][0]][(int)eff_picked[2][1]];

#pragma endregion ����Ԥ��������


#pragma region �߳��еľֲ�����

		// ����ָ��Ի����ָ��
		CAOSys_v8Dlg* pW = (CAOSys_v8Dlg*)pParam;

		// ���ͼ�йصı���
		uchar image2DBuf[480][480];  // ��ά��ʽ


		// ��������,checkbox��������
		CButton* subApertureImageSwitch = (CButton*)(pW->GetDlgItem(IDC_CHECK_PICSWITCH));
		CButton* wavefrontSwich = (CButton*)(pW->GetDlgItem(IDC_CHECK_WAVEFRONTSWITCH));

		std::vector<double> lsqy;  // lsqx=lsqA*lsqy
		lsqy.resize(610);  // �����������ڴ�ռ�
		int row_effsub;  // ��Ч�����������
		int col_effsub;  // ��Ч�����������

		double zernikeMatrix_recon_array_ACEMETHOD[140];   // ������С���˷������ִ����


#pragma endregion �߳��еľֲ�����




		// �ջ�
		CloseLoopFlag = TRUE;
		while (CloseLoopFlag)
		{

#pragma region ��������λ��

			// ��һ������������λ��
			// ��ͨģʽ��ȡ����λ��
			WFS_TakeSpotfieldImage(instr.handle);
			// ��������λ��
			WFS_CalcSpotsCentrDiaIntens(instr.handle, OPTION_DYN_NOISE_CUT, 0);


#pragma region ��ʾ�ӿ׾�ͼ��

			if (subApertureImageSwitch->GetCheck() == 1)
			{

				// ��ͼ��ˢ���ڴ�
				WFS_GetSpotfieldImageCopy(instr.handle, imageBuf, row_image, col_image);
				// ��ͼ����һάתΪ��ά�������ת��������֤����ȷ��
				for (int row = 0; row < 480; ++row)
					for (int col = 0; col < 480; ++col)
					{
						image2DBuf[row][col] = imageBuf[480 * row + col];
					}

				m_img = cvCreateImageHeader(cvSize(480, 480), 8, 1);
				cvSetData(m_img, image2DBuf, 480); // ��һ���������ڴ棬Ӧ����ͨ��cvReleaseImageHeader�ͷŵ�


				// ������TAB�ؼ����ӿ׾���ǩҳ�ϵĶԻ����ϵ�pic�ؼ���ʾ�ӿ׾���ʵʱͼ��
				// ptr_SubApertureImageDlg��pW�ĳ�Ա
				pW->ptr_SubApertureImageDlg->ShowSubApertuerImageFrame();

				// ���ñ�־
				if (CMOSImageFlag == FALSE)
					CMOSImageFlag = TRUE;

			}
			else
			{
				if (CMOSImageFlag == TRUE)
				{
					pW->ptr_SubApertureImageDlg->ShowNoCMOSImage();
				}
				CMOSImageFlag = FALSE;  // ���ñ�־
			}


#pragma endregion ��ʾ�ӿ׾�ͼ��



#pragma endregion ��������λ��


#pragma region �����Ѱ���

			// �ڶ����������Ѱ���
			// �����Ѱ���
			WFS_CalcSpotToReferenceDeviations(instr.handle, instr_setup.cancel_tilt);
			// ��ȡ�Ѱ�������������ת��Ϊб�����ݣ�������Ҫ���е�λת����WFS_GetSpotDeviations�õ��ĵ�λ��pixels
			WFS_GetSpotDeviations(instr.handle, *deviation_x, *deviation_y);


			// ��¼����ǰ������
// 			fp = fopen("D:\\externLib\\AOS\\Output\\DEBUG_ORIGIN_deviation_x.txt", "w");
// 			if (!fp)
// 			{
// 				::MessageBox(NULL, _T("�޷���WFS_SpotCentroids_X�ļ� ��"), _T("д��״̬"), MB_OK);
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
			


#pragma endregion �����Ѱ���



#pragma region ��ǰͳ�Ʋ���

			WFS_CalcWavefront(instr.handle, instr_setup.wavefront_type, instr_setup.pupil_circular, *wavefront);
			WFS_CalcWavefrontStatistics(instr.handle, &wavefront_min, &wavefront_max,
				&wavefront_diff, &wavefront_mean, &wavefront_rms, &wavefront_weighted_rms);

			// ��ʾPVֵ
			(pW->m_Edit_Sta_PV).Format(_T("%lf"), wavefront_diff);
			pW->SetDlgItemTextW(IDC_EDIT_STA_PV, pW->m_Edit_Sta_PV);

			// ��ʾRMSֵ
			(pW->m_Edit_Sta_RMS).Format(_T("%lf"), wavefront_rms);
			pW->SetDlgItemTextW(IDC_EDIT_STA_RMS, pW->m_Edit_Sta_RMS);


#pragma endregion ��ǰͳ�Ʋ���



#pragma region ���ž���

			int subapture_counter = 0; // ÿ��ѭ����������Ҫ����
			// ������lsqAһ�µ���Ч��˳��ѹջ

			for (int subapture_counter = 0; subapture_counter < 305; ++subapture_counter)
			{

				row_effsub = eff_picked[subapture_counter][0] - 1;
				col_effsub = eff_picked[subapture_counter][1] - 1;
				// ���Ѱ����ĵ�λ��pixelתΪnm��һ�����ش�С9.9um
				lsqy[2 * subapture_counter] = deviation_x[row_effsub][col_effsub];  // ��ѹ��X����
				lsqy[2 * subapture_counter + 1] = deviation_y[row_effsub][col_effsub];  // ��ѹ��y����

			}
			// ��¼����֮�������
// 			write_1d_File("D:\\externLib\\AOS\\Output\\DEBUG_REARRANGE_deviation_x.txt",lsqy);



#pragma endregion ���ž���


#pragma region ����ִ����

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

				zernikeMatrix_recon_array_ACEMETHOD[row] = sum_temp * impulse_stroke;  // �õ��ĵ�λ��nm
			}



			// ��¼ִ����
			fp = fopen("D:\\externLib\\AOS\\Output\\DEBUG_DM_Stroke.txt", "w");
			if (!fp)
			{
				::MessageBox(NULL, _T("�޷���WFS_ZernikeCoeff�ļ� ��"), _T("Writing Status"), MB_OK);
				return -1;
			}

			for (int i = 0; i < 140 + 1; ++i)
			{
				fprintf(fp, "%f", zernikeMatrix_recon_array_ACEMETHOD[i]);
				fputc('\n', fp);
			}
			fclose(fp);



#pragma endregion ����ִ����



#pragma region �������ξ�

			//## ����Ҫ��һ��ת������vectorת��Ϊ����
			P_DM_SetQuadraticCoeffAndMaxV(coeff, 200);
			aoSystemData->dDMDesired = zernikeMatrix_recon_array_ACEMETHOD;
			int status = P_DM_SetSpatialFrame();

#pragma endregion �������ξ�






#pragma region �ȴ�ʱ��

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
			} while (nTime_dmwait < 2000);


#pragma endregion �ȴ�ʱ��



		}  // �ջ�����





	} // if������ֱ��б�ʷ�����



#pragma endregion ֱ��б��
	  


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// �˳��߳�
	return 0;

} // �߳̽���

////////////////////////////////////////////////////////////////////////////////////////////////////////////




#pragma region //## C���ĺ����𽥷������ã��𽥲���C++���ĺ�����11��������
// ����ǰ�����SPOT����λ��д���ļ�
int WFS_WriteSpotCentroids()
{
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WFS_WriteSpotDeviations()
{
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_SpotDeviations_X.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_SpotDeviations_X�ļ� ��"), _T("д��״̬"), MB_OK);
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
		::MessageBox(NULL, _T("�޷���WFS_SpotDeviations_Y�ļ� ��"), _T("д��״̬"), MB_OK);
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
	// ��Zernikeϵ��д���ļ�
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_ZernikeCoeff.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_ZernikeCoeff�ļ� ��"), _T("Writing Status"), MB_OK);
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
		::MessageBox(NULL, _T("�޷���WFS_Zernike_RMS_ROC�ļ� ��"), _T("д��״̬"), MB_OK);
		return -1;
	}

	fprintf(fp, "zernike_orders_rms_um��\n");

	for (int i = 0; i < MAX_ZERNIKE_ORDERS + 1; ++i)
	{
		fprintf(fp, "%f", zernike_orders_rms_um[i]);
		fputc('\n', fp);
	}


	fprintf(fp, "\n");
	fprintf(fp, "roc_mm�� %lf", roc_mm);


	fclose(fp);

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ǰzernike����ʽ�õ���spot deviations�����Ϣд���ļ�
int WFS_WriteCalcReconstrDeviations()
{
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��spot deviations�õ��Ĳ�ǰ��Ϣд���ļ�
int WFS_WriteCalcWavefront()
{
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_CalcWavefront.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_CalcWavefront�ļ� ��"), _T("д��״̬"), MB_OK);
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
// ����ǰ��ͳ����Ϣд���ļ�
int WFS_WriteCalcWavefrontStatistics()
{
	fp = fopen("D:\\externLib\\AOS\\Output\\WFS_CalcWavefrontStatistics.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���WFS_CalcWavefrontStatistics�ļ� ��"), _T("д��״̬"), MB_OK);
		return -1;
	}

	fprintf(fp, "wavefront_min��  %lf \n", wavefront_min);
	fprintf(fp, "wavefront_max�� %lf \n", wavefront_max);
	fprintf(fp, "wavefront_diff�� %lf \n", wavefront_diff);
	fprintf(fp, "wavefront_mean�� %lf \n", wavefront_mean);
	fprintf(fp, "wavefront_rms�� %lf \n", wavefront_rms);
	fprintf(fp, "wavefront_weighted_rms�� %lf \n", wavefront_weighted_rms);


	fclose(fp);

	return 0;
}


// ����ǰ��Zernike����д���ļ�
int WFS_WriteZernikeMatrix()
{
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
	fp = fopen("D:\\externLib\\AOS\\Output\\DM_1DArray.txt", "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���DM_1DArray�ļ� ��"), _T("Writing Status"), MB_OK);
		return -1;
	}

	for (int i = 0; i < MAX_ZERNIKE_MODES + 1; ++i)
	{
		fprintf(fp, "%f", DM_Stroke_1D[i]);
		fputc('\n', fp);
	}
	fclose(fp);


}

#pragma endregion //## C���ĺ����𽥷������ã��𽥲���C++���ĺ���




#pragma region mapping   // ��δ���Ҫ��
////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


// д���ά���ݣ���һ���ܹ��ɹ�������άvector��ͦ�����׵ģ�
int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out);

	std::vector<std::vector<double>>::iterator iter_row;		// ����row����ĵ�����
	std::vector<double>::iterator iter_col;				// ����col����ĵ�����


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



// ʹ�����ĸ����ȡ�ļ��еľ���
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


int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col)
{
	std::vector<double> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// ���ذ汾
int init_2dVector(std::vector<std::vector<int>>&vectordata, const int row, const int col)
{
	std::vector<int> initVector(col, 0);
	for (int i = 0; i < row; ++i)
		vectordata.push_back(initVector);


	return 0;
}

// �ͷŶ�άvector����
int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// ���ذ汾
int release_2dVector(std::vector<std::vector<int>>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;
}

// һάvector��ʼ��
int init_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.push_back(0);

	return 0;

}

// �ͷ�һάvector����
int release_1dVector(std::vector<double>&vectordata, const int row)
{
	for (int i = 0; i < row; ++i)
		vectordata.pop_back();

	return 0;

}


#pragma endregion ȫ�ֺ���



//----------------------------------------------------  �ָ���  ----------------------------------------------------//






