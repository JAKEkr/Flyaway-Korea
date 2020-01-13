// TAB1.cpp: 구현 파일
//

#include "pch.h"
#include "Flyaway.h"
#include "TAB1.h"
#include "afxdialogex.h"


// CTAB1 대화 상자

IMPLEMENT_DYNAMIC(CTAB1, CDialogEx)

CTAB1::CTAB1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB1_DIALOG, pParent)
{

}

CTAB1::~CTAB1()
{
}

void CTAB1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTAB1, CDialogEx)
END_MESSAGE_MAP()


// CTAB1 메시지 처리기
