
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	CSplitterWnd m_wndSplitter;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	void SwitchView(CRuntimeClass* view);
protected:
	afx_msg LRESULT OnSwitchView(WPARAM wParam, LPARAM lParam);
};


