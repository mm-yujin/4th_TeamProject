// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"


// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
	for_each(m_mapPngImg.begin(), m_mapPngImg.end(), 
		[](auto& MyPair) {

		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_mapPngImg.clear();

}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveData)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnListBox()
{
	UpdateData(TRUE);

	CString		strFindName;

	//GetCurSel : ����Ʈ �ڽ����� ������ ����� �ε����� ��ȯ

	int		iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	// GetText : �ش� �ε����� ���ڿ��� ������ �Լ�
	m_ListBox.GetText(iIndex, strFindName);

	auto		iter = m_mapPngImg.find(strFindName);

	if (iter == m_mapPngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	int i = 0;

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : �Ű� ������ �Ѱܹ��� ���� ���ڰ� ���� ������ �������� ���� ������ �������� �Ǻ��ϴ� �Լ�
		// ���� ������ ���ڶ� �Ǻ��� ��� 0�� �ƴ� ���� ��ȯ

		if (0 != isdigit(strFindName[i]))
			break;
	}
	// Delete(index, count) : �ε��� ��ġ�κ��� ī��Ʈ��ŭ ���ڸ� �����ϴ� �Լ�

	strFindName.Delete(0, i);

	m_iDrawID = _tstoi(strFindName);

	UpdateData(FALSE);

}

void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);
	
	TCHAR	szFilePath[MAX_PATH] = L"";
	TCHAR	szFileName[MAX_STR] = L"";
	
	// DragQueryFile : ��ӵ� ������ ������ ������ �Լ�
	// 0xffffffff(-1)�� �� ��° �Ű� ������ ������ ��� ��ӵ� ������ ������ ��ȯ

	int	iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);

		// PathFindFileName : ��� �� ���� �̸��� ����� �Լ�
		CString	strFileName = PathFindFileName(strRelativePath);

		lstrcpy(szFileName, strFileName.GetString());
		
		//PathRemoveExtension : Ȯ���ڸ� �߶󳻴� �Լ�
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_mapPngImg.find(strFileName);

		if (iter == m_mapPngImg.end())
		{
			CImage* pPndImg = new CImage;

			pPndImg->Load(strRelativePath);

			m_mapPngImg.insert({ strFileName, pPndImg });
			m_ListBox.AddString(strFileName);
		}
	}

	Horizontal_Scroll();

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(FALSE);
}

void CMapTool::Horizontal_Scroll()
{
	CString	strName;
	CSize	Size;

	int	iWidth = 0;

	CDC*	pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// GetTextExtent : ���� ���ڿ��� ���̸� �ȼ� ������ ��ȯ
		Size = pDC->GetTextExtent(strName);

		if (Size.cx > iWidth)
			iWidth = Size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : ����Ʈ �ڽ��� ���η� ��ũ�� �� �� �ִ� �ִ� ������ ������ �Լ�
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);

}


void CMapTool::OnSaveData()
{
	CFileDialog	Dlg(FALSE, // TRUE(����), FALSE(�ٸ� �̸����� ����) ��� ����
		L"dat", // default Ȯ���ڸ�
		L"*.dat",  // ��ȭ ���ڿ� ǥ���� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б� ���� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ� ���� �� ��� �޼��� ���)
		L"Data File(*.dat) | *.dat||", // "�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ�"
		this);	// �θ� ������ �ּ�

	TCHAR		szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : ���õ� ��θ� ��ȯ
		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*		pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
		CTerrain*		pTerrain = pMainView->m_pTerrain;

		vector< TILE*>&		vecTile = pTerrain->Get_VecTile();

		if (vecTile.empty())
			return;

		for (auto& iter : vecTile)
			WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);


		CloseHandle(hFile);

	}
}
