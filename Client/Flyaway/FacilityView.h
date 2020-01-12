#pragma once



// CFacilityView 폼 보기

class CFacilityView : public CFormView
{
	DECLARE_DYNCREATE(CFacilityView)

protected:
	CFacilityView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CFacilityView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFacilityView };
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
	CString url;

	CListCtrl m_FacilityListView;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSerchbutton();
	CString m_keyword;
};


