#pragma once

#include "afxwin.h"
#include "Include.h"
#include "TeamAgent.h"

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

public:
	afx_msg void OnListBox();
	afx_msg void OnCreateUnit();
	afx_msg void OnSearchData();


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

	CTeamAgent	m_TeamAgent;

	map<CString, UNITDATA*>		m_mapUnitData;

	afx_msg void OnDeleteData();
	afx_msg void OnSaveData();
	afx_msg void OnLoadData();

};
