#pragma once

#include "..\MainWindow\sga.hpp"
#include "tower.h"

class Enemy : public MainWindow<Enemy>
{
	typedef Enemy Me;
	typedef MainWindow<Enemy> Base;
public :
	Enemy()
	{
	}
	~Enemy()
	{
	}
	void Draw(HDC hdc)
	{
	}
	void move()
	{
	}
protected :
	void SetEventMap()
	{
		AddEventHandler(WM_CREATE, &Me::OnCreate);
		AddEventHandler(WM_DESTROY, &Me::OnDestroy);
		AddEventHandler(WM_PAINT, &Me::OnPaint);
		AddEventHandler(WM_TIMER, &Me::OnTimer);
	}
	LRESULT OnTimer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		x += 10;
		if(x + 20 > rectView.right) 
		{
			x = rectView.right - 10;
			y += 10;

		}
		if(y + 20 > rectView.bottom)
		{
			x -= 10;
			y = rectView.bottom - 10;
		}
		
		::InvalidateRgn(hWnd, NULL, TRUE);

		return 0;
	}
	LRESULT OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		hdc = ::BeginPaint(hWnd, &ps);
		::Ellipse(hdc, x-10, y-10, x+10, y+10);
		::EndPaint(hWnd, &ps);

		SetTimer(hWnd, 1, 70, NULL);

		return 0;
	}
	LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		::GetClientRect(hWnd, &rectView);
		x = 10;
		y = 50;

		return 0;
	}
	LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		::KillTimer(hWnd, 1);
		::PostQuitMessage(0);

		return 0;
	}
private :
	HDC hdc;
	PAINTSTRUCT ps;
	Rect rcClient;

	RECT rectView;
	int x;
	int y;
};