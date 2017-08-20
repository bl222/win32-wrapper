#include "winclipboard.h"
#include "wincanvas.h"

//------------------------------------------------------------
// Copy a string from to the clipboad.
//
// parameters:
// 
// Win::Base & win -> The window opening the clipboard.
// const std::tstring str -> The string being copied to the clipboard. 
//------------------------------------------------------------

void Win::Clipboard::TextClip::Copy (Win::Base & win, const std::tstring str)
{
	Win::Global::Handle handle = Win::Global::Creator::CreateClipboardHandle ((str.length () + 1) * sizeof (TCHAR)) ;
	TCHAR * ptr ;
	Win::Global::Lock lock (handle, reinterpret_cast <void **> (&ptr)) ;

	::lstrcpy (ptr, &str[0]) ;

	Win::Clipboard::Saver save (win) ;

	save.SetHandle (Win::Clipboard::Text, handle) ;

}

//------------------------------------------------------------
// Copy a string from to the clipboad.  The string becomes 
// empty.
//
// parameters:
// 
// Win::Base & win -> The window opening the clipboard.
// const std::tstring str -> The string being copied to the clipboard. 
//------------------------------------------------------------

void Win::Clipboard::TextClip::Cut (Win::Base & win, std::tstring & str)
{
	Copy (win, str) ;
	str = TEXT ("") ;
}

//------------------------------------------------------------
// Obtains a string from to the clipboad.
//
// Return value:  The string from the clipboard.
//
// parameters:
// 
// Win::Base & win -> The window opening the clipboard.
//------------------------------------------------------------

std::tstring Win::Clipboard::TextClip::Paste (Win::Base & win)
{
	Win::Global::Handle handle ;
	Win::Clipboard::Reader read (win);
	TCHAR * ptr ;
	std::tstring str ;

	handle = read.GetHandle (Win::Clipboard::Text) ;

	if (handle == NULL)
		throw Win::Exception (TEXT("Error, could no obtain a text from the clipboard")) ;

	Win::Global::Lock lock (handle, reinterpret_cast <void **> (&ptr)) ;

	str = ptr ;
	
	return ptr ;
}

void Win::Clipboard::DDBClip::Copy  (Win::Base & win, const Win::Bitmap::DDB::Handle ddb)
{
	Win::Bitmap::DDB::StrongHandle bit = Win::Bitmap::DDB::Creator::CreateCopy (ddb) ;

	Win::Clipboard::Saver save (win) ;

	save.SetDDBHandle (Win::Clipboard::DDB, bit.Release ()) ;
}


void Win::Clipboard::DDBClip::Cut   (Win::Base & win, Win::Bitmap::DDB::StrongHandle ddb)
{
	Copy (win, ddb) ;
}

Win::Bitmap::DDB::StrongHandle Win::Clipboard::DDBClip::Paste (Win::Base & win)
{
	Win::Bitmap::DDB::Handle ddbClip ;
	Win::Bitmap::DDB::StrongHandle ddb ;
	Win::Clipboard::Reader read (win);

	ddbClip = read.GetDDBHandle (Win::Clipboard::DDB) ;

	if (ddbClip == NULL)
		throw Win::Exception (TEXT("Error, could no obtain a ddb from the clipboard")) ;

	ddb = Win::Bitmap::DDB::Creator::CreateCopy (ddbClip) ;

	
	return ddb ;
}

void	Win::Clipboard::DIBSectionClip::Copy  (Win::Base & win, Win::Bitmap::DIBSection::Handle dib)
{
	HGLOBAL handle = dib.CopyToClipboard () ;

	Win::Clipboard::Saver save (win) ;

	save.SetHandle (Win::Clipboard::DIB, handle) ;

}

void	Win::Clipboard::DIBSectionClip::Cut   (Win::Base & win, Win::Bitmap::DIBSection::StrongHandle dib)
{
	Copy (win, dib) ;
} 


Win::Bitmap::DIBSection::StrongHandle Win::Clipboard::DIBSectionClip::Paste (Win::Base & win)
{
	Win::Global::Handle					  handle ;
	Win::Clipboard::Reader				  read (win);
	BYTE *                                pGlobal ;
	Win::Bitmap::DIBSection::StrongHandle dib ;

	handle = read.GetHandle (Win::Clipboard::DIB) ;

	if (handle == NULL)
		throw Win::Exception (TEXT("Error, could no obtain a DIBSection from the clipboard")) ;

	Win::Global::Lock lock (handle, (void **) &pGlobal) ;

	dib.PasteFromClipboard ((BITMAPINFO *) pGlobal) ;


	return dib ;
}
