
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "TextureMgr.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView() : m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

#pragma region ����

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����

#pragma endregion ����

void CToolView::OnInitialUpdate()
{
	SetScrollSizes(MM_TEXT, CSize(TILEX * TILECX, TILEY * TILECY / 2));

	// AfxGetMainWnd : ���� ���� �����츦 ��ȯ�ϴ� ���� �Լ�

	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();
	
	RECT	rcWnd{};

	// GetWindowRect : ���� �������� ��Ʈ ������ ���� ����ϴ� �Լ�
	pMainFrm->GetWindowRect(&rcWnd);
	
	// SetRect : ������ �Ű� ������� ��Ʈ ������ ����ϴ� �Լ�
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	// GetClientRect : ���� view â�� ��Ʈ ������ ������ �Լ�
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos : �Ű� ���� ��� ���Ӱ� �������� ��ġ�� ũ�⸦ �����ϴ� �Լ�
	// SetWindowPos(��ġ�� �������� z����, x��ǥ, y��ǥ, ���� ũ��, ���� ũ��, ��ġ�� �������� ũ�� �� ���� ����(���� ������ �����ϰڴٴ� �ɼ�))

	pMainFrm->SetWindowPos(nullptr, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);
	
	CScrollView::OnInitialUpdate();

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Initialize()))
		AfxMessageBox(L"CDevice Initialize FAILED");


	//if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	//	AfxMessageBox(L"CUBE IMG FAILED");


	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->Set_MainView(this);
}

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CDevice::Get_Instance()->Render_Begin();

	m_pTerrain->Render();

	CDevice::Get_Instance()->Render_End();
}

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	Safe_Delete(m_pTerrain);

	CTextureMgr::Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonDown(nFlags, point);

	if (m_bIsDragView)
		return;

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm*		pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitter.GetPane(1, 0));
	CMapTool*		pMapTool = &(pMyForm->m_MapTool);
	
	m_pTerrain->Tile_Change(D3DXVECTOR3(float(point.x) / m_fZoom + (float)GetScrollPos(0),
										float(point.y) / m_fZoom + (float)GetScrollPos(1),
										0.f), pMapTool->m_iDrawID);

	// Invalidate : ȣ�� ��, �������� WM_PAINT�� WM_ERASEBKGND �޼����� �߻���Ŵ
	// FALSE : WM_PAINT �޼����� �߻�
	// TRUE : WM_PAINT, WM_ERASEBKGND �޼����� �� �� �߻�

	Invalidate(FALSE);

	
	CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

	pMiniView->Invalidate(FALSE);


}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnRButtonDown(nFlags, point);

	m_ptStartDrag = point;

	m_bIsDragView = true;
}

BOOL CToolView::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{
	CScrollView::OnMouseWheel(fFlags, zDelta, point);

	if (zDelta > 0)
	{
		m_fZoom = min(m_fZoom * 1.2f, 8.f);
	}
	else if (zDelta < 0)
	{
		m_fZoom = max(m_fZoom * 0.8f, 0.1f);
	}

	if (m_pTerrain)
	{
		m_pTerrain->Set_Size({ m_fZoom, m_fZoom, m_fZoom });
	}

	SetScrollSizes(MM_TEXT, CSize(int((float)m_szOriginal.cx * m_fZoom),
		int((float)m_szOriginal.cy * m_fZoom)));

	Invalidate(FALSE);

	return 0;
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);

	if (m_bIsDragView && GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_ptCurDrag = point;

		// �並 �Ű��ִ� �ڵ�
		SetScrollPos(0,
			min(GetScrollPos(0) + int(float(m_ptStartDrag.x - m_ptCurDrag.x) / m_fZoom), GetScrollLimit(0))
		);
		SetScrollPos(1,
			min(GetScrollPos(1) + int(float(m_ptStartDrag.y - m_ptCurDrag.y) / m_fZoom), GetScrollLimit(1))
		);

		Invalidate(FALSE);

		m_ptStartDrag = point;
	}
	else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitter.GetPane(1, 0));
		CMapTool* pMapTool = &(pMyForm->m_MapTool);

		m_pTerrain->Tile_Change(D3DXVECTOR3(int(float(point.x) / m_fZoom + GetScrollPos(0)),
			int(float(point.y) / m_fZoom + GetScrollPos(1)),
			0.f), pMapTool->m_iDrawID);

		Invalidate(FALSE);


		CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

		pMiniView->Invalidate(FALSE);
	}
}

void CToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CScrollView::OnRButtonUp(nFlags, point);

	m_bIsDragView = false;
}


