
// IhparkMsgView.cpp: CIhparkMsgView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IhparkMsg.h"
#endif

#include "IhparkMsgDoc.h"
#include "IhparkMsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIhparkMsgView

IMPLEMENT_DYNCREATE(CIhparkMsgView, CView)

BEGIN_MESSAGE_MAP(CIhparkMsgView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDM_GRID5_SIZE, &CIhparkMsgView::OnGrid5Size)
	ON_COMMAND(IDM_GRID7_SIZE, &CIhparkMsgView::OnGrid7Size)
	ON_COMMAND(IDM_GRID9_SIZE, &CIhparkMsgView::OnGrid9Size)
	ON_UPDATE_COMMAND_UI(IDM_GRID5_SIZE, &CIhparkMsgView::OnUpdateGrid5Size)
	ON_UPDATE_COMMAND_UI(IDM_GRID7_SIZE, &CIhparkMsgView::OnUpdateGrid7Size)
	ON_UPDATE_COMMAND_UI(IDM_GRID9_SIZE, &CIhparkMsgView::OnUpdateGrid9Size)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CIhparkMsgView 생성/소멸

CIhparkMsgView::CIhparkMsgView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_BrushColor = RGB(255, 255, 255);
}

CIhparkMsgView::~CIhparkMsgView()
{
}

BOOL CIhparkMsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIhparkMsgView 그리기

void CIhparkMsgView::OnDraw(CDC* pDC)
{
	CIhparkMsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC MemDC, MemDC2;
	MemDC.CreateCompatibleDC(pDC);
	MemDC2.CreateCompatibleDC(pDC);
	CBitmap bitmap, bitmap2;
	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap2.LoadBitmap(IDB_BITMAP2);
	BITMAP bmpinfo;
	BITMAP bmpinfo2;
	bitmap.GetBitmap(&bmpinfo);
	bitmap2.GetBitmap(&bmpinfo2);

	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap);
	CBitmap *pOldBitmap2 = (CBitmap *)MemDC2.SelectObject(&bitmap2);

	CRect rc;
	this->GetClientRect(&rc);
	width = rc.Width();
	height = rc.Height();
	rc.DeflateRect(width, height);

	/*CBrush myBrush(m_BrushColor);
	CBrush *pOldBrush = pDC->SelectObject(&myBrush);*/

	pDC->Rectangle(&rc);
	if (grid == 5) {
		for (int i = 1; i < 5; i++) {

			pDC->MoveTo((width / 5)*i, 0);
			pDC->LineTo((width / 5)*i, height);

			pDC->MoveTo(0, (height / 5)*i);
			pDC->LineTo(width, (height / 5)*i);
		}
		pDC->StretchBlt(m_Pt.x - (width / 10), m_Pt.y - (height / 10), width / 5, height / 5, &MemDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
		switch (bomb) {
		case 0:
			pDC->StretchBlt(m_Pt2.x, m_Pt2.y, width / 5, height / 5, &MemDC2, 0, 0, bmpinfo2.bmWidth, bmpinfo2.bmHeight, SRCCOPY);
			break;
		case 1:
			pDC->StretchBlt(m_Pt2.x + (width / 5), m_Pt2.y, width / 5, height / 5, &MemDC2, 0, 0, bmpinfo2.bmWidth, bmpinfo2.bmHeight, SRCCOPY);
			break;
		}
	}
	else if (grid == 7) {
		for (int i = 1; i < 7; i++) {

			pDC->MoveTo((width / 7)*i, 0);
			pDC->LineTo((width / 7)*i, height);

			pDC->MoveTo(0, (height / 7)*i);
			pDC->LineTo(width, (height / 7)*i);
		}
		pDC->StretchBlt(m_Pt.x - (width / 14), m_Pt.y - (height / 14), width / 7, height / 7, &MemDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}
	else {
		for (int i = 1; i < 9; i++) {

			pDC->MoveTo((width / 9)*i, 0);
			pDC->LineTo((width / 9)*i, height);

			pDC->MoveTo(0, (height / 9)*i);
			pDC->LineTo(width, (height / 9)*i);
		}
		pDC->StretchBlt(m_Pt.x - (width / 18), m_Pt.y - (height / 18), width / 9, height / 9, &MemDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}

	MemDC.SelectObject(pOldBitmap);
	MemDC2.SelectObject(pOldBitmap2);
	bitmap.DeleteObject();
	bitmap2.DeleteObject();

	/*CBrush solidBrush;
	solidBrush.CreateSolidBrush(RGB(0, 0, 255));
	pOldBrush = pDC->SelectObject(&solidBrush);
	pDC->Rectangle(m_Pt.x - (width/10), m_Pt.y - (height/10), m_Pt.x + (width/10), m_Pt.y + (height/10));
	pDC->SelectObject(pOldBrush);
	solidBrush.DeleteObject();
	myBrush.DeleteObject(); 파란색 도형을 키로 이동시키는 코드*/
}



// CIhparkMsgView 인쇄

BOOL CIhparkMsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIhparkMsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIhparkMsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CIhparkMsgView 진단

#ifdef _DEBUG
void CIhparkMsgView::AssertValid() const
{
	CView::AssertValid();
}

void CIhparkMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIhparkMsgDoc* CIhparkMsgView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIhparkMsgDoc)));
	return (CIhparkMsgDoc*)m_pDocument;
}
#endif //_DEBUG


