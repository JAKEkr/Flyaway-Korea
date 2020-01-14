// DepartureTabDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "DepartureTabDialog.h"
#include "afxdialogex.h"


// CDepartureTabDialog 대화 상자

IMPLEMENT_DYNAMIC(CDepartureTabDialog, CDialogEx)

CDepartureTabDialog::CDepartureTabDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DepartureTabDialog, pParent)
{

}

CDepartureTabDialog::~CDepartureTabDialog()
{
}

void CDepartureTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DepartureListView, m_DepartureListView);
}


BEGIN_MESSAGE_MAP(CDepartureTabDialog, CDialogEx)
	ON_MESSAGE(UM_UPDATE, &CDepartureTabDialog::OnDataUpdate)
END_MESSAGE_MAP()


// CDepartureTabDialog 메시지 처리기

BOOL CDepartureTabDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_DepartureListView.DeleteAllItems();

	m_DepartureListView.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_DepartureListView.InsertColumn(0, _T("No"), NULL, 50);
	m_DepartureListView.InsertColumn(1, _T("항공사"), NULL, 152);
	m_DepartureListView.InsertColumn(2, _T("편명"), NULL, 125);
	m_DepartureListView.InsertColumn(3, _T("예정시간"), NULL, 80);
	m_DepartureListView.InsertColumn(4, _T("변경시간"), NULL, 80);
	m_DepartureListView.InsertColumn(5, _T("도착지"), NULL, 100);
	m_DepartureListView.InsertColumn(6, _T("탑승구"), NULL, 75);
	m_DepartureListView.InsertColumn(7, _T("현황"), NULL, 75);
	m_DepartureListView.InsertColumn(8, _T("터미널"), NULL, 75);

	return TRUE;
}

afx_msg LRESULT CDepartureTabDialog::OnDataUpdate(WPARAM wParam, LPARAM lParam)
{
	CFlyawayDoc* pDoc = (CFlyawayDoc*)lParam;

	m_DepartureListView.DeleteAllItems();

	Json::Value departures = pDoc->datas;

	for (int row = 0; row < departures.size(); ++row)
	{
		CString no, data;
		no.Format(_T("%d"), row + 1);
		m_DepartureListView.InsertItem(row, no);

		Json::Value departure = departures[row];
		m_DepartureListView.SetItemText(row, 1, (LPCTSTR)CString(departure["airline"].asCString()));
		m_DepartureListView.SetItemText(row, 2, (LPCTSTR)CString(departure["flightId"].asCString()));
		m_DepartureListView.SetItemText(row, 3, (LPCTSTR)CString(departure["scheduleDateTime"].asCString()));
		m_DepartureListView.SetItemText(row, 4, (LPCTSTR)CString(departure["estimatedDateTime"].asCString()));
		m_DepartureListView.SetItemText(row, 5, (LPCTSTR)CString(departure["airport"].asCString()));
		m_DepartureListView.SetItemText(row, 6, (LPCTSTR)CString(departure["gatenumber"].asCString()));
		m_DepartureListView.SetItemText(row, 7, (LPCTSTR)CString(departure["remark"].asCString()));
		m_DepartureListView.SetItemText(row, 8, (LPCTSTR)CString(departure["terminalId"].asCString()));
	}

	return TRUE;
}
