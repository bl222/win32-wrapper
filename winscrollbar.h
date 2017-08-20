//-----------------------------------------------------------------
//  This file contains classes that allow using scrollbar controls.
//-----------------------------------------------------------------

#if !defined (WINSCROLLBAR_H)

	#define WINSCROLLBAR_H
	#include "useunicode.h"
	#include "winencapsulation.h"
	#include "wincontrol.h"

namespace Win
{
	//-------------------------------------------------------------------------
	// Win::VerticalScrollBarHandlet represents a vertical scrollbar created by
	// the WS_VSCROLL window style.
	//-------------------------------------------------------------------------

	class VerticalScrollBarHandle
	{
	public:

		//-------------------------------------------------------------------------
		// Constructor.  Saves the handle of the window owning the scrollbar and
		// initialize the SCROLLINFO data member.
		//
		// Parameters:
		//
		// const Win::Base hwnd -> The handle of the window owning the scrollbar.
		//-------------------------------------------------------------------------

		VerticalScrollBarHandle (const Win::Base hwnd) 
			: _h (hwnd)
		{
			//memset (this, 0, sizeof (*this)) ;		
			_vertScroll.cbSize = sizeof (SCROLLINFO) ;
		}
		
		//-------------------------------------------------------------------------
		// Obtains the minimum range of the scrollbar.
		//
		// Return value: The minimum range of the scrollbar.
		//-------------------------------------------------------------------------

		int  GetMinRange ()
		{
			_vertScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			return _vertScroll.nMin ;
		}

		//-------------------------------------------------------------------------
		// Obtains the maximum range of the scrollbar.
		//
		// Return value: The maximum range of the scrollbar.
		//-------------------------------------------------------------------------

		int  GetMaxRange ()
		{
			_vertScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			return _vertScroll.nMax ;
		}

		//-------------------------------------------------------------------------
		// Obtains the both the maximum and minimum range of the scrollbar.
		//
		// Parameters:
		// 
		// int & min -> Will contain the minimum range.
		// int & max -> Will contain the maximum range.
		//-------------------------------------------------------------------------

		void GetRange (int & min, int & max)
		{
			_vertScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			min = _vertScroll.nMin ;
			max = _vertScroll.nMax ;

		}

		//-------------------------------------------------------------------------
		// Obtains the page size of the scrollbar.
		//
		// Return value: The page size of the scrollbar.
		//-------------------------------------------------------------------------

		UINT GetPageSize () 
		{
			_vertScroll.fMask = SIF_PAGE ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			return _vertScroll.nPage ;
		}

		//-------------------------------------------------------------------------
		// Obtains the position of the thumb of the of the scrollbar.
		//
		// Return value: The position of the thumb.
		//-------------------------------------------------------------------------

