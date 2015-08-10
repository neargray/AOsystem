// DeformMirrorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DeformMirrorDlg.h"

#include "AOSys_v8.h"




// CDeformMirrorDlg dialog

IMPLEMENT_DYNAMIC(CDeformMirrorDlg, CDialogEx)

CDeformMirrorDlg::CDeformMirrorDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDeformMirrorDlg::IDD, pParent)
// �ؼ���ʼ����ֵ
{

}

CDeformMirrorDlg::~CDeformMirrorDlg()
{
}

void CDeformMirrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// ��ÿ���ؼ��󶨵�������
	for (int i = 0; i < 144; ++i)
	{
		DDX_Text(pDX, IDC_EDIT_DM_M001 + i, m_Edit_DM[i]);
	}

}


BEGIN_MESSAGE_MAP(CDeformMirrorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SUBDLG_SUBAPERTURE_REFRESH, &CDeformMirrorDlg::OnBnClickedButtonSubdlgSubapertureRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SUBDLG_SUBAPERTURE_LOAD, &CDeformMirrorDlg::OnBnClickedButtonSubdlgSubapertureLoad)
END_MESSAGE_MAP()


// CDeformMirrorDlg message handlers
// �� ��ǰ�ؽ�ģʽ�� ��ǰ�ؽ��¼� ��õ�zernikeMatrix_reconˢ���� TAB�ؼ������ξ����ƾ��󡱱�ǩҳ��EDIT�ؼ� ��
void CDeformMirrorDlg::OnBnClickedButtonSubdlgSubapertureRefresh()
{
	// TODO: Add your control notification handler code here  vector<vector<double>>& array_2d

	// ���ڴ��е�ֵˢ��EDIT�ؼ���ʾ
	float temp = 0;
	for (int k_index = 0; k_index < 144; ++k_index)
	{
		temp = (zernikeMatrix_recon[k_index / 12][k_index % 12]) * 500 * pid_p + 1200;
		m_Edit_DM[k_index].Format(_T("%lf"), temp); // һά����תΪ��ά����
		SetDlgItemTextW(IDC_EDIT_DM_M001 + k_index, m_Edit_DM[k_index]);

	}

	write_2d_File("D:\\externLib\\AOS\\Output\\TAB_ZernikeMatrixRefresh.txt", zernikeMatrix_recon);

}

// �� TAB�ؼ������ξ����ƾ��󡱱�ǩҳ��EDIT�ؼ� �е�ֵˢ����ξ�
void CDeformMirrorDlg::OnBnClickedButtonSubdlgSubapertureLoad()
{
	// TODO: Add your control notification handler code here
	float temp = 0;
	for (int k_index = 0; k_index < 144; ++k_index)
	{
		GetDlgItem(IDC_EDIT_DM_M001 + k_index)->GetWindowText(m_Edit_DM[k_index]);
		temp = _ttof(m_Edit_DM[k_index]);  // һά����תΪ��ά����
		zernikeMatrix_recon[k_index / 12][k_index % 12] = (temp - 1200) / (500 * pid_d);

	}
	
	write_2d_File("D:\\externLib\\AOS\\Output\\TAB_ZernikeMatrixLoad.txt", zernikeMatrix_recon);


}
