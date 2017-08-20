#include <memory>
#include "wndproc.h"
#include "wincontroller.h"
#include "winkeyboard.h"
#include "winmouse.h"
#include "winctrleventhandlers.h"

//--------------------------------------------------------------------
// This is the predefined window procedure that is used with every
// created window.  This procedure is hidden thanks to the 
// Win::Controller.
//--------------------------------------------------------------------

LRESULT CALLBACK Win::Proc ( HWND hwnd, UINT msg, WPARAM wParam, 
					   LPARAM lParam )
{

	// Obtains a pointer on the controller.of the window.
	Win::dow::Controller * pCtr = GetLong <Win::dow::Controller *> (hwnd) ;

	switch (msg)
	{

	// This message is used to do some innitialisation so the Win::Controller 
	// object works properlly.
	case WM_NCCREATE:
		{
			// Creates a Win::CreationData pointer on the CREATESTRUCT passed
			// in the lParam.
			Win::CreationData const * pData =  
				reinterpret_cast <CreationData const *> (lParam) ;

			StrongPointer <Win::dow::Controller> * ap 
				= reinterpret_cast <StrongPointer<Win::dow::Controller> *> (pData->GetCreationData ()) ;

			pCtr = ap->Release () ;

			// Initialize the Win::dow::Handle object inside the Win::Controller object.
			pCtr->SetWindowHandle (hwnd) ;

			// Places the controller back in the window.
			SetLong <Win::dow::Controller *> (hwnd, pCtr) ;

			break ;

		}

	//---------------------------------------------------------------
	// Almost all the messages work the same.  If the corresponding 
	// methods in Win::Controller returns true, the window
	// procedure return 0.  Else, the DefWindowProc is called for
	// default behavior.
	//---------------------------------------------------------------

	case WM_CREATE:
		{
			if (pCtr->OnCreate (reinterpret_cast <CreationData const *> (lParam)))
				return 0 ;
		}
		break ;

	case WM_PAINT:
		{
			if(pCtr->OnPaint ())
				return 0 ;
		}
		break ;

	case WM_ACTIVATE:
		{
			ActivateAction aa(LOWORD (wParam)) ;

			Win::dow::Handle hwndPrev (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnActivate (aa, HIWORD (wParam) != FALSE, hwndPrev))
				return 0 ;
		}
		break ;
		
	case WM_CANCELMODE:
		{
			if (pCtr->OnCancelMode ())
				return 0 ;
		}
		break ;

	case WM_CAPTURECHANGED:
		{
			Win::dow::Handle hwndNewCapture (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnCaptureChange (hwndNewCapture))
				return 0 ;
		}
		break ;

	case WM_ENABLE:
		{
			if(pCtr->OnEnable (wParam == TRUE))
				return 0 ;
		}
		break ; 

	case WM_ENDSESSION:
		{
			if(pCtr->OnEndSession (wParam == TRUE, lParam))
				return 0 ;
		}
		break ;

	case WM_ENTERIDLE:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

			if(pCtr->OnEnterIdle (wParam == MSGF_DIALOGBOX, hwnd))
				return 0 ;
		}
		break ;
		
	case WM_ENTERSIZEMOVE:
		{
			if (pCtr->OnEnterSizeMove ())
				return 0 ;
		}
		break ;

	case WM_EXITSIZEMOVE:
		{
			if (pCtr && pCtr->OnExitSizeMove ())
				return 0 ;
		}
		break ;

	case WM_GETMINMAXINFO:
		{
			if (pCtr != 0) // Necessary because sometime this is received before WM_NCCREATE
			{	
				if (pCtr->OnGetMinMaxInfo (reinterpret_cast <Win::MinMaxInfo * const> (lParam)))
					return 0 ;
			}
		}
		break ;

	case WM_SETFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnSetFocus (hwnd))
				return 0 ;
		}
		break ;

	case WM_SETREDRAW:
		{
			if (pCtr->OnSetRedraw (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_SIZE:
		{
			Win::SizeType type (wParam) ;

			if (pCtr->OnSize (LOWORD (lParam), HIWORD (lParam), type))
				return 0 ;
		}
		break ;

	case WM_SHOWWINDOW:
		{
			Win::ShowWindowStatus status (lParam) ;

			if (pCtr->OnShowWindow (wParam == TRUE, status))
				return 0 ;
		}
		break ;

	case WM_CLOSE:
		{
			if (pCtr->OnClose ())
				return 0 ;
		}
		break ;

	case WM_QUERYENDSESSION:
		{
			if (!pCtr->OnQueryEndSession (lParam))
				return 0 ;
		}
		break ;

	case WM_VSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(pCtr->OnVerticalScroll (HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
			else // Control scrollbar.
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

				if (pCtr->OnControlVerticalScroll (hwnd,
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_HSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(pCtr->OnHorizontalScroll (HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
			else // Control scrollbar.
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

				if (pCtr->OnControlHorizontalScroll (hwnd,
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_DISPLAYCHANGE:
		{
			if (pCtr->OnDisplayChange (wParam, LOWORD (lParam), HIWORD (lParam)))
				return 0 ;
		}
		break ;

	case WM_FONTCHANGE:
		{	
			if (pCtr->OnFontChange ())
				return 0 ;			
		}
		break ;

	case WM_ACTIVATEAPP:
		{
			if (pCtr->OnOtherAppActivate (wParam == TRUE, lParam))
				return 0 ;
		}
		break ;

	case WM_COMPACTING:
		{
			if (pCtr->OnCompacting (wParam))
				return 0 ;
		}
		break ;

		//Palette Messages
	case WM_PALETTECHANGED:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnPaletteChanged (hwnd))
				return 0 ;
		}
		break ;

	case WM_PALETTEISCHANGING:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnPaletteIsChanging (hwnd))
				return 0 ;
		}
		break ;

	case WM_QUERYNEWPALETTE:
		{
			if (pCtr->OnQueryNewPalette ())
				return TRUE ;
		}
		return FALSE;

		//Menu Messages
	case WM_ENTERMENULOOP:
		{
			if (pCtr->OnEnterMenuLoop (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_EXITMENULOOP:
		{
			if (pCtr->OnExitMenuLoop (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_CONTEXTMENU:  
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnContextMenu ( LOWORD (lParam), HIWORD (lParam), hwnd))
				return 0; //Not suppose to return a value...
		}
		break ;

	case WM_INITMENU:
		{
			Win::Menu::Handle menu (reinterpret_cast <HMENU> (wParam)) ;

			if (pCtr->OnInitMenu(menu))
				return 0 ;
		}
		break ;

	case WM_INITMENUPOPUP:
		{
			HMENU hMenuPopup = reinterpret_cast <HMENU> (wParam) ;

			if (pCtr->OnInitMenuPopup (LOWORD (lParam), HIWORD (lParam) == TRUE, hMenuPopup))
				return 0 ;
		}
		break ;

	//Keyboard Message
	case WM_KILLFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast<HWND> (wParam)) ;

			if (pCtr->OnKillFocus (hwnd))
				return 0 ;
		}
		break ;

	case WM_CHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;
		
	case WM_DEADCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSDEADCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysDeadChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_KEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSKEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_KEYUP:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyUp (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSKEYUP:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysKeyUp (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_TIMECHANGE:
		{
			if (pCtr->OnTimeChange ())
				return 0 ;
		}
		break ;


	case WM_USERCHANGED:
		{
			if (pCtr->OnUserChanged ())
				return 0 ;
		}
		break ;
		
	case WM_MOVE:
		{
			if (pCtr->OnMove(LOWORD (lParam), HIWORD (lParam)))
				return 0 ;
		}
		break ;
		
	//Timer message
	case WM_TIMER:
		{
			if (pCtr->OnTimer (wParam, reinterpret_cast<TIMERPROC *> (lParam) ))
				return 0 ;
		}
		break ;


	//Mouse messages
	case WM_LBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;
	case WM_LBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_LBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MOUSEMOVE:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMouseMove (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMOUSEMOVE:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMouseMove(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_DESTROY:
		{
			if( pCtr->OnDestroy())
				return 0 ;
		}
		break ;

	case WM_NCDESTROY:
		{
			if (pCtr->OnNonClientDestroy ())
			{
				delete pCtr ;
				return 0 ;
			}
			delete pCtr ;
		}
		break ;

	//Clipboard Message

	case WM_CHANGECBCHAIN:
		{
			Win::dow::Handle hwndRemove (reinterpret_cast <HWND> (wParam)) ;
			Win::dow::Handle hwndNext   (reinterpret_cast <HWND> (lParam)) ;

			if(pCtr->OnChangeCBChain (hwndRemove, hwndNext))
				return 0 ;
		}
		break ;

	case WM_DRAWCLIPBOARD:
		{
			if(pCtr->OnDrawClipboard ())
				return 0 ;
		}
		break ;

	case WM_DESTROYCLIPBOARD:
		{
			if (pCtr->OnDestroyClipboard ())
				return 0 ;
		}
		break ;

	case WM_RENDERALLFORMATS:
		{
			if(pCtr->OnRenderAllFormats ())
				return 0 ;
		}
		break ;

	case WM_RENDERFORMAT:
		{
			if (pCtr->OnRenderFormat (wParam))
				return 0 ;
		}
		break ;
	
	//Child Message
	case WM_CHILDACTIVATE:
		{
			if (pCtr->OnChildActivate ()) 
				return 0 ;
		}
		break ;

	case WM_COMMAND:
		{
			if (lParam == 0)  //Menu or accelerator
			{
				if (pCtr->OnCommand(LOWORD (wParam), HIWORD (wParam) == 1)) 
					return 0 ;
			}
			else //control
			{
				HWND ctrl = reinterpret_cast<HWND>(lParam);
				if (pCtr->OnControl (Win::dow::Handle (ctrl), LOWORD (wParam), HIWORD (wParam)))
					return 0;
			}
		}
		break ;

	case WM_NOTIFY:
		{
			if (pCtr->OnNotify (static_cast <int> (wParam), lParam))
				return 0 ;
		}
		break ;

	case WM_SYSCOMMAND:
		{
			if (pCtr->OnSysCommand (wParam, LOWORD(lParam), HIWORD (lParam)))
				return 0 ;

		}
		break ;

	case WM_CTLCOLORSCROLLBAR:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnScrollBarColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;


	case WM_CTLCOLORSTATIC:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnStaticColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORBTN:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnButtonColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORDLG:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnDlgColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLOREDIT:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnEditColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORLISTBOX:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnListBoxColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	default:

		//-----------------------------------------------------------
		// User defined message. If the method in Win::Controller,
		// returns true, result is returned, else default behavior.
		//-----------------------------------------------------------

		if (msg >= WM_USER)
		{
			LRESULT result = 0 ;
			if (pCtr->OnUserMessage (msg, wParam, lParam, result))
				return result ;
		}
		break;

	}

	return ::DefWindowProc ( hwnd, msg, wParam, lParam ) ;
}

//-----------------------------------------------------
// This is the window procedure predifined for window
// subclassing.  Its works the same way as the 
// normal procedure.


LRESULT CALLBACK Win::SubProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SubController * pCtr = Win::GetLong <SubController *> (hwnd) ;

    switch (msg)
    {

	case WM_CREATE:
		{
			if ( pCtr->OnCreate (reinterpret_cast<CreationData const *> (lParam)))
				return 0 ;
		}
		break ;

	case WM_LBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;
		
	case WM_NCDESTROY:
		{
			if (pCtr->OnNonClientDestroy ())
			{
				delete pCtr ;
				return 0 ;
			}
			
			ProcPtr tmp = pCtr->GetPrevProc () ;

			Win::dow::Handle win (hwnd) ;

			win.UnSubClass () ;

			return ::CallWindowProc (tmp, hwnd, WM_NCDESTROY, wParam, lParam) ;
		}

	case WM_KEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SETFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnSetFocus (hwnd))
				return 0 ;
		}
		break ;
	case WM_CTLCOLORSCROLLBAR:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnScrollBarColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;


	case WM_CTLCOLORSTATIC:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnStaticColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORBTN:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnButtonColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORDLG:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnDlgColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLOREDIT:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnEditColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORLISTBOX:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnListBoxColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;


	}

	// Call the previous window procedure of the window.
	return pCtr->CallPrevProc (msg, wParam, lParam) ;
}

//--------------------------------------------------------------------
// This is the predefined window procedure that is used with every
// created frame window.  This procedure is hidden thanks to the 
// Win::FrameController.
//--------------------------------------------------------------------

LRESULT CALLBACK Win::FrameProc ( HWND hwnd, UINT msg, WPARAM wParam, 
					   LPARAM lParam )
{
	// Obtains a pointer on the controller.of the window.
	Win::Frame::Controller * pCtr = GetLong <Frame::Controller *> (hwnd) ;
	HWND                   client = pCtr ? pCtr->_myClient : 0 ;


	switch (msg)
	{

	// This message is used to do some innitialisation so the Win::Controller 
	// object works properlly.
	case WM_NCCREATE:
		{
			// Creates a Win::CreationData pointer on the CREATESTRUCT passed
			// in the lParam.
			Win::CreationData const * pData =  
				reinterpret_cast <CreationData const *> (lParam) ;

			StrongPointer <Win::Frame::Controller> * ap 
				= reinterpret_cast <StrongPointer<Win::Frame::Controller> *> (pData->GetCreationData ()) ;

			pCtr = ap->Release () ;


			// Initialize the Win::dow::Handle object inside the Win::Controller object.
			pCtr->SetFrameHandle (hwnd) ;
			pCtr->_myClient = 0 ;

			// Places the controller back in the window.
			SetLong <Frame::Controller *> (hwnd, pCtr) ;

			break ;


		}
	//---------------------------------------------------------------
	// Almost all the messages work the same.  If the corresponding 
	// methods in Win::Controller returns true, the window
	// procedure return 0.  Else, the DefWindowProc is called for
	// default behavior.
	//---------------------------------------------------------------

	case WM_CREATE:
		{
			if (pCtr->OnCreate (reinterpret_cast <CreationData const *> (lParam)))
				return 0 ;
		}
		break ;

	case WM_PAINT:
		{
			if(pCtr->OnPaint ())
				return 0 ;
		}
		break ;

	case WM_ACTIVATE:
		{
			ActivateAction aa(LOWORD (wParam)) ;

			Win::dow::Handle hwndPrev (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnActivate (aa, HIWORD (wParam) != FALSE, hwndPrev))
				return 0 ;
		}
		break ;
		
	case WM_CANCELMODE:
		{
			if (pCtr->OnCancelMode ())
				return 0 ;
		}
		break ;

	case WM_CAPTURECHANGED:
		{
			Win::dow::Handle hwndNewCapture (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnCaptureChange (hwndNewCapture))
				return 0 ;
		}
		break ;

	case WM_ENABLE:
		{
			if(pCtr->OnEnable (wParam == TRUE))
				return 0 ;
		}
		break ; 

	case WM_ENDSESSION:
		{
			if(pCtr->OnEndSession (wParam == TRUE, lParam))
				return 0 ;
		}
		break ;

	case WM_ENTERIDLE:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

			if(pCtr->OnEnterIdle (wParam == MSGF_DIALOGBOX, hwnd))
				return 0 ;
		}
		break ;
		
	case WM_ENTERSIZEMOVE:
		{
			if (pCtr->OnEnterSizeMove ())
				return 0 ;
		}
		break ;

	case WM_EXITSIZEMOVE:
		{
			if (pCtr->OnExitSizeMove ())
				return 0 ;
		}
		break ;

	case WM_GETMINMAXINFO:
		{
			if (pCtr != 0) // Necessary because sometime this is received before WM_NCCREATE
			{	
				if (pCtr->OnGetMinMaxInfo (reinterpret_cast <Win::MinMaxInfo * const> (lParam)))
					return 0 ;
			}
		}
		break ;

	case WM_SETFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnSetFocus (hwnd))
				return 0 ;
		}
		break ;

	case WM_SETREDRAW:
		{
			if (pCtr->OnSetRedraw (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_SIZE:
		{
			Win::SizeType type (wParam) ;

			if (pCtr->OnSize (LOWORD (lParam), HIWORD (lParam), type))
				return 0 ;
		}
		break ;

	case WM_SHOWWINDOW:
		{
			Win::ShowWindowStatus status (lParam) ;

			if (pCtr->OnShowWindow (wParam == TRUE, status))
				return 0 ;
		}
		break ;

	case WM_CLOSE:
		{
			if (pCtr->OnClose ())
				return 0 ;
		}
		break ;

	case WM_QUERYENDSESSION:
		{
			if (pCtr->OnQueryEndSession (lParam))
				return 0 ;
		}
		break ;

	case WM_VSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(pCtr->OnVerticalScroll (HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
			else // Control scrollbar.
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

				if (pCtr->OnControlVerticalScroll (hwnd,
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_HSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(pCtr->OnHorizontalScroll (HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
			else // Control scrollbar.
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

				if (pCtr->OnControlHorizontalScroll (hwnd,
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_DISPLAYCHANGE:
		{
			if (pCtr->OnDisplayChange (wParam, LOWORD (lParam), HIWORD (lParam)))
				return 0 ;
		}
		break ;

	case WM_FONTCHANGE:
		{	
			if (pCtr->OnFontChange ())
				return 0 ;			
		}
		break ;

	case WM_ACTIVATEAPP:
		{
			if (pCtr->OnOtherAppActivate (wParam == TRUE, lParam))
				return 0 ;
		}
		break ;

	case WM_COMPACTING:
		{
			if (pCtr->OnCompacting (wParam))
				return 0 ;
		}
		break ;

		//Palette Messages
	case WM_PALETTECHANGED:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnPaletteChanged (hwnd))
				return 0 ;
		}
		break ;

	case WM_PALETTEISCHANGING:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnPaletteIsChanging (hwnd))
				return 0 ;
		}
		break ;

	case WM_QUERYNEWPALETTE:
		{
			if (pCtr->OnQueryNewPalette ())
				return TRUE ;
		}
		return FALSE;

		//Menu Messages
	case WM_ENTERMENULOOP:
		{
			if (pCtr->OnEnterMenuLoop (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_EXITMENULOOP:
		{
			if (pCtr->OnExitMenuLoop (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_CONTEXTMENU:  
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnContextMenu ( LOWORD (lParam), HIWORD (lParam), hwnd))
				return 0; //Not suppose to return a value...
		}
		break ;

	case WM_INITMENU:
		{
			Win::Menu::Handle menu (reinterpret_cast <HMENU> (wParam)) ;

			if (pCtr->OnInitMenu(menu))
				return 0 ;
		}
		break ;

	case WM_INITMENUPOPUP:
		{
			HMENU hMenuPopup = reinterpret_cast <HMENU> (wParam) ;

			if (pCtr->OnInitMenuPopup (LOWORD (lParam), HIWORD (lParam) == TRUE, hMenuPopup))
				return 0 ;
		}
		break ;

	//Keyboard Message
	case WM_KILLFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast<HWND> (wParam)) ;

			if (pCtr->OnKillFocus (hwnd))
				return 0 ;
		}
		break ;

	case WM_CHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;
		
	case WM_DEADCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSDEADCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysDeadChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_KEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSKEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_KEYUP:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyUp (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSKEYUP:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysKeyUp (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_TIMECHANGE:
		{
			if (pCtr->OnTimeChange ())
				return 0 ;
		}
		break ;


	case WM_USERCHANGED:
		{
			if (pCtr->OnUserChanged ())
				return 0 ;
		}
		break ;
		
	case WM_MOVE:
		{
			if (pCtr->OnMove(LOWORD (lParam), HIWORD (lParam)))
				return 0 ;
		}
		break ;
		
	//Timer message
	case WM_TIMER:
		{
			if (pCtr->OnTimer (wParam, reinterpret_cast<TIMERPROC *> (lParam) ))
				return 0 ;
		}
		break ;


	//Mouse messages
	case WM_LBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;
	case WM_LBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_LBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MOUSEMOVE:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMouseMove (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMOUSEMOVE:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMouseMove(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_DESTROY:
		{
			if( pCtr->OnDestroy())
				return 0 ;
		}
		break ;

	case WM_NCDESTROY:
		{
			if (pCtr->OnNonClientDestroy ())
			{
				delete pCtr ;
				return 0 ;
			}
			delete pCtr ;
		}
		break ;

	//Clipboard Message

	case WM_CHANGECBCHAIN:
		{
			Win::dow::Handle hwndRemove (reinterpret_cast <HWND> (wParam)) ;
			Win::dow::Handle hwndNext   (reinterpret_cast <HWND> (lParam)) ;

			if(pCtr->OnChangeCBChain (hwndRemove, hwndNext))
				return 0 ;
		}
		break ;

	case WM_DRAWCLIPBOARD:
		{
			if(pCtr->OnDrawClipboard ())
				return 0 ;
		}
		break ;

	case WM_DESTROYCLIPBOARD:
		{
			if (pCtr->OnDestroyClipboard ())
				return 0 ;
		}
		break ;

	case WM_RENDERALLFORMATS:
		{
			if(pCtr->OnRenderAllFormats ())
				return 0 ;
		}
		break ;

	case WM_RENDERFORMAT:
		{
			if (pCtr->OnRenderFormat (wParam))
				return 0 ;
		}
		break ;
	
	//Child Message
	case WM_CHILDACTIVATE:
		{
			if (pCtr->OnChildActivate ()) 
				return 0 ;
		}
		break ;

	case WM_COMMAND:
		{
			if (lParam == 0)  //Menu or accelerator
			{
				if (pCtr->OnCommand(LOWORD (wParam), HIWORD (wParam) == 1)) 
					return 0 ;
			}
			else //control
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND>(lParam)) ;

				if (pCtr->OnControl (hwnd, LOWORD (wParam), HIWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_NOTIFY:
		{
			if (pCtr->OnNotify (static_cast <int> (wParam), lParam))
				return 0 ;
		}
		break ;


	case WM_SYSCOMMAND:
		{
			if (pCtr->OnSysCommand (wParam, LOWORD(lParam), HIWORD (lParam)))
				return 0 ;

		}
		break ;

	case WM_CTLCOLORSCROLLBAR:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnScrollBarColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;


	case WM_CTLCOLORSTATIC:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnStaticColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORBTN:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnButtonColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORDLG:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnDlgColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLOREDIT:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnEditColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORLISTBOX:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnListBoxColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	default:

		//-----------------------------------------------------------
		// User defined message. If the method in Win::Controller,
		// returns true, result is returned, else default behavior.
		//-----------------------------------------------------------

		if (msg >= WM_USER)
		{
			LRESULT result = 0 ;
			if (pCtr->OnUserMessage (msg, wParam, lParam, result))
				return result ;
		}
		break;

	}


	return ::DefFrameProc ( hwnd, client, msg, wParam, lParam ) ;
}

LRESULT CALLBACK Win::MDIChildProc ( HWND hwnd, UINT msg, WPARAM wParam, 
					   LPARAM lParam )
{
	// Obtains a pointer on the controller.of the window.
	Win::MDIChild::Controller * pCtr = Win::GetLong <Win::MDIChild::Controller *> (hwnd) ;

	switch (msg)
	{

	// This message is used to do some innitialisation so the Win::Controller 
	// object works properlly.
	case WM_NCCREATE:
		{
			// Creates a Win::CreationData pointer on the CREATESTRUCT passed
			// in the lParam.
			Win::CreationData const * pData =  
				reinterpret_cast <CreationData const *> (lParam) ;

			// Gets a pointer on the controller.
			MDICREATESTRUCT * pCreate = reinterpret_cast <MDICREATESTRUCT *> (pData->GetCreationData ()) ;

			StrongPointer<Win::MDIChild::Controller> * ap 
				= reinterpret_cast <StrongPointer<Win::MDIChild::Controller> *> (pCreate->lParam) ;

			pCtr = ap->Release () ;

			// Initialize the Win::dow::Handle object inside the Win::Controller object.
			pCtr->SetMDIChildHandle (hwnd) ;

			// Places the controller back in the window.
			SetLong <Win::MDIChild::Controller *> (hwnd, pCtr) ;

			break ;

		}
	//---------------------------------------------------------------
	// Almost all the messages work the same.  If the corresponding 
	// methods in Win::Controller returns true, the window
	// procedure return 0.  Else, the DefWindowProc is called for
	// default behavior.
	//---------------------------------------------------------------

	case WM_CREATE:
		{
			if (pCtr->OnCreate (reinterpret_cast <CreationData const *> (lParam)))
				return 0 ;
		}
		break ;

	case WM_PAINT:
		{
			if(pCtr->OnPaint ())
				return 0 ;
		}
		break ;

	case WM_ACTIVATE:
		{
			ActivateAction aa(LOWORD (wParam)) ;

			Win::dow::Handle hwndPrev (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnActivate (aa, HIWORD (wParam) != FALSE, hwndPrev))
				return 0 ;
		}
		break ;
		
	case WM_CANCELMODE:
		{
			if (pCtr->OnCancelMode ())
				return 0 ;
		}
		break ;

	case WM_CAPTURECHANGED:
		{
			Win::dow::Handle hwndNewCapture (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnCaptureChange (hwndNewCapture))
				return 0 ;
		}
		break ;

	case WM_ENABLE:
		{
			if(pCtr->OnEnable (wParam == TRUE))
				return 0 ;
		}
		break ; 

	case WM_ENDSESSION:
		{
			if(pCtr->OnEndSession (wParam == TRUE, lParam))
				return 0 ;
		}
		break ;

	case WM_ENTERIDLE:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

			if(pCtr->OnEnterIdle (wParam == MSGF_DIALOGBOX, hwnd))
				return 0 ;
		}
		break ;
		
	case WM_ENTERSIZEMOVE:
		{
			if (pCtr->OnEnterSizeMove ())
				return 0 ;
		}
		break ;

	case WM_EXITSIZEMOVE:
		{
			if (pCtr->OnExitSizeMove ())
				return 0 ;
		}
		break ;

	case WM_GETMINMAXINFO:
		{
			if (pCtr != 0) // Necessary because sometime this is received before WM_NCCREATE
			{	
				if (pCtr->OnGetMinMaxInfo (reinterpret_cast <Win::MinMaxInfo * const> (lParam)))
					return 0 ;
			}
		}
		break ;

	case WM_SETFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnSetFocus (hwnd))
				return 0 ;
		}
		break ;

	case WM_SETREDRAW:
		{
			if (pCtr->OnSetRedraw (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_SIZE:
		{
			Win::SizeType type (wParam) ;

			if (pCtr->OnSize (LOWORD (lParam), HIWORD (lParam), type))
				return 0 ;
		}
		break ;

	case WM_SHOWWINDOW:
		{
			Win::ShowWindowStatus status (lParam) ;

			if (pCtr->OnShowWindow (wParam == TRUE, status))
				return 0 ;
		}
		break ;

	case WM_CLOSE:
		{
			if (pCtr->OnClose ())
				return 0 ;
		}
		break ;

	case WM_QUERYENDSESSION:
		{
			if (pCtr->OnQueryEndSession (lParam))
				return 0 ;
		}
		break ;

	case WM_VSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(pCtr->OnVerticalScroll (HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
			else // Control scrollbar.
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

				if (pCtr->OnControlVerticalScroll (hwnd,
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_HSCROLL:
		{
			if (lParam == 0) // Not a control scrolbar.
			{
				if(pCtr->OnHorizontalScroll (HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
			else // Control scrollbar.
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND> (lParam)) ;

				if (pCtr->OnControlHorizontalScroll (hwnd,
					::GetWindowLong (reinterpret_cast <HWND> (lParam), GWL_ID), HIWORD (wParam), LOWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_DISPLAYCHANGE:
		{
			if (pCtr->OnDisplayChange (wParam, LOWORD (lParam), HIWORD (lParam)))
				return 0 ;
		}
		break ;

	case WM_FONTCHANGE:
		{	
			if (pCtr->OnFontChange ())
				return 0 ;			
		}
		break ;

	case WM_ACTIVATEAPP:
		{
			if (pCtr->OnOtherAppActivate (wParam == TRUE, lParam))
				return 0 ;
		}
		break ;

	case WM_COMPACTING:
		{
			if (pCtr->OnCompacting (wParam))
				return 0 ;
		}
		break ;

		//Palette Messages
	case WM_PALETTECHANGED:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnPaletteChanged (hwnd))
				return 0 ;
		}
		break ;

	case WM_PALETTEISCHANGING:
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnPaletteIsChanging (hwnd))
				return 0 ;
		}
		break ;

	case WM_QUERYNEWPALETTE:
		{
			if (pCtr->OnQueryNewPalette ())
				return TRUE ;
		}
		return FALSE;

		//Menu Messages
	case WM_ENTERMENULOOP:
		{
			if (pCtr->OnEnterMenuLoop (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_EXITMENULOOP:
		{
			if (pCtr->OnExitMenuLoop (wParam == TRUE))
				return 0 ;
		}
		break ;

	case WM_CONTEXTMENU:  
		{
			Win::dow::Handle hwnd (reinterpret_cast <HWND> (wParam)) ;

			if (pCtr->OnContextMenu ( LOWORD (lParam), HIWORD (lParam), hwnd))
				return 0; //Not suppose to return a value...
		}
		break ;

	case WM_INITMENU:
		{
			Win::Menu::Handle menu (reinterpret_cast <HMENU> (wParam)) ;

			if (pCtr->OnInitMenu(menu))
				return 0 ;
		}
		break ;

	case WM_INITMENUPOPUP:
		{
			HMENU hMenuPopup = reinterpret_cast <HMENU> (wParam) ;

			if (pCtr->OnInitMenuPopup (LOWORD (lParam), HIWORD (lParam) == TRUE, hMenuPopup))
				return 0 ;
		}
		break ;

	//Keyboard Message
	case WM_KILLFOCUS:
		{
			Win::dow::Handle hwnd (reinterpret_cast<HWND> (wParam)) ;

			if (pCtr->OnKillFocus (hwnd))
				return 0 ;
		}
		break ;

	case WM_CHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;
		
	case WM_DEADCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSDEADCHAR:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysDeadChar (static_cast<TCHAR> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_KEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSKEYDOWN:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysKeyDown (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_KEYUP:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnKeyUp (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_SYSKEYUP:
		{
			Win::Key::Data kData (lParam) ;

			if (pCtr->OnSysKeyUp (static_cast<int> (wParam), kData))
				return 0 ;
		}
		break ;

	case WM_TIMECHANGE:
		{
			if (pCtr->OnTimeChange ())
				return 0 ;
		}
		break ;


	case WM_USERCHANGED:
		{
			if (pCtr->OnUserChanged ())
				return 0 ;
		}
		break ;
		
	case WM_MOVE:
		{
			if (pCtr->OnMove(LOWORD (lParam), HIWORD (lParam)))
				return 0 ;
		}
		break ;
		
	//Timer message
	case WM_TIMER:
		{
			if (pCtr->OnTimer (wParam, reinterpret_cast<TIMERPROC *> (lParam) ))
				return 0 ;
		}
		break ;


	//Mouse messages
	case WM_LBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;
	case WM_LBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_LBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnLeftButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnMiddleButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONDBLCLK:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONDOWN:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonDown (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_RBUTTONUP:
		{
			Win::Mouse::KeyState kState (wParam) ;
	
			if (pCtr->OnRightButtonUp (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;
		}
		break ;

	case WM_MOUSEMOVE:
		{
			Win::Mouse::KeyState kState (wParam) ;
		
			if (pCtr->OnMouseMove (LOWORD (lParam), HIWORD (lParam), kState))
				return 0 ;

		}
		break ;

	case WM_NCLBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCLBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCLeftButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMiddleButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONDBLCLK:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonDoubleClick (LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONDOWN:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonDown(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCRBUTTONUP:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCRightButtonUp(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_NCMOUSEMOVE:
		{
			Win::Mouse::HitText hText (wParam) ;
	
			if (pCtr->OnNCMouseMove(LOWORD (lParam), HIWORD (lParam), hText))
				return 0 ;
		}
		break ;

	case WM_DESTROY:
		{
			if( pCtr->OnDestroy())
				return 0 ;	
		}
		break ;

	case WM_NCDESTROY:
		{
			if (pCtr->OnNonClientDestroy ())
			{
				delete pCtr ;
				return 0 ;
			}
			delete pCtr ;
		}
		break ;

	//Clipboard Message

	case WM_CHANGECBCHAIN:
		{
			Win::dow::Handle hwndRemove (reinterpret_cast <HWND> (wParam)) ;
			Win::dow::Handle hwndNext   (reinterpret_cast <HWND> (lParam)) ;

			if(pCtr->OnChangeCBChain (hwndRemove, hwndNext))
				return 0 ;
		}
		break ;

	case WM_DRAWCLIPBOARD:
		{
			if(pCtr->OnDrawClipboard ())
				return 0 ;
		}
		break ;

	case WM_DESTROYCLIPBOARD:
		{
			if (pCtr->OnDestroyClipboard ())
				return 0 ;
		}
		break ;

	case WM_RENDERALLFORMATS:
		{
			if(pCtr->OnRenderAllFormats ())
				return 0 ;
		}
		break ;

	case WM_RENDERFORMAT:
		{
			if (pCtr->OnRenderFormat (wParam))
				return 0 ;
		}
		break ;
	
	//Child Message
	case WM_CHILDACTIVATE:
		{
			if (pCtr->OnChildActivate ()) 
				return 0 ;
		}
		break ;

	case WM_COMMAND:
		{
			if (lParam == 0)  //Menu or accelerator
			{
				if (pCtr->OnCommand(LOWORD (wParam), HIWORD (wParam) == 1)) 
					return 0 ;
			}
			else //control
			{
				Win::dow::Handle hwnd (reinterpret_cast <HWND>(lParam)) ;

				if (pCtr->OnControl (hwnd, LOWORD (wParam), HIWORD (wParam)))
					return 0 ;
			}
		}
		break ;

	case WM_NOTIFY:
		{
			if (pCtr->OnNotify (static_cast <int> (wParam), lParam))
				return 0 ;
		}
		break ;

	case WM_SYSCOMMAND:
		{
			if (pCtr->OnSysCommand (wParam, LOWORD(lParam), HIWORD (lParam)))
				return 0 ;

		}
		break ;

	case WM_MDIACTIVATE:
		{
			Win::MDIChild::Handle desactivated (reinterpret_cast <HWND> (wParam)) ;
			Win::MDIChild::Handle activated (reinterpret_cast <HWND> (lParam)) ;

			if (pCtr->OnMDIActivated (desactivated, activated))
				return 0 ;
		}
		break ;

	case WM_CTLCOLORSCROLLBAR:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnScrollBarColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;


	case WM_CTLCOLORSTATIC:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnStaticColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORBTN:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnButtonColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORDLG:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnDlgColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLOREDIT:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnEditColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	case WM_CTLCOLORLISTBOX:
		{
			Win::ControlColor ctrColor ;

			if (pCtr->OnListBoxColor ((HWND) lParam, ctrColor))
			{
				if (ctrColor.ChangedTextColor ())
					::SetTextColor ((HDC) wParam, ctrColor._textColor.GetColorRef ()) ;
				if (ctrColor.ChangedBackgroundColor ())
					::SetBkColor ((HDC) wParam, ctrColor._backColor.GetColorRef ()) ;

				return (LRESULT) ctrColor._brush ;
			}
		}

		break;

	default:

		//-----------------------------------------------------------
		// User defined message. If the method in Win::Controller,
		// returns true, result is returned, else default behavior.
		//-----------------------------------------------------------

		if (msg >= WM_USER)
		{
			LRESULT result = 0 ;
			if (pCtr->OnUserMessage (msg, wParam, lParam, result))
				return result ;
		}
		break;

	}

	return ::DefMDIChildProc ( hwnd, msg, wParam, lParam ) ;
}