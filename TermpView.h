#include "imageData.h"
// TermpView.h: CTermpView 클래스의 인터페이스
//

#pragma once


class CTermpView : public CFormView
{
private:
	imageData* pImg = NULL; // for image display
	unsigned char* imgCopy = NULL;

protected: // serialization에서만 만들어집니다.
	CTermpView() noexcept;
	DECLARE_DYNCREATE(CTermpView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TERMP_FORM };
#endif

// 특성입니다.
public:
	CTermpDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTermpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImageDisplay();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMode0();
	afx_msg void OnBnClickedMode1();
	afx_msg void OnBnClickedMode2();
	afx_msg void OnBnClickedRotation();
	afx_msg void OnBnClickedSupresol();
	afx_msg void OnBnClickedZoom();
};

#ifndef _DEBUG  // TermpView.cpp의 디버그 버전
inline CTermpDoc* CTermpView::GetDocument() const
   { return reinterpret_cast<CTermpDoc*>(m_pDocument); }
#endif

