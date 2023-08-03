// LUA_Script.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "LUA_Script.h"
#include "afxdialogex.h"

using namespace std;

// CLUA_Script 대화 상자

IMPLEMENT_DYNAMIC(CLUA_Script, CDialog)

CLUA_Script::CLUA_Script(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CLUA_Script, pParent)
{

}

CLUA_Script::~CLUA_Script()
{
	for (auto iter = m_vecSlider.begin(); iter != m_vecSlider.end();)
	{
		if (iter != m_vecSlider.end())
		{
			Safe_Delete<CSliderCtrl*>(*iter);
			iter = m_vecSlider.erase(iter);
		}
		else
			++iter;
	}
}

void CLUA_Script::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LUA_LIST, m_ListCtrl);
	
}


BEGIN_MESSAGE_MAP(CLUA_Script, CDialog)
	ON_EN_UPDATE(IDC_LUA_EDIT, &CLUA_Script::OnEnUpdateLuaEdit)
	ON_BN_CLICKED(IDC_LUA_SAVE, &CLUA_Script::OnSaveLua)
END_MESSAGE_MAP()


// CLUA_Script 메시지 처리기


BOOL CLUA_Script::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_RichEdit.SubclassDlgItem(IDC_LUA_EDIT, this);

	m_ListCtrl.InsertColumn(0, _T("Slider Column"), LVCFMT_LEFT, 140);
	m_ListCtrl.ShowScrollBar(0);
	m_ListCtrl.SetScrollRange(0, 0, 140 * 10);
	//m_ListCtrl.SetScrollPos

	for (int i = 0; i < 10; ++i)
	{
		AddSlider(i);
	}
	
	return TRUE;
}

void CLUA_Script::AddSlider(int iIndex)
{
	CSliderCtrl* pSlider = new CSliderCtrl();
	pSlider->Create(WS_CHILD | WS_VISIBLE | TBS_HORZ, CRect(0, 0 + 40 * iIndex, 140, 40 + 40 * iIndex), &m_ListCtrl, IDC_LUA_LIST);
	pSlider->SetRange(0, 100);
	pSlider->SetPos(50);
	m_vecSlider.push_back(pSlider);

	m_ListCtrl.SetItemText(iIndex, 0, _T(""));
	m_ListCtrl.SetItemData(iIndex, (DWORD_PTR)pSlider);

	
}

void CLUA_Script::OnEnUpdateLuaEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.
	
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CLUA_Script::OnSaveLua()
{
	wofstream		fout;

	fout.open(L"../Lua/Script/Damage.lua", ios::out);

	if (!fout.fail())		// 개방 성공
	{
		CString strText;
		int iLength = m_RichEdit.GetWindowTextLength();
		m_RichEdit.GetWindowText(strText.GetBufferSetLength(iLength), iLength + 1);
		strText.ReleaseBuffer();

		fout << strText.GetString();

		fout.close();
	}

	WinExec("notepad.exe ../Lua/Script/Damage.lua", SW_SHOW);
}

