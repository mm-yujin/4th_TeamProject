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
	
}


BEGIN_MESSAGE_MAP(CLUA_Script, CDialog)
	ON_EN_UPDATE(IDC_LUA_EDIT, &CLUA_Script::OnEnUpdateLuaEdit)
	ON_BN_CLICKED(IDC_LUA_SAVE, &CLUA_Script::OnSaveLua)
	ON_BN_CLICKED(IDC_LUA_SAVE2, &CLUA_Script::OnSaveLua2)
	ON_BN_CLICKED(IDC_LUA_SAVE3, &CLUA_Script::OnSaveLua3)
	ON_BN_CLICKED(IDC_LUA_LOAD, &CLUA_Script::OnLoadLua)
	ON_BN_CLICKED(IDC_LUA_LOAD2, &CLUA_Script::OnLoadLua2)
	ON_BN_CLICKED(IDC_LUA_LOAD3, &CLUA_Script::OnLoadLua3)
END_MESSAGE_MAP()


// CLUA_Script 메시지 처리기


BOOL CLUA_Script::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_RichEdit.SubclassDlgItem(IDC_LUA_EDIT, this);
	m_RichEdit2.SubclassDlgItem(IDC_LUA_EDIT2, this);
	m_RichEdit3.SubclassDlgItem(IDC_LUA_EDIT3, this);

	OnLoadLua();
	OnLoadLua2();
	OnLoadLua3();
	
	return TRUE;
}

void CLUA_Script::AddSlider(int iIndex)
{
	/*CSliderCtrl* pSlider = new CSliderCtrl();
	pSlider->Create(WS_CHILD | WS_VISIBLE | TBS_HORZ, CRect(0, 0 + 40 * iIndex, 140, 40 + 40 * iIndex), &m_ListCtrl, IDC_LUA_LIST);
	pSlider->SetRange(0, 100);
	pSlider->SetPos(50);
	m_vecSlider.push_back(pSlider);

	m_ListCtrl.SetItemText(iIndex, 0, _T(""));
	m_ListCtrl.SetItemData(iIndex, (DWORD_PTR)pSlider);*/

	
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

void CLUA_Script::OnLoadLua()
{
	wifstream		fin;

	fin.open(L"../Lua/Script/Damage.lua", ios::in);

	if (!fin.fail())		// 개방 성공
	{
		CString strText;
		wstringstream buffer;
		wstring line;
		while (getline(fin, line))
		{
			buffer << line << endl;
		}

		strText = buffer.str().c_str();
		m_RichEdit.SetWindowTextW(strText);

		fin.close();
	}
}

void CLUA_Script::OnSaveLua2()
{
	wofstream		fout;

	fout.open(L"../Lua/Script/Defence.lua", ios::out);

	if (!fout.fail())		// 개방 성공
	{
		CString strText;
		int iLength = m_RichEdit2.GetWindowTextLength();
		m_RichEdit2.GetWindowText(strText.GetBufferSetLength(iLength), iLength + 1);
		strText.ReleaseBuffer();

		fout << strText.GetString();

		fout.close();
	}

	WinExec("notepad.exe ../Lua/Script/Defence.lua", SW_SHOW);
}

void CLUA_Script::OnLoadLua2()
{
	wifstream		fin;

	fin.open(L"../Lua/Script/Defence.lua", ios::in);

	if (!fin.fail())		// 개방 성공
	{
		CString strText;
		wstringstream buffer;
		wstring line;
		while (getline(fin, line))
		{
			buffer << line << endl;
		}

		strText = buffer.str().c_str();
		m_RichEdit2.SetWindowTextW(strText);

		fin.close();
	}
}

void CLUA_Script::OnSaveLua3()
{
	wofstream		fout;

	fout.open(L"../Lua/Script/Block.lua", ios::out);

	if (!fout.fail())		// 개방 성공
	{
		CString strText;
		int iLength = m_RichEdit3.GetWindowTextLength();
		m_RichEdit3.GetWindowText(strText.GetBufferSetLength(iLength), iLength + 1);
		strText.ReleaseBuffer();

		fout << strText.GetString();

		fout.close();
	}

	WinExec("notepad.exe ../Lua/Script/Block.lua", SW_SHOW);
}

void CLUA_Script::OnLoadLua3()
{
	wifstream		fin;

	fin.open(L"../Lua/Script/Block.lua", ios::in);

	if (!fin.fail())		// 개방 성공
	{
		CString strText;
		wstringstream buffer;
		wstring line;
		while (getline(fin, line))
		{
			buffer << line << endl;
		}

		strText = buffer.str().c_str();
		m_RichEdit3.SetWindowTextW(strText);

		fin.close();
	}
}
