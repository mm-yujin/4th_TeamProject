// LUA_Script.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "LUA_Script.h"
#include "afxdialogex.h"


// CLUA_Script 대화 상자

IMPLEMENT_DYNAMIC(CLUA_Script, CDialog)

CLUA_Script::CLUA_Script(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CLUA_Script, pParent)
{

}

CLUA_Script::~CLUA_Script()
{
}

void CLUA_Script::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLUA_Script, CDialog)
END_MESSAGE_MAP()


// CLUA_Script 메시지 처리기
