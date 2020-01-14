// ParkinglotView.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "ParkinglotView.h"


// CParkinglotView

IMPLEMENT_DYNCREATE(CParkinglotView, CFormView)

CParkinglotView::CParkinglotView()
	: CFormView(IDD_CParkinglotView)
{
	url.Format(_T("%s%s"), _T(SERVER_HOST), _T("/parkinglot/"));
}

CParkinglotView::~CParkinglotView()
{
}

void CParkinglotView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SEND, m_Combo);
	DDX_Control(pDX, IDC_ParkinglotView, m_ParkinglotListView);
}

BEGIN_MESSAGE_MAP(CParkinglotView, CFormView)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_SEND, &CParkinglotView::OnCbnSelchangeComboSend)
	ON_MESSAGE(UM_UPDATE, &CParkinglotView::OnDataUpdate)
END_MESSAGE_MAP()


// CParkinglotView 진단

#ifdef _DEBUG
void CParkinglotView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CParkinglotView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CParkinglotView 메시지 처리기


void CParkinglotView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CStatic* m_map = (CStatic*)GetDlgItem(IDC_MAP);

	CBitmap image_t1;

	HBITMAP h_old_bitmap;

	image_t1.LoadBitmapW(IDB_BITMAP5);

	h_old_bitmap = m_map->SetBitmap(image_t1);

	if (h_old_bitmap != NULL)::DeleteObject(h_old_bitmap);

	image_t1.Detach();

	m_Combo.AddString(_T("제1 여객터미널 주차장 안내"));
	m_Combo.AddString(_T("제2 여객터미널 주차장 안내"));

	m_Combo.SetCurSel(0);

	m_ParkinglotListView.DeleteAllItems();
	m_ParkinglotListView.InsertColumn(0, _T("No"), NULL, 50);
	m_ParkinglotListView.InsertColumn(1, _T("구분"), NULL, 248);
	m_ParkinglotListView.InsertColumn(2, _T("주차 가능 수"), NULL, 290);
	m_ParkinglotListView.InsertColumn(3, _T("총 주차 구역"), NULL, 290);

	((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(url + _T("T1"), m_hWnd);
}


HBRUSH CParkinglotView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CParkinglotView::OnCbnSelchangeComboSend()
{
	CStatic* m_map = (CStatic*)GetDlgItem(IDC_MAP);

	CBitmap image_t1;
	CBitmap image_t2;

	int index = m_Combo.GetCurSel();

	HBITMAP h_old_bitmap;

	if (index == 0)
	{
		image_t1.LoadBitmapW(IDB_BITMAP5);
		h_old_bitmap = m_map->SetBitmap(image_t1);

		((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(url + _T("T1"), m_hWnd);

	}
	else
	{
		image_t2.LoadBitmapW(IDB_BITMAP6);
		h_old_bitmap = m_map->SetBitmap(image_t2);

		((CFlyawayApp*)AfxGetApp())->m_pDoc->updateData(url + _T("T2"), m_hWnd);
	}

	if (h_old_bitmap != NULL)::DeleteObject(h_old_bitmap);

	image_t1.Detach();
}


afx_msg LRESULT CParkinglotView::OnDataUpdate(WPARAM wParam, LPARAM lParam)
{
	CFlyawayDoc* pDoc = (CFlyawayDoc*)GetDocument();

	m_ParkinglotListView.DeleteAllItems();

	Json::Value parkinglots = pDoc->datas;

	for (int row = 0; row < parkinglots.size(); ++row)
	{
		CString no, data;
		no.Format(_T("%d"), row + 1);
		m_ParkinglotListView.InsertItem(row, no);

		Json::Value parkinglot = parkinglots[row];
		m_ParkinglotListView.SetItemText(row, 1, (LPCTSTR)CString(parkinglot["floor"].asCString()));
		m_ParkinglotListView.SetItemText(row, 2, (LPCTSTR)CString(parkinglot["parking"].asCString()));
		m_ParkinglotListView.SetItemText(row, 3, (LPCTSTR)CString(parkinglot["parkingarea"].asCString()));
	}

	return TRUE;
}
