// GetUnique.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetUniqueApp:
// �йش����ʵ�֣������ GetUnique.cpp
//

class CGetUniqueApp : public CWinApp
{
public:
	CGetUniqueApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetUniqueApp theApp;