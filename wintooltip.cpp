#include "wintooltip.h"

//-------------------------------------------------------------------------
// Adds a tool
//-------------------------------------------------------------------------

void Win::ToolTipHandle::AddTool (Win::Base win, const UINT id, Win::Rect & rect, std::tstring str, const UINT flag, const LPARAM lParam)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = flag ;
	ti.hwnd		   = win ;
	ti.uId		   = id ;
	ti.rect.left   = rect.GetLeft () ;
	ti.rect.right  = rect.GetRight () ;
	ti.rect.bottom = rect.GetBottom () ;
	ti.rect.top    = rect.GetTop () ;
	ti.hinst       = win.GetInstance () ;
	ti.lpszText    = &str [0] ;
	ti.lParam      = lParam ;

	if (SendMessage (TTM_ADDTOOL, 0, reinterpret_cast <LPARAM> (&ti)) == FALSE)
		throw Win::Exception (TEXT("Error, could not add a tool to the tooltip")) ;

}

//-------------------------------------------------------------------------
// Adds a tool
//-------------------------------------------------------------------------

void Win::ToolTipHandle::AddTool (Win::Base win, const UINT id, Win::Rect & rect, const UINT flag, const LPARAM lParam)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = flag | TTF_IDISHWND;
	ti.hwnd		   = win ;
	ti.uId		   = id ;
	ti.rect.left   = rect.GetLeft () ;
	ti.rect.right  = rect.GetRight () ;
	ti.rect.bottom = rect.GetBottom () ;
	ti.rect.top    = rect.GetTop () ;
	ti.hinst       = win.GetInstance () ;
	ti.lpszText = LPSTR_TEXTCALLBACK  ;
	ti.lParam      = lParam ;

	if (SendMessage (TTM_ADDTOOL, 0, reinterpret_cast <LPARAM> (&ti))== FALSE)
		throw Win::Exception (TEXT("Error, could not add a tool to the tooltip")) ;

}

//-------------------------------------------------------------------------
// Adds a tool
//-------------------------------------------------------------------------

void Win::ToolTipHandle::AddTool (HINSTANCE hInstance, Win::Base win, const UINT id, Win::Rect & rect, int stringId, const UINT flag, const LPARAM lParam)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = flag ;
	ti.hwnd		   = win ;
	ti.uId		   = id ;
	ti.rect.left   = rect.GetLeft () ;
	ti.rect.right  = rect.GetRight () ;
	ti.rect.bottom = rect.GetBottom () ;
	ti.rect.top    = rect.GetTop () ;
	ti.hinst       = hInstance ;
	ti.lpszText    = reinterpret_cast <TCHAR *> (stringId)  ;
	ti.lParam      = lParam ;

	if (SendMessage (TTM_ADDTOOL, 0, reinterpret_cast <LPARAM> (&ti))== FALSE)
		throw Win::Exception (TEXT("Error, could not add a tool to the tooltip")) ;

}

//-------------------------------------------------------------------------
// Adds a tool
//-------------------------------------------------------------------------

void Win::ToolTipHandle::AddTool (Win::Base win, std::tstring & str, const UINT flag, const LPARAM lParam)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = flag;
	ti.hwnd		   =  ::GetParent (win) ;
	ti.uId		   = reinterpret_cast <UINT> (static_cast <HWND> (win)) ;
	
	ti.hinst       = win.GetInstance () ;
	ti.lpszText    = &str [0] ;
	ti.lParam      = lParam ;

	if (SendMessage (TTM_ADDTOOL, 0, reinterpret_cast <LPARAM> (&ti))== FALSE)
		throw Win::Exception (TEXT("Error, could not add a tool to the tooltip")) ;

}

//-------------------------------------------------------------------------
// Adds a tool
//-------------------------------------------------------------------------

void Win::ToolTipHandle::AddTool (Win::Base win,const UINT flag, const LPARAM lParam)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = flag | TTF_IDISHWND;
	ti.hwnd		   = ::GetParent (win) ;
	ti.uId		   = reinterpret_cast <UINT> (static_cast <HWND> (win)) ;
	
	ti.hinst       = win.GetInstance () ;
	ti.lpszText    = LPSTR_TEXTCALLBACK ;
	ti.lParam      = lParam ;

	if (SendMessage (TTM_ADDTOOL, 0, reinterpret_cast <LPARAM> (&ti)) == FALSE)
		throw Win::Exception (TEXT("Error, could not add a tool to the tooltip")) ;

}

