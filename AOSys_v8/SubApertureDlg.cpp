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

	// 获得pic控件的句柄，这样才知道去哪里显示图像
	CDC *pDC = GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->GetDC();  // 这一句申请了内存，需要通过ReleaseDC释放

	HDC hDC = pDC->GetSafeHdc();  // 这一句申请了内存，需要通过DeleteDC释放
	CRect rect;
	GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->GetClientRect(&rect);

	CvvImage cimg;
	// m_img是全局变量，要想在这里使用
	// 就需要在SubApertureDlg.h文件中，用extern声明才能在这里使用
	cimg.CopyOf(m_img); 
	cimg.DrawToHDC(hDC, &rect);

	//要调用CWnd类下的ReleaseDC函数
	DeleteDC(hDC);
	GetDlgItem(IDC_STATIC_PIC_SUBAPERTUER)->ReleaseDC(pDC);
	// 释放cvCreateImageHeader创建的header
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
