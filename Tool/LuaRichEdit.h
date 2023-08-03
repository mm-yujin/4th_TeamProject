#pragma once


// CLuaRichEdit

class CLuaRichEdit : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CLuaRichEdit)

public:
	CLuaRichEdit();
	virtual ~CLuaRichEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
};


