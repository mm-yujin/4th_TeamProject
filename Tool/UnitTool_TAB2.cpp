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
		m_iSlider_Hos[i] = { 0 };
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
	DDX_Slider(pDX, IDC_SLIDER1, m_iSlider_Hos[0]);
	DDV_MinMaxInt(pDX, m_iSlider_Hos[0], 0, 100);
	DDX_Slider(pDX, IDC_SLIDER2, m_iSlider_Hos[1]);
	DDV_MinMaxInt(pDX, m_iSlider_Hos[1], 0, 100);
	DDX_Control(pDX, IDC_LIST4, m_ListBox_ViewHos_From);
	DDX_Control(pDX, IDC_LIST5, m_ListBox_SettingHos_From);
	DDX_Text(pDX, IDC_EDIT5, m_Hos_Cap[0]);
	DDX_Text(pDX, IDC_EDIT8, m_Hos_Cap[1]);
	DDX_Control(pDX, IDC_LIST2, m_ListBox_ViewHos_To);
	DDX_Control(pDX, IDC_LIST3, m_ListBox_SettingHos_To_Once);
	DDX_Control(pDX, IDC_LIST6, m_ListBox_SettingHos_To_Multi);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider[0]);
	DDX_Control(pDX, IDC_SLIDER2, m_Slider[1]);
	DDX_Control(pDX, IDC_EDIT5, m_Edit_Slider5);
	DDX_Control(pDX, IDC_EDIT8, m_Edit_Slider8);
}




BEGIN_MESSAGE_MAP(UnitTool_TAB2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UnitTool_TAB2::OnAddTeamButton)
	ON_LBN_SELCHANGE(IDC_LIST4, &UnitTool_TAB2::OnListBox_ViewHos_From)
	ON_LBN_SELCHANGE(IDC_LIST5, &UnitTool_TAB2::OnListBox_SettingHos_From)
	ON_LBN_SELCHANGE(IDC_LIST3, &UnitTool_TAB2::OnListBox_Setting_To_Once)
	ON_LBN_SELCHANGE(IDC_LIST6, &UnitTool_TAB2::OnListBox_Setting_To_Multi)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &UnitTool_TAB2::OnNM_HOS_drawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &UnitTool_TAB2::OnNM_HOS_drawSlider2)
	ON_BN_CLICKED(IDC_BUTTON8, &UnitTool_TAB2::OnApplyButton)
	ON_BN_CLICKED(IDC_BUTTON2, &UnitTool_TAB2::OnResetButton)
	ON_BN_CLICKED(IDC_BUTTON9, &UnitTool_TAB2::OnSaveButton)
	ON_BN_CLICKED(IDC_BUTTON10, &UnitTool_TAB2::OnLoadButton)
END_MESSAGE_MAP()


// UnitTool_TAB2 메시지 처리기



