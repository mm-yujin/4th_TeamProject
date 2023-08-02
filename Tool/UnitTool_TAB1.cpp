﻿// UnitTool_TAB1.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_TAB1.h"
#include "afxdialogex.h"


// UnitTool_TAB1 대화 상자

IMPLEMENT_DYNAMIC(UnitTool_TAB1, CDialogEx)

UnitTool_TAB1::UnitTool_TAB1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITTOOL_TAB1, pParent)
	, m_strTemp(_T(""))
	, m_strSrc(_T(""))
	, m_strName(_T(""))
	, m_iHp(0)
	, m_iAttack(0)
	, m_strFindName(_T(""))
{

}

UnitTool_TAB1::~UnitTool_TAB1()
{
	for_each(m_mapUnitData.begin(), m_mapUnitData.end(), CDeleteMap());
	m_mapUnitData.clear();
}

void UnitTool_TAB1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iHp);
	DDX_Text(pDX, IDC_EDIT5, m_iAttack);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_CHECK1, m_Check[0]);
	DDX_Control(pDX, IDC_CHECK2, m_Check[1]);
	DDX_Control(pDX, IDC_CHECK3, m_Check[2]);

	DDX_Text(pDX, IDC_EDIT6, m_strFindName);

}


BEGIN_MESSAGE_MAP(UnitTool_TAB1, CDialogEx)

	ON_LBN_SELCHANGE(IDC_LIST1, &UnitTool_TAB1::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON2, &UnitTool_TAB1::OnCreateUnit)
	ON_EN_CHANGE(IDC_EDIT6, &UnitTool_TAB1::OnSearchData)
	ON_BN_CLICKED(IDC_BUTTON5, &UnitTool_TAB1::OnDeleteData)
	ON_BN_CLICKED(IDC_BUTTON6, &UnitTool_TAB1::OnSaveData)
	ON_BN_CLICKED(IDC_BUTTON7, &UnitTool_TAB1::OnLoadData)
END_MESSAGE_MAP()


// UnitTool_TAB1 메시지 처리기


void UnitTool_TAB1::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString		strFindName;

	//GetCurSel : 리스트 박스에서 선택한 목록의 인덱스를 반환

	int		iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	// GetText : 해당 인덱스의 문자열을 얻어오는 함수
	m_ListBox.GetText(iIndex, strFindName);

	auto		iter = m_mapUnitData.find(strFindName);

	if (iter == m_mapUnitData.end())
		return;

	m_strName = iter->second->strName;
	m_iHp = iter->second->iHp;
	m_iAttack = iter->second->iAttack;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}

	m_Radio[iter->second->byJobIndex].SetCheck(TRUE);

	if (iter->second->byItem & RUBY)
		m_Check[0].SetCheck(TRUE);

	if (iter->second->byItem & DIAMOND)
		m_Check[1].SetCheck(TRUE);

	if (iter->second->byItem & SAPPHIRE)
		m_Check[2].SetCheck(TRUE);


	UpdateData(FALSE);

}


void UnitTool_TAB1::OnCreateUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	UNITDATA* pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iHp = m_iHp;
	pUnit->iAttack = m_iAttack;

	for (int i = 0; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck())
		{
			pUnit->byJobIndex = i;
			break;
		}
	}


	pUnit->byItem = 0x00;

	if (m_Check[0].GetCheck())
		pUnit->byItem |= RUBY;

	if (m_Check[1].GetCheck())
		pUnit->byItem |= DIAMOND;

	if (m_Check[2].GetCheck())
		pUnit->byItem |= SAPPHIRE;



	// AddString : 리스트 박스에 문자열을 추가
	m_ListBox.AddString(pUnit->strName);
	m_mapUnitData.insert({ pUnit->strName, pUnit });

	m_strName = L"";
	m_iHp = 0;
	m_iAttack = 0;
	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}


	UpdateData(FALSE);
}



void UnitTool_TAB1::OnSearchData()
{
	UpdateData(TRUE);

	auto& iter = m_mapUnitData.find(m_strFindName);

	if (iter == m_mapUnitData.end())
		return;

	int		iIndex = m_ListBox.FindString(0, m_strFindName);

	if (LB_ERR == iIndex)
		return;

	m_ListBox.SetCurSel(iIndex);

	m_strName = iter->second->strName;
	m_iHp = iter->second->iHp;
	m_iAttack = iter->second->iAttack;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_Check[i].SetCheck(FALSE);
	}

	m_Radio[iter->second->byJobIndex].SetCheck(TRUE);

	if (iter->second->byItem & RUBY)
		m_Check[0].SetCheck(TRUE);

	if (iter->second->byItem & DIAMOND)
		m_Check[1].SetCheck(TRUE);

	if (iter->second->byItem & SAPPHIRE)
		m_Check[2].SetCheck(TRUE);


	UpdateData(FALSE);
}



