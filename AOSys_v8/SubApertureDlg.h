#pragma once

#include "Resource.h"

#include "CvvImage.h"   // opencv for show
#include "WFS.h"

// OpenCV��ͷ�ļ�
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



//using namespace cv;

extern IplImage *m_img;  // ��ȡͼƬ



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
	//  �ӶԻ�����ʾ
	BOOL ShowSubApertuerImageFrame();
	BOOL ShowNoCMOSImage();
};