void UnitTool_TAB2::OnAddTeamButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_TeamMainList.empty()) {
		if (L"" == m_str_AddTeam)
		{
			AfxMessageBox(L"공백은 팀 명으로 사용할 수 없습니다.");
			return;
		}
		m_TeamMainList.push_back(m_str_AddTeam);
	}

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
		if (L"" == m_str_AddTeam)
		{
			AfxMessageBox(L"공백은 팀 명으로 사용할 수 없습니다.");
			return;
		}

		m_TeamMainList.push_back(m_str_AddTeam);
	}

	CString Before, Before2;
	pair<CString, CString> KeyValue, NowValue;

	if (m_Hostility_Map.empty()) {
		for (auto& iter = m_TeamMainList.begin(); iter != m_TeamMainList.end(); ++iter)
		{
			for (auto& iter2 = m_TeamMainList.begin(); iter2 != m_TeamMainList.end(); ++iter2)
			{
				if (iter != iter2)
				{
					CString source = *iter;
					CString target = *iter2;
					int hostilityValue = 50;

					//m_inner_Maplist.push_back(pair<CString, CString>(source, target));
					//m_inner_Maplist.insert(pair<CString, CString>(source, target));
					//m_Hostility_Map.emplace(m_inner_Maplist, hostilityValue);

					m_Hostility_Map[*iter][*iter2] = hostilityValue;

					m_inner_Maplist.clear();
				}
			}
		}
	}
	else if (!m_Hostility_Map.empty())
	{
		for (auto iter = m_TeamMainList.begin(); iter != m_TeamMainList.end(); ++iter)
		{
			CString source = *iter;
			CString target = m_str_AddTeam;
			int hostilityValue = 50;

			if (source != m_str_AddTeam)
			{
				//m_inner_Maplist.insert(pair<CString, CString>(source, target));
				//m_inner_Maplist.insert(pair<CString, CString>(target, source));

				m_Hostility_Map[source][target] = hostilityValue;
				m_Hostility_Map[target][source] = hostilityValue;

				m_inner_Maplist.clear();
			}
		}
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

	//multimap<CString, CString> searchKey;
	//for (auto& iter : m_TeamViewToList) {
	//	if (strFindName != iter) {
	//		//list<pair<CString, CString>> searchKey;
	//		//searchKey.push_back(make_pair(strFindName, iter));
	//		searchKey.insert(make_pair(strFindName, iter));
	//	}
	//}

	//const size_t sizem = searchKey.size();

	vector<CString> View;
	int iCount = 0;


	for (auto& iter : m_Hostility_Map[strFindName]) {
		CString strTo = iter.first;
		int Hos = iter.second;
		CString Level, FindStr;
		
		//if (iter.first != searchKey)
		//{

		if (Hos >= 85)							{	Level = L"강한 적대";	}
		else if ((Hos >= 70) && (Hos < 85))		{	Level = L"적대";		}
		else if ((Hos >= 55) && (Hos < 70))		{	Level = L"약한 적대";	}
		else if ((Hos >= 45) && (Hos < 55))		{	Level = L"보통";		}
		else if ((Hos >= 30) && (Hos < 45))		{	Level = L"약한 우호";	}
		else if ((Hos >= 15) && (Hos < 30))		{	Level = L"우호";		}
		else if ((Hos >= 0) && (Hos < 20))		{	Level = L"강한 우호";	}

		View.push_back(strFindName + "->" + strTo + " | " + Level);

		//if (iCount == 0) {
		//	View.push_back(strFindName + "->" + iter2 + " | " + Level);
		//	++iCount;
		//}
		//else if (iCount > 0) {
		//	int NowCount = iCount;
		//	CString sTemp = strFindName + "->" + iter2;
		//	int iFind;

		//	for (size_t i = 0; i < View.size(); ++i)
		//	{
		//		iFind = View[i].Find(L"|");
		//		if (iFind >= 0) {
		//			FindStr = View[i].Left(iFind);
		//		}
		//		if (FindStr == sTemp)
		//		{
		//			View[i] = sTemp + " | " + Level;
		//			++iCount;
		//		}
		//	}
		//	if (FindStr != sTemp)
		//	{
		//		View.push_back(sTemp + " | " + Level);
		//		++iCount;
		//	}
		//}
		//}
	}

	sort(View.begin(), View.end());
	View.erase(unique(View.begin(), View.end()), View.end());

	for (size_t i = 0; i < View.size(); ++i)
	{
		m_ListBox_ViewHos_To.AddString(View[i]);
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




void UnitTool_TAB2::OnListBox_Setting_To_Once()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString		strFromName;
	CString		strFindName;
	int			iFindIndex = 0;
	int			iSelCount = 0;
	int			iStayIndex = 0;
	CString		strStayName;

	UpdateData(TRUE);

	iSelCount = m_ListBox_SettingHos_To_Multi.GetSelCount();
	if (iSelCount > 1) {
		//int*	pIndexs = new int[iSelCount];
		CString* pNames = new CString[iSelCount];

		int FullCount = m_ListBox_SettingHos_To_Multi.GetCount(), NowCount = 0;

		for (int i = 0; i < FullCount; ++i)
		{
			if (m_ListBox_SettingHos_To_Multi.GetSel(i)) 
			{
				m_ListBox_SettingHos_To_Multi.GetText(i, pNames[NowCount]);
				NowCount++;
			}
		}

		m_ListBox_SettingHos_To_Multi.ResetContent();

		for (auto& iter : m_TeamSetToList) {
			m_ListBox_SettingHos_To_Multi.AddString(iter);
		}

		int		iIndex = m_ListBox_SettingHos_To_Once.GetCurSel();
		m_ListBox_SettingHos_To_Once.GetText(iIndex, strFromName);


		for (int i = 0; i < m_ListBox_SettingHos_To_Multi.GetCount(); ++i) {

			m_ListBox_SettingHos_To_Multi.GetText(i, strFindName);

			if (strFromName == strFindName) {
				m_ListBox_SettingHos_To_Multi.DeleteString(i);
			}
		}

		for (int i = 0; i < iSelCount; ++i)
		{
			iFindIndex = m_ListBox_SettingHos_To_Multi.FindStringExact(-1, pNames[i]);
			m_ListBox_SettingHos_To_Multi.SetSel(iFindIndex);
		}
		pNames = nullptr;
		delete[] pNames;
	}



	else if (iSelCount <= 1) {
		iStayIndex = m_ListBox_SettingHos_To_Multi.GetCurSel();

		if (-1 != iStayIndex) {
			m_ListBox_SettingHos_To_Multi.GetText(iStayIndex, strStayName);
		}

		m_ListBox_SettingHos_To_Multi.ResetContent();

		for (auto& iter : m_TeamSetToList) {
			m_ListBox_SettingHos_To_Multi.AddString(iter);
		}

		int		iIndex = m_ListBox_SettingHos_To_Once.GetCurSel();
		m_ListBox_SettingHos_To_Once.GetText(iIndex, strFromName);

		if (-1 != iStayIndex) {

			for (int i = 0; i < m_ListBox_SettingHos_To_Multi.GetCount(); ++i) {

				m_ListBox_SettingHos_To_Multi.GetText(i, strFindName);

				if (strFromName == strFindName) {
					m_ListBox_SettingHos_To_Multi.DeleteString(i);

					iFindIndex = m_ListBox_SettingHos_To_Multi.FindStringExact(-1, strStayName);
					m_ListBox_SettingHos_To_Multi.SetCurSel(iFindIndex);
				}
			}
		}
		else if (-1 == iStayIndex) {

			iFindIndex = m_ListBox_SettingHos_To_Multi.FindStringExact(-1, strFromName);
			m_ListBox_SettingHos_To_Multi.DeleteString(iFindIndex);

		}

	}
	
	UpdateData(FALSE);

}



void UnitTool_TAB2::OnListBox_Setting_To_Multi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString		strFromName;
	CString		strFindName;
	int			iFindIndex = 0;
	int			iSelCount = 0;
	int			iStayIndex = 0;
	CString		strStayName;

	UpdateData(TRUE);

	iStayIndex = m_ListBox_SettingHos_To_Once.GetCurSel();
	if (-1 != iStayIndex) {
		m_ListBox_SettingHos_To_Once.GetText(iStayIndex, strStayName);
	}

	m_ListBox_SettingHos_To_Once.ResetContent();

	for (auto& iter : m_TeamSetToList) {
		m_ListBox_SettingHos_To_Once.AddString(iter);
	}

	iSelCount = m_ListBox_SettingHos_To_Multi.GetSelCount();
	CString* pNames = new CString[iSelCount];
	int		NowCount = 0;

	for (int i = 0; i < m_ListBox_SettingHos_To_Multi.GetCount(); ++i)
	{
		if (m_ListBox_SettingHos_To_Multi.GetSel(i))
		{
			m_ListBox_SettingHos_To_Multi.GetText(i, pNames[NowCount]);
			NowCount++;
		}
	}

	for (int i = 0; i < iSelCount; ++i)
	{
		iFindIndex = m_ListBox_SettingHos_To_Once.FindStringExact(-1, pNames[i]);
		m_ListBox_SettingHos_To_Once.DeleteString(iFindIndex);
	}
	
	iFindIndex = m_ListBox_SettingHos_To_Once.FindStringExact(-1, strStayName);
	m_ListBox_SettingHos_To_Once.SetCurSel(iFindIndex);

	UpdateData(FALSE);

	pNames = nullptr;
	delete[] pNames;
}



