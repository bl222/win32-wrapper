//------------------------------------------------------------
// This file contains classes working with the clipboard.
//------------------------------------------------------------

#if !defined (WINCLIPBOARD_H)

	#define WINCLIPBOARD_H

	#include "useunicode.h"
	#include "win.h"
	#include "winglobalhandle.h"

	namespace Win
	{
		namespace Clipboard
		{
			enum Format {Text = CF_TEXT, DDB = CF_BITMAP, DIB = CF_DIB} ;

			//------------------------------------------------------------
			// Win::Clipboard::Reader is used to open the clipboard for
			// reading.  When an object is created, the clipboard is 
			// opened.  When the object is destroyed, the clipboard is
			// close.
			//------------------------------------------------------------

			class Reader
			{
			public:

				//------------------------------------------------------------
				// Constructor.  Opens the clipboard.
				//
				// Parameters:
				//
				// const Win::Base hwnd -> Handle of the window opening the 
				//					  clipboard.
				//------------------------------------------------------------

				Reader (const Win::Base & hwnd)
				{
					if (::OpenClipboard (hwnd) == 0)
						throw Win::Exception (TEXT("Error, could not open the clipboard.")) ;
				}

				//------------------------------------------------------------
				// Destructor.  Close the clipboard.
				//------------------------------------------------------------

				~Reader ()
				{
					::CloseClipboard () ;
				}

				//------------------------------------------------------------
				// Obtains a global handle containing the data of the clipboard.
				//
				// Return value:  A global handle containing the data of the
				//				  clipboard.
				//
				// Parameters:
				//
				// const Win::Clipboard::Format format -> Format of the desired data.
				//------------------------------------------------------------

				Win::Global::Handle GetHandle (const Win::Clipboard::Format format) const 
				{
					return ::GetClipboardData (format) ;
				}

				//------------------------------------------------------------
				// Obtains a bitmap handle containing the data of the clipboard.
				//
				// Return value:  A bitmap handle containing the data of the
				//				  clipboard.
				//
				// Parameters:
				//
				// const Win::Clipboard::Format format -> Format of the desired data.
				//------------------------------------------------------------

				Win::Bitmap::DDB::Handle GetDDBHandle (const Win::Clipboard::Format format) const 
				{
					return Win::Bitmap::DDB::Handle ((HBITMAP)::GetClipboardData (format)) ;
				}

			} ;

			//------------------------------------------------------------
			// Win::Clipboard::Saver is used to open the clipboard for
			// saving data.  When an object is created, the clipboard is 
			// opened.  When the object is destroyed, the clipboard is
			// close.
			//------------------------------------------------------------

			class Saver
			{
			public:

				//------------------------------------------------------------
				// Constructor.  Opens the clipboard and empty it.
				//
				// Parameters:
				//
				// const Win::Base hwnd -> Handle of the window opening the 
				//						  clipboard.
				//------------------------------------------------------------

				Saver (const Win::Base hwnd)
				{
					if (::OpenClipboard (hwnd) == 0)
						throw Win::Exception (TEXT("Error, could not open the clipboard.")) ;
					if (::EmptyClipboard () == 0)
						throw Win::Exception (TEXT("Error, could not empty the clipboard.")) ;
				}

				//------------------------------------------------------------
				// Used to set some data in the clipboard
				//
				// Parameters:
				//
				// const Win::Clipboard::Format format     -> Format of the data.
				// const Win::Global::Handle hGlobal -> Global handle containing the data.
				//------------------------------------------------------------

				void SetHandle (const Win::Clipboard::Format format, const Win::Global::Handle hGlobal) const
				{
					if (::SetClipboardData (format, hGlobal) == 0)
						throw Win::Exception (TEXT("Error, could not set the clipboard data.")) ;
				}

				//------------------------------------------------------------
				// Used to set a DDB in the clipboard
				//
				// Parameters:
				//
				// const Win::Clipboard::Format format     -> Format of the data.
				// Win::Bitmap::DDB::Handle -> Handle of the DDB to be set to the clipboard.
				//------------------------------------------------------------

				void SetDDBHandle (const Win::Clipboard::Format format, const Win::Bitmap::DDB::Handle ddb) const
				{
					if (::SetClipboardData (format, ddb) == 0)
						throw Win::Exception (TEXT("Error, could not set the clipboard data.")) ;
				}

				//------------------------------------------------------------
				// Destructor.  Close the clipboard
				//------------------------------------------------------------

				~Saver ()
				{
					::CloseClipboard () ;
				}

			} ;

			//------------------------------------------------------------
			// Determines wheter the requested format is available on the
			// clipboard or not.
			//
			// Return value:  true if the format is available, else false.
			//------------------------------------------------------------

			inline bool IsFormatAvailable  (const Win::Clipboard::Format format)
			{
				::IsClipboardFormatAvailable (format) ;
			}

			//------------------------------------------------------------
			// Win::Clipboard::TextClip is used to send/retrieve text
			// to/from the clipboard. 
			//------------------------------------------------------------

			class TextClip
			{ 
			public:

				static void		   Copy  (Win::Base & win, const std::tstring str) ;
				static void		   Cut   (Win::Base & win, std::tstring & str) ;
				static std::tstring Paste (Win::Base & win) ;
			} ;

			//------------------------------------------------------------
			// Win::Clipboard::DDBClip is used to send/retrieve a DDB
			// to/from the clipboard. 
			//------------------------------------------------------------

			class DDBClip
			{ 
			public:

				static void						Copy  (Win::Base & win, const Win::Bitmap::DDB::Handle ddb) ;
				static void						Cut   (Win::Base & win, Win::Bitmap::DDB::StrongHandle ddb) ;
				static Win::Bitmap::DDB::StrongHandle Paste (Win::Base & win) ;

			private:

			} ;

			//------------------------------------------------------------
			// Win::Clipboard::DIBSectionClip is used to send/retrieve a DIBSection
			// to/from the clipboard. 
			//------------------------------------------------------------

			class DIBSectionClip
			{ 
			public:

				static void						Copy  (Win::Base & win, Win::Bitmap::DIBSection::Handle dib) ;
				static void						Cut   (Win::Base & win, Win::Bitmap::DIBSection::StrongHandle dib) ;
				static Win::Bitmap::DIBSection::StrongHandle Paste (Win::Base & win) ;

			} ;

		}
	}

#endif