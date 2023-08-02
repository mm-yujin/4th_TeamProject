#pragma once

#include "afxwin.h"
#include "Include.h"
// UnitTool_TAB1 대화 상자

class UnitTool_TAB1 : public CDialogEx
{
	DECLARE_DYNAMIC(UnitTool_TAB1)

public:
	UnitTool_TAB1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UnitTool_TAB1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
