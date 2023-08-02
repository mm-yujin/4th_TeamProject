// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnMapTool)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnPathFInd)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnMySheet)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnLUAScript)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnTeamAgent)
END_MESSAGE_MAP()


// CMyForm �����Դϴ�.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// CreatePointFont(��Ʈ ũ��, �۾�ü)
	m_Font.CreatePointFont(120, L"����");

	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON4)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON5)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON3)->SetFont(&m_Font);
}


void CMyForm::OnUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// GetSafeHwnd : ���� ���̾�α��� ������ �ڵ��� ��ȯ, �ڵ��� null�̸� ���� �����Ǿ� ���� ������ �ǹ�

	if(nullptr == m_UnitTool.GetSafeHwnd())
		m_UnitTool.Create(IDD_UNITTOOL);

	m_UnitTool.ShowWindow(SW_SHOW);

}


void CMyForm::OnMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_MAPTOOL);

	m_MapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnPathFInd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_PathFind.GetSafeHwnd())
		m_PathFind.Create(IDD_CPathFind);

	m_PathFind.ShowWindow(SW_SHOW);
}


void CMyForm::OnMySheet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_MySheet.GetSafeHwnd())
		m_MySheet.Create(IDD_CMySheet);

	m_MySheet.ShowWindow(SW_SHOW);
}


void CMyForm::OnLUAScript()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_LUAScript.GetSafeHwnd())
		m_LUAScript.Create(IDD_CLUA_Script);

	m_LUAScript.ShowWindow(SW_SHOW);
}


void CMyForm::OnTeamAgent()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_TeamAgent.GetSafeHwnd())
		m_TeamAgent.Create(IDD_CTeamAgent);

	m_TeamAgent.ShowWindow(SW_SHOW);
}
