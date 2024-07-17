
// TermpView.cpp: CTermpView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Termp.h"
#endif

#include "TermpDoc.h"
#include "TermpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTermpView

IMPLEMENT_DYNCREATE(CTermpView, CFormView)

BEGIN_MESSAGE_MAP(CTermpView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_IMAGE_DISPLAY, &CTermpView::OnBnClickedImageDisplay)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MODE0, &CTermpView::OnBnClickedMode0)
	ON_BN_CLICKED(IDC_MODE1, &CTermpView::OnBnClickedMode1)
	ON_BN_CLICKED(IDC_MODE2, &CTermpView::OnBnClickedMode2)
	ON_BN_CLICKED(IDC_ROTATION, &CTermpView::OnBnClickedRotation)
	ON_BN_CLICKED(IDC_SUPRESOL, &CTermpView::OnBnClickedSupresol)
	ON_BN_CLICKED(IDC_ZOOM, &CTermpView::OnBnClickedZoom)
END_MESSAGE_MAP()

// CTermpView 생성/소멸

CTermpView::CTermpView() noexcept
	: CFormView(IDD_TERMP_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTermpView::~CTermpView()
{
	if (imgCopy) // delete new object
	delete[] imgCopy;
}

void CTermpView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CTermpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CTermpView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CTermpView 인쇄

BOOL CTermpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTermpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTermpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTermpView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CTermpView 진단

#ifdef _DEBUG
void CTermpView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTermpView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTermpDoc* CTermpView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTermpDoc)));
	return (CTermpDoc*)m_pDocument;
}
#endif //_DEBUG


// CTermpView 메시지 처리기


void CTermpView::OnBnClickedImageDisplay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, image display button"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];
	pImg->getImage(imgCopy); // get image data to display
	Invalidate(true); // active WM_PAINT message
}


void CTermpView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
	if (imgCopy) // if image data exists, display the image
	{
		// display image using SetPixel
		unsigned char value;
		for (int i = 0; i < pImg->getHeight(); i++)
			for (int j = 0; j < pImg->getWidth(); j++)
			{
				int ypos = 150 + i;
				int xpos = 200 + j;
				value = imgCopy[i * pImg->getWidth() + j]; // get image pixel value
				dc.SetPixel(xpos, ypos, RGB(value, value, value));
			}
	}
}


void CTermpView::OnBnClickedMode0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, mode 0 start!"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];

	pImg->imageProc(0);

	pImg->getImage(imgCopy); // get image data to display

	Invalidate(true); // active WM_PAINT message
}


void CTermpView::OnBnClickedMode1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, mode 1 start!"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];

	pImg->imageProc(1);

	pImg->getImage(imgCopy); // get image data to display

	Invalidate(true); // active WM_PAINT message
}


void CTermpView::OnBnClickedMode2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, mode 2 start!"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];

	pImg->imageProc(2);

	pImg->getImage(imgCopy); // get image data to display

	Invalidate(true); // active WM_PAINT message
}


void CTermpView::OnBnClickedRotation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, ratation start!"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];

	pImg->imageProc(3);

	pImg->getImage(imgCopy); // get image data to display

	Invalidate(true); // active WM_PAINT message
}


void CTermpView::OnBnClickedSupresol()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, SuperResolution start!"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];

	pImg->imageProc(4);

	pImg->getImage(imgCopy); // get image data to display

	Invalidate(true); // active WM_PAINT message
}


void CTermpView::OnBnClickedZoom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Hi, Zoom start!"));
	CTermpDoc* pDoc = GetDocument();
	pImg = pDoc->getImg();
	imgCopy = new unsigned char[pImg->getHeight() * pImg->getWidth()];

	pImg->imageProc(5);

	pImg->getImage(imgCopy); // get image data to display

	Invalidate(true); // active WM_PAINT message
}
