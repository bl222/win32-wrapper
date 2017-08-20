#include "wincanvas.h"

//---------------------------------------------------------------------------------------
// Constructor.  Innitialize the object with the parameters.
//
// Parameters:
//
// const int tabLenght               -> The tab lenght
// const int leftMargin              -> The left margin.
// const int rightMargin             -> The right margin.
// const UINT const UINT lenghtDrawn -> The lenght drawn.
//---------------------------------------------------------------------------------------

Win::DrawTextParams::DrawTextParams (const int tabLenght, const int leftMargin, const int rightMargin, const UINT lengthDrawn)
{
	_struct.iTabLength    = tabLenght ;
	_struct.iLeftMargin   = leftMargin ;
	_struct.iRightMargin  = rightMargin ;
	_struct.uiLengthDrawn = lengthDrawn ;
	_struct.cbSize = sizeof (DRAWTEXTPARAMS) ;
}

//--------------------------------------------------------------------
// Obtains the current position.
//
// Return value: The  current position.
//--------------------------------------------------------------------

Win::Point Win::Canvas::GetCurrentPositon () const
{
	Win::Point p ;

	if (::GetCurrentPositionEx (_h, p) == 0)
		throw Win::Exception (TEXT("The method GetCurrentPosition was unsuccessful")) ;

	return p ;
}

//--------------------------------------------------------------------
// Draws a line between two points.
//
// Return value:  True if the method succeed, else false.
//
// Parameters:
//
// const int x1 -> X coordinate of the first point.
// const int y1 -> Y coordinate of the first point.
// const int x2 -> X coordinate of the second point.
// const int y2 -> Y coordinate of the second point.
//--------------------------------------------------------------------

void Win::Canvas::Line (const int x1, const int y1, const int x2, const int y2)  const
{
	if (::MoveToEx (_h, x1, y1, 0) == 0)
		throw Win::Exception (TEXT("The method Line () was unsuccessful")) ;
		
	if (::LineTo (_h, x2, y2) == 0)
		throw Win::Exception (TEXT("The method Line () was unsuccessful")) ;
}

//-----------------------------------------------------------------------
// Selects a region as the current clipping region. 
//
// Return value:  A numerical value describing the new clipping region.
//
// Parameters:
//
// const Win::Region::Handle regio -> Handle of the region.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::SelectClipRegion (const Win::Region::Handle region) const 
{
	int clip ;
				
	clip = ::SelectClipRgn (_h, region) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method SelectClipRegion was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
}

//-----------------------------------------------------------------------
// Intersects the current clipping region with a rectangle.
//
// Return value: Return value:  A numerical value describing the new 
//				 clipping region.
//
// Parameters:
//
// const int xLeft    -> X coordinate of the upper left conner of the 
//					     rectangle.
// const int yTop     -> Y coordinate of the upper left conner of the 
//					     rectangle.
// const int xRight   -> X coordinate of the lower right conner of the 
//					     rectangle.
// const int yBottom -> Y coordinate of the lower right conner of the 
//				     	rectangle.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::IntersectClipRect (const int xLeft, const int yTop, const int xRight, const int yBottom) const 
{
	int clip ;
				
	clip = ::IntersectClipRect (_h, xLeft, yTop, xRight, yBottom) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method IntersectClipRect was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
}

//-----------------------------------------------------------------------
// Intersects the current clipping region with a rectangle.
//
// Return value: Return value:  A numerical value describing the new 
//				 clipping region.
//
// Parameters:
//
// const Win::Rect & rect -> The rectangle that will intersect the clipping
//							 region.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::IntersectClipRect (const Win::Rect & rect) const 
{
	int clip ;
			
	clip = ::IntersectClipRect (_h, rect.GetLeft (), rect.GetTop (), rect.GetRight (), rect.GetBottom ()) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method IntersectClipRect was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
}