BOOL UnitTool_TAB2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	for (int i = 0; i < 2; ++i)
	{
		m_Slider[i].SetTicFreq(10);
		m_Slider[i].SetLineSize(5);
		m_Slider[i].SetPageSize(5);

		m_iSlider_Hos[i] = 50;
		m_Slider[i].SetPos(50);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void UnitTool_TAB2::OnNM_HOS_drawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString szCAP = L"";

	m_iSlider_Hos[0] = m_Slider[0].GetPos();

	if (m_iSlider_Hos[0] >= 85)										{	szCAP = L"강한 적대";	}
	else if ((m_iSlider_Hos[0] >= 70) && (m_iSlider_Hos[0] < 85))	{	szCAP = L"적대";		}
	else if ((m_iSlider_Hos[0] >= 55) && (m_iSlider_Hos[0] < 70))	{	szCAP = L"약한 적대";	}
	else if ((m_iSlider_Hos[0] >= 45) && (m_iSlider_Hos[0] < 55))	{	szCAP = L"보통";		}
	else if ((m_iSlider_Hos[0] >= 30) && (m_iSlider_Hos[0] < 45))	{	szCAP = L"약한 우호";	}
	else if ((m_iSlider_Hos[0] >= 15) && (m_iSlider_Hos[0] < 30))	{	szCAP = L"우호";		}
	else if ((m_iSlider_Hos[0] >= 0) && (m_iSlider_Hos[0] < 20))	{	szCAP = L"강한 우호";	}

	SetDlgItemText(IDC_EDIT5, szCAP);

	*pResult = 0;
}



