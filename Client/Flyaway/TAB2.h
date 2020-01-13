#pragma once


// CTAB2 대화 상자

class CTAB2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTAB2)

public:
	CTAB2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTAB2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB2_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
