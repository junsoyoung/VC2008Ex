
// test1_a.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Ctest1_aApp:
// �� Ŭ������ ������ ���ؼ��� test1_a.cpp�� �����Ͻʽÿ�.
//

class Ctest1_aApp : public CWinAppEx
{
public:
	Ctest1_aApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Ctest1_aApp theApp;