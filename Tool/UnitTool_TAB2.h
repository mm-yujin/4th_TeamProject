#pragma once

#include "afxwin.h"
#include "Include.h"

// UnitTool_TAB2 대화 상자

class UnitTool_TAB2 : public CDialogEx
{
	DECLARE_DYNAMIC(UnitTool_TAB2)

public:
	UnitTool_TAB2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UnitTool_TAB2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
