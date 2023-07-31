#pragma once
#include "afxwin.h"

#include "Include.h"
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnListBox();
	afx_msg void OnCreateUnit();	
	virtual BOOL OnInitDialog();
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

public:
	map<CString, UNITDATA*>		m_mapUnitData;

	afx_msg void OnDeleteData();
	afx_msg void OnSaveData();
	afx_msg void OnLoadData();
};

// �����ϱ�, �ҷ�����, �����ϱ�, Ž���ϱ�(edit control �̿��Ͽ� Ž��)