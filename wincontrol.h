//---------------------------------------------------------
// This file contains classes linked to Window's control.
//---------------------------------------------------------

#if !defined (WINCONTROL_H)

	#define WINCONTROL_H
	#include "useunicode.h"
	#include "wincreator.h"
	#include  "winunicodehelper.h"
	namespace Win
	{

		//----------------------------------------------------------
		// Win::SimpleControl represents an handle to a Window 
		// control.  Used as a base class for type specifics controls 
		// handles
		//----------------------------------------------------------

			class SimpleControlHandle : public Win::dow::Handle
			{
			public:

				//----------------------------------------------------------
				// Constructor.  Creates a Win::SimpleControl with a parent 
				// and id.
				//
				// Parameters:
				//
				// const HWND parent -> Parent of the control.
				// const int id      -> Id of the control.
				//----------------------------------------------------------

				SimpleControlHandle (const Win::Base parent, const int id)
					: Win::dow::Handle (::GetDlgItem (parent, id)),
					  _id (id)
				{}

				//----------------------------------------------------------
				// Constructor.  Useful for creating unnitialized control
				// handles (egal to 0).
				//
				// Parameters:
				//
				// const HWND win -> Handle of the control.
				//----------------------------------------------------------

				SimpleControlHandle (const Win::Base win = NULL)
					: Win::dow::Handle (win), 
					  _id (0)
				{}

				//----------------------------------------------------------
				// Initializes the data members by specifying the parent and
				// the id.
				//
				// Parameters:
				//
				// const HWND parent -> Parent of the control.
				// const int id      -> Id of the control.
				//----------------------------------------------------------

				void Init (const Win::Base parent, const int id)
				{
					Handle::Init (::GetDlgItem (parent, id)) ;  //Use base class init to initialize handle.
					_id = id ;
				}
				
				//-----------------------------------------------------------------
				// Determines if the control is being clicked.
				//
				// Return value:  True if the control is being clicked, else false.
				//
				// Parameters:
				//.
				// const int code -> WPARAM of the WM_COMMAND message.
				//----------------------------------------------------------------

				static bool IsClicked (const int code)
				{
					return code == BN_CLICKED ;
				}

				//-----------------------------------------------------------------
				// Obtains the id of the control.
				//
				// Return value:  Id of the control.
				//----------------------------------------------------------------

				int GetId () const 
				{
					return _id ; 
				}

				int GetInteger () const ;
				unsigned int GetUnsignedInteger () const ;

				void SetInteger (const int value, const bool isSigned = false) const
				{
					::SetDlgItemInt (::GetParent (_h), _id, value, isSigned) ;
				}

			protected:
				int _id ; // Id of the control.

			} ;

			//-----------------------------------------------------------------
			// Win::ControlCreator is used to create Window's control. Is
			// a base class for creators of specifics types of controls.
			//-----------------------------------------------------------------

			class ControlCreator : public Win::dow::ChildCreator
			{
			public:

				//----------------------------------------------------------
				// Constructor.  Create a Win::ControlCreator object.  The
				//
				// Parameters:
				//
				// const std::tstring classname -> Name of the window class 
				//                                of the control.
				// const HWND parent           -> Parent of the control.
				// const int id                -> id of the control.
				//----------------------------------------------------------

				ControlCreator (const std::tstring classname, const Win::Base parent, const int id)
					: Win::dow::ChildCreator (classname, parent, id)
				{
					_style = WS_CHILD | WS_VISIBLE ;
				}

				//----------------------------------------------------------
				// Undo the changes made to the style of the control.
				//----------------------------------------------------------

				void ResetStyle () 
				{
					_style = WS_CHILD | WS_VISIBLE ;
				}
			} ;

	}
#endif