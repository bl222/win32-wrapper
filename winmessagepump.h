//-----------------------------------------------------
// This file contains a single class: Win::MessagePump
//-----------------------------------------------------

#if !defined (WINMESSAGEPUMP_H)

	#define WINMESSAGEPUMP_H
	#include "useunicode.h"
	#include "win.h"
	#include "winaccelerator.h"
	#include <list>

	namespace Win
	{
		//------------------------------------------------------------
		// Win::MessagePump implements a message loop.  The message
		// loop dispatch messages to the window procedure.
		//------------------------------------------------------------

		class MessagePump
		{
			typedef std::list<HWND>::iterator DlgIter;
		public:

			//------------------------------------------------------------
			// Constructor.  Simply set the data members to 0.
			//------------------------------------------------------------

			MessagePump ()
				: _hAccel    (NULL),
				  _winTop    (NULL),
				  _mdiClient (NULL)
			{}

			//------------------------------------------------------------
			// When a program uses keyboard acceleration, the message loop
			// needs to have access to the handle of the accelerator table
			// and the handle of the top window.  This methods is used for
			// this purpose.
			//
			// Parameters:  
			//
			// const HWND hwndTop  -> Handle of the top window.
			// const HACCEL hAccel -> Handle of the accelerator table.
			//------------------------------------------------------------

			void SetKbdAccelerator (const Win::Base hwndTop, const Win::Accelerator::Handle hAccel) 
			{
				_winTop = hwndTop ;
				_hAccel = hAccel ;
			}

			//------------------------------------------------------------
			// When a MDI application uses keyboard acceleration, the message loop
			// needs to have access to the handle of the MDI client window.
			// this function allows this.
			//
			// Parameters:  
			//
			// const HWND hwndTop  -> Handle of the top window.
			// const HACCEL hAccel -> Handle of the accelerator table.
			//------------------------------------------------------------

			void SetMDIClient (const Win::Base mdiClient)
			{				
				_mdiClient = mdiClient ;
			}

			//------------------------------------------------------------
			// When a modeless dialog is being displayed, the message loop
			// must have access to the handle of the dialog.  This function
			// add the handle of a dialog to a list of dialog handle. Use 
			// this function when a modeless dialog has being created.
			//
			// Parameters:  
			//
			// const HWND dlg -> Handle of the dialog.
			//------------------------------------------------------------

			void AddDialogFilter (const Win::dow::Handle hDlg) 
			{ 
				_dlgList.push_back (hDlg) ; 
			}

			void RemoveDialogFilter (const Win::dow::Handle hDlg) ; // Remove dialog handle.
			int Pump () ; //GetMessage.
			int MDIPump () ; //GetMessage. for MDI app.
			bool PumpPeek () ; // Peek message.

		private:
			std::list<HWND> _dlgList ; // List of dialog handle.
			HACCEL	        _hAccel ;  // Handle of the keyboard accelerators
			HWND	        _winTop ;  // Handle of the top window.
			HWND			_mdiClient ; // Handle of the MDI client used for MDI application.
		} ;
	}

#endif