		int  GetCurrentPosition ()
		{
			_vertScroll.fMask = SIF_POS ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			return _vertScroll.nPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains the position of the thumb of the of the scrollbar as it is being
		// scrolled.
		//
		// Return value: The position of the thumb as it is being scroll.
		//-------------------------------------------------------------------------

		int  GetTrackingPosition ()
		{
			_vertScroll.fMask = SIF_TRACKPOS ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			return _vertScroll.nTrackPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains all the info on the scrollbar.
		//
		// Parameters:
		// 
		// int & min       -> Will contain the minimum range.
		// int & max       -> Will contain the maximum range.
		// UINT & pageSize -> Will contain the page size.
		// int & pos       -> Will contain the position of the thumb.
		//-------------------------------------------------------------------------

		void GetAllInfo  (int & min, int & max, UINT & pageSize, int & pos)
		{
			_vertScroll.fMask = SIF_ALL ;
			::GetScrollInfo (_h, SB_VERT, &_vertScroll) ;

			min      = _vertScroll.nMin ;
			max      = _vertScroll.nMax ;
			pageSize = _vertScroll.nPage ;
			pos      = _vertScroll.nPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains all the info on the scrollbar.
		//
		// Parameters:
		// 
		// Win::ScrollInfo & scrollInfo -> Will contain the info.
		//-------------------------------------------------------------------------

		void GetAllInfo  (Win::ScrollInfo & scrollInfo) 
		{
			scrollInfo.SetMask (SIF_ALL) ;
			::GetScrollInfo (_h, SB_VERT, reinterpret_cast <LPSCROLLINFO> (&scrollInfo)) ;
		}

		//-------------------------------------------------------------------------
		// Sets the range of the scrollbar.
		//
		// Parameters:
		// 
		// const int min     -> Minimum range of the scrollbar.
		// const int max     -> Maximum range of the scrollbar.
		// const bool redraw -> True if the scrollbar must be redrawn, else false.
		//-------------------------------------------------------------------------

		void SetRange (const int min, const int max, const bool redraw = false)
		{
			_vertScroll.nMin  = min ;
			_vertScroll.nMax  = max ;
			_vertScroll.fMask = SIF_RANGE ;

			::SetScrollInfo (_h, SB_VERT, &_vertScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets the page size of the scrollbar.
		//
		// Parameters:
		// 
		// const UINT pageSize -> The size of a page.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetPageSize (const UINT pageSize, const bool redraw = false)
		{
			_vertScroll.nPage = pageSize ;
			_vertScroll.fMask = SIF_PAGE ;

			::SetScrollInfo (_h, SB_VERT, &_vertScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets the position of the thumb of the scrollbar.
		//
		// Parameters:
		// 
		// const int pos       -> New position of thumb.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetCurrentPosition (const int pos, const bool redraw = false)
		{
			_vertScroll.nPos  = pos ;
			_vertScroll.fMask = SIF_POS ;

			::SetScrollInfo (_h, SB_VERT, &_vertScroll, redraw) ;
		}
		
		//--------------------------------------------------------------------------
		// Sets all the parameters of the scrollbar.
		//
		// Parameters:
		// 
		// const int min       -> Minimum range of the scrollbar.
		// const int max       -> Maximum range of the scrollbar.
		// const UINT pageSize -> The size of a page.
		// const int pos       -> New position of thumb.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetAllInfo  (const int min, const int max, const UINT pageSize, const int pos, const bool redraw = false) 
		{
			_vertScroll.nMin  = min ;
			_vertScroll.nMax  = max ;
			_vertScroll.nPage = pageSize ;
			_vertScroll.nPos  = pos ;
			_vertScroll.fMask = SIF_ALL ;

			::SetScrollInfo (_h, SB_VERT, &_vertScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets all the parameters of the scrollbar.
		//
		// Parameters:
		// 
		// Win::ScrollInfo & scrollInfo -> Contains all the parameters of the
		//								   scrollbar.
		// const bool redraw		    -> True if the scrollbar must be redrawn,
		//								   else false.
		//--------------------------------------------------------------------------

		void SetAllInfo  (Win::ScrollInfo & scrollInfo, const bool redraw = false)
		{
			scrollInfo.SetMask(SIF_ALL) ;

			::SetScrollInfo (_h, SB_VERT, reinterpret_cast <LPSCROLLINFO> (&scrollInfo), redraw) ;
		}
		
		//--------------------------------------------------------------------------
		// Can either shows or hides the scrollbar.
		//
		// Parameters:
		// 
		// const bool show -> If true show the scrollbar.  If false hide the 
		//					  scrollbar.
		//--------------------------------------------------------------------------

		bool SetShow (const bool show = true)
		{
			return ::ShowScrollBar (_h, SB_VERT,show) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Shows the scrollbar.
		//--------------------------------------------------------------------------

		bool Show () const
		{
			return ::ShowScrollBar (_h, SB_VERT, TRUE) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Hides the scrollbar.
		//--------------------------------------------------------------------------

		bool Hide () const
		{
			return ::ShowScrollBar (_h, SB_VERT, FALSE) != 0 ;
		}

		//-------------------------------------------------------------------------
		// Can be used to enable/disable any arrow on the scrollbar.
		//
		// Parameters:
		//
		// const UINT arrowFlag -> A flag indicating which arrow is disabled or 
		//						   enabled.
		//-------------------------------------------------------------------------

		bool SetEnable (const UINT arrowFlag)
		{
			return ::EnableScrollBar (_h, SB_VERT, arrowFlag) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Enanbles both arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool EnableBothArrow () const 
		{
			return ::EnableScrollBar (_h, SB_VERT, ESB_ENABLE_BOTH) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disables both arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableBothArrow () const 
		{
			return ::EnableScrollBar (_h, SB_VERT, ESB_DISABLE_BOTH) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disables the up arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableUpArrow () const 
		{
			return ::EnableScrollBar (_h, SB_VERT, ESB_DISABLE_UP) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disables the down arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableDownArrow () const 
		{
			return ::EnableScrollBar (_h, SB_VERT, ESB_DISABLE_DOWN) != 0 ;
		}

	private:
		SCROLLINFO _vertScroll ; // Used to obtain/modify the parameters of the scrollbar.
		Win::Base      _h ; // Window owning the scroll bar
	} ;

	//-------------------------------------------------------------------------
	// Win::HorizontalScrollBarHandlet represents an horizontal scrollbar created by
	// the WS_HSCROLL window style.
	//-------------------------------------------------------------------------

	class HorizontalScrollBarHandle
	{
	public:

		//-------------------------------------------------------------------------
		// Constructor.  Saves the handle of the window owning the scrollbar and
		// initialize the SCROLLINFO data member.
		//
		// Parameters:
		//
		// const Win::Base hwnd -> The handle of the window owning the scrollbar.
		//-------------------------------------------------------------------------

		HorizontalScrollBarHandle (const Win::Base hwnd) 
			: _h (hwnd)
		{
					
			_horzScroll.cbSize = sizeof (SCROLLINFO) ;
		}

		//-------------------------------------------------------------------------
		// Obtains the minimum range of the scrollbar.
		//
		// Return value: The minimum range of the scrollbar.
		//-------------------------------------------------------------------------		

		int  GetMinRange () 
		{
			_horzScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;

			return _horzScroll.nMin ;
		}

		//-------------------------------------------------------------------------
		// Obtains the maximum range of the scrollbar.
		//
		// Return value: The maximum range of the scrollbar.
		//-------------------------------------------------------------------------

		int  GetMaxRange () 
		{
			_horzScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;

			return _horzScroll.nMax ;
		}

		//-------------------------------------------------------------------------
		// Obtains the both the maximum and minimum range of the scrollbar.
		//
		// Parameters:
		// 
		// int & min -> Will contain the minimum range.
		// int & max -> Will contain the maximum range.
		//-------------------------------------------------------------------------

		void GetRange (int & min, int & max)
		{
			_horzScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;
			min = _horzScroll.nMin ;
			max = _horzScroll.nMax ;

		}

		//-------------------------------------------------------------------------
		// Obtains the page size of the scrollbar.
		//
		// Return value: The page size of the scrollbar.
		//-------------------------------------------------------------------------

		UINT GetPageSize () 
		{
			_horzScroll.fMask = SIF_PAGE ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;

			return _horzScroll.nPage ;
		}

		//-------------------------------------------------------------------------
		// Obtains the position of the thumb of the of the scrollbar.
		//
		// Return value: The position of the thumb.
		//-------------------------------------------------------------------------

		int  GetCurrentPosition () 
		{
			_horzScroll.fMask = SIF_POS ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;

			return _horzScroll.nPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains the position of the thumb of the of the scrollbar as it is being
		// scrolled.
		//
		// Return value: The position of the thumb as it is being scroll.
		//-------------------------------------------------------------------------

		int  GetTrackingPosition () 
		{
			_horzScroll.fMask = SIF_TRACKPOS ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;

			return _horzScroll.nTrackPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains all the info on the scrollbar.
		//
		// Parameters:
		// 
		// int & min       -> Will contain the minimum range.
		// int & max       -> Will contain the maximum range.
		// UINT & pageSize -> Will contain the page size.
		// int & pos       -> Will contain the position of the thumb.
		//-------------------------------------------------------------------------

		void GetAllInfo  (int & min, int & max, UINT & pageSize, int & pos)
		{
			_horzScroll.fMask = SIF_ALL ;
			::GetScrollInfo (_h, SB_HORZ, &_horzScroll) ;

			min      = _horzScroll.nMin ;
			max      = _horzScroll.nMax ;
			pageSize = _horzScroll.nPage ;
			pos      = _horzScroll.nPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains all the info on the scrollbar.
		//
		// Parameters:
		// 
		// Win::ScrollInfo & scrollInfo -> Will contain the info.
		//-------------------------------------------------------------------------

		void GetAllInfo  (Win::ScrollInfo & scrollInfo)
		{
			scrollInfo.SetMask (SIF_ALL) ;
			::GetScrollInfo (_h, SB_HORZ, reinterpret_cast <LPSCROLLINFO> (&scrollInfo)) ;
		}

		//-------------------------------------------------------------------------
		// Sets the range of the scrollbar.
		//
		// Parameters:
		// 
		// const int min     -> Minimum range of the scrollbar.
		// const int max     -> Maximum range of the scrollbar.
		// const bool redraw -> True if the scrollbar must be redrawn, else false.
		//-------------------------------------------------------------------------

		void SetRange (const int min, const int max, const bool redraw = false)
		{
			_horzScroll.nMin  = min ;
			_horzScroll.nMax  = max ;
			_horzScroll.fMask = SIF_RANGE ;

			::SetScrollInfo (_h, SB_HORZ, &_horzScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets the page size of the scrollbar.
		//
		// Parameters:
		// 
		// const UINT pageSize -> The size of a page.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetPageSize (const UINT pageSize, const bool redraw = false)
		{
			_horzScroll.nPage = pageSize ;
			_horzScroll.fMask = SIF_PAGE ;

			::SetScrollInfo (_h, SB_HORZ, &_horzScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets the position of the thumb of the scrollbar.
		//
		// Parameters:
		// 
		// const int pos       -> New position of thumb.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetCurrentPosition (const int pos, const bool redraw = false)
		{
			_horzScroll.nPos  = pos ;
			_horzScroll.fMask = SIF_POS ;

			::SetScrollInfo (_h, SB_HORZ, &_horzScroll, redraw) ;
		}
		
		//--------------------------------------------------------------------------
		// Sets all the parameters of the scrollbar.
		//
		// Parameters:
		// 
		// const int min       -> Minimum range of the scrollbar.
		// const int max       -> Maximum range of the scrollbar.
		// const UINT pageSize -> The size of a page.
		// const int pos       -> New position of thumb.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetAllInfo  (const int min, const int max, const UINT pageSize, const int pos, const bool redraw = false) 
		{
			_horzScroll.nMin  = min ;
			_horzScroll.nMax  = max ;
			_horzScroll.nPage = pageSize ;
			_horzScroll.nPos  = pos ;
			_horzScroll.fMask = SIF_ALL ;

			::SetScrollInfo (_h, SB_HORZ, &_horzScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets all the parameters of the scrollbar.
		//
		// Parameters:
		// 
		// Win::ScrollInfo & scrollInfo -> Contains all the parameters of the
		//								   scrollbar.
		// const bool redraw		    -> True if the scrollbar must be redrawn,
		//								   else false.
		//--------------------------------------------------------------------------

		void SetAllInfo  (Win::ScrollInfo & scrollInfo, const bool redraw = false)
		{
			scrollInfo.SetMask(SIF_ALL) ;

			::SetScrollInfo (_h, SB_HORZ, reinterpret_cast <LPSCROLLINFO> (&scrollInfo), redraw) ;
		}
		
		//--------------------------------------------------------------------------
		// Can either shows or hides the scrollbar.
		//
		// Parameters:
		// 
		// const bool show -> If true show the scrollbar.  If false hide the 
		//					  scrollbar.
		//--------------------------------------------------------------------------
	
		bool SetShow (const bool show = true) const 
		{
			return ::ShowScrollBar (_h, SB_HORZ,show) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Shows the scrollbar.
		//--------------------------------------------------------------------------

		bool Show () const 
		{
			return ::ShowScrollBar (_h, SB_HORZ, TRUE) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Hides the scrollbar.
		//--------------------------------------------------------------------------

		bool Hide () const 
		{
			return ::ShowScrollBar (_h, SB_HORZ, FALSE) != 0 ;
		}

		//-------------------------------------------------------------------------
		// Can be used to enable/disable any arrow on the scrollbar.
		//
		// Parameters:
		//
		// const UINT arrowFlag -> A flag indicating which arrow is disabled or 
		//						   enabled.
		//-------------------------------------------------------------------------

		bool SetEnable (const UINT arrowFlag)const 
		{
			return ::EnableScrollBar (_h, SB_HORZ, arrowFlag) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Enables both arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool EnableBothArrow () const 
		{
			return ::EnableScrollBar (_h, SB_HORZ, ESB_ENABLE_BOTH) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disables both arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableBothArrow () const 
		{
			return ::EnableScrollBar (_h, SB_HORZ, ESB_DISABLE_BOTH) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Enables the left arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableLeftArrow () const 
		{
			return ::EnableScrollBar (_h, SB_HORZ, ESB_DISABLE_LEFT) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Enables the right arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableRightArrow () const 
		{
			return ::EnableScrollBar (_h, SB_HORZ, ESB_DISABLE_RIGHT) != 0 ;
		}
	private:

		SCROLLINFO _horzScroll ; // Used to obtain/modify the parameters of the scrollbar.
		Win::Base      _h ; // Window owning the scroll bar.
	} ;

	//-------------------------------------------------------------------------
	// Win::ControlScrollBarHandle encapsulates a scrollbar control handle.  Represents 
	// a scrollbar control.  Inherit from Win::SimpleControl for basic 
	// functionality.
	//-------------------------------------------------------------------------

	class ControlScrollBarHandle : public SimpleControlHandle
	{
	public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the scrollbar
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Baseparent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

		ControlScrollBarHandle (const Win::Base parent, const int id)
			: SimpleControlHandle (parent, id)
		{
			_controlScroll.cbSize = sizeof (SCROLLINFO) ;
		}

		//-------------------------------------------------------------------------
		// Constructor.  Set the encapsulate handle directly
		// 
		// Parameters:
		//
		// const Win::Basewin -> Handle of the group box control.
		//-------------------------------------------------------------------------

		ControlScrollBarHandle (const Win::Base win = NULL)
			: SimpleControlHandle (win)
		{
			
			_controlScroll.cbSize = sizeof (SCROLLINFO) ;
		}

		void operator = (ControlScrollBarHandle & sh)
		{
			_h = sh._h;
		}

		//-------------------------------------------------------------------------
		// Initialize the handle and the id through the parent handle.
		//-------------------------------------------------------------------------

		void Init (const Win::Base parent, const int id)
		{
			SimpleControlHandle::Init (parent, id) ;
		}

		//-------------------------------------------------------------------------
		// Obtains the minimum range of the scrollbar.
		//
		// Return value: The minimum range of the scrollbar.
		//-------------------------------------------------------------------------

		int GetMinRange () 
		{
			_controlScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			return _controlScroll.nMin ;
		}

		//-------------------------------------------------------------------------
		// Obtains the maximum range of the scrollbar.
		//
		// Return value: The maximum range of the scrollbar.
		//-------------------------------------------------------------------------

		int GetMaxRange () 
		{
			_controlScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			return _controlScroll.nMax ;
		}

		//-------------------------------------------------------------------------
		// Obtains the both the maximum and minimum range of the scrollbar.
		//
		// Parameters:
		// 
		// int & min -> Will contain the minimum range.
		// int & max -> Will contain the maximum range.
		//-------------------------------------------------------------------------

		void GetRange (int & min, int & max)
		{
			_controlScroll.fMask = SIF_RANGE ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			min = _controlScroll.nMin ;
			max = _controlScroll.nMax ;

		}

		//-------------------------------------------------------------------------
		// Obtains the page size of the scrollbar.
		//
		// Return value: The page size of the scrollbar.
		//-------------------------------------------------------------------------

		UINT GetPageSize () 
		{
			_controlScroll.fMask = SIF_PAGE ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			return _controlScroll.nPage ;
		}

		//-------------------------------------------------------------------------
		// Obtains the position of the thumb of the of the scrollbar.
		//
		// Return value: The position of the thumb.
		//-------------------------------------------------------------------------

		int  GetCurrentPosition () 
		{
			_controlScroll.fMask = SIF_POS ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			return _controlScroll.nPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains the position of the thumb of the of the scrollbar as it is being
		// scrolled.
		//
		// Return value: The position of the thumb as it is being scroll.
		//-------------------------------------------------------------------------

		int  GetTrackingPosition () 
		{
			_controlScroll.fMask = SIF_TRACKPOS ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			return _controlScroll.nTrackPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains all the info on the scrollbar.
		//
		// Parameters:
		// 
		// int & min       -> Will contain the minimum range.
		// int & max       -> Will contain the maximum range.
		// UINT & pageSize -> Will contain the page size.
		// int & pos       -> Will contain the position of the thumb.
		//-------------------------------------------------------------------------

		void GetAllInfo  (int & min, int & max, UINT & pageSize, int & pos)
		{
			_controlScroll.fMask = SIF_ALL ;
			::GetScrollInfo (_h, SB_CTL, &_controlScroll) ;

			min      = _controlScroll.nMin ;
			max      = _controlScroll.nMax ;
			pageSize = _controlScroll.nPage ;
			pos      = _controlScroll.nPos ;
		}

		//-------------------------------------------------------------------------
		// Obtains all the info on the scrollbar.
		//
		// Parameters:
		// 
		// Win::ScrollInfo & scrollInfo -> Will contain the info.
		//-------------------------------------------------------------------------

		void GetAllInfo  (Win::ScrollInfo & scrollInfo)
		{
			scrollInfo.SetMask (SIF_ALL) ;
			::GetScrollInfo (_h, SB_CTL, reinterpret_cast <LPSCROLLINFO> (&scrollInfo)) ;
		}

		//-------------------------------------------------------------------------
		// Sets the range of the scrollbar.
		//
		// Parameters:
		// 
		// const int min     -> Minimum range of the scrollbar.
		// const int max     -> Maximum range of the scrollbar.
		// const bool redraw -> True if the scrollbar must be redrawn, else false.
		//-------------------------------------------------------------------------

		void SetRange    (const int min, const int max, const bool redraw = false)
		{
			_controlScroll.nMin  = min ;
			_controlScroll.nMax  = max ;
			_controlScroll.fMask = SIF_RANGE ;

			::SetScrollInfo (_h, SB_CTL, &_controlScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets the page size of the scrollbar.
		//
		// Parameters:
		// 
		// const UINT pageSize -> The size of a page.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetPageSize (const UINT pageSize, const bool redraw = false)
		{
			_controlScroll.nPage = pageSize ;
			_controlScroll.fMask = SIF_PAGE ;

			::SetScrollInfo (_h, SB_CTL, &_controlScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets the position of the thumb of the scrollbar.
		//
		// Parameters:
		// 
		// const int pos       -> New position of thumb.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetCurrentPosition (const int pos, const bool redraw = false)
		{
			_controlScroll.nPos  = pos ;
			_controlScroll.fMask = SIF_POS ;
			::SetScrollInfo (_h, SB_CTL, &_controlScroll, redraw) ;
		}
		
		//--------------------------------------------------------------------------
		// Sets all the parameters of the scrollbar.
		//
		// Parameters:
		// 
		// const int min       -> Minimum range of the scrollbar.
		// const int max       -> Maximum range of the scrollbar.
		// const UINT pageSize -> The size of a page.
		// const int pos       -> New position of thumb.
		// const bool redraw   -> True if the scrollbar must be redrawn, else false.
		//--------------------------------------------------------------------------

		void SetAllInfo  (const int min, const int max, const UINT pageSize, const int pos, const bool redraw = false) 
		{
			_controlScroll.nMin  = min ;
			_controlScroll.nMax  = max ;
			_controlScroll.nPage = pageSize ;
			_controlScroll.nPos  = pos ;
			_controlScroll.fMask = SIF_ALL ;

			::SetScrollInfo (_h, SB_CTL, &_controlScroll, redraw) ;
		}

		//--------------------------------------------------------------------------
		// Sets all the parameters of the scrollbar.
		//
		// Parameters:
		// 
		// Win::ScrollInfo & scrollInfo -> Contains all the parameters of the
		//								   scrollbar.
		// const bool redraw		    -> True if the scrollbar must be redrawn,
		//								   else false.
		//--------------------------------------------------------------------------

		void SetAllInfo  (Win::ScrollInfo & scrollInfo, const bool redraw = false)
		{
			scrollInfo.SetMask(SIF_ALL) ;

			::SetScrollInfo (_h, SB_CTL, reinterpret_cast <LPSCROLLINFO> (&scrollInfo), redraw) ;
		}
		
		//--------------------------------------------------------------------------
		// Can either shows or hides the scrollbar.
		//
		// Parameters:
		// 
		// const bool show -> If true show the scrollbar.  If false hide the 
		//					  scrollbar.
		//--------------------------------------------------------------------------

		bool SetShow (const bool show = true)
		{
			return ::ShowScrollBar (_h, SB_CTL,show) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Shows the scrollbar.
		//--------------------------------------------------------------------------

		bool Show () const 
		{
			return ::ShowScrollBar (_h, SB_CTL, TRUE) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Hides the scrollbar.
		//--------------------------------------------------------------------------

		bool Hide () const 
		{
			return ::ShowScrollBar (_h, SB_CTL, FALSE) != 0 ;
		}

		//-------------------------------------------------------------------------
		// Can be used to enable/disable any arrow on the scrollbar.
		//
		// Parameters:
		//
		// const UINT arrowFlag -> A flag indicating which arrow is disabled or 
		//						   enabled.
		//-------------------------------------------------------------------------

		bool SetEnable (UINT arrowFlag) const  
		{
			return ::EnableScrollBar (_h, SB_CTL, arrowFlag) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Enables both arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool EnableBothArrow () const 
		{
			return ::EnableScrollBar (_h, SB_CTL, ESB_ENABLE_BOTH) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disables both arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableBothArrow () const 
		{
			return ::EnableScrollBar (_h, SB_CTL, ESB_DISABLE_BOTH) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disable the left arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableLeftOrUpArrow () const 
		{
			return ::EnableScrollBar (_h, SB_CTL, ESB_DISABLE_LTUP) != 0 ;
		}

		//--------------------------------------------------------------------------
		// Disable the right arrow of the scrollbar.
		//--------------------------------------------------------------------------

		bool DisableRightOrDownArrow () const 
		{
			return ::EnableScrollBar (_h, SB_CTL, ESB_DISABLE_RTDN) != 0 ;
		}
	private:

		SCROLLINFO _controlScroll ; // Used to obtain/modify the parameters of the scrollbar.
	} ;

	//-------------------------------------------------------------------------
	// Win::ScrollBarHandle Creator allows to create a scrollbar control.
	// Inherit from Win::ControlCreator for basic functionality.
	//-------------------------------------------------------------------------	

	class ScrollBarCreator : public ControlCreator
	{
	public:

		//-------------------------------------------------------------------------
		// Constructor.  Creates a scrollbar control with the functionality of 
		// Win::ControlCreator.
		//-------------------------------------------------------------------------

		ScrollBarCreator (const Win::Base parent, const int id)
			: ControlCreator (std::tstring (TEXT("scrollbar")), parent, id) 
		{}

		//-------------------------------------------------------------------------
		// Creates a new ControlScrollBar control.
		// 
		// Return value:  The scroll bar control handle.
		//
		// Parameters:
		//
		// const std::tstring title -> The title of the scroll bar control.
		//-------------------------------------------------------------------------

		Win::ControlScrollBarHandle Create (const std::tstring title) const
		{
			return ChildCreator::Create (title) ;
		}

		//-------------------------------------------------------------------------
		// The following methods all serve the same purpose.  They set one of the 
		// style of the future scrollbar control.
		//-------------------------------------------------------------------------

		void SetBottomAlignStyle             () {_style |= SBS_BOTTOMALIGN ;}
		void SetHorzStyle                    () {_style |= SBS_HORZ ;}
		void SetLeftAlignStyle               () {_style |= SBS_LEFTALIGN ;}
		void SetRightAlignStyle              () {_style |= SBS_RIGHTALIGN ;}
		void SetSizeboxStyle                 () {_style |= SBS_SIZEBOX ;}
		void SetSizeboxBottomRightAlignStyle () {_style |= SBS_SIZEBOXBOTTOMRIGHTALIGN ;}
		void SetSizeboxTopLeftAlingStyle     () {_style |= SBS_SIZEBOXTOPLEFTALIGN ;}
		void SetSizeGripStyle                () {_style |= SBS_SIZEGRIP ;}
		void SetTopAlignStyle                () {_style |= SBS_TOPALIGN ;}
		void SetVertStyle                    () {_style |= SBS_VERT ;}

	} ;
}

#endif
