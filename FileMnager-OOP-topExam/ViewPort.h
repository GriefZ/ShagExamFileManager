#pragma once
#include <iostream>
#include <string>
#include <vector>


class ViewPort
{
	int m_width;
	int m_height;
	std::vector<std::string> m_vp;
public:
	ViewPort():m_width{0},m_height{0}
	{
		m_vp.clear();
	}
	ViewPort(int w, int h)
	{
		ReSize(w, h);
	}
	ViewPort& ReSize(int w, int h)
	{
		m_width = w;
		m_height = h;
		m_vp.resize(m_height);
		return *this;
	}
	ViewPort& operator()(int w, int h)
	{
		return ReSize(w, h);
	}
	ViewPort& Fill()
	{
		m_vp[0] = "\xc9" + std::string(m_width - 2, '\xcd') + "\xbb";
		for (int i = 1; i < m_height-1; i++)
			m_vp[i] = "\xba" + std::string(m_width - 2, ' ') + "\xba";
		m_vp[m_height - 1] = "\xc8" + std::string(m_width - 2, '\xcd') + "\xbc";
		return *this;
	}
	ViewPort& Show()
	{
		for (int i = 0; i < m_height; i++)
			std::cout << "\n" << m_vp[i];
		return *this;
	}
	ViewPort operator+(const ViewPort& b)
	{
		ViewPort c(m_width + b.m_width, std::max(m_height, b.m_height));
		for (int i = 0; i < c.m_height; i++)
		{
			std::string lvp = std::string(m_width, ' ');
			std::string rvp = std::string(b.m_width, ' ');
			if (i < m_height)
				lvp = m_vp[i];
			if (i < b.m_height)
				rvp = b.m_vp[i];
			c.m_vp[i] = lvp + rvp;
		}
		return c;
	}
};

