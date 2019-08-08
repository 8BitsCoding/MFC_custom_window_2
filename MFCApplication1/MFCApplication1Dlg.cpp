
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CRgn rgn;
	rgn.CreateEllipticRgn(0,0,200,200);
	SetWindowRgn(rgn, TRUE);

	SetBackgroundColor(RGB(0, 200, 255));

	SetLayeredWindowAttributes(RGB(255,0,0), 80, LWA_ALPHA | LWA_COLORKEY);
	// 붉은색은 투명하게 해달라

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(RGB(255, 0, 0));
		dc.SelectStockObject(NULL_PEN);
		dc.Ellipse(30, 30, 170, 170);

		CPen grid_pen(PS_DOT, 1, RGB(0, 0, 128));
		CPen * p_old_pen = dc.SelectObject(&grid_pen);
		dc.SetBkColor(TRANSPARENT);
		dc.MoveTo(100, 30);
		dc.LineTo(100, 170);
		dc.MoveTo(30, 100);
		dc.LineTo(170, 100);
		dc.SelectObject(p_old_pen);
		grid_pen.DeleteObject();
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_is_clicked == 0) {
		m_is_clicked = 1;
		GetCursorPos(&m_prev_pos);
		// 화면을 기준으로 내 마우스가 어디있는지 확인
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_is_clicked == 1) {
		CRect r;
		GetWindowRect(r);

		CPoint pos;
		GetCursorPos(&pos);

		SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top + pos.y - m_prev_pos.y, 0, 0, SWP_NOSIZE);
		m_prev_pos = pos;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_is_clicked == 1) {
		m_is_clicked = 0;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
