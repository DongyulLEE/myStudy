#pragma once

#include "resource.h"


class Window
{
public :
	Window(const LPCWSTR ClassNmae, const LPCWSTR TitleName,DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
	
	virtual ATOM init();
	bool creat();
	void handleMessage();
	HWND GetHandle();

protected:
	WNDCLASSEX wcex;
	LPCWSTR ClassNmae;
	LPCWSTR TitleName;
	DWORD dwStyle;
	int x, y, nWidth, nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;
	HWND hWnd;
};


class myButton : public Window
{
public:
	myButton(const LPCWSTR ClassNmae, const LPCWSTR TitleName,DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
	ATOM init();
};

