

#if !defined (WINENCAPSULATION_H)

	#define WINENCAPSULATION_H
	#include "useunicode.h"
	#include "winstruct.h"
	#include "winexception.h"

	namespace Win
	{
		//---------------------------------------------------------------------------
		// Win::Size encapsulates a SIZE structure through private inheritance
		//
		// Dara members of SIZE:
		//
		// cx -> Rectangle width.
		// cy -> Rectangle height.
		//---------------------------------------------------------------------------

		class Size : public Sys::Struct<SIZE>
		{
		public:

			//------------------------------------------------------------------
			// Constructor.
			//------------------------------------------------------------------

			Size ()
				: Sys::Struct<SIZE> ()
			{}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Win::Size object with a SIZE windows
			// structure.
			//------------------------------------------------------------------

			Size (const SIZE & size)
				: Sys::Struct<SIZE> (size)
			{}

			//---------------------------------------------------------------------------
			// Constructor.  Create a new Win::Size object from 2 int value.
			//
			// parameters:
			//
			// const int width  -> Width of the new object.
			// const int height -> Height of the new object.
			//---------------------------------------------------------------------------

			Size (const int width, const int height)
			{
				_struct.cx = width ;
				_struct.cy = height ;
			}

			//---------------------------------------------------------------------------
			// Get the rectangle's width
			//
			// Return value:  The cx data member of the SIZE structure
			//---------------------------------------------------------------------------

			int GetWidth () const 
			{
				return _struct.cx ;
			}

			//---------------------------------------------------------------------------
			// Get the rectangle's height.
			//
			// Return value:  The cy data member of the SIZE structure
			//---------------------------------------------------------------------------

			int GetHeight () const
			{
				return _struct.cy ;
			}
			
			//---------------------------------------------------------------------------
			// Set the rectangle's width.
			//
			// Parameters:
			// 
			// const int width -> The new width of the rectangle.
			//---------------------------------------------------------------------------

		    void SetWidth (const int width)  
			{
				_struct.cx = width ;
			}

			//---------------------------------------------------------------------------
			// Set the rectangle's height.
			//
			// Parameters:
			// 
			// const int height -> The new height of the rectangle.
			//---------------------------------------------------------------------------

	        void SetHeight (const int height) 
			{
				_struct.cy = height ;
			}

		} ;

		//---------------------------------------------------------------------------
		// Win::Point encapsulates a POINT structure through private inheritance
		//
		// Dara members of POINT:
		//
		// x -> X coordinate of the point.
		// y -> Y coordinate of the point.
		//---------------------------------------------------------------------------

		class Point : public Sys::Struct<POINT>
		{
		public :

			//------------------------------------------------------------------
			// Constructor.
			//------------------------------------------------------------------

			Point ()
				: Sys::Struct<POINT> ()
			{}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Win::Size object with a SIZE windows
			// structure.
			//------------------------------------------------------------------

			Point (const POINT & point)
				: Sys::Struct<POINT> (point)
			{}

			//---------------------------------------------------------------------------
			// Constructor.  Create a new Win::Point object from 2 int value.
			//
			// parameters:
			//
			// const int X -> X coordinate of the new object.
			// const int Y -> Y coordinate of the new object.
			//---------------------------------------------------------------------------

			Point (const int x, const int y) 
			{
				_struct.x = x ;
				_struct.y = y ;
			}

			//---------------------------------------------------------------------------
			// Get the x coordinate of the point.
			//
			// Return value:  The x data member of the POINT structure
			//---------------------------------------------------------------------------

			LONG GetX () const 
			{
				return _struct.x ;
			}

			//---------------------------------------------------------------------------
			// Get the y coordinate of the point.
			//
			// Return value:  The y data member of the POINT structure
			//---------------------------------------------------------------------------

			LONG GetY () const 
			{
				return _struct.y ;
			}

			//---------------------------------------------------------------------------
			// Set the new x coordinate of the point.
			//
			// Parameters:
			// 
			// const int width -> The new x coordinate of the point.
			//---------------------------------------------------------------------------

			void SetX (const LONG x) 
			{
				_struct.x = x ;
			}

			//---------------------------------------------------------------------------
			// Set the new y coordinate of the point.
			//
			// Parameters:
			// 
			// const int width -> The new y coordinate of the point.
			//---------------------------------------------------------------------------

			void SetY (const LONG y) 
			{
				_struct.y = y ;
			}

		} ;

		//---------------------------------------------------------------------------
		// Win::Rect encapsulates a Rect structure through private inheritance.
		//
		// Dara members of RECT:
		//
		// left    -> x coordinate of the upper left corner of the rectangle
		// top     -> y coordinate of the upper left corner of the rectangle
		// right   -> x coordinate of the lower right corner of the rectangle
		// bottom  -> y coordinate of the lower right corner of the rectangle
		//---------------------------------------------------------------------------

		class Rect : public Sys::Struct<RECT>
		{
		public:

			//------------------------------------------------------------------
			// Constructor.
			//------------------------------------------------------------------

			Rect ()
				: Sys::Struct<RECT> ()
			{}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Win::Rect object with a RECT windows
			// structure.
			//------------------------------------------------------------------

			Rect (const RECT & rect)
				: Sys::Struct<RECT> (rect)
			{}

			Rect (const RECTL & rect) ;

			Rect (const LONG l, const LONG r, const LONG t, const LONG b) ;

			//---------------------------------------------------------------------
			// Obtains the x coordinate of the upper left corner of the rectangle.
			//
			// Return value: The left data member of the RECT structure.
			//---------------------------------------------------------------------

			LONG GetLeft () const 
			{
				return _struct.left ;
			}

			//---------------------------------------------------------------------
			// Obtains the y coordinate of the upper left corner of the rectangle.
			//
			// Return value: The top data member of the RECT structure.
			//---------------------------------------------------------------------

			LONG GetTop () const 
			{
				return _struct.top ;
			}

			//---------------------------------------------------------------------
			// Obtains the x coordinate of the lower right corner of the rectangle.
			//
			// Return value: The right data member of the RECT structure.
			//---------------------------------------------------------------------

			LONG GetRight  () const 
			{
				return _struct.right ;
			}

			//---------------------------------------------------------------------
			// Obtains y coordinate of the lower right corner of the rectangle.
			//
			// Return value: The bottom data member of the RECT structure.
			//---------------------------------------------------------------------

			LONG GetBottom () const 
			{
				return _struct.bottom ;
			}

			//---------------------------------------------------------------------
			// Set the x coordinate of the upper left corner of the rectangle.
			//
			// Parameters:
			// 
			// const LONG l -> The new left value.
			//---------------------------------------------------------------------

			void SetLeft (const LONG l) 
			{
				_struct.left = l ;
			}

			//---------------------------------------------------------------------
			// Set the y coordinate of the upper left corner of the rectangle.
			//
			// Parameters:
			// 
			// const LONG t -> The new top value.
			//---------------------------------------------------------------------

			void SetTop (const LONG t) 
			{
				_struct.top = t ;
			}

			//---------------------------------------------------------------------
			// Set the x coordinate of the bottom right corner of the rectangle.
			//
			// Parameters:
			// 
			// const LONG r -> The new right value.
			//---------------------------------------------------------------------

			void SetRight (const LONG r) 
			{
				_struct.right = r ;
			}

			//---------------------------------------------------------------------
			// Set the x coordinate of the bottom right corner of the rectangle.
			//
			// Parameters:
			// 
			// const LONG b -> The new bottom value.
			//---------------------------------------------------------------------

			void SetBottom (const LONG b) 
			{
				_struct.bottom = b ;
			}

			//---------------------------------------------------------------------
			// Moves the rectangle represented by the Win::Rect object.
			//
			// Parameters:
			// 
			// const int x -> How much the rectangle must be moved on the left or
			//				  right.
			// const int y -> How much the rectangle must be moved up or down.
			//---------------------------------------------------------------------

			void Offset (const int x, const int y)
			{
				if (::OffsetRect (&_struct, x, y) == 0)
					throw Win::Exception (TEXT("Error, Could not offset rectangle.")) ;
			}

			//---------------------------------------------------------------------
			// Resize the rectangle represented by the Win::Rect object.
			//
			// Parameters:
			// 
			// const int x -> By how much the rectangle's width must be resized.
			// const int y -> By How much the rectangle's height must be resized.
			//---------------------------------------------------------------------

			void Inflate (const int x, const int y)  
			{
				if (::InflateRect (&_struct, x, y) == 0)
					throw Win::Exception (TEXT("Error, Could not inflate rectangle.")) ;
			}

			//---------------------------------------------------------------------
			// Set all the data members of the Win::Rect object to 0.
			//---------------------------------------------------------------------

			bool Empty ()
			{
				if (::SetRectEmpty (&_struct) == 0)
					throw Win::Exception (TEXT("Error, Could not empty the rectangle.")) ;
			}

			//---------------------------------------------------------------------
			// Set the data members of Win::Rect object with another Win::Rect
			// object passed as a parameter.
			//
			// Parameters:
			// 
			// const Win::Rect & srcRect -> Used to set the data members of the
			//								current Win::Rect object.
			//---------------------------------------------------------------------

			void Copy (const Win::Rect & srcRect)
			{
				if (::CopyRect (&_struct, srcRect) == 0)
					throw Win::Exception (TEXT("Error, Could not copy the rectangle.")) ;
			}

			//---------------------------------------------------------------------
			// Set the data members of the Win::Rect object to the intersection 
			// rectangle of 2 others Win::Rect objects.
			//
			// Parameters:
			// 
			// const Win::Rect & srcRect1 -> First Win::Rect which will be used for
			//								 the intersection.
			// const Win::Rect & srcRect2 -> Second Win::Rect which will be used for
			//								 the intersection.
			//---------------------------------------------------------------------

			void Intersect (const Win::Rect & srcRect1, const Win::Rect & srcRect2)
			{
				if (::IntersectRect (&_struct, srcRect1, srcRect2) == 0)
					throw Win::Exception (TEXT("Error, Could not intersect the rectangles.")) ;
			}

			//---------------------------------------------------------------------
			// Set the data members of the Win::Rect object to the union 
			// rectangle of 2 others Win::Rect objects.
			//
			// Parameters:
			// 
			// const Win::Rect & srcRect1 -> First Win::Rect which will be used for
			//								 the union.
			// const Win::Rect & srcRect2 -> Second Win::Rect which will be used for
			//								 the union.
			//---------------------------------------------------------------------

			void Union (const Win::Rect & srcRect1, const Win::Rect & srcRect2) 
			{
				if (::UnionRect (&_struct, srcRect1, srcRect2) == 0)
					throw Win::Exception (TEXT("Error, Could not unify the rectangles.")) ;
			}

			//-----------------------------------------------------------------------
			// Determines if the Win::Rect object is empty.  (All data members are 0)
			//
			// Return value:  True if the Win::Rect object is empty, else false.
			//-----------------------------------------------------------------------

			bool IsEmpty () const
			{
				return ::IsRectEmpty (&_struct) != 0 ;

			}

			void PointInside (const Win::Point & point) const ;

		} ;

		//---------------------------------------------------------------------------
		// Win::MinMaxInfo encapsulates a MINMAXINFO structure through private 
		// inheritance.
		//
		// Data members of MINMAXINFO:
		//
		// ptMaxSize      -> The maximized width and height of the maximized window.
		// ptMaxPosition  -> The position of the left side and top of the maximized 
		//                   window.
		// ptMinTrackSize -> Minimum tracking width and height of the window.
		// ptMaxTrackSize -> Maximum tracking width and height of the window.
		//---------------------------------------------------------------------------

		class MinMaxInfo : public Sys::Struct<MINMAXINFO>
		{
		public:

			//------------------------------------------------------------------
			// Constructor.
			//------------------------------------------------------------------

			MinMaxInfo ()
				: Sys::Struct<MINMAXINFO> ()
			{}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Win::MinMaxInfo object with a RECT windows
			// structure.
			//------------------------------------------------------------------

			MinMaxInfo (const MINMAXINFO & minMax)
				: Sys::Struct<MINMAXINFO> (minMax)
			{}

			MinMaxInfo (const long maxX, const long maxY, const long maxWidth, const long maxHeight, const long maxTrackWidth, const long maxTrackHeight, const long minTrackWidth, const long minTrackHeight) ;

			//-----------------------------------------------------------------------
			// Obtains the maximun width of the window.
			//
			// Return value: The ptMaxSize.x data member of the MINMAXINFO structure.
			//-----------------------------------------------------------------------

			long GetMaxWidth () const 
			{
				return _struct.ptMaxSize.x ;
			}

			//-----------------------------------------------------------------------
			// Obtains the maximum height of the window.
			//
			// Return value: The ptMaxSize.y data member of the MINMAXINFO structure.
			//-----------------------------------------------------------------------

			long GetMaxHeight () const 
			{
				return _struct.ptMaxSize.y ;
			}

			//-----------------------------------------------------------------------
			// Obtains the maximum position of the left side of the window.
			//
			// Return value: The ptMaxPosition.x data member of the MINMAXINFO 
			//				 structure.
			//-----------------------------------------------------------------------

			long GetMaxPosX () const 
			{
				return _struct.ptMaxPosition.x ;
			}

			//-----------------------------------------------------------------------
			// Obtains the maximum position of the top of the window.
			//
			// Return value: The ptMaxPosition.y data member of the MINMAXINFO 
			//				 structure.
			//-----------------------------------------------------------------------

			long GetMaxPoxY () const 
			{
				return _struct.ptMaxPosition.y ;
			}

			//-----------------------------------------------------------------------
			// Obtains the minimum tracking width of the window.
			//
			// Return value: The ptMinTrackSize.x data member of the MINMAXINFO 
			//				 structure.
			//-----------------------------------------------------------------------

			long GetMinTrackWidth () const 
			{
				return _struct.ptMinTrackSize.x ;
			}

			//-----------------------------------------------------------------------
			// Obtains the minimum tracking height of the window.
			//
			// Return value: The ptMinTrackSize.y data member of the MINMAXINFO 
			//				 structure.
			//-----------------------------------------------------------------------

			long GetMinTrackHeight () const 
			{
				return _struct.ptMinTrackSize.x ;
			}

			//-----------------------------------------------------------------------
			// Obtains the maximun tracking width of the window.
			//
			// Return value: The ptMaxTrackSize.x data member of the MINMAXINFO 
			//				 structure.
			//-----------------------------------------------------------------------

			long GetMaxTrackWidth () const 
			{
				return _struct.ptMaxTrackSize.x ;
			}

			//-----------------------------------------------------------------------
			// Obtains the maximun tracking height of the window.
			//
			// Return value: The ptMaxTrackSize.y data member of the MINMAXINFO 
			//				 structure.
			//-----------------------------------------------------------------------

			long GetMaxTrackHeight () const 
			{
				return _struct.ptMaxTrackSize.y ;
			}

			//---------------------------------------------------------------------
			// Set the maximum width of the window..
			//
			// Parameters:
			// 
			// const long width -> The new maximum width.
			//---------------------------------------------------------------------

			void SetMaxWidth (const long width)    
			{
				_struct.ptMaxSize.x = width ;
			}

			//---------------------------------------------------------------------
			// Set the maximum height of the window..
			//
			// Parameters:
			// 
			// const long height -> The new maximum height.
			//---------------------------------------------------------------------

			void SetMaxHeight (const long height)   
			{
				_struct.ptMaxSize.y = height ;
			}

			//---------------------------------------------------------------------
			// Set the maximum position of the left side of the window..
			//
			// Parameters:
			// 
			// const long width -> The new maximumposition of the left size.
			//---------------------------------------------------------------------

			void SetMaxPoxX (const long x)        
			{
				_struct.ptMaxPosition.x = x ;
			}

			//---------------------------------------------------------------------
			// Set the maximum position of the top of the window..
			//
			// Parameters:
			// 
			// const long width -> The new maximum position of the top.
			//---------------------------------------------------------------------

			void SetMaxPoxY (const long y)        
			{
				_struct.ptMaxPosition.y = y ;
			}

			//---------------------------------------------------------------------
			// Set the minimun tracking width of the the window..
			//
			// Parameters:
			// 
			// const long width -> The new minimum tracking width.
			//---------------------------------------------------------------------

			void SetMinTrackWidth (const long width)    
			{
				_struct.ptMinTrackSize.x = width ;
			}

			//---------------------------------------------------------------------
			// Set the minimun tracking height of the the window..
			//
			// Parameters:
			// 
			// const long width -> The new minimum tracking height.
			//---------------------------------------------------------------------

			void SetMinTrackHeight (const long height)   
			{
				_struct.ptMinTrackSize.y = height ;
			}

			//---------------------------------------------------------------------
			// Set the maximum tracking width of the the window..
			//
			// Parameters:
			// 
			// const long width -> The new maximum tracking width.
			//---------------------------------------------------------------------

			void SetMaxTrackWidth (const long width)    
			{
				_struct.ptMaxTrackSize.x = width ;
			}

			//---------------------------------------------------------------------
			// Set the maximum tracking height of the the window..
			//
			// Parameters:
			// 
			// const long width -> The new maximum tracking height.
			//---------------------------------------------------------------------

			void SetMaxTrackHeight (const long height)   
			{
				_struct.ptMaxTrackSize.y = height ;
			}
		} ;

		//---------------------------------------------------------------------------
		// Win::ScrollInfo encapsulates a	SCROLLINFO structure through private 
		// inheritance.
		//
		// Dara members of SCROLLINFO:
		//
		// cbSize    -> Size of a SCROLLINFO structure.
		// fMask     -> Indicate which data members must be set\retrived.
		// nMin      -> Minimum scrolling position.
		// nMax      -> Maximum scrolling position.
		// nPage     -> Page size.
		// nPos      -> Position of the thumb of the scrollbar.
		// nTrackPos -> Position of the thumb of the scrollbar while the user is
		//              dragging it.
		//---------------------------------------------------------------------------

		class ScrollInfo : public Sys::Struct<SCROLLINFO>
		{
		public:

			//------------------------------------------------------------------
			// Constructor.
			//------------------------------------------------------------------

			ScrollInfo ()
				: Sys::Struct<SCROLLINFO> ()
			{
				_struct.cbSize = sizeof (SCROLLINFO) ;
			}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Win::MinMaxInfo object with a RECT windows
			// structure.
			//------------------------------------------------------------------

			ScrollInfo (const SCROLLINFO & scroll)
				: Sys::Struct<SCROLLINFO> (scroll)
			{
				_struct.cbSize = sizeof (SCROLLINFO) ;
			}

			ScrollInfo (const int min, const int max, const int page, const int pos, const int trackPos, const unsigned int mask) ;

			//-----------------------------------------------------------------------
			// Obtains the minimum scrolling value of the scrollbar.
			//
			// Return value: The nMin data member of the SCROLLINFO structure.
			//-----------------------------------------------------------------------

			int GetMinRange () const 
			{
				return _struct.nMin ;
			}

			//-----------------------------------------------------------------------
			// Obtains the maximum scrolling value of the scrollbar.
			//
			// Return value: The nMax data member of the SCROLLINFO structure.
			//-----------------------------------------------------------------------

			int GetMaxRange () const 
			{
				return _struct.nMax ;
			}

			//-----------------------------------------------------------------------
			// Obtains the page size of the scrollbar.
			//
			// Return value: The nPage data member of the SCROLLINFO structure.
			//-----------------------------------------------------------------------

			UINT GetPageSize () const 
			{
				return _struct.nPage ;
			}

			//-----------------------------------------------------------------------
			// Obtains the position of the thumb of the scrollbar.
			//
			// Return value: The nPos data member of the SCROLLINFO structure.
			//-----------------------------------------------------------------------

			int GetPosition () const 
			{
				return _struct.nPos ;
			}

			//-----------------------------------------------------------------------
			// Obtains the position of the thumb of the scrollbar as the user is 
			// dragging it.
			//
			// Return value: The nMin data member of the SCROLLINFO structure.
			//-----------------------------------------------------------------------

			int GetTrackingPosition () const 
			{
				return _struct.nTrackPos ;
			}

			//-----------------------------------------------------------------------
			// Obtains the mask value.
			//
			// Return value: The fMask data member of the SCROLLINFO structure.
			//-----------------------------------------------------------------------

			UINT GetMask () const 
			{
				return _struct.fMask ;
			}

			//-----------------------------------------------------------------------
			// Sets the minimum scrolling value of the scrollbar.
			//
			// Parameters: 
			//
			// const int min -> The new minimum scrolling value. 
			//-----------------------------------------------------------------------

			void SetMinRange (const int min)       
			{
				_struct.nMin = min ;
			}

			//-----------------------------------------------------------------------
			// Sets the maximum scrolling value of the scrollbar.
			//
			// Parameters: 
			//
			// const int max -> The new maximum scrolling value. 
			//-----------------------------------------------------------------------

			void SetMaxRange (const int max)       
			{
				_struct.nMax = max ;
			}

			//-----------------------------------------------------------------------
			// Sets the page size of the scroll bar.
			//
			// Parameters: 
			//
			// const int max -> The new page value value. 
			//-----------------------------------------------------------------------

			void SetPageSize (const UINT pageSize) 
			{
				_struct.nPage = pageSize ;
			}

			//-----------------------------------------------------------------------
			// Sets the position of the thumb of the scrollbar.
			//
			// Parameters: 
			//
			// const int max -> The new position of the thumb. 
			//-----------------------------------------------------------------------

			void SetPosition (const int pos)       
			{
				_struct.nPos = pos ;
			}

			//-----------------------------------------------------------------------
			// Sets the position of the thumb of the scrollbar as the user is
			// dragging it.
			//
			// Parameters: 
			//
			// const int max -> The new position of the thumb as the user is 
			//                  dragging it. 
			//-----------------------------------------------------------------------

			void SetTrackingPosition (const int trackPos)  
			{
				_struct.nTrackPos = trackPos;
			}

			//-----------------------------------------------------------------------
			// Sets the new flag value
			//
			// Parameters: 
			//
			// const int max -> The new flag value.
			//-----------------------------------------------------------------------

			void SetMask (const UINT mask)     
			{
				_struct.fMask = mask ;
			}

		} ;
	}

#endif