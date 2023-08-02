#pragma once

#include "afxwin.h"

#include "Include.h"

// CTeamAgent 대화 상자

class CTeamAgent : public CDialog
{
	DECLARE_DYNAMIC(CTeamAgent)

public:
	CTeamAgent(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTeamAgent();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTeamAgent };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