// CIhparkMsgView 메시지 처리기


void CIhparkMsgView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ViewSize = CSize(cx, cy);
	m_Pt = CPoint(cx / 2, cy / 2);
	m_Pt2 = CPoint(0, 0);
}


void CIhparkMsgView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (grid == 5) {
		switch (nChar) {
		case VK_UP:
			m_Pt.y -= height / 5;
			if (m_Pt.y < 0)
				m_Pt.y = m_ViewSize.cy - height / 10;
			break;

		case VK_DOWN:
			m_Pt.y += height / 5;
			if (m_Pt.y > m_ViewSize.cy)
				m_Pt.y = 0 + height / 10;
			break;

		case VK_LEFT:
			m_Pt.x -= width / 5;
			if (m_Pt.x < 0)
				m_Pt.x = m_ViewSize.cx - width / 10;
			break;

		case VK_RIGHT:
			m_Pt.x += width / 5;
			if (m_Pt.x > m_ViewSize.cx)
				m_Pt.x = 0 + width / 10;
			break;
		}
	}
	else if (grid == 7) {
		switch (nChar) {
		case VK_UP:
			m_Pt.y -= height / 7;
			if (m_Pt.y < 0)
				m_Pt.y = m_ViewSize.cy - height / 14;
			break;

		case VK_DOWN:
			m_Pt.y += height / 7;
			if (m_Pt.y > m_ViewSize.cy)
				m_Pt.y = 0 + height / 14;
			break;

		case VK_LEFT:
			m_Pt.x -= width / 7;
			if (m_Pt.x < 0)
				m_Pt.x = m_ViewSize.cx - width / 14;
			break;

		case VK_RIGHT:
			m_Pt.x += width / 7;
			if (m_Pt.x > m_ViewSize.cx)
				m_Pt.x = 0 + width / 14;
			break;
		}
	}
	else {
		switch (nChar) {
		case VK_UP:
			m_Pt.y -= height / 9;
			if (m_Pt.y < 0)
				m_Pt.y = m_ViewSize.cy - height / 18;
			break;

		case VK_DOWN:
			m_Pt.y += height / 9;
			if (m_Pt.y > m_ViewSize.cy)
				m_Pt.y = 0 + height / 18;
			break;

		case VK_LEFT:
			m_Pt.x -= width / 9;
			if (m_Pt.x < 0)
				m_Pt.x = m_ViewSize.cx - width / 18;
			break;

		case VK_RIGHT:
			m_Pt.x += width / 9;
			if (m_Pt.x > m_ViewSize.cx)
				m_Pt.x = 0 + width / 18;
			break;
		}
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CIhparkMsgView::OnGrid5Size()
{
	grid = 5;
	Invalidate();
	m_Pt.x = width / 2;
	m_Pt.y = height / 2;
}


void CIhparkMsgView::OnGrid7Size()
{
	grid = 7;
	Invalidate();
	m_Pt.x = width / 2;
	m_Pt.y = height / 2;
}


void CIhparkMsgView::OnGrid9Size()
{
	grid = 9;
	Invalidate();
	m_Pt.x = width / 2;
	m_Pt.y = height / 2;
}


void CIhparkMsgView::OnUpdateGrid5Size(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(grid == 5);
}


void CIhparkMsgView::OnUpdateGrid7Size(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(grid == 7);
}


void CIhparkMsgView::OnUpdateGrid9Size(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(grid == 9);
}


void CIhparkMsgView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu *subMenu = menu.GetSubMenu(4);
	CMenu *pContextMenu = subMenu->GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}


void CIhparkMsgView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (grid == 5) {
		if (point.x < (width / 5) && point.y < (height / 5)) {
			bomb = 0;
			Invalidate();
		}
		else if ((width / 5) < point.x < (width / 5) * 2 && point.y < (height / 5)) {
			bomb = 1;
			Invalidate();
		}
		else {}
	}
	else {}
		/*
		else if ((width / 5) * 2 < point.x < (width / 5) * 3 && point.y < (height / 5)) {
			bomb = 2;
			Invalidate();
		}
		else if ((width / 5) * 3 < point.x < (width / 5) * 4 && point.y < (height / 5)) {
			bomb = 3;
			Invalidate();
		}
		else if ((width / 5) * 4 < point.x < (width / 5) * 5 && point.y < (height / 5)) {
			bomb = 4;
			Invalidate();
		}
		if (point.x < (width / 5) && (height / 5) < point.y < (height / 5) * 2) {
			bomb = 5;
			Invalidate();
		}
		else if ((width / 5) < point.x < (width / 5) * 2 && (height / 5) < point.y < (height / 5) * 2) {
			bomb = 6;
			Invalidate();
		}
		else if ((width / 5) * 2 < point.x < (width / 5) * 3 && (height / 5) < point.y < (height / 5) * 2) {
			bomb = 7;
			Invalidate();
		}
		else if ((width / 5) * 3 < point.x < (width / 5) * 4 && (height / 5) < point.y < (height / 5) * 2) {
			bomb = 8;
			Invalidate();
		}
		else if ((width / 5) * 4 < point.x < (width / 5) * 5 && (height / 5) < point.y < (height / 5) * 2) {
			bomb = 9;
			Invalidate();
		}
		else {}
	}
	else {}
	*/
	CView::OnLButtonDown(nFlags, point);
}

