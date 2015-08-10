// DeformMirrorMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "AOSys_v8.h"
#include "DeformMirrorMatrix.h"
#include "afxdialogex.h"


// CDeformMirrorMatrix dialog

IMPLEMENT_DYNAMIC(CDeformMirrorMatrix, CDialogEx)

CDeformMirrorMatrix::CDeformMirrorMatrix(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeformMirrorMatrix::IDD, pParent)
{

}

CDeformMirrorMatrix::~CDeformMirrorMatrix()
{
}

void CDeformMirrorMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeformMirrorMatrix, CDialogEx)
END_MESSAGE_MAP()


// CDeformMirrorMatrix message handlers
