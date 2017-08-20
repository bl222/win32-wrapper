#if !defined (WINIMAGELOADER_H)

	#define WINIMAGELOADER_H
	#include "useunicode.h"
	namespace Win
	{
		//--------------------------------------------------------------------
		// ImageLoader is a base class for all class used to load image.
		// (There a 3, Win::Icon::Loader, Win::Cursor::Loader and Win::Bitmap::Loader
		//--------------------------------------------------------------------

		class ImageLoader
		{
		public:
				//--------------------------------------------------------------------
				// Changes the instance of the program.
				//
				// Parameters:
				//
				// const HINSTANCE hInstance -> The new instance.
				//--------------------------------------------------------------------

				void SetInstance (const HINSTANCE hInstance)
				{
					_hInstance = hInstance ;
				}
				//--------------------------------------------------------------------
				// Specifies that the image will use default color.
				//--------------------------------------------------------------------

				void SetDefaultColor ()
				{
					_flag |= LR_DEFAULTCOLOR ;
				}

				//--------------------------------------------------------------------
				// Specifies that the image will use default size.
				//--------------------------------------------------------------------

				void SetDefaultSize ()
				{
					_flag |= LR_DEFAULTSIZE ;
				}

				//--------------------------------------------------------------------
				// Specifies that the image will map 3D colors
				//--------------------------------------------------------------------

				void SetMap3DColors ()
				{
					_flag |= LR_LOADMAP3DCOLORS ;
				}

				//--------------------------------------------------------------------
				// Specifies that the image will be transparent.
				//--------------------------------------------------------------------

				void SetTransparent ()
				{
					_flag |= LR_LOADTRANSPARENT ;
				}

				//--------------------------------------------------------------------
				// Specifies that the image will be monochrome.
				//--------------------------------------------------------------------

				void SetMonochrome ()
				{
					_flag |= LR_MONOCHROME ;
				}

				//--------------------------------------------------------------------
				// Specifies that the image will use VGA color.
				//--------------------------------------------------------------------

				void SetVGAColor ()
				{
					_flag |= LR_VGACOLOR ;
				}

				void resetFlags ()
				{
					_flag = 0 ;
				}

				//-----------------------------------------------------------
				// Sets the flag using the WINAPI flags
				//
				// Parameters:
				//
				// UINT flag -> The WINAPI flags.
				//-----------------------------------------------------------

				void SetFlag (UINT flag)
				{
					_flag = flag ;
				}

		protected:

			ImageLoader (const HINSTANCE hInstance = NULL)
				: _hInstance (hInstance),
				  _flag (0)
			{}

			HINSTANCE _hInstance ;
			UINT      _flag ;

		} ;

	}

#endif