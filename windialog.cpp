#include "windialog.h"
#include <tchar.h>
//--------------------------------------------------------------------
// This is the predefined modal dialog procedure that is used with every
// created dialog.  This procedure is hidden thanks to the 
// Win::Dialog::ModalController.
//--------------------------------------------------------------------

BOOL CALLBACK Win::Dialog::ModalProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	// Obtains a pointer on the controller.of the window.
	Win::Dialog::Controller * ctrl = GetLong <Win::Dialog::Controller *> (hDlg) ;

	switch (message)
	{

	// This message is used to do some innitialisation so the Win::Dialog::ModalController 
	// object works properlly.
	case WM_INITDIALOG:
		{
			// Gets a pointer on the controller.
			ctrl = reinterpret_cast <Win::Dialog::Controller *> (lParam) ;

			// Places the controller back in the window.
			SetLong <Win::Dialog::Controller *> (hDlg, ctrl) ;

			// Initialize the Win::dow::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle object inside the Win::Dialog::ModalController object.
			ctrl->SetWindow (hDlg) ;
				
			if (ctrl->OnInitDialog (hDlg))
				return TRUE ;
		}
		break ;

	//---------------------------------------------------------------
	// Almost all the messages work the same.  If the corresponding 
	// methods in Win::Dialog::ModalController returns true, the dialog
	// procedure return TRUE, else it's return FALSE.
	//---------------------------------------------------------------

	case WM_COMMAND:
			if (lParam == 0)  //Menu or accelerator
			{
				if (ctrl && ctrl->OnCommand(LOWORD (wParam), HIWORD (wParam) == 1)) 
					return 0 ;
			}
			else //control
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND>(lParam)) ;

				if (ctrl && ctrl->OnControl (hwnd, LOWORD (wParam), HIWORD (wParam)))
					return 0 ;
			}  
		break ;

	case WM_NOTIFY:
		if (ctrl && ctrl->OnNotify (hDlg, wParam, reinterpret_cast <NMHDR *>(lParam)))
			return TRUE ;     
		break ;

	case WM_VSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(ctrl && ctrl->OnVerticalScroll (HIWORD (wParam), LOWORD (wParam)))
					return TRUE ;
			}
			else // Control scrolbar.
			{
				if (ctrl && ctrl->OnControlVerticalScroll (reinterpret_cast <HWND> (lParam),
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return TRUE ;
			}
		}
		break ;

	}

	return FALSE;
}

//--------------------------------------------------------------------
// This is the predefined modeless dialog procedure that is used with 
// every created dialog.  This procedure is hidden thanks to the 
// Win::Dialog::ModelessController.
//--------------------------------------------------------------------

BOOL CALLBACK Win::Dialog::ModelessProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Obtains a pointer on the controller.of the window.
	Win::Dialog::Controller * ctrl = Win::GetLong <Win::Dialog::Controller *> (hDlg) ;

	try
	{
		switch (message)
		{

		// This message is used to do some innitialisation so the Win::Dialog::ModelessController 
		// object works properlly.
		case WM_INITDIALOG:
			{
				// Gets a pointer on the controller.
				StrongPointer <Win::Dialog::Controller> * ap 
					= reinterpret_cast <StrongPointer <Win::Dialog::Controller> *> (lParam) ;
					;
				ctrl = ap->Release () ;
				
				// Initialize the Win::dow::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle::Handle object inside the Win::Dialog::ModelesslController object.
				ctrl->SetWindow (hDlg) ;

				// Places the controller back in the window.
				Win::SetLong <Win::Dialog::Controller *> (hDlg, ctrl) ;
									
				if (ctrl->OnInitDialog (hDlg))
						return TRUE ;

			}
			break;

		//---------------------------------------------------------------
		// Almost all the messages work the same.  If the corresponding 
		// methods in Win::Dialog::ModelessController returns true, the dialog
		// procedure return TRUE, else it's return FALSE.
		//---------------------------------------------------------------

		case WM_COMMAND:
			if (lParam == 0)  //Menu or accelerator
			{
				if (ctrl && ctrl->OnCommand(LOWORD (wParam), HIWORD (wParam) == 1)) 
					return 0 ;
			}
			else //control
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND>(lParam)) ;

				if (ctrl && ctrl->OnControl (hwnd, LOWORD (wParam), HIWORD (wParam)))
					return 0 ;
			}   
			break ;

		// Destroy the controller.
		case WM_DESTROY:
			delete ctrl ;
			break ;

		case WM_NOTIFY:
			if (ctrl && ctrl->OnNotify (hDlg, wParam, reinterpret_cast <NMHDR *> (lParam)))
				return TRUE ;  
			break ;

		case WM_VSCROLL:
			{
				if (lParam == 0) // Not a control scrolbar.
				{
					if(ctrl && ctrl->OnVerticalScroll (HIWORD (wParam), LOWORD (wParam)))
						return TRUE ;
				}
				else // Control scrolbar.
				{
					if (ctrl && ctrl->OnControlVerticalScroll (reinterpret_cast <HWND> (lParam),
						::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
						return TRUE ;
				}
			}
			break ;
		}
	}
	catch (Win::Exception & e) // An error occured.
	{
		e.Show () ;
	}
	return FALSE ;
}

