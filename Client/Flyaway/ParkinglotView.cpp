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
}

BEGIN_MESSAGE_MAP(CParkinglotView, CFormView)
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
