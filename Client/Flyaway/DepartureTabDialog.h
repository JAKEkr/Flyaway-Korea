#pragma once


// CDepartureTabDialog 대화 상자

class CDepartureTabDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDepartureTabDialog)

public:
	CDepartureTabDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDepartureTabDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DepartureTabDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_DepartureListView;
protected:
	afx_msg LRESULT OnDataUpdate(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
};
