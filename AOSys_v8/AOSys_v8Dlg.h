

// AOSys_v8Dlg.h : ͷ�ļ�
#pragma once

// ����include WFS.h�ļ�������Ϊ�����õ��˸��ļ�������������ͣ�����ViChar
#include "afxcmn.h"
#include <vector>
#include <string>		// for string
#include <fstream>		// for file I/O
#include <iomanip>		// for setw()
#include <cstdlib>		// for exit()
#include <iostream>
#include <sstream>		// for istringstream
#include <strstream>

#include "WFS.h"
#include "CvvImage.h"   // opencv for show

// ���ѡ����ͷ�ļ�
#include "SubApertureDlg.h"
#include "DeformMirrorDlg.h"
#include "DeviationXDlg.h"
#include "MiscSettingDlg.h"
#include "afxwin.h"



// ˫�������͵Ķ�άvector��ר������inputMatrix������ȡtxt�ļ��еľ�����õ���������
typedef std::vector<std::vector<double>> MyMat_double;



#pragma region ȫ�ֺ�������
//----------------------------------------------------  ȫ�ֺ�������  ----------------------------------------------------//
// ��������׳��Ĵ���
void WFS_HandleErrors(int err);

// ѡ��WFS�豸
int WFS_SelectInstrument(LPVOID pParam, int* selection, ViChar* resourceName);

// ѡ��MLA
int SlectMLA(int* selection);

// ��ʼ��WFS
// ���Դ����κμ򵥵��������ͣ�ע�⻹ԭ��thisָ��ȵ�������ݵģ�
void WFS_Initialization_Sequence(LPVOID pParam);

//--------------------------------------------------------------------------------

#pragma region //## C���ĺ����𽥷������ã��𽥲���C++���ĺ�����11��������
// ����ǰ��SPOT����λ��д���ļ�
int WFS_WriteSpotCentroids();

// ����ǰ��Deviationλ��д���ļ�
int WFS_WriteSpotDeviations();

// ����ǰ��zernike����ʽ��Ϣд���ļ�
int WFS_WriteZernikeLsf();

// ����ǰzernike����ʽ�õ���spot deviations�����Ϣд���ļ�
int WFS_WriteCalcReconstrDeviations();

// ��spot deviations�õ��Ĳ�ǰ��Ϣд���ļ�
int WFS_WriteCalcWavefront();

// ����ǰ��ͳ����Ϣд���ļ�
int WFS_WriteCalcWavefrontStatistics();

// ����ǰ��Zernike����д���ļ�
int WFS_WriteZernikeMatrix();

// ��wavefront��zerWave_Matrix29����ļ������д���ļ�
int WFS_WriteWavefrontZernikeError();

// ���ھ�̬У����ǰʱ��У��matlab�����zernike��Ͼ���
int DM_WriteCheckZernikeMatrix();

// ���ڽ�������ľ���д���ļ�
int DM_WriteTransposeMatrix();

// ���ڽ�һά������д���ļ�����д����ξ���һά����
int DM_Write1DMatrix();
#pragma endregion //## C���ĺ����𽥷������ã��𽥲���C++���ĺ���


//--------------------------------------------------------------------------------


// ������ǰ̽��׶ε��̺߳���
UINT ThreadFunc_WFS_Measurement_DET(LPVOID pParam);

// ������ǰ�ؽ��׶ε��̺߳���
UINT ThreadFunc_WFS_Measurement_REC(LPVOID pParam);

// ������ǰ���ƽ׶ε��̺߳���
UINT ThreadFunc_WFS_Measurement_CONLOOP(LPVOID pParam);

// Ԥ������̺߳���
UINT ThreadFunc_PreCalculation(LPVOID pParam);

//--------------------------------------------------------------------------------

// ����ת��
int MatrixTranspose(int gridIndex, float** matrixOut, float** matrixIn);

// �������ҷ�ת
int MatrixFlipLeftRight(int gridIndex, float** matrixOut, float** matrixIn);

// �������·�ת
int MatrixFlipUpDown(int gridIndex, float** matrixOut, float** matrixIn);

// ����˳ʱ����ת90��=���·�ת��ת��
int MatrixRotate90(int gridIndex, float** matrixOut, float** matrixIn);
int MatrixRotate90_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector�汾


