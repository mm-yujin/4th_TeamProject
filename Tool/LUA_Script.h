#pragma once


#include "afxwin.h"

#include "Include.h"
#include "LuaRichEdit.h"


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

public:
	vector<CSliderCtrl*>	m_vecSlider;
	CLuaRichEdit			m_RichEdit;
	CLuaRichEdit			m_RichEdit2;
	CLuaRichEdit			m_RichEdit3;

public:
	afx_msg virtual BOOL OnInitDialog() override;
	void AddSlider(int iIndex);
	afx_msg void OnEnUpdateLuaEdit();
	afx_msg void OnSaveLua();
	afx_msg void OnLoadLua();
	afx_msg void OnSaveLua2();
	afx_msg void OnLoadLua2();
	afx_msg void OnSaveLua3();
	afx_msg void OnLoadLua3();
};
