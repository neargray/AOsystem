#pragma once


// CDeformMirrorMatrix dialog

class CDeformMirrorMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDeformMirrorMatrix)

public:
	CDeformMirrorMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeformMirrorMatrix();

// Dialog Data
	enum { IDD = IDD_DIALOG_DMMATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
