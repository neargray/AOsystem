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
}


BEGIN_MESSAGE_MAP(CMiscSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REMEMBER_DEVI, &CMiscSettingDlg::OnBnClickedButtonRememberDevi)
	ON_BN_CLICKED(IDC_BUTTON_DLG_DRAW, &CMiscSettingDlg::OnBnClickedButtonDlgDraw)
	ON_BN_CLICKED(IDC_BUTTON_DLG_CLEAN, &CMiscSettingDlg::OnBnClickedButtonDlgClean)
	//ON_WM_PAINT()
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


void CMiscSettingDlg::OnBnClickedButtonDlgDraw()
{
	// TODO: Add your control notification handler code here

	//display = 1;
	//RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

}


void CMiscSettingDlg::OnBnClickedButtonDlgClean()
{
	// TODO: Add your control notification handler code here

	display = 2;
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

}


//void CMiscSettingDlg::OnPaint()
//{
//
//
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // device context for painting
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// Center icon in client rectangle
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// Draw the icon
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//
//		if (display == 1)
//		{
//			CPaintDC dc(this);
//
//			CPen pen(PS_SOLID, 1, RGB(rand() % 255, rand() % 255, rand() % 255));
//			dc.SelectObject(pen);
//
//			CRect rect;
//			GetClientRect(&rect);
//			int nWidth = 0.75*rect.Width();
//			int nHeight = 0.75*rect.Height();
//
//			const unsigned int SEGMENT = 100;
//			CPoint pt[SEGMENT];
//			for (int i = 0; i < SEGMENT; ++i)
//			{
//				pt[i].x = i*nWidth / SEGMENT;
//				//pt[i].y = (int)((nHeight / 2)*(1 - sin(2 * 3.1415926*i / SEGMENT)));
//				pt[i].y = rand() % 100 + 140;
//
//			}
//
//			dc.Polyline(pt, SEGMENT);
//
//			DeleteObject(dc);
//
//		}
//		if (display == 2)
//		{
//			CPaintDC dc(this);
//
//			CPen pen(PS_SOLID, 1, RGB(230, 230, 230));  // (230, 230, 230)这个RGB值比较接近界面的灰色了
//			dc.SelectObject(pen);
//
//			CRect rect;
//			GetClientRect(&rect);
//			int nWidth = 0.75*rect.Width();
//			int nHeight = 0.75*rect.Height();
//
//			const unsigned int SEGMENT = 100;
//			CPoint pt[SEGMENT];
//			for (int i = 0; i < SEGMENT; ++i)
//			{
//				pt[i].x = i*nWidth / SEGMENT;
//				pt[i].y = (int)((nHeight / 2)*(1 - sin(2 * 3.1415926*i / SEGMENT))) + 30;
//			}
//
//			dc.Polyline(pt, SEGMENT);
//
//			DeleteObject(dc);
//
//
//		}
//	}
//
//
//}
