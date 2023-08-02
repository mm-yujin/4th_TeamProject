// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
#include "ToolView.h"

// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UNITTOOL, pParent)

{

}

CUnitTool::~CUnitTool()
{


}


void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_Main, m_TAB);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Main, &CUnitTool::OnSelchangeTabMain)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.




void CUnitTool::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_TAB.GetCurSel();

	switch (sel) {
	case 0:
		dlg_Tab1->ShowWindow(SW_SHOW);
		dlg_Tab2->ShowWindow(SW_HIDE);
		break;
	case 1:
		dlg_Tab1->ShowWindow(SW_HIDE);
		dlg_Tab2->ShowWindow(SW_SHOW);
		break;
	}



	*pResult = 0;
}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_TAB.InsertItem(0, L"UNIT Data");
	m_TAB.InsertItem(1, L"TEAM Data");

	m_TAB.SetCurSel(0);

	CRect rect;
	m_TAB.GetWindowRect(&rect);

	dlg_Tab1 = new UnitTool_TAB1;
	dlg_Tab1->Create(IDD_UNITTOOL_TAB1, &m_TAB);
	dlg_Tab1->MoveWindow(0, 25, rect.Width(), rect.Height());
	dlg_Tab1->ShowWindow(SW_SHOW);

	dlg_Tab2 = new UnitTool_TAB2;
	dlg_Tab2->Create(IDD_UNITTOOL_TAB2, &m_TAB);
	dlg_Tab2->MoveWindow(0, 25, rect.Width(), rect.Height());
	dlg_Tab2->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUnitTool::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::PostNcDestroy();

	dlg_Tab1->DestroyWindow();
	delete dlg_Tab1;
	dlg_Tab1 = NULL;

	dlg_Tab2->DestroyWindow();
	delete dlg_Tab2;
	dlg_Tab2 = NULL;

}
