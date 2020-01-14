#pragma once
#include "DepartureTabDialog.h"
#include "ArrivalTabDialog.h"


// CFlightInfoView 폼 보기

class CFlightInfoView : public CFormView
{
	DECLARE_DYNCREATE(CFlightInfoView)

protected:
	CFlightInfoView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CFlightInfoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFlightInfoView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString departuresUrl;
	CString arrivalsUrl;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CTabCtrl m_mainTab;
	CDepartureTabDialog m_DepartureTab;
	CArrivalTabDialog m_ArrivalTab;
	CWnd* m_pwndShow;
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	afx_msg LRESULT OnDataUpdate(WPARAM wParam, LPARAM lParam);
};


