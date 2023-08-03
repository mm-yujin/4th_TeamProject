// LuaRichEdit.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "LuaRichEdit.h"


// CLuaRichEdit

IMPLEMENT_DYNAMIC(CLuaRichEdit, CRichEditCtrl)

CLuaRichEdit::CLuaRichEdit()
{

}

CLuaRichEdit::~CLuaRichEdit()
{
}


BEGIN_MESSAGE_MAP(CLuaRichEdit, CRichEditCtrl)
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()



// CLuaRichEdit 메시지 처리기
UINT CLuaRichEdit::OnGetDlgCode()
{
	UINT flags = CRichEditCtrl::OnGetDlgCode();
	flags &= ~DLGC_WANTTAB;
	return flags;
}

BOOL CLuaRichEdit::PreTranslateMessage(MSG* pMsg)
{
    // 텍스트 색상 변경
    /*long iStart, iEnd;
    GetSel(iStart, iEnd);

    CHARFORMAT cf;
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_COLOR;
    cf.crTextColor = 0xFF0000FF;

    SetSel(iStart, iEnd);
    SetSelectionCharFormat(cf);

    SetSel(iStart, iStart);*/

    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
    {
        CString strNewText = _T("\t");
        ReplaceSel(strNewText);
        return TRUE; // Tab 키를 여기서 처리하고 더 이상 전파되지 않도록 합니다.
    }
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        CString strNewText = _T("\n");
        
        CString strPrevText;
        GetLine(SendMessage(EM_LINEFROMCHAR, -1, 0), strPrevText.GetBufferSetLength(256), 256);
        ReplaceSel(strNewText);
        if (-1 != strPrevText.Find(_T("function"), 0))
        {
            ReplaceSel(_T("\t"));
        }
        
        return TRUE; // Tab 키를 여기서 처리하고 더 이상 전파되지 않도록 합니다.
    }

    return CRichEditCtrl::PreTranslateMessage(pMsg);
}
