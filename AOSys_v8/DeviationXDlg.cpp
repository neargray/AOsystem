// DeviationXDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DeviationXDlg.h"

#include "AOSys_v8.h"


// CDeviationXDlg dialog

IMPLEMENT_DYNAMIC(CDeviationXDlg, CDialogEx)

CDeviationXDlg::CDeviationXDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDeviationXDlg::IDD, pParent)
{

}

CDeviationXDlg::~CDeviationXDlg()
{
}

void CDeviationXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// 将每个控件绑定到数组中
	for (int i = 0; i < 100; ++i)
	{
		DDX_Text(pDX, IDC_EDIT_DLG_DEVI_X001 + i, m_Edit_DeviationX[i]);
	}
	for (int i = 0; i < 100; ++i)
	{
		DDX_Text(pDX, IDC_EDIT_DLG_DEVI_Y001 + i, m_Edit_DeviationY[i]);
	}


}


BEGIN_MESSAGE_MAP(CDeviationXDlg, CDialogEx)
END_MESSAGE_MAP()


// CDeviationXDlg message handlers


BOOL CDeviationXDlg::ShowDeviationX()
{
	float temp_x[10][10];
	float temp_y[10][10];

	// 将29x29抽取为10x10数据，因为一个子对话框的控件数目不能超过255个
	for (int row = 6, row_temp = 0; row < 25; row += 2, row_temp++)
		for (int col = 6, col_temp = 0; col < 25; col += 2, col_temp++)
		{
			temp_x[row_temp][col_temp] = deviation_x[row][col];
			temp_y[row_temp][col_temp] = deviation_y[row][col];
		}

	for (int k_index = 0; k_index < 100; ++k_index)
	{
		m_Edit_DeviationX[k_index].Format(_T("%lf"), temp_x[k_index / 10][k_index % 10]); // 一维数组转为二维数组
		SetDlgItemTextW(IDC_EDIT_DLG_DEVI_X001 + k_index, m_Edit_DeviationX[k_index]);

	}

	for (int k_index = 0; k_index < 100; ++k_index)
	{
		m_Edit_DeviationY[k_index].Format(_T("%lf"), temp_y[k_index / 12][k_index % 12]); // 一维数组转为二维数组
		SetDlgItemTextW(IDC_EDIT_DLG_DEVI_Y001 + k_index, m_Edit_DeviationY[k_index]);

	}



	return 0;
}
