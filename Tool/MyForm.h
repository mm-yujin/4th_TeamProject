#pragma once


#include "UnitTool.h"
#include "MapTool.h"

#include "PathFind.h"
#include "MySheet.h"
#include "LUA_Script.h"
#include "TeamAgent.h"

// CMyForm �� ���Դϴ�.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:

	virtual void OnInitialUpdate();
	afx_msg void OnUnitTool();

public:
	CFont		m_Font;
	CUnitTool	m_UnitTool;
	CMapTool	m_MapTool;

	CPathFind	m_PathFind;
	CMySheet	m_MySheet;
	CLUA_Script	m_LUAScript;
	CTeamAgent	m_TeamAgent;

	afx_msg void OnMapTool();
	afx_msg void OnPathFInd();
	afx_msg void OnMySheet();
	afx_msg void OnLUAScript();
	afx_msg void OnTeamAgent();
};


