
// AOSys_v8.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "Resource.h"		// ������


// CAOSys_v8App: 
// �йش����ʵ�֣������ AOSys_v8.cpp
//

class CAOSys_v8App : public CWinApp
{
public:
	CAOSys_v8App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAOSys_v8App theApp;

