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
	url.Format(_T("%s%s"), _T(SERVER_HOST), _T("/facility_info/"));
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
	ON_MESSAGE(UM_UPDATE, &CFacilityView::OnDataUpdate)
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

	m_FacilityListView.DeleteAllItems();

	m_FacilityListView.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_FacilityListView.InsertColumn(0, _T("No"), NULL, 50);
	m_FacilityListView.InsertColumn(1, _T("매장명"), NULL, 127);
	m_FacilityListView.InsertColumn(2, _T("위치"), NULL, 350);
	m_FacilityListView.InsertColumn(3, _T("시간"), NULL, 185);
	m_FacilityListView.InsertColumn(4, _T("전화번호"), NULL, 185);

	UpdateData(FALSE);
}


void CFacilityView::OnBnClickedSerchbutton()//검색버튼을 누르면 생기는 이벤트입니다.
{
	UpdateData(TRUE);
	((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(url + m_keyword, m_hWnd);
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

afx_msg LRESULT CFacilityView::OnDataUpdate(WPARAM wParam, LPARAM lParam)
{
	CFlyawayDoc* pDoc = (CFlyawayDoc*)GetDocument();

	m_FacilityListView.DeleteAllItems();

	Json::Value facilities = pDoc->datas;

	for (int row = 0; row < facilities.size(); ++row)
	{	
		CString no, data;
		no.Format(_T("%d"), row + 1);
		m_FacilityListView.InsertItem(row, no);

		Json::Value facility = facilities[row];
		m_FacilityListView.SetItemText(row, 1, (LPCTSTR)CString(facility["facilitynm"].asCString()));
		m_FacilityListView.SetItemText(row, 2, (LPCTSTR)CString(facility["lcnm"].asCString()));
		m_FacilityListView.SetItemText(row, 3, (LPCTSTR)CString(facility["servicetime"].asCString()));
		m_FacilityListView.SetItemText(row, 4, (LPCTSTR)CString(facility["tel"].asCString()));
	}

	return TRUE;
}