//----------------------------------------------------------------------
// Constructor.  Innitialize the data of the OPENFILENAME structure.
//----------------------------------------------------------------------

Win::Dialog::Modal::OpenFileNameData::OpenFileNameData ()
{
	Clear () ;
	lStructSize    = sizeof (OPENFILENAME) ;
	_fileName [0]  = '\0' ;
	_fileTitle [0] = '\0' ;
	lpstrFile      = _fileName ;
	lpstrFileTitle = _fileTitle ;
	nMaxFile       = MAX_PATH ;
	nMaxFileTitle  = MAX_PATH ;
}

//----------------------------------------------------------------------
// Constructor.  Innitialize the data of the CHOOSEFONT structure.
//----------------------------------------------------------------------

Win::Dialog::Modal::ChooseFontData::ChooseFontData ()
{
	Clear () ;
	lStructSize = sizeof (CHOOSEFONT) ;
	lpLogFont = reinterpret_cast <LOGFONT*> (&_font) ;
}

//----------------------------------------------------------------------
// Constructor.  Innitialize the data of the CHOOSEFONT structure.
//----------------------------------------------------------------------

Win::Dialog::Modal::ChooseColorData::ChooseColorData ()
{
	Clear () ;
	lStructSize = sizeof(CHOOSECOLOR) ;
	lpCustColors = &_defColor [0] ;
}

//----------------------------------------------------------------------
// Obtains the user made custom color in a Win::Color array.
//
// Parameters:
//
// Win::Color defColor [] -> Will contain the custom colors
// const int count        -> Size of the defColor array. Max 16.
//----------------------------------------------------------------------

void Win::Dialog::Modal::ChooseColorData::GetCustomColor (Win::Color defColor [], const int count) const
{
	for (int i = 0 ; i < count && i < 16 ; i++)
		defColor [i].SetColorRef (_defColor [i]) ;
}

//----------------------------------------------------------------------
// Constructor.  Innitialize the data of the FINDREPLACE structure.
//----------------------------------------------------------------------

Win::Dialog::Modeless::FindReplaceData::FindReplaceData ()
{
	Clear () ;
	lStructSize = sizeof (FINDREPLACE) ;
		
	wFindWhatLen = 256 ;
	_find.reserve (256  + 1) ;
	_find.resize (256) ;
	lpstrFindWhat = &_find [0] ;

	wReplaceWithLen = 256 ;
	_replace.reserve (256  + 1) ;
	_replace.resize (256) ;
	lpstrReplaceWith = &_replace [0] ;
				
}

//----------------------------------------------------------------------
// Changes the max size of the string to be found or replaced.
//
// Parameters: 
// 
// const WORD len -> New max size of the string.
//----------------------------------------------------------------------

void Win::Dialog::Modeless::FindReplaceData::SetFindWhatLen (const WORD len)
{
	lpstrFindWhat = 0;
	_find.reserve (len  + 1);
	_find.resize (len);
	lpstrFindWhat = &_find [0];
}

//----------------------------------------------------------------------
// Changes the max size of the replacement string.
//
// Parameters: 
// 
// const WORD len -> New max size of the string.
//----------------------------------------------------------------------

