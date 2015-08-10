#pragma once

#include "Resource.h"

#include "CvvImage.h"   // opencv for show
#include "WFS.h"

// OpenCV的头文件
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



//using namespace cv;

extern IplImage *m_img;  // 读取图片



// CSubApertureDlg dialog

class CSubApertureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubApertureDlg)

public:
	CSubApertureDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubApertureDlg();


// Dialog Data
	enum { IDD = IDD_DIALOG_SUBAPERTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//  子对话框显示
	BOOL ShowSubApertuerImageFrame();
	BOOL ShowNoCMOSImage();
};

