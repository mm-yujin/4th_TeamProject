﻿#pragma once

#include "afxwin.h"

#include "Include.h"

// CPathFind 대화 상자

class CPathFind : public CDialog
{
	DECLARE_DYNAMIC(CPathFind)

public:
	CPathFind(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPathFind();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPathFind };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};