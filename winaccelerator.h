#if !defined (WINACCELERATOR_H)
	#include "useunicode.h"
	#include "winunicodehelper.h"	
	#include "winhandle.h"

	#define WINACCELERATOR_H

	namespace Win
	{

		namespace Accelerator
		{
			class Handle : public Sys::Handle <HACCEL>
			{
			public:
				Handle (const HACCEL hAccel = NULL)
					:  Sys::Handle <HACCEL> (hAccel)
				{} 
			} ;

			class Loader 
			{
			public:

				//--------------------------------------------------------------------
				// Constructor
				//
				// Parameters:
				//
				// const HINSTANCE hInstance -> The instance of the program.
				//--------------------------------------------------------------------

				Loader (const HINSTANCE hInstance = NULL)
				{
					_hInstance = hInstance  ;
				}

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

				Win::Accelerator::Handle LoadResource (const int id) ;
				Win::Accelerator::Handle LoadResource (const std::tstring  name) ;

				static Win::Accelerator::Handle LoadResource (HINSTANCE hInstance, const int id) ;
				static Win::Accelerator::Handle LoadResource (HINSTANCE hInstance, const std::tstring  name) ;

			private:

				HINSTANCE _hInstance ;
			} ;
		}

	}
#endif