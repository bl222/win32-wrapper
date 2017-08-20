#include "wincaret.h"

//----------------------------------------------------------------
// Creates the caret, sets it's position and then shows it.
//
// Parameters:
//
// const int width		 -> Width of the caret.
// const int height	  	 -> Height of the caret.
// const HBITMAP bmp	 -> Bitmap determining the caret shape. (Can be 0).
// const int x			 -> X coordinate of the position of the caret.
// const int y			 -> Y coordinate of the position of the caret.
//----------------------------------------------------------------

void Win::Caret::Create (const int width, const int height, const Win::Bitmap::DDB::Handle bmp, const int x, const int y)
{
	if (!::CreateCaret (_hwnd, bmp, width, height)) // Makes sure the caret was created.
		throw Win::Exception (TEXT("he caret could not be created")) ;

	if (!::SetCaretPos (x, y)) // Makes sure the position of the caret was set.
		throw Win::Exception (TEXT("The position on the caret could not be set during it's creation")) ;

	if (!::ShowCaret (_hwnd)) // Makes sure the caret was shown.
		throw (TEXT("The caret could not be shown during it's creation")) ;
}
//----------------------------------------------------------------
// Destructor. Hides the caret and then destroys it.
//----------------------------------------------------------------

void Win::Caret::Destroy ()
{
	if (!::HideCaret (_hwnd))
		throw Win::Exception (TEXT("Error, could not hide the caret.")) ;
	
	if (!::DestroyCaret ())
		throw Win::Exception (TEXT("Error, could not destroy the caret")) ;
}

//----------------------------------------------------------------
// Obtains the position of the caret
//
// Return value: The position of the carret.
//----------------------------------------------------------------

Win::Point Win::Caret::GetPosition () const 
{
	Win::Point point ;

	if (::GetCaretPos (reinterpret_cast <LPPOINT> (&point)) == 0)
		throw Win::Exception (TEXT("Error, could not get the caret position!"));

	return point ;
}

//----------------------------------------------------------------
// Obtains the position of the caret
//
// Return value: The position of the carret.
//----------------------------------------------------------------

void Win::Caret::GetPosition (int x, int y) const 
{
	Win::Point point ;

	if (::GetCaretPos (reinterpret_cast <LPPOINT> (&point)) == 0)
		throw Win::Exception (TEXT("Error, could not get the caret position!"));

	x = point.GetX () ;
	y = point.GetY () ;
}