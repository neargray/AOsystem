#pragma once


// m_DeformMirrorMatrixDlg dialog

class m_DeformMirrorMatrixDlg : public CDialogEx
{
	DECLARE_DYNAMIC(m_DeformMirrorMatrixDlg)

public:
	m_DeformMirrorMatrixDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~m_DeformMirrorMatrixDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DMMATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
