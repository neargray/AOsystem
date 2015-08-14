#pragma once

#include "Resource.h"



// CReconWavefrontDlg dialog

class CReconWavefrontDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReconWavefrontDlg)

public:
	CReconWavefrontDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReconWavefrontDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_RECONWAVEFRONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

