// TeamAgent.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "TeamAgent.h"
#include "afxdialogex.h"


// CTeamAgent 대화 상자

IMPLEMENT_DYNAMIC(CTeamAgent, CDialog)

CTeamAgent::CTeamAgent(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CTeamAgent, pParent)
{

}

CTeamAgent::~CTeamAgent()
{
}

void CTeamAgent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTeamAgent, CDialog)
END_MESSAGE_MAP()


// CTeamAgent 메시지 처리기
