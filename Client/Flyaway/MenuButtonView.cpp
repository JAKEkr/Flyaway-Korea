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
	DDX_Control(pDX, IDC_HomeButton, m_Button_Home);
	//  DDX_Control(pDX, IDC_FlightInfoButton, m_Button_Flight);
	DDX_Control(pDX, IDC_FlightInfoButton, m_Button_Flight);
	DDX_Control(pDX, IDC_FacilityButton, m_Button_Facility);
	DDX_Control(pDX, IDC_ParkinglotButton, m_Button_Parking);
	//  DDX_Control(pDX, IDC_CloseButton, m_Button_Home);
	DDX_Control(pDX, IDC_CloseButton, m_Button_Close);
}

BEGIN_MESSAGE_MAP(CMenuButtonView, CFormView)
	ON_BN_CLICKED(IDC_HomeButton, &CMenuButtonView::OnBnClickedHomebutton)
	ON_BN_CLICKED(IDC_FlightInfoButton, &CMenuButtonView::OnBnClickedFlightinfobutton)
	ON_BN_CLICKED(IDC_FacilityButton, &CMenuButtonView::OnBnClickedFacilitybutton)
	ON_BN_CLICKED(IDC_ParkinglotButton, &CMenuButtonView::OnBnClickedParkinglotbutton)
	ON_BN_CLICKED(IDC_CloseButton, &CMenuButtonView::OnBnClickedClosebutton)
	ON_WM_CTLCOLOR()
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
	ResizeParentToFit();
	//버튼 폰트를 바꾸기 위한 설정입니다.
    //버튼 색상을 위한 설정입니다.
	m_Button_Home.EnableWindowsTheming(FALSE);
	m_Button_Home.SetFaceColor(RGB(197, 197, 230), true);
	m_Button_Home.SetTextColor(RGB(102, 102, 189)); //텍스트의 색상을 변경합니다

	m_Button_Flight.EnableWindowsTheming(FALSE);
	m_Button_Flight.SetFaceColor(RGB(197, 197, 230), true);
	m_Button_Flight.SetTextColor(RGB(102, 102, 189)); //텍스트의 색상을 변경합니다

	m_Button_Facility.EnableWindowsTheming(FALSE);
	m_Button_Facility.SetFaceColor(RGB(197, 197, 230), true);
	m_Button_Facility.SetTextColor(RGB(102, 102, 189)); //텍스트의 색상을 변경합니다

	m_Button_Parking.EnableWindowsTheming(FALSE);
	m_Button_Parking.SetFaceColor(RGB(197, 197, 230), true);
	m_Button_Parking.SetTextColor(RGB(102, 102, 189)); //텍스트의 색상을 변경합니다

	m_Button_Close.EnableWindowsTheming(FALSE);
	m_Button_Close.SetFaceColor(RGB(197, 197, 230), true);
	m_Button_Close.SetTextColor(RGB(102, 102, 189)); //텍스트의 색상을 변경합니다
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


HBRUSH CMenuButtonView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
