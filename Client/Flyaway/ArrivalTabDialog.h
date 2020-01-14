#pragma once


// CArrivalTabDialog 대화 상자

class CArrivalTabDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CArrivalTabDialog)

public:
	CArrivalTabDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CArrivalTabDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ArrivalTabDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ArrivalListView;
protected:
	afx_msg LRESULT OnDataUpdate(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
};
