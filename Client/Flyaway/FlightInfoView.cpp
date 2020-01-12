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
}

BEGIN_MESSAGE_MAP(CFlightInfoView, CFormView)
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
