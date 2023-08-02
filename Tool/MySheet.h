#pragma once


#include "afxwin.h"

#include "Include.h"

// CMySheet 대화 상자

class CMySheet : public CDialog
{
	DECLARE_DYNAMIC(CMySheet)

public:
	CMySheet(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMySheet();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMySheet };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
