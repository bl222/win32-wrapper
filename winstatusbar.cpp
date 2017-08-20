#include "winstatusbar.h"

//-------------------------------------------------------------------------
// Obtain the width of the vetical border, horizontal border and border 
// between rectangle.
//
// Parameters:
//
// int  & vertWidth -> Will contain the vertical borders width.
// int  & horzWidth -> Will contain the horizontal borders width.
// int  & betweenWidth -> Will contain the vertical borders width.
//-------------------------------------------------------------------------

void Win::StatusBarHandle::GetBordersWitdh (int  & vertWidth, int & horzWidth, int & betweenWidth) const
{
	int tab [3] ;

	if (SendMessage (SB_GETBORDERS, 0, reinterpret_cast <LPARAM> (tab)) == FALSE)
		throw Win::Exception (TEXT("Error, could not get borders width of the status bar")) ;

	horzWidth    = tab [0] ;
	vertWidth    = tab [1] ;
	betweenWidth = tab [2] ;
}

//-------------------------------------------------------------------------
// Changes the width of the vetical border, horizontal border and border 
// between rectangle.
//
// Parameters:
//
// int  vertWidth    -> The new vertical borders width.
// int  horzWidth    -> The new horizontal borders width.
// int  betweenWidth -> The new vertical borders width.
//-------------------------------------------------------------------------

void Win::StatusBarHandle::SetBordersWitdh (const int vertWidth, const int  horzWidth, const int betweenWidth) const
{
/*	int tab [3] ;

	tab [0] = vertWidth ;
	tab [1] = horzWidth ;
	tab [2] = betweenWidth ;

	if (SendMessage (SB_SETBORDERS, 0, reinterpret_cast <LPARAM> (tab)) == FALSE)
		throw Win::Exception (TEXT("Error, could not get borders width of the status bar")) ;*/

}

//-------------------------------------------------------------------------
// Obtains the drawing rectangle of the status bar
//
// Return value A Win::Rect objet that will contain the coordinates of the drawing rectangle
//
// Parameters:
// const long index -> The index of the desired part
//-------------------------------------------------------------------------

Win::Rect Win::StatusBarHandle::GetRect (const long index) const
{
	Win::Rect rect ;

	if (SendMessage (SB_GETRECT, index, reinterpret_cast <WPARAM> (reinterpret_cast <LPRECT> (&rect))) == FALSE)
		throw Win::Exception (TEXT("Error, could not get the rectangle of the status bar")) ;

	return rect ;
}

//-------------------------------------------------------------------------
// Return the text of a part on the status bar
//
// Return value:  The text.
//
// Parameters:
//
// const long index -> Index of the desired part.
//-------------------------------------------------------------------------

std::tstring Win::StatusBarHandle::GetText (const long index) const 
{
	int len = GetTextLength (index);
	std::tstring str;

	// Copy the caption in str.
	if (len > 0)
	{
		str.reserve (len + 1);
		str.resize (len);
		SendMessage (SB_GETTEXT, index, reinterpret_cast <LPARAM> (&str [0]));
	}
				
	return str;
}

//-------------------------------------------------------------------------
// Return the tooltip text of a part on the status bar
//
// Return value:  The tooltip text.
//
// Parameters:
//
// const long index   -> Index of the desired part.
// const short nbChar -> Maximum size of the string receiving the tooltip
//-------------------------------------------------------------------------

std::tstring Win::StatusBarHandle::GetToolTipText (const short index, const short nbChar) const
{
	std::tstring str ;
	// Copy the tooltip in str.
	if (nbChar > 0)
	{
		str.reserve (nbChar + 1);
		str.resize (nbChar);
		SendMessage (SB_GETTIPTEXT, MAKEWPARAM (index, nbChar), reinterpret_cast <LPARAM> (&str [0]));
	}
				
	return str;
}