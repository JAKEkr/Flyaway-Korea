// FlightInfoView.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "FlightInfoView.h"


// CFlightInfoView

IMPLEMENT_DYNCREATE(CFlightInfoView, CFormView)

CFlightInfoView::CFlightInfoView()
	: CFormView(IDD_CFlightInfoView)
{
	departuresUrl.Format(_T("%s%s"), _T(SERVER_HOST), _T("/schedule/departures"));
	arrivalsUrl.Format(_T("%s%s"), _T(SERVER_HOST), _T("/schedule/arrivals"));
}

CFlightInfoView::~CFlightInfoView()
{
}

void CFlightInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TabView, m_mainTab);
}

BEGIN_MESSAGE_MAP(CFlightInfoView, CFormView)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TabView, &CFlightInfoView::OnTcnSelchangeTab)
	ON_MESSAGE(UM_UPDATE, &CFlightInfoView::OnDataUpdate)
END_MESSAGE_MAP()


// CFlightInfoView 진단

#ifdef _DEBUG
void CFlightInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFlightInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


HBRUSH CFlightInfoView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) {
	case CTLCOLOR_DLG:   /// 다이얼로그 배경색을 white로.
	{
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
		break;
	}
	case CTLCOLOR_BTN:    // 버튼의 배경색을 투명으로...
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	case CTLCOLOR_STATIC:
	{
		pDC->SetTextColor(RGB(0, 255, 255));  // static text 글자색 변경
		pDC->SetBkMode(TRANSPARENT);   // static text 배경색 투명
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	}

	return hbr;
}


void CFlightInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	this->m_mainTab.InsertItem(0, _T("가는편"), 0);
	this->m_mainTab.InsertItem(1, _T("오는편"), 0);

	CRect rect;
	this->m_mainTab.GetClientRect(&rect);
	this->m_DepartureTab.Create(IDD_DepartureTabDialog, &this->m_mainTab);
	this->m_DepartureTab.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

	this->m_ArrivalTab.Create(IDD_ArrivalTabDialog, &this->m_mainTab);
	this->m_ArrivalTab.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW);

	this->m_pwndShow = &this->m_DepartureTab;

	((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(departuresUrl, m_hWnd);
}


void CFlightInfoView::OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (this->m_pwndShow != NULL)
	{
		this->m_pwndShow->ShowWindow(SW_HIDE);
		this->m_pwndShow = NULL;
	}

	int tabIndex = this->m_mainTab.GetCurSel();

	switch (tabIndex)
	{
	case 0:
		this->m_DepartureTab.ShowWindow(SW_SHOW);
		this->m_pwndShow = &this->m_DepartureTab;
		((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(departuresUrl, m_hWnd);
		break;
	case 1:
		this->m_ArrivalTab.ShowWindow(SW_SHOW);
		this->m_pwndShow = &this->m_ArrivalTab;
		((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(arrivalsUrl, m_hWnd);
		break;
	}
}


afx_msg LRESULT CFlightInfoView::OnDataUpdate(WPARAM wParam, LPARAM lParam)
{
	m_pwndShow->SendMessage(UM_UPDATE, NULL, (LPARAM)GetDocument());
	return TRUE;
}
