#pragma once
#include "ViewPort.h"
#include <conio.h>
#include <Windows.h>

class MainWnd
{
	ViewPort m_lvp;
	ViewPort m_rvp;
	CONSOLE_SCREEN_BUFFER_INFO m_screen;
	HANDLE m_console;
	bool m_fullScreen;
public:
	MainWnd()
	{
		m_lvp(20, 20);
		m_rvp(20, 20);
		m_fullScreen = false;
		ResizeByWindows();
	}
	void SwitchMode()
	{
		m_console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (m_console == INVALID_HANDLE_VALUE)
		{
			std::cout << "\nError get console";
			return;
		}
		if (SetConsoleDisplayMode(m_console, (m_fullScreen) ? 2 : 1, 0))
		{
			m_fullScreen = !m_fullScreen;
			ResizeByWindows();
		}
		else
		{
			std::cout << "\nError switch FullScreen mode";
			return;
		}
	}
	void ResizeByWindows()
	{
		m_console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (m_console == INVALID_HANDLE_VALUE)
		{
			std::cout << "\nError get console";
			return;
		}
		if (!GetConsoleScreenBufferInfo(m_console, &m_screen))
		{
			std::cout << "\nError get screen size";
			return;
		}
		int w = m_screen.srWindow.Right - m_screen.srWindow.Left;
		int h = m_screen.srWindow.Bottom - m_screen.srWindow.Top;
		m_lvp(w / 2, h - 1);
		m_rvp(w / 2, h - 1);
	}
	void Show()
	{
		system("cls");
		m_lvp.Fill();
		m_rvp.Fill();
		(m_lvp + m_rvp).Show();
		std::cout << "\n";
	}
	void LoopMsg()
	{
		while (true)
		{
			Show();
			int key = _getch();
			if (key == 224)
				key = _getch();
			std::cout << "\n" << key;
			switch (key)
			{
			case 27://Esc
				return;
				break;
			case 134://F12 //fullscreen switch
				SwitchMode();
				break;
			}
		}
	}
};

