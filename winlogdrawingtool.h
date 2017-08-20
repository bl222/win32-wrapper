//---------------------------------------------------------------------
// This file contains classes encapsulating WinAPI structure 
// used to create drawing tool like pen, brush, font, etc.  These 
// classes could had been define in the windrawingtool.h file but
// that file was very big so it was divided in 2.
//---------------------------------------------------------------------

#if !defined (WINLOGDRAWINGTOOL_H)

	#define WINLOGDRAWINGTOOL_H

	#include "useunicode.h"
	

	namespace Win
	{
		namespace ExtendedPen 
		{ 
			class Data ;
			class Creator ;
		}

		namespace Bitmap
		{
			namespace DDB
			{
				class Handle ;
			}
		}

		namespace Brush
		{



			namespace Solid
			{

			}
		

			namespace Hatch
			{


			}

			namespace Pattern
			{

			}
		}

		namespace Pen
		{

		}


		namespace ExtendedPen
		{


			namespace Color
			{


			}
		}

		namespace Font
		{

		}



		namespace Bitmap
		{


		}

		namespace Palette
		{


		}




	}

#endif
