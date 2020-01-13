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