void UnitTool_TAB2::OnNM_HOS_drawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString szCAP = L"";

	m_iSlider_Hos[1] = m_Slider[1].GetPos();

	if (m_iSlider_Hos[1] >= 85)										{	szCAP = L"강한 적대";	}
	else if ((m_iSlider_Hos[1] >= 70) && (m_iSlider_Hos[1] < 85))	{	szCAP = L"적대";		}
	else if ((m_iSlider_Hos[1] >= 55) && (m_iSlider_Hos[1] < 70))	{	szCAP = L"약한 적대";	}
	else if ((m_iSlider_Hos[1] >= 45) && (m_iSlider_Hos[1] < 55))	{	szCAP = L"보통";		}
	else if ((m_iSlider_Hos[1] >= 30) && (m_iSlider_Hos[1] < 45))	{	szCAP = L"약한 우호";	}
	else if ((m_iSlider_Hos[1] >= 15) && (m_iSlider_Hos[1] < 30))	{	szCAP = L"우호";		}
	else if ((m_iSlider_Hos[1] >= 0) && (m_iSlider_Hos[1] < 20))	{	szCAP = L"강한 우호";	}

	SetDlgItemText(IDC_EDIT8, szCAP);
	*pResult = 0;
}



void UnitTool_TAB2::OnApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strFromName;
	CString strToOnceName;
	vector<CString> vecstrToMultieName;
	int		SelCount = 0;
	int		NowCount = 0;

	if ((LB_ERR == m_ListBox_SettingHos_From.GetCurSel()) ||

		(LB_ERR == m_ListBox_SettingHos_To_Once.GetCurSel() &&
			0 == m_ListBox_SettingHos_To_Multi.GetSelCount())
		)
	{
		AfxMessageBox(L"From 또는 To의 선택 값이 없습니다. 확인하고 다시 시도해주세요.");
	}
	else {
		int iIndex = m_ListBox_SettingHos_From.GetCurSel();
		m_ListBox_SettingHos_From.GetText(iIndex, strFromName);

		if (LB_ERR != m_ListBox_SettingHos_To_Once.GetCurSel())
		{
			int iIndex2 = m_ListBox_SettingHos_To_Once.GetCurSel();
			m_ListBox_SettingHos_To_Once.GetText(iIndex2, strToOnceName);
		}

		SelCount = m_ListBox_SettingHos_To_Multi.GetSelCount();
		vecstrToMultieName.clear();

		if (SelCount >= 1)
		for (int i = 0; i < m_ListBox_SettingHos_To_Multi.GetCount(); ++i)
		{
			if (m_ListBox_SettingHos_To_Multi.GetSel(i))
			{
				CString Temp;
				m_ListBox_SettingHos_To_Multi.GetText(i, Temp);
				vecstrToMultieName.push_back(Temp);
				++NowCount;
			}
		}		

		if (((strFromName != L"") && (strToOnceName != L"")) || 
			((strFromName != L"") && (NowCount != 0)))
		{
			if ((strFromName != L"") && (strToOnceName != L"")) {
				//multimap<CString, CString> searchKey;
				//searchKey.emplace(strFromName, strToOnceName);
				//auto iter = m_Hostility_Map.find(searchKey);
				//iter->second = m_iSlider_Hos[0];
				m_Hostility_Map[strFromName][strToOnceName] = m_iSlider_Hos[0];
			}
			if ((strFromName != L"") && (NowCount != 0))
			{
				//multimap<CString, CString> searchKey2;
				//for (auto& veciter : vecstrToMultieName) {
				//	searchKey2.emplace(strFromName, veciter);
				//}
				//for (auto& searchiter : searchKey2) {
					//if (iter.first == searchKey2) {
					//	iter.second = m_iSlider_Hos[1];
					//}
				//	m_Hostility_Map[searchKey2] = m_iSlider_Hos[1];
				//}

				for (int i = 0; i != vecstrToMultieName.size(); ++i)
				m_Hostility_Map[strFromName][vecstrToMultieName[i]] = m_iSlider_Hos[1];
			}
		}
	//	OnResetButton();
	}

}