void Win::Dialog::Modeless::FindReplaceData::SetReplaceWidthLen (const WORD len)
{
	lpstrReplaceWith = 0;
	_replace.reserve (len  + 1);
	_replace.resize (len);
	lpstrReplaceWith = &_replace [0];
}

//--------------------------------------------------------------------
// Changes all the data of the font that will be created.
//--------------------------------------------------------------------

void Win::Dialog::Modal::FontInfo::SetAllData (const std::tstring face, const Win::Font::CharSet charSet, const int height, const int width, const int escapement, const int orientation, 
	     const Win::Font::Weight weight, const bool italic, const bool underline, const bool strikeOut, 
	     const Win::Font::OutPrecis outputPrescision, const Win::Font::ClipPrecis clipPrescision, const Win::Font::Quality quality, 
	     const Win::Font::Pitch pitch, const Win::Font::Family family) 
{
	_struct.lfWidth         = width ;
	_struct.lfHeight        = height ;
	_struct.lfOrientation   = orientation ;
	_struct.lfQuality       = quality ;
	_struct.lfClipPrecision = clipPrescision ;
	_struct.lfOutPrecision  = outputPrescision ;
	_struct.lfItalic        = italic ;
	_struct.lfUnderline     = underline ;
	_struct.lfStrikeOut     = strikeOut ;
	_struct.lfEscapement    = escapement ;
	_struct.lfWeight        = weight ;
	_struct.lfCharSet       = charSet ;

	SetFamily      (family) ;
	SetPitch       (pitch) ;
	_tcscpy (_struct.lfFaceName, face.c_str ()) ;
}

//-----------------------------------------------------------------------------
//Creates a modelfes dialog.
//
// Parameters:
//
// const Win::dow::Handle & win                      -> Window owning the dialog box.
// const int id                              -> Id of the dialog resource.
// std::auto_ptr <ModelessController> & ctrl -> Points on the Controller of the 
//												dialog box.
//-----------------------------------------------------------------------------

Win::Dialog::Modeless::Handle Win::Dialog::Modeless::Creator::Create (StrongPointer <Win::Dialog::Modeless::Controller> & ctrl)
{
	Win::Dialog::Modeless::Handle dlg ;

	dlg = ::CreateDialogParam ( _parent.GetInstance (),
								 MAKEINTRESOURCE (_id),
								 _parent,
								 static_cast <DLGPROC> (Win::Dialog::ModelessProc),
								 reinterpret_cast <LPARAM> (&ctrl)) ;

	if (!dlg) // Make sure the dialog was created.
		throw Win::Exception (TEXT("Internal error: Cannot create modeless dialog.")) ;

	return dlg ;
}

//-----------------------------------------------------------------------------
//Creates a find modelfes dialog.
//
// Parameters:
//
// Win::Dialog::Modeless::FindReplaceData & data -> Data used to create the dialog
//-----------------------------------------------------------------------------

Win::Dialog::Modeless::Handle Win::Dialog::Modeless::FindCreator::Create (Win::Dialog::Modeless::FindReplaceData & data)
{
	Win::Dialog::Modeless::Handle dlg ;

	dlg = ::FindText (reinterpret_cast <LPFINDREPLACE> (&data)) ;

	if (!dlg) // Make sure the dialog was created.
		throw Win::Exception (TEXT("Internal error: Cannot create a find modeless dialog.")) ;

	return dlg ;
}

//-----------------------------------------------------------------------------
//Creates a find-replace modelfes dialog.
//
// Parameters:
//
// Win::Dialog::Modeless::FindReplaceData & data -> Data used to create the dialog
//-----------------------------------------------------------------------------

Win::Dialog::Modeless::Handle Win::Dialog::Modeless::ReplaceCreator::Create (Win::Dialog::Modeless::FindReplaceData & data)
{
	Win::Dialog::Modeless::Handle dlg ;

	dlg = ::ReplaceText (reinterpret_cast <LPFINDREPLACE> (&data)) ;

	if (!dlg) // Make sure the dialog was created.
		throw Win::Exception (TEXT("Internal error: Cannot create a find modeless dialog.")) ;

	return dlg ;
}