// ����˳ʱ����ת180��=���ҷ�ת�����·�ת
int MatrixRotate180(int gridIndex, float** matrixOut, float** matrixIn);
int MatrixRotate180_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector�汾

// ����˳ʱ����ת270��=���ڷ�ת����ת��
int MatrixRotate270(int gridIndex, float** matrixOut, float** matrixIn);
int MatrixRotate270_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector�汾

// �������κ���ת
int MatrixRotate0_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector�汾

// ���·�ת
int MatrixFlipUpDown_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector�汾

// ���ҷ�ת
int MatrixFlipLeftRight_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector�汾


//--------------------------------------------------------------------------------
// �������°��д���ļ��ĺ�������Ҫ������ʹ����std::vector������ϣ���ܹ��𲽴���֮ǰ��C����ȫ�ֺ���

// д��һά����
int write_1d_File(const std::string& filename, std::vector<double>& array_1d);

// д���ά����
int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d);
int write_2d_File(const std::string& filename, std::vector<std::vector<int>>& array_2d);  // ���ذ汾

// ʹ�����ĸ����ȡ�ļ��еľ���
MyMat_double inputMatrix(const std::string& filename);

// ��άvector��ʼ��
int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col);
int init_2dVector(std::vector<std::vector<int>>&vectordata, const int row, const int col); // ���ذ汾

// �ͷŶ�άvector����
int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row);
int release_2dVector(std::vector<std::vector<int>>&vectordata, const int row);    // ���ذ汾

// һάvector��ʼ��
int init_1dVector(std::vector<double>&vectordata, const int row);

// �ͷ�һάvector����
int release_1dVector(std::vector<double>&vectordata, const int row);


// ������С�κ��������ֱ��inline
static inline void IntToString(std::string& out, const int value)
{
	std::strstream ss; // #include <strstream>
	ss << value;
	ss >> out;
}


// ���ڵȴ�һ��ʱ��ĺ���������ʱ�䵥λms
int wait4U(int time_milliseconds);

// �����������ξ��ĺ�������λ��nm���������ô��βΣ������С�̶�
int DriveDeformMirror_nm(double (&executeStroke)[140]);

// �����������ξ��ĺ�������λ��V���������Ŀǰ��û��д
// int DriveDeformMirror_V(double(&executeStroke)[140]);

// ����̽�Ⲩǰ���Ѱ���(����������ͨģʽ)
int Detect_Wavefront2Deviation_Normal();

// ����ֱ�Ӵ����Ѱ�������֤����������û����Чֵ����������ͨģʽ�����ģʽ��������ܰ�����Чֵ���Ѱ��������ȫ����Ч���Ѱ���
int MeanInterpolation_KillNAN();

// ���㲢�������ۺ��������ۺ����ļ��㷽ʽ�ǣ�x��y������Ѱ���ƽ����ӣ���󿪸��ŵõ�
double CalcMeritFunc_SquareDevi();



#pragma endregion ȫ�ֺ�������

//----------------------------------------------------  ����Ϊȫ�ֺ�������  ----------------------------------------------------//

#pragma region //��ܴ���

// CAOSys_v8Dlg �Ի���
class CAOSys_v8Dlg : public CDialogEx
{
// ����
public:
	CAOSys_v8Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	CWinThread* pThread_DET;  // ���ڲ�ǰ̽����߳�
	CWinThread* pThread_REC;  // ���ڲ�ǰ�ؽ����߳�
	CWinThread* pThread_LOOP; // ���ڱջ����߳�
	CWinThread* pThread_PreCalc; // ���ڱջ����߳�


