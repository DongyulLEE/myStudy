#pragma once

#include "resource.h"


class Window
{
public:
	static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	virtual bool create(const LPCWSTR TitleName,HWND pWnd);
	virtual LRESULT handleMessage(HWND, UINT, WPARAM, LPARAM);
	HWND GetHWND();

protected:
	HWND pWnd;
	HWND hWnd;
	HINSTANCE hInstance;
};


class mybutton : public Window
{
public:
	mybutton();
	~mybutton();
	virtual LRESULT handleMessage(HWND, UINT, WPARAM, LPARAM);
	virtual bool create(const LPCWSTR TitleName,HWND pWnd);
};
