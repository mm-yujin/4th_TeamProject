#pragma once
#include "afxwin.h"
#include "TeamAgent.h"
#include "Include.h"

#include "UnitTool_TAB1.h"
#include "UnitTool_TAB2.h"

// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
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
	afx_msg void OnListBox();
	afx_msg void OnCreateUnit();	
	afx_msg void OnSearchData();

public:
	// 아무 의미 없는 변수
	CString m_strTemp;
	CString m_strSrc;
	CString m_strName;
	int m_iHp;
	int m_iAttack;

public:
	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_Check[3];
	CButton m_Bitmap;
	CString m_strFindName;
	CButton m_Team[3];

	CTeamAgent	m_TeamAgent;

	CTabCtrl m_TAB;
	UnitTool_TAB1*	dlg_Tab1;
	UnitTool_TAB2*	dlg_Tab2;

public:
	map<CString, UNITDATA*>		m_mapUnitData;

	afx_msg void OnDeleteData();
	afx_msg void OnSaveData();
	afx_msg void OnLoadData();
	afx_msg void OnBnClickedButton1_TeamAgent();
	afx_msg void OnTeamNameSet();
	CButton m_TeamNameCheck;
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};

// 저장하기, 불러오기, 삭제하기, 탐색하기(edit control 이용하여 탐색)