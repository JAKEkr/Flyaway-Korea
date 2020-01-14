// ArrivalTabDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "ArrivalTabDialog.h"
#include "afxdialogex.h"


// CArrivalTabDialog 대화 상자

IMPLEMENT_DYNAMIC(CArrivalTabDialog, CDialogEx)

CArrivalTabDialog::CArrivalTabDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ArrivalTabDialog, pParent)
{
}

CArrivalTabDialog::~CArrivalTabDialog()
{
}

void CArrivalTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ArrivalListView, m_ArrivalListView);
}


BEGIN_MESSAGE_MAP(CArrivalTabDialog, CDialogEx)
	ON_MESSAGE(UM_UPDATE, &CArrivalTabDialog::OnDataUpdate)
END_MESSAGE_MAP()


// CArrivalTabDialog 메시지 처리기

BOOL CArrivalTabDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ArrivalListView.DeleteAllItems();

	m_ArrivalListView.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ArrivalListView.InsertColumn(0, _T("No"), NULL, 50);
	m_ArrivalListView.InsertColumn(1, _T("항공사"), NULL, 152);
	m_ArrivalListView.InsertColumn(2, _T("편명"), NULL, 125);
	m_ArrivalListView.InsertColumn(3, _T("예정시간"), NULL, 80);
	m_ArrivalListView.InsertColumn(4, _T("변경시간"), NULL, 80);
	m_ArrivalListView.InsertColumn(5, _T("출발지"), NULL, 100);
	m_ArrivalListView.InsertColumn(6, _T("출구"), NULL, 75);
	m_ArrivalListView.InsertColumn(7, _T("현황"), NULL, 75);
	m_ArrivalListView.InsertColumn(8, _T("터미널"), NULL, 75);

	return TRUE;
}

afx_msg LRESULT CArrivalTabDialog::OnDataUpdate(WPARAM wParam, LPARAM lParam)
{
	CFlyawayDoc* pDoc = (CFlyawayDoc*)lParam;

	m_ArrivalListView.DeleteAllItems();

	Json::Value arrivals = pDoc->datas;

	for (int row = 0; row < arrivals.size(); ++row)
	{
		CString no, data;
		no.Format(_T("%d"), row + 1);
		m_ArrivalListView.InsertItem(row, no);

		Json::Value arrival = arrivals[row];
		m_ArrivalListView.SetItemText(row, 1, (LPCTSTR)CString(arrival["airline"].asCString()));
		m_ArrivalListView.SetItemText(row, 2, (LPCTSTR)CString(arrival["flightId"].asCString()));
		m_ArrivalListView.SetItemText(row, 3, (LPCTSTR)CString(arrival["scheduleDateTime"].asCString()));
		m_ArrivalListView.SetItemText(row, 4, (LPCTSTR)CString(arrival["estimatedDateTime"].asCString()));
		m_ArrivalListView.SetItemText(row, 5, (LPCTSTR)CString(arrival["airport"].asCString()));
		m_ArrivalListView.SetItemText(row, 6, (LPCTSTR)CString(arrival["exitnumber"].asCString()));
		m_ArrivalListView.SetItemText(row, 7, (LPCTSTR)CString(arrival["remark"].asCString()));
		m_ArrivalListView.SetItemText(row, 8, (LPCTSTR)CString(arrival["terminalId"].asCString()));
	}

	return TRUE;
}