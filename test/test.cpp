// test.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "test.h"

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.

BOOL				InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


Window win1;
mybutton b1;
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	
	win1.create(_T("test1"),NULL);
	//mybutton b1;
	b1.create(_T("mybutton"),win1.GetHWND());


	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK Window::staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* pPwindow= (Window*)GetProp(hWnd, _T("wincreate"));
	mybutton* pPmybutton= (mybutton*)GetProp(hWnd, _T("mybutton"));
	
	if(hWnd==win1.GetHWND())
		win1.handleMessage(hWnd, message, wParam, lParam);
	if(hWnd==b1.GetHWND())
		b1.handleMessage(hWnd,message,wParam,lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);

}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



mybutton::mybutton()
{
	hWnd=NULL;
	pWnd=NULL;
}

mybutton::~mybutton()
{
	RemoveProp(hWnd,_T("mybutton"));
}

bool mybutton::create(const LPCWSTR TitleName,HWND pWnd)
{
	WNDCLASS wc;
	DWORD		dwStyle;
	hInstance = GetModuleHandle(NULL);


	wc.style		=	CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	=	(WNDPROC) staticWndProc;
	wc.cbClsExtra	=	0;
	wc.cbWndExtra	=	0;
	wc.hInstance	=	hInstance;
	wc.hIcon		=	LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor		=	LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=	(HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName	=	NULL;
	wc.lpszClassName=	_T("mybutton");

	if(!RegisterClass(&wc))
	{
		MessageBox(NULL,_T("Failed To Register The Window Class."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);		
		return FALSE;
	}
	
	dwStyle=WS_CHILD|WS_VISIBLE;	

	hWnd=CreateWindow(_T("mybutton"),TitleName,dwStyle,50,50,100,30,pWnd,NULL,hInstance,this);

	if(!hWnd)
	{
		MessageBox(NULL,_T("mybutton Creation Error."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	SetProp(hWnd, _T("mybutton"), (HANDLE)this);
	
	return TRUE;
}

LRESULT mybutton::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH MyBrush,OldBrush;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_LBUTTONDOWN:
		hdc=GetDC(hWnd);
		MyBrush=(HBRUSH)GetStockObject(BLACK_BRUSH);
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,0,0,100,30);
		SelectObject(hdc,OldBrush);
		ReleaseDC(hWnd, hdc);
		break;

	case WM_LBUTTONUP:
		hdc=GetDC(hWnd);
		MyBrush=(HBRUSH)GetStockObject(GRAY_BRUSH);
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,0,0,100,30);
		SelectObject(hdc,OldBrush);
		ReleaseDC(hWnd, hdc);
		//MessageBox(hWnd,L"First Button Clicked",L"Button",MB_OK);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyBrush=(HBRUSH)GetStockObject(GRAY_BRUSH);
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,0,0,100,30);
		SelectObject(hdc,OldBrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

Window::Window()
{
	hWnd=NULL;
}

Window::~Window()
{
	RemoveProp(hWnd,_T("wincreate"));
}

bool Window :: create(const LPCWSTR TitleName, HWND pWnd)
{
	WNDCLASS wc;
	DWORD		dwStyle;
	hInstance = GetModuleHandle(NULL);


	wc.style		=	CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	=	(WNDPROC) staticWndProc;
	wc.cbClsExtra	=	0;
	wc.cbWndExtra	=	0;
	wc.hInstance	=	hInstance;
	wc.hIcon		=	LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor		=	LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=	NULL;
	wc.lpszMenuName	=	MAKEINTRESOURCE(IDC_TEST);
	wc.lpszClassName=	_T("wincreate");

	if(!RegisterClass(&wc))
	{
		MessageBox(NULL,_T("Failed To Register The Window Class."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);		
		return FALSE;
	}
	
	dwStyle=WS_OVERLAPPEDWINDOW;	

	hWnd=CreateWindow(_T("wincreate"),TitleName,dwStyle,0,0,500,500,NULL,NULL,hInstance,this);

	if(!hWnd)
	{
		MessageBox(NULL,_T("Window Creation Error."),_T("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

//	SetProp(hWnd, _T("wincreate"), (HANDLE)this);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	return TRUE;
}

LRESULT Window::handleMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND Window::GetHWND()
{
	return hWnd;
}