// UnitTool_TAB2.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_TAB2.h"
#include "afxdialogex.h"


// UnitTool_TAB2 대화 상자

IMPLEMENT_DYNAMIC(UnitTool_TAB2, CDialogEx)

UnitTool_TAB2::UnitTool_TAB2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITTOOL_TAB2, pParent)
	, m_str_AddTeam(_T(""))
{
	for (int i = 0; i < 2; ++i) {
		m_Slider_Hos[i] = { 0 };
		m_Hos_Cap[i] = _T("");
	}
}

UnitTool_TAB2::~UnitTool_TAB2()
{
}

void UnitTool_TAB2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str_AddTeam);
	DDX_Slider(pDX, IDC_SLIDER1, m_Slider_Hos[0]);
	DDV_MinMaxInt(pDX, m_Slider_Hos[0], 0, 100);
	DDX_Slider(pDX, IDC_SLIDER2, m_Slider_Hos[1]);
	DDV_MinMaxInt(pDX, m_Slider_Hos[1], 0, 100);
	DDX_Control(pDX, IDC_LIST4, m_ListBox_ViewHos_From);
	DDX_Control(pDX, IDC_LIST5, m_ListBox_SettingHos_From);
	DDX_Text(pDX, IDC_EDIT5, m_Hos_Cap[0]);
	DDX_Text(pDX, IDC_EDIT8, m_Hos_Cap[1]);
	DDX_Control(pDX, IDC_LIST2, m_ListBox_ViewHos_To);
	DDX_Control(pDX, IDC_LIST3, m_ListBox_SettingHos_To_Once);
	DDX_Control(pDX, IDC_LIST6, m_ListBox_SettingHos_To_Multi);
}


BEGIN_MESSAGE_MAP(UnitTool_TAB2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UnitTool_TAB2::OnAddTeamButton)
	ON_LBN_SELCHANGE(IDC_LIST4, &UnitTool_TAB2::OnListBox_ViewHos_From)
	ON_LBN_SELCHANGE(IDC_LIST5, &UnitTool_TAB2::OnListBox_SettingHos_From)
END_MESSAGE_MAP()


// UnitTool_TAB2 메시지 처리기


void UnitTool_TAB2::OnAddTeamButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_TeamMainList.empty())
		m_TeamMainList.push_back(m_str_AddTeam);

	else if (!m_TeamMainList.empty())
	{
		for (auto& iter : m_TeamMainList)
		{
			if (iter == m_str_AddTeam)
			{
				AfxMessageBox(L"이미 존재하는 팀 명 입니다. 다른 팀 명을 입력해주세요.");
				return;
			}
		}

		m_TeamMainList.push_back(m_str_AddTeam);
	}


	m_ListBox_ViewHos_From.ResetContent();
	m_ListBox_SettingHos_From.ResetContent();

	if (!m_TeamMainList.empty())
	{
		for (auto& iter : m_TeamMainList) {
			m_ListBox_ViewHos_From.AddString(iter);
			m_ListBox_SettingHos_From.AddString(iter);
		}
	}

	m_str_AddTeam = L"";

	UpdateData(FALSE);
}


void UnitTool_TAB2::OnListBox_ViewHos_From()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_ListBox_ViewHos_To.ResetContent();

	CString		strFindName;
	int		iIndex = m_ListBox_ViewHos_From.GetCurSel();
	m_ListBox_ViewHos_From.GetText(iIndex, strFindName);

	if (!m_TeamViewToList.empty())
		m_TeamViewToList.clear();

	for (auto& iter : m_TeamMainList) {
		if (iter != strFindName)
			m_TeamViewToList.push_back(iter);
	}

	for (auto& iter : m_TeamViewToList) {
		m_ListBox_ViewHos_To.AddString(iter);
	}

	UpdateData(FALSE);
}


void UnitTool_TAB2::OnListBox_SettingHos_From()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_ListBox_SettingHos_To_Once.ResetContent();
	m_ListBox_SettingHos_To_Multi.ResetContent();

	CString		strFindName;
	int		iIndex = m_ListBox_SettingHos_From.GetCurSel();
	m_ListBox_SettingHos_From.GetText(iIndex, strFindName);

	if (!m_TeamSetToList.empty())
		m_TeamSetToList.clear();

	for (auto& iter : m_TeamMainList) {
		if (iter != strFindName)
			m_TeamSetToList.push_back(iter);
	}

	for (auto& iter : m_TeamSetToList) {
		m_ListBox_SettingHos_To_Once.AddString(iter);
		m_ListBox_SettingHos_To_Multi.AddString(iter);
	}

	UpdateData(FALSE);



}
