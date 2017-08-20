#include "winedit.h"

//-------------------------------------------------------------------------
// Obtains the formating rectangle of the EditHandleHandle control.
//
// Return value: The formating rectangle.
//-------------------------------------------------------------------------

Win::Rect Win::EditHandle::GetRect () const
{
	Win::Rect rect ;

	SendMessage (EM_GETRECT, 0, 
	reinterpret_cast <LPARAM> (reinterpret_cast <LPRECT> (&rect))) ;

	return rect ;
}

//-------------------------------------------------------------------------
// Obtains the left and right margins of the edit control.
// 
// Parameters:
//
// int & left  -> Will contain the left margin.
// int & right -> Will contain the right margin.
//-------------------------------------------------------------------------

void Win::EditHandle::GetMargins (int & left, int & right) const
{
	int margin = SendMessage (EM_GETMARGINS, 0, 0) ;

	left  = LOWORD (margin) ;
	right = HIWORD (margin) ;
}

//-------------------------------------------------------------------------
// Obtains the character index of a line from it's line number.
//
// Return value:  The character index of the line.
//
// Parameters:
//
// const int charIndex -> The line number.
//-------------------------------------------------------------------------

int Win::EditHandle::GetLineIndex (const int line) const
{
	int index ;
	index =  SendMessage (EM_LINEINDEX, line, 0) ;

	if (index == -1)
		throw Win::Exception (TEXT("Error, the line specified does not exist.")) ;

	return index ;
}

//-------------------------------------------------------------------------
// Adds text at the end of the edit control.
// 
// Parameters:
//
// const std::tstring str -> Contains the text to be added at the end of the
//							edit control.
//-------------------------------------------------------------------------

void Win::EditHandle::Append (const std::tstring str)
{
	// Set the selection at the end of the edit control.
	int len = GetTextLenght () ;
	SetSelection (len, -1) ;

	// Replace the selection by the desired text.
	SendMessage (EM_REPLACESEL, 0, reinterpret_cast <LPARAM> (str.c_str ())) ;
}

//-------------------------------------------------------------------------
// Selects one line of a multiline edit control..
// 
// Parameters:
//
// const int lineNo -> number of the line to be selected.
//-------------------------------------------------------------------------

void Win::EditHandle::SelectLine (const int lineNo)
{
	// Find the starting and ending charcter index of the line.
	int lineStart = SendMessage (EM_LINEINDEX, lineNo) ;
	int lineLen   = SendMessage (EM_LINELENGTH, lineNo) ;

	// Select the line.
	SetSelection (lineStart, lineStart + lineLen) ;
}

//-------------------------------------------------------------------------
// Deletes all the text of the edit control.
//-------------------------------------------------------------------------

void Win::EditHandle::Clear ()
{
	SelectAll () ;
	SendMessage (WM_CLEAR, 0, 0) ;
}
