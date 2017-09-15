#ifndef SUPPRESS_STYLE_H
#define SUPPRESS_STYLE_H

///////////////////////////
//
//	Objects of this class will suppress a window style
//  from construction until destruction.
//
//	Author: Dave Lorde	(dlorde@cix.compulink.co.uk)
//
//          Copyright January 2000
//

class  SuppressStyle
{
public:
	SuppressStyle(HWND hWnd, DWORD style)
		:m_hWnd(hWnd), m_Style(style), m_OldStyle(0)
	{
		m_OldStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
		if (m_OldStyle & m_Style)
			SetWindowLong(m_hWnd, GWL_STYLE, m_OldStyle & ~m_Style); 
	}

	~SuppressStyle()
	{
		if (m_OldStyle & m_Style)
			SetWindowLong(m_hWnd, GWL_STYLE, m_OldStyle);
	}

private:
	DWORD m_Style;
	DWORD m_OldStyle;
	HWND  m_hWnd;
};

#endif