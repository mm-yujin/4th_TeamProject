#pragma once
#include "afxwin.h"
#include "TeamAgent.h"
#include "Include.h"

#include "UnitTool_TAB1.h"
#include "UnitTool_TAB2.h"

// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnListBox();
	afx_msg void OnCreateUnit();	
	afx_msg void OnSearchData();

public:
	// �ƹ� �ǹ� ���� ����
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

// �����ϱ�, �ҷ�����, �����ϱ�, Ž���ϱ�(edit control �̿��Ͽ� Ž��)