// MiscSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AOSys_v8.h"
#include "MiscSettingDlg.h"
#include "afxdialogex.h"


// CMiscSettingDlg dialog

IMPLEMENT_DYNAMIC(CMiscSettingDlg, CDialogEx)

CMiscSettingDlg::CMiscSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMiscSettingDlg::IDD, pParent)
	, m_Edit_TimeSetter(_T(""))
	, m_Static_RememberState(_T(""))
{
}

CMiscSettingDlg::~CMiscSettingDlg()
{
}

void CMiscSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SUBDLG_TIMERSETTING, m_Edit_TimeSetter);
	DDX_Control(pDX, IDC_CHECK_SUBDLG_TIMESETTER, m_Check_SubDlg_TimeSetter);
	DDX_Control(pDX, IDC_CHECK_REMEMBER_DEVIATION, m_Check_SubDlg_RemeberDevi);
	DDX_Text(pDX, IDC_STATIC_REMEMBER_STATE, m_Static_RememberState);
	DDX_Control(pDX, IDC_CHECK_REMEMBER_MERIT, m_Check_Remember_Merit);
}


BEGIN_MESSAGE_MAP(CMiscSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REMEMBER_DEVI, &CMiscSettingDlg::OnBnClickedButtonRememberDevi)
END_MESSAGE_MAP()


// CMiscSettingDlg message handlers


void CMiscSettingDlg::OnBnClickedButtonRememberDevi()
{
	// TODO: Add your control notification handler code here
	FILE   *fp;


	CString filenamePrefix, strTemp, finenameSuffix;
	CString strRow, strCol, fileFullPath;

	filenamePrefix = "D:\\externLib\\AOS\\Output\\MiscSetting_REMEMBERDEVIATION_";
	strTemp = "_";
	finenameSuffix = ".txt";


	for (int row = 0; row < 29;++row)
	{
		for (int col = 0; col < 29; ++col)
		{

			strRow.Format(_T("%d"), row);
			strCol.Format(_T("%d"), col);

			fileFullPath = filenamePrefix + strRow + strTemp + strCol + finenameSuffix;

			fp = _tfopen((LPCTSTR)fileFullPath, _T("w"));

			if (!fp)
			{
				::MessageBox(NULL, _T("无法写入文件！"), _T("写入状态"), MB_OK);
			}

			for (int i = 0; i < 100; ++i)
			{
				fprintf(fp, "%f", rememberDeviationX[row][col][i]);
				fputc('\n', fp);
			}

			fprintf(fp, "\n");

			fclose(fp);

		}
	}




}





