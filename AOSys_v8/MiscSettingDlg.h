#pragma once
#include "afxwin.h"


// CMiscSettingDlg dialog

extern	float	rememberDeviationX[40][50][100]; // ���ڼ�¼ÿ��ʱ���Ѱ�����ֵ
extern	float	rememberDeviationY[40][50][100]; // ���ڼ�¼ÿ��ʱ���Ѱ�����ֵ


class CMiscSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMiscSettingDlg)

public:
	CMiscSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMiscSettingDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_MISCSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_Edit_TimeSetter;
	CButton m_Check_SubDlg_TimeSetter;
	CButton m_Check_SubDlg_RemeberDevi;
	CString m_Static_RememberState;
	afx_msg void OnBnClickedButtonRememberDevi();

	CButton m_Check_Remember_Merit;
};
