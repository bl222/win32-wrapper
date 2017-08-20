//-----------------------------------------------------------------
// This file contains classes representing icon.
//-----------------------------------------------------------------

#if !defined (WINICON_H)

	#define WINICON_H
	#include "useunicode.h"
	#include <windows.h>
	#include "winunicodehelper.h"
	#include "winexception.h"
	#include "winimageloader.h"
	#include "winhandle.h"

	namespace Win
	{

		namespace Icon
		{
			//------------------------------------------------------------------
			// Win::Icon::Disposal is used to destroy a cursor  Used only internaly by winlib, not by users.
			//------------------------------------------------------------------

			struct Disposal
			{
				static void Dispose (HICON h)
				{
					::DestroyIcon (h) ;
				}
			} ;

			typedef Sys::Handle <HICON> Handle ; // Handle for an icon.
			typedef Sys::StrongHandle <Win::Icon::Handle, Win::Icon::Disposal> StrongHandle ;  // Strong handle owning the icon.

			//------------------------------------------------------------------
			// Win::Icon::Loader is used to load an icon custom made by
			// the user.
			//------------------------------------------------------------------

			class Loader : public Win::ImageLoader
			{
			public:

				HICON LoadResource (const int id, const int width, const int height) ;
				HICON LoadResource (const std::tstring  name, const int width, const int height) ;
				HICON LoadFile (const std::tstring  name, const int width, const int height) ;

				static HICON LoadResource (HINSTANCE hInstance, const int id, const int width, const int height, const UINT flags) ;
				static HICON LoadResource (HINSTANCE hInstance, const std::tstring  name, const int width, const int height, const UINT flags) ;
				static HICON LoadFile (const std::tstring  name, const int width, const int height, const UINT flags) ;

			protected:

				//------------------------------------------------------------------
				// Constructor.
				//------------------------------------------------------------------

				Loader (const HINSTANCE hInstance = NULL)
					: Win::ImageLoader (hInstance)
				{}
			} ;

			//------------------------------------------------------------------
			// Win::Icon::Loader is used to load an icon custom made by
			// the user.  The icon have standard "small" dimension.
			//------------------------------------------------------------------

			class SmallLoader : public Win::Icon::Loader
			{
			public:

				//------------------------------------------------------------------
				// Constructor.
				//------------------------------------------------------------------

				SmallLoader (const HINSTANCE hInstance = NULL)
					: Win::Icon::Loader (hInstance)
				{}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const int id -> Id of the icon.
				//------------------------------------------------------------------

				Win::Icon::StrongHandle LoadResource (const int id)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (id, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON))) ;
				}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the icon.
				//------------------------------------------------------------------

				Win::Icon::StrongHandle LoadResource (const std::tstring  name)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (name, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON))) ;
				}

				//------------------------------------------------------------------
				// Loads from a file.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the file.
				//------------------------------------------------------------------

				Win::Icon::StrongHandle LoadFile (const std::tstring  name)
				{
					return Win::Icon::StrongHandle (Loader::LoadFile (name, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON))) ;
				}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const int id -> Id of the icon.
				// const HINSTANCE hInstance -> Instance of the program
				// const UINT flag -> The options flag
				//------------------------------------------------------------------

				static Win::Icon::StrongHandle LoadResource (const HINSTANCE hInstance, const int id, const UINT flag)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (hInstance, id, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), flag)) ;
				}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the icon.
				// const HINSTANCE hInstance -> Instance of the program
				// const UINT flag -> The options flag
				//------------------------------------------------------------------

				static Win::Icon::StrongHandle LoadResource (const HINSTANCE hInstance, const std::tstring name, const UINT flag)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (hInstance, name, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), flag)) ;
				}

				//------------------------------------------------------------------
				// Loads from a file.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the file.
				// const UINT flag -> The options flag
				//------------------------------------------------------------------

				static Win::Icon::StrongHandle LoadFile (const std::tstring  name, const UINT flag)
				{
					return Win::Icon::StrongHandle (Loader::LoadFile (name, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), flag)) ;
				}

			} ;

			//------------------------------------------------------------------
			// Win::Icon::Loader is used to load an icon custom made by
			// the user.  The icon have standard "big" dimension.
			//------------------------------------------------------------------

			class BigLoader : public Win::Icon::Loader
			{
			public:

				//------------------------------------------------------------------
				// Constructor.
				//------------------------------------------------------------------

				BigLoader (const HINSTANCE hInstance = NULL)
					: Win::Icon::Loader (hInstance)
				{}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const int id -> Id of the icon.
				//------------------------------------------------------------------

				Win::Icon::StrongHandle LoadResource (const int id)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (id, ::GetSystemMetrics (SM_CXICON), ::GetSystemMetrics (SM_CYICON))) ;
				}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the icon.
				//------------------------------------------------------------------

				Win::Icon::StrongHandle LoadResource (const std::tstring  name)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (name, ::GetSystemMetrics (SM_CXICON), ::GetSystemMetrics (SM_CYICON))) ;
				}

				//------------------------------------------------------------------
				// Loads from a file.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the file.
				//------------------------------------------------------------------

				Win::Icon::StrongHandle LoadFile (const std::tstring  name)
				{
					return Win::Icon::StrongHandle (Loader::LoadFile (name, ::GetSystemMetrics (SM_CXICON), ::GetSystemMetrics (SM_CYICON))) ;
				}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const int id -> Id of the icon.
				// const HINSTANCE hInstance -> Instance of the program
				// const UINT flag -> The options flag
				//------------------------------------------------------------------

				static Win::Icon::StrongHandle LoadResource (const HINSTANCE hInstance, const int id, const UINT flag)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (hInstance, id, ::GetSystemMetrics (SM_CXICON), ::GetSystemMetrics (SM_CYICON), flag)) ;
				}

				//------------------------------------------------------------------
				// Loads from a resource.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the icon.
				// const HINSTANCE hInstance -> Instance of the program
				// const UINT flag -> The options flag
				//------------------------------------------------------------------

				static Win::Icon::StrongHandle LoadResource (const HINSTANCE hInstance, const std::tstring name, const UINT flag)
				{
					return Win::Icon::StrongHandle (Loader::LoadResource (hInstance, name, ::GetSystemMetrics (SM_CXICON), ::GetSystemMetrics (SM_CYICON), flag)) ;
				}

				//------------------------------------------------------------------
				// Loads from a file.
				//
				// Return value:  A StrongHandle representing the icon.
				//
				// Parameter
				//
				// const std::tstring  name -> Name of the file.
				// const UINT flag -> The options flag
				//------------------------------------------------------------------

				static Win::Icon::StrongHandle LoadFile (const std::tstring  name, const UINT flag)
				{
					return Win::Icon::StrongHandle (Loader::LoadFile (name, ::GetSystemMetrics (SM_CXICON), ::GetSystemMetrics (SM_CYICON), flag)) ;
				}
			} ;

			//------------------------------------------------------------------
			// Win::Icon::PredifinedLoader is use to load a predifined icon.
			//------------------------------------------------------------------

			class PredefinedLoader
			{
			public:

				PredefinedLoader ()
				{}

				//------------------------------------------------------------------
				// The following methods load differents predefined icons.  The
				// predifined icon must not be destroyed, so they are returned
				// as Handle and not StrongHandle.
				//------------------------------------------------------------------

				static Win::Icon::Handle LoadApplication () {return Load (IDI_APPLICATION) ;}
				static Win::Icon::Handle LoadHand		 () {return Load (IDI_HAND) ;}
				static Win::Icon::Handle LoadQuestion    () {return Load (IDI_QUESTION) ;}
				static Win::Icon::Handle LoadExclamation () {return Load (IDI_EXCLAMATION) ;}
				static Win::Icon::Handle LoadAsterisk    () {return Load (IDI_ASTERISK) ;}
				static Win::Icon::Handle LoadWinLogo     () {return Load (IDI_WINLOGO) ;}


			private:

				static HCURSOR Load (TCHAR * id) ;
			} ;
		}
	}

#endif