//-------------------------------------------------------------------------
// Adds a tool
//-------------------------------------------------------------------------

void Win::ToolTipHandle::AddTool (HINSTANCE hInstance, Win::Base win, int stringId, const UINT flag, const LPARAM lParam)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = flag ;
	ti.hwnd		   =  ::GetParent (win) ;
	ti.uId		   = reinterpret_cast <UINT> (static_cast <HWND> (win)) ;
	
	ti.hinst       = hInstance ;
	ti.lpszText    = reinterpret_cast <TCHAR *> (stringId) ;
	ti.lParam      = lParam ;

	if (SendMessage (TTM_ADDTOOL, 0, reinterpret_cast <LPARAM> (&ti)) == FALSE)
		throw Win::Exception (TEXT("Error, could not add a tool to the tooltip")) ;

}

//-------------------------------------------------------------------------
// Removes a tool
//
// Parameters:
//
// Win::Base & win -> The handle of the tooltip
// const int id -> The id of the tooltip
//-------------------------------------------------------------------------

void Win::ToolTipHandle::DeleteTool (Win::Base win, const UINT id) 
{
	TOOLINFO ti ;
				
	ti.cbSize = sizeof (TOOLINFO) ;
	ti.hwnd   = win ;
	ti.uId    = id ;
}

//-------------------------------------------------------------------------
// Gets the text of a tool tip
//
// Return value:  The text.
//
// Parameters:
//
// Win::Base & win -> The handle of the tooltip
// const int id -> The id of the tooltip
//-------------------------------------------------------------------------

std::tstring Win::ToolTipHandle::GetText (Win::Base win, const int id) const
{
	std::tstring str ;
	TOOLINFO ti ;

	str.reserve (255 + 1);
	str.resize (255);
	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = 0 ;
	ti.hwnd		   = win ;
	ti.uId		   = id ;
	ti.hinst       = NULL ;
	ti.lpszText    = &str [0]  ;
	ti.lParam      = 0 ;

	SendMessage (TTM_GETTEXT, 0, reinterpret_cast <LPARAM> (&ti)) ;

	return str ;
}

//-------------------------------------------------------------------------
// Sets the bounding rectangle
//
// Parameters:
//
// Win::Base & win -> The handle of the tooltip
// Win::Rect & rect -> The new bounding rectangle
// const int id -> The id of the tooltip
//-------------------------------------------------------------------------

void Win::ToolTipHandle::SetBoundingRect (Win::Base win, Win::Rect & rect, const UINT id)
{
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = 0 ;
	ti.hwnd		   = win ;
	ti.uId		   = id ;
	ti.rect.left   = rect.GetLeft () ;
	ti.rect.right  = rect.GetRight () ;
	ti.rect.bottom = rect.GetBottom () ;
	ti.rect.top    = rect.GetTop () ;
	ti.hinst       = NULL ;
	ti.lpszText    = NULL ;
	ti.lParam      = 0 ;

	SendMessage (TTM_NEWTOOLRECT, 0, reinterpret_cast <LPARAM> (&ti)) ;
}

//-------------------------------------------------------------------------
// Starts tracking a tooltip
//
// Parameters:
//
// Win::Base & win -> The handle of the tooltip
// const int id -> The id of the tooltip
// bool activate -> True is activated, false is desactivated.
//-------------------------------------------------------------------------

void Win::ToolTipHandle::TrackActivate (Win::Base & win, const int id, bool activate)
{
			
	TOOLINFO ti ;

	ti.cbSize	   = sizeof (TOOLINFO) ;
	ti.uFlags	   = 0 ;
	ti.hwnd		   = win ;
	ti.uId		   = id ;

	ti.hinst       = NULL ;
	ti.lpszText    = NULL ;
	ti.lParam      = 0 ;

	SendMessage (TTM_TRACKACTIVATE, activate, reinterpret_cast <LPARAM> (&ti)) ;

}