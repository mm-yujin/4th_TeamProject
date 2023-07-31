// MiniView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MiniView.h"
#include "Device.h"
#include "MainFrm.h"
#include "ToolView.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	// AfxGetMainWnd : 현재 쓰레드로부터 Wnd를 반환, 현재 쓰레드가 메인 쓰레드일 경우 AfxGetMainWnd를 반환
	//	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// AfxGetApp : 메인 쓰레드를 갖고 있는 현재 메인 app을 반환
	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	//GetPane(행, 열) : 해당하는 창의 정보를 얻어오는 함수 
	CToolView*		pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	//GetParentFrame : 현재 View를 둘러 싸고 있는 FrameWnd를 반환
	//CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(GetParentFrame());

	CTerrain*		pTerrain = pMainView->m_pTerrain;


	CDevice::Get_Instance()->Render_Begin();

	pTerrain->Mini_Render();

	CDevice::Get_Instance()->Render_End(m_hWnd);
}


// CMiniView 진단입니다.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기입니다.