void UnitTool_TAB1::OnDeleteData()
{
	UpdateData(TRUE);

	CString		strFindName = L"";

	int		iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	// GetText : 해당 인덱스의 문자열을 얻어오는 함수
	m_ListBox.GetText(iIndex, strFindName);

	auto		iter = m_mapUnitData.find(strFindName);

	if (iter == m_mapUnitData.end())
		return;

	Safe_Delete(iter->second);
	m_mapUnitData.erase(strFindName);

	m_ListBox.DeleteString(iIndex);

	UpdateData(FALSE);
}


void UnitTool_TAB1::OnSaveData()
{
	// CFileDialog : 파일 열기 혹은 저장작업 필요한 대화상자를 생성하는 객체

	CFileDialog	Dlg(FALSE, // TRUE(열기), FALSE(다른 이름으로 저장) 모드 지정
		L"dat", // default 확장자명
		L"*.dat",  // 대화 상자에 표시할 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기 전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 저장 시 경고 메세지 띄움)
		L"Data File(*.dat) | *.dat||", // "콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열"
		this);	// 부모 윈도우 주소

	TCHAR		szPath[MAX_PATH] = L"";

	// GetCurrentDirectory: 현재 프로젝트가 있는 디렉토리 경로를 얻어옴(절대 경로)
	GetCurrentDirectory(MAX_PATH, szPath);
	//szPath = 0x00afeb90 L"D:\\유준환\\139기\\Frame139\\Tool"

	// PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라내는 함수, 경로 상에 파일명이 없다면 제일 말단 폴더 이름을 잘라낸다.
	PathRemoveFileSpec(szPath);
	// szPath = 0x00afeb90 L"D:\\유준환\\139기\\Frame139"

	/* /, //, \, \\, | (token, 구분자) : 경로에서 폴더명 단위로 잘라내어 쓰거나 읽고자 할 때 구분하기 위한 기호 */

	lstrcat(szPath, L"\\Data");
	// szPath = 0x00afeb90 L"D:\\유준환\\139기\\Frame139\\Data"

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : 선택된 경로를 반환
		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		DWORD	dwStrByte = 0;

		for (auto& MyPair : m_mapUnitData)
		{
			// key 값 저장
			dwStrByte = sizeof(TCHAR) * (MyPair.first.GetLength() + 1);

			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, MyPair.first.GetString(), dwStrByte, &dwByte, nullptr);

			// value 값 저장

			WriteFile(hFile, &(MyPair.second->iAttack), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(MyPair.second->iHp), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(MyPair.second->byJobIndex), sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &(MyPair.second->byItem), sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &(MyPair.second->byTeam), sizeof(BYTE), &dwByte, nullptr);

		}

		CloseHandle(hFile);

	}
}

/*
string strName;
char	szName[32];

strcpy_s(szName, strName.c_str());*/


void UnitTool_TAB1::OnLoadData()
{
	UpdateData(TRUE);

	CFileDialog	Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기 전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 저장 시 경고 메세지 띄움)
		L"Data File(*.dat) | *.dat||", this);

	TCHAR		szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{

		for (auto& MyPair : m_mapUnitData)
			delete MyPair.second;

		m_mapUnitData.clear();
		m_ListBox.ResetContent();

		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		DWORD	dwStrByte = 0;
		UNITDATA	tData{};


		while (true)
		{
			// key 값 저장
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR* pName = new TCHAR[dwStrByte];

			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

			// value 값 저장

			ReadFile(hFile, &(tData.iAttack), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iHp), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.byJobIndex), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tData.byItem), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tData.byTeam), sizeof(BYTE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[]pName;
				break;
			}

			UNITDATA* pUnit = new UNITDATA;
			pUnit->strName = pName;
			delete[]pName;

			pUnit->iAttack = tData.iAttack;
			pUnit->iHp = tData.iHp;
			pUnit->byJobIndex = tData.byJobIndex;
			pUnit->byItem = tData.byItem;
			pUnit->byTeam = tData.byTeam;

			m_mapUnitData.insert({ pUnit->strName, pUnit });

			m_ListBox.AddString(pUnit->strName);

		}

		CloseHandle(hFile);

	}

	UpdateData(FALSE);
}


//void UnitTool_TAB1::OnBnClickedButton1_TeamAgent()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	if (!m_TeamNameCheck.GetCheck())
//		AfxMessageBox(L"진영(팀) 이름의 확정 처리가 되지 않았습니다. \n 확정 처리 후 세팅이 가능합니다.");
//
//	else if (m_TeamNameCheck.GetCheck()) {
//		if (nullptr == m_TeamAgent.GetSafeHwnd())
//			m_TeamAgent.Create(IDD_CTeamAgent);
//
//		m_TeamAgent.ShowWindow(SW_SHOW);
//	}
//}
//
//
//void UnitTool_TAB1::OnTeamNameSet()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	if (m_TeamNameCheck.GetCheck())
//	{
//		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
//		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
//		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
//	}
//	else if (!m_TeamNameCheck.GetCheck())
//	{
//		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
//		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
//		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
//	}
//}
