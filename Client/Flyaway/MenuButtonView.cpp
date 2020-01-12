// MenuButtonView.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "MenuButtonView.h"

#include "HomeView.h"
#include "FlightInfoView.h"
#include "FacilityView.h"
#include "ParkinglotView.h"

// CMenuButtonView

IMPLEMENT_DYNCREATE(CMenuButtonView, CFormView)

CMenuButtonView::CMenuButtonView()
	: CFormView(IDD_MenuButtonView)
{
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
}

CMenuButtonView::~CMenuButtonView()
{
}

void CMenuButtonView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMenuButtonView, CFormView)
	ON_BN_CLICKED(IDC_HomeButton, &CMenuButtonView::OnBnClickedHomebutton)
	ON_BN_CLICKED(IDC_FlightInfoButton, &CMenuButtonView::OnBnClickedFlightinfobutton)
	ON_BN_CLICKED(IDC_FacilityButton, &CMenuButtonView::OnBnClickedFacilitybutton)
	ON_BN_CLICKED(IDC_ParkinglotButton, &CMenuButtonView::OnBnClickedParkinglotbutton)
	ON_BN_CLICKED(IDC_CloseButton, &CMenuButtonView::OnBnClickedClosebutton)
END_MESSAGE_MAP()


// CMenuButtonView 진단

#ifdef _DEBUG
void CMenuButtonView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMenuButtonView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMenuButtonView 메시지 처리기


void CMenuButtonView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CRect rcClient;
	GetClientRect(&rcClient);
	SetScaleToFitSize(rcClient.Size());

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
}

void CMenuButtonView::OnBnClickedHomebutton()
{
	AfxGetMainWnd()->SendMessage(UM_SWITCH, 0, (LPARAM)RUNTIME_CLASS(CHomeView));
}


void CMenuButtonView::OnBnClickedFlightinfobutton()
{
	AfxGetMainWnd()->SendMessage(UM_SWITCH, 0, (LPARAM)RUNTIME_CLASS(CFlightInfoView));
}


void CMenuButtonView::OnBnClickedFacilitybutton()
{
	AfxGetMainWnd()->SendMessage(UM_SWITCH, 0, (LPARAM)RUNTIME_CLASS(CFacilityView));
}


void CMenuButtonView::OnBnClickedParkinglotbutton()
{
	AfxGetMainWnd()->SendMessage(UM_SWITCH, 0, (LPARAM)RUNTIME_CLASS(CParkinglotView));
}


void CMenuButtonView::OnBnClickedClosebutton()
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);
}