//-----------------------------------------------------------------------
// Excludes a rectangle from the current clipping region.
//
// Return value: Return value:  A numerical value describing the new 
//				 clipping region.
//
// Parameters:
//
// const int xLeft    -> X coordinate of the upper left conner of the 
//					     rectangle.
// const int yTop     -> Y coordinate of the upper left conner of the 
//					     rectangle.
// const int xRight   -> X coordinate of the lower right conner of the 
//					     rectangle.
// const int yBottom -> Y coordinate of the lower right conner of the 
//				     	rectangle.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::ExcludeClipRect (const int xLeft, const int yTop, const int xRight, const int yBottom) const 
{
	int clip ;
				
	clip = ::ExcludeClipRect (_h, xLeft, yTop, xRight, yBottom) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method ExcludeClipRect was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
}

//-----------------------------------------------------------------------
// Exclude the current clipping region with a rectangle.
//
// Return value: Return value:  A numerical value describing the new 
//				 clipping region.
//
// Parameters:
//
// const Win::Rect & rect -> The rectangle that will exclude the clipping
//							 region.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::ExcludeClipRect (const Win::Rect & rect) const 
{
	int clip ;
			
	clip = ::ExcludeClipRect (_h, rect.GetLeft (), rect.GetTop (), rect.GetRight (), rect.GetBottom ()) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method IntersectClipRect was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
}

//-----------------------------------------------------------------------
// Moves the current clipping region.
//
// Return value: Return value:  A numerical value describing the new 
//				 clipping region.
//
// Parameters:
//
// const int x -> Horizontal offset.
// const int y -> Vertical offset.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::OffsetClipRegion (const int x, const int y) const 
{
	int clip ;
				
	clip = ::OffsetClipRgn (_h, x, y) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method OffsetClipRect was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
}

//-----------------------------------------------------------------------
// Obtains the rectangle containing the clipping region.
//
// Return value: Return value:  A numerical value describing the new 
//				 clipping region.
//
// Parameters:
//
// Win::Rect * rect -> Will contain the coordinates of the rectangle.
//-----------------------------------------------------------------------

Win::Canvas::Clipping Win::Canvas::GetClipBox (Win::Rect & rect) const 
{
	int clip ;
		
	clip = ::GetClipBox (_h, reinterpret_cast <LPRECT> (&rect)) ;

	if (clip == ERROR)
		throw Win::Exception (TEXT("The method GetClipBox was unsuccessful")) ;

	return static_cast <Win::Canvas::Clipping> (clip) ;
} 

//-----------------------------------------------------------------------
// Obtains some info about the current pen.
//
// Return value:  The info on the pen.
//-----------------------------------------------------------------------

Win::Pen::Data Win::Canvas::GetPenData () const 
{
	Win::Pen::Data data ;

	if (::GetObject (GetPenHandle (), sizeof (LOGPEN), reinterpret_cast <LOGPEN *> (&data)) == 0)
		throw Win::Exception (TEXT("The method GetPenData was unsuccessful")) ;

	return data ;
}

//-----------------------------------------------------------------------
// Obtains some info about the current pen.
//
// Return value:  The info on the pen.
//-----------------------------------------------------------------------

Win::ExtendedPen::Color::Data Win::Canvas::GetExtendedPenColorData () const 
{
	Win::ExtendedPen::Color::Data data ;

	if (::GetObject (GetExtendedPenColorHandle (), sizeof (EXTLOGPEN), reinterpret_cast <EXTLOGPEN *> (&data)) == 0)
		throw Win::Exception (TEXT("The method GetExtendedPenColorData was unsuccessful")) ;

	return data ;
}

//-----------------------------------------------------------------------
// Obtains some info about the current brush.
//
// Return value:  The info on the brush.
//-----------------------------------------------------------------------

Win::Brush::Solid::Data Win::Canvas::GetSolidBrushData () const 
{
	Win::Brush::Solid::Data data ;

	if (::GetObject (GetSolidBrushHandle (), sizeof (LOGBRUSH), reinterpret_cast <LOGBRUSH *> (&data)) == 0)
		throw Win::Exception (TEXT("The method GetSolidBrushData was unsuccessful")) ;

	return data ;
}
			
//-----------------------------------------------------------------------
// Obtains some info about the current brush.
//
// Return value:  The info on the brush.
//-----------------------------------------------------------------------

Win::Brush::Hatch::Data Win::Canvas::GetHatchBrushData () const 
{
	Win::Brush::Hatch::Data data ;

	if (::GetObject (GetHatchBrushHandle (), sizeof (LOGBRUSH), reinterpret_cast <LOGBRUSH *> (&data)) == 0)
		throw Win::Exception (TEXT("The method GetHatchBrushData was unsuccessful")) ;

	return data ;
}			

//-----------------------------------------------------------------------
// Obtains some info about the current font.
//
// Return value:  The info on the font.
//-----------------------------------------------------------------------

Win::Font::Data Win::Canvas::GetFontData () const 
{
	Win::Font::Data data ;

	if (::GetObject (GetFontHandle (), sizeof (LOGFONT), reinterpret_cast <LOGFONT *> (&data)) == 0)
		throw Win::Exception (TEXT("The method GetFontData was unsuccessful")) ;

	return data ;
}

//--------------------------------------------------------------------
// Obtains various information about the current physical font in a 
// Win::TextMetrics object.  
//
// Return value:  The informations about the current physical font.
//--------------------------------------------------------------------

Win::Font::TextMetrics Win::Canvas::GetTextMetrics () const 
{
	Win::Font::TextMetrics textMetrics ;

	if (::GetTextMetrics (_h, reinterpret_cast <LPTEXTMETRIC> (&textMetrics) ) == 0)
		throw Win::Exception (TEXT("The method GetTextMetrics was unsuccessful")) ;

	return textMetrics ;
}

//--------------------------------------------------------------------
// Obtains the viewport origin.
//
// Return value:  the viewport origin.
//--------------------------------------------------------------------

Win::Point Win::Canvas::GetViewportOrigin () const 
{
	Win::Point p ;

	if (::GetViewportOrgEx (_h, reinterpret_cast <LPPOINT> (&p)) == 0)
		throw Win::Exception (TEXT("The method GetViewportOrigin was unsuccessful")) ;

	return p ;
}

//--------------------------------------------------------------------
// Obtains the viewport extend.
//
// Return value: the viewport extend.
//--------------------------------------------------------------------

Win::Size Win::Canvas::GetViewportExtend () const 
{
	Win::Size size ;

	if (::GetViewportExtEx (_h, reinterpret_cast <LPSIZE> (&size) ) == 0)
		throw Win::Exception (TEXT("The method GetViewportExtend was unsuccessful")) ;

	return size ;
}

//--------------------------------------------------------------------
// Obtains the window origin.
//
// Return value: the window origin.
//--------------------------------------------------------------------

Win::Point Win::Canvas::GetWindowOrigin () const 
{
	Win::Point p ;

	if (::GetWindowOrgEx (_h, reinterpret_cast <LPPOINT> (&p)) == 0)
		throw Win::Exception (TEXT("The method GetWindowOrigin was unsuccessful")) ;

	return p ;
}

//--------------------------------------------------------------------
// Obtains the window extend.
//
// Return value:  the window extend.
//--------------------------------------------------------------------

Win::Size Win::Canvas::GetWindowExtend () const 
{
	Win::Size size ;

	if (::GetWindowExtEx(_h, reinterpret_cast <LPSIZE> (&size) ) == 0)
		throw Win::Exception (TEXT("The method GetWindowExtend was unsuccessful")) ;

	return size ;
}

//--------------------------------------------------------------------
// Obtains the brush origin..
//
// Return value: the brush origin.
//--------------------------------------------------------------------

Win::Point Win::Canvas::GetBrushOrigin () const 
{
	Win::Point p ;

	if (::GetBrushOrgEx (_h, reinterpret_cast<LPPOINT> (&p)) == 0)
		throw Win::Exception (TEXT("The method GetBrushOrigin was unsuccessful")) ;

	return p ;
}
