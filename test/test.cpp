// test.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "test.h"

#define MAX_LOADSTRING 100

// ���� ����:
HWND hWndp;
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcb(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;

	Window win(L"window",L"TINNOS",WS_OVERLAPPEDWINDOW,0, 0, 500, 500, NULL, NULL, hInstance, NULL);
	win.init();
	win.creat();
	ShowWindow(win.GetHandle(), nCmdShow);
	UpdateWindow(win.GetHandle());

	myButton button(L"mybutton",L"button",WS_CHILD|WS_VISIBLE,50,50,100,30, win.GetHandle(), NULL, hInst, NULL);
	button.init();
	button.creat();
	
	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case WM_LBUTTONUP:
		//hdc=GetDC(hWnd);
		//ReleaseDC(hWnd, hdc);
		MessageBox(hWnd,L"First Button Clicked",L"Button",MB_OK);
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
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



LRESULT CALLBACK WndProcb(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		// �޴� ������ ���� �м��մϴ�.
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




// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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



Window::Window(const LPCWSTR ClassNmae, const LPCWSTR TitleName,DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	this->ClassNmae=ClassNmae;
	this->TitleName=TitleName;
	this->dwStyle=dwStyle;
	this->x=x;
	this->y=y;
	this->nWidth=nWidth;
	this->nHeight=nHeight;
	this->hWndParent=hWndParent;
	this->hMenu=hMenu;
	this->hInstance=hInstance;
	this->lpParam=lpParam;

}

ATOM Window::init()
{
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= ClassNmae;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

bool Window::creat()
{
	
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
	hWnd = CreateWindow(ClassNmae, TitleName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	
	if (!hWnd)
	{
		return FALSE;
	}

   return TRUE;
}

HWND Window:: GetHandle()
{
	return hWnd;
}

myButton::myButton(const LPCWSTR ClassNmae, const LPCWSTR TitleName,DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
	:Window(ClassNmae,TitleName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)
{

}

ATOM myButton::init()
{
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProcb;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= ClassNmae;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


	return RegisterClassEx(&wcex);
}
