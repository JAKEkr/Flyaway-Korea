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

}

CParkinglotView::~CParkinglotView()
{
}

void CParkinglotView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SEND, m_combo);
	DDX_Control(pDX, IDC_MAP, m_map);
	DDX_Control(pDX, IDC_LIST_T1, m_listT1);
	DDX_Control(pDX, IDC_LIST_T2, m_listT2);
}

BEGIN_MESSAGE_MAP(CParkinglotView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_SEND, &CParkinglotView::OnComboBoxSelected)
	ON_WM_CTLCOLOR()
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

	image_t1.LoadBitmapA(IDB_BITMAP5);

	h_old_bitmap = m_map->SetBitmap(image_t1);

	if (h_old_bitmap != NULL)::DeleteObject(h_old_bitmap);

	image_t1.Detach();

	m_combo.AddString(_T("제1 여객터미널 주차장 안내"));
	m_combo.AddString(_T("제2 여객터미널 주차장 안내"));

	m_combo.SetCurSel(0);

	GetDlgItem(IDC_LIST_T1)->ShowWindow(TRUE);
	GetDlgItem(IDC_LIST_T2)->ShowWindow(FALSE);
}

void CParkinglotView::OnComboBoxSelected()
{
	CStatic* m_map = (CStatic*)GetDlgItem(IDC_MAP);
	
	int index;

	CBitmap image_t1;
	CBitmap image_t2;

	index = m_combo.GetCurSel();
	
	HBITMAP h_old_bitmap;

	if (index == 0)
	{
		image_t1.LoadBitmapA(IDB_BITMAP5);

		h_old_bitmap = m_map->SetBitmap(image_t1);

		GetDlgItem(IDC_LIST_T2)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_T1)->ShowWindow(TRUE);
		m_listT1.InsertString(-1,_T("1터미널 리스트"));
	}
	else
	{
		image_t2.LoadBitmapA(IDB_BITMAP6);

		h_old_bitmap = m_map->SetBitmap(image_t2);

		GetDlgItem(IDC_LIST_T1)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_T2)->ShowWindow(TRUE);
		m_listT2.InsertString(-1,_T("2터미널 리스트"));
	}

	if (h_old_bitmap != NULL)::DeleteObject(h_old_bitmap);

	image_t1.Detach();
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
