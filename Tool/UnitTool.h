#pragma once
#include "afxwin.h"
#include "TeamAgent.h"
#include "Include.h"

#include "UnitTool_TAB1.h"
#include "UnitTool_TAB2.h"

// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialogEx
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	

	DECLARE_MESSAGE_MAP()
public:

	CTabCtrl m_TAB;
	UnitTool_TAB1*	dlg_Tab1;
	UnitTool_TAB2*	dlg_Tab2;

public:

	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
};

// 저장하기, 불러오기, 삭제하기, 탐색하기(edit control 이용하여 탐색)