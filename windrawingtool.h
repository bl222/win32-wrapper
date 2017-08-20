//-----------------------------------------------------------------
// This file contains classes encapsulating various drawing tools 
// like pens, brushes, fonts, palettes and bitmaps.
//-----------------------------------------------------------------

#if !defined (WINDRAWINGTOOL_H)

	#define WINDRAWINGTOOL_H
	#include "useunicode.h"
	#include <cassert>
	#include <TCHAR.h>
	#include "winhandle.h"
	#include "wincolor.h"
	#include "winexception.h"
	#include "winencapsulation.h"
	#include "winimageloader.h"
	#include "strongpointer.h"
#include "winunicodehelper.h"
	namespace Win
	{
		class Canvas ;
		namespace Polygon
		{
			enum FillMode {Alternate = ALTERNATE, Winding = WINDING} ;
		}

		namespace Clipboard
		{
			class DIBSectionClip ;
		}

		namespace GDI
		{
			//--------------------------------------------------------------------
			// Encapsulation of a basic GDI handle. Used by winlib to implements
			// pen, extended pen, brush, font, bitmap, palette and region handle
			//--------------------------------------------------------------------

			template <class Logical, class NormalHandle = HGDIOBJ>
			class Handle : public Sys::Handle<NormalHandle>
			{
				public:

					Handle (NormalHandle h = NULL)
						: Sys::Handle<NormalHandle> (h)
					{}

				//--------------------------------------------------------------------
				// Obtains various data about a GDI object.  Logical will be a different
				// class depending on the object.
				//
				// Return value:  If the method succeed, the number of byte of data
				//				  obtained, else 0.
				//
				// Parameters:
				//
				// Logical & log -> This object will contain data about the object.
				//							   
				//--------------------------------------------------------------------

				void  GetData (Logical & log) const 
				{
					if (::GetObject (_h, sizeof (Logical), 
										reinterpret_cast <Logical *> (&log)) == 0)
						throw Win::Exception (TEXT("Could not obtain the data about the handle.")) ;
				}

				//--------------------------------------------------------------------
				// Obtains various data about a GDI object.  Logical will be a different
				// class depending on the object.
				//
				// Return value:  The data about the GDI object.					   
				//--------------------------------------------------------------------

				Logical GetData () const
				{
					Logical data ;

					if (::GetObject (_h, sizeof (Logical), 
									reinterpret_cast <Logical *> (&log)) == 0)
					throw Win::Exception (TEXT("Could not obtain the data about the handle.")) ;

					return data ;
				}

			} ;

			//------------------------------------------------------------------
			// Sys::GDI::Disposal is used to destroy a GDI Handle (pen, brush, 
			// font, bitmap, ect).  Used only internaly by winlib, not by users.
			//------------------------------------------------------------------

			template<class NormalHandle>
			struct Disposal
			{
				static void Dispose (NormalHandle h)
				{
					::DeleteObject (h) ;
				}
			} ;
		}

		namespace Bitmap
		{
			namespace DDB
			{
				//---------------------------------------------------------------------------
				// Win::Bitmap::Data encapsulates a BITMAP structure through private 
				// inheritance.  a A Win::Bitmap::Data object contains various 
				// parameters defining a bitmap that can be used to create a real bitmap.
				//
				// Data members of BITMAP:
				//
				// LONG   bmType       -> Must be 0
				// LONG   bmWidth      -> Width in pixel of the bitmap.
				// LONG   bmHeight     -> Height in pixel of the pixel.
				// LONG   bmWidthBytes -> Number of bytes in each scan line.
				// WORD   bmPlanes     -> Count of color plane.
				// WORD   bmBitsPixel  -> Number of bit per pixel.
				// LPVOID bmBits       -> Pointer on the bits defining the picture.
				//---------------------------------------------------------------------------

				class Data : public Sys::Struct <BITMAP>
				{
				public:

					//---------------------------------------------------------------------
					// Constructor. Data members are initialized to 0.
					//---------------------------------------------------------------------

					Data ()
						: Sys::Struct <BITMAP> ()
					{}

					Data (const BITMAP bitmap)
						: Sys::Struct <BITMAP> (bitmap)
					{}

					//-------------------------------------------------------------------
					// Obtains the width of the Win::Bitmap::Data object.
					// 
					// Return value:  The bmWidth data member of the BITMAP 
					// structure.
					//-------------------------------------------------------------------

					LONG GetWidth () const
					{
						return _struct.bmWidth ;
					}

					//-------------------------------------------------------------------
					// Obtains the height of the Win::Bitmap::Data object.
					// 
					// Return value:  The bmHeight data member of the BITMAP 
					// structure.
					//-------------------------------------------------------------------

					LONG GetHeight () const
					{
						return _struct.bmHeight ;
					}

					//-------------------------------------------------------------------
					// Obtains the byte width of the Win::Bitmap::Data object.
					// 
					// Return value:  The bmWidthBytes data member of the BITMAP 
					// structure.
					//-------------------------------------------------------------------

					LONG GetWidthBytes () const
					{
						return _struct.bmWidthBytes ;
					}

					//-------------------------------------------------------------------
					// Obtains the number of color plane of the Win::Bitmap::Data object.
					// 
					// Return value:  The bmPlanes data member of the BITMAP 
					// structure.
					//-------------------------------------------------------------------

					WORD GetPlanes () const
					{
						return _struct.bmPlanes ;
					}

					//-------------------------------------------------------------------
					// Obtains the number of bit per pixrl of the Win::Bitmap::Data 
					// object.
					// 
					// Return value:  The bmBitsPerPixel data member of the BITMAP 
					// structure.
					//-------------------------------------------------------------------

					WORD GetBitsPerPixel () const
					{
						return _struct.bmBitsPixel ;
					}
				} ;
				
				//--------------------------------------------------------------------
				// Handle for a device dependent bitmap.
				//--------------------------------------------------------------------

				class Handle : public Win::GDI::Handle <Win::Bitmap::DDB::Data, HBITMAP>
				{
				public:

					//--------------------------------------------------------------------
					// Constructor.
					//--------------------------------------------------------------------

					Handle (HBITMAP bitmap = NULL)
						: Win::GDI::Handle <Win::Bitmap::DDB::Data, HBITMAP> (bitmap)
					{}

					int  GetWidth () const ;
					int  GetHeight () const ;
					void GetDimension (int & width, int & height) const ;


				} ;
				typedef Sys::StrongHandle <Win::Bitmap::DDB::Handle, Win::GDI::Disposal<HBITMAP> > StrongHandle ; // Strong handle owning the DDB

				//--------------------------------------------------------------------
				// Win::Bitmap::DDB::Creator is used to create a bitmap
				//--------------------------------------------------------------------

				class Creator
				{
				public:

					//--------------------------------------------------------------------
					// Constructor.
					//--------------------------------------------------------------------

					Creator ()
						: _width  (0),
						  _height (0)
					{}

					//--------------------------------------------------------------------
					// Constructor. Sets the data used to create the bitmap.
					//--------------------------------------------------------------------

					Creator (const int width, const int height, const void * bits)
						: _width  (width),
						  _height (height)
					{}

					//--------------------------------------------------------------------
					// Changes the width of the bitmap that will be created.
					// 
					// parameters:
					//
					// const int width -> The new width.
					//--------------------------------------------------------------------

					void SetWidth (const int width)
					{
						_width = width ;
					}

					//--------------------------------------------------------------------
					// Changes the height of the bitmap that will be created.
					// 
					// parameters:
					//
					// const int height -> The new height.
					//--------------------------------------------------------------------

					void SetHeight (const int height) 
					{
						_height = height ;
					}

					//--------------------------------------------------------------------
					// Changes all the data of the bitmap that will be created.
					// 
					// parameters:
					//
					// const int width   -> The new width.
					// const int height  -> The new height.
					//--------------------------------------------------------------------

					void SetAllData (const int width, const int height)
					{
						_width  = width ;
						_height = height ;

					}

					Win::Bitmap::DDB::StrongHandle CreateMonochrome (const void * bits = NULL) ;
					Win::Bitmap::DDB::StrongHandle CreateCompatible (Win::Canvas & canvas) ;

					static Win::Bitmap::DDB::StrongHandle CreateMonochrome (const int width, const int height, const void * bits = NULL) ;
					static Win::Bitmap::DDB::StrongHandle CreateCompatible (const int width, const int height, Win::Canvas & canvas) ;
					static Win::Bitmap::DDB::StrongHandle CreateCopy (Win::Bitmap::DDB::Handle ddb) ;

				private:

					int    _width ;
					int    _height ;

				} ;

				//--------------------------------------------------------------------
				// Win::Bitmap::DDB::Loader is used to load a bitmap from a file or a 
				// resource.
				//--------------------------------------------------------------------

				class Loader : public Win::ImageLoader
				{
				public:

					//--------------------------------------------------------------------
					// Constructor.
					//--------------------------------------------------------------------

					Loader (const HINSTANCE hInstance = NULL, const int width = 0, const int height = 0)
						: _width     (width),
						  _height    (height)
					{}

					//--------------------------------------------------------------------
					// Changes the desired width of the bitmap.
					//
					// Parameters:
					//
					// const int width -> The new width.
					//--------------------------------------------------------------------

					void SetDesiredWidth (const int width)
					{
						_width = width ;
					}

					//--------------------------------------------------------------------
					// Changes the desired height of the bitmap.
					//
					// Parameters:
					//
					// const int heigth -> The new height.
					//--------------------------------------------------------------------

					void SetDesiredHeight (const int height)
					{
						_height = height ;
					}

					//--------------------------------------------------------------------
					// Changes all the data of the bitmap.
					//
					// Parameters:
					//
					// const HINSTANCE hInstance -> The new instance.
					// const int width           -> The new width.
					// const int heigth          -> The new height.
					//--------------------------------------------------------------------

					void SetAllData (const HINSTANCE hInstance, const int width, const int height)
					{
						_hInstance = hInstance ;
						_width     = width ;
						_height    = height ;
					}

					Win::Bitmap::DDB::StrongHandle LoadResource (const int id) ;
					Win::Bitmap::DDB::StrongHandle LoadResource (const std::tstring  name) ;
					Win::Bitmap::DDB::StrongHandle LoadFile (const std::tstring  name) ;

					static Win::Bitmap::DDB::StrongHandle LoadResource (const HINSTANCE hInstance, const int width, const int height, const int id, const UINT flag) ;
					static Win::Bitmap::DDB::StrongHandle LoadResource (const HINSTANCE hInstance, const int width, const int height, const std::tstring  name, const UINT flag) ;
					static Win::Bitmap::DDB::StrongHandle LoadFile (const int width, const int height, const std::tstring  name, const UINT flag) ;

				private:

					int       _width ;
					int       _height ;
				} ;

			}

			namespace DIBSection
			{
				//---------------------------------------------------------------------------
				// Win::Bitmap::DIBSection::RGBQuad encapsulates a RGBQUAD structure through 
				// private inheritance
				//
				// Dara members of RGBQUAD:
				//
				// BYTE    rgbBlue     -> Level of blue.
				// BYTE    rgbGreen    -> Level of green.
				// BYTE    rgbRed      -> Level of red.
				// BYTE    rgbReserved -> Not used, 0.
				//---------------------------------------------------------------------------

				class RGBQuad : public Sys::Struct <RGBQUAD>
				{
				public:

					//---------------------------------------------------------------------------
					// Constructor.
					//---------------------------------------------------------------------------

					RGBQuad ()
						: Sys::Struct <RGBQUAD> ()
					{}

					//---------------------------------------------------------------------------
					// Constructor.  Creates an object with a RGBQUAD structure.
					//---------------------------------------------------------------------------

					RGBQuad (const RGBQUAD rgb)
						: Sys::Struct <RGBQUAD> (rgb)
					{}

					//---------------------------------------------------------------------------
					// Constructor. 
					//
					// Parameter:
					// 
					// const BYTE red   -> Desired red value.
					// const BYTE green -> Desired green value.
					// const BYTE blue  -> Desired blue value.
					//---------------------------------------------------------------------------

					RGBQuad (const BYTE red, const BYTE green, const BYTE blue)
					{
						_struct.rgbRed   = red ;
						_struct.rgbGreen = green ;
						_struct.rgbBlue  = blue ;
					}

					//---------------------------------------------------------------------------
					// Constructor. Creates a new RGBQuad object from a Win::RGBColor.
					//
					// Parameter:
					// 
					// const Win::RGBColor & color -> color used to create the RGBQuad.
					//---------------------------------------------------------------------------

					RGBQuad (const Win::RGBColor & color)
					{
						_struct.rgbRed   = static_cast<BYTE> (color.GetRed   ()) ;
						_struct.rgbGreen = static_cast<BYTE> (color.GetBlue  ()) ;
						_struct.rgbBlue  = static_cast<BYTE> (color.GetGreen ()) ;
					}

					//---------------------------------------------------------------------------
					// Obtains the red value.
					//
					// Return value:  The red value.
					//---------------------------------------------------------------------------

					BYTE GetRed () const
					{
						return _struct.rgbRed ;
					}

					//---------------------------------------------------------------------------
					// Obtains the green value.
					//
					// Return value:  The green value.
					//---------------------------------------------------------------------------

					BYTE GetGreen () const 
					{
						return _struct.rgbGreen ;
					}

					//---------------------------------------------------------------------------
					// Obtains the blue value.
					//
					// Return value:  The blue value.
					//---------------------------------------------------------------------------

					BYTE GetBlue () const
					{
						return _struct.rgbBlue  ;
					}

					//---------------------------------------------------------------------------
					// Obtains the red, green and blue value.
					//
					// parameters:
					//
					// BYTE & red   -> Will contain the red value.
					// BYTE & green -> Will contain the green value.
					// BYTE & blue  -> Will contain the blue value.
					//---------------------------------------------------------------------------

					BYTE GetColor (BYTE & red, BYTE & green, BYTE & blue) const
					{
						red   = _struct.rgbRed ;
						blue  = _struct.rgbBlue ;
						green = _struct.rgbGreen ;
					}

					//---------------------------------------------------------------------------
					// Obtains a Win::RGBColor containing the red, green and blue value of the RGBQuad.
					//
					// Return value:  A Win::RGBColor object.
					//---------------------------------------------------------------------------

					Win::RGBColor GetColor () const 
					{
						return Win::RGBColor (_struct.rgbRed, _struct.rgbGreen, _struct.rgbBlue) ;
					}

					//---------------------------------------------------------------------------
					// Changes the red value.
					//
					// Parameters:
					//
					// const BYTE red -> The new red value.
					//---------------------------------------------------------------------------

					void SetRed (const BYTE red) 
					{
						_struct.rgbRed = red ;
					}

					//---------------------------------------------------------------------------
					// Changes the green value.
					//
					// Parameters:
					//
					// const BYTE green -> The new green value.
					//---------------------------------------------------------------------------

					void SetGreen (const BYTE green) 
					{
						_struct.rgbGreen = green ;
					}

					//---------------------------------------------------------------------------
					// Changes the blue value.
					//
					// Parameters:
					//
					// const BYTE blue -> The new blue value.
					//---------------------------------------------------------------------------

					void SetBlue (const BYTE blue) 
					{
						_struct.rgbRed = blue ;
					}

					//---------------------------------------------------------------------------
					// Changes the red, green and blue value.
					//
					// Parameters:
					//
					// const BYTE red   -> The new red value.
					// const BYTE green -> The new green value.
					// const BYTE blue  -> The new blue value.
					//---------------------------------------------------------------------------

					void SetColor (const BYTE red, const BYTE green, const BYTE blue)
					{
						_struct.rgbRed   = red ;
						_struct.rgbGreen = green ;
						_struct.rgbBlue  = blue ;

					}

					//---------------------------------------------------------------------------
					// Changes the red, green and blue value.
					//
					// Parameters:
					//
					// const Win::RGBColor & color -> The new color.of the RGB::Quad
					//---------------------------------------------------------------------------

					void SetColor (const Win::RGBColor & color)
					{
						_struct.rgbRed   = static_cast<BYTE> (color.GetRed ()) ;
						_struct.rgbGreen = static_cast<BYTE> (color.GetGreen ()) ;
						_struct.rgbBlue  = static_cast<BYTE> (color.GetBlue ()) ;

					}
				} ;

				class Loader ;
				class Creator ;
				class PixelPlotter ;

				//---------------------------------------------------------------------
				// Handle for a DIBSection
				//---------------------------------------------------------------------

				class Handle : public Win::Bitmap::DDB::Handle
				{
					friend class Win::Bitmap::DIBSection::Loader ;
					friend class Win::Bitmap::DIBSection::Creator ;
					friend class Win::Bitmap::DIBSection::PixelPlotter ;
					friend class Win::Clipboard::DIBSectionClip ;

				public:

					//---------------------------------------------------------------------
					// Constructor.
					//---------------------------------------------------------------------

					Handle (HBITMAP bitmap = NULL, BYTE * bit = NULL)
						: Win::Bitmap::DDB::Handle (bitmap),
						  _bits (bit)

					{}

					void Save										 (const std::tstring fileName);
					int GetRowLenght								 () ;
					int GetNumColorsInTable							 () ;
					int GetCompression								 () ;
					bool IsNotCompressed							 () ;
					void SetColorInTable                             (int pos, Win::Bitmap::DIBSection::RGBQuad & quad) ;
					Win::Bitmap::DIBSection::RGBQuad GetColorInTable (int pos) ;

				protected:

					BITMAPINFO * CopyToClipboard () ;
					

					BYTE *  _bits ;
				} ;
				
				//---------------------------------------------------------------------
				// Strong Handle for a DIBSection.  Owns the DIBSection
				//---------------------------------------------------------------------

				class StrongHandle : public Sys::StrongHandle<Win::Bitmap::DIBSection::Handle, Win::GDI::Disposal<HBITMAP> >//Win::Bitmap::DIBSection::Handle
				{
					friend class Win::Bitmap::DIBSection::Loader ;	
					friend class Win::Bitmap::DIBSection::Creator ;
					friend class Win::Bitmap::DIBSection::PixelPlotter ;
					friend class Win::Clipboard::DIBSectionClip ;

				public:

					//---------------------------------------------------------------------
					// Constructor.
					//---------------------------------------------------------------------

					StrongHandle (HBITMAP bitmap = NULL, BYTE * bits = NULL)
						: Sys::StrongHandle<Win::Bitmap::DIBSection::Handle, Win::GDI::Disposal<HBITMAP> > (bitmap)
						  
					{
						_bits = bits ;
					}

					//------------------------------------------------------------------
					// Transfer a DIB Section from one StrongHandle to
					// another StrongHandle.
					//
					// Parameters:
					// 
					// StrongHandle & sh -> The object giving up ownership.
					//------------------------------------------------------------------

					Win::Bitmap::DIBSection::StrongHandle & operator = (Win::Bitmap::DIBSection::StrongHandle & sh)
					{

						StrongHandle tmp = sh ;
						std::swap (_h, tmp._h) ;
						_bits = sh._bits ;
						return *this ;
					}

				protected:

					void PasteFromClipboard (BITMAPINFO * packedDib) ;
				} ;

				//---------------------------------------------------------------------
				// Win::Bitmap::DIBSection::Loader is used to load a DIBSection from
				// a file or a resource.
				//---------------------------------------------------------------------

				class Loader
				{
				public:

					static Win::Bitmap::DIBSection::StrongHandle LoadFile     (const std::tstring name) ;
					static Win::Bitmap::DIBSection::StrongHandle LoadResource (const int id, const HINSTANCE hInstance) ;
					static Win::Bitmap::DIBSection::StrongHandle LoadResource (const std::tstring name, const HINSTANCE hInstance) ;
				} ;

				//---------------------------------------------------------------------
				// Used to create a DIBSection.
				//---------------------------------------------------------------------

				class Creator
				{
				public:

					//---------------------------------------------------------------------
					// Constructor.
					//---------------------------------------------------------------------

					Creator ()
					{}


					//---------------------------------------------------------------------
					// Constructor. Sets the innitial parmeters.
					//
					// Parameters:
					//
					// const unsigned int width     -> New width of the bitmap.
					// const unsigned int height    -> New height of the bitmap.
					// const unsigned int colorBits -> The number of bits for one color pixel.
					// const unsigned int colorUsed -> The number of color used in the palette
					//								   (0 if no palette).
					//---------------------------------------------------------------------

					Creator (const unsigned int width, const unsigned int height, const unsigned int colorBits, const unsigned int colorUsed)
						: _width     (width),
						  _height    (height),
						  _colorBits (colorBits),
						  _colorUsed (colorUsed)
					{}

					//---------------------------------------------------------------------
					// Changes the width and height of the future DIB section.
					//
					// Parameters:
					//
					// const unsigned int width     -> New width of the bitmap.
					// const unsigned int height    -> New height of the bitmap.
					//---------------------------------------------------------------------

					void SetDimension (const unsigned int width, const unsigned height)
					{
						_width  = width ;
						_height = height ;
					}

					//---------------------------------------------------------------------
					// Changes the number of bits per pixel.
					//
					// Parameters:
					//
					// const unsigned int colorBits -> The number of bits for one color pixel.
					//---------------------------------------------------------------------

					void SetColorBits (const unsigned int colorBits)
					{
						_colorBits = colorBits ;
					}

					//---------------------------------------------------------------------
					// Changes the number of color used in the palette.
					//
					// Parameters:
					//
					// const unsigned int colorUsed -> The number of color used in the palette
					//								   (0 if no palette).
					//---------------------------------------------------------------------

					void SetColorUsed (const unsigned int colorUsed)
					{
						_colorUsed = colorUsed ;
					}

					//---------------------------------------------------------------------
					// Changes all the parameters of the future DIB Section.
					//
					// Parameters:
					//
					// const unsigned int width     -> New width of the bitmap.
					// const unsigned int height    -> New height of the bitmap.
					// const unsigned int colorBits -> The number of bits for one color pixel.
					// const unsigned int colorUsed -> The number of color used in the palette
					//								   (0 if no palette).
					//---------------------------------------------------------------------

					void SetAllData (const unsigned int width, const unsigned int height, const unsigned int colorBits, const unsigned int colorUsed)
					{
						_width     = width ;
						_height    = height ;
						_colorBits = colorBits ;
						_colorUsed = colorUsed ;
					}

					Win::Bitmap::DIBSection::StrongHandle Create () ;

					static Win::Bitmap::DIBSection::StrongHandle Create (const unsigned int width, const unsigned int height, const unsigned int colorBits, const unsigned int colorUsed) ;


				private:

					unsigned int _width ;
					unsigned int _height ;
					unsigned int _colorBits ;
					unsigned int _colorUsed ;
				} ;

				//---------------------------------------------------------------------
				// Win::Bitmap::DIBSection::PixelPlotter is used to modify the pixel
				// of a DIB section.
				//---------------------------------------------------------------------

				class PixelPlotter 
				{
				public:

					//---------------------------------------------------------------------
					// Constructor.
					//---------------------------------------------------------------------

					PixelPlotter ()
						: _h (NULL)
					{}

					//---------------------------------------------------------------------
					// Constructor.  Set the DIB section that will be modified.
					// 
					// Parameters:
					//
					// Win::Bitmap::DIBSection::Handle handle -> The new DIB section.
					//---------------------------------------------------------------------

					PixelPlotter (Win::Bitmap::DIBSection::Handle handle)
						: _h (handle)
					{
						PlotMaker () ;
					}

					//---------------------------------------------------------------------
					// Changes the DIB section that will be modified.
					// 
					// Parameters:
					//
					// Win::Bitmap::DIBSection::Handle handle -> The new DIB section.
					//---------------------------------------------------------------------

					void SetNewDIBSectionHandle (Win::Bitmap::DIBSection::Handle handle)
					{
						_h = handle ;
						PlotMaker () ;
					}

					DWORD GetPixel (int x, int y) ;
					void  SetPixel (int x, int y, DWORD pix) ;

					Win::Bitmap::DIBSection::RGBQuad GetPixelColor (int x, int y) ;
					void							 SetPixelColor (int x, int y, Win::Bitmap::DIBSection::RGBQuad & rgb) ;

				private:

					//---------------------------------------------------------------------
					// Cannot be passed by value, use reference.
					//---------------------------------------------------------------------

					PixelPlotter (PixelPlotter & plot)
					{}

					//---------------------------------------------------------------------
					// No copy allowed!.
					//---------------------------------------------------------------------

					PixelPlotter operator = (PixelPlotter & plot)
					{}

					void PlotMaker () ;

					int MaskToRightShift (DWORD mask) ;
					int MaskToLeftShift (DWORD mask) ;
					BYTE * GetPixelPtr (DIBSECTION & ds, int x, int y) ;

				private:

					Win::Bitmap::DIBSection::Handle _h ;
					StrongArrayPointer <BYTE *>    _ptr ;
					unsigned int					_rightShift [3] ;
					unsigned int					_leftShift  [3] ;
					unsigned int					_bitFields  [3] ;					
				} ;
			}
		}

		namespace Brush
		{
			//---------------------------------------------------------------------------
			// Win::Brush::Data encapsulates a LOGBRUSH structure through private 
			// inheritance.  This class is not used directly.
			// Data members of LOGBRUSH:
			//
			// lbColor -> Color of the brush.
			// lbStyle -> A brush can have many different styles. This data member 
			//			  indicates the style of the brush.
			// lbHatch -> Depends on the lbStyle parameters.  Can be an handle to a DIB 
			//            or indicate the type of hash used.
			//---------------------------------------------------------------------------

			class Data : public Sys::Struct <LOGBRUSH>
			{
			protected:

				//---------------------------------------------------------------------
				// Constructor. Data members are initialized to 0.
				//---------------------------------------------------------------------

				Data () 
					: Sys::Struct <LOGBRUSH> ()
				{}

				//------------------------------------------------------------------
				// Constructor.  Creates a new Win::Brush::Data object with a LOGBRUSH
				// windows structure.
				//------------------------------------------------------------------

				Data (const LOGBRUSH & brush)
					: Sys::Struct <LOGBRUSH> (brush)
				{}
			} ;

			typedef Win::GDI::Handle <Win::Brush::Data, HBRUSH> Handle ; // Handle for a brush
			typedef Sys::StrongHandle<Win::Brush::Handle, Win::GDI::Disposal<HBRUSH> > StrongHandle ; // Strong handle owning the brush

			namespace Solid
			{
				//---------------------------------------------------------------------------
				// Win::Brush::Solid::Data encapsulates a LOGBRUSH structure through private 
				// inheritance.  A Win::Brush::Solid::Data object contains various parameters 
				// defining a solid brush and can be used to create a real solid brush. 
				// Win::Brush::Data is only used for solid brush.
				//
				// Data members of LOGBRUSH:
				//
				// lbColor -> Color of the brush.
				// lbStyle -> A brush can have many different styles. This data member 
				//			  indicates the style of the brush.
				// lbHatch -> Depends on the lbStyle parameters.  Can be an handle to a DIB 
				//            or indicate the type of hash used.
				//---------------------------------------------------------------------------

				class Data : public Win::Brush::Data
				{
				public:
			
					//---------------------------------------------------------------------
					// Constructor. Data members are initialized to 0.
					//---------------------------------------------------------------------

					Data () 
						: Win::Brush::Data ()
					{
						_struct.lbStyle = BS_SOLID ;
					}

					//------------------------------------------------------------------
					// Constructor.  Creates a new Win::Brush::Data object with a LOGBRUSH
					// windows structure.
					//------------------------------------------------------------------

					Data (const LOGBRUSH & brush)
						: Win::Brush::Data (brush)
					{
						_struct.lbStyle = BS_SOLID ;
					}

					//-------------------------------------------------------------------
					// Obtains the color of the brush.
					// 
					// Return value:  A Win::Color object representing the color of the 
					// brush.
					//-------------------------------------------------------------------

					Win::Color GetColor () const
					{
						return _struct.lbColor ;
					}

					void operator = (LOGBRUSH & data)
					{
						if (&_struct != &data)
						{
							::CopyMemory (&_struct, &data, sizeof (data)) ;
							_struct.lbStyle = BS_SOLID ;
						}
					}
					
				} ;

				typedef Win::GDI::Handle <Win::Brush::Solid::Data, HBRUSH> Handle ; // Handle for a brush
				typedef Sys::StrongHandle<Win::Brush::Solid::Handle, Win::GDI::Disposal<HBRUSH> > StrongHandle ; // Strong handle owning the brush

				//--------------------------------------------------------------------
				// Win::Brush::StockLoader is used to load the various type of stockbrush.
				//--------------------------------------------------------------------

				class StockLoader
				{
				public:

					StockLoader ()
					{}

					//--------------------------------------------------------------------
					// These methods are used to load the different type of stockbrush
					// 
					// Return value: a Win::Brush::StrongHandle representing the stockbrush.
					//--------------------------------------------------------------------

					static Win::Brush::Solid::StrongHandle LoadWhite        () {return Win::Brush::Solid::StrongHandle (Load (WHITE_BRUSH)) ;}
					static Win::Brush::Solid::StrongHandle LoadBlack        () {return Win::Brush::Solid::StrongHandle (Load (BLACK_BRUSH)) ;}
					static Win::Brush::Solid::StrongHandle LoadNull         () {return Win::Brush::Solid::StrongHandle (Load (NULL_BRUSH)) ;}
					static Win::Brush::Solid::StrongHandle LoadHollow       () {return Win::Brush::Solid::StrongHandle (Load (HOLLOW_BRUSH)) ;}
					static Win::Brush::Solid::StrongHandle LoadGray         () {return Win::Brush::Solid::StrongHandle (Load (GRAY_BRUSH)) ;}
					static Win::Brush::Solid::StrongHandle LoadDarkGray     () {return Win::Brush::Solid::StrongHandle (Load (DKGRAY_BRUSH)) ;}
					static Win::Brush::Solid::StrongHandle LoadLightGray    () {return Win::Brush::Solid::StrongHandle (Load (LTGRAY_BRUSH)) ;}
		
				private:

					static HBRUSH Load (const int id) ;
				} ;

				//--------------------------------------------------------------------
				// Win::Brush::Creator is used to create a new brush.
				//--------------------------------------------------------------------

				class Creator
				{
				public:

					//--------------------------------------------------------------------
					// Constructor.  Innitialize the brush data to 0.
					//--------------------------------------------------------------------

					Creator () 
					{
						_logBrush.lbStyle = BS_SOLID ;
						_logBrush.lbHatch = 0 ;
						_logBrush.lbColor = 0 ;
					}
					
					//--------------------------------------------------------------------
					// Constructor.  Innitialize the brush data with its parameters.
					// 
					// Parameters:
					//
					// const Win::Color & color    -> Color of the new brush.
					//--------------------------------------------------------------------

					Creator (const Win::Color & color)
					{
						_logBrush.lbStyle = BS_SOLID ;
						_logBrush.lbColor = color ;
						_logBrush.lbHatch = 0 ;
					}

					//--------------------------------------------------------------------
					// Changes the color of the brush that will be created.
					// 
					// Parameters:
					//
					// const Win::Color & color -> The new color.
					//--------------------------------------------------------------------

					void SetColor (const Win::Color & color) 
					{
						_logBrush.lbColor = color ;
					}

					Win::Brush::Solid::StrongHandle Create () ;

					static Win::Brush::Solid::StrongHandle Create (Win::Color & color) ;

				private:

					LOGBRUSH _logBrush ; // Data about the brush to be created.

				} ;
			}

			namespace Hatch
			{	
				// Possible type of hatch for a brush.
				enum Type {Vertical = HS_VERTICAL, Horizontal = HS_HORIZONTAL, 
					Cross = HS_CROSS, BackDiagonal = HS_BDIAGONAL, FowardDiagonal = HS_FDIAGONAL, 
					DiagonalCross = HS_DIAGCROSS} ;

				//---------------------------------------------------------------------------
				// Win::Brush::Hatch::Data encapsulates a LOGBRUSH structure through private 
				// inheritance.  a A Win::Brush::Hatch::Data object contains various parameters 
				// defining a hatch brush and can be used to create a real hatch brush.  
				// Win::Brush::Data is only used for hatch brush.
				//
				// Data members of LOGBRUSH:
				//
				// lbColor -> Color of the brush.
				// lbStyle -> A brush can have many different styles. This data member 
				//			  indicates the style of the brush.
				// lbHatch -> Depends on the lbStyle parameters.  Can be an handle to a DIB 
				//            or indicate the type of hash used.
				//---------------------------------------------------------------------------

				class Data : public Win::Brush::Data
				{
				public:

					//---------------------------------------------------------------------
					// Constructor. Data members are initialized to 0.
					//---------------------------------------------------------------------

					Data () 
						: Win::Brush::Data ()
					{
						_struct.lbStyle = BS_HATCHED ;
					}

					//------------------------------------------------------------------
					// Constructor.  Creates a new Win::Hatch::Brush::Data object with a LOGBRUSH
					// windows structure.
					//------------------------------------------------------------------

					Data (const LOGBRUSH & brush)
						: Win::Brush::Data (brush)
					{
						_struct.lbStyle = BS_HATCHED ;
					}
					
					//-------------------------------------------------------------------
					// Obtains the color of the hatch.
					// 
					// Return value:  A Win::Color object representing the color of the 
					// brush.
					//-------------------------------------------------------------------

					Win::Color GetColor () const
					{
						return _struct.lbColor ;
					}

					//-------------------------------------------------------------------
					// Obtains the type of hatch of the brush.
					// 
					// Return value:  The lbHatch data member of the LOGBRUSH structure.
					//-------------------------------------------------------------------

					Win::Brush::Hatch::Type GetHatch () const 
					{
						return static_cast <Brush::Hatch::Type> (_struct.lbHatch) ;
					}

					void operator = (LOGBRUSH & data)
					{
						if (&_struct != &data)
						{
							::CopyMemory (&_struct, &data, sizeof (data)) ;
							_struct.lbStyle = BS_HATCHED ;
						}
					}
				} ;

				typedef Win::GDI::Handle <Win::Brush::Hatch::Data, HBRUSH> Handle ; // Handle for a brush
				typedef Sys::StrongHandle<Win::Brush::Hatch::Handle, Win::GDI::Disposal<HBRUSH> > StrongHandle ; // Strong handle owning the brush

				//--------------------------------------------------------------------
				// Win::Brush::Hatch::Creator is used to create a new hatch brush.
				//--------------------------------------------------------------------

				class Creator
				{
				public:

					//--------------------------------------------------------------------
					// Constructor.  Innitialize the brush data to 0.
					//--------------------------------------------------------------------

					Creator () 
					{
						_logBrush.lbStyle = BS_HATCHED ;
						_logBrush.lbHatch = HS_VERTICAL ;
						_logBrush.lbColor = 0 ;
					}
						
					//--------------------------------------------------------------------
					// Constructor.  Innitialize the brush data with its parameters.
					// 
					// Parameters:
					//
					// const Win::Color & color    -> Color of the new brush.
					//--------------------------------------------------------------------

					Creator (const Win::Color & color, const Win::Brush::Hatch::Type type = Win::Brush::Hatch::Vertical)
					{
						_logBrush.lbStyle = BS_HATCHED ;
						_logBrush.lbHatch = type ;
						_logBrush.lbColor = color ;
					}

					//--------------------------------------------------------------------
					// Changes the color of the brush that will be created.
					// 
					// Parameters:
					//
					// const Win::Color & color -> The new color.
					//--------------------------------------------------------------------

					void SetColor (const Win::Color & color) 
					{
						_logBrush.lbColor = color ;
					}

					//-------------------------------------------------------------------
					// Changes the hatches of the brush that will be created.
					// 
					// Parameters:
					//
					// const HatchBrush::Type hatch -> The new hatch type.
					//-------------------------------------------------------------------

					void SetHatch (const Win::Brush::Hatch::Type type)  
					{
						_logBrush.lbHatch = type ;
					}

					//--------------------------------------------------------------------
					// Changes the data of the brush that will be created.
					//--------------------------------------------------------------------

					void SetAllData (const Win::Color & color, const Win::Brush::Hatch::Type type)
					{
						_logBrush.lbHatch = type ;
						_logBrush.lbColor = color ;
					}

					Win::Brush::Hatch::StrongHandle Create () ;

					static Win::Brush::Hatch::StrongHandle Create (const Win::Color & color, const Win::Brush::Hatch::Type type) ;
	

				private:

					LOGBRUSH _logBrush ; // Data about the brush to be created.

				} ;				
			}

			namespace Pattern
			{
				typedef Sys::Handle <HBRUSH> Handle ; //Handle to a pattern brush

				typedef Sys::StrongHandle<Win::Brush::Pattern::Handle, Win::GDI::Disposal<HBRUSH> > StrongHandle ; // Strong handle owning the brush 

				//--------------------------------------------------------------------
				// Win::Brush::Pattern::Creator is used to create a pattern brush.
				//--------------------------------------------------------------------

				class Creator
				{
				public:
					static Win::Brush::Pattern::StrongHandle Create (Win::Bitmap::DDB::StrongHandle handle) ;
					static Win::Brush::Pattern::StrongHandle Create (Win::Bitmap::DIBSection::StrongHandle handle) ;

				} ;
			}
		}

		namespace Pen
		{
			// Possible style for a pen.
			enum Style {Solid = PS_SOLID, Dash = PS_DASH, Dot = PS_DOT, DashDot = PS_DASHDOT, DashDotDot = PS_DASHDOTDOT} ;

			//---------------------------------------------------------------------------
			// Win::LogicalPen encapsulates a LOGPEN structure through private 
			// inheritance.  a A Win::LogicalPen object contains various parameters 
			// defining a pen and can be used to create a real pen.
			//
			// Data members of LOGPEN:
			//
			// lopnColor   -> Color of the pen.
			// lopnStyle   -> A pen can have many different styles. This data member 
			//			      indicates the style of the pen.
			// lopnWidth.x -> Width of the pen.
			//---------------------------------------------------------------------------

			class Data : public Sys::Struct <LOGPEN>
			{
			public:

				//---------------------------------------------------------------------
				// Constructor. Data members are initialized to 0.
				//---------------------------------------------------------------------

				Data () 
					: Sys::Struct <LOGPEN> ()
				{}

				//------------------------------------------------------------------
				// Constructor.  Creates a new Win::Pen::Data object with a LOGPEN
				// windows structure.
				//------------------------------------------------------------------

				Data (const LOGPEN & pen)
					: Sys::Struct <LOGPEN> (pen)
				{}

				//-------------------------------------------------------------------
				// Obtains the style of the pen.
				// 
				// Return value:  The lopnStyle data member of the LOGPEN structure.
				//-------------------------------------------------------------------

				Win::Pen::Style GetStyle () const 
				{
					return static_cast <Win::Pen::Style> (_struct.lopnStyle) ;
				}

				//--------------------------------------------------------------------
				// Obtains the width of the pen.
				// 
				// Return value:  The lopnWidth.x data member of the LOGPEN structure.
				//--------------------------------------------------------------------

				LONG GetWidth () const 
				{
					return _struct.lopnWidth.x ;
				}

				//-------------------------------------------------------------------
				// Obtains the color of the pen.
				// 
				// Return value:  A Win::Color object representing the color of the 
				//				  pen.
				//-------------------------------------------------------------------

				Win::Color GetColor () const 
				{
					return _struct.lopnColor ;
				}
			} ;

			typedef Win::GDI::Handle <Win::Pen::Data, HPEN> Handle ; // Handle for a pen
			typedef Sys::StrongHandle<Win::Pen::Handle, Win::GDI::Disposal<HPEN> > StrongHandle ; // Strong handle owning the pen./

			//--------------------------------------------------------------------
			// Win::Pen::StockLoader is used to load the various type of stockpen.
			//--------------------------------------------------------------------

			class StockLoader
			{
			public:

				StockLoader ()
				{}

				//--------------------------------------------------------------------
				// These methods are used to load the different type of stockpen
				// 
				// Return value: a Win::Pen::StrongHandle representing the stockpen.
				//--------------------------------------------------------------------

				static Win::Pen::StrongHandle LoadWhite () {return Win::Pen::StrongHandle (Load (WHITE_PEN)) ;}
				static Win::Pen::StrongHandle LoadBlack () {return Win::Pen::StrongHandle (Load (BLACK_PEN)) ;}
				static Win::Pen::StrongHandle LoadNull  () {return Win::Pen::StrongHandle (Load (NULL_PEN)) ;}
				
			private:

				static HPEN Load (const int id) ;
			} ;

			//--------------------------------------------------------------------
			// Win::Pen::Creator is used to create a new pen.
			//--------------------------------------------------------------------

			class Creator
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Innitialize the pen data to 0.
				//--------------------------------------------------------------------

				Creator () 
				{
					memset (&_logPen, 0, sizeof(LOGPEN)) ;
				}
				
				//--------------------------------------------------------------------
				// Constructor.  Innitialize the pen data with its parameters.
				// 
				// Parameters:
				//
				// const Win::Color & color    -> Color of the new pen.
				// const Win::Pen::Style style -> Style of the new pen.
				// const LONG width            -> Width of the new pen.
				//--------------------------------------------------------------------

				Creator (const Win::Color & color, const Win::Pen::Style style = Win::Pen::Solid, const LONG width = 0)
				{
					_logPen.lopnColor   = color ;
					_logPen.lopnStyle   = style ;
					_logPen.lopnWidth.x = width ;
				}

				//--------------------------------------------------------------------
				// Changes the width of the pen that will be created.
				// 
				// Parameters:
				//
				// const LONG width -> The new width.
				//--------------------------------------------------------------------

				void SetWidth (const LONG width)
				{
					_logPen.lopnWidth.x = width ;
				}

				//--------------------------------------------------------------------
				// Changes the style of the pen that will be created.
				// 
				// Parameters:
				//
				// const Win::Pen::Style style -> The new style.
				//--------------------------------------------------------------------

				void SetStyle (const Win::Pen::Style style)
				{
					_logPen.lopnStyle = style ;
				}

				//--------------------------------------------------------------------
				// Changes the color of the pen that will be created.
				// 
				// Parameters:
				//
				// const Win::Color & color -> The new color.
				//--------------------------------------------------------------------

				void SetColor (const Win::Color & color) 
				{
					_logPen.lopnColor = color ;
				}

				void SetAllData (const Win::Color & color, const Win::Pen::Style style, const LONG width) ;

				Win::Pen::StrongHandle Create () ;

				static Win::Pen::StrongHandle Create (const Win::Color & color, const  Win::Pen::Style style, const LONG width) ;

			private:

				LOGPEN _logPen ; // Data about the pen to be created.

			} ;
		}

		namespace ExtendedPen
		{
			// Possible type for a extended pen.
			enum Type   {Geometric = PS_GEOMETRIC, Cosmetic = PS_COSMETIC} ;

			// Possible ¸EndCap for a extended pen.
			enum EndCap {Round = PS_ENDCAP_ROUND, Square = PS_ENDCAP_SQUARE, Flat = PS_ENDCAP_FLAT} ;

			// Possible Join for a extended pen.
			enum Join   {Bevel = PS_JOIN_BEVEL, Miter = PS_JOIN_MITER, RoundJ = PS_JOIN_ROUND} ;

			namespace Color
			{
					//---------------------------------------------------------------------------
					// Win::ExtendedPen::Color::Data encapsulates a EXTLOGPEN structure through private 
					// inheritance.  a A Win::ExtendedPen::Data object contains various 
					// parameters defining an extended pen that can be used to create a real 
					// extended pen.
					//
					// Data members of EXTLOGPEN:
					//
					// elpPenStyle      -> Style of the pen.
					// elpWidth         -> Width of the pen.
					// elpBrushStyle    -> Style of the brush used by the pen.
					// elpColor         -> Color of the brush used by the pen.
					// elpHatch         -> Type of hatch used by the brush.
					// elpNumEntries    -> Not used by the class.
					// elpStyleEntry[1] -> Not use by the class.
					//---------------------------------------------------------------------------

					class Data : public Sys::Struct <EXTLOGPEN>
					{
						//friend class Win::ExtendedPen::Creator ;

					public:

						//---------------------------------------------------------------------
						// Constructor. Data members are initialized to 0.
						//---------------------------------------------------------------------

						Data () 
							: Sys::Struct <EXTLOGPEN> ()
						{
							_struct.elpBrushStyle    = BS_SOLID ; 
							_struct.elpHatch         = 0 ; 
						}

						//------------------------------------------------------------------
						// Constructor.  Creates a new Win::ExtendedPen::Data object with a
						// EXTLOGPEN windows structure.
						//------------------------------------------------------------------

						Data (const EXTLOGPEN & extPen)
							: Sys::Struct <EXTLOGPEN> (extPen)
						{
							_struct.elpBrushStyle    = BS_SOLID ; 
							_struct.elpHatch         = 0 ; 
						}

						//-------------------------------------------------------------------
						// Obtains the width of the extended pen.
						// 
						// Return value:  The elpWidth data member of the EXTLOGPEN 
						// structure.
						//-------------------------------------------------------------------

						UINT GetWidth () const 
						{
							return _struct.elpWidth ;
						}

						//-------------------------------------------------------------------
						// Obtains the style of the extended pen.
						// 
						// Return value:  The style of the extended pen.
						//-------------------------------------------------------------------

						Win::Pen::Style GetStyle () const
						{
							return static_cast <Win::Pen::Style> (_struct.elpPenStyle & 0x00000007) ;
						}

						//-------------------------------------------------------------------
						// Obtains the type of the extended pen.
						// 
						// Return value:  The type of the extended pen.
						//-------------------------------------------------------------------

						Win::ExtendedPen::Type GetType () const
						{
							return static_cast <Win::ExtendedPen::Type> (_struct.elpPenStyle & 0x00010000) ;
						}

						//-------------------------------------------------------------------
						// Obtains the end cap of the extended pen.
						// 
						// Return value:  The end cap of the extended pen.
						//-------------------------------------------------------------------

						Win::ExtendedPen::EndCap GetEndCap () const
						{
							return static_cast <Win::ExtendedPen::EndCap> (_struct.elpPenStyle & 0x00000300) ;
						}

						//-------------------------------------------------------------------
						// Obtains the join of the extended pen.
						// 
						// Return value:  The join of the extended pen.
						//-------------------------------------------------------------------

						Win::ExtendedPen::Join GetJoin () const
						{
							return static_cast <Win::ExtendedPen::Join> (_struct.elpPenStyle & 0x00003000) ;
						}

						Win::Color GetColor () const
						{
							return _struct.elpColor ;
						}
					} ;

					typedef Win::GDI::Handle <Win::ExtendedPen::Color::Data, HPEN> Handle ; // Handle for a extended pen
					typedef Sys::StrongHandle<Win::ExtendedPen::Color::Handle, Win::GDI::Disposal<HPEN> > StrongHandle ; // Strong handle owning the extended pen.

					//--------------------------------------------------------------------
					// Win::ÈxtendedPen::Color::Creator is used to create a new pen.
					//--------------------------------------------------------------------

					class Creator
					{
					public:

						//--------------------------------------------------------------------
						// Constructor.  Innitialize the pen data to 0.
						//--------------------------------------------------------------------

						Creator ()
							: _width (0),
							  _style (Win::Pen::Solid),
					   		  _join  (Win::ExtendedPen::Bevel),
							  _endCap (Win::ExtendedPen::Round),
							  _type   (Win::ExtendedPen::Geometric)
							  
						{
							memset (&_logBrush, 0, sizeof(LOGBRUSH)) ;
							_logBrush.lbStyle = BS_SOLID ;

						}

						//--------------------------------------------------------------------
						// Constructor.  Innitialize the pen data with its parameters.
						// 
						// Parameters:
						//
						// const Win::Pen::Style style           -> Style of the pen.
						// const Win::ExtendedPen::Type type     -> Type of the pen.
						// const Win::ExtendedPen::EndCap endCap -> End caps of the pen
						// const Win::ExtendedPen::Join join     -> Join of the pen.
						// const LONG width                      -> Width of the pen.
						// Win::Brush::Data brush                -> Data on the solid brush 
						//											used to create de pen.
						//--------------------------------------------------------------------


						Creator (const Win::Color & color, const Win::Pen::Style style = Win::Pen::Solid, const Win::ExtendedPen::Type type = Win::ExtendedPen::Geometric,
							const Win::ExtendedPen::EndCap endCap = Win::ExtendedPen::Flat, const Win::ExtendedPen::Join join = Win::ExtendedPen::Bevel,
							const UINT width = 0)
						{
							SetAllData (color, style, type, endCap, join, width) ;
							_logBrush.lbStyle = BS_SOLID ;
							_logBrush.lbHatch = 0 ;
						}


						//--------------------------------------------------------------------
						// Changes the width of the pen that will be created.
						// 
						// Parameters:
						//
						// const LONG width -> The new width.
						//--------------------------------------------------------------------

						void SetWidth (const LONG width)
						{
							_width = width ;
						}

						//--------------------------------------------------------------------
						// Changes the style of the pen that will be created.
						// 
						// Parameters:
						//
						// const Win::Pen::Style style -> The new style.
						//--------------------------------------------------------------------


						void SetStyle (const Win::Pen::Style style)
						{
							_style = style ;
						}

						//--------------------------------------------------------------------
						// Changes the type of the pen that will be created.
						// 
						// Parameters:
						//
						// const Win::ExtendedPen::Type type-> The new type.
						//--------------------------------------------------------------------

						void SetType (const Win::ExtendedPen::Type type)
						{
							_type = type ;
						}

						//--------------------------------------------------------------------
						// Changes the endcaps of the pen that will be created.
						// 
						// Parameters:
						//
						// const Win::ExtendedPen::EndCap-> The new endcaps.
						//--------------------------------------------------------------------

						void SetEndCap (const Win::ExtendedPen::EndCap endCap)
						{
							_endCap = endCap ;
						}

						//--------------------------------------------------------------------
						// Changes the join of the pen that will be created.
						// 
						// Parameters:
						//
						// const Win::ExtendedPen::Join join-> The new join.
						//--------------------------------------------------------------------

						void SetJoin (const Win::ExtendedPen::Join join)
						{
							_join = join ;
						}

						//--------------------------------------------------------------------
						// Changes the brush data of the pen that will be created.
						// 
						// Parameters:
						//
						// const Win::Brush::Solid::Data & data -> The new brush data.
						//--------------------------------------------------------------------

						void SetColor (Win::Color & color)
						{
							_logBrush.lbColor = color ;
						}

						//--------------------------------------------------------------------
						// Changes all the data of the pen that will be created.
						//--------------------------------------------------------------------

						void SetAllData (const Win::Color & color, const Win::Pen::Style style, const Win::ExtendedPen::Type type,
							const Win::ExtendedPen::EndCap endCap, const Win::ExtendedPen::Join join,const UINT width) ;

						Win::ExtendedPen::Color::StrongHandle Create () ;

						static Win::ExtendedPen::Color::StrongHandle Create (const Win::Color & color, const Win::Pen::Style style, const Win::ExtendedPen::Type type,
							const Win::ExtendedPen::EndCap endCap, const Win::ExtendedPen::Join join,const UINT width) ;


					private:

						LOGBRUSH				 _logBrush ;
						LONG                     _width ;
						Win::Pen::Style			 _style ;
						Win::ExtendedPen::EndCap _endCap ;
						Win::ExtendedPen::Join   _join ;
						Win::ExtendedPen::Type   _type ;
				
					} ;
				}	
		}

		namespace Font
		{
			enum VerticalTextAlign   {BaseLine = TA_BASELINE, Bottom = TA_BOTTOM, Top = TA_TOP} ;
			enum HorizontalTextAlign {Left = TA_LEFT, Right = TA_RIGHT, Center = TA_CENTER} ;
			enum UpdateCurrentPos    {NoUpdate = TA_NOUPDATECP, Update = TA_UPDATECP} ;

			// Possible weight for a font.
			enum Weight     {DefaultWeight = FW_DONTCARE, Thin = FW_THIN, ExtraLight = FW_EXTRALIGHT, Light = FW_EXTRALIGHT, Normal = FW_NORMAL,
						      Medium = FW_MEDIUM, SemiBold = FW_SEMIBOLD, Bold = FW_BOLD, ExtraBold = FW_EXTRABOLD, Black = FW_BLACK} ;
		
			// Possible character set for a font.
			enum CharSet    { Ansi = ANSI_CHARSET, Baltic = BALTIC_CHARSET, ChineseBig5 = CHINESEBIG5_CHARSET, DefaultCharSet = DEFAULT_CHARSET,
						      EastEurope = EASTEUROPE_CHARSET, Gb2312 = GB2312_CHARSET, Greek = GREEK_CHARSET, Hangul = HANGUL_CHARSET,
						      Mac = MAC_CHARSET, Oem = OEM_CHARSET, Russian = RUSSIAN_CHARSET, Shiftjis = SHIFTJIS_CHARSET, Symbol = SYMBOL_CHARSET,
						      Turkish = TURKISH_CHARSET } ;

			// Possible output precision for a font.
			enum OutPrecis  { OutCharacter = OUT_CHARACTER_PRECIS, OutDefault = OUT_DEFAULT_PRECIS, OutDevice = OUT_DEVICE_PRECIS,
							  OutOutline = OUT_OUTLINE_PRECIS, OutRaster = OUT_RASTER_PRECIS, OutString = OUT_STRING_PRECIS,
							  OutStroke = OUT_STROKE_PRECIS, OutTrueTypeOnly = OUT_TT_ONLY_PRECIS, OutTrueType = OUT_TT_PRECIS } ;

			// Possible clipping precision for a font.
			enum ClipPrecis { ClipDefault = CLIP_DEFAULT_PRECIS, ClipCharacter = CLIP_CHARACTER_PRECIS, ClipStroke = CLIP_STROKE_PRECIS,
							  ClipMask = CLIP_MASK, ClipEmbedded = CLIP_EMBEDDED, ClipLhAngles = CLIP_LH_ANGLES, ClipTrueTypeAway = CLIP_TT_ALWAYS} ;

			// Possible type for a font.
			enum Quality    { DefaultQuality = DEFAULT_QUALITY, Draft = DRAFT_QUALITY, Proof = PROOF_QUALITY } ;

			// Possible pitch for a font.
			enum Pitch      {DefaultPitch = DEFAULT_PITCH, Fixed = FIXED_PITCH, Variable = VARIABLE_PITCH } ;

			// Possible family for a font.
			enum Family   {Decorative = FF_DECORATIVE, DefaultFamily = FF_DONTCARE, Modern = FF_MODERN, Roman = FF_ROMAN, Script = FF_SCRIPT, Swiss =FF_SWISS } ;

			//---------------------------------------------------------------------------
			// Win::Font::Data encapsulates a LOGFONT structure through private 
			// inheritance.  a A Win::Font::Data object contains various 
			// parameters defining a font that can be used to create a real font.
			//
			// Data members of LOGFONT:
			//
			// lfHeight                -> Height of the characters.
			// lfWidth                 -> Width of the characters.
			// lfEscapement            -> Angle, in tenth of degree, between the 
			//							  escapement vector and the x-axis.
			// lfOrientation		   -> Orientation of the font.
			// lfWeight                -> Determines if the characters are bold.
			// lfItalic                -> Determines if the characters are italic.
			// lfUnderline             -> Determines if the characters are underlined.
			// lfStrikeOut             -> Determines if the characters are strike out.
			// lfCharSet               -> The char set used by the font.
			// lfOutPrecision          -> The output precision of the font.
			// lfClipPrecision         -> The clipping precision of the font.
			// lfQuality               -> The output quality of the font.
			// lfPitchAndFamily        -> The pitch and the family of the font.
			// lfFaceName[LF_FACESIZE] -> Typeface name of the font.
			//---------------------------------------------------------------------------

			class Data : public Sys::Struct <LOGFONT>
			{
			public:

				//---------------------------------------------------------------------
				// Constructor. Data members are initialized to 0.
				//---------------------------------------------------------------------

				Data () 
					: Sys::Struct <LOGFONT> ()
				{}

				Data (const LOGFONT & font)
					: Sys::Struct <LOGFONT> ()
				{}
	
				//-------------------------------------------------------------------
				// Obtains the height of the font.
				// 
				// Return value:  The lfHeight data member of the LOGFONT structure.
				//-------------------------------------------------------------------

				LONG GetHeight () const 
				{
					return _struct.lfHeight ; 
				}

				//-------------------------------------------------------------------
				// Obtains the width of the font.
				// 
				// Return value:  The lfWidth data member of the LOGFONT structure.
				//-------------------------------------------------------------------

				LONG GetWidth () const 
				{
					return _struct.lfWidth ; 
				}

				//-------------------------------------------------------------------
				// Obtains the escapement of the font.
				// 
				// Return value:  The lfEscapement data member of the LOGFONT 
				// structure.
				//-------------------------------------------------------------------

				LONG GetEscapement () const 
				{
					return _struct.lfEscapement ; 
				}

				//-------------------------------------------------------------------
				// Obtains the orientation of the font.
				// 
				// Return value:  The lfOrientation data member of the LOGFONT 
				// structure.
				//-------------------------------------------------------------------

				LONG GetOrientation () const 
				{
					return _struct.lfOrientation ; 
				}

				//-------------------------------------------------------------------
				// Obtains the weight of the font.
				// 
				// Return value:  The lfWeight data member of the LOGFONT structure.
				//-------------------------------------------------------------------

				LONG GetWeight () const 
				{
					return _struct.lfWeight ; 
				}

				//-------------------------------------------------------------------
				// Determines if the font is italic.
				// 
				// Return value:  True if the font is italic, else false.
				//-------------------------------------------------------------------

				bool IsItalic () const 
				{
					return _struct.lfItalic == TRUE ; 
				}

				//-------------------------------------------------------------------
				// Determines if the font is underlined.
				// 
				// Return value:  True if the font is underlined, else false.
				//-------------------------------------------------------------------

				bool IsUnderline () const 
				{
					return _struct.lfUnderline == TRUE ; 
				}

				//-------------------------------------------------------------------
				// Determines if the font is strike out.
				// 
				// Return value:  True if the font is strike out, else false.
				//-------------------------------------------------------------------

				bool IsStrikeOut () const 
				{
					return _struct.lfStrikeOut == TRUE ; 
				}

				//-------------------------------------------------------------------
				// Obtains the char set of the font.
				// 
				// Return value:  The lfCharSet data member of the LOGFONT structure.
				//-------------------------------------------------------------------

				Win::Font::CharSet GetCharSet () const 
				{
					return static_cast <Win::Font::CharSet> (_struct.lfCharSet) ;
				}

				//-------------------------------------------------------------------
				// Obtains the output precision of the font.
				// 
				// Return value:  The lfOutPrecision data member of the LOGFONT 
				// structure.
				//-------------------------------------------------------------------

				Win::Font::OutPrecis GetOutPrecision () const 
				{
					return static_cast <Win::Font::OutPrecis> (_struct.lfOutPrecision) ; 
				}

				//-------------------------------------------------------------------
				// Obtains the clip precision of the font.
				// 
				// Return value:  The lfClipPrecision data member of the LOGFONT 
				// structure.
				//-------------------------------------------------------------------

				Win::Font::ClipPrecis GetClipPrecision () const 
				{
					return static_cast <Win::Font::ClipPrecis> (_struct.lfClipPrecision) ; 
				}

				//-------------------------------------------------------------------
				// Obtains the quality of the font.
				// 
				// Return value:  The lfQuality data member of the LOGFONT 
				// structure.
				//-------------------------------------------------------------------

				Win::Font::Quality GetQuality () const 
				{
					return static_cast <Win::Font::Quality> (_struct.lfQuality) ; 
				}

				//-------------------------------------------------------------------
				// Obtains the pitch of the font.
				// 
				// Return value:  The low byte of the lfPitchAndFamily data member 
				// of the LOGFONT structure.
				//-------------------------------------------------------------------

				Win::Font::Pitch GetPitch () const 
				{
					return static_cast <Win::Font::Pitch> (_struct.lfPitchAndFamily & 0x03) ;
				}
				
				//-------------------------------------------------------------------
				// Obtains the family of the font.
				// 
				// Return value:  The high byte of the lfPitchAndFamily data member 
				// of the LOGFONT structure.
				//-------------------------------------------------------------------

				Win::Font::Family GetFamily () const 
				{
					return static_cast <Win::Font::Family> (_struct.lfPitchAndFamily & 0xF0) ;
				}

				//-------------------------------------------------------------------
				// Obtains the face name of the font.
				// 
				// Return value:  The lfFaceName data member of the LOGFONT 
				// structure.
				//-------------------------------------------------------------------

				const std::tstring GetFaceName () const 
				{
					return _struct.lfFaceName ;
				} 
			} ;

			//---------------------------------------------------------------------------
			// Win::TextMetrics encapsulates a TEXTMETRICS structure through private 
			// inheritance.  a A Win::TextMetrics object contains various 
			// data about a physical font.
			//
			// Data members of LOGFONT:
			//
			//
			// tmHeight           -> Height of a character.
			// tmAscent           -> Units above the baseline of the character.
			// tmDescent          -> Units below the baseline of the character.
			// tmInternalLeading  -> Amount of internal leading.
			// tmExternalLeading  -> Amount of external leading.
			// tmAveCharWidth     -> Average width of the characters.
			// tmMaxCharWidth     -> Maximum width of a character.
			// tmWeight			  -> Weight of the font.
			// tmOverhang		  -> The extra width per string that can be added to 
			//						 some synthesized fonts
			// tmDigitizedAspectX -> The horizontal aspect of the device the font was
			//						 define for.
			// tmDigitizedAspectY -> The vertical aspect of the device the font was
			//						 define for.
			// tmFirstChar		  -> First character defined by the font
			// tmLastChar         -> Last character defined by the font
			// tmDefaultChar      -> Character that replace the characters not present
			//					  -> in the font.
			// tmBreakChar		  -> Character used to define word break.
			// tmItalic			  -> True if the font is italic.
			// tmUnderlined       -> True if the font is underlined.
			// tmStruckOut        -> True if the font is struct out.
			// tmPitchAndFamily   -> The pitch and family of the font.
			// tmCharSet          -> The char set of the font.
			//---------------------------------------------------------------------------

			class TextMetrics : public Sys::Struct <TEXTMETRIC>
			{
			public:	
				
				// Possible pitch technologie  for a font.
				enum PitchTechnologie {FixedPitch = TMPF_FIXED_PITCH, Vector = TMPF_VECTOR, TrueType = TMPF_TRUETYPE, Device = TMPF_DEVICE} ;

				//---------------------------------------------------------------------
				// Constructor. Data members are initialized to 0.
				//---------------------------------------------------------------------

				TextMetrics ()
				{}

				TextMetrics (TEXTMETRIC textMetric)
					: Sys::Struct <TEXTMETRIC> (textMetric)
				{}

				//-------------------------------------------------------------------
				// Obtains the height of the Win::TextMetrics object.
				// 
				// Return value:  The tmHeight data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetHeight () const 
				{
					return _struct.tmHeight ;
				}

				//-------------------------------------------------------------------
				// Obtains the total height (including external leading) of the
				// Win::TextMetrics object.
				// 
				// Return value:  The sum oftmHeight and tmExternalLeading. 
				//-------------------------------------------------------------------

				LONG GetTotalHeight () const 
				{
					return _struct.tmHeight + _struct.tmExternalLeading ;
				}

				//-------------------------------------------------------------------
				// Obtains the ascent of the Win::TextMetrics object.
				// 
				// Return value:  The tmAscent data member of the TEXTMETRICS  
				// structure.
				//-------------------------------------------------------------------

				LONG GetAscent () const 
				{
					return _struct.tmAscent ;
				}

				//-------------------------------------------------------------------
				// Obtains the descent of the Win::TextMetrics object.
				// 
				// Return value:  The tmDescent data member of the TEXTMETRICS  
				// structure.
				//-------------------------------------------------------------------

				LONG GetDescent () const 
				{
					return _struct.tmDescent ;
				}
				
				//-------------------------------------------------------------------
				// Obtains the internal leading of the Win::TextMetrics object.
				// 
				// Return value:  The tmInternalLeading data member of the TEXTMETRICS  
				// structure.
				//-------------------------------------------------------------------

				LONG GetInternalLeading () const 
				{
					return _struct.tmInternalLeading ;
				}
				
				//-------------------------------------------------------------------
				// Obtains the external leading of the Win::TextMetrics object.
				// 
				// Return value:  The tmExternalLeading data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetExternalLeading () const 
				{
					return _struct.tmExternalLeading ;
				}

				//-------------------------------------------------------------------
				// Obtains the average width of a character
				// 
				// Return value:  The tmAveCharWidth data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetAverageWitdh () const 
				{
					return _struct.tmAveCharWidth ;
				}

				//-------------------------------------------------------------------
				// Obtains the average width of a capital character.
				// 
				// Return value:  The value of a calcul determining the average width
				//                of a capital character.
				//-------------------------------------------------------------------

				LONG GetAverageCapWidth () const 
				{
					return (_struct.tmPitchAndFamily & 1 ? 3 : 2) * _struct.tmAveCharWidth / 2 ;
				}

				//-------------------------------------------------------------------
				// Obtains the maximum width of a character
				// 
				// Return value:  The tmMaxCharWidth data member of the 
				// TEXTMETRICS structure.
				//-------------------------------------------------------------------

				LONG GetMaxWidth () const 
				{
					return _struct.tmMaxCharWidth ;
				}

				//-------------------------------------------------------------------
				// Obtains the weight of the Win::TextMetrics object.
				// 
				// Return value:  The tmHeight data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetWeight () const 
				{
					return _struct.tmWeight ;
				}

				//-------------------------------------------------------------------
				// Obtains the Overbang of the Win::TextMetrics object.
				// 
				// Return value:  The tmOverbang data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetOverhang () const 
				{
					return _struct.tmOverhang;
				}

				//-------------------------------------------------------------------
				// Obtains the digitized aspect X of the Win::TextMetrics object.
				// 
				// Return value:  The tmDigitizedAspectX data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetDigitizedAspectX () const 
				{
					return _struct.tmDigitizedAspectX ;
				}

				//-------------------------------------------------------------------
				// Obtains the digitized aspect Y of the Win::TextMetrics object.
				// 
				// Return value:  The tmDigitizedAspectY data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				LONG GetDigitizedAspectY () const 
				{
					return _struct.tmDigitizedAspectY ;
				}

				//-------------------------------------------------------------------
				// Obtains the first character defined in the font represented by
				// the Win::TextMetrics object.
				// 
				// Return value:  The tmFirstChar data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				BCHAR GetFirstChar () const 
				{
					return _struct.tmFirstChar ;
				}

				//-------------------------------------------------------------------
				// Obtains the last character defined in the font represented by
				// the Win::TextMetrics object.
				// 
				// Return value:  The tmLastChar data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				BCHAR GetLastChar () const 
				{
					return _struct.tmLastChar ;
				}

				//-------------------------------------------------------------------
				// Obtains the character used for characters not defined in the font 
				// represented by the Win::TextMetrics object.
				// 
				// Return value:  The tmDefaultChar data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				BCHAR GetDefaultChar () const 
				{
					return _struct.tmDefaultChar ;
				}

				//-------------------------------------------------------------------
				// Obtains the character used to define word break in the font 
				// represented by the Win::TextMetrics object.
				// 
				// Return value:  The tmBreakChar data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				BCHAR GetBreakChar () const 
				{
					return _struct.tmBreakChar ;
				}

				//-------------------------------------------------------------------
				// Determines if the font represented by the Win::TextMetrics object
				// is italic.
				// 
				// Return value:  True if the font is italic, else false.
				//-------------------------------------------------------------------

				bool IsItalic () const 
				{
					return _struct.tmItalic != 0 ;
				}
				
				//-------------------------------------------------------------------
				// Determines if the font represented by the Win::TextMetrics object
				// is underline.
				// 
				// Return value:  True if the font is underline, else false.
				//-------------------------------------------------------------------

				bool IsUnderlined () const 
				{
					return _struct.tmUnderlined != 0 ;
				}
				
				//-------------------------------------------------------------------
				// Determines if the font represented by the Win::TextMetrics object
				// is struck out.
				// 
				// Return value:  True if the font is struct out, else false.
				//-------------------------------------------------------------------

				bool IsStruckOut () const 
				{
					return _struct.tmStruckOut != 0 ;
				}
				
				//-------------------------------------------------------------------
				// Obtains thefamily of the Win::TextMetrics object.
				// 
				// Return value:  The family of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				Win::Font::Family GetFamily () const 
				{
					return static_cast <Win::Font::Family> (_struct.tmPitchAndFamily & 0xF0) ;
				}
				
				//-------------------------------------------------------------------
				// Obtains the pitch technologie of the Win::TextMetrics object.
				// 
				// Return value:  The pitch technologie of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				Win::Font::TextMetrics::PitchTechnologie GetPitch () const 
				{
					return static_cast <Win::Font::TextMetrics::PitchTechnologie> (_struct.tmPitchAndFamily & 0x02) ;
				}

				//-------------------------------------------------------------------
				// Obtains the char set of the Win::TextMetrics object.
				// 
				// Return value:  The tmCharSet data member of the TEXTMETRICS 
				// structure.
				//-------------------------------------------------------------------

				Win::Font::CharSet GetCharSet () const 
				{
					return static_cast <Win::Font::CharSet> (_struct.tmCharSet) ;
				} 
			} ;

			// Handle for a font
			class Handle : public Win::GDI::Handle <Win::Font::Data, HFONT>
			{ 
			public:

				Handle (HFONT font = NULL)
					: Win::GDI::Handle <Win::Font::Data, HFONT> (font)
				{}

				void GetTextMetrics (Win::Font::TextMetrics & textMetrics) ;
			} ;

			typedef Sys::StrongHandle<Win::Font::Handle, Win::GDI::Disposal<HFONT> > StrongHandle ; // Strong handle owning the brush

				//--------------------------------------------------------------------
				// Win::Font::StockLoader is used to load the various type of stockfont.
				//--------------------------------------------------------------------

				class StockLoader
				{
				public:

					StockLoader ()
					{}

					//--------------------------------------------------------------------
					// These methods are used to load the different type of stockfont
					// 
					// Return value: a Win::Font::StrongHandle representing the stockfont.
					//--------------------------------------------------------------------

					static Win::Font::StrongHandle LoadFixedAnsi   () {return Win::Font::StrongHandle (Load (ANSI_FIXED_FONT)) ;}
					static Win::Font::StrongHandle LoadVarAnsi     () {return Win::Font::StrongHandle (Load (ANSI_VAR_FONT)) ;}
					static Win::Font::StrongHandle LoadDefaultGui  () {return Win::Font::StrongHandle (Load (DEFAULT_GUI_FONT)) ;}
					static Win::Font::StrongHandle LoadFixedOem    () {return Win::Font::StrongHandle (Load (OEM_FIXED_FONT)) ;}
					static Win::Font::StrongHandle LoadSystem      () {return Win::Font::StrongHandle (Load (SYSTEM_FONT)) ;}
					static Win::Font::StrongHandle LoadFixedSystem () {return Win::Font::StrongHandle (Load (SYSTEM_FIXED_FONT)) ;}
		
				private:

					static HFONT Load (const int id) ;
				} ;

				//--------------------------------------------------------------------
				// Win::Font::Creator is used to create a new font.
				//--------------------------------------------------------------------

				class Creator
				{
				public:
					
					//--------------------------------------------------------------------
					// Constructor.  Innitialize the brush data to 0.
					//--------------------------------------------------------------------
					Creator ()
					{
						memset (&_logFont, 0, sizeof(LOGFONT)) ;
					}

					//--------------------------------------------------------------------
					// Constructor.  Innitialize the brush data with its parameters.
					// 
					// Parameters:
					//
					// const Win::Color & color    -> Color of the new brush.
					//--------------------------------------------------------------------

					Creator (const std::tstring face, const Win::Font::CharSet charSet = Win::Font::DefaultCharSet, const int height = 0, const int width = 0, const int escapement = 0, const int orientation = 0, 
						     const Win::Font::Weight weight = Win::Font::DefaultWeight, const bool italic = false, const bool underline = false, const bool strikeOut = false, 
						     const Win::Font::OutPrecis outputPrescision = Win::Font::OutDefault, const Win::Font::ClipPrecis clipPrescision = ClipDefault, const Win::Font::Quality quality = Win::Font::DefaultQuality, 
						     const Win::Font::Pitch pitch = Win::Font::DefaultPitch, const Win::Font::Family family = Win::Font::DefaultFamily) 
					{
						SetAllData (face, charSet, height, width, escapement, orientation, weight, italic, underline, strikeOut, outputPrescision, clipPrescision, quality, pitch, family) ;
					}

					//-------------------------------------------------------------------
					// Changes the height of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG height -> The new height.
					//-------------------------------------------------------------------

					void SetHeight (const LONG height) 
					{
						_logFont.lfHeight = height ;
					}

					//-------------------------------------------------------------------
					// Changes the width of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG width -> The new width.
					//-------------------------------------------------------------------

					void SetWidth (const LONG width)  
					{
						_logFont.lfWidth = width ;
					}

					//-------------------------------------------------------------------
					// Changes the escapement of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG escapement -> The new escapement.
					//-------------------------------------------------------------------

					void SetEscapement (const LONG escapement) 
					{
						_logFont.lfEscapement = escapement ;
					}

					//-------------------------------------------------------------------
					// Changes the orientation of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG orientation -> The new orientation.
					//-------------------------------------------------------------------

					void SetOrientation (const LONG orientation) 
					{
						_logFont.lfOrientation = orientation ;
					}

					//-------------------------------------------------------------------
					// Changes the weight of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG weight -> The new weight.
					//-------------------------------------------------------------------

					void SetWeight (const LONG weight) 
					{
						_logFont.lfWeight = weight ;
					}

					//-------------------------------------------------------------------
					// Changes the italic of the font that will be created.
					// 
					// Parameters:
					//
					// const bool italic -> If true the font is made italic, else
					//                      the font is made not italic.
					//-------------------------------------------------------------------

					void SetItalic (const bool italic = true) 
					{
						_logFont.lfItalic = italic ;
					}

					//-------------------------------------------------------------------
					// Changes the underline of the font that will be created.
					// 
					// Parameters:
					//
					// const bool under -> If true the font is made underline, else
					//                      the font is made not underline.
					//-------------------------------------------------------------------

					void SetUnderline (const bool under = true) 
					{
						_logFont.lfUnderline = under ;
					}

					//-------------------------------------------------------------------
					// Makes the Win::Font::Data object strike out or not.
					// 
					// Parameters:
					//
					// const bool strike -> If true the font is made strike out, else
					//                      the font is made not strike out.
					//-------------------------------------------------------------------

					void SetStrikeOut (const bool strike = true) 
					{
						_logFont.lfStrikeOut = strike ;
					}

					//-------------------------------------------------------------------
					// Changes the charset of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE charset -> The new char set.
					//-------------------------------------------------------------------

					void SetCharSet (const Win::Font::CharSet charset) 
					{
						_logFont.lfCharSet = charset ;
					}

					//-------------------------------------------------------------------
					// Changes the output precision of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE precision -> The new output precision.
					//-------------------------------------------------------------------

					void SetOutPrecision (const Win::Font::OutPrecis precision) 
					{
						_logFont.lfOutPrecision = precision ;
					}

					//-------------------------------------------------------------------
					// Changes the clip precision of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE precision -> The new clip precision.
					//-------------------------------------------------------------------

					void SetClipPrecision (const Win::Font::ClipPrecis precision) 
					{
						_logFont.lfClipPrecision = precision ;
					}

					//-------------------------------------------------------------------
					// Changes the quality of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE quality -> The new quality.
					//-------------------------------------------------------------------

					void SetQuality (const Win::Font::Quality quality) 
					{
						_logFont.lfQuality = quality ;
					}

					//-------------------------------------------------------------------
					// Changes the pitch of the font that will be created.
					// 
					// Parameters:
					//
					// const Win::Font::Pitch pitch -> The new pitch.
					//-------------------------------------------------------------------

					void SetPitch (const Win::Font::Pitch pitch) 
					{
						_logFont.lfPitchAndFamily &= 0xFC ;
						_logFont.lfPitchAndFamily |= pitch ;
					}

					//-------------------------------------------------------------------
					// Changes the family of the font that will be created.
					// 
					// Parameters:
					//
					// const Win::Font::Pitch pitch -> The new family.
					//-------------------------------------------------------------------

					void SetFamily (const Win::Font::Family family) 
					{
						_logFont.lfPitchAndFamily &= 0x02 ;
						_logFont.lfPitchAndFamily |= family ;
					}

					//-------------------------------------------------------------------
					// Changes the face name of the font that will be created.
					// 
					// Parameters:
					//
					// const std::tstring faceName -> The new face name.
					//-------------------------------------------------------------------

					void SetFaceName (const std::tstring faceName) 
					{
						::_tcscpy (_logFont.lfFaceName, faceName.c_str ()) ;
					}

					void SetAllData (const std::tstring face, const Win::Font::CharSet charSet, const int height, const int width, const int escapement, const int orientation, 
						     const Win::Font::Weight weight, const bool italic, const bool underline, const bool strikeOut, 
						     const Win::Font::OutPrecis outputPrescision, const Win::Font::ClipPrecis clipPrescision, const Win::Font::Quality quality, 
						     const Win::Font::Pitch pitch, const Win::Font::Family family) ;


					Win::Font::StrongHandle Create () ;
				/*	static Win::Font::StrongHandle Create (const std::tstring face, const Win::Font::CharSet charSet, const int height, const int width, const int escapement, const int orientation, 
						     const Win::Font::Weight weight, const bool italic, const bool underline, const bool strikeOut, 
						     const Win::Font::OutPrecis outputPrescision, const Win::Font::ClipPrecis clipPrescision, const Win::Font::Quality quality, 
						     const Win::Font::Pitch pitch, const Win::Font::Family family) ;*/

				private:

					LOGFONT _logFont ;
				} ;
		}

		//------------------------------------------------------------------
		// Win::Region::RectangleCreator allow to create and use a rectangle region.
		//------------------------------------------------------------------

		namespace Region
		{
			typedef Sys::Handle <HRGN> Handle ;
			typedef Sys::StrongHandle<Win::Region::Handle, Win::GDI::Disposal<HRGN> > StrongHandle ; // Strong handle owning the region

			enum CombineFlag {And = RGN_AND, Copy = RGN_COPY, Or = RGN_OR, Diff = RGN_DIFF, Xor = RGN_XOR} ;

			class RectangleCreator
			{ 
			public:

				//--------------------------------------------------------------------
				// Constructor
				//--------------------------------------------------------------------

				RectangleCreator ()
					: _rect ()
				{}


				//--------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// parameter:
				//
				// const int xLeft         -> X coordinate of the top left corner.
				// const int yTop          -> Y coordinate of the top left corner.
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				//--------------------------------------------------------------------

				RectangleCreator (const int xLeft, const int yTop, const int xRight, const int yBottom)
					: _rect (xLeft, xRight, yTop, yBottom)
				{}

				//--------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// parameter:
				//
				// const Win::Rect & rect -> The parameters used to create the region.				//--------------------------------------------------------------------
				//--------------------------------------------------------------------

				RectangleCreator (const Win::Rect & rect)
					: _rect (rect) 
				{}

				//--------------------------------------------------------------------
				// Changes the top left corner of the created region.
				// 
				// parameter:
				//
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				//--------------------------------------------------------------------

				void SetTopLeftCorner (const int x, const int y)
				{
					_rect.SetLeft (x) ;
					_rect.SetTop  (y) ;
				}

				//--------------------------------------------------------------------
				// Changes the bottom right corner of the created region.
				// 
				// parameter:
				//
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner..
				//--------------------------------------------------------------------

				void SetBottomRightCorner (const int x, const int y)
				{
					_rect.SetRight  (x) ;
					_rect.SetBottom (y) ;
				}

				//--------------------------------------------------------------------
				// Changes all the data of the created region
				// 
				// parameter:
				//
				// const int xLeft         -> X coordinate of the top left corner.
				// const int yTop          -> Y coordinate of the top left corner.
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				//--------------------------------------------------------------------

				void SetAllData (const int xLeft, const int yTop, const int xRight, const int yBottom)
				{
					_rect.SetLeft  (xLeft) ;
					_rect.SetTop    (yTop) ;
					_rect.SetRight  (xRight) ;
					_rect.SetBottom (yBottom) ;					
				}

				//--------------------------------------------------------------------
				// Changes all the data of the created region
				// 
				// parameter:
				//
				// const int xLeft         -> X coordinate of the top left corner.
				// const int yTop          -> Y coordinate of the top left corner.
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				//--------------------------------------------------------------------

				void SetAllData (const Win::Rect & rect)
				{
					_rect = rect ;
				}

				Win::Region::StrongHandle Create () ;
				static Win::Region::StrongHandle Create (const int xLeft, const int yTop, const int xRight, const int yBottom) ;


			protected:

				Win::Rect _rect ;
			} ;

			//------------------------------------------------------------------
			// Win::Region::EllipseCreator allow to create and use an elliptic region.
			//------------------------------------------------------------------

			class EllipseCreator : public RectangleCreator
			{
			public:

				//--------------------------------------------------------------------
				// Constructor
				//--------------------------------------------------------------------

				EllipseCreator ()
					: RectangleCreator ()
				{}


				//--------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// parameter:
				//
				// const int xLeft         -> X coordinate of the top left corner.
				// const int yTop          -> Y coordinate of the top left corner.
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				//--------------------------------------------------------------------

				EllipseCreator (const int xLeft, const int yTop, const int xRight, const int yBottom)
					: RectangleCreator (xLeft, yTop, xRight, yBottom)
				{}

				//--------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// parameter:
				//
				// const Win::Rect & rect -> The parameters used to create the region.				//--------------------------------------------------------------------
				//--------------------------------------------------------------------

				EllipseCreator (const Win::Rect & rect)
					: RectangleCreator (rect) 
				{}

				Win::Region::StrongHandle Create () ;
				static Win::Region::StrongHandle Create (const int xLeft, const int yTop, const int xRight, const int yBottom) ;

			} ;

		//------------------------------------------------------------------
		// Win::Region::RoundRectangleCreator allow to create and use a round rectangle region.
		//------------------------------------------------------------------

			class RoundRectangleCreator
			{
				public:

				//--------------------------------------------------------------------
				// Constructor
				//--------------------------------------------------------------------

				RoundRectangleCreator ()
					: _rect ()
				{}


				//--------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// parameter:
				//
				// const int xLeft         -> X coordinate of the top left corner.
				// const int yTop          -> Y coordinate of the top left corner.
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				// const int widthEllipse  -> Width of the ellipse used to create
				//						   	  a round corner.
				// const int heightEllipse -> Height of the ellipse used to create
				//						   	  a round corner.
				//--------------------------------------------------------------------

				RoundRectangleCreator (const int xLeft, const int yTop, const int xRight, const int yBottom, const int ellipseWidth, const int ellipseHeight)
					: _rect    (xLeft, xRight, yTop, yBottom),
					  _eWidth  (ellipseWidth),
					  _eHeight (ellipseHeight)
				{}

				//--------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// parameter:
				//
				// const Win::Rect & rect -> The parameters used to create the region.
				// const int widthEllipse  -> Width of the ellipse used to create
				//						   	  a round corner.
				// const int heightEllipse -> Height of the ellipse used to create
				//						   	  a round corner.
				//--------------------------------------------------------------------

				RoundRectangleCreator (const Win::Rect & rect,  const int ellipseWidth, const int ellipseHeight)
					: _rect    (rect),
					  _eWidth  (ellipseWidth),
					  _eHeight (ellipseWidth)
				{}

				//--------------------------------------------------------------------
				// Changes the top left corner of the created region.
				// 
				// parameter:
				//
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				//--------------------------------------------------------------------


				void SetTopLeftCorner (const int x, const int y)
				{
					_rect.SetLeft (x) ;
					_rect.SetTop  (y) ;
				}

				//--------------------------------------------------------------------
				// Changes the bottom right corner of the created region.
				// 
				// parameter:
				//
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner..
				//--------------------------------------------------------------------

				void SetBottomRightCorner (const int x, const int y)
				{
					_rect.SetRight  (x) ;
					_rect.SetBottom (y) ;
				}

				//--------------------------------------------------------------------
				// Changes the width and height of the ellipse used to make the
				// corners round.
				//
				// parameters 
				//
				// const int widthEllipse  -> Width of the ellipse used to create
				//						   	  a round corner.
				// const int heightEllipse -> Height of the ellipse used to create
				//						   	  a round corner.
				//--------------------------------------------------------------------

				void SetEllipseDimension (const int ellipseWidth, const int ellipseHeight)
				{
					_eWidth =  ellipseWidth ;
					_eHeight = ellipseHeight ;
				}

				//--------------------------------------------------------------------
				// Changes all the data of the created region
				// 
				// parameter:
				//
				// const int xLeft         -> X coordinate of the top left corner.
				// const int yTop          -> Y coordinate of the top left corner.
				// const int xRight        -> X coordinate of the bottom right corner.
				// const int bottom        -> Y coordinate of the bottom right corner.
				// const int widthEllipse  -> Width of the ellipse used to create
				//						   	  a round corner.
				// const int heightEllipse -> Height of the ellipse used to create
				//						   	  a round corner.
				//--------------------------------------------------------------------

				void SetAllData (const int xLeft, const int yTop, const int xRight, const int yBottom, const int ellipseWidth, const int ellipseHeight)
				{
					_rect.SetLeft   (xLeft) ;
					_rect.SetTop    (yTop) ;
					_rect.SetRight  (xRight) ;
					_rect.SetBottom (yBottom) ;	
					_eWidth  = ellipseWidth ;
					_eHeight = ellipseHeight ;
				}

				//--------------------------------------------------------------------
				// Changes all the data of the created region
				// 
				// parameter:
				//
				// const Win::Rect & rect  -> Data about the position of the corners
				// const int widthEllipse  -> Width of the ellipse used to create
				//						   	  a round corner.
				// const int heightEllipse -> Height of the ellipse used to create
				//						   	  a round corner.
				//--------------------------------------------------------------------

				void SetAllData (const Win::Rect & rect, const int ellipseWidth, const int ellipseHeight)
				{
					_rect = rect ;
					_eWidth  = ellipseWidth ;
					_eHeight = ellipseHeight ;
				}

				Win::Region::StrongHandle Create () ;
				static Win::Region::StrongHandle Create (const int xLeft, const int yTop, const int xRight, const int yBottom, const int ellipseWidth, const int ellipseHeight) ;


			private:

				Win::Rect    _rect ;
				unsigned int _eWidth ;
				unsigned int _eHeight ;
			} ;

		//------------------------------------------------------------------
		// Win::Region::PolygonCreator allow to create and use a polygon region.
		//------------------------------------------------------------------

			class PolygonCreator
			{
			public:
				
				//--------------------------------------------------------------------
				// Constructor
				//--------------------------------------------------------------------

				PolygonCreator ()
					: _p   (NULL),
					  _nb   (0),
					  _mode (Win::Polygon::Alternate)
				{}

				//------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region
				// 
				// Parameters:
				//
				// const Win::Point * p	-> Array of point forming the polygon.
				// const int nb         -> Number of points
				// const int fillMode   -> Filling mode of the polygonal region.
				//------------------------------------------------------------------

				PolygonCreator (Win::Point * p, const int nb, const Win::Polygon::FillMode mode)
					: _p   (p),
					  _nb   (nb),
					  _mode (mode)
				{}

				//------------------------------------------------------------------
				// Changes the points of the polygon used to create the region
				// 
				// Parameters:
				//
				// const Win::Point * p	-> Array of point forming the polygon.
				// const int nb         -> Number of points
				//------------------------------------------------------------------

				void SetPoints (Win::Point * p, const int nb)
				{
					_p  = p ;
					_nb = nb ;
				}

				//------------------------------------------------------------------
				// Changes the polygon filling mode to create the region
				// 
				// Parameters:
				// const int fillMode   -> Filling mode of the polygonal region.
				//------------------------------------------------------------------

				void SetFillMode (Win::Polygon::FillMode mode)
				{
					_mode = mode ;
				}

				//------------------------------------------------------------------
				// Changes all the data used to create the region.
				// 
				// Parameters:
				//
				// const Win::Point * p	-> Array of point forming the polygon.
				// const int nb         -> Number of points
				// const int fillMode   -> Filling mode of the polygonal region.
				//------------------------------------------------------------------

				void SetAllData (Win::Point * p, const int nb, const Win::Polygon::FillMode mode)
				{
					_p  = p ;
					_nb = nb ;
					_mode = mode ;
				}

				Win::Region::StrongHandle Create () ;
				static Win::Region::StrongHandle Create (Win::Point * p, const int nb, const Win::Polygon::FillMode mode) ;

			private:

				Win::Point *			_p ;
				int					 _nb ;
				Win::Polygon::FillMode _mode ;
			} ;

			class PolyPolygonCreator
			{
			public:
				
				//--------------------------------------------------------------------
				// Constructor
				//--------------------------------------------------------------------

				PolyPolygonCreator ()
					: _p      (NULL),
					  _nb     (0),
					  _nbPoly (0),
					  _mode    (Win::Polygon::Alternate)
				{}

				//------------------------------------------------------------------
				// Constructor.  Sets the parameters used to create the region.
				// 
				// Parameters:
				//
				// const Win::Point * p	 -> Array of point forming the polygons.
				// const int *  nb       -> Array telling the nomber of point for
				//							each Polygon.
				// const int nbPoly      -> Number of polygons
				// const int fillMode    -> Filling mode of the polygonal region.
				//------------------------------------------------------------------

				PolyPolygonCreator (Win::Point * p, int * nb, const int nbPoly, const Win::Polygon::FillMode mode)
					: _p      (p),
					  _nb     (nb),
					  _nbPoly (nbPoly),
					  _mode   (mode)
				{}

				//------------------------------------------------------------------
				// Changes the points of the polygon used to create the region
				//
				// Parameters:
				//
				// const Win::Point * p	 -> Array of point forming the polygons.
				// const int *  nb       -> Array telling the nomber of point for
				//							each Polygon.
				// const int nbPoly      -> Number of polygons
				//------------------------------------------------------------------

				void SetPoints (Win::Point * p, int * nb, const int nbPoly)
				{
					_p      = p ;
					_nb     = nb ;
					_nbPoly = nbPoly ;
				}

				//------------------------------------------------------------------
				// Changes the polygon filling mode to create the region
				// 
				// Parameters:
				// const int fillMode   -> Filling mode of the polygonal region.
				//------------------------------------------------------------------

				void SetFillMode (Win::Polygon::FillMode mode)
				{
					_mode = mode ;
				}

				//------------------------------------------------------------------
				// Changes all the data used to create the region.
				// 
				// Parameters:
				//
				//
				// const Win::Point * p	 -> Array of point forming the polygons.
				// const int *  nb       -> Array telling the nomber of point for
				//							each Polygon.
				// const int nbPoly      -> Number of polygons
				// const int fillMode    -> Filling mode of the polygonal region.
				//------------------------------------------------------------------
				//------------------------------------------------------------------

				void SetAllData (Win::Point * p, int * nb,const int nbPoly, const Win::Polygon::FillMode mode)
				{
					_p      = p ;
					_nb     = nb ;
					_nbPoly = nbPoly ;
					_mode   = mode ;
				}

				Win::Region::StrongHandle Create () ;

				static Win::Region::StrongHandle Create (Win::Point * p, int * nb,const int nbPoly, const Win::Polygon::FillMode mode) ;


			private:

				Win::Point *		  	 _p ;
				int *                   _nb ;
				int				   	    _nbPoly ;
				Win::Polygon::FillMode  _mode ;
			} ;

		//------------------------------------------------------------------
		// Win::Region::PathCreator allow to create and use a region from a path
		//------------------------------------------------------------------

			class PathCreator
			{
			public:

				static Win::Region::StrongHandle Create (Win::Canvas & canvas) ;
			} ;

		//------------------------------------------------------------------
		// Win::Region::Combinator creates a region by combining 2 others region.
		//------------------------------------------------------------------

			class Combinator
			{
			public:

				static Win::Region::StrongHandle Combine (Win::Region::Handle rgn1, Win::Region::Handle rgn2 = NULL, const Win::Region::CombineFlag flag = And) ;
			} ;
		} ;

		namespace Palette
		{
			enum Flag {NoFlag = 0, Explicit = PC_EXPLICIT, NoCollapse = PC_NOCOLLAPSE, Reserved = PC_RESERVED} ;

			//---------------------------------------------------------------------------
			// Win::Palette::Data encapsulates a LOGPALETTE structure through pointer data.
			// member.  A Win::Palette::Data object contains various  data that can be 
			// used to create a "real" palette..
			//
			// Data members of LOGPALETTE:
			//
			// palNumEntries -> The number of palette color entries.
			// palVersion    -> Must be 0x0300.
			// peRed         -> Red value of the palette entry.
			// peGreen       -> Green value of the palette entry.
			// peBlue        -> Blue value of the entry
			// peFlags       -> A special attribute of the entry.
			//---------------------------------------------------------------------------

			class Data
			{
			public:

				//---------------------------------------------------------------------
				// Constructor. Data members are initialized to 0.
				//---------------------------------------------------------------------

				Data ()
					: _pal (NULL)
				{
					_pal->palVersion    = 0x0300 ;
				}
				
				//---------------------------------------------------------------------
				// Constructor. Create a Win::Palette::Data object that can hold
				// a certain number of color entry.
				// 
				// Parameters:
				// 
				// const unsigned short size -> Number of entry the object can hold.
				//---------------------------------------------------------------------

				Data (const unsigned short size)
					: _pal (NULL)
				{
					Resize (size) ;
				}

				//---------------------------------------------------------------------
				// Copy constructor.
				//---------------------------------------------------------------------

				Data (Win::Palette::Data & data)
					: _pal (NULL)
				{
					::CopyMemory (_pal, data._pal, sizeof (LOGPALETTE) + (data.GetSize () - 1) * sizeof (PALETTEENTRY)) ;
				}

				//---------------------------------------------------------------------
				// Destructor.  Free the memory used by the Win::Palette::Data object.
				//---------------------------------------------------------------------

				~Data ()
				{
					Free () ;

				}

				void Resize (const unsigned short size) ;

				//---------------------------------------------------------------------
				// Obtains the size of the Win::Palette::Data object.
				// 
				// Return value:  The size of the object.
				//---------------------------------------------------------------------	

				unsigned short GetSize () const
				{
					return _pal->palNumEntries ;
				}

				Win::Color GetEntry (const int pos) const ;

				void SetEntry (const int pos, const BYTE red, const BYTE green, const BYTE blue, const Win::Palette::Flag flag = NoFlag) ;
				void SetEntry (const int pos, Win::RGBColor & color, const Win::Palette::Flag flag = NoFlag) ;
				void CreateFromSystemPalette () ;

				//---------------------------------------------------------------------
				// Gives direct access to the LOGPALETTE pointer.  Useful for 
				// compability with the WinAPI.
				// 
				// Return value:  A constant pointer on the LOGPALETTE.
				//---------------------------------------------------------------------

				const LOGPALETTE * GetPointer () const 
				{
					return _pal ;
				}

				//------------------------------------------------------------------
				// Makes Win::Palette::Data compatible with the windows API.
				//------------------------------------------------------------------

				operator const LOGPALETTE * () const
				{
					return _pal ;
				}

				void operator = (Win::Palette::Data & data)
				{
					if (_pal != data._pal)
					{
						Free () ;
						::CopyMemory (_pal, data._pal, sizeof (LOGPALETTE) + (data.GetSize () - 1) * sizeof (PALETTEENTRY)) ;
					}
					
				}

			private:

				//---------------------------------------------------------------------
				// Frees the memory used by the Win::Palette::Data object.
				//---------------------------------------------------------------------

				void Free ()
				{
					if (_pal != NULL)  // Must point on a LOGPALETTE.
					{
						free (_pal) ;
						_pal = NULL;
					}

					
				}

			private:

				LOGPALETTE * _pal ; // Will point on a LOGPALETTE.
			} ;

			typedef Sys::Handle <HPALETTE> Handle ;
			typedef Sys::StrongHandle <Win::Palette::Handle, Win::GDI::Disposal<HPALETTE> > StrongHandle ; // Strong handle owning the palette

			//------------------------------------------------------------------
			// Win::Palette::HalftoneCreator is use to create a halftone palette
			//------------------------------------------------------------------
			class HalftoneCreator
			{

				static Win::Palette::StrongHandle Create (const Win::Canvas & canvas) ;
			} ;

			//------------------------------------------------------------------
			// Win::Palette::Creator is use to create a palette
			//------------------------------------------------------------------

			class Creator
			{
				static Win::Palette::StrongHandle Create (const Win::Palette::Data & data) ;
			} ;



		}
	}
	
#endif