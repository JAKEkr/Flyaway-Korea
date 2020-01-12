
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Flyaway.h"

#include "MainFrm.h"

#include "MenuButtonView.h"
#include "HomeView.h"
#include "FlightInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_MESSAGE(UM_SWITCH, &CMainFrame::OnSwitchView)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	if (cs.hMenu != NULL) {   // 메뉴 없애기
		::DestroyMenu(cs.hMenu);      // delete menu if loaded
		cs.hMenu = NULL;              // no menu for this window
	}

	cs.lpszName = _T("FlyAway"); //메인 프레임 이름 지정
	cs.style &= ~FWS_ADDTOTITLE; //메인 프레임 이름 지정

	cs.cx = 1600; //메인 프레임 가로 크기입니다.
	cs.cy = 1000;  //메인 프레임 세로 크기입니다.

	return TRUE;
	/*
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;

	return TRUE;
	*/
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect cr;

	if (!m_wndSplitter.CreateStatic(this, 2, 1)) {
		TRACE0("Failed to create split bar ");
		return FALSE;
	}

	GetClientRect(&cr);
	CSize upperViewSize(cr.Width(), cr.Height() / 4);
	CSize lowerViewSize(cr.Width(), 3 * cr.Height() / 4);

	((CFlyawayApp*)AfxGetApp())->m_pDoc = (CFlyawayDoc*)(pContext->m_pCurrentDoc);

	pContext->m_pCurrentFrame = this;
	BOOL rc = m_wndSplitter.CreateView(1, 0, pContext->m_pNewViewClass, lowerViewSize, pContext);
	if (!rc)
		return FALSE;

	pContext->m_pNewViewClass = RUNTIME_CLASS(CMenuButtonView);
	pContext->m_pCurrentDoc = ((CFlyawayApp*)AfxGetApp())->m_pDoc;
	pContext->m_pCurrentFrame = this;
	rc = m_wndSplitter.CreateView(0, 0, pContext->m_pNewViewClass, upperViewSize, pContext);

	m_wndSplitter.RecalcLayout();
	m_wndSplitter.SetActivePane(1, 0);

	return rc;
}

afx_msg LRESULT CMainFrame::OnSwitchView(WPARAM wParam, LPARAM lParam)
{
	CRect cr;
	GetClientRect(&cr);
	CSize lowerViewSize(cr.Width(), 3 * cr.Height() / 4);

	CCreateContext Context;
	Context.m_pNewViewClass = (CRuntimeClass*)lParam;
	Context.m_pCurrentDoc = ((CFlyawayApp*)AfxGetApp())->m_pDoc;
	Context.m_pCurrentFrame = this;
	Context.m_pNewDocTemplate = Context.m_pCurrentDoc->GetDocTemplate();
	Context.m_pLastView = (CView*)m_wndSplitter.GetPane(1, 0);

	m_wndSplitter.DeleteView(1, 0);
	m_wndSplitter.CreateView(1, 0, Context.m_pNewViewClass, lowerViewSize, &Context);
	CView* pView = (CView*)m_wndSplitter.GetPane(1, 0);
	pView->GetParentFrame()->RecalcLayout();
	m_wndSplitter.RecalcLayout();
	pView->OnInitialUpdate();
	m_wndSplitter.SetActivePane(1, 0);

	return TRUE;
}
