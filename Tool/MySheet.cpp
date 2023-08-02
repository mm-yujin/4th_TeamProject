// MySheet.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "MySheet.h"
#include "afxdialogex.h"


// CMySheet 대화 상자

IMPLEMENT_DYNAMIC(CMySheet, CDialog)

CMySheet::CMySheet(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CMySheet, pParent)
{

}

CMySheet::~CMySheet()
{
}

void CMySheet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMySheet, CDialog)
END_MESSAGE_MAP()


// CMySheet 메시지 처리기