void UnitTool_TAB2::OnResetButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_ListBox_ViewHos_From.ResetContent();
	m_ListBox_ViewHos_To.ResetContent();
	m_ListBox_SettingHos_From.ResetContent();
	m_ListBox_SettingHos_To_Once.ResetContent();
	m_ListBox_SettingHos_To_Multi.ResetContent();

	if (!m_TeamMainList.empty())
	{
		for (auto& iter : m_TeamMainList) {
			m_ListBox_ViewHos_From.AddString(iter);
			m_ListBox_SettingHos_From.AddString(iter);
		}
	}

	m_ListBox_ViewHos_From.SetCurSel(-1);
	m_ListBox_SettingHos_From.SetCurSel(-1);

	m_str_AddTeam = L"";

	UpdateData(FALSE);
}





void UnitTool_TAB2::OnSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	wofstream  fout;
	fout.open(L"../Data/TeamAgent.txt", ios::out);

	if (!fout.fail())
	{
		for (auto& iter : m_Hostility_Map)
		{
			for (auto& iter2 : m_Hostility_Map[iter.first])
			{
				CString From = iter.first;
				CString To = iter2.first;

				fout << From.GetString() << L"|" << To.GetString() << L"|" << iter2.second << endl;
			}
		}
		AfxMessageBox(L"Save Complete.");
		fout.close();
	}
}





void UnitTool_TAB2::OnLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	wifstream		fin;
	fin.open(L"../Data/TeamAgent.txt", ios::in);

	if (!fin.fail())
	{
		m_Hostility_Map.clear();
		m_TeamMainList.clear();

		TCHAR From[MAX_STR] = L"";
		TCHAR To[MAX_STR] = L"";
		TCHAR Hos[MAX_STR] = L"";

		while (true)
		{
			fin.getline(From, MAX_STR, '|');
			fin.getline(To, MAX_STR, '|');
			fin.getline(Hos, MAX_STR);

			if (fin.eof())
				break;

			m_Hostility_Map[From][To] = _ttoi(Hos);
		}

		for (auto& iter : m_Hostility_Map)
		{
			m_TeamMainList.push_back(iter.first);
		}

		AfxMessageBox(L"Load Complete.");
	}
	UpdateData(FALSE);
	OnResetButton();
}
