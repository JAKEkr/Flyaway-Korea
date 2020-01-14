
// FlyawayDoc.cpp: CFlyawayDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Flyaway.h"
#endif

#include "FlyawayDoc.h"
#include "afxinet.h"
#include "MainFrm.h"

#include <propkey.h>

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFlyawayDoc

IMPLEMENT_DYNCREATE(CFlyawayDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlyawayDoc, CDocument)
END_MESSAGE_MAP()


// CFlyawayDoc 생성/소멸

CFlyawayDoc::CFlyawayDoc() noexcept
{
    datas = NULL;
}

CFlyawayDoc::~CFlyawayDoc()
{
}

BOOL CFlyawayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CFlyawayDoc serialization

void CFlyawayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CFlyawayDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CFlyawayDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFlyawayDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFlyawayDoc 진단

#ifdef _DEBUG
void CFlyawayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlyawayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFlyawayDoc 명령
BOOL CFlyawayDoc::updateData(CString url, HWND hWnd)
{
    CString res = requestGET(url);

    Json::Reader reader;
    Json::Value root;

    bool parsingRet = reader.parse(std::string((CStringA)res), root);

    if (!root["success"].asString()._Equal("true"))
        return FALSE;

    Json::Value type = root["type"];
    datas = root[type.asString()];

    SendMessage(hWnd, UM_UPDATE, NULL, NULL);
    //SendMessage(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveView()->m_hWnd, UM_UPDATE, NULL, NULL);

    return TRUE;
}

CString CFlyawayDoc::requestGET(CString url)
{
    //http 세션 / 커넥션
    CInternetSession* pSession = NULL;
    CHttpConnection* pHttpConnect = NULL;
    CHttpFile* pHttpFile = NULL;

    // url파싱 변수
    CString strServerName, strObject;
    INTERNET_PORT nPort;
    DWORD dwServiceType = 0;
    DWORD m_dwStatusCode = 0;

    // url파싱
    AfxParseURL(url, dwServiceType, strServerName, strObject, nPort);

    // http연결요청
    pSession = new CInternetSession;
    pHttpConnect = pSession->GetHttpConnection(strServerName, nPort);

    pHttpFile = pHttpConnect->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);

    // 데이터 전송
    pHttpFile->SendRequest();

    pHttpFile->QueryInfoStatusCode(m_dwStatusCode);

    CString szHeaders;
    pHttpFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, szHeaders);

    BOOL bUTF8mode = szHeaders.Find(_T("charset=UTF-8")) >= 0 ||
        szHeaders.Find(_T("charset=utf-8")) >= 0 ||
        szHeaders.Find(_T("CHARSET=UTF-8")) >= 0 ||
        szHeaders.Find(_T("CHARSET=utf-8")) >= 0;

    CString strCompleteString;
    if (m_dwStatusCode == 200)
    {
        CString strResult;
        while (pHttpFile->ReadString(strResult))
        {
            if (bUTF8mode)
                strCompleteString += CW2T(CA2W((char*)strResult.GetBuffer(), CP_UTF8));
            else
                strCompleteString += CW2T(CA2W((char*)strResult.GetBuffer()));

            strResult.ReleaseBuffer();
        }
    }

    // 세션해제
    if (pHttpFile)
    {
        delete pHttpFile;
        pHttpFile = NULL;
    }
    if (pHttpConnect)
    {
        pHttpConnect->Close();
        delete pHttpConnect;
        pHttpConnect = NULL;
    }
    if (pSession)
    {
        pSession->Close();
        delete pSession;
        pSession = NULL;
    }

    return strCompleteString;
}