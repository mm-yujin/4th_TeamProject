// PathFind.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "PathFind.h"
#include "afxdialogex.h"


// CPathFind 대화 상자

IMPLEMENT_DYNAMIC(CPathFind, CDialog)

CPathFind::CPathFind(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CPathFind, pParent)
{

}

CPathFind::~CPathFind()
{
}

void CPathFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPathFind, CDialog)
END_MESSAGE_MAP()


// CPathFind 메시지 처리기
