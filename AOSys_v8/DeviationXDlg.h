#pragma once

#include "Resource.h"


extern float deviation_x[40][50];
extern float deviation_y[40][50];


// CDeviationXDlg dialog

class CDeviationXDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviationXDlg)

public:
	CDeviationXDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeviationXDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DEVIATION_X };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_Edit_DeviationX[100];
	CString m_Edit_DeviationY[100];


	BOOL ShowDeviationX();
};
