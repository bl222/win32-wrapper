#include "winencapsulation.h"

//---------------------------------------------------------------------
// Constructor.  Creates a new Win::Rect object from 4 int values.
//
// parameters:
//
// const Win::Rect & rect -> Used to create a new Win::Rect object.
//---------------------------------------------------------------------

Win::Rect::Rect (const LONG l, const LONG r, const LONG t, const LONG b)
{
	_struct.left   = l ;
	_struct.right  = r ;
	_struct.top    = t ;
	_struct.bottom = b ;
}

//---------------------------------------------------------------------
// Constructor.  Creates a new Win::Rect object from a RECTL structure.
//---------------------------------------------------------------------

Win::Rect::Rect (const RECTL & rect)
{
	_struct.left   = rect.left ;
	_struct.right  = rect.right ;
	_struct.top    = rect.top ;
	_struct.bottom = rect.bottom ;
}

//---------------------------------------------------------------------
// Determines if a point is inside the rectangle represented by the
// Win::Rect object.
//
// Return value:  True if the point is inside the rectangle, else false.
//
// Parameters:
// 
// const Win::Point & point -> The point which may or may not be inside
//							   the rectangle.
//---------------------------------------------------------------------

void Win::Rect::PointInside (const Win::Point & point) const
{
	POINT  p ;
	p.x = point.GetX () ;
	p.y = point.GetY () ;

	if (::PtInRect (&_struct, p) == 0)
		throw Win::Exception (TEXT("Error, Could not determine if the point is inside the rectangle.")) ;

}

//---------------------------------------------------------------------
// Constructor.  Creates a new Win::MinMaxInfo object from 8 long values.
//---------------------------------------------------------------------

Win::MinMaxInfo::MinMaxInfo (const long maxX, const long maxY, const long maxWidth, const long maxHeight, const long maxTrackWidth, const long maxTrackHeight, const long minTrackWidth, const long minTrackHeight)
{
	_struct.ptMaxSize.x		 = maxWidth ;
	_struct.ptMaxSize.y		 = maxHeight ;
	_struct.ptMaxPosition.x  = maxX ;
	_struct.ptMaxPosition.y  = maxY ;
	_struct.ptMaxTrackSize.x = maxTrackWidth ;
	_struct.ptMaxTrackSize.y = maxTrackHeight ;
	_struct.ptMinTrackSize.x = minTrackWidth ;
	_struct.ptMinTrackSize.y = minTrackHeight ;

}

//---------------------------------------------------------------------
// Constructor.  Creates a new Win::ScrollInfo object from individuals
// values.
//---------------------------------------------------------------------

Win::ScrollInfo::ScrollInfo (const int min, const int max, const int page, const int pos, const int trackPos, const unsigned int mask)
{
	_struct.nMin      = min ;
	_struct.nMax      = max ;
	_struct.nPage     = page ;
	_struct.nPos      = pos ;
	_struct.nTrackPos = trackPos ;
	_struct.fMask     = mask ;
	_struct.cbSize    = sizeof (SCROLLINFO) ;
}
