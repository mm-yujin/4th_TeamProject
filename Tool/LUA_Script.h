#pragma once


#include "afxwin.h"

#include "Include.h"


// CLUA_Script 대화 상자

class CLUA_Script : public CDialog
{
	DECLARE_DYNAMIC(CLUA_Script)

public:
	CLUA_Script(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLUA_Script();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLUA_Script };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
