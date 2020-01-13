// FacilityView.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "FacilityView.h"


// CFacilityView

IMPLEMENT_DYNCREATE(CFacilityView, CFormView)

CFacilityView::CFacilityView()
	: CFormView(IDD_CFacilityView)
	, m_keyword(_T(""))
{
	url = "http://27.96.135.10:8888/facility_info/";
}

CFacilityView::~CFacilityView()
{
}

void CFacilityView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FacilityList, m_FacilityListView);
	DDX_Text(pDX, IDC_SearchEdit, m_keyword);
}

BEGIN_MESSAGE_MAP(CFacilityView, CFormView)
	ON_BN_CLICKED(IDC_SerchButton, &CFacilityView::OnBnClickedSerchbutton)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFacilityView 진단

#ifdef _DEBUG
void CFacilityView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFacilityView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFacilityView 메시지 처리기


void CFacilityView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_FacilityListView.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_FacilityListView.InsertColumn(0, _T("매장명"), NULL, 200);
	m_FacilityListView.InsertColumn(1, _T("위치"), NULL, 300);
	m_FacilityListView.InsertColumn(2, _T("시간"), NULL, 300);
	m_FacilityListView.InsertColumn(3, _T("전화번호"), NULL, 300);

	m_FacilityListView.SetItemText(0, 1, _T("child of first"));

	UpdateData(FALSE);
}


void CFacilityView::OnBnClickedSerchbutton()//검색버튼을 누르면 생기는 이벤트입니다.
{
	UpdateData(TRUE);
	((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(url + m_keyword);
}


HBRUSH CFacilityView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
