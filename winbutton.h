//-----------------------------------------------------------------
//  This file contains classes that allow using button controls.
//-----------------------------------------------------------------

#if !defined (WINBUTTON_H)

	#define WINBUTTON_H
	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include "wincontrol.h"
	#include "winicon.h"
	#include "winctrleventhandlers.h"
	#include <memory>
	namespace Win
	{

		//-------------------------------------------------------------------------
		// Win::GroupBoxHandle encapsulates a group box control handle.  Represent 
		// a group box control.  Inherit from Win::SimpleControlHandle for basic 
		// functionality.
		//-------------------------------------------------------------------------

		class GroupBoxHandle : public Win::SimpleControlHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the group box
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			GroupBoxHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			GroupBoxHandle (const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::PushButtonHandle encapsulates a push buttom control handle.  Represent 
		// a push button control.  Inherit from Win::SimpleControlHandle for basic 
		// functionality.
		//-------------------------------------------------------------------------

		class PushButtonHandle : public Win::SimpleControlHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the push button
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			PushButtonHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			PushButtonHandle (const Win::Base win = NULL)
				: SimpleControlHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}

			//-------------------------------------------------------------------------
			// Simulates a user clicking the button.
			//-------------------------------------------------------------------------

			void Click () const
			{
				SendMessage (BM_CLICK, 0, 0) ;
			}

			//-------------------------------------------------------------------------
			// Sets a bitmap that will be displayed on the push button control.
			//
			// Parameters:
			// 
			// const HBITMAP bitmap -> Handle of the bitmap.
			//-------------------------------------------------------------------------

			void SetBitmap (const Win::Bitmap::DDB::Handle bitmap) const
			{
					SendMessage (BM_SETIMAGE, IMAGE_BITMAP, 
					reinterpret_cast <LPARAM> (static_cast <HBITMAP> (bitmap))) ;
			}

			//-------------------------------------------------------------------------
			// Sets a icon that will be displayed on the push button control.
			//
			// Parameters:
			// 
			// const HICON icon -> Handle of the icon.
			//-------------------------------------------------------------------------

			void SetIcon (const Win::Icon::Handle icon) const
			{
					SendMessage (BM_SETIMAGE, IMAGE_ICON, 
					reinterpret_cast <LPARAM> (static_cast <HICON> (icon))) ;
			}

			//-------------------------------------------------------------------------
			// Determines if the button has keyboard focus.
			//
			// Return value:  True if the push button has focus, else false.
			//-------------------------------------------------------------------------

			bool HasFocus () const
			{
				return SendMessage (BM_GETSTATE, 0, 0) == BST_FOCUS ;
			}

			//-------------------------------------------------------------------------
			// Determines if the button is pushed.
			//
			// Return value:  True if the push button is pushed, else false.
			//-------------------------------------------------------------------------

			bool IsPushed () const
			{
				return SendMessage (BM_GETSTATE, 0, 0) == BST_PUSHED ;
			}

			//-------------------------------------------------------------------------
			// High light the button
			//-------------------------------------------------------------------------

			void HighLight () const
			{
				SendMessage (BM_SETSTATE, TRUE, 0) ;
			}

			//-------------------------------------------------------------------------
			// Removes the high light from the button.
			//-------------------------------------------------------------------------

			void RemoveHighLight () const
			{
				SendMessage (BM_SETSTATE, FALSE, 0) ;
			}

			//-------------------------------------------------------------------------
			// Highlight the button or removes it.
			//
			// const bool highlight -> True the button is hightlighted, false the
			//						   highlight is removed.
			//-------------------------------------------------------------------------

			void SetHighLight (const bool highlight) const
			{
				SendMessage (BM_SETSTATE, highlight, 0) ;
			}

			//-------------------------------------------------------------------------
			// Changes the style of the button..
			//
			// const unsigned long style -> The new style.
			// const bool highlight      -> True if the button must be redrawn, false
			//								the button is not redrawn.
			//-------------------------------------------------------------------------

			void SetStyle (const unsigned long style, const bool redraw = true) const
			{
				SendMessage (BM_SETSTYLE, style, MAKELPARAM(redraw,0)) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::AutoCheckBoxHandleHandle encapsulates an auto CheckBoxHandle control handle.  Represents 
		// an auto chexbox control.  Inherit from Win::PushButtonHandle control for basic 
		// functionality.
		//-------------------------------------------------------------------------

		class AutoCheckBoxHandle : public PushButtonHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the auto CheckBoxHandle
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			AutoCheckBoxHandle (const Win::Base parent, const int id)
				: PushButtonHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			AutoCheckBoxHandle (const Win::Base win = NULL)
				: PushButtonHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}

			//-------------------------------------------------------------------------
			// Determines if the auto CheckBoxHandle is checked
			//
			// Return value:  True, it is checked, false it is not checked.
			//-------------------------------------------------------------------------

			bool IsChecked () const
			{
				return SendMessage (BM_GETCHECK, 0, 0) == BST_CHECKED ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::CheckBoxHandle encapsulates a CheckBoxHandle control handle.  Represents 
		// a chexbox control.  Inherit from Win::AutoCheckBoxHandleHandle control for basic 
		// functionality.
		//-------------------------------------------------------------------------

		class CheckBoxHandle : public AutoCheckBoxHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the CheckBoxHandle
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			CheckBoxHandle (const Win::Base parent, const int id)
				: AutoCheckBoxHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			CheckBoxHandle (const Win::Base win = NULL)
				: AutoCheckBoxHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}

			//-------------------------------------------------------------------------
			// Check the CheckBoxHandle.
			//-------------------------------------------------------------------------

			void Check () const
			{
				SendMessage (BM_SETCHECK, BST_CHECKED, 0) ;
			}

			//-------------------------------------------------------------------------
			// Uncheck the CheckBoxHandle.
			//-------------------------------------------------------------------------

			void UnCheck () const
			{
				SendMessage (BM_SETCHECK, BST_UNCHECKED, 0) ;
			}

			//-------------------------------------------------------------------------
			// If the CheckBoxHandle is checked, its becomes unchecked.  If the CheckBoxHandle
			// is uncheck, its becomes checked.
			//-------------------------------------------------------------------------

			void Toggle () const
			{
				SendMessage (BM_SETCHECK, 
					!SendMessage (BM_GETCHECK, 0, 0), 0) ;
			}
 
			//-------------------------------------------------------------------------
			// Makes the button checked or unchecked.
			//
			// Parameters:
			//
			// const bool checked -> True, the button is checked.  False, the button is
			//						 unchecked.
			//-------------------------------------------------------------------------

			void SetCheck (const bool checked) const
			{
				SendMessage (BM_SETCHECK, checked, 0) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::ThreeStateCheckBoxHandle encapsulates a three state CheckBoxHandle control 
		// handle.  Represents a three state chexbox control.  Inherit from 
		// Win::AutoCheckBoxHandleHandle control for basic functionality.
		//-------------------------------------------------------------------------

		class ThreeStateCheckBoxHandle : public CheckBoxHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the three state 
			// CheckBoxHandle control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			ThreeStateCheckBoxHandle (const Win::Base parent, const int id)
				: CheckBoxHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			ThreeStateCheckBoxHandle (const Win::Base win = NULL)
				: CheckBoxHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id);
			}

			//-------------------------------------------------------------------------
			// Gives the three state CheckBoxHandle a particular check type.
			// 
			// Parameters:
			//
			// const int checkType -> BST_CHECKED = Makes the button checked.
			//						  BST_INDETERMINATE = Makes the button indeterminated
			//						  BST_UNCHECKED = Makes the button unchecked.
			//-------------------------------------------------------------------------

			void SetCheck (const int checkType) const
			{
				SendMessage (BM_SETCHECK, checkType, 0) ;
			}

			//-------------------------------------------------------------------------
			// Makes the check box indeterminated.
			//-------------------------------------------------------------------------

			void MakeIndeterminate () const
			{
				SendMessage (BM_SETCHECK, BST_INDETERMINATE, 0) ;
			}

			//-------------------------------------------------------------------------
			// Determines if the CheckBoxHandle is indeterminated.
			//
			// Return value: True if the button is indeterminated, else false.
			//-------------------------------------------------------------------------

			bool IsInteterminate () const
			{
				return SendMessage (BM_GETCHECK, 0, 0) == BST_INDETERMINATE ;
			}

			//-------------------------------------------------------------------------
			// Obtains the state of the three state CheckBoxHandle.
			//
			// Return value: The state of the three state CheckBoxHandle.
			//-------------------------------------------------------------------------

			int GetState () const
			{
				return SendMessage (BM_GETCHECK, 0, 0) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::RadioButtonHandle encapsulates a radio button control 
		// handle.  Represents a radio button control.  Inherit from 
		// Win::AutoCheckBoxHandleHandle control for basic functionality.
		//-------------------------------------------------------------------------

		class RadioButtonHandle : public AutoCheckBoxHandle
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the radio button
			// control through it's parent.
			// 
			// Parameters:
			//
			// const Win::Base parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			RadioButtonHandle (const Win::Base parent, const int id)
				: AutoCheckBoxHandle (parent, id)
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const Win::Base win -> Handle of the group box control.
			//-------------------------------------------------------------------------

			RadioButtonHandle (const Win::Base win = NULL)
				: AutoCheckBoxHandle (win)
			{}

			//-------------------------------------------------------------------------
			// Initialize the handle and the id through the parent handle.
			//-------------------------------------------------------------------------

			void Init (const Win::Base parent, const int id)
			{
				SimpleControlHandle::Init (parent, id) ;
			}

			//-------------------------------------------------------------------------
			//  Checks the radio button..
			//-------------------------------------------------------------------------

			void Check () const
			{
				SendMessage (BM_SETCHECK, BST_CHECKED, 0) ;
			}

			//-------------------------------------------------------------------------
			// Unchecks the radio button.
			//-------------------------------------------------------------------------

			void UnCheck () const
			{
				SendMessage (BM_SETCHECK, BST_UNCHECKED, 0) ;
			}
 
			//-------------------------------------------------------------------------
			// Checks or unchecks the radio button.
			//
			// Parameters:
			//
			//
			// const bool checked -> True if the radio button must be checked. False
			//						 if the radio button must be unchecked.
			//-------------------------------------------------------------------------

			void SetCheck (const bool checked) const
			{
				SendMessage (BM_SETCHECK, checked, 0) ;
			}
		} ;

		//-------------------------------------------------------------------------
		// Win::ButtonCreator allows to create a button control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class ButtonCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates a button control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			ButtonCreator (const Win::Base parent, const int id)
				: ControlCreator (std::tstring (TEXT("button")), parent, id) 
			{}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future button control.
			//-------------------------------------------------------------------------

			void SetLeftTextStyle          () {_style |= BS_LEFTTEXT ;}
			void SetOwnerDrawStyle         () {_style |= BS_OWNERDRAW ;}
			void SetBitmapStyle            () {_style |= BS_BITMAP ;}
			void SetBottomStyle            () {_style |= BS_BOTTOM ;}
			void SetCenterStyle            () {_style |= BS_CENTER ;}
			void SetIconStyle              () {_style |= BS_ICON ;}
			void SetFlatStyle              () {_style |= BS_FLAT ;}
			void SetLeftStyle              () {_style |= BS_LEFT ;}
			void SetMultilineStyle         () {_style |= BS_MULTILINE ;}
			void SetNotify                 () {_style |= BS_NOTIFY ;}
			void SetPushLikeStyle          () {_style |= BS_PUSHLIKE ;}
			void SetRightStyle             () {_style |= BS_RIGHT ;}
			void SetRightButtonStyle       () {_style |= BS_RIGHTBUTTON ;}
			void SetTextStyle              () {_style |= BS_TEXT ;}
			void SetTopStyle               () {_style |= BS_TOP ;}
			void SetVerticalCenterStyle    () {_style |= BS_VCENTER ;}
		} ;

		//-------------------------------------------------------------------------
		// Win::GroupBoxCreator allows to create a button control.
		// Inherit from Win::ButtonlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class GroupBoxCreator : public ButtonCreator
		{
		public:
			//-------------------------------------------------------------------------
			// Constructor.  Creates a gropbox control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			GroupBoxCreator (const Win::Base parent, const int id)
				: ButtonCreator (parent, id) 
			{
				_style |= BS_GROUPBOX;
			}

			//-------------------------------------------------------------------------
			// Resets the style of the group box to be created.
			//-------------------------------------------------------------------------

			void ResetStyle ()
			{
				ChildCreator::ResetStyle ();
				_style |= BS_GROUPBOX ;
			}

			//-------------------------------------------------------------------------
			// Creates a new groupbox control.
			// 
			// Return value:  The groupbox control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the groupbox control.
			//-------------------------------------------------------------------------

			Win::GroupBoxHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::PushButtonCreator allows to create a button control.
		// Inherit from Win::ButtonlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class PushButtonCreator : public ButtonCreator
		{
		public:
			//-------------------------------------------------------------------------
			// Constructor.  Creates a push button control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			PushButtonCreator (const Win::Base parent, const int id)
				: ButtonCreator (parent, id) 
			{
				_style |= BS_PUSHBUTTON;
			}

			//-------------------------------------------------------------------------
			// Resets the style of the push button to be created.
			//-------------------------------------------------------------------------

			void ResetStyle ()
			{
				ChildCreator::ResetStyle ();
				_style |= BS_PUSHBUTTON ;
			}

			//-------------------------------------------------------------------------
			// Creates a new pushbutton control.
			// 
			// Return value:  The pushbutton control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the pushbutton control.
			//-------------------------------------------------------------------------

			Win::PushButtonHandle Create (const std::tstring title, std::auto_ptr<BaseButtonEventHandler> eventHandler) const
			{
				Win::BaseController * ctrl = Win::GetLong<BaseController *> (_parent);
				Win::dow::Handle tmp = ChildCreator::Create (title) ;
				
				ctrl->RegisterControl (tmp, eventHandler.release ());
				return tmp ;
			}

			//-------------------------------------------------------------------------
			// Sets the default push button style.
			//-------------------------------------------------------------------------

			void SetDefaultPushButtonStyle () {_style |= BS_DEFPUSHBUTTON ;}

		} ;

		//-------------------------------------------------------------------------
		// Win::CheckBoxCreator allows to create a button control.
		// Inherit from Win::ButtonlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class CheckBoxCreator : public ButtonCreator
		{
		public:
			//-------------------------------------------------------------------------
			// Constructor.  Creates a gropbox control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			CheckBoxCreator (const Win::Base parent, const int id)
				: ButtonCreator (parent, id) 
			{
				_style |= BS_CHECKBOX;
			}

			//-------------------------------------------------------------------------
			// Resets the style of the check box to be created.
			//-------------------------------------------------------------------------

			void ResetStyle ()
			{
				ChildCreator::ResetStyle ();
				_style |= BS_CHECKBOX ;
			}

			//-------------------------------------------------------------------------
			// Creates a new checkbox control.
			// 
			// Return value:  The groupbox control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the groupbox control.
			//-------------------------------------------------------------------------

			Win::CheckBoxHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::AutoCheckBoxCreator allows to create a button control.
		// Inherit from Win::ButtonlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class AutoCheckBoxCreator : public ButtonCreator
		{
		public:
			//-------------------------------------------------------------------------
			// Constructor.  Creates a auto check box control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			AutoCheckBoxCreator (const Win::Base parent, const int id)
				: ButtonCreator (parent, id) 
			{
				_style |= BS_AUTOCHECKBOX;
			}

			//-------------------------------------------------------------------------
			// Resets the style of the auto check box to be created.
			//-------------------------------------------------------------------------

			void ResetStyle ()
			{
				ChildCreator::ResetStyle ();
				_style |= BS_AUTOCHECKBOX ;
			}

			//-------------------------------------------------------------------------
			// Creates a new autocheckbox control.
			// 
			// Return value:  The  autocheckbox control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the autocheckbox control.
			//-------------------------------------------------------------------------

			Win::AutoCheckBoxHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::ThreeStateCheckBoxCreator allows to create a button control.
		// Inherit from Win::ButtonlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class ThreeStateCheckBoxCreator : public ButtonCreator
		{
		public:
			//-------------------------------------------------------------------------
			// Constructor.  Creates a 3 state check box control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			ThreeStateCheckBoxCreator (const Win::Base parent, const int id)
				: ButtonCreator (parent, id) 
			{
				_style |= BS_3STATE;
			}

			//-------------------------------------------------------------------------
			// Resets the style of the 3 state check box to be created.
			//-------------------------------------------------------------------------

			void ResetStyle ()
			{
				ChildCreator::ResetStyle ();
				_style |= BS_3STATE ;
			}

			//-------------------------------------------------------------------------
			// Creates a new 3STATEcheckbox control.
			// 
			// Return value:  The  3STATEcheckbox control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the autocheckbox control.
			//-------------------------------------------------------------------------

			Win::ThreeStateCheckBoxHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::RadioButtonCreator allows to create a button control.
		// Inherit from Win::ButtonlCreator for basic functionality.
		//-------------------------------------------------------------------------		

		class RadioButtonCreator : public ButtonCreator
		{
		public:
			//-------------------------------------------------------------------------
			// Constructor.  Creates a radio button control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			RadioButtonCreator (const Win::Base parent, const int id)
				: ButtonCreator (parent, id) 
			{
				_style |= BS_RADIOBUTTON;
			}

			//-------------------------------------------------------------------------
			// Resets the style of the radio button to be created.
			//-------------------------------------------------------------------------

			void ResetStyle ()
			{
				ChildCreator::ResetStyle ();
				_style |= BS_RADIOBUTTON ;
			}

			//-------------------------------------------------------------------------
			// Creates a new radio button control.
			// 
			// Return value:  The radiobutton control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the radiobutton control.
			//-------------------------------------------------------------------------

			Win::RadioButtonHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}
		} ;
	}
#endif