// PathFind.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "PathFind.h"
#include "afxdialogex.h"
#include "FileInfo.h"


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
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFind, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CPathFind::OnSaveData)
	ON_BN_CLICKED(IDC_BUTTON2, &CPathFind::OnLoadData)
	ON_LBN_SELCHANGE(IDC_LIST1, &CPathFind::OnListBox)
END_MESSAGE_MAP()


// CPathFind 메시지 처리기
void CPathFind::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CPathFind::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	wofstream		fout;
	fout.open(L"../Data/ImgPath.txt", ios::out);
	if (!fout.fail())		// 개방 성공
	{
		for (auto& iter : m_PathList)
		{
			fout << iter->wstrObjKey << L"|" << iter->wstrStateKey << L"|" << iter->iCount << L"|" << iter->wstrPath << endl;
		}
		fout.close();
	}
	WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
}


void CPathFind::OnLoadData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	wifstream		fin;
	fin.open(L"../Data/ImgPath.txt", ios::in);

	if (!fin.fail())
	{
		TCHAR	szObjKey[MAX_STR] = L"";
		TCHAR	szStateKey[MAX_STR] = L"";
		TCHAR	szCount[MAX_STR] = L"";
		TCHAR	szPath[MAX_PATH] = L"";

		wstring		wstrCombined = L"";

		m_ListBox.ResetContent();

		while (true)
		{
			fin.getline(szObjKey, MAX_STR, '|');
			fin.getline(szStateKey, MAX_STR, '|');
			fin.getline(szCount, MAX_STR, '|');
			fin.getline(szPath, MAX_PATH);

			if (fin.eof())
				break;

			wstrCombined = wstring(szObjKey) + L"|" + szStateKey + L"|" + szCount + L"|" + szPath;

			m_ListBox.AddString(wstrCombined.c_str());
		}
		fin.close();
	}

	WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
	UpdateData(FALSE);
}

void CPathFind::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	TCHAR	szFilePath[MAX_PATH] = L"";

	int	iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		CFileInfo::DirInfoExtration(szFilePath, m_PathList);
	}

	m_ListBox.ResetContent();

	wstring		wstrCombined = L"";
	TCHAR		szBuf[MIN_STR] = L"";

	for (auto& iter : m_PathList)
	{
		// _itow_s : 정수를 wstr로 변환,  10진수로 변환하겠다는 의미
		_itow_s(iter->iCount, szBuf, 10);

		wstrCombined = iter->wstrObjKey + L"|" + iter->wstrStateKey + L"|" + szBuf + L"|" + iter->wstrPath;

		m_ListBox.AddString(wstrCombined.c_str());
	}
	UpdateData(FALSE);
}