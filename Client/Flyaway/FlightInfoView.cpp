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

}

CFlightInfoView::~CFlightInfoView()
{
}

void CFlightInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_mainTab);
}

BEGIN_MESSAGE_MAP(CFlightInfoView, CFormView)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFlightInfoView::OnTcnSelchangeTab1)
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


// CFlightInfoView 메시지 처리기


HBRUSH CFlightInfoView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
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
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CFlightInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strTab = _T("");
	strTab.Format(_T("가는편"));
	this->m_mainTab.InsertItem(0, strTab, 0);
	strTab.Format(_T("오는편"));
	this->m_mainTab.InsertItem(1, strTab, 0);

	CRect rect;
	this->m_mainTab.GetClientRect(&rect);
	this->m_tab1.Create(IDD_TAB1_DIALOG, &this->m_mainTab);
	this->m_tab1.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

	this->m_tab2.Create(IDD_TAB2_DIALOG, &this->m_mainTab);
	this->m_tab2.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW);

	this->m_pwndShow = &this->m_tab1;
}


void CFlightInfoView::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (this->m_pwndShow != NULL)
	{
		this->m_pwndShow->ShowWindow(SW_HIDE);
		this->m_pwndShow = NULL;
	}

	int tabIndex = this->m_mainTab.GetCurSel();

	switch (tabIndex)
	{
	case 0:
		this->m_tab1.ShowWindow(SW_SHOW);
		this->m_pwndShow = &this->m_tab1;
		break;
	case 1:
		this->m_tab2.ShowWindow(SW_SHOW);
		this->m_pwndShow = &this->m_tab2;
		break;
	}
	*pResult = 0;
}
