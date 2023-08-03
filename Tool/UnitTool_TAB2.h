#pragma once

#include "afxwin.h"
#include "Include.h"

// UnitTool_TAB2 대화 상자

class UnitTool_TAB2 : public CDialogEx
{
	DECLARE_DYNAMIC(UnitTool_TAB2)

public:
	UnitTool_TAB2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UnitTool_TAB2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	list<CString>& Get_MainList() { return m_TeamMainList; } //유닛 쪽에서 필요
	//리턴할 때 & 안써서 값복사가 일어나 새로 만들어서 넘겨줌...................................
	//직접참조 or 포인터 무방
public:
	CString m_str_AddTeam;

	list<CString>	m_TeamMainList;
	list<CString>	m_TeamViewToList;
	list<CString>	m_TeamSetToList;

	CMap<CString, LPCTSTR, int, int> m_HostilityMap;
	//MainList와 ToList의 조합으로 키값 정하기. 사용 전 값이 있나 확인 필수

	afx_msg void OnAddTeamButton();
	afx_msg void OnListBox_ViewHos_From();
	afx_msg void OnListBox_SettingHos_From();


	CSliderCtrl m_Slider[2];
	int m_iSlider_Hos[2];

	CListBox m_ListBox_ViewHos_From;
	CListBox m_ListBox_ViewHos_To;
	
	CListBox m_ListBox_SettingHos_From;
	CListBox m_ListBox_SettingHos_To_Once;
	CListBox m_ListBox_SettingHos_To_Multi;
	
	CString m_Hos_Cap[2];
	afx_msg void OnListBox_Setting_To_Once();
	afx_msg void OnListBox_Setting_To_Multi();

	virtual BOOL OnInitDialog();
	afx_msg void OnNM_HOS_drawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNM_HOS_drawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_Edit_Slider5;
	CEdit m_Edit_Slider8;
};
