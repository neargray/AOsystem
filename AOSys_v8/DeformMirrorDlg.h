#pragma once

#include <vector>
#include <iostream>
#include "Resource.h"

#include "WFS.h"
#include "AOSystem_DataStructures.h"



extern std::vector<std::vector<double>> zernikeMatrix_recon;
extern double coeff[3];  // nm - V映射系数
extern AOSystemData *aoSystemData;
extern int write_2d_File(const std::string& filename, std::vector<std::vector<double>>& array_2d);
extern double pid_p, pid_i, pid_d;




// CDeformMirrorDlg dialog

class CDeformMirrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeformMirrorDlg)

public:
	CDeformMirrorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeformMirrorDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DMMATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSubdlgSubapertureRefresh();
	afx_msg void OnBnClickedButtonSubdlgSubapertureLoad();

	// 控件的成员变量数组
	CString m_Edit_DM[144];

};


