//------------------------------------------------------
// This file contains classes dealing with the canvas.
//-----------------------------------------------------

#if !defined (WINCANVAS_H)

	#define WINCANVAS_H
	#include "useunicode.h"
	#include "winencapsulation.h"
	#include "winhandle.h"
	#include "windrawingtool.h"
	#include "win.h"
	#include "winunicodehelper.h"
//	#include "winimagelist.h"

	namespace Win
	{
		namespace Brush
		{
			namespace Solid
			{
				class Holder ;
			}

			namespace Hatch
			{
				class Holder ;
			}

			namespace Pattern
			{
				class Holder ;	
			}
		}

		namespace Pen
		{
				class Holder ;
		}

		namespace ExtendedPen
		{
			namespace Color
			{
				class Holder ;
			}
		}

		namespace Background
		{
			enum Mode {Opaque = OPAQUE, Transparent = TRANSPARENT} ;
		}

		namespace Drawing
		{
			enum Mode {Black = R2_BLACK, CopyPen = R2_COPYPEN, MaskNotPen = R2_MASKNOTPEN, MaskPen = R2_MASKPEN,
					   MaskPenNot = R2_MASKPENNOT, MergeNotPen = R2_MERGENOTPEN, MergePen = R2_MERGEPEN,
					   MergePenNot = R2_MERGEPENNOT, NoP = R2_NOP, Not = R2_NOT, NotCopyPen = R2_NOTCOPYPEN,
					   NotMaskPen = R2_NOTMASKPEN, NotMergePen = R2_NOTMERGEPEN, NotXorPen = R2_NOTXORPEN,
					   White = R2_WHITE, XorPen = R2_XORPEN} ;
		}

		namespace Mapping
		{
			enum Mode {Anisotropic = MM_ANISOTROPIC, HiEnglish = MM_HIENGLISH, HiMetric = MM_HIMETRIC, 
				Isotropic = MM_ISOTROPIC, LowEnglish = MM_LOENGLISH, LowMetric = MM_LOMETRIC, 
				Text = MM_TEXT, Twips = MM_TWIPS} ;
		}

		//------------------------------------------------------
		// Base class for classes giving capabilities info about
		// a Canvas (device context) object.
		//------------------------------------------------------

		class Capabilities
		{
		public:

			//------------------------------------------------------
			// Obtains the int value representing the capability.
			//
			// return value:  The capability in integer form.
			//-------------------------------------------------------

			int GetCapabilities () const
			{
				return _caps ;
			}

		protected:

			//-------------------------------------------------------
			// Constructor.
			//-------------------------------------------------------

			Capabilities (const int caps)
				: _caps (caps)
			{}

			int _caps ;
		} ;

		//------------------------------------------------------
		// Contains information about the raster capabilities of
		// a Canvas (Device context).
		//------------------------------------------------------

		class RasterCapabilities : public Capabilities
		{
		public:

			//-------------------------------------------------------
			// Constructor.
			//-------------------------------------------------------

			RasterCapabilities (const int caps)
				: Capabilities (caps)
			{}

			//-------------------------------------------------------
			// Each of these method tells wether or not the Canvas
			// (Device Context) support a particular feature or not.
			//
			// Return value: True if the feature is supported, else
			//				 false.
			//-------------------------------------------------------

			bool RequireBanding       () const {return (_caps & RC_BANDING)      != 0 ;}
			bool CanBlit              () const {return (_caps & RC_BITBLT)       != 0 ;}
			bool CanUseBitmapBigger64 () const {return (_caps & RC_BITMAP64)     != 0 ;}
			bool CanUseDIB            () const {return (_caps & RC_DI_BITMAP)    != 0 ;}
			bool CanUseDIBToDev       () const {return (_caps & RC_DIBTODEV)     != 0 ;}
			bool CanFloodFill		  () const {return (_caps & RC_FLOODFILL)    != 0 ;}
			bool CanUseWindow20		  () const {return (_caps & RC_GDI20_OUTPUT) != 0 ;}
			bool IsPaletteBase		  () const {return (_caps & RC_PALETTE)      != 0 ;}
			bool CanScale			  () const {return (_caps & RC_SCALING)      != 0 ;}
			bool CanStretchBlit		  () const {return (_caps & RC_STRETCHBLT)   != 0 ;}
			bool CanStretchDIB		  () const {return (_caps & RC_STRETCHDIB)   != 0 ;}
		} ;

		//------------------------------------------------------
		// Contains information about the curve capabilities of
		// a Canvas (Device context).
		//------------------------------------------------------

		class CurveCapabilities : public Capabilities
		{
		public:

			//-------------------------------------------------------
			// Constructor.
			//-------------------------------------------------------

			CurveCapabilities (const int caps)
				: Capabilities (caps)
			{}

			//-------------------------------------------------------
			// Each of these method tells wether or not the Canvas
			// (Device Context) support a particular feature or not.
			//
			// Return value: True if the feature is supported, else
			//				 false.
			//-------------------------------------------------------

			bool NoCurveSupport          () const {return (_caps & CC_NONE)       != 0 ;}
			bool CanDrawChordArc         () const {return (_caps & CC_CHORD)      != 0 ;}
			bool CanDrawCircle           () const {return (_caps & CC_CIRCLES)    != 0 ;}
			bool CanDrawEllipse          () const {return (_caps & CC_ELLIPSES)   != 0 ;}
			bool CanDrawInterior         () const {return (_caps & CC_INTERIORS)  != 0 ;}
			bool CanDrawPie              () const {return (_caps & CC_PIE)        != 0 ;}
			bool CanDrawRoundRect        () const {return (_caps & CC_ROUNDRECT)  != 0 ;}
			bool CanDrawStyledBorder     () const {return (_caps & CC_STYLED)     != 0 ;}
			bool CanDrawWideBorder       () const {return (_caps & CC_WIDE)       != 0 ;}
			bool CanDrawWideStyledBorder () const {return (_caps & CC_WIDESTYLED) != 0 ;}
		} ;

		//------------------------------------------------------
		// Contains information about the line capabilities of
		// a Canvas (Device context).
		//------------------------------------------------------

		class LineCapabilities : public Capabilities
		{
		public:

			//-------------------------------------------------------
			// Constructor.
			//-------------------------------------------------------

			LineCapabilities (const int caps)
				: Capabilities (caps)
			{}

			//-------------------------------------------------------
			// Each of these method tells wether or not the Canvas
			// (Device Context) support a particular feature or not.
			//
			// Return value: True if the feature is supported, else
			//				 false.
			//-------------------------------------------------------

			bool NoLineSupport           () const {return (_caps & LC_NONE)       != 0 ;}
			bool CanDrawInterior         () const {return (_caps & LC_INTERIORS)  != 0 ;}
			bool CanDrawStyledLine       () const {return (_caps & LC_STYLED)     != 0 ;}
			bool CanDrawWideLine         () const {return (_caps & LC_WIDE)       != 0 ;}
			bool CanDrawWideStyledLine   () const {return (_caps & LC_WIDESTYLED) != 0 ;}
			bool CanDrawMarker           () const {return (_caps & LC_MARKER)     != 0 ;}
			bool CanDrawPolyline         () const {return (_caps & LC_POLYLINE)   != 0 ;}
			bool CanDrawPolymarker       () const {return (_caps & LC_POLYMARKER) != 0 ;}

		} ;

		//------------------------------------------------------
		// Contains information about the polygonal capabilities of
		// a Canvas (Device context).
		//------------------------------------------------------

		class PolygonalCapabilities : public Capabilities
		{
		public:

			//-------------------------------------------------------
			// Constructor.
			//-------------------------------------------------------

			PolygonalCapabilities (const int caps)
				: Capabilities (caps)
			{}

			//-------------------------------------------------------
			// Each of these method tells wether or not the Canvas
			// (Device Context) support a particular feature or not.
			//
			// Return value: True if the feature is supported, else
			//				 false.
			//-------------------------------------------------------

			bool NoPolySupport           () const {return (_caps & PC_NONE)        != 0 ;}
			bool CanDrawInterior         () const {return (_caps & PC_INTERIORS)   != 0 ;}
			bool CanDrawStyledBorder     () const {return (_caps & PC_STYLED)      != 0 ;}
			bool CanDrawWideBorder       () const {return (_caps & PC_WIDE)        != 0 ;}
			bool CanDrawWideStyledBorder () const {return (_caps & PC_WIDESTYLED)  != 0 ;}
			bool CanDrawAlternateFill    () const {return (_caps & PC_POLYGON)     != 0 ;}
			bool CanDrawRectangle        () const {return (_caps & PC_RECTANGLE)   != 0 ;}
			bool CanDrawScanline         () const {return (_caps & PC_SCANLINE)    != 0 ;}
			bool CanDrawWindingFill		 () const {return (_caps & PC_WINDPOLYGON) != 0 ;}
		} ;

		//------------------------------------------------------
		// Contains information about the textual capabilities of
		// a Canvas (Device context).
		//------------------------------------------------------

		class TextCapabilities : public Capabilities
		{
		public:

			//-------------------------------------------------------
			// Constructor.
			//-------------------------------------------------------

			TextCapabilities (const int caps)
				: Capabilities (caps)
			{}

			//-------------------------------------------------------
			// Each of these method tells wether or not the Canvas
			// (Device Context) support a particular feature or not.
			//
			// Return value: True if the feature is supported, else
			//				 false.
			//-------------------------------------------------------

			bool CanCharOutputPrecision    () const {return (_caps & TC_OP_CHARACTER) != 0 ;}
			bool CanStrokeOutputPrecision  () const {return (_caps & TC_OP_STROKE)    != 0 ;}
			bool CanStrokeClipPrecision    () const {return (_caps & TC_CP_STROKE)    != 0 ;}
			bool CanRotate90               () const {return (_caps & TC_CR_90)        != 0 ;}
			bool CanRotateAny	           () const {return (_caps & TC_CR_ANY)       != 0 ;}
			bool CanScaleBothXandY		   () const {return (_caps & TC_OP_STROKE)	  != 0 ;}
			bool CanDoubledCharScaling     () const {return (_caps & TC_SA_DOUBLE)    != 0 ;}
			bool UseIntegerMultipleScaling () const {return (_caps & TC_SA_INTEGER)   != 0 ;}
			bool UseAnyMultipleScaling     () const {return (_caps & TC_SA_CONTIN)    != 0 ;}
			bool CanDrawDoubleWeightChar   () const {return (_caps & TC_EA_DOUBLE)    != 0 ;}
			bool CanItalize                () const {return (_caps & TC_IA_ABLE)	  != 0 ;}
			bool CanUnderline              () const {return (_caps & TC_UA_ABLE)	  != 0 ;}
			bool CanStrikeout              () const {return (_caps & TC_SO_ABLE)	  != 0 ;}
			bool CanUseRasterFont          () const {return (_caps & TC_RA_ABLE)	  != 0 ;}
			bool CanUseVectorFont          () const {return (_caps & TC_VA_ABLE)	  != 0 ;}
			bool CanScrollBlit			   () const {return (_caps & TC_SCROLLBLT)	  == 0 ;}
		} ;

		//------------------------------------------------------
		// Win::ExtendedTextOutOptions is used to specify the 
		// options for the ExtendedTextOutOptions method of the
		// Win::Canvas class.
		//------------------------------------------------------

		class ExtendedTextOutOptions
		{
		friend class Canvas ;

		public:

			//------------------------------------------------------
			// Constructor.  Sets the options to 0.
			//------------------------------------------------------
			
			ExtendedTextOutOptions () 
				: _options (0) 
			{}

			//------------------------------------------------------
			// The following 3 methods are used to set the desired
			// options.
			//------------------------------------------------------

			void SetClipRectangle () {_options |= ETO_CLIPPED ;}
			void SetFillRectangle () {_options |= ETO_OPAQUE ;}
			void SetGlyphIndex    () {_options |= ETO_GLYPH_INDEX ;} 
			
			void Reset            () {_options = 0 ;} // Resets the options to 0.

		private:

			UINT _options ; // Contains the desired options.
		} ;

		//------------------------------------------------------
		// Win:DrawTextFormat is used to specify the format
		//	for the DrawText method of the Win::Canvas class.
		//------------------------------------------------------

		class DrawTextFormat
		{
		friend class Canvas ;

		public:

			//------------------------------------------------------
			// Constructor.  Sets the format to 0.
			//------------------------------------------------------

			DrawTextFormat ()
				: _format (0) 
			{}

			//------------------------------------------------------
			// The following 20 methods are used to set the desired
			// formats.
			//------------------------------------------------------

			void SetAlignLeft          () {_format |= DT_LEFT ;}
			void SetAlignRight         () {_format |= DT_RIGHT  ;}
			void SetAlignCenter        () {_format |= DT_CENTER ;}
			void SetAlignTop           () {_format |= DT_TOP ;}
			void SetAlignBottom        () {_format |= DT_BOTTOM ;}
			void SetAlignVCenter       () {_format |= DT_VCENTER ;}
			void SetCalcRect           () {_format |= DT_CALCRECT ;}
			void SetEditControl        () {_format |= DT_EDITCONTROL ;}
			void SetEndEllipsis        () {_format |= DT_END_ELLIPSIS ;}
			void SetPathEllipsis       () {_format |= DT_PATH_ELLIPSIS ;}
			void SetExpandTab          () {_format |= DT_EXPANDTABS ;}
			void SetExternalLeading    () {_format |= DT_EXTERNALLEADING ;}
			void SetInternal           () {_format |= DT_INTERNAL ;}
			void SetModifyString       () {_format |= DT_MODIFYSTRING ;}
			void SetNoClip             () {_format |= DT_NOCLIP ;}
			void SetNoPrefix           () {_format |= DT_NOPREFIX ;}
			void SetRightToLeftReading () {_format |= DT_RTLREADING ;}
			void SetSingleLine         () {_format |= DT_SINGLELINE ;}
			void SetWordBreak          () {_format |= DT_WORDBREAK ;}
			void SetWordEllipsis       () {_format |= DT_WORD_ELLIPSIS ;}

			void Reset                 () {_format = 0 ;} // Resets the options to 0.

			
			//------------------------------------------------------
			// Sets the desired tab stop.
			//
			// Parameters:
			//
			// BYTE tabstop -> The desired tabstop.
			//------------------------------------------------------

			void SetTabstop (BYTE tabstop)
			{
				_format &= 0xFFFF00FF ;
				_format |= (tabstop << 8) ;
				_format |= DT_TABSTOP ;
			}

		private:
			UINT _format ; // Contains the desired formats.
		} ;

		//---------------------------------------------------------------------------
		// Win::DrawTextParams encapsulates a DRAWTEXTPARAMS structure through 
		// private inheritance
		//
		// Dara members of DRAWTEXTPARAMS:
		//
		// cbSize        -> Size of DRAWTEXTPARAMS.
		// iTabLength    -> Size of each tab stop.
		// iLeftMargin   -> Left margin width.
		// iRightMargin  -> Right margin width.
		// uiLengthDrawn -> Number of characters drawn by the method.
		//---------------------------------------------------------------------------

		class DrawTextParams : public Sys::Struct <DRAWTEXTPARAMS>
		{
			//-----------------------------------------------------------------------
			// Constructor.  Initialize the data members of the DRAWTEXTPARAMS struct.
			//-----------------------------------------------------------------------

			DrawTextParams () 
				: Sys::Struct <DRAWTEXTPARAMS> ()
			{					
				
				_struct.cbSize = sizeof (DRAWTEXTPARAMS) ;
			}

			DrawTextParams (const DRAWTEXTPARAMS & params)
				: Sys::Struct <DRAWTEXTPARAMS> (params)
			{
				_struct.cbSize = sizeof (DRAWTEXTPARAMS) ;
			}

			DrawTextParams (const int tabLenght, const int leftMargin, const int rightMargin, const UINT lengthDrawn) ;

			//-----------------------------------------------------------------------
			// Obtains the lenght of a tabstop
			//
			// Return value:  The lenght of a tab stop.
			//-----------------------------------------------------------------------

			int  GetTabLength   () const  
			{
				return _struct.iTabLength ;
			}

			//-----------------------------------------------------------------------
			// Obtains the width of the left margin.
			//
			// Return value:  The width of the left margin.
			//-----------------------------------------------------------------------

			int  GetLeftMargin  () const 
			{
				return _struct.iLeftMargin ;
			}

			//-----------------------------------------------------------------------
			// Obtains the width of the right margin.
			//
			// Return value:  The width of the right margin.
			//-----------------------------------------------------------------------

			int  GetRightMargin () const 
			{
				return _struct.iRightMargin ;
			}

			//-----------------------------------------------------------------------
			// Obtains the number of character drawn by the method..
			//
			// Return value:  The number of character drawn.
			//-----------------------------------------------------------------------

			UINT GetLengthDrawn () const 
			{
				return _struct.uiLengthDrawn ;
			}

			//-----------------------------------------------------------------------
			// Sets the lenght of a tab stop.
			//
			// Parameters:
			//
			// const int tabLength -> The new lenght of a tab stop.
			//-----------------------------------------------------------------------

			void SetTabLength   (const int tabLength)    
			{
				_struct.iTabLength = tabLength ;
			}

			//-----------------------------------------------------------------------
			// Sets the width of the left margin.
			//
			// Parameters:
			//
			// const int leftMargin -> The new width of the left margin.
			//-----------------------------------------------------------------------

			void SetLeftMargin  (const int leftMargin)   
			{
				_struct.iLeftMargin = leftMargin ;
			}

			//-----------------------------------------------------------------------
			// Sets the width of the right margin.
			//
			// Parameters:
			//
			// const int rightMarginMargin -> The new width of the right margin.
			//-----------------------------------------------------------------------

			void SetRightMargin (const int rightMargin)  
			{
				_struct.iRightMargin = rightMargin ;
			}

			//-----------------------------------------------------------------------
			// Sets the number of character drawn by the method.
			//
			// Parameters:
			//
			// const UINT lengthDrawn -> Number of drawn character.
			//-----------------------------------------------------------------------

			void SetLenghtDrawn (const UINT lengthDrawn) 
			{
				_struct.uiLengthDrawn = lengthDrawn ;
			}
		} ;

		//-------------------------------------------------------------------
		// In order to draw on awindow and work with bitmap (and other things)
		// one must use device context.  Device context can be tricky 
		// because different device context are created and destroyed by 
		// differents WinAPI functions and yet they are all represented by 
		// the same handle:  HDC.  The following classes represent various
		// kind of device context.  Each kind of DC is automatically created 
		// and destroyed by the appropriate WinAPI function.
		//-------------------------------------------------------------------

		//-------------------------------------------------------------------
		// Win::Canvas is not used directly.  It is used to provide basic
		// functionality for others Canvas classes, each of which represents
		// a kind of device context.
		//-------------------------------------------------------------------

		class Canvas : public Sys::Handle <HDC>
		{
			friend class Win::Brush::Solid::Holder ;
			friend class Win::Brush::Hatch::Holder ;
			friend class Win::Brush::Pattern::Holder ;
			friend class Win::Pen::Holder ;
			friend class Win::ExtendedPen::Color::Holder ;

		public:

			enum Clipping {NullRegion = NULLREGION, SimpleRegion = SIMPLEREGION, ComplexRegion = COMPLEXREGION} ;

			enum Technologie {Plotter = DT_PLOTTER, RasterDisplay = DT_RASDISPLAY, RasterPrinter = DT_RASPRINTER, 
				RasterCamera = DT_RASCAMERA, CharaterStream = DT_CHARSTREAM, Metafile = DT_METAFILE, DisplayFile = DT_DISPFILE} ;

			//-----------------------------------------------------------------------
			// Constructor.  Creates a canvas object.
			//
			// const HDC hdc -> Handle of the object that will be represented by the
			//					object.
			//-----------------------------------------------------------------------

			Canvas (const HDC hdc = NULL) 
				: Sys::Handle <HDC> (hdc),
				  _brushType        (BS_SOLID),
				  _penType          (NormalPen)
			{}

			//Note: Certaine GetDeviceCaps sont pour les printer, les implémenter lorsque PrinterCanvas sera implémenter!

			//-------------------------------------------------------
			// Each of these method obtains information about a
			// specific aspect of a canvas (device context).
			//
			// Return value: An integer representing the desired
			//				 information.
			//-------------------------------------------------------

			int  GetDriverVersion					  () const {return ::GetDeviceCaps (_h, DRIVERVERSION) ;}
			int  GetWidthPhysicalScreenInMilli		  () const {return ::GetDeviceCaps (_h, HORZSIZE) ;}
			int  GetHeightPhysicalScreenInMilli		  () const {return ::GetDeviceCaps (_h, VERTSIZE) ;}
			int  GetWidthPhysicalScreenInPixel		  () const {return ::GetDeviceCaps (_h, HORZRES) ;}
			int  GetHeightPhysicalScreenInRasterLines () const {return ::GetDeviceCaps (_h, VERTRES) ;}
			int  GetNbPixelsPerLogicalInchForWidth    () const {return ::GetDeviceCaps (_h, LOGPIXELSX) ;}
			int  GetNbPixelsPerLogicalInchForHeight   () const {return ::GetDeviceCaps (_h, LOGPIXELSY) ;}
			int  GetBitsPerPixel					  () const {return ::GetDeviceCaps (_h, BITSPIXEL) ;}
			int  GetNbColorPlanes					  () const {return ::GetDeviceCaps (_h, PLANES) ;}
			int  GetNbBrushes                         () const {return ::GetDeviceCaps (_h, NUMBRUSHES) ;}
			int  GetNbPens                            () const {return ::GetDeviceCaps (_h, NUMPENS) ;}
			int  GetNbFonts                           () const {return ::GetDeviceCaps (_h, NUMFONTS) ;}
			int  GetNbEntriesColorTable               () const {return ::GetDeviceCaps (_h, NUMCOLORS) ;}
			int  GetWidthPixel						  () const {return ::GetDeviceCaps (_h, ASPECTX) ;}
			int  GetHeightPixel                       () const {return ::GetDeviceCaps (_h, ASPECTY) ;}
			int  GetDiagonalWidthPixel				  () const {return ::GetDeviceCaps (_h, ASPECTXY) ;}
			bool CanClipRectangle					  () const {return ::GetDeviceCaps (_h, CLIPCAPS) == 1 ;}
			int  GetSizeSystemPalete	 			  () const {return ::GetDeviceCaps (_h, SIZEPALETTE) ;}
			int  GetNbReserveEntrySystemPalete		  () const {return ::GetDeviceCaps (_h, NUMRESERVED) ;}
			int  GetColorResolution	 				  () const {return ::GetDeviceCaps (_h, COLORRES) ;}
			int  GetVerticalRefreshRate				  () const {return ::GetDeviceCaps (_h, VREFRESH) ;}

			//-------------------------------------------------------
			// Each of these method obtains the capabilities of
			// a canvas (device context) about a certain domain (line,
			// curve, ect).
			//
			// Return value: An object representing the desired capability.
			//-------------------------------------------------------

			Win::RasterCapabilities    GetRaterCapabilities     () const {return ::GetDeviceCaps (_h, RASTERCAPS) ;}
			Win::CurveCapabilities     GetCurveCapabilities     () const {return ::GetDeviceCaps (_h, CURVECAPS) ;}
			Win::LineCapabilities      GetLineCapabilities      () const {return ::GetDeviceCaps (_h, LINECAPS) ;}
			Win::PolygonalCapabilities GetPolygonalCapabilities () const {return ::GetDeviceCaps (_h, POLYGONALCAPS) ;}
			Win::TextCapabilities      GetTextCapabilities      () const {return ::GetDeviceCaps (_h, TEXTCAPS) ;}

			//-------------------------------------------------------
			// Obtains the technologie the Canvas object (device context)
			// represents.
			//
			// Return value:  The technologie of the Canvas object.
			//-------------------------------------------------------

			Win::Canvas::Technologie   GetTechnologie		    () const {return static_cast <Win::Canvas::Technologie> (::GetDeviceCaps (_h, TECHNOLOGY)) ;}

			//--------------------------------------------------------------------
			// Obtains info on the device represented by the device context.
			//
			// Return value:  The requested info.
			//
			// Parameters:
			//
			// const int index -> The desired info on the device.
			//--------------------------------------------------------------------

			int GetCaps (const int index) const
			{
				return ::GetDeviceCaps (_h, index) ;
			}

			//--------------------------------------------------------------------
			// Sets one of the pixel to a specific color.
			//
			// Return value:  The old color of the pixel.
			//
			// Parameters:
			//
			// const int x            -> The x coordinate of the pixel.
			// const int y			  -> The y coordinate of the pixel.
			// const Win::Color color -> New color of the pixel.
			//--------------------------------------------------------------------

			Win::Color SetPixel (const Win::Color & color, const int x, const int y) const
			{
				return ::SetPixel (_h, x, y, color.GetColorRef ()) ;
			}

			//--------------------------------------------------------------------
			// Obtains the color of one of the pixel.
			//
			// Return value:  The color of the pixel.
			//
			// Parameters:
			//
			// const int x            -> The x coordinate of the pixel.
			// const int y			  -> The y coordinate of the pixel.
			//--------------------------------------------------------------------

			Win::Color GetPixel (const int x, const int y) const
			{
				return ::GetPixel (_h, x, y) ;
			}

			//--------------------------------------------------------------------
			// Changes the current position.
			//
			// Parameters:
			//
			// const int x    -> The x coordinate of the pixel.
			// const int y	  -> The y coordinate of the pixel.
			// Win::Point * p -> Will contain the old current position.
			//--------------------------------------------------------------------

			void MoveTo (const int x, const int y, Win::Point * p = NULL) const
			{
				if (::MoveToEx (_h, x, y, reinterpret_cast <LPPOINT> (p)) == 0)
					throw Win::Exception (TEXT("The method MoveTo was unsuccessful")) ;

			}

			//--------------------------------------------------------------------
			// Obtains the current position.
			//
			// Parameters:
			//
			// Win::Point * p -> Will contain the  current position.
			//--------------------------------------------------------------------

			void GetCurrentPosition (Win::Point & p) const
			{
				if (::GetCurrentPositionEx (_h, p) == 0)
					throw Win::Exception (TEXT("The method GetCurrentPosition was unsuccessful")) ;
				
			}

			Win::Point GetCurrentPositon () const ;

			//--------------------------------------------------------------------
			// Draws a line from a specified point to the current position.
			//
			// Parameters:
			//
			// const int x -> X coordinate of the specified point.
			// const int y -> Y coordinate of the specified point.
			//--------------------------------------------------------------------

			void LineTo (const int x, const int y) const
			{
				if (::LineTo (_h, x, y) == 0)
					throw Win::Exception (TEXT("The method LineTo was unsuccessful")) ;

			}

			//--------------------------------------------------------------------
			// Draws a line between two points.
			//
			// Parameters:
			//
			// const int x1 -> X coordinate of the first point.
			// const int y1 -> Y coordinate of the first point.
			// const int x2 -> X coordinate of the second point.
			// const int y2 -> Y coordinate of the second point.
			//--------------------------------------------------------------------

			void Line (const int x1, const int y1, const int x2, const int y2)  const ;

			//-----------------------------------------------------------------------
			// Draws an arc.
			//
			// Parameters:
			//
			// const int xLeft    -> X coordinate of the upper left conner of the 
			//					     bounding rectangle.
			// const int yTop     -> Y coordinate of the upper left conner of the 
			//					     bounding rectangle.
			// const int xRight   -> X coordinate of the lower right conner of the 
			//					     bounding rectangle.
			// const int yBorttom -> Y coordinate of the lower right conner of the 
			//				     	 bounding rectangle.
			// const int xStart   -> X coordinate of the first radial ending point.
			// const int yStart   -> Y coordinate of the first radial ending point.
			// const int xEnd     -> X coordinate of the second radial ending point.
			// const int yEnd     -> Y coordinate of the second radial ending point.
			//-----------------------------------------------------------------------

			void Arc (const int xLeft, const int yTop, const int xRight, const int yBottom, const int xStart, const int yStart, const int xEnd, const int yEnd) const
			{
				if (::Arc (_h, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd) == 0)
					throw Win::Exception (TEXT("The method Arc was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws a serie of connected lines.
			//
			// Parameters:
			//
			// const Win::Point * p  -> Points on an array containing the points of 
			//						    the lines.
			// const unsigned int nb -> Numbers of points.
			//-----------------------------------------------------------------------

			void Polyline (const Win::Point * p, const unsigned int nb) const
			{		
				 if (::Polyline (_h, reinterpret_cast <CONST POINT *> (p), nb) == 0)
					throw Win::Exception (TEXT("The method Polyline was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws a serie of connected lines.  The first point is the current
			// position.
			//
			// Parameters:
			//
			// const Win::Point * p  -> Points on an array containing the points of 
			//						    the lines.
			// const unsigned int nb -> Numbers of points.
			//-----------------------------------------------------------------------

			void PolylineTo (const Win::Point * p, const unsigned int nb) const
			{
				if (::Polyline (_h, reinterpret_cast <CONST POINT *> (p), nb) == 0)
					throw Win::Exception (TEXT("The method PolylineTo was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws many series of connected lines.
			//
			// Parameters:
			//
			// const Win::Point * p     -> Points on an array containing the points of 
			//						    the lines.
			// const DWORD * polyPoints -> Points on an array containg the number of
			//							   points for each polyline.
			// const unsigned int nb    -> Numbers of polylines.
			//-----------------------------------------------------------------------

			void PolyPolyline (const Win::Point * p, const DWORD * polyPoints, const int nb) const
			{
				if (::PolyPolyline (_h, reinterpret_cast <CONST POINT *> (p), polyPoints, nb) == 0)			
					throw Win::Exception (TEXT("The method PolyPolyline was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws a serie of bezier curves.
			//
			// Parameters:
			//
			// const Win::Point * p     -> Points on an array containing the end an
			//							   controls points of the curve
			// const unsigned int nb    -> Numbers of points in the array.
			//-----------------------------------------------------------------------

			void PolyBezier (const Win::Point * p, const int nb) const
			{
				if (::PolyBezier (_h, reinterpret_cast <CONST POINT *> (p), nb) == 0)
					throw Win::Exception (TEXT("The method PolyBezier was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws a serie of bezier curves.  The current position is the first 
			// point.
			//
			// Parameters:
			//
			// const Win::Point * p     -> Points on an array containing the end an
			//							   controls points of the curve
			// const unsigned int nb    -> Numbers of points in the array.
			//-----------------------------------------------------------------------

			void PolyBezierTo (const Win::Point * p, const int nb) const
			{
				if (::PolyBezierTo (_h, reinterpret_cast <CONST POINT *> (p), nb) == 0)
					throw Win::Exception (TEXT("The method PolyBezierTo was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws a rectangle.
			//
			// Parameters:
			//
			// const int xLeft    -> X coordinate of the upper left conner of the 
			//					     rectangle.
			// const int yTop     -> Y coordinate of the upper left conner of the 
			//					     brectangle.
			// const int xRight   -> X coordinate of the lower right conner of the 
			//					     rectangle.
			// const int yBottom  -> Y coordinate of the lower right conner of the 
			//				     	 rectangle.
			//-----------------------------------------------------------------------

			void Rectangle (const int xLeft, const int yTop, const int xRight, const int yBottom) const
			{
				if (::Rectangle (_h, xLeft, yTop, xRight, yBottom) == 0)
					throw Win::Exception (TEXT("The method Rectangle was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws a round rectangle.
			//
			// Parameters:
			//
			// const int xLeft               -> X coordinate of the upper left conner 
			//							  	    of the bounding rectangle.
			// const int yTop                -> Y coordinate of the upper left conner 
			//							 	    of the bounding rectangle.
			// const int xRight              -> X coordinate of the lower right conner 
			//							 	    of the bounding rectangle.
			// const int yBorttom            -> Y coordinate of the lower right conner 
			//								    of the bounding rectangle.
			// const int widthCornerEllipse  -> With of the ellipse used to make round
			//								    corner.
			// const int heightCornerEllipse -> Height of the ellipse used to make
			//									round corner.
			//-----------------------------------------------------------------------

			void RoundRectangle (const int xLeft, const int yTop, const int xRight, const int yBottom, const int widthCornerEllipse, const int heightCornerEllipse) const
			{
				if (::RoundRect (_h, xLeft, yTop, xRight, yBottom, widthCornerEllipse, heightCornerEllipse) == 0)
					throw Win::Exception (TEXT("The method RoundRectangle was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws an ellipse.
			//
			// Parameters:
			//
			// const int xLeft               -> X coordinate of the upper left conner 
			//							  	    of the bounding rectangle.
			// const int yTop                -> Y coordinate of the upper left conner 
			//							 	    of the bounding rectangle.
			// const int xRight              -> X coordinate of the lower right conner 
			//							 	    of the bounding rectangle.
			// const int yBottom            -> Y coordinate of the lower right conner 
			//								    of the bounding rectangle.
			//-----------------------------------------------------------------------

			void Ellipse (const int xLeft, const int yTop, const int xRight, const int yBottom) const
			{
				if (::Ellipse (_h, xLeft, yTop, xRight, yBottom) == 0)
					throw Win::Exception (TEXT("The method Ellipse was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws a pie.
			//
			// Parameters:
			//
			// const int xLeft    -> X coordinate of the upper left conner of the 
			//					     bounding rectangle.
			// const int yTop     -> Y coordinate of the upper left conner of the 
			//					     bounding rectangle.
			// const int xRight   -> X coordinate of the lower right conner of the 
			//					     bounding rectangle.
			// const int yBorttom -> Y coordinate of the lower right conner of the 
			//				     	 bounding rectangle.
			// const int xStart   -> X coordinate of the first radial ending point.
			// const int yStart   -> Y coordinate of the first radial ending point.
			// const int xEnd     -> X coordinate of the second radial ending point.
			// const int yEnd     -> Y coordinate of the second radial ending point.
			//-----------------------------------------------------------------------

			void Pie (const int xLeft, const int yTop, const int xRight, const int yBottom, const int xStart, const int yStart, const int xEnd, const int yEnd) const
			{
				if (::Pie (_h, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd) == 0)
					throw Win::Exception (TEXT("The method Pie was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws a chord.
			//
			// Parameters:
			//
			// const int xLeft    -> X coordinate of the upper left conner of the 
			//					     bounding rectangle.
			// const int yTop     -> Y coordinate of the upper left conner of the 
			//					     bounding rectangle.
			// const int xRight   -> X coordinate of the lower right conner of the 
			//					     bounding rectangle.
			// const int yBorttom -> Y coordinate of the lower right conner of the 
			//				     	 bounding rectangle.
			// const int xStart   -> X coordinate of the first radial ending point.
			// const int yStart   -> Y coordinate of the first radial ending point.
			// const int xEnd     -> X coordinate of the second radial ending point.
			// const int yEnd     -> Y coordinate of the second radial ending point.
			//-----------------------------------------------------------------------

			void Chord (const int xLeft, const int yTop, const int xRight, const int yBottom, const int xStart, const int yStart, const int xEnd, const int yEnd) const
			{
				if (::Chord (_h, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd) == 0)
					throw Win::Exception (TEXT("The method Chord was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws a polygon.
			//
			// Parameters:
			//
			// const Win::Point * p  -> Points on an array containing the points of 
			//						    the polygon.
			// const unsigned int nb -> Numbers of points.
			//-----------------------------------------------------------------------

			void Polygon (const Win::Point * p, const int nb) const
			{
				if (::Polygon (_h, reinterpret_cast<CONST POINT *> (p), nb) == 0)
					throw Win::Exception (TEXT("The method Polygon was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws many polygons.
			//
			// Parameters:
			//
			// const Win::Point * p     -> Points on an array containing the points of 
			//						       the polygons.
			// const DWORD * polyPoints -> Points on an array containg the number of
			//							   points for each polygon.
			// const unsigned int nb    -> Numbers of polygons.
			//-----------------------------------------------------------------------

			void PolyPolygon (const Win::Point * p, const int * polyCount, const int nb) const 
			{
				if (::PolyPolygon (_h, reinterpret_cast <CONST POINT *> (p), polyCount, nb) == 0)
					throw Win::Exception (TEXT("The method PolyPolygon was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Fills a region using a specified brush.
			//
			// Parameters:
			//
			// const HRGN rgn     -> Handle of the region.
			// const HBRUSH brush -> Handle of the brush.
			//-----------------------------------------------------------------------

			void FillRegion (const Win::Region::Handle rgn, const HBRUSH brush) const
			{
				if (::FillRgn (_h, rgn, brush) == 0)
					throw Win::Exception (TEXT("The method FillRegion was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Frames a region using a specified brush.
			//
			// Parameters:
			//
			// const HRGN rgn     -> Handle of the region.
			// const HBRUSH brush -> Handle of the brush.
			// const int xFrame   -> Width of the frame.
			// const int yFrame   -> Height of the frame.
			//-----------------------------------------------------------------------

			void FrameRegion (const Win::Region::Handle rgn, const HBRUSH brush, const int xFrame, const int yFrame) const 
			{
				if (::FrameRgn (_h, rgn, brush, xFrame, yFrame) == 0)
					throw Win::Exception (TEXT("The method FrameRegion was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Inverts the colors of a region.
			//
			// Parameters:
			//
			// const HRGN rgn -> Handle of the region.
			//-----------------------------------------------------------------------

			void InvertRegion (const Win::Region::Handle rgn) const 
			{
				 if (::InvertRgn (_h, rgn) == 0)
					throw Win::Exception (TEXT("The method InvertRegion was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Paints a region with the brush selected in the device context.
			//
			// Parameters:
			//
			// const HRGN rgn -> Handle of the region.
			//-----------------------------------------------------------------------

			void PaintRegion (const Win::Region::Handle rgn) const 
			{
				if (::PaintRgn (_h, rgn) == 0)
					throw Win::Exception (TEXT("The method PaintRegion was unsuccessful")) ;
			}

			//Path functions

			//-----------------------------------------------------------------------
			// Begins a path.
			//-----------------------------------------------------------------------

			void BeginPath () const 
			{
				if (::BeginPath (_h) == 0)
					throw Win::Exception (TEXT("The method BeginPath was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Ends a path.
			//-----------------------------------------------------------------------

			void EndPath () const 
			{
				if (::EndPath (_h) == 0)
					throw Win::Exception (TEXT("The method EndPath was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Strokes a path using the curently selected pen.
			//-----------------------------------------------------------------------
 
			void StrokePath () const 
			{
				if (::StrokePath (_h) == 0)
					throw Win::Exception (TEXT("The method StrokePath was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Fills a path using the curently selected brush.
			//-----------------------------------------------------------------------

			void FillPath () const 
			{
				if (::FillPath (_h) == 0)
					throw Win::Exception (TEXT("The method FillPath was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Strokes and fills a path.
			//-----------------------------------------------------------------------

			void StrokeAndFillPath () const 
			{
				if (::StrokeAndFillPath (_h) == 0)
					throw Win::Exception (TEXT("The method StrokeAndFillPath was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Fills a rectangle with a specified brush. 
			//
			// Parameters:
			//
			// Win::Rect & rect   -> The rectangle.
			// const HBRUSH brush -> Handle of the brush.
			//-----------------------------------------------------------------------

			void FillRect (Win::Rect & rect, const HBRUSH brush) const 
			{
				if (::FillRect (_h, reinterpret_cast <RECT *> (&rect), brush) == 0)
					throw Win::Exception (TEXT("The method FillRect was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Frames a rectangle with a specified brush. 
			//
			// Parameters:
			//
			// Win::Rect & rect   -> The rectangle.
			// const HBRUSH brush -> Handle of the brush.
			//-----------------------------------------------------------------------

			void FrameRect (Win::Rect & rect, const HBRUSH brush) const 
			{
				if (::FrameRect (_h, reinterpret_cast <RECT *> (&rect), brush) == 0)
					throw Win::Exception (TEXT("The method FrameRect was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Inverts the colors of a rectangle. 
			//
			// Parameters:
			//
			// Win::Rect & rect   -> The rectangle.
			//-----------------------------------------------------------------------

			void InvertRect (Win::Rect & rect) const 
			{
				if (::InvertRect (_h, reinterpret_cast <RECT *> (&rect) ) ==0)
					throw Win::Exception (TEXT("The method InvertRect was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws a focus rectangle. 
			//
			// Parameters:
			//
			// Win::Rect & rect   -> The coordinate rectangle.
			//-----------------------------------------------------------------------

			bool DrawFocusRect (const Win::Rect & rect) const 
			{
				if (::DrawFocusRect (_h, reinterpret_cast <CONST RECT *> (&rect)) == 0)
					throw Win::Exception (TEXT("The method DrawFocusRect was unsuccessful")) ;
			}

			Win::Canvas::Clipping SelectClipRegion (const Win::Region::Handle region) const ;

			//-----------------------------------------------------------------------
			// Selects the current path as  clipping region. 
			//
			// Parameters:
			//
			// const int clipMode -> Indiquates how the path is to be used.
			//-----------------------------------------------------------------------

			void SelectClipPath (const Win::Region::CombineFlag clipMode = Win::Region::Copy) const
			{
				if ( ::SelectClipPath (_h, clipMode) == 0)
					throw Win::Exception (TEXT("The method SelectClipPath was unsuccessful")) ;
			}

			Win::Canvas::Clipping IntersectClipRect (const int xLeft, const int yTop, const int xRight, const int yBottom) const ;
			Win::Canvas::Clipping IntersectClipRect (const Win::Rect & rect) const ;
			Win::Canvas::Clipping ExcludeClipRect   (const int xLeft, const int yTop, const int xRight, const int yBottom) const ;
			Win::Canvas::Clipping ExcludeClipRect   (const Win::Rect & rect) const ;
			Win::Canvas::Clipping OffsetClipRegion  (const int x, const int y) const ;
			Win::Canvas::Clipping GetClipBox        (Win::Rect & rect) const ;

			//-----------------------------------------------------------------------
			// Converts device points to logical points
			//
			// Parameters:
			//
			// Win::Point * p -> Points on an array of points to be converted.
			// const int nb   -> Number of points in the array.
			//-----------------------------------------------------------------------

			void DevicePointToLogicalPoint (Win::Point * p, const int nb = 1) const 
			{
				if (::DPtoLP (_h, reinterpret_cast <LPPOINT> (p), nb) == 0)
					throw Win::Exception (TEXT("The method DevicePointToLogicalPoint was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Converts logical points to device points
			//
			// Parameters:
			//
			// Win::Point * p -> Points on an array of points to be converted.
			// const int nb   -> Number of points in the array.
			//-----------------------------------------------------------------------

			void LogicalPointToDevicePoint (Win::Point * p, const int nb = 1) const 
			{
				if (::LPtoDP (_h, reinterpret_cast <LPPOINT> (&p), nb) == 0)
					throw Win::Exception (TEXT("The method LogicalPointToDevicePoint was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Display a string of text.
			//
			// Parameters:
			//
			// std::tstring & str-> The text buffer
			// const int x      -> X coordinate of the text.
			// const int y      -> Y coordinate of the text
			//-----------------------------------------------------------------------

			void TextOut (const std::tstring & str, const int x, const int y) const 
			{
				if (::TextOut (_h, x, y, str.c_str (), str.length ()) == 0)
					throw Win::Exception (TEXT("The method TextOut was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Display a string of text.  This methods expand tabs.
			//
			// Parameters:
			//
			// const int x         -> X coordinate of the text.
			// const int y         -> Y coordinate of the text
			// std::string const * buf    -> Contains the text.
			// const int tapPos    -> Number of tabs.
			// int * tapStopPos    -> Array containing tab position.
			// const int tabOrigin -> X coordinate used for tab expansion.
			//-----------------------------------------------------------------------

			void TabbedTextOut (const std::tstring & str, const int x, const int y, const int tapPos, int * tapStopPos, const int tabOrigin) const 
			{
				if (::TabbedTextOut (_h, x, y, str.c_str (), str.length (), tapPos,tapStopPos, tabOrigin ) == 0)
					throw Win::Exception (TEXT("The method TabbedTextOut was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Display a string of text on the screen. Can specify extended option.
			//
			// Parameters:
			//
			// const int x						   -> X coordinate of the text.
			// const int y                         -> Y coordinate of the text
			// Win::ExtendedTextOutOptions options -> Contain the desired extended 
			//										  options.
			// const Rect * rect                   -> Clipping rectangle (optional).
			// std::tstring str					   -> Contains the text.
			// const UINT nb					   -> Lenght of the text in characters.
			// CONST INT * spacing				   -> Spacing between adjacent 
			//										  character cells.
			//-----------------------------------------------------------------------

			void ExtentedTextOut (const std::tstring & str, const int x, const int y, Win::ExtendedTextOutOptions & options, const Rect * rect, CONST INT * spacing = NULL) const 
			{
				if (::ExtTextOut (_h, x, y, options._options, 
					reinterpret_cast<const RECT *> (rect), str.c_str (), str.length (), spacing) == 0)
						throw Win::Exception (TEXT("The method ExtendedTextOut was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Display a string of text on the screen. Can specify extended option.
			//
			// Parameters:
			//
			// const int x						   -> X coordinate of the text.
			// const int y                         -> Y coordinate of the text
			// UINT options						   -> Contain the desired extended 
			//										  options.
			// const Rect * rect                   -> Clipping rectangle (optional).
			// std::tstring str					   -> Contains the text.
			// const UINT nb					   -> Lenght of the text in characters.
			// CONST INT * spacing				   -> Spacing between adjacent 
			//										  character cells.
			//-----------------------------------------------------------------------

			void ExtentedTextOut (const std::tstring & str, const int x, const int y, UINT options, const Rect * rect, CONST INT * spacing = NULL) const 
			{
				if (::ExtTextOut (_h, x, y, options, 
					reinterpret_cast<const RECT *> (rect), str.c_str (), str.length (), spacing) == 0)
						throw Win::Exception (TEXT("The method ExtendedTextOut was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Draws formated text on the screen.  
			//
			// Parameters:
			// std::tstring const * buf			  -> Contains the text.
			// Win::Rect & rect			  -> The text will be formated in this rectangle.
			// Win::DrawTextFormat format -> Specicies the format of the text.
			//-----------------------------------------------------------------------

			void DrawText (const std::tstring & str, Win::Rect & rect, Win::DrawTextFormat & format) const 
			{
				if (::DrawText (_h, str.c_str (), str.length (), reinterpret_cast <RECT *> (&rect), format._format ) == 0) 
					throw Win::Exception (TEXT("The method DrawText was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws formated text on the screen.  
			//
			// Parameters:
			// char const * buf			  -> Contains the text.
			// Win::Rect & rect			  -> The text will be formated in this rectangle.
			// UINT format				  -> Specicies the format of the text.
			//-----------------------------------------------------------------------

			void DrawText (const std::tstring & str, Win::Rect & rect,UINT format) const 
			{
				if (::DrawText (_h, str.c_str (), str.length (), reinterpret_cast <RECT *> (&rect),format ) == 0) 
					throw Win::Exception (TEXT("The method DrawText was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Draws formated text on the screen.  Can use more advance options.
			//
			// Parameters:
			// char const * buf			    -> Contains the text.
			// const UINT nb			    -> Lenght of the text in characters.
			// Win::Rect & rect			    -> The text will be formated in this 
			//								   rectangle.
			// Win::DrawTextFormat format   -> Specicies the format of the text.
			// Win::DrawTextParams * params -> Points on an object defining various
			//								   parameters.
			//-----------------------------------------------------------------------			

			void ExtendedDrawText (std::tstring & str, Win::Rect & rect, Win::DrawTextFormat & format, Win::DrawTextParams * params) const 
			{
				if (::DrawTextEx (_h, &str[0], str.length(), reinterpret_cast <RECT *> (&rect), 
					  format._format, reinterpret_cast <LPDRAWTEXTPARAMS> (params) ) == 0)
						throw Win::Exception (TEXT("The method ExtendedDrawText was unsuccessful")) ;
			}
			
			//-----------------------------------------------------------------------
			// Draws formated text on the screen.  Can use more advance options.
			//
			// Parameters:
			// char const * buf			    -> Contains the text.
			// const UINT nb			    -> Lenght of the text in characters.
			// Win::Rect & rect			    -> The text will be formated in this 
			//								   rectangle.
			// UINT format					-> Specicies the format of the text.
			// Win::DrawTextParams * params -> Points on an object defining various
			//								   parameters.
			//-----------------------------------------------------------------------			

			void ExtendedDrawText (std::tstring & str, Win::Rect & rect, UINT format, Win::DrawTextParams * params) const 
			{
				if (::DrawTextEx (_h, &str[0], str.length(), reinterpret_cast <RECT *> (&rect), 
					  format, reinterpret_cast <LPDRAWTEXTPARAMS> (params) ) == 0)
						throw Win::Exception (TEXT("The method ExtendedDrawText was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current pen.
			//
			// Return value: The handle of the current pen.
			//-----------------------------------------------------------------------

			Win::Pen::Handle GetPenHandle () const 
			{
				assert (_penType == Win::Canvas::NormalPen) ;
				return reinterpret_cast <HPEN> (::GetCurrentObject (_h, OBJ_PEN) ) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current extended color pen.
			//
			// Return value: The handle of the current pen.
			//-----------------------------------------------------------------------

			Win::ExtendedPen::Color::Handle GetExtendedPenColorHandle () const 
			{
				assert (_penType == Win::Canvas::ExtendedPenColor) ;
				return reinterpret_cast <HPEN> (::GetCurrentObject (_h, OBJ_PEN) ) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current solid brush.
			//
			// Return value: The handle of the current brush.
			//-----------------------------------------------------------------------

			Win::Brush::Solid::Handle GetSolidBrushHandle () const 
			{
				assert (_brushType == BS_SOLID) ;
				return reinterpret_cast <HBRUSH> (::GetCurrentObject (_h, OBJ_BRUSH)) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current hatch brush.
			//
			// Return value: The handle of the current brush.
			//-----------------------------------------------------------------------

			Win::Brush::Hatch::Handle GetHatchBrushHandle () const 
			{
				assert (_brushType == BS_HATCHED) ;
				return reinterpret_cast <HBRUSH> (::GetCurrentObject (_h, OBJ_BRUSH)) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current pattern brush.
			//
			// Return value: The handle of the current brush.
			//-----------------------------------------------------------------------

			Win::Brush::Pattern::Handle GetPatternBrushHandle () const 
			{
				assert (_brushType == BS_PATTERN) ;
				return reinterpret_cast <HBRUSH> (::GetCurrentObject (_h, OBJ_BRUSH)) ;
			}

			//-------------------------------------------------------
			// Determines wether or not the canvas uses a normal pen.
			//
			// Return value: True if the pen is a normal pen, else false.
			//-------------------------------------------------------

			bool ContainsNormalPen () const
			{
				return _penType == Win::Canvas::NormalPen ;
			}

			//-------------------------------------------------------
			// Determines wether or not the canvas uses an extended pen.
			//
			// Return value: True if the pen is an extended pen, else false.
			//-------------------------------------------------------

			bool ContainsExtendedPen () const
			{
				return _penType == Win::Canvas::ExtendedPenColor ;
			}

			//-------------------------------------------------------
			// Determines wether or not the canvas uses a solid brush.
			//
			// Return value: True if the pen is a solid brush, else false.
			//-------------------------------------------------------

			bool ContainsSolidBrush () const
			{
				return _brushType == BS_SOLID ;
			}

			//-------------------------------------------------------
			// Determines wether or not the canvas uses a hatch brush.
			//
			// Return value: True if the pen is a hatch brush, else false.
			//-------------------------------------------------------

			bool ContainsHatchBrush () const
			{
				return _brushType == BS_HATCHED ;
			}

			//-------------------------------------------------------
			// Determines wether or not the canvas uses a pattern brush.
			//
			// Return value: True if the pen is a pattern brush, else false.
			//-------------------------------------------------------

			bool ContainsPatternBrush () const
			{
				return _brushType == BS_PATTERN ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current font.
			//
			// Return value: The handle of the current font.
			//-----------------------------------------------------------------------

			Win::Font::Handle GetFontHandle () const 
			{
				return reinterpret_cast <HFONT> (::GetCurrentObject (_h, OBJ_FONT)) ;
			}

			//-----------------------------------------------------------------------
			// Obtains some info about the current pen.
			//
			// Parameters:
			//
			// Win::Pen::Data & logPen -> Will contain the info about the current 
			//							   pen.
			//-----------------------------------------------------------------------

			void GetPenData (Win::Pen::Data & logPen) const 
			{
				if (::GetObject (GetPenHandle (), sizeof (LOGPEN), reinterpret_cast <LOGPEN *> (&logPen)) == 0)
					throw Win::Exception (TEXT("The method GetPenData was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains some info about the current extended pen.
			//
			// Parameters:
			//
			// Win::LogicalPen & logPen -> Will contain the info about the current 
			//							   extended pen.
			//-----------------------------------------------------------------------

			void GetExtendedPenColorData (Win::ExtendedPen::Color::Data & logPen) const 
			{
				if (::GetObject (GetExtendedPenColorHandle (), sizeof (EXTLOGPEN), reinterpret_cast <EXTLOGPEN *> (&logPen)) == 0)
					throw Win::Exception (TEXT("The method GetExtendedColorPenData was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains some info about the current brush.
			//
			// Return value: The number of byte of info.
			//
			// Parameters:
			//
			// Win::Brush::Solid::Data -> Will contain the info about the current 
			//							  brush.
			//-----------------------------------------------------------------------

			void GetSolidBrushData (Win::Brush::Solid::Data & logBrush) const 
			{
				if (::GetObject (GetSolidBrushHandle (), sizeof (LOGBRUSH), reinterpret_cast<LOGBRUSH *> (&logBrush) ) == 0)
					throw Win::Exception (TEXT("The method GetSolidBrushData was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains some info about the current brush.
			//
			// Return value: The number of byte of info.
			//
			// Parameters:
			//
			// Win::Brush::Hatch::Data -> Will contain the info about the current 
			//							  brush.
			//-----------------------------------------------------------------------

			void GetHatchBrushData (Win::Brush::Hatch::Data & logBrush) const 
			{
				if (::GetObject (GetHatchBrushHandle (), sizeof (LOGBRUSH), reinterpret_cast<LOGBRUSH *> (&logBrush) ) == 0)
					throw Win::Exception (TEXT("The method GetHatchBrushData was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains some info about the current font.
			//
			// Parameters:
			//
			// Win::LogicalFont & logFont -> Will contain the info about the current 
			//								 font.
			//-----------------------------------------------------------------------

			void GetFontData (Win::Font::Data & logFont) const 
			{
				if (::GetObject (GetFontHandle (), sizeof (LOGFONT), reinterpret_cast <LOGFONT *> (&logFont) ) == 0)
					throw Win::Exception (TEXT("The method GetFontData was unsuccessful")) ;
			}

			//--------------------------------------------------------------------
			// Obtains various information about the current physical font in a 
			// Win::TextMetrics object.  
			//
			// Parameters:
			//
			// Win::TextMetrics & textMetrics -> Will contain the information
			//                                   about the physical font.
			//--------------------------------------------------------------------

			void GetTextMetrics (Win::Font::TextMetrics & textMetrics) const 
			{
				if (::GetTextMetrics (_h, reinterpret_cast <LPTEXTMETRIC> (&textMetrics) ) == 0)
					throw Win::Exception (TEXT("The method GetTextMetrics was unsuccessful")) ;
			}

			Win::Pen::Data GetPenData                             () const ;
			Win::ExtendedPen::Color::Data GetExtendedPenColorData () const ;
			Win::Brush::Solid::Data GetSolidBrushData             () const ;
			Win::Brush::Hatch::Data GetHatchBrushData             () const ;
			Win::Font::Data GetFontData                           () const ;
			Win::Font::TextMetrics GetTextMetrics                 () const ;

			//-----------------------------------------------------------------------
			// Sets the text alignement.
			// 
			// parameters:
			//
			// const Win::Font::VerticalTextAlign vert   -> The vertical alignement.
			// const Win::Font::HorizontalTextAlign horz -> The horizontal alignement.
			// const Win::Font::UpdateTextAlign update   -> Wheter or not the current pos is updated.
			//-----------------------------------------------------------------------

			void SetTextAlign (const Win::Font::VerticalTextAlign vert, const Win::Font::HorizontalTextAlign horz, const Win::Font::UpdateCurrentPos update = Win::Font::NoUpdate)
			{
				if (::SetTextAlign (_h, vert | horz | update) == GDI_ERROR)
					throw Win::Exception (TEXT("The method SetTextAlign was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current text alignement.
			//
			// Return value: The current text alignement.
			//-----------------------------------------------------------------------

			UINT GetTextAlign () const 
			{
				return ::GetTextAlign (_h) ;
			}

			//-----------------------------------------------------------------------
			// Sets the text color.
			// 
			// parameters:
			//
			// const Win::Color & color -> The new color.
			//-----------------------------------------------------------------------

			void SetTextColor (const Win::Color & color)
			{
				if (::SetTextColor (_h, color) == CLR_INVALID)
					throw Win::Exception (TEXT("The method SetTextColor was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current text color.
			//
			// Return value: The current text color.
			//-----------------------------------------------------------------------

			Win::Color GetTextColor () const 
			{
				return ::GetTextColor (_h) ;
			}

			//-----------------------------------------------------------------------
			// Sets the extra spacing between character.
			// 
			// parameters:
			//
			// const int extra -> The new extra spacing
			//-----------------------------------------------------------------------

			void SetTextCharacterExtra (const int extra)
			{
				if (::SetTextCharacterExtra (_h, extra) == 0x80000000)
					throw Win::Exception (TEXT("The method SetTextCharacterExtra was unsuccessful")) ;

			}

			//-----------------------------------------------------------------------
			// Obtains the current text extra character spacing.
			//
			// Return value: The current text extra character spacing.
			//-----------------------------------------------------------------------

			int GetTextCharacterExtra () const 
			{
				return ::GetTextCharacterExtra (_h) ;
			}

			//-----------------------------------------------------------------------
			// Sets the background color.
			// 
			// parameters:
			//
			// const Win::Color & color -> The new color.
			//-----------------------------------------------------------------------

			void SetBackgroundColor (const Win::Color & color)
			{
				if (::SetBkColor (_h, color) == CLR_INVALID)
					throw Win::Exception (TEXT("The method SetBackgroundColor was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current background color.
			//
			// Return value: The current background color.
			//-----------------------------------------------------------------------

			Win::Color GetBackgroundColor () const 
			{
				return ::GetBkColor (_h) ;
			}

			//-----------------------------------------------------------------------
			// Sets the background mode.
			// 
			// parameters:
			//
			// const Win::Background::Mode mode -> The new mode.
			//-----------------------------------------------------------------------

			void SetBackgroundMode (const Win::Background::Mode mode)
			{
				if (::SetBkMode (_h, mode) == 0)
					throw Win::Exception (TEXT("The method SetBackgroundColor was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current background mode.
			//
			// Return value: The current background mode.
			//-----------------------------------------------------------------------

			Win::Background::Mode GetBackgroundMode () const 
			{
				return static_cast <Win::Background::Mode> (::GetBkMode (_h)) ;
			}

			//-----------------------------------------------------------------------
			// Sets the polygon filling mode.
			// 
			// parameters:
			//
			// const Win::Polygon::FillMode mode -> The new mode.
			//-----------------------------------------------------------------------

			void SetPolygonFillingMode (const Win::Polygon::FillMode mode)
			{
				if (::SetPolyFillMode (_h, mode) == 0)
					throw Win::Exception (TEXT("The method SetPolygonFillingMode was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current polygon filling mode.
			//
			// Return value: The current polygon filling mode.
			//-----------------------------------------------------------------------

			Win::Polygon::FillMode GetPolygonFillMode () const 
			{
				return static_cast <Win::Polygon::FillMode> (::GetPolyFillMode (_h)) ;
			}

			//-----------------------------------------------------------------------
			// Sets the drawing mode.
			// 
			// parameters:
			//
			// const Win::Drawing::Mode mode -> The new mode.
			//-----------------------------------------------------------------------

			void SetDrawingMode (const Win::Drawing::Mode mode)
			{
				if (::SetROP2 (_h, mode) == 0)
					throw Win::Exception (TEXT("The method SetDrawingMode was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current drawing mode.
			//
			// Return value: The current drawing mode.
			//-----------------------------------------------------------------------

			Win::Drawing::Mode GetDrawingMode () const 
			{
				return static_cast <Win::Drawing::Mode> (::GetROP2 (_h)) ;
			}

			//-----------------------------------------------------------------------
			// Sets the viewport origin.
			//
			// Parameters:  
			// const int x    -> The new x origin.
			// const int y    -> The new y origin.
			// Win::Point * p -> Will contain the old origin.
			//-----------------------------------------------------------------------

			void SetViewportOrigin (const int x, const int y, Win::Point * p) 
			{
				if (::SetViewportOrgEx (_h, x, y, reinterpret_cast <LPPOINT> (p)) == 0)
					throw Win::Exception (TEXT("The method SetViewportOrigin was unsuccessful")) ;
			}

			//--------------------------------------------------------------------
			// Obtains the viewport origin.
			//
			// Parameters:
			//
			// Win::Point & p -> Will contain the viewport origin.
			//--------------------------------------------------------------------

			void GetViewportOrigin (Win::Point & p) const 
			{
				if (::GetViewportOrgEx (_h, reinterpret_cast <LPPOINT> (&p)) == 0)
					throw Win::Exception (TEXT("The method GetViewportOrigin was unsuccessful")) ;
			}

			Win::Point GetViewportOrigin () const ;

			//-----------------------------------------------------------------------
			// Sets the viewport Extend.
			//
			// Parameters:  
			// const int xExtend    -> The new x origin.
			// const int yExtend    -> The new y origin.
			// Win::Point * p        -> Will contain the old origin.
			//-----------------------------------------------------------------------

			void SetViewportExtend (const int xExtend, const int yExtend, Win::Size * size) 
			{
				if (::SetViewportExtEx  (_h, xExtend, yExtend, reinterpret_cast <LPSIZE> (size)) == 0)
					throw Win::Exception (TEXT("The method SetViewportExtend was unsuccessful")) ;
			}

			//--------------------------------------------------------------------
			// Obtains the viewport extend.
			//
			// Parameters:
			//
			// Win::Size & size -> Will contain the viewport extend.
			//--------------------------------------------------------------------

			void GetViewportExtend (Win::Size & size) const 
			{
				if (::GetViewportExtEx (_h, reinterpret_cast <LPSIZE> (&size) ) == 0)
					throw Win::Exception (TEXT("The method GetViewportExtend was unsuccessful")) ;
			}

			Win::Size GetViewportExtend () const ;

			//-----------------------------------------------------------------------
			// Sets window origin.
			//
			// Parameters:  
			// const int x    -> The new x origin.
			// const int y    -> The new y origin.
			// Win::Point * p -> Will contain the old origin.
			//-----------------------------------------------------------------------

			void SetWindowOrigin (const int x, const int y, Win::Point * p) 
			{
				if (::SetWindowOrgEx (_h, x, y, reinterpret_cast <LPPOINT> (p)) == 0)
					throw Win::Exception (TEXT("The method SetWindowOrigin was unsuccessful")) ;
			}

			//--------------------------------------------------------------------
			// Obtains the window origin.
			//
			// Parameters:
			//
			// Win::Point & p -> Will contain the window origin.
			//--------------------------------------------------------------------

			void GetWindowOrigin (Win::Point & p) const 
			{
				if (::GetWindowOrgEx (_h, reinterpret_cast <LPPOINT> (&p)) == 0)
					throw Win::Exception (TEXT("The method GetWindowOrigin was unsuccessful")) ;
			}

			Win::Point GetWindowOrigin () const ;

			//-----------------------------------------------------------------------
			// Sets the window Extend.
			//
			// Parameters:  
			// const int xExtend    -> The new x origin.
			// const int yExtend    -> The new y origin.
			// Win::Point * p        -> Will contain the old origin.
			//-----------------------------------------------------------------------

			void SetWindowtExtend (const int xExtend, const int yExtend, Win::Size * size) 
			{
				if (::SetWindowExtEx  (_h, xExtend, yExtend, reinterpret_cast <LPSIZE> (size)) == 0)
					throw Win::Exception (TEXT("The method SetWindowExtend was unsuccessful")) ;
			}

			//--------------------------------------------------------------------
			// Obtains the window extend.
			//
			// Return value: True if the method succeed, else false.
			//
			// Parameters:
			//
			// Win::Size & size -> Will contain the window extend.
			//--------------------------------------------------------------------

			void GetWindowExtend (Win::Size & size) const 
			{
				if (::GetWindowExtEx(_h, reinterpret_cast <LPSIZE> (&size) ) == 0)
					throw Win::Exception (TEXT("The method GetWindowExtend was unsuccessful")) ;
			}

			Win::Size GetWindowExtend () const ;

			//-----------------------------------------------------------------------
			// Sets the mapping mode.
			// 
			// parameters:
			//
			// const Win::Mapping::Mode mode -> The new mode.
			//-----------------------------------------------------------------------

			void SetMappingMode (const Win::Mapping::Mode mode)
			{
				if (::SetMapMode  (_h, mode) == 0)
					throw Win::Exception (TEXT("The method SetMapMode was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current mapping mode.
			//
			// Return value: The current mapping mode.
			//-----------------------------------------------------------------------

			Win::Mapping::Mode GetMapMode () const 
			{
				return static_cast <Win::Mapping::Mode> (::GetMapMode (_h)) ;
			}

			//-----------------------------------------------------------------------
			// Sets the brush origin.
			//
			// Parameters:  
			// const int x    -> The new x origin.
			// const int y    -> The new y origin.
			// Win::Point * p -> Will contain the old origin.
			//-----------------------------------------------------------------------

			void SetBrushOrigin (const int x, const int y, Win::Point * p) 
			{
				if (::SetBrushOrgEx (_h, x, y, reinterpret_cast <LPPOINT> (p)) == 0)
					throw Win::Exception (TEXT("The method SetBrushOrigin was unsuccessful")) ;
			}

			//--------------------------------------------------------------------
			// Obtains the brush origin..
			//
			// Parameters:
			//
			// Win::Point & point -> Will contain the brush origin.
			//--------------------------------------------------------------------

			void GetBrushOrigin (Win::Point & p) const 
			{
				if (::GetBrushOrgEx (_h, reinterpret_cast<LPPOINT> (&p)) == 0)
					throw Win::Exception (TEXT("The method GetBrushOrigin was unsuccessful")) ;
			}

			Win::Point GetBrushOrigin () const ;

			//-----------------------------------------------------------------------
			// Sets the stretch blit mode.
			// 
			// parameters:
			//
			// const int mode -> The new mode.
			//-----------------------------------------------------------------------

			void SetStretchBlitMode (const int mode)
			{
				if (::SetStretchBltMode  (_h, mode) == 0)
					throw Win::Exception (TEXT("The method SetStretchBlitMode was unsuccessful")) ;
			}

			//-----------------------------------------------------------------------
			// Obtains the current stretch blit mode.
			//
			// Return value: The current stretch blit mode.
			//-----------------------------------------------------------------------

			int GetStretchBltMode () const 
			{
				return ::GetStretchBltMode (_h) ;
			}

			//-----------------------------------------------------------------------
			// Updates the colors of the palette.
			//-----------------------------------------------------------------------

			void UpdatePaletteColors () const 
			{
				::UpdateColors (_h) ;
			}

			//-----------------------------------------------------------------------
			// Draw a bitmap on the the canvas.
			//
			// parameters:
			//
			// Win::Canvas & source   -> Canvas holding the bitmap.
			// const int destX        -> x coordinate where the bitmap will be blitted.
			// const int destY        -> y coordinate where the bitmap will be blitted.
			// const int sourceWidth  -> Width of the bitmap.
			// const int sourceHeight -> Height of the bitmap.
			// const int sourceX      -> x coordinate of the source.
			// const int sourceY      -> y coordinate of the source.
			// const DWORD mode       -> Drawing mode used to blit the bitmap.
			//-----------------------------------------------------------------------

			void Blit (Win::Canvas & source, const int destX, const int destY, const int sourceWidth, const int sourceHeight, const int sourceX = 0, const int sourceY = 0, const DWORD mode = SRCCOPY)
			{
				if (::BitBlt (_h, destX, destY, sourceWidth, sourceHeight, source, sourceX, sourceY, mode) == 0)
					throw Win::Exception (TEXT("The method Blit was unsuccessful")) ;					
			}

			//-----------------------------------------------------------------------
			// Draw a bitmap on the the canvas, the bitmap can be stretched.
			//
			// parameters:
			//
			// Win::Canvas & source   -> Canvas holding the bitmap.
			// const int destX        -> x coordinate where the bitmap will be blitted.
			// const int destY        -> y coordinate where the bitmap will be blitted.
			// const int destWidth    -> Width of the stretch bitmap.
			// const int destHeight   -> Height of the stretch bitmap.
			// const int sourceWidth  -> Width of the bitmap.
			// const int sourceHeight -> Height of the bitmap.
			// const int sourceX      -> x coordinate of the source.
			// const int sourceY      -> y coordinate of the source.
			// const DWORD mode       -> Drawing mode used to blit the bitmap.
			//-----------------------------------------------------------------------

			void StretchBlit (Win::Canvas & source, const int destX, const int destY, const int destWidth, const int destHeight, const int sourceWidth, const int sourceHeight, const int sourceX = 0, const int sourceY = 0, const DWORD mode = SRCCOPY)
			{
				if (::StretchBlt (_h, destX, destY, destWidth, destHeight, source, sourceX, sourceY, sourceWidth, sourceHeight, mode) == 0)
					throw Win::Exception (TEXT("The method StretchBlit was unsuccessful")) ;					
			}

			/*void DrawImageFromImageList (Win::ImageListHandle h, const int index, const int x, const int y, const int flag = ILD_NORMAL, const int overlayIndex = 0) 
			{
				if (ImageList_Draw (h, index, _h, x, y, flag | INDEXTOOVERLAYMASK (overlayIndex)) == 0)
					throw Win::Exception ("Error, could not draw the image from the image list") ;
			}
		
			void DrawImageFromImageList (Win::ImageListHandle h, const int index, const int x, const int y, const int width, const int height, const int flag = ILD_NORMAL, const int overlayIndex = 0) 
			{
				if (ImageList_DrawEx (h, index, _h, x, y, width, height, CLR_DEFAULT, CLR_DEFAULT, flag | INDEXTOOVERLAYMASK (overlayIndex)) == 0)
					throw Win::Exception ("Error, could not draw the image from the image list") ;
			}*/

		private:

			enum PenType {NormalPen = 0, ExtendedPenColor = 1} ;

			BYTE        _brushType ;
			Win::Canvas::PenType _penType ;

		} ;

		//-------------------------------------------------------------------
		// Win::UpdateCanvas represents a device context use to update the
		// client area of a window outside of the WM_PAINT message.
		//-------------------------------------------------------------------

		class UpdateCanvas : public Win::Canvas
		{
		public:

			//-------------------------------------------------------------------
			// Constructor.  Creates the device context.
			//
			// Parameters:
			// 
			// const HWND & hwnd -> The device context will represent the client
			//					        area of this window.
			//-------------------------------------------------------------------

			UpdateCanvas (const Win::Base & hwnd) 
				:	Canvas (::GetDC (hwnd)),
				_hwnd (hwnd) 
			  {}

			//-------------------------------------------------------------------
			// Destructor.  Release the device context.
			//-------------------------------------------------------------------

			~UpdateCanvas () 
			{
				::ReleaseDC (_hwnd, _h) ;
			}

		private:

			UpdateCanvas (const Win::UpdateCanvas & canvas) ;
			UpdateCanvas & operator = (Win::UpdateCanvas & canvas) ;

		private:

			Win::Base _hwnd ;
		} ;

		//-------------------------------------------------------------------
		// Win::PaintCanvas represents a device context use to update the
		// client area of a window during a WM_PAINT message.
		//-------------------------------------------------------------------

		class PaintCanvas : public Canvas
		{
		public:

			//-------------------------------------------------------------------
			// Constructor.  Creates the device context.
			//
			// Parameters:
			// 
			// const HWND & hwnd -> The device context will represent the client
			//							area of this window.
			//-------------------------------------------------------------------

			PaintCanvas (const Win::Base & hwnd)
				: Canvas (::BeginPaint (hwnd, &_paint)),
				  _hwnd (hwnd) 
			{}

			//-------------------------------------------------------------------
			// Destructor.  Release the device context.
			//-------------------------------------------------------------------

			~PaintCanvas ()
			{
				::EndPaint (_hwnd, &_paint) ;
			}

			//-------------------------------------------------------------------
			// Obtains the top of the rectangle that need repainting.
			//
			// Return value: The top of the rectangle.
			//-------------------------------------------------------------------

			int Top () const    
			{
				return _paint.rcPaint.top ; 
			}

			//-------------------------------------------------------------------
			// Obtains the bottom of the rectangle that need repainting.
			//
			// Return value: The bottom of the rectangle.
			//-------------------------------------------------------------------

			int  Bottom () const 
			{
				return _paint.rcPaint.bottom ; 
			}

			//-------------------------------------------------------------------
			// Obtains the left of the rectangle that need repainting.
			//
			// Return value: The left of the rectangle.
			//-------------------------------------------------------------------

			int  Left () const   
			{
				return _paint.rcPaint.left ; 
			}

			//-------------------------------------------------------------------
			// Obtains the right of the rectangle that need repainting.
			//
			// Return value: The top of the rectangle.
			//-------------------------------------------------------------------

			int  Right () const  
			{
				return _paint.rcPaint.right ; 
			}

			//-------------------------------------------------------------------
			// Determines if the background was erased.
			//
			// Return value: True if the backgrounds was erased, else false.
			//-------------------------------------------------------------------

			bool BackgroundWasErased () const 
			{
				return _paint.fErase == FALSE ;
			}

		private:

			PaintCanvas (const Win::PaintCanvas & canvas) ;
			PaintCanvas & operator = (Win::PaintCanvas & canvas) ;

		private:

			Win::Base    _hwnd ;
			PAINTSTRUCT _paint ;
		} ;

		//-------------------------------------------------------------------
		// Win::DisplayCanvas represents a device context giving access to the
		// whole monitor.  Useful when there are no windows.
		//-------------------------------------------------------------------

		class DisplayCanvas: public Canvas
		{
		public:

			//-------------------------------------------------------------------
			// Constructor.  Creates the device context.
			//-------------------------------------------------------------------

			DisplayCanvas ()
				: Canvas (::CreateDC (TEXT("DISPLAY"), NULL, NULL, NULL))
			{}

			//-------------------------------------------------------------------
			// Destructor. Deletes the device context.
			//-------------------------------------------------------------------

			~DisplayCanvas ()
			{
				::DeleteDC (_h) ;
			}

		private:

			DisplayCanvas (const Win::DisplayCanvas & canvas) ;
			DisplayCanvas & operator = (Win::DisplayCanvas & canvas) ;
		} ;


		//-------------------------------------------------------------------
		// Win::WindowCanvas represents a device context representing a whole
		// window.
		//-------------------------------------------------------------------

		class WindowCanvas : public Canvas
		{
		public:

			//-------------------------------------------------------------------
			// Constructor.  Creates the device context.
			//
			// Parameters:
			// 
			// const HWND hwnd -> The device context will represent this window.
			//-------------------------------------------------------------------

			WindowCanvas (const Win::Base & hwnd)
				: Canvas (::GetWindowDC (hwnd)),
			 	  _hwnd (hwnd)
			{}

			//-------------------------------------------------------------------
			// Destrucctor.  Releases the device context.
			//-------------------------------------------------------------------

			~WindowCanvas ()
			{
				::ReleaseDC (_hwnd, _h) ;
			}

		private:

			WindowCanvas (const Win::WindowCanvas & canvas) ;
			WindowCanvas & operator = (Win::WindowCanvas & canvas) ;

		private:

			Win::Base _hwnd ;
		} ;

		//-------------------------------------------------------------------
		// Win::MemoryCanvas represents a memory device context used to
		// hold a bitmap.
		//-------------------------------------------------------------------

		class MemoryCanvas : public Canvas
		{
		public:

			MemoryCanvas ()
				: Canvas (::CreateCompatibleDC (NULL))
			{}
			//-------------------------------------------------------------------
			// Constructor.  Creates the device context.
			//
			// Parameters:
			// 
			// const Win::Canvas & canvas -> The device context will be compatible with this
			//								 other device context.
			//-------------------------------------------------------------------

			MemoryCanvas (const Win::Canvas & canvas) 
				: Canvas (::CreateCompatibleDC (canvas))
			{}

			//-------------------------------------------------------------------
			// Destrucctor.  Releases the device context.
			//-------------------------------------------------------------------

			~MemoryCanvas ()
			{
				::DeleteDC(_h) ; 
			}

		private:

			MemoryCanvas (const Win::MemoryCanvas & canvas) ;
			MemoryCanvas & operator = (Win::MemoryCanvas & canvas) ;
		} ;

		namespace GDI
		{
			//--------------------------------------------------------------------
			// Win::GDI::Holder is used to select an object in a
			// device context.  When a Win::GDI::Holder is created, a new object
			// is selected in the device context.  When the Holder is destroyed,
			// the old object is re-selected.  Win::GDI::Holder is used to 
			// implement holders for every appropriate type of GDI handles (pen,
			// brush, font, ect).
			//--------------------------------------------------------------------

			template <class BaseHandle, class BaseCanvas = Win::Canvas>
			class Holder
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Selects a specified object in a device context.
				//
				// Parameters:
				//
				// const HDC hdc          -> The device context.
				// const NativeHandle pen -> Handle of the object to be selected.
				//--------------------------------------------------------------------

				Holder (BaseCanvas & canvas, const BaseHandle object)
					: _canvas (canvas)

				{
					_old = reinterpret_cast <BaseHandle::Type> 
								(::SelectObject (_canvas, object)) ;
				}

				//--------------------------------------------------------------------
				// Destructor.  The old object is selected in the device context.
				//--------------------------------------------------------------------

				~Holder ()
				{		
					::SelectObject (_canvas, _old) ;
				}

			protected:

				Win::Canvas &    _canvas ; // The device context in which the object is selected.
				typename BaseHandle::Type _old ;    // Hold the old object.	
			} ;
		}

		namespace Bitmap
		{
			namespace DDB
			{
				typedef Win::GDI::Holder <Win::Bitmap::DDB::Handle, Win::MemoryCanvas> Holder; // Holder for a DDB
			}

			namespace DIBSection
			{
				typedef Win::GDI::Holder <Win::Bitmap::DIBSection::Handle, Win::MemoryCanvas> Holder; // Holder for a DDB
			}
		}

		namespace Brush
		{
			typedef Win::GDI::Holder <Win::Brush::Handle> Holder ; // Holder for a brush.

			namespace Solid
			{
				//-------------------------------------------------------
				// Holder for a solid brush.
				//-------------------------------------------------------

				class Holder : public Win::GDI::Holder <Win::Brush::Solid::Handle>
				{
				public:
					Holder (Win::Canvas & canvas, Win::Brush::Solid::Handle h)
						: Win::GDI::Holder <Win::Brush::Solid::Handle> (canvas, h)
					{
						_brushType = canvas._brushType ;
						canvas._brushType = BS_SOLID ;
					}

					~Holder ()
					{
						_canvas._brushType = _brushType ;
					}

				private:

					BYTE _brushType ;
				} ;
			}

			namespace Hatch
			{
				//-------------------------------------------------------
				// Holder for a hatch brush.
				//-------------------------------------------------------

				class Holder : public Win::GDI::Holder <Win::Brush::Hatch::Handle>
				{
				public: 

					Holder (Win::Canvas & canvas, Win::Brush::Hatch::Handle h)
						: Win::GDI::Holder <Win::Brush::Hatch::Handle> (canvas, h)
					{
						_brushType = canvas._brushType ;
						canvas._brushType = BS_HATCHED ;
					}

					~Holder ()
					{
						_canvas._brushType = _brushType ;
					}

				private:

					BYTE  _brushType ;
				} ;
			}

			namespace Pattern
			{
				//-------------------------------------------------------
				// Holder for a pattern brush.
				//-------------------------------------------------------

				class Holder : public Win::GDI::Holder <Win::Brush::Pattern::Handle>
				{
				public:

					Holder (Win::Canvas & canvas, Win::Brush::Pattern::Handle h)
						: Win::GDI::Holder <Win::Brush::Pattern::Handle> (canvas, h)
					{
						_brushType = canvas._brushType ;
						canvas._brushType = BS_PATTERN ;
					}

					~Holder ()
					{
						
						_canvas._brushType = _brushType ;
					}

				private:

					 BYTE _brushType ;
				} ;		
			}
		}

		namespace Pen
		{

			//-------------------------------------------------------
			// Holder for a pen.
			//-------------------------------------------------------

			class Holder : public Win::GDI::Holder <Win::Pen::Handle>
			{
			public:

				Holder (Win::Canvas & canvas, Win::Pen::Handle h)
						: Win::GDI::Holder <Win::Pen::Handle> (canvas, h)
				{
					_penType = canvas._penType ;
					canvas._penType = Win::Canvas::NormalPen ;
				}
				
				~Holder ()
				{
					_canvas._penType = _penType ;
				}

				private:

					Win::Canvas::PenType _penType ;
			} ;
		}

		namespace ExtendedPen
		{
			namespace Color
			{
				//-------------------------------------------------------
				// Holder for an extended pen.
				//-------------------------------------------------------

				class Holder : public Win::GDI::Holder <Win::ExtendedPen::Color::Handle>
				{
				public:

					Holder (Win::Canvas & canvas, Win::ExtendedPen::Color::Handle h)
						: Win::GDI::Holder <Win::ExtendedPen::Color::Handle> (canvas, h)
					{
						_penType = canvas._penType ;
						canvas._penType = Win::Canvas::ExtendedPenColor ;
					}

				
					~Holder ()
					{
						_canvas._penType = _penType ;
					}

					private:

						Win::Canvas::PenType _penType ;
				} ;	
			}
		}

		namespace Font
		{
			typedef Win::GDI::Holder <Win::Font::Handle> Holder ; // Holder for a brush.
		}

		namespace Palette
		{
			//--------------------------------------------------------------------
			// Win::Palette::Holder is used to select a palette in a
			// device context.  When a Win::Palette::Holder is created, a new palette
			// is selected in the device context.  When the object is destroyed,
			// the old palette is re-selected.
			//--------------------------------------------------------------------

			class Holder
			{
			public:

				//--------------------------------------------------------------------
				// Constructor.  Selects a specified palette in a device context. and
				// realize it.
				//
				// Parameters:
				//
				// const HDC hdc    -> The device context.
				// const HFONT font -> Handle of the font to be selected.
				//--------------------------------------------------------------------

				Holder (const Win::Canvas & canvas, const Win::Palette::Handle palette)
					: _hdc (canvas)

				{
					  _oldPalette = reinterpret_cast <HPALETTE> (::SelectPalette(_hdc, palette, false)) ;

					  ::RealizePalette (_hdc) ;
				}

				//--------------------------------------------------------------------
				// Destructor.  Selects the old palette in a device context.
				//--------------------------------------------------------------------

				~Holder ()
				{
					::SelectPalette ( _hdc, _oldPalette, false ) ;
				}

			private:

				HDC      _hdc ; // The device context in which the palette is selected.
				HPALETTE _oldPalette ; // Hold the old palette.
			} ;
		}
	}


#endif