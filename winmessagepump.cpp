#include "winmessagepump.h"

#include "winexception.h"

//------------------------------------------------------------
// Remove a dialog handle from the list.  Use this method when 
// a modeless dialog is being destroy.
//
// Parameters:  
//
// const Win::dow::Handle dlg -> Handle of the dialog to be removed.
//------------------------------------------------------------

void Win::MessagePump::RemoveDialogFilter (const Win::dow::Handle hDlg)
{
	_dlgList.remove (hDlg) ;
}

//------------------------------------------------------------
// A message loop implemented with the ::GetMessage function.
//
// Return value:  0 if normal termination.
//------------------------------------------------------------

int Win::MessagePump::Pump () 
{
    MSG  message ;
	int status ;


	//Wait for a message.
    while ((status = ::GetMessage (&message, NULL, 0, 0 )) != 0)
    {
		//Error.
		if (status < 0)
			throw Win::Exception (TEXT("Error in the Windows message loop")) ;

		// Checks if the message if for a modeless dialog.
		DlgIter it ;
		for (it = _dlgList.begin () ; it != _dlgList.end () ; ++it)
		{
			if (*it == NULL || ::IsDialogMessage (*it, &message))
				break ;
		}

		if (it == _dlgList.end ())  // If the message is not for a modeless dialog.
		{
			// Check for accelerator table.
			if (!_hAccel || !::TranslateAccelerator (_winTop, _hAccel, &message))
			{
				::TranslateMessage (&message) ;
				::DispatchMessage (&message) ;
			}
		}
    }

    return message.wParam ;
}

//------------------------------------------------------------
// A message loop implemented with the ::GetMessage function.
// Used for MDI application.
//
// Return value:  0 if normal termination.
//------------------------------------------------------------

int Win::MessagePump::MDIPump () 
{
    MSG  message ;
	int status ;


	//Wait for a message.
    while ((status = ::GetMessage (&message, NULL, 0, 0 )) != 0)
    {
		//Error.
		if (status < 0)
			throw Win::Exception (TEXT("Error in the Windows message loop")) ;

		// Checks if the message if for a modeless dialog.
		DlgIter it ;
		for (it = _dlgList.begin () ; it != _dlgList.end () ; ++it)
		{
			if (*it == NULL || ::IsDialogMessage (*it, &message))
				break ;
		}

		if (it == _dlgList.end ())  // If the message is not for a modeless dialog.
		{
			// Check for accelerator table.
			if (!_hAccel || (!::TranslateMDISysAccel (_mdiClient, &message) && !::TranslateAccelerator (_winTop, _hAccel, &message)))
			{
				::TranslateMessage (&message) ;
				::DispatchMessage (&message) ;
			}
		}
    }

    return message.wParam ;
}

//------------------------------------------------------------
// A message loop implemented with the ::PeekMessage function.
//------------------------------------------------------------

bool Win::MessagePump::PumpPeek ()
{
    MSG  message ;
	int status ;

	// Peek for a message.
    while ((status = ::PeekMessage (&message, NULL, 0, 0, PM_REMOVE)) != 0)
    {
		// Error.
		if (status < 0)
			throw Win::Exception (TEXT("Error in the Windows peek message loop")) ;

		// Checks if the message if for a modeless dialog.
		DlgIter it ;
		for (it = _dlgList.begin () ; it != _dlgList.end () ; ++it)
		{
			if (*it == NULL || ::IsDialogMessage (*it, &message))
				break ;
		}

		if (it == _dlgList.end ()) // If the message is not for a modeless dialog.
		{
			if (message.message == WM_QUIT)
				return false ;
			// Check for accelerator table.
			if (!_hAccel || !::TranslateAccelerator (_winTop, _hAccel, &message))
			{
				::TranslateMessage (&message) ;
				::DispatchMessage (&message) ;
			}
		}
    }

	return true ;
}
