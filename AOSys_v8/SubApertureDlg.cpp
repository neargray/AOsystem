// SubApertureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"

#include "SubApertureDlg.h"



// CSubApertureDlg dialog

IMPLEMENT_DYNAMIC(CSubApertureDlg, CDialogEx)

CSubApertureDlg::CSubApertureDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSubApertureDlg::IDD, pParent)
{

}

CSubApertureDlg::~CSubApertureDlg()
{
}

void CSubApertureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubApertureDlg, CDialogEx)
END_MESSAGE_MAP()


// CSubApertureDlg message handlers


BOOL CSubApertureDlg::ShowSubApertuerImageFrame()
{

	// ���pic�ؼ��ľ����������֪��ȥ������ʾͼ��
	CDC *pDC = GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->GetDC();  // ��һ���������ڴ棬��Ҫͨ��ReleaseDC�ͷ�

	HDC hDC = pDC->GetSafeHdc();  // ��һ���������ڴ棬��Ҫͨ��DeleteDC�ͷ�
	CRect rect;
	GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->GetClientRect(&rect);

	CvvImage cimg;
	// m_img��ȫ�ֱ�����Ҫ��������ʹ��
	// ����Ҫ��SubApertureDlg.h�ļ��У���extern��������������ʹ��
	cimg.CopyOf(m_img); 
	cimg.DrawToHDC(hDC, &rect);

	//Ҫ����CWnd���µ�ReleaseDC����
	DeleteDC(hDC);
	GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->ReleaseDC(pDC);
	// �ͷ�cvCreateImageHeader������header
	cvReleaseImageHeader(&m_img);

	return TRUE;
}


BOOL CSubApertureDlg::ShowNoCMOSImage()
{
	cv::Mat NoCMOSImage = cv::imread("nocomosimage.jpg");
	IplImage header_NoCMOSImage = NoCMOSImage;


	CDC* pDC = GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CvvImage cimg;
	cimg.CopyOf(&header_NoCMOSImage);
	CRect rect;
	GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->GetClientRect(&rect);
	cimg.DrawToHDC(hDC, &rect);

	return 0;
}
