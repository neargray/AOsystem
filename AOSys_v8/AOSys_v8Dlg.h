

// AOSys_v8Dlg.h : 头文件
#pragma once

// 这里include WFS.h文件，是因为下面用到了该文件定义的数据类型，比如ViChar
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

// 添加选项卡类的头文件
#include "SubApertureDlg.h"
#include "DeformMirrorDlg.h"
#include "DeviationXDlg.h"
#include "MiscSettingDlg.h"
#include "afxwin.h"



// 双精度类型的二维vector，专门用于inputMatrix函数读取txt文件中的矩阵而用的数据类型
typedef std::vector<std::vector<double>> MyMat_double;



#pragma region 全局函数声明
//----------------------------------------------------  全局函数声明  ----------------------------------------------------//
// 处理错误抛出的错误
void WFS_HandleErrors(int err);

// 选择WFS设备
int WFS_SelectInstrument(LPVOID pParam, int* selection, ViChar* resourceName);

// 选择MLA
int SlectMLA(int* selection);

// 初始化WFS
// 可以传递任何简单的数据类型，注意还原！this指针等等是最常传递的！
void WFS_Initialization_Sequence(LPVOID pParam);

//--------------------------------------------------------------------------------

#pragma region //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数（11个函数）
// 将当前的SPOT中心位置写入文件
int WFS_WriteSpotCentroids();

// 将当前的Deviation位置写入文件
int WFS_WriteSpotDeviations();

// 将当前的zernike多项式信息写入文件
int WFS_WriteZernikeLsf();

// 将当前zernike多项式得到的spot deviations拟合信息写入文件
int WFS_WriteCalcReconstrDeviations();

// 将spot deviations得到的波前信息写入文件
int WFS_WriteCalcWavefront();

// 将波前的统计信息写入文件
int WFS_WriteCalcWavefrontStatistics();

// 将当前的Zernike矩阵写入文件
int WFS_WriteZernikeMatrix();

// 将wavefront与zerWave_Matrix29矩阵的减法结果写入文件
int WFS_WriteWavefrontZernikeError();

// 用于静态校正波前时，校验matlab计算的zernike拟合矩阵
int DM_WriteCheckZernikeMatrix();

// 用于将操作后的矩阵写入文件
int DM_WriteTransposeMatrix();

// 用于将一维的数组写入文件，即写入变形镜的一维数组
int DM_Write1DMatrix();
#pragma endregion //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数


//--------------------------------------------------------------------------------


// 声明波前探测阶段的线程函数
UINT ThreadFunc_WFS_Measurement_DET(LPVOID pParam);

// 声明波前重建阶段的线程函数
UINT ThreadFunc_WFS_Measurement_REC(LPVOID pParam);

// 声明波前控制阶段的线程函数
UINT ThreadFunc_WFS_Measurement_CONLOOP(LPVOID pParam);

// 预处理的线程函数
UINT ThreadFunc_PreCalculation(LPVOID pParam);

//--------------------------------------------------------------------------------

// 矩阵转置
int MatrixTranspose(int gridIndex, float** matrixOut, float** matrixIn);

// 矩阵左右翻转
int MatrixFlipLeftRight(int gridIndex, float** matrixOut, float** matrixIn);

// 矩阵上下翻转
int MatrixFlipUpDown(int gridIndex, float** matrixOut, float** matrixIn);

// 矩阵顺时针旋转90度=上下翻转后转置
int MatrixRotate90(int gridIndex, float** matrixOut, float** matrixIn);
int MatrixRotate90_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector版本


// 矩阵顺时针旋转180度=左右翻转后上下翻转
int MatrixRotate180(int gridIndex, float** matrixOut, float** matrixIn);
int MatrixRotate180_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector版本

// 矩阵顺时针旋转270度=作于翻转后再转置
int MatrixRotate270(int gridIndex, float** matrixOut, float** matrixIn);
int MatrixRotate270_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector版本

// 不进行任何旋转
int MatrixRotate0_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector版本

// 上下翻转
int MatrixFlipUpDown_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector版本

// 左右翻转
int MatrixFlipLeftRight_vector(std::vector<std::vector<double>>& matrixOut, std::vector<std::vector<double>>& matrixIn);   // vector版本


//--------------------------------------------------------------------------------
// 以下是新版的写入文件的函数，主要特征是使用了std::vector容器，希望能够逐步代替之前的C风格的全局函数

// 写入一维数据
int write_1d_File(const std::string& filename, std::vector<double>& array_1d);

// 写入二维数据
int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d);
int write_2d_File(const std::string& filename, std::vector<std::vector<int>>& array_2d);  // 重载版本

// 使用流的概念读取文件中的矩阵
MyMat_double inputMatrix(const std::string& filename);

// 二维vector初始化
int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col);
int init_2dVector(std::vector<std::vector<int>>&vectordata, const int row, const int col); // 重载版本

// 释放二维vector数据
int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row);
int release_2dVector(std::vector<std::vector<int>>&vectordata, const int row);    // 重载版本

// 一维vector初始化
int init_1dVector(std::vector<double>&vectordata, const int row);

// 释放一维vector数据
int release_1dVector(std::vector<double>&vectordata, const int row);


// 由于是小段函数，因此直接inline
static inline void IntToString(std::string& out, const int value)
{
	std::strstream ss; // #include <strstream>
	ss << value;
	ss >> out;
}


// 用于等待一定时间的函数，输入时间单位ms
int wait4U(int time_milliseconds);

// 用于驱动变形镜的函数，单位是nm，按照引用传形参，数组大小固定
int DriveDeformMirror_nm(double (&executeStroke)[140]);

// 用于驱动变形镜的函数，单位是V，这个函数目前还没有写
// int DriveDeformMirror_V(double(&executeStroke)[140]);

// 用于探测波前的脱靶量(仅适用于普通模式)
int Detect_Wavefront2Deviation_Normal();

// 用于直接处理脱靶量，保证处理后的数据没有无效值，适用于普通模式与高速模式，输入可能包含无效值的脱靶量，输出全部有效的脱靶量
int MeanInterpolation_KillNAN();

// 计算并返回评价函数，评价函数的计算方式是：x与y方向的脱靶量平方相加，最后开根号得到
double CalcMeritFunc_SquareDevi();



#pragma endregion 全局函数声明

//----------------------------------------------------  以上为全局函数声明  ----------------------------------------------------//

#pragma region //框架代码

// CAOSys_v8Dlg 对话框
class CAOSys_v8Dlg : public CDialogEx
{
// 构造
public:
	CAOSys_v8Dlg(CWnd* pParent = NULL);	// 标准构造函数

	CWinThread* pThread_DET;  // 用于波前探测的线程
	CWinThread* pThread_REC;  // 用于波前重建的线程
	CWinThread* pThread_LOOP; // 用于闭环的线程
	CWinThread* pThread_PreCalc; // 用于闭环的线程


	// TAB控件上每个对话框的指针，每个对话框都有一个指针
	// 子对话框的类被定义为主对话框类的成员变量
	CSubApertureDlg*  ptr_SubApertureImageDlg;
	CDeformMirrorDlg* ptr_DeformMirrorDlg;
	CDeviationXDlg* ptr_DeviationXDlg;
	CMiscSettingDlg* ptr_MiscSettingDlg;



// 对话框数据
	enum { IDD = IDD_AOSYS_V8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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


#pragma endregion //框架代码


