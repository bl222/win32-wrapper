//----------------------------------------------------------------
// This file contains only one class: Win::Color.
//----------------------------------------------------------------

#if !defined (WINCOLOR_H)

	#define WINCOLOR_H
	#include "useunicode.h"
	#include <windows.h>

	namespace Win
	{
		//----------------------------------------------------------------
		// Win::Color encapsulates a COLORREF value.  This makes working 
		// with colors easier.Win::Color is a base class used to create
		// the class representing the 3 types of colors in Windows:
		// RGB, palette RGB and palette index.  Win::Color should not
		// be used directly by users.
		//----------------------------------------------------------------

		class Color
		{
		public:

			//------------------------------------------------------------------
			// Constructor.  Create a black color.
			//------------------------------------------------------------------

			Color ()
				: _color (0)
			{}

			//------------------------------------------------------------------
			// Constructor.  Create a Win::Color object from a COLORREF.
			//
			// Parameters:
			//
			// const COLORREF color -> COLORREF from witch the object is created.
			//------------------------------------------------------------------

			Color (const COLORREF color)
				: _color (color)	  
			{}

		
			//--------------------------------------------------------------------
			// Obtains the value of the COLORREF encapsulated in the Win::Color
			// object.
			//
			// Return value:  The red value.
			//--------------------------------------------------------------------

			COLORREF GetColorRef () const 
			{
				return _color ;
			}

			//----------------------------------------------------------------
			// Set the color of the Win::Color object with a COLORREF
			//
			// Parameters:
			//
			// const COLORREF color -> Red value between 0 and 255
			//----------------------------------------------------------------

			void SetColorRef (const COLORREF color)    
			{
				_color = color ;
			}

			//--------------------------------------------------------------------
			// Determines if the color is valid.
			//
			// Return value:  If color is valid return true, else false.
			//--------------------------------------------------------------------

			bool IsValidColor () 
			{
				return _color >= 0 && _color != CLR_INVALID ;
			}

			//--------------------------------------------------------------------
			// Converts the ¸Win::Color object into a COLORREF value.
			// Used for compatibility with the WinAPI.
			//--------------------------------------------------------------------

			operator COLORREF () const
			{
				return _color ;
			}

		protected: 
			COLORREF _color ;
		} ; 

		//----------------------------------------------------------------
		// Win::RGBColor is a class representing standard RGB colors in
		// Windows.
		//----------------------------------------------------------------

		class RGBColor : public Win::Color
		{
		public:

			//------------------------------------------------------------------
			// Constructor.  Create a black color.
			//------------------------------------------------------------------

			RGBColor ()
				: Color ()
			{
				MakeRGB () ;
			}

			//----------------------------------------------------------------
			// Constructor.  Create a Win::RGBColor object from red, green and
			// blue value.
			//
			// Parameters:
			//
			// const unsigned short red   -> Red value between 0 and 255
			// const unsigned short green -> Green value between 0 and 255
			// const unsigned short blue  -> Blue value between 0 and 255
			//----------------------------------------------------------------

			RGBColor (const unsigned short red, const unsigned short green, const unsigned short blue)
				: Color ()
				 
			{
				_color = RGB (red, green, blue) ;
				MakeRGB () ;
			}
			
			//------------------------------------------------------------------
			// Constructor.  Create a Win::RGBColor object from a COLORREF.
			//
			// Parameters:
			//
			// const COLORREF color -> COLORREF from witch the object is created.
			//------------------------------------------------------------------

			RGBColor (const COLORREF color)
				: Color ()
				  
			{
				_color  = color ;
				MakeRGB () ;
			}

			//------------------------------------------------------------------
			// Constructor.  Create a Win::RGBColor object from a Win::Color.
			//
			// Parameters:
			//
			// const RGBCOLOR color -> Win::RGBColor from witch the object is created.
			//------------------------------------------------------------------

			RGBColor (const Win::RGBColor & color) 
				: Color ()
			{
				_color = color ;
				MakeRGB () ;
			}

			virtual ~RGBColor ()
			{}

			void GetRGB (unsigned short & red, unsigned short & green, unsigned short & blue) const ;

			//--------------------------------------------------------------------
			// Obtains the red value.
			//
			// Return value:  The red value.
			//--------------------------------------------------------------------

			BYTE GetRed () const 
			{
				return static_cast <BYTE> (_color & 0x000000FF) ;
			}

			//--------------------------------------------------------------------
			// Obtains the green value.
			//
			// Return value:  The green value.
			//--------------------------------------------------------------------

			BYTE GetGreen () const 
			{
				return static_cast <BYTE> ((_color & 0x0000FF00) >> 8) ;
			}
			
			//--------------------------------------------------------------------
			// Obtains the blue value.
			//
			// Return value:  The blue value.
			//--------------------------------------------------------------------

			BYTE GetBlue () const 
			{
				return static_cast <BYTE> ((_color & 0x00FF0000) >> 16) ;
			}

			//----------------------------------------------------------------
			// Set the red, green and blue values of the Win::Color object.
			//
			// Parameters:
			//
			// const unsigned short red   -> Red value between 0 and 255.
			// const unsigned short green -> Green value between 0 and 255.
			// const unsigned short blue  -> Blue value between 0 and 255.
			//----------------------------------------------------------------

			void SetRGB (const unsigned short red, const unsigned short green, const unsigned short blue) 
			{
				_color = RGB (red, green, blue) ;
			}

			//----------------------------------------------------------------
			// Set the red value of the Win::Color object.
			//
			// Parameters:
			//
			// const unsigned short red -> Red value between 0 and 255.
			//----------------------------------------------------------------

			void SetRed (const unsigned short red)   
			{ 
				_color = (_color & 0xFFFFFF00) | static_cast <DWORD> (red) ;
			}

			//----------------------------------------------------------------
			// Set the green value of the Win::Color object.
			//
			// Parameters:
			//
			// const unsigned short green -> Green value between 0 and 255.
			//----------------------------------------------------------------

			void SetGreen (const unsigned short green) 
			{ 
				_color = (_color & 0xFFFF00FF) | static_cast <DWORD> (green << 8) ; 
			}

			//----------------------------------------------------------------
			// Set the blue value of the Win::Color object.
			//
			// Parameters:
			//
			// const unsigned short blue -> Blue value between 0 and 255.
			//----------------------------------------------------------------

			void SetBlue (const unsigned short blue)  
			{ 
				_color = (_color & 0xFF00FFFF) | static_cast <DWORD> (blue << 16) ; 
			}

			//----------------------------------------------------------------
			// Convert a Win::Color object into a RGBColor
			//----------------------------------------------------------------

			virtual void operator = (Win::Color & color)
			{
				_color = color.GetColorRef () ;
				MakeRGB () ;
			}

		private:

			//----------------------------------------------------------------
			// Makes sure the encapsulated COLORREF value represents a 
			// RGB color.
			//----------------------------------------------------------------
			
			void MakeRGB ()
			{
				_color = _color | 0x02000000 ;
			}

		} ;

		//----------------------------------------------------------------
		// Win::PaletteRGBColor is a class representing palette RGB colors in
		// Windows.
		//----------------------------------------------------------------

		class PaletteRGBColor : public Win::RGBColor
		{
		public:

			//------------------------------------------------------------------
			// Constructor.  Create a black color.
			//------------------------------------------------------------------

			PaletteRGBColor ()
				: RGBColor ()
			{
				MakePaletteRGB () ;
			}

			//----------------------------------------------------------------
			// Constructor.  Create a Win::PaletteRGBColor object from red, green and
			// blue value.
			//
			// Parameters:
			//
			// const unsigned short red   -> Red value between 0 and 255
			// const unsigned short green -> Green value between 0 and 255
			// const unsigned short blue  -> Blue value between 0 and 255
			//----------------------------------------------------------------

			PaletteRGBColor (const unsigned short red, const unsigned short green, const unsigned short blue)
				: RGBColor ()
				  
			{
				_color = PALETTERGB ( red, green, blue) ;
				MakePaletteRGB () ;
			}
			

			//------------------------------------------------------------------
			// Constructor.  Create a Win::PaletteRGBColor object from a COLORREF.
			//
			// Parameters:
			//
			// const COLORREF color -> COLORREF from witch the object is created.
			//------------------------------------------------------------------

			PaletteRGBColor (const COLORREF color)
				: RGBColor ()
			{
				_color = color ;
				MakePaletteRGB () ;
			}

			//------------------------------------------------------------------
			// Constructor.  Create a Win::PaletteRGBColor object from a Win::Color.
			//
			// Parameters:
			//
			// const PaletteRGBCOLOR color -> Win::RGBColor from witch the object is created.
			//------------------------------------------------------------------

			PaletteRGBColor (const Win::PaletteRGBColor & color) 
				: RGBColor ()
			{
				_color = color ;
				MakePaletteRGB () ;
			}

			//----------------------------------------------------------------
			// Convert a Win::Color object into a PaletteRGBColor
			//----------------------------------------------------------------

			void operator = (Win::Color & color)
			{
				_color = color.GetColorRef ();
				MakePaletteRGB () ;
			}

		private:

			//----------------------------------------------------------------
			// Makes sure the encapsulated COLORREF value represents a 
			// palette RGB color.
			//----------------------------------------------------------------

			void MakePaletteRGB ()
			{
				_color = _color | 0x02000000 ;
			}

		} ;

		//----------------------------------------------------------------
		// Win::RGBColor is a class representing palette index colors in
		// Windows.
		//----------------------------------------------------------------

		class PaletteIndexColor : public Win::Color
		{
		public:

			//------------------------------------------------------------------
			// Constructor.  Create a black color.
			//------------------------------------------------------------------

			PaletteIndexColor ()
				: Color ()
			{
				MakePaletteIndex () ;
			}

			//------------------------------------------------------------------
			// Constructor.  Create a color from a palette index.
			//
			//	unsigned int index -> The palette index.
			//------------------------------------------------------------------

		/*	PaletteIndexColor (unsigned int index)
				: Color ()
			{
				_color = PALETTEINDEX (index) ;
			}*/

			//------------------------------------------------------------------
			// Constructor.  Create a Win::PaletteRGBColor object from a COLORREF.
			//
			// Parameters:
			//
			// const COLORREF color -> COLORREF from witch the object is created.
			//------------------------------------------------------------------

			PaletteIndexColor (const COLORREF color)
				: Color ()
				 
			{
				_color = color ;
				MakePaletteIndex () ;
			}

			//------------------------------------------------------------------
			// Constructor.  Create a Win::PaletteRGBColor object from a Win::Color.
			//
			// Parameters:
			//
			// const PaletteRGBCOLOR color -> Win::RGBColor from witch the object is created.
			//------------------------------------------------------------------

			PaletteIndexColor (const Win::PaletteRGBColor & color) 
				: Color ()
			{
				_color = color ;
				MakePaletteIndex () ;
			}

			//----------------------------------------------------------------
			// Obtains the palette index contained into the object
			//----------------------------------------------------------------

			unsigned int GetIndex () const
			{
				return _color ;
			}

			//----------------------------------------------------------------
			// Sets the palette index contained into the object.
			//----------------------------------------------------------------

			void SetIndex (const COLORREF index)
			{
				_color = PALETTEINDEX (index) ;
			}

			//----------------------------------------------------------------
			// Convert a Win::Color object into a PaletteIndexColor
			//----------------------------------------------------------------

			void operator = (Win::Color & color)
			{
				_color = color.GetColorRef () ;
				MakePaletteIndex () ;
			}

		private:

			//----------------------------------------------------------------
			// Makes sure the encapsulated COLORREF value represents a 
			// palette index color.
			//----------------------------------------------------------------

			void MakePaletteIndex ()
			{
				_color = _color | 0x01000000 ;
			}
		} ;

	}




#endif