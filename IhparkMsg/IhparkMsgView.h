
// IhparkMsgView.h: CIhparkMsgView 클래스의 인터페이스
//

#pragma once


class CIhparkMsgView : public CView
{
public:
	COLORREF m_BrushColor;
	int width, height;
	CSize m_ViewSize;
	CPoint m_Pt;
	CPoint m_Pt2;
	int grid = 5;
	int grid2;
	int bomb;
protected: // serialization에서만 만들어집니다.
	CIhparkMsgView() noexcept;
	DECLARE_DYNCREATE(CIhparkMsgView)

// 특성입니다.
public:
	CIhparkMsgDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CIhparkMsgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGrid5Size();
	afx_msg void OnGrid7Size();
	afx_msg void OnGrid9Size();
	afx_msg void OnUpdateGrid5Size(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGrid7Size(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGrid9Size(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // IhparkMsgView.cpp의 디버그 버전
inline CIhparkMsgDoc* CIhparkMsgView::GetDocument() const
   { return reinterpret_cast<CIhparkMsgDoc*>(m_pDocument); }
#endif

