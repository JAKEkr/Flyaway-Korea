// HomeView.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "HomeView.h"


// CHomeView

IMPLEMENT_DYNCREATE(CHomeView, CFormView)

CHomeView::CHomeView()
	: CFormView(IDD_CHomeView)
{

}

CHomeView::~CHomeView()
{
}

void CHomeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHomeView, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHomeView 진단

#ifdef _DEBUG
void CHomeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHomeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHomeView 메시지 처리기


HBRUSH CHomeView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CHomeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 사진을 업로드하는데 필요한 코드입니다.
	bmp.LoadBitmap(IDB_BITMAP4);
	((CStatic*)GetDlgItem(IDC_STATIC_LOGO))->SetBitmap(bmp);
	((CStatic*)GetDlgItem(IDC_STATIC_LOGO))->ModifyStyle(0, WS_CLIPSIBLINGS);
	((CStatic*)GetDlgItem(IDC_STATIC_LOGO))->SetBitmap((HBITMAP)bmp.GetSafeHandle());
}
