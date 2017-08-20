//-----------------------------------------------------------------
//  This file contains classes that allow using static controls.
//-----------------------------------------------------------------

#if !defined (WINSTATIC_H)

	#define WINSTATIC_H
	#include "useunicode.h"
	#include "wincontrol.h"
	#include "winicon.h"

	namespace Win
	{
		//-------------------------------------------------------------------------
		// Win::Static encapsulates a static control handle.  Represent a static
		// control.  Inherit from Win::SimpleControl for basic functionality.
		//-------------------------------------------------------------------------

		class StaticHandle : public SimpleControlHandle
		{
			
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle to represent the static
			// control through it's parent.
			// 
			// Parameters:
			//
			// const HWND parent -> Parent of the static control.
			// const int id      -> Id of the static control.
			//-------------------------------------------------------------------------

			StaticHandle (const Win::Base parent, const int id)
				: SimpleControlHandle (parent, id) 
			{}

			//-------------------------------------------------------------------------
			// Constructor.  Set the encapsulate handle directly
			// 
			// Parameters:
			//
			// const HWND win -> Handle of the static control.
			//-------------------------------------------------------------------------

			StaticHandle (const Win::Base win = NULL)
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
			// Sets a bitmap that will be displayed on the static control.
			//
			// Parameters:
			// 
			// const HBITMAP bitmap -> Handle of the bitmap.
			//-------------------------------------------------------------------------

			void SetBitmap (const Win::Bitmap::DDB::Handle bitmap)
			{
				SendMessage (STM_SETIMAGE, IMAGE_BITMAP, 
							reinterpret_cast <LPARAM> (reinterpret_cast <HANDLE> (static_cast<HBITMAP> (bitmap)))) ;
			}

			//-------------------------------------------------------------------------
			// Sets a icon that will be displayed on the static control.
			//
			// Parameters:
			// 
			// const HICON icon -> Handle of the icon.
			//-------------------------------------------------------------------------

			void SetIcon (const Win::Icon::Handle icon)
			{
				SendMessage (STM_SETIMAGE, IMAGE_ICON, 
							reinterpret_cast <LPARAM> (reinterpret_cast <HANDLE> (static_cast <HICON> (icon)))) ;
			}

		} ;

		//-------------------------------------------------------------------------
		// Win::StaticCreator allows to create a static control.
		// Inherit from Win::ControlCreator for basic functionality.
		//-------------------------------------------------------------------------

		class StaticCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  Creates a static control with the functionality of 
			// Win::ControlCreator.
			//-------------------------------------------------------------------------

			StaticCreator (const Win::Base parent, const int id)
				: ControlCreator (std::tstring (TEXT("static")), parent, id) 
			{}


			//-------------------------------------------------------------------------
			// Creates a new static control.
			// 
			// Return value:  The static control handle.
			//
			// Parameters:
			//
			// const std::tstring title -> The title of the static control.
			//-------------------------------------------------------------------------

			Win::StaticHandle Create (const std::tstring title) const
			{
				return ChildCreator::Create (title) ;
			}

			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future static control.
			//-------------------------------------------------------------------------

			void SetBitmapStyle         () {_style |= SS_BITMAP ;}
			void SetBlackFrameStyle     () {_style |= SS_BLACKFRAME ;}
			void SetBlackRectStyle      () {_style |= SS_BLACKRECT ;}
			void SetCenterStyle         () {_style |= SS_CENTER ;}
			void SetCenterImageStyle    () {_style |= SS_CENTERIMAGE ;}
			void SetEndEllipsisStyle    () {_style |= SS_ENDELLIPSIS ;}
			void SetPathEllipsisStyle   () {_style |= SS_PATHELLIPSIS ;}
			void SetEnhMetafileStyle    () {_style |= SS_ENHMETAFILE ;}
			void SetEtchedFrameStyle    () {_style |= SS_ETCHEDFRAME ;}
			void SetEtchedHorzStyle     () {_style |= SS_ETCHEDHORZ ;}
			void SetEtchedVertStyle     () {_style |= SS_ETCHEDVERT ;}
			void SetGrayFrameStyle      () {_style |= SS_GRAYFRAME ;}
 			void SetGrayRectStyle       () {_style |= SS_GRAYRECT ;}
			void SetIconStyle           () {_style |= SS_ICON ;}
			void SetLeftStyle           () {_style |= SS_LEFT ;}
			void SetLeftNoWordWrapStyle () {_style |= SS_LEFTNOWORDWRAP ;}
			void SetNoPrefixStyle       () {_style |= SS_NOPREFIX ;}
			void SetNotifyStyle         () {_style |= SS_NOTIFY ;}
			void SetOwnerDrawStyle      () {_style |= SS_OWNERDRAW ;}
			void SetRealSizeImageStyle  () {_style |= SS_REALSIZEIMAGE ;}
			void SetRightStyle          () {_style |= SS_RIGHT ;}
			void SetRightJustStyle      () {_style |= SS_RIGHTJUST ;}
			void SetSimpleStyle         () {_style |= SS_SIMPLE ;}
			void SetWhiteFrameStyle     () {_style |= SS_WHITEFRAME ;}
			void SetWhiteRectStyle      () {_style |= SS_WHITERECT ;}
			void SetWordEllipsisStyle   () {_style |= SS_WORDELLIPSIS ;}
		} ;
	}

#endif