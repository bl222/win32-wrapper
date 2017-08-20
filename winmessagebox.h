
//---------------------------------------------------
// This file contains a class encapsulating a MessageBox.
//---------------------------------------------------

#if !defined (WINMESSAGEBOX_H)

	#define WINMESSAGEBOX_H
	#include "useunicode.h"
	#include "win.h"

	namespace Win
	{
	//---------------------------------------------------
	// Win::MessageDlg can be used to display a message box
	//---------------------------------------------------
		class MessageDlg
		{
		public:
			enum Type    {AbortRetryIgnore = MB_ABORTRETRYIGNORE, Ok = MB_OK, OkCancel = MB_OKCANCEL, RetryCancel = MB_RETRYCANCEL, YesNo = MB_YESNO, YesNoCancel = MB_YESNOCANCEL} ; // Buttons on the message box
			enum Icon    {None = 0, Exclamation = MB_ICONEXCLAMATION, Information = MB_ICONINFORMATION , Question = MB_ICONQUESTION, Stop = MB_ICONSTOP, Hand = MB_ICONHAND} ; // Icon of the message box.
			enum Default {Button1 = MB_DEFBUTTON1, Button2 = MB_DEFBUTTON2, Button3 = MB_DEFBUTTON3, Button4 = MB_DEFBUTTON4} ; // Default button on the message box
			enum Modal   {Application = MB_APPLMODAL, System = MB_SYSTEMMODAL, Task = MB_TASKMODAL} ; // Modality of the message box
			enum Return  {IdAbort = IDABORT, IdCancel = IDCANCEL, IdIgnore = IDIGNORE, IdYes = IDYES, IdNO = IDNO, IdOk = IDOK, IdRetry = IDRETRY} ; // Return value that can be returned by a Message box.


			//-----------------------------------------------------------------------
			// Constructor.
			//
			// Parameters:
			//
			// std::tstring      title   -> The desired title
			// Win::Base owner   -> Handle to the window owning the message box
			// Type             type    -> Indiquates which buttons will be on the message box.
			// Icon				Icon    -> Indiquates which icons will be displayed on the message box.
			// Default			Default -> Indiquates which button is the default.
			// Modal            modal   -> Indiquates the modality of the message box.
			//----------------------------------------------------------------------

			MessageDlg (std::tstring title, Win::Base owner = NULL, Type type = Ok, Icon icon = None, Default def = Button1, Modal modal = Application)
				: _owner (owner),
				  _title (title),
				  _style (type | icon | def | modal)
				  
			{}

			//-----------------------------------------------------------------------
			// Constructor.
			//
			// Parameters:
			//
			// Win::Base owner   -> Handle to the window owning the message box
			//----------------------------------------------------------------------

			MessageDlg (Win::Base owner = NULL)
				: _owner (owner),
				  _title (TEXT("")),
				  _style (0)
			{}

			//-----------------------------------------------------------------------
			// Sets the desired buttons
			//
			// Parameters:
			// Type type -> Indiquates the desired buttons.
			//----------------------------------------------------------------------

			void SetButtonType (Win::MessageDlg::Type type)
			{
				_style &= 0xFFFFFFF0 ;
				_style |= type;
			}

			//-----------------------------------------------------------------------
			// Sets the desired icon
			//
			// Parameters:
			// Icon icon -> Indiquates the desired icon.
			//----------------------------------------------------------------------

			void SetIcon (Win::MessageDlg::Icon icon)
			{
				_style &= 0xFFFFFF0F ;
				_style |= icon;
			}

			//-----------------------------------------------------------------------
			// Sets the default buttons
			//
			// Parameters:
			// Default def -> Indiquates the desired default button.
			//------------------------------------ ----------------------------------

			void SetDefaultButton (Win::MessageDlg::Default def)
			{
				_style &= 0xFFFFF0FF ;
				_style |= def;
			}

			//-----------------------------------------------------------------------
			// Sets the modality
			//
			// Parameters:
			// Modal modal -> Indiquates the desired modality.
			//----------------------------------------------------------------------

			void SetModality (Win::MessageDlg::Modal modal)
			{
				_style &= 0xFFFF0FFF ;
				_style |= modal;
			}

			//-----------------------------------------------------------------------
			// Sets the owner of the message box
			//
			// Parameters:
			//
			// Win::Base owner -> The owner.
			//----------------------------------------------------------------------

			void SetOwner (Win::Base owner)
			{
				_owner = owner;
			}

			//-----------------------------------------------------------------------
			// Sets the desired title
			//
			// Parameters:
			// 
			// str::string title -> The title.
			//----------------------------------------------------------------------

			void SetTitle (std::tstring title)
			{
				_title = title ;
			}

			//-----------------------------------------------------------------------
			// Show a message box
			//
			// Return Value:  A value indicating the button that was pressed.
			//
			// Parameters:
			// 
			// str::string text -> The message to be displayed to the user.
			//----------------------------------------------------------------------

			Win::MessageDlg::Return Show (std::tstring text)
			{
				return static_cast <Win::MessageDlg::Return> (::MessageBox (_owner, text.c_str(), _title.c_str(), _style)) ;
			}

			//-----------------------------------------------------------------------
			// Used to show a message box without having to create a MessageDlg object.
			//
			// Return Value:  A value indicating the button that was pressed.
			//
			// Parameters:
			//
			// str::string text -> The message to be displayed to the user.
			// std::tstring      title   -> The desired title
			// Win::Base owner   -> Handle to the window owning the message box
			// Type             type    -> Indiquates which buttons will be on the message box.
			// Icon				Icon    -> Indiquates which icons will be displayed on the message box.
			// Default			Default -> Indiquates which button is the default.
			// Modal            modal   -> Indiquates the modality of the message box.
			//----------------------------------------------------------------------

			static Win::MessageDlg::Return Show (std::tstring text, std::tstring title, Win::Base owner = NULL, Win::MessageDlg::Type type = Ok, Win::MessageDlg::Icon icon = None, Win::MessageDlg::Default def = Button1, Win::MessageDlg::Modal modal = Application)
			{
				return static_cast <Win::MessageDlg::Return> (::MessageBox (owner, text.c_str(), title.c_str(), type | icon | def | modal)) ;
			}

			
			//-----------------------------------------------------------------------
			// Useful to convert integer, float ect to string
			//----------------------------------------------------------------------

			template<class T>
			static std::tstring ToString (T val)
			{
				std::tostringstream toStr;
				toStr << val;
				return toStr.str ();
			}

		private:

			UINT             _style; // Style of the message box (buttons, icon, etc.)
			Win::Base _owner ; // Windows owning the message box.
			std::tstring      _title ; // Title of the message box.

		} ;
	}

#endif