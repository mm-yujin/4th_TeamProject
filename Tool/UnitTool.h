#pragma once
#include "afxwin.h"
#include "TeamAgent.h"
#include "Include.h"

#include "UnitTool_TAB1.h"
#include "UnitTool_TAB2.h"

// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialogEx
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

	CTabCtrl m_TAB;
	UnitTool_TAB1*	dlg_Tab1;
	UnitTool_TAB2*	dlg_Tab2;

public:

	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
};

// �����ϱ�, �ҷ�����, �����ϱ�, Ž���ϱ�(edit control �̿��Ͽ� Ž��)