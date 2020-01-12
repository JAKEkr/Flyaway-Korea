// FacilityView.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "FacilityView.h"


// CFacilityView

IMPLEMENT_DYNCREATE(CFacilityView, CFormView)

CFacilityView::CFacilityView()
	: CFormView(IDD_CFacilityView)
{

}

CFacilityView::~CFacilityView()
{
}

void CFacilityView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFacilityView, CFormView)
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