	// TAB�ؼ���ÿ���Ի����ָ�룬ÿ���Ի�����һ��ָ��
	// �ӶԻ�����౻����Ϊ���Ի�����ĳ�Ա����
	CSubApertureDlg*  ptr_SubApertureImageDlg;
	CDeformMirrorDlg* ptr_DeformMirrorDlg;
	CDeviationXDlg* ptr_DeviationXDlg;
	CMiscSettingDlg* ptr_MiscSettingDlg;



// �Ի�������
	enum { IDD = IDD_AOSYS_V8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonWfsIni();
	afx_msg void OnClickedButtonDmIni();
	afx_msg void OnClickedButtonGridon();
	afx_msg void OnClickedButtonClose();
	afx_msg void OnClickedButtonDetDetection();
	afx_msg void OnClickedButtonDetWrite();
	afx_msg void OnClickedButtonRecReconstruction();
	afx_msg void OnClickedButtonRecWrite();
	afx_msg void OnClickedButtonConCloseloop();
	afx_msg void OnClickedButtonConWrite();
	afx_msg void OnClickedButtonRecZerfiterr();
	CString m_Edit_Sta_WfsName;
	CString m_Eit_Sta_WfsSN;
	CString m_Edit_Sta_RscName;
	CString m_Edit_Sta_Expo;
	CString m_Edit_Sta_Gain;
	CString m_Edit_Sta_BL;
	CString m_Edit_Manufacture;
	CString m_Edit_CMOSSN;
	CString m_Edit_Sta_Calibration;
	CString m_Edit_Sta_Resolution;
	CString m_Edit_Sta_SubApture;
	CString m_Edit_Sta_SubApture_Y;
	CString m_Edit_Sta_PupilDia_X;
	CString m_Edit_Sta_PupilDia_Y;
	CString m_Edit_Sta_PupilCenter_X;
	CString m_Edit_Sta_Pupil_Center_Y;
	CString m_Edit_WFSStatus;
	CString m_Edit_DMStatus;
	CString m_Edit_WFSSel;
	CString m_Edit_Grid_Index;
	CString m_Edit_Sta_Write;
	CString m_Edit_Sta_BeamCen_X;
	CString m_Edit_Sta_BeamCen_Y;
	CString m_Edit_Sta_BeamDia_X;
	CString m_Edit_Sta_BeamDia_Y;
	CString m_Edit_Sta_WavefrontType;
	CString m_Edit_Sta_PupilLimit;
	CString m_Edit_Sta_PV;
	CString m_Edit_Sta_Frame;
	CString m_Edit_Sta_RMS;
	CString m_Edit_Show_PupilLimit;
	CString m_Edit_Show_WavefrontType;
	CString m_Edit_PupilCenter_X;
	CString m_Edit_PupilCenter_Y;
	CString m_Edit_PupilDia_X;
	CString m_Edit_PupilDia_Y;
	CString m_Edit_Show_BL;
	CString m_Edit_Show_CancelTilt;
	CString m_Edit_Sta_CancelTilt;
	CString m_Edit_Sta_GridType;
	afx_msg void OnClickedButtonRecConDm();
	CString m_Edit_Sta_Map;
	afx_msg void OnClickedButtonDmZero();
	afx_msg void OnClickedButtonDmCenterup();
	CString m_Edit_Sta_Time;
	CString m_Edit_Sta_Watch;
	afx_msg void OnBnClickedButtonInterrupt();
	CTabCtrl m_tabDisplay;
//	afx_msg void OnTcnSelchangingTabDisplay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabDisplay(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_Edit_SetNoiseCut;
	CString m_Edit_Std_NoiseCut;
	CString m_Edit_CoordMove_X;
	CString m_Edit_CoordMove_Y;
	afx_msg void OnBnClickedButtonReleaseMem();
	CString m_Edit_ShowPID_I;
	CString m_Edit_ShowPID_D;
	CString m_Edit_ShowPID_P;
	CString m_Edit_SetPID_D;
	CString m_Edit_SetPID_I;
	CString m_Edit_SetPID_P;
	afx_msg void OnBnClickedButtonGearup();
	CString m_Edit_SetAngle;
	CComboBox m_Combo_ChooseAlgo;
	afx_msg void OnSelchangeComboChoosealgo();
	CString m_Edit_ShowMerit;
	CString m_Edit_Show_NewTimer;
	afx_msg void OnBnClickedButtonPreCalc();
	int Show_MeritPVRMS(double merit, double PV, double RMS);
	int Timer_SetTimer(double settimer);
	int rotateMatrix_12vector(int angle, std::vector<std::vector<double>>& origin, std::vector<std::vector<double>>& modified);
	int Show_PVRMS(double PV, double RMS);
};


#pragma endregion //��ܴ���


