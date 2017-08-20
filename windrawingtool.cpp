#include <fstream>
#include "windrawingtool.h"
#include "wincanvas.h"
#include "winglobalhandle.h"
#include "winmessagebox.h"

//---------------------------------------------------------------------
// Gives the Win::Palette::Data object a new size.
// 
// Parameters:
// 
// const unsigned short size -> The new size.
//---------------------------------------------------------------------	

void Win::Palette::Data::Resize (const unsigned short size)
{
	// Make sure size is valid.
	assert (size != 0 && size <= 256) ;

	Free () ;
	// Create new LOGPALETTE.
	_pal                = reinterpret_cast <LOGPALETTE *> (malloc (sizeof (LOGPALETTE) + (size - 1) * sizeof (PALETTEENTRY))) ;
	_pal->palNumEntries = size ;
	_pal->palVersion    = 0x0300 ;
}

//---------------------------------------------------------------------
// Obtains the color of one of the entries of the Win::Palette::Data object.
// 
// Parameters:
// 
// const int pos              -> The position of the entry to set. 
//								 First entry is 0.
//---------------------------------------------------------------------	

Win::Color Win::Palette::Data::GetEntry (const int pos) const
{
	return RGB (_pal->palPalEntry[pos].peRed, _pal->palPalEntry[pos].peGreen, _pal->palPalEntry[pos].peBlue) ;
}

//---------------------------------------------------------------------
// Sets one of the entries of the Win::Palette::Data object.
// 
// Parameters:
// 
// const int pos              -> The position of the entry to set. 
//								 First entry is 0.
// const unsigned short red   -> Red color value of the entry.
// const unsigned short green -> Green color value of the entry.
// const unsigned short blue  -> Blue color value of the entry.
// const unsigned short flag  -> Attributes of the entry.
//---------------------------------------------------------------------	

void Win::Palette::Data::SetEntry (const int pos, const BYTE red, const BYTE green, const BYTE blue, const Win::Palette::Flag flag)
{
	assert (_pal && pos < _pal->palNumEntries && pos >= 0) ; 
				
	_pal->palPalEntry[pos].peRed   = red ;
	_pal->palPalEntry[pos].peGreen = green ;
	_pal->palPalEntry[pos].peBlue  = blue ;
	_pal->palPalEntry[pos].peFlags = flag ;
}

//---------------------------------------------------------------------
// Sets one of the entries of the Win::Palette::Data object.
// 
// Parameters:
// 
// const int pos              -> The position of the entry to set. 
//								 First entry is 0.
// Win::RGBColor & colortry.  -> Color of the entry.
// const unsigned short flag  -> Attributes of the entry.
//---------------------------------------------------------------------	

void Win::Palette::Data::SetEntry (const int pos, Win::RGBColor & color, const Win::Palette::Flag flag)
{
	assert (_pal && pos < _pal->palNumEntries && pos >= 0) ; 
				
	_pal->palPalEntry[pos].peRed   = color.GetRed   () ;
	_pal->palPalEntry[pos].peGreen = color.GetGreen () ;
	_pal->palPalEntry[pos].peBlue  = color.GetBlue  () ;
	_pal->palPalEntry[pos].peFlags = flag ;
}
			
//---------------------------------------------------------------------
// Fills the Win::Palette::Data object with the entries of the system 
// palette.
//---------------------------------------------------------------------

void Win::Palette::Data::CreateFromSystemPalette ()
{
	assert (_pal) ;

	int i ;

	for (i = 0; i < _pal->palNumEntries; i++)
	{
		_pal->palPalEntry[i].peRed   = i ;
		_pal->palPalEntry[i].peGreen = 0 ;
		_pal->palPalEntry[i].peBlue  = 0 ;
		_pal->palPalEntry[i].peFlags = PC_EXPLICIT ; // System palette entry.
	}
}

//--------------------------------------------------------------------
// Obtains an handle of one of the stockbrush.
// 
// Parameters:
//
// const int id -> Identify the stock brush that must be load.
//--------------------------------------------------------------------

HBRUSH Win::Brush::Solid::StockLoader::Load (const int id)
{
	HBRUSH h = reinterpret_cast <HBRUSH> (::GetStockObject (id)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error!  Could not obtain a stock pen")) ;

	return h ;
}

//--------------------------------------------------------------------
// Creates a new brush and obtains a StrongHandle for it.
// 
// Return value:  A Win::Brush::StrongHandle object representing the new
//				  brush.
//--------------------------------------------------------------------

Win::Brush::Solid::StrongHandle Win::Brush::Solid::Creator::Create ()
{
	HBRUSH h = ::CreateBrushIndirect (&_logBrush) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a brush.")) ; 

	 return Win::Brush::Solid::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new brush and obtains a StrongHandle for it.
// 
// Return value:  A Win::Brush::StrongHandle object representing the new
//				  brush.
//--------------------------------------------------------------------

Win::Brush::Solid::StrongHandle Win::Brush::Solid::Creator::Create (Win::Color & color)
{
	
	HBRUSH h = ::CreateSolidBrush (color) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a brush.")) ; 

	 return Win::Brush::Solid::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new hatch brush and obtains a StrongHandle for it.
// 
// Return value:  A Win::Brush::StrongHandle object representing the new
//				  brush.
//--------------------------------------------------------------------

Win::Brush::Hatch::StrongHandle Win::Brush::Hatch::Creator::Create (const Win::Color & color, const Win::Brush::Hatch::Type type)
{
	HBRUSH h = ::CreateHatchBrush (static_cast <int> (type), color) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a brush.")) ; 

	 return Win::Brush::Hatch::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new pattern brush and obtains a StrongHandle for it.
// 
// Return value:  A Win::Brush::Pattern::StrongHandle object representing the new
//				  brush.
//
//
// parameters:
//
// Win::Bitmap::DDB::StrongHandle handle -> The bitmap used to create the
//											pattern brush.
//--------------------------------------------------------------------

Win::Brush::Pattern::StrongHandle Win::Brush::Pattern::Creator::Create (Win::Bitmap::DDB::StrongHandle handle)
{
	
	HBRUSH h = ::CreatePatternBrush (handle) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a brush.")) ; 
	


	 return Win::Brush::Pattern::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new pattern brush and obtains a StrongHandle for it.
// 
// Return value:  A Win::Brush::Pattern::StrongHandle object representing the new
//				  brush.
//
//
// parameters:
//
// Win::Bitmap::DIBSection::StrongHandle handle -> The bitmap used to create the
//											pattern brush.
//--------------------------------------------------------------------

Win::Brush::Pattern::StrongHandle Win::Brush::Pattern::Creator::Create (Win::Bitmap::DIBSection::StrongHandle handle)
{
	HBRUSH h = ::CreatePatternBrush (handle) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a brush.")) ; 

	 return Win::Brush::Pattern::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Obtains an handle of one of the stockpen.
// 
// Parameters:
//
// const int id -> Identify the stock pen that must be load.
//--------------------------------------------------------------------

HPEN Win::Pen::StockLoader::Load (const int id) 
{
	HPEN h = reinterpret_cast <HPEN> (::GetStockObject (id)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error!  Could not obtain a stock pen")) ;

	return h ;
}

//--------------------------------------------------------------------
// Changes the color, width and style of the pen that will be created.
// 
// Parameters:
//
// const Win::Color & color    -> The new color.
// const Win::Pen::Style style -> The new style.
// const LONG width            -> The new width.
//--------------------------------------------------------------------

void Win::Pen::Creator::SetAllData (const Win::Color & color, const Win::Pen::Style style, const LONG width)
{
	_logPen.lopnColor   = color ;
	_logPen.lopnStyle   = style ;
	_logPen.lopnWidth.x = width ;
}

//--------------------------------------------------------------------
// Creates a new pen and obtains a StrongHandle for it.
// 
// Return value:  A Win::Pen::StrongHandle object representing the new
//				  pen.
//--------------------------------------------------------------------

Win::Pen::StrongHandle Win::Pen::Creator::Create (const Win::Color & color, const Win::Pen::Style style, const LONG width)
{
	HPEN h = ::CreatePen (static_cast <int> (style), width, color) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a pen.")) ; 

	 return Win::Pen::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new pen and obtains a StrongHandle for it.
// 
// Return value:  A Win::Pen::StrongHandle object representing the new
//				  pen.
//--------------------------------------------------------------------

Win::Pen::StrongHandle Win::Pen::Creator::Create ()
{
	HPEN h = ::CreatePenIndirect (&_logPen) ;

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a pen.")) ; 

	 return Win::Pen::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Changes all the data of the pen that will be created.
//--------------------------------------------------------------------

void Win::ExtendedPen::Color::Creator::SetAllData (const Win::Color & color, const Win::Pen::Style style, const Win::ExtendedPen::Type type,
				const Win::ExtendedPen::EndCap endCap, const Win::ExtendedPen::Join join,const UINT width)
{
	_logBrush.lbColor = color ;
	_width  = width ;
	_style  = style ;
	_type   = type ;
	_endCap = endCap ;
	_join   = join ;
}

//--------------------------------------------------------------------
// Creates a new extended pen and obtains a StrongHandle for it.
// 
// Return value:  A Win::ExtendedPen::Color::StrongHandle object representing the new
//				  brush.
//--------------------------------------------------------------------

Win::ExtendedPen::Color::StrongHandle Win::ExtendedPen::Color::Creator::Create ()
{

	HPEN h = ::ExtCreatePen (_style | _join | _endCap | _type,
							 _width, &_logBrush, 0, NULL);

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a extended pen.")) ; 

	 return Win::ExtendedPen::Color::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new extended pen and obtains a StrongHandle for it.
// 
// Return value:  A Win::ExtendedPen::Color::StrongHandle object representing the new
//				  brush.
//--------------------------------------------------------------------

Win::ExtendedPen::Color::StrongHandle Win::ExtendedPen::Color::Creator::Create (const Win::Color & color, const Win::Pen::Style style, const Win::ExtendedPen::Type type,
				const Win::ExtendedPen::EndCap endCap, const Win::ExtendedPen::Join join,const UINT width)
{

	LOGBRUSH logBrush ;
	logBrush.lbColor = color ;

	HPEN h = ::ExtCreatePen (style | join | endCap | type,
							 width, &logBrush, 0, NULL);

	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a extended pen.")) ; 

	 return Win::ExtendedPen::Color::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Obtains an handle of one of the stockfont.
// 
// Parameters:
//
// const int id -> Identify the stock font that must be load.
//--------------------------------------------------------------------

HFONT Win::Font::StockLoader::Load (const int id) 
{
	HFONT h = reinterpret_cast <HFONT> (::GetStockObject (id)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error!  Could not obtain a stock font")) ;

	return h ;
}

//--------------------------------------------------------------------
// Changes all the data of the font that will be created.
//--------------------------------------------------------------------

void Win::Font::Creator::SetAllData (const std::tstring face, const Win::Font::CharSet charSet, const int height, const int width, const int escapement, const int orientation, 
	     const Win::Font::Weight weight, const bool italic, const bool underline, const bool strikeOut, 
	     const Win::Font::OutPrecis outputPrescision, const Win::Font::ClipPrecis clipPrescision, const Win::Font::Quality quality, 
	     const Win::Font::Pitch pitch, const Win::Font::Family family) 
{
	_logFont.lfWidth         = width ;
	_logFont.lfHeight        = height ;
	_logFont.lfOrientation   = orientation ;
	_logFont.lfQuality       = quality ;
	_logFont.lfClipPrecision = clipPrescision ;
	_logFont.lfOutPrecision  = outputPrescision ;
	_logFont.lfItalic        = italic ;
	_logFont.lfUnderline     = underline ;
	_logFont.lfStrikeOut     = strikeOut ;
	_logFont.lfEscapement    = escapement ;
	_logFont.lfWeight        = weight ;
	_logFont.lfCharSet       = charSet ;

	SetFamily      (family) ;
	SetPitch       (pitch) ;
	_tcscpy (_logFont.lfFaceName, face.c_str ()) ;
}

//--------------------------------------------------------------------
// Creates a new font.
//
// Return value: A strong handle representing the new font.
//--------------------------------------------------------------------

Win::Font::StrongHandle Win::Font::Creator::Create ()
{
   	 HFONT h = ::CreateFontIndirect (&_logFont) ;
	 if (h == NULL) 
		throw Win::Exception (TEXT("Error, could not create a font.")) ; 

	 return Win::Font::StrongHandle (h) ; 
}

//--------------------------------------------------------------------
// Creates a new font.
//
// Return value: A strong handle representing the new font.
//--------------------------------------------------------------------

/*Win::Font::StrongHandle Win::Font::Creator::Create (const std::tstring face, const Win::Font::CharSet charSet, const int height, const int width, const int escapement, const int orientation, 
	     const Win::Font::Weight weight, const bool italic, const bool underline, const bool strikeOut, 
	     const Win::Font::OutPrecis outputPrescision, const Win::Font::ClipPrecis clipPrescision, const Win::Font::Quality quality, 
	     const Win::Font::Pitch pitch, const Win::Font::Family family) 
{																									
   	 HFONT h = ::CreateFont (width, height, escapement, orientation, weight, italic, underline, strikeOut, charSet, outputPrescision, clipPrescision, quality, pitch | family, face.c_str ()) ;
	 if (h == Handle::NullValue ()) 
		throw Win::Exception ("Error, could not create a font.") ; 

	 return Win::Font::StrongHandle (h) ; 
}*/

//------------------------------------------------------------------
// Creates a rectangular region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::RectangleCreator::Create (const int xLeft, const int yTop, const int xRight, const int yBottom)
{
	HRGN h = ::CreateRectRgn (xLeft, yTop, xRight, yBottom) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a rectangular region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::RectangleCreator::Create ()
{
	HRGN h = ::CreateRectRgnIndirect (_rect) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a elliptic region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::EllipseCreator::Create ()
{
	HRGN h = ::CreateEllipticRgnIndirect (_rect) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a elliptic region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::EllipseCreator::Create (const int xLeft, const int yTop, const int xRight, const int yBottom)
{
	HRGN h = ::CreateEllipticRgn (xLeft, yTop, xRight, yBottom) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a round rectangle region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::RoundRectangleCreator::Create ()
{
	HRGN h = ::CreateRoundRectRgn (_rect.GetLeft (), _rect.GetTop (), _rect.GetRight (), _rect.GetBottom (), _eWidth, _eHeight) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a round rectangle region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::RoundRectangleCreator::Create (const int xLeft, const int yTop, const int xRight, const int yBottom, const int eWidth, const int eHeight)
{
	HRGN h = ::CreateRoundRectRgn (xLeft, yTop, xRight, yBottom, eWidth, eHeight) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a polygon region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::PolygonCreator::Create ()
{
	HRGN h = ::CreatePolygonRgn (reinterpret_cast <const POINT *> (_p), _nb, _mode) ;
	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a polygon region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::PolygonCreator::Create (Win::Point * p, const int nb, const Win::Polygon::FillMode mode)
{
	HRGN h = ::CreatePolygonRgn (reinterpret_cast <const POINT *> (p), nb, mode) ;
	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}


//------------------------------------------------------------------
// Creates a poly polygon region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::PolyPolygonCreator::Create ()
{
	HRGN h = ::CreatePolyPolygonRgn (reinterpret_cast <const POINT *> (_p), _nb, _nbPoly, _mode) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a poly polygon region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::PolyPolygonCreator::Create (Win::Point * p, int * nb,const int nbPoly, const Win::Polygon::FillMode mode)
{
	HRGN h = ::CreatePolyPolygonRgn (reinterpret_cast <const POINT *> (p), nb, nbPoly, mode) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates a path region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::PathCreator::Create (Win::Canvas & canvas)
{
	HRGN h = ::PathToRegion (canvas) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a region")) ;

	return Win::Region::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Combines two regions region.
//------------------------------------------------------------------

Win::Region::StrongHandle Win::Region::Combinator::Combine (Win::Region::Handle rgn1, Win::Region::Handle rgn2, Win::Region::CombineFlag flag)
{
	HRGN h   = ::CreateRectRgn (0, 0, 2, 2) ;

	int code =  ::CombineRgn (h, rgn1, rgn2, flag) ;

	if (code == ERROR)
		throw Win::Exception (TEXT("Error, could not combine 2 regions")) ;

	return Win::Region::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Obtains various information about the physical font in a 
// Win::TextMetrics object.  
//
// Parameters:
//
// Win::TextMetrics & textMetrics -> Will contain the information
//                                   about the physical font.
//--------------------------------------------------------------------

void Win::Font::Handle::GetTextMetrics (Win::Font::TextMetrics & textMetrics)
{
	Win::DisplayCanvas canvas ; // Create a canvas.

	Win::Font::Holder font (canvas, *this) ; // Select the font in the canvas.

	// Use the canvas to fill the Win::TextMetrics object.
	::GetTextMetrics (canvas, reinterpret_cast <LPTEXTMETRIC> (&textMetrics)) ;
}

//------------------------------------------------------------------
// Creates the halftone palette
//------------------------------------------------------------------

Win::Palette::StrongHandle Win::Palette::HalftoneCreator::Create (const Win::Canvas & canvas)
{
	HPALETTE h = ::CreateHalftonePalette (canvas) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a halftone palette")) ;

	return Win::Palette::StrongHandle (h) ;
}

//------------------------------------------------------------------
// Creates the palette
//------------------------------------------------------------------

Win::Palette::StrongHandle Win::Palette::Creator::Create (const Win::Palette::Data & data)
{
	HPALETTE h = ::CreatePalette (data) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a palette")) ;

	return Win::Palette::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Obtains the width of the bitmap.
//
// return value:  The width of the bitmap.
//--------------------------------------------------------------------

int Win::Bitmap::DDB::Handle::GetWidth () const
{
	BITMAP data ;

	::GetObject (_h, sizeof (BITMAP), &data) ;

	return data.bmWidth ;
}

//--------------------------------------------------------------------
// Obtains the height of the bitmap.
//
// return value:  The height of the bitmap.
//--------------------------------------------------------------------

int Win::Bitmap::DDB::Handle::GetHeight () const 
{
	BITMAP data ;

	::GetObject (_h, sizeof (BITMAP), &data) ;

	return data.bmHeight ;
}
					
//--------------------------------------------------------------------
// Obtains the width and height of the bitmap.
//
// parameters:
//
// int & width  -> Will contain the width of the bitmap.
// int & height -> Will contain the height of the bitmap.
//--------------------------------------------------------------------

void Win::Bitmap::DDB::Handle::GetDimension (int & width, int & height) const
{
	BITMAP data ;

	::GetObject (_h, sizeof (BITMAP), &data) ;

	width  = data.bmWidth ;
	height = data.bmHeight ;
}




//--------------------------------------------------------------------
// Creates a Monochrome bitmap.
//
// parameters:
//
// const void * bits -> Optionnal pointers on bits innitializing the bitmap.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Creator::CreateMonochrome (const void * bits)
{
	HBITMAP h = ::CreateBitmap (_width, _height, 1, 1, bits) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a monochrome bitmap")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Creates a bitmap compatible with a particular device context (canvas).
//
// parameters:
//
// Win::Canvas & canvas -> The device context with witch the bitmap
//						   will be compatible.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Creator::CreateCompatible (Win::Canvas & canvas)
{
	HBITMAP h = ::CreateCompatibleBitmap (canvas, _width, _height) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a monochrome bitmap")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Creates a Monochrome bitmap.
//
// parameters:
//
// const void * bits -> Optionnal pointers on bits innitializing the bitmap.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Creator::CreateMonochrome (const int width, const int height, const void * bits)
{
	HBITMAP h = ::CreateBitmap (width, height, 1, 1, bits) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a monochrome bitmap")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Creates a bitmap compatible with a particular device context (canvas).
//
// parameters:
//
// const int width      -> width of the bitmap.
// const int height     -> height of the bitmap.
// Win::Canvas & canvas -> The device context with witch the bitmap
//						   will be compatible.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Creator::CreateCompatible (const int width, const int height, Win::Canvas & canvas)
{
	HBITMAP h = ::CreateCompatibleBitmap (canvas, width, height) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create a monochrome bitmap")) ;



	return Win::Bitmap::DDB::StrongHandle (h) ;
}

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Creator::CreateCopy (Win::Bitmap::DDB::Handle ddbSrc)
{
	Win::Bitmap::DDB::Data data ;
	ddbSrc.GetData (data) ;

	HBITMAP h = ::CreateBitmapIndirect (data) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create copy of a bitmap")) ;

	Win::MemoryCanvas canvasSrc ;
	Win::MemoryCanvas canvasDest ;

	Win::Bitmap::DDB::Holder holdSrc  (canvasSrc, ddbSrc) ;
	Win::Bitmap::DDB::Holder holdDest (canvasDest, h) ;

	canvasDest.Blit (canvasSrc, 0, 0, data.GetWidth (), data.GetHeight ()) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a resource.
//
// Parameters:
//
// const int id -> The numerical Id of the resource.
//--------------------------------------------------------------------


Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Loader::LoadResource (const int id)
{
	HBITMAP h = reinterpret_cast <HBITMAP> (::LoadImage (_hInstance, MAKEINTRESOURCE (id), IMAGE_BITMAP,
							_width, _height, _flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a bitmap resource")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a resource.
//
// Parameters:
//
// const std::tstring  name -> The name of the resource.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Loader::LoadResource (const std::tstring  name)
{


	HBITMAP h = reinterpret_cast <HBITMAP> (::LoadImage (_hInstance, name.c_str (), IMAGE_BITMAP,
			_width, _height, _flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a bitmap resource")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a file.
//
// Parameters:
//
// const std::tstring  name -> The name of the file.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Loader::LoadFile (const std::tstring  name)
{
	UINT tmp = _flag ;
	tmp |= LR_LOADFROMFILE ;

	HBITMAP h = reinterpret_cast <HBITMAP> (::LoadImage (NULL, name.c_str (), IMAGE_BITMAP,
			_width, _height, tmp)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a bitmap file")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a resource.
//
// Parameters:
//
// const int id -> The numerical Id of the resource.
//--------------------------------------------------------------------


Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Loader::LoadResource (const HINSTANCE hInstance, const int width, const int height, const int id, const UINT flag)
{
	HBITMAP h = reinterpret_cast <HBITMAP> (::LoadImage (hInstance, MAKEINTRESOURCE (id), IMAGE_BITMAP,
							width, height, flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a bitmap resource")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a resource.
//
// Parameters:
//
// const std::tstring  name -> The name of the resource.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Loader::LoadResource (const HINSTANCE hInstance, const int width, const int height,const std::tstring  name, const UINT flag)
{


	HBITMAP h = reinterpret_cast <HBITMAP> (::LoadImage (hInstance, name.c_str (), IMAGE_BITMAP,
			width, height, flag)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a bitmap resource")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Loads bitmap from a file.
//
// Parameters:
//
// const std::tstring  name -> The name of the file.
//--------------------------------------------------------------------

Win::Bitmap::DDB::StrongHandle Win::Bitmap::DDB::Loader::LoadFile (const int width, const int height,const std::tstring  name, const UINT flag)
{
	UINT tmp = flag ;
	tmp |= LR_LOADFROMFILE ;

	HBITMAP h = reinterpret_cast <HBITMAP> (::LoadImage (NULL, name.c_str (), IMAGE_BITMAP,
			width, height, tmp)) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Could not load a bitmap file")) ;

	return Win::Bitmap::DDB::StrongHandle (h) ;
}

//--------------------------------------------------------------------
// Obtains the row length of the dib section.
//
// Return value:  The row lenght.
//--------------------------------------------------------------------

int Win::Bitmap::DIBSection::Handle::GetRowLenght ()
{
	assert (_h != NULL ) ;

	DIBSECTION ds ;

	::GetObject (_h, sizeof (DIBSECTION), &ds) ;

	return 4 * ((ds.dsBm.bmWidth * ds.dsBm.bmBitsPixel + 31) / 32) ;
}

//--------------------------------------------------------------------
// Obtains the number of colors in the color table.
//
// Return value:  The number of color.
//--------------------------------------------------------------------

int Win::Bitmap::DIBSection::Handle::GetNumColorsInTable ()
{
	assert (_h != NULL) ;

	DIBSECTION ds ;

	::GetObject (_h, sizeof (DIBSECTION), &ds) ;

	if (ds.dsBmih.biClrUsed != 0)
		return ds.dsBmih.biClrUsed ;
	else if (ds.dsBm.bmBitsPixel <= 8)
		return 1 << ds.dsBm.bmBitsPixel ;

	return 0 ;
}

//--------------------------------------------------------------------
// Obtains the compression method of the dib section.
//
// Return value:  The compression method.
//--------------------------------------------------------------------

int Win::Bitmap::DIBSection::Handle::GetCompression ()
{
	assert (_h != NULL) ;

	DIBSECTION ds ;

	::GetObject (_h, sizeof (DIBSECTION), &ds) ;

	return ds.dsBmih.biCompression ;
}

//--------------------------------------------------------------------
// Determines if the DIB section is compressed.
//
// Return value:  True if the DIB section is compressed, else false.
//--------------------------------------------------------------------

bool Win::Bitmap::DIBSection::Handle::IsNotCompressed ()
{
	assert (_h != NULL) ;
	
	DIBSECTION ds ;

	::GetObject (_h, sizeof (DIBSECTION), &ds) ;

	if (ds.dsBmih.biCompression == BI_RGB || ds.dsBmih.biCompression == BI_BITFIELDS)
		return true ;

	return false ;
}

//--------------------------------------------------------------------
// Changes one of the color in the color table.
//
// Parameters:
//
// int pos								   -> The position of the color 
//											  to be changed.
// Win::Bitmap::DIBSection::RGBQuad & quad -> Contains the new color.
//--------------------------------------------------------------------

void Win::Bitmap::DIBSection::Handle::SetColorInTable (int pos, Win::Bitmap::DIBSection::RGBQuad & quad)
{
	assert (_h != NULL) ;

	Win::MemoryCanvas        canvas (NULL) ;
	Win::Bitmap::DDB::Holder hold (canvas, _h) ;

	if (!::SetDIBColorTable (canvas, pos, 1, reinterpret_cast <RGBQUAD *> (&quad)))
		throw Win::Exception (TEXT("Could not set the DIB color table entry")) ;
}

//--------------------------------------------------------------------
// Obtains one of the color in the color table.
//
// Return value:  The desired color.
//
// Parameters:
//
// int pos								   -> The position of the desired 
//											  color 
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::RGBQuad Win::Bitmap::DIBSection::Handle::GetColorInTable (int pos)
{
	assert (_h != NULL) ;

	Win::MemoryCanvas                canvas (NULL) ;
	Win::Bitmap::DDB::Holder         hold (canvas, _h) ;
	Win::Bitmap::DIBSection::RGBQuad quad ;

	if (!::GetDIBColorTable (canvas, pos, 1, reinterpret_cast <RGBQUAD *> (&quad)))
		throw Win::Exception (TEXT("Could not get the DIB color table entry")) ;

	return quad ;
}

//--------------------------------------------------------------------
// Saves the DIB section to a file.
//
// Parameters:
//
// const std::tstring fileName -> Name of the DIBSection.
//--------------------------------------------------------------------

void Win::Bitmap::DIBSection::Handle::Save (const std::tstring fileName)
{
	BITMAPFILEHEADER bmfh ;
	int              totalSize ;
	DIBSECTION       ds ;

	std::string tmpFileName;

	#if defined (_UNICODE)
		BOOL useless;
		tmpFileName.reserve (tmpFileName.length() + 1);
		tmpFileName.resize (tmpFileName.length());

		::WideCharToMultiByte (CP_ACP, 0, fileName.c_str(),fileName.length(), &tmpFileName[0], tmpFileName.length(), "a", &useless);
	#else
		tmpFileName = fileName;
	#endif


	::GetObject (_h, sizeof (DIBSECTION), &ds) ;

	totalSize = (GetNumColorsInTable () * sizeof (RGBQUAD)) + ds.dsBmih.biSize + (GetHeight () * GetRowLenght ()) ;

	if (ds.dsBmih.biCompression == BI_BITFIELDS)
		totalSize = 3 * sizeof (DWORD) ;

	
	std::ofstream saver (tmpFileName.c_str (), std::ios::binary | std::ios::out) ;

	if (!saver)
		throw Win::Exception (TEXT("Could not open the bitmap file for saver")) ;

	bmfh.bfType = * (WORD *) "BM" ; //UNICODE WHAT
	bmfh.bfSize = sizeof (BITMAPFILEHEADER) + totalSize ;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = bmfh.bfSize - (GetHeight () * GetRowLenght ()) ;

	saver.write ((char *) &bmfh, sizeof (BITMAPFILEHEADER)) ;

	if (saver.fail ())
	{
		saver.close () ;

		throw Win::Exception (TEXT("Could not save the bitmap file")) ;
	}

	saver.write ((char *) &ds.dsBmih, sizeof (BITMAPINFOHEADER)) ;

	if (saver.fail ())
	{
		saver.close () ;

		throw Win::Exception (TEXT("Could not save the bitmap file")) ;
	}

	if (ds.dsBmih.biCompression == BI_BITFIELDS)
	{
		saver.write ((char *)&ds.dsBitfields, 3 * sizeof (DWORD)) ;
		if (saver.fail ())
		{
			saver.close () ;

			throw Win::Exception (TEXT("Could not save the bitmap file")) ;
		}
	}

	if (ds.dsBmih.biClrUsed != 0)
	{
		
		Win::Bitmap::DIBSection::RGBQuad quad ;
		for (unsigned int i = 0; i < ds.dsBmih.biClrUsed; i++)
		{
			quad = GetColorInTable (i) ;
			saver.write ((char *) reinterpret_cast<RGBQUAD *> (&quad), sizeof (RGBQUAD)) ;
			if (saver.fail ())
			{
				saver.close () ;

				throw Win::Exception (TEXT("Could not save the bitmap file")) ;
			}
		}
		
	}

	saver.write (reinterpret_cast <char *> (_bits), GetHeight () * GetRowLenght ()) ;
	if (saver.fail ())
	{
		saver.close () ;

		throw Win::Exception (TEXT("Could not save the bitmap file")) ;
	}

	saver.close () ;
}

BITMAPINFO * Win::Bitmap::DIBSection::Handle::CopyToClipboard ()
{
	DIBSECTION				  ds ;
	DWORD					  dibSize ;
	Win::Global::StrongHandle hGlobal ;
	BITMAPINFO *              packedDib ;
	RGBQUAD *				  rgb ;
	int                       numColor ;
	BYTE *                    bits ;

	if (_bits == NULL || _h == NULL)
		throw Win::Exception (TEXT("Error, could not send a DIB section to the clipboard")) ;

	::GetObject (_h, sizeof (DIBSECTION),  &ds) ;

	dibSize = (GetNumColorsInTable () * sizeof (RGBQUAD)) + ds.dsBmih.biSize + (GetHeight () * GetRowLenght ()) ;

	hGlobal = Win::Global::Creator::Create (dibSize, GHND | GMEM_SHARE) ;
	Win::Global::Lock lock (hGlobal, (void **) &packedDib) ;

	if (packedDib == NULL)
		throw Win::Exception (TEXT("Error, could not send a DIB section to the clipboard")) ;

	::CopyMemory (packedDib, &ds.dsBmih, sizeof (BITMAPINFOHEADER)) ;

	rgb = (RGBQUAD *) ((BYTE *) packedDib + sizeof (BITMAPINFOHEADER)) ;

	if (ds.dsBmih.biCompression == BI_BITFIELDS)
	{
		::CopyMemory (rgb, ds.dsBitfields, 3 * sizeof(DWORD)) ;

		rgb = (RGBQUAD *) ((BYTE *) rgb + 3 * sizeof (DWORD)) ;
	}

	numColor = GetNumColorsInTable () ;

	if (numColor != 0)
	{
		Win::MemoryCanvas canvas (NULL) ;
		Win::Bitmap::DIBSection::Holder hold (canvas, _h) ;

		::GetDIBColorTable (canvas, 0, numColor, rgb) ;
	}

	bits = (BYTE *) (rgb + numColor) ;

	::CopyMemory (bits, _bits, GetHeight () * GetRowLenght ()) ;

	HGLOBAL tmp = hGlobal.Release () ;
	return (BITMAPINFO *) tmp ;

}

void Win::Bitmap::DIBSection::StrongHandle::PasteFromClipboard (BITMAPINFO * packedDib)
{
	BYTE *      bits ;
	DWORD       infoSize = 0 ;
	DWORD       maskSize = 0;
	DWORD       colorSize = 0;
	int         bitCount = 0;

	if (packedDib == 0)
	{
		throw Win::Exception (TEXT("Error, could not pas a DIB section from the clipboard")) ;
	}

	infoSize = packedDib->bmiHeader.biSize ;

	if (infoSize != sizeof (BITMAPCOREHEADER) && infoSize != sizeof (BITMAPINFOHEADER) && infoSize != sizeof (BITMAPV4HEADER))
	{
		throw Win::Exception (TEXT("Error, could not paste a DIB section")) ;
	}

	if (infoSize == sizeof (BITMAPINFOHEADER) && packedDib->bmiHeader.biCompression == BI_BITFIELDS)
	{
		maskSize = 3 * sizeof (DWORD) ;
	}
	else
	{
		maskSize = 0 ;
	}


	if (infoSize == sizeof (BITMAPCOREHEADER))
	{
		bitCount = ((BITMAPCOREHEADER *) packedDib)->bcBitCount ;

		if (bitCount <= 8)
		{
			colorSize = (1 << bitCount) * sizeof (RGBTRIPLE) ;
		}
		else
		{
			colorSize = 0 ;
		}
	}
	else
	{
		if (packedDib->bmiHeader.biClrUsed > 0)
		{
			colorSize = packedDib->bmiHeader.biClrUsed * sizeof (RGBQUAD) ;
		}
		else if (packedDib->bmiHeader.biBitCount <= 8)
		{
			colorSize = (1 << packedDib->bmiHeader.biBitCount) * sizeof (RGBQUAD) ;
		}
		else
			colorSize = 0 ;
	}
	

	bits = (BYTE *) packedDib ;
		;
	bits += infoSize + maskSize + colorSize ;

	_h = ::CreateDIBSection (NULL, packedDib, DIB_RGB_COLORS, reinterpret_cast <void **> (&_bits),NULL, 0);

	if (_h == NULL || bits == NULL)
		throw Win::Exception (TEXT("Error, could not paste a DIB section from the clipboard")) ;

	::CopyMemory (_bits, bits,GetHeight () * GetRowLenght ()) ;
}

//--------------------------------------------------------------------
// Loads a DIB section from a file.
//
// Return value:  A StrongHandle on the DIB section.
//
// Parameters:
//
// const std::tstring fileName -> file name of the DIBSection.
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::StrongHandle Win::Bitmap::DIBSection::Loader::LoadFile (const std::tstring fileName)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFO     * pbmi;
	Win::Bitmap::DIBSection::StrongHandle bitmap ;
	int              sizeInfo;
	int              sizeBit;

	std::string tmpFileName;
	#if defined (_UNICODE)
		BOOL useless;
		tmpFileName.reserve (tmpFileName.length() + 1);
		tmpFileName.resize (tmpFileName.length());

		::WideCharToMultiByte (CP_ACP, 0, fileName.c_str(),fileName.length(), &tmpFileName[0], tmpFileName.length(), "a", &useless);
	#else
		tmpFileName = fileName;
	#endif

	std::ifstream reader (tmpFileName.c_str (), std::ios_base::in | std::ios_base::binary);

	if (!reader)
		throw Win::Exception (TEXT("Could not open the bitmap file"));

	reader.read (reinterpret_cast <char *> (&bmfh), sizeof(BITMAPFILEHEADER));

	if (reader.fail () || (bmfh.bfType != * reinterpret_cast<WORD *> ("BM"))) // UNICODE WHAT
	{
		reader.close ();
		throw Win::Exception (TEXT("Could not read the bitmap file"));
	}

	sizeInfo = bmfh.bfOffBits - sizeof (BITMAPFILEHEADER);

	pbmi = reinterpret_cast <BITMAPINFO *> (malloc (sizeInfo));

	if (pbmi == NULL)
	{
		reader.close ();
		throw Win::Exception (TEXT("Could not read the bitmap file"));
	}

	reader.read (reinterpret_cast <char *> (pbmi), sizeInfo);

	if (reader.fail ())
	{
		reader.close ();
		free (pbmi);
		throw Win::Exception (TEXT("Could not read the bitmap file"));
	}

	bitmap._h = ::CreateDIBSection (NULL, pbmi, DIB_RGB_COLORS, reinterpret_cast <void **> (&bitmap._bits),NULL, 0);

	if (!bitmap._h)
	{
		reader.close () ;
		free (pbmi) ;
		throw Win::Exception (TEXT("Could not cteatre a DIB section"));
	}

	free (pbmi);

	sizeBit = bmfh.bfSize - bmfh.bfOffBits;

	reader.read (reinterpret_cast <char *> (bitmap._bits), sizeBit);

	if (reader.fail ())
	{
		reader.close ();
		throw Win::Exception (TEXT("Could not read the bitmap file"));
	}

	reader.close ();

	return bitmap ;
}

//--------------------------------------------------------------------
// Loads a DIB section from a resource.
//
// Return value:  A StrongHandle on the DIB section.
//
// Parameters:
//
// const int id				 -> ID of the resource.
// const HINSTANCE hInstance -> Instance of the program.
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::StrongHandle Win::Bitmap::DIBSection::Loader::LoadResource (const int id, const HINSTANCE hInstance)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFO     * pbmi;
	Win::Bitmap::DIBSection::StrongHandle bitmap ;
	int              sizeInfo;
	int              sizeBit;
	HGLOBAL          resource ;
	BYTE *           pResource ;

	resource = ::LoadResource (hInstance,
								::FindResource (hInstance, MAKEINTRESOURCE (id), TEXT("DIBSECTION"))) ;

	 if (resource == NULL)
		throw Win::Exception (TEXT("Could not load the resource")) ;

	pResource = reinterpret_cast <BYTE *> (::LockResource (resource)) ;

	if (pResource == NULL)
	{
		::FreeResource (resource) ;
		throw Win::Exception (TEXT("Could not load the resource")) ;
	}
	
	::CopyMemory (&bmfh, pResource, sizeof (bmfh)) ;

	pResource += sizeof (bmfh) ;

	sizeInfo = bmfh.bfOffBits - sizeof (BITMAPFILEHEADER);

	pbmi = reinterpret_cast <BITMAPINFO *> (malloc (sizeInfo));

	if (pbmi == NULL)
	{
		::FreeResource (resource) ;
		throw Win::Exception (TEXT("Could not load the resource"));
	}

	::CopyMemory (pbmi, pResource, sizeInfo) ;

	pResource += sizeInfo ;

	bitmap._h = ::CreateDIBSection (NULL, pbmi, DIB_RGB_COLORS, reinterpret_cast <void **> (&bitmap._bits),NULL, 0);

	if (!bitmap._h)
	{
		free (pbmi);
		::FreeResource (resource) ;

		throw Win::Exception (TEXT("Could not cteatre a DIB section"));
	}

	free (pbmi);

	sizeBit = bmfh.bfSize - bmfh.bfOffBits;

	::CopyMemory (bitmap._bits, pResource, sizeBit) ;

	::FreeResource (resource) ;

	return bitmap ;
}

//--------------------------------------------------------------------
// Loads a DIB section from a resource.
//
// Return value:  A StrongHandle on the DIB section.
//
// Parameters:
//
// const str::string name    -> ID of the resource.
// const HINSTANCE hInstance -> Instance of the program.
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::StrongHandle Win::Bitmap::DIBSection::Loader::LoadResource (const std::tstring name, const HINSTANCE hInstance)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFO     * pbmi;
	Win::Bitmap::DIBSection::StrongHandle bitmap ;
	int              sizeInfo;
	int              sizeBit;
	HGLOBAL          resource ;
	BYTE *           pResource ;

	resource = ::LoadResource (hInstance,
								::FindResource (hInstance, name.c_str (), TEXT("DIBSECTION"))) ;

	 if (resource == NULL)
		throw Win::Exception (TEXT("Could not load the resource")) ;

	pResource = reinterpret_cast <BYTE *> (::LockResource (resource)) ;

	if (pResource == NULL)
	{
		::FreeResource (resource) ;
		throw Win::Exception (TEXT("Could not load the resource")) ;
	}
	
	::CopyMemory (&bmfh, pResource, sizeof (bmfh)) ;

	pResource += sizeof (bmfh) ;

	sizeInfo = bmfh.bfOffBits - sizeof (BITMAPFILEHEADER);

	pbmi = reinterpret_cast <BITMAPINFO *> (malloc (sizeInfo));

	if (pbmi == NULL)
	{
		::FreeResource (resource) ;
		throw Win::Exception (TEXT("Could not load the resource"));
	}

	::CopyMemory (pbmi, pResource, sizeInfo) ;

	pResource += sizeInfo ;

	bitmap._h = ::CreateDIBSection (NULL, pbmi, DIB_RGB_COLORS, reinterpret_cast <void **> (&bitmap._bits),NULL, 0);

	if (!bitmap._h)
	{
		free (pbmi);
		::FreeResource (resource) ;

		throw Win::Exception (TEXT("Could not cteatre a DIB section"));
	}

	free (pbmi);

	sizeBit = bmfh.bfSize - bmfh.bfOffBits;

	::CopyMemory (bitmap._bits, pResource, sizeBit) ;

	::FreeResource (resource) ;

	return bitmap ;
}

//--------------------------------------------------------------------
// Creates a DIB section.
//
// Return value:  A StrongHandle on the DIB section.
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::StrongHandle Win::Bitmap::DIBSection::Creator::Create (const unsigned int width, const unsigned int height, const unsigned int colorBits, const unsigned int colorUsed)
{
	BITMAPINFO * pbmi;
	int entries = 1;
	Win::Bitmap::DIBSection::StrongHandle bitmap ;

	assert (width > 0 && height > 0 && (colorBits == 1 || colorBits == 4 || colorBits == 8 || colorBits == 16 || colorBits == 24 || colorBits == 32));

	if (colorUsed != 0)
		entries = colorUsed;
	else if (colorBits <= 8)
		entries = 1 << colorBits;

	pbmi = reinterpret_cast <BITMAPINFO *> (malloc (sizeof (BITMAPINFOHEADER ) + (entries - 1) * sizeof (RGBQUAD)));

	if (pbmi == NULL)
		throw Win::Exception (TEXT("Could not create a DIB section"));

	memset (pbmi, 0, sizeof(sizeof (BITMAPINFOHEADER ) + (entries - 1) * sizeof (RGBQUAD))) ;

	pbmi->bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = width;
	pbmi->bmiHeader.biHeight = height;
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biBitCount = colorBits;
	pbmi->bmiHeader.biCompression = BI_RGB;
	pbmi->bmiHeader.biSizeImage = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 0;
	pbmi->bmiHeader.biYPelsPerMeter = 0;
	pbmi->bmiHeader.biClrUsed = colorUsed;
	pbmi->bmiHeader.biClrImportant = 0;

	bitmap._h = ::CreateDIBSection (NULL, pbmi, DIB_RGB_COLORS, reinterpret_cast <void **> (&bitmap._bits),NULL, 0);

	if (!bitmap._h)
	{
		free (pbmi);
		throw Win::Exception (TEXT("Could not cteatre a DIB section"));
	}

	free (pbmi);

	memset (bitmap._bits, 0, bitmap.GetHeight () * bitmap.GetRowLenght ()) ;

	return bitmap ;

}

//--------------------------------------------------------------------
// Creates a DIB section.
//
// Return value:  A StrongHandle on the DIB section.
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::StrongHandle Win::Bitmap::DIBSection::Creator::Create ()
{
	BITMAPINFO * pbmi;
	int entries = 1;
	Win::Bitmap::DIBSection::StrongHandle bitmap ;

	assert (_width > 0 && _height > 0 && (_colorBits == 1 || _colorBits == 4 || _colorBits == 8 || _colorBits == 16 || _colorBits == 24 || _colorBits == 32));

	if (_colorUsed != 0)
		entries = _colorUsed;
	else if (_colorBits <= 8)
		entries = 1 << _colorBits;

	pbmi = reinterpret_cast <BITMAPINFO *> (malloc (sizeof (BITMAPINFOHEADER ) + (entries - 1) * sizeof (RGBQUAD)));

	if (pbmi == NULL)
		throw Win::Exception (TEXT("Could not create a DIB section"));

	memset (pbmi, 0, sizeof(sizeof (BITMAPINFOHEADER ) + (entries - 1) * sizeof (RGBQUAD))) ;

	pbmi->bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = _width;
	pbmi->bmiHeader.biHeight = _height;
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biBitCount = _colorBits;
	pbmi->bmiHeader.biCompression = BI_RGB;
	pbmi->bmiHeader.biSizeImage = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 0;
	pbmi->bmiHeader.biYPelsPerMeter = 0;
	pbmi->bmiHeader.biClrUsed = _colorUsed;
	pbmi->bmiHeader.biClrImportant = 0;

	bitmap._h = ::CreateDIBSection (NULL, pbmi, DIB_RGB_COLORS, reinterpret_cast <void **> (&bitmap._bits),NULL, 0);

	if (!bitmap._h)
	{
		free (pbmi);
		throw Win::Exception (TEXT("Could not cteatre a DIB section"));
	}

	free (pbmi);

	memset (bitmap._bits, 0, bitmap.GetHeight () * bitmap.GetRowLenght ()) ;

	return bitmap ;

}

//--------------------------------------------------------------------
// Obtains the number of right shift necessary.
//--------------------------------------------------------------------

int Win::Bitmap::DIBSection::PixelPlotter::MaskToRightShift (DWORD mask)
{
	int shift;

	if (mask == 0)
		return 0;

	for (shift = 0; !(mask & 1); shift++)
		mask >>= 1;

	return shift;

}

//--------------------------------------------------------------------
// Obtains the number of left shift necessary.
//--------------------------------------------------------------------

int Win::Bitmap::DIBSection::PixelPlotter::MaskToLeftShift (DWORD mask)
{
	int shift;

	if (mask == 0)
		return 0;

	while (!(mask & 1))
		mask >>= 1;

	for (shift = 0; mask & 1; shift++)
		mask >>= 1;

	return 8 - shift;

}

//--------------------------------------------------------------------
// Creates a data structure necessary to change and obtain the pixels.
//--------------------------------------------------------------------

void Win::Bitmap::DIBSection::PixelPlotter::PlotMaker ()
{
	int i = 0;
	int rowLenght;
	DIBSECTION ds ;

	::GetObject (_h, sizeof (DIBSECTION), &ds);

	if (ds.dsBmih.biCompression == BI_BITFIELDS)
	{
		for (i = 0; i < 3; i++)
		{
			_leftShift [i] = MaskToLeftShift (ds.dsBitfields [i]);
			_rightShift [i]= MaskToRightShift (ds.dsBitfields [i]);

			_bitFields [i] = ds.dsBitfields [i];

		}
	}
	else if (ds.dsBmih.biCompression == BI_RGB)
	{
		if (ds.dsBm.bmBitsPixel == 16)
		{
			_bitFields [0] = 0x00007C00;
			_bitFields [1] = 0x000003E0;
			_bitFields [2] = 0x0000001F;

			_rightShift [0] = 10;
			_rightShift [1] = 5;
			_rightShift [2] = 0;

			_leftShift [0] = 3;
			_leftShift [1] = 3;
			_leftShift [2] = 3;

		}
		else if (ds.dsBm.bmBitsPixel == 24 || ds.dsBm.bmBitsPixel == 32)
		{
			_bitFields [0] = 0x00FF0000;
			_bitFields [1] = 0x0000FF00;
			_bitFields [2] = 0x000000FF;

			_rightShift [0] = 16;
			_rightShift [1] = 8;
			_rightShift [2] = 0;

			_leftShift [0] = 0;
			_leftShift [1] = 0;
			_leftShift [2] = 0;
		}
	}

	_ptr.Resize (ds.dsBm.bmHeight);

	rowLenght = _h.GetRowLenght ();

	if (ds.dsBm.bmHeight > 0)
	{	
		int y = 0;

		BYTE * byte = NULL ;
		for (y = 0; y < ds.dsBm.bmHeight; y++)
		{
			_ptr [y] =_h._bits + (ds.dsBm.bmHeight - y - 1) * rowLenght;
			
		}
	}
	else 
	{
		int y = 0;
		for (y = 0; y < ds.dsBm.bmHeight; y++)
			_ptr [y] = _h._bits + y * rowLenght;
	}
}

//--------------------------------------------------------------------
// Obtains a pointer on a particular pixel.
//
// Return Value:  The pointer on the pixel.
//
// DIBSECTION & ds -> contain various info that are necessary.
// int x           -> The x coordinate of the pixel.
// int y           -> The y coordinate of the pixel.
//--------------------------------------------------------------------

BYTE * Win::Bitmap::DIBSection::PixelPlotter::GetPixelPtr (DIBSECTION & ds, int x, int y)
{
	assert (_h != NULL && x >= 0 && x < ds.dsBm.bmWidth && y >= 0 && y < ds.dsBm.bmHeight);
	
	return _ptr [y] + (x * ds.dsBm.bmBitsPixel >> 3) ;
}

//--------------------------------------------------------------------
// Obtains the value of a particular pixel.
//
// Return Value:  The value of the pixel.
//
// Parameters:
// 
// int x           -> The x coordinate of the pixel.
// int y           -> The y coordinate of the pixel.
//--------------------------------------------------------------------

DWORD Win::Bitmap::DIBSection::PixelPlotter::GetPixel (int x, int y)
{
	assert (_h != NULL) ;

	DIBSECTION ds ;

	::GetObject (_h._h, sizeof (DIBSECTION), &ds) ;

	BYTE * pixel = GetPixelPtr (ds, x, y);

	if (!pixel)
		throw Win::Exception (TEXT("Could not get a pixel from a DIB"));

	switch (ds.dsBm.bmBitsPixel)
	{
	case 1:
		return 0x01 & (*pixel >> (7 - (x & 7)));
	case 4:
		return 0x0F & (*pixel >> (x & 1 ? 0 : 4));
	case 8:
		return *pixel;
	case 16:
		return * reinterpret_cast <WORD *> (pixel);
	case 24:
		return 0x00FFFFFF & * reinterpret_cast <DWORD *> (pixel);
	case 32:
		return * reinterpret_cast <DWORD *> (pixel);
	default:
		throw Win::Exception (TEXT("Could not get a pixel from a DIB"));
	}

	return 0;

}

//--------------------------------------------------------------------
// Changes the value of a particular pixel.
//
// Parameters:
//
// int x     -> The x coordinate of the pixel.
// int y     -> The y coordinate of the pixel.
// DWORD pix -> The new value of the pixel.
//--------------------------------------------------------------------

void Win::Bitmap::DIBSection::PixelPlotter::SetPixel (int x, int y, DWORD pix)
{
	assert (_h != NULL) ;

	DIBSECTION ds ;

	::GetObject (_h._h, sizeof (DIBSECTION), &ds) ;

	BYTE * pixel = GetPixelPtr (ds, x, y);

	if (!pixel)
		throw Win::Exception (TEXT("Could not set a pixel to a DIB"));

	switch (ds.dsBm.bmBitsPixel)
	{
	case 1:
		*pixel &= ~(1 << (7 - (x & 7)));
		*pixel |= pix << (7 - (x & 7));
		break;
	case 4:
		*pixel &= 0x0F << (x & 1 ? 4 : 0);
		*pixel |= pix << (x & 1 ? 0 : 4);
		break;
	case 8:
		*pixel = static_cast <BYTE> (pix);
		break;
	case 16:
		* reinterpret_cast <WORD *> (pixel) = static_cast<WORD> (pix);
			
		break;
	case 24:
		* reinterpret_cast <RGBTRIPLE *> (pixel) = * reinterpret_cast<RGBTRIPLE *> (&pix);
		break;
	case 32:
		* reinterpret_cast <DWORD *> (pixel) = pix;
		break;
	default:
		throw Win::Exception (TEXT("Could not set a pixel to a DIB"));
	}
}

//--------------------------------------------------------------------
// Obtains the color of a particular pixel.
//
// Return Value:  The value of the pixel.
//
// Parameters:
// 
// int x           -> The x coordinate of the pixel.
// int y           -> The y coordinate of the pixel.
//--------------------------------------------------------------------

Win::Bitmap::DIBSection::RGBQuad Win::Bitmap::DIBSection::PixelPlotter::GetPixelColor (int x, int y)
{
	RGBQUAD    quad ;
	DIBSECTION ds ;

	::GetObject (_h._h, sizeof (DIBSECTION), &ds) ;quad;

	try
	{
		assert (ds.dsBm.bmBitsPixel != 0);

		DWORD pixel;
		
		pixel = GetPixel (x, y);

		if (ds.dsBm.bmBitsPixel <= 8)
			return _h.GetColorInTable (static_cast<int> (pixel));
		else if (ds.dsBm.bmBitsPixel == 24)
		{
			* reinterpret_cast <RGBTRIPLE *> (&quad) = * reinterpret_cast <RGBTRIPLE *> (&pixel);
			quad.rgbReserved = 0;
		}
		else if (ds.dsBm.bmBitsPixel == 32 && ds.dsBmih.biCompression == BI_RGB)
		{
			quad = * reinterpret_cast <RGBQUAD *> (&pixel);
		}
		else
		{
			quad.rgbRed = static_cast <BYTE> ((_bitFields [0] & pixel) >> _rightShift [0] << _leftShift [0]);
			quad.rgbGreen = static_cast <BYTE> ((_bitFields [1] & pixel) >> _rightShift [1] << _leftShift [1]);
			quad.rgbBlue = static_cast <BYTE> ((_bitFields [2] & pixel) >> _rightShift [2] << _leftShift [2]);
		}
	}
	catch (Win::Exception e)
	{
		throw e;

	}

	return quad;

}

//--------------------------------------------------------------------
// Changes the colorof a particular pixel. (must be at least a 16 bit DIB section).
//
// Parameters:
//
// int x								 -> The x coordinate of the pixel.
// int y								 -> The y coordinate of the pixel.
// in::Bitmap::DIBSection::RGBQuad & rgb -> The new color of the pixel.
//--------------------------------------------------------------------

void Win::Bitmap::DIBSection::PixelPlotter::SetPixelColor (int x, int y, Win::Bitmap::DIBSection::RGBQuad & rgb)
{	
	DIBSECTION ds ;

	::GetObject (_h._h, sizeof (DIBSECTION), &ds) ;

	try
	{
		assert (ds.dsBm.bmBitsPixel  > 8);

		DWORD pixel;

		if (ds.dsBm.bmBitsPixel == 24)
		{
			* reinterpret_cast <RGBTRIPLE *> (&pixel) = * reinterpret_cast <RGBTRIPLE *> (&rgb);
			pixel &= 0x00FFFFFF ;
		}
		else if (ds.dsBm.bmBitsPixel == 32 && ds.dsBmih.biCompression == BI_RGB)
		{
			* reinterpret_cast <RGBQUAD *> (&pixel) = * reinterpret_cast <RGBQUAD *> (&rgb);
		}
		else
		{
			pixel = (rgb.GetRed () >> _leftShift [0]) << _rightShift [0];
			pixel |= (rgb.GetGreen () >> _leftShift [1]) << _rightShift [1];
			pixel |= (rgb.GetBlue () >> _leftShift [2]) << _rightShift [2];
		}
	
		SetPixel (x, y, pixel);
	}
	catch (Win::Exception e)
	{
		throw e;
	}
} 