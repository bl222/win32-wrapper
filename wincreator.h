//------------------------------------------------------------------
// This file contains classes used to create window or child window.
//------------------------------------------------------------------

#if !defined (WINCREATOR_H)

	#define WINCREATOR_H
	#include "useunicode.h"
	#include "winexception.h"
	#include "wincontroller.h"
	#include "winupcast.h"
	#include "winunicodehelper.h"

	namespace Win
	{

		//-------------------------------------------------------------------
		// BaseCreator is not used directly.  Rather it is use to provide
		// basic functionnality for a serie of object used to create various
		// type of windowsWin::Creator allows to create window.  
		//-------------------------------------------------------------------

		class BaseCreator
		{
		public: 

			virtual ~BaseCreator ()
			{}

			void SetPosition (const int x, const int y, const int width, const int height) ;

			//-------------------------------------------------------------------
			// Set the handle of the menu to be used by the window.
			//
			// Parameters:
			//
			// const HMENU -> handle of the menu.
			//-------------------------------------------------------------------

			void SetMenu (const Win::Menu::Bar::Handle menu)
			{
				_menu = menu ;
			}

			void SetMenu (const HINSTANCE hInstance, const int id) ;
			void SetMenu (HINSTANCE hInstance, const std::tstring name) ;

			//----------------------------------------------------------------------
			// Resets the style.
			//----------------------------------------------------------------------

			void ResetStyle ()
			{
				_style = 0;
				_styleEX = 0;
			}

			//----------------------------------------------------------------------
			// Sets the WS_BORDER style
			//----------------------------------------------------------------------

			void SetBorderStyle()
			{
				_style |= WS_BORDER ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_BORDER and WS_CAPTION style
			//----------------------------------------------------------------------

			void SetCaptionStyle()
			{
				_style |= WS_CAPTION ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_CHILD style
			//----------------------------------------------------------------------

			void SetChildStyle()
			{
				_style |= WS_CHILD ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_CLIPCHILDREN style
			//----------------------------------------------------------------------

			void SetClipChildrenStyle()
			{
				_style |= WS_CLIPCHILDREN ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_CLIPSIBLINGS style
			//----------------------------------------------------------------------

			void SetClipSiblingsStyle()
			{
				_style |= WS_CLIPSIBLINGS ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_DISABLED style
			//----------------------------------------------------------------------

			void SetDisabledStyle()
			{
				_style |= WS_DISABLED ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_DLGFRAME style
			//----------------------------------------------------------------------

			void SetDlgFrameStyle()
			{
				_style |= WS_DLGFRAME ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_HSCROLL style
			//----------------------------------------------------------------------

			void SetHorizontalScrollStyle()
			{
				_style |= WS_HSCROLL ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_BORDER style
			//----------------------------------------------------------------------

			void SetGroupStyle()
			{
				_style |= WS_GROUP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_ICONIC style
			//----------------------------------------------------------------------

			void SetIconicStyle()
			{
				_style |= WS_ICONIC ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MAXIMISE style
			//----------------------------------------------------------------------

			void SetMaximizeStyle()
			{
				_style |= WS_MAXIMIZE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MAXIMISEBOX style
			//----------------------------------------------------------------------

			void SetMaximizeBoxStyle()
			{
				_style |= WS_MAXIMIZEBOX ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MINIMISE style
			//----------------------------------------------------------------------

			void SetMinimizeStyle()
			{
				_style |= WS_MINIMIZE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MINIMISEBOX style
			//----------------------------------------------------------------------

			void SetMinimizeBoxStyle()
			{
				_style |= WS_MINIMIZEBOX ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_OVERLAPPED style
			//----------------------------------------------------------------------

			void SetOverlappedStyle()
			{
				_style |= WS_OVERLAPPED ;
			}

				//----------------------------------------------------------------------
			// Sets the WS_OVERLAPPEDWINDOW style
			//----------------------------------------------------------------------

			void SetOverlappedWindowStyle()
			{
				_style |= WS_OVERLAPPEDWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_POPUP style
			//----------------------------------------------------------------------

			void SetPopupStyle()
			{
				_style |= WS_POPUP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_POPUPWINDOW style
			//----------------------------------------------------------------------

			void SetPopupWindowStyle()
			{
				_style |= WS_POPUPWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_SYSMENU and WS_CAPTION style
			//----------------------------------------------------------------------

			void SetSysMenuStyle()
			{
				_style |= WS_SYSMENU | WS_CAPTION;
			}

			//----------------------------------------------------------------------
			// Sets the WS_TABSTOP style
			//----------------------------------------------------------------------

			void SetTabStopStyle()
			{
				_style |= WS_TABSTOP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_THICKFRAME style
			//----------------------------------------------------------------------

			void SetThickFrameStyle()
			{
				_style |= WS_THICKFRAME ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_VISIBLE style
			//----------------------------------------------------------------------

			void SetVisibleStyle()
			{
				_style |= WS_VISIBLE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_VERTICALSCROLL style
			//----------------------------------------------------------------------

			void SetVerticalScrollStyle()
			{
				_style |= WS_VSCROLL ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_ACCEPTFILES style
			//----------------------------------------------------------------------

			void SetAcceptFilesStyle ()
			{
				_styleEX |= WS_EX_ACCEPTFILES ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_APPWINDOW style
			//----------------------------------------------------------------------

			void SetAppWindowStyle ()
			{
				_styleEX |= WS_EX_APPWINDOW ;
			}
			//----------------------------------------------------------------------
			// Sets the WS_EX_ACCEPTFILES style
			//----------------------------------------------------------------------

			void SetClientEdgeStyle ()
			{
				_styleEX |= WS_EX_CLIENTEDGE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_CONTEXTHELP style
			//----------------------------------------------------------------------

			void SetContextHelpStyle ()
			{
				_styleEX |= WS_EX_CONTEXTHELP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_CONTROLPARENT style
			//----------------------------------------------------------------------

			void SetControlParentStyle ()
			{
				_styleEX |= WS_EX_CONTROLPARENT ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_ACCEPTFILES style
			//----------------------------------------------------------------------

			void SetDlgModalFrameStyle ()
			{
				_styleEX |= WS_EX_DLGMODALFRAME ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_LEFT style
			//----------------------------------------------------------------------

			void SetLeftStyle ()
			{
				_styleEX |= WS_EX_LEFT ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_LEFTSCROLLBAR style
			//----------------------------------------------------------------------

			void SetLeftScrollbarStyle ()
			{
				_styleEX |= WS_EX_LEFTSCROLLBAR ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_LTRReadingS style
			//----------------------------------------------------------------------

			void SetLeftToRigthReadingStyle ()
			{
				_styleEX |= WS_EX_LTRREADING ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_MDICHILD style
			//----------------------------------------------------------------------

			void SetMDIChildStyle ()
			{
				_styleEX |= WS_EX_MDICHILD ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_NOPARENTNOTIFY style
			//----------------------------------------------------------------------

			void SetNoParentNotifyStyle ()
			{
				_styleEX |= WS_EX_NOPARENTNOTIFY ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_OVERLAPPEDWINDOW style
			//----------------------------------------------------------------------

			void SetOverlappedWindowEXStyle ()
			{
				_styleEX |= WS_EX_OVERLAPPEDWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_PALETTEWINDOW style
			//----------------------------------------------------------------------

			void SetPaletteWindowStyle ()
			{
				_styleEX |= WS_EX_PALETTEWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_RIGHT style
			//----------------------------------------------------------------------

			void SetRightStyle ()
			{
				_styleEX |= WS_EX_RIGHT ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_RIGHTSCROLLBAR style
			//----------------------------------------------------------------------

			void SetRightScrollbarStyle ()
			{
				_styleEX |= WS_EX_RIGHTSCROLLBAR ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_RTLREADING style
			//----------------------------------------------------------------------

			void SetRightToLeftReadingStyle ()
			{
				_styleEX |= WS_EX_RTLREADING ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_STATICEDGE style
			//----------------------------------------------------------------------

			void SetStaticEdgeStyle ()
			{
				_styleEX |= WS_EX_STATICEDGE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_TOOLWINDOW style
			//----------------------------------------------------------------------

			void SetToolWindowStyle ()
			{
				_styleEX |= WS_EX_TOOLWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_TOPMOST style
			//----------------------------------------------------------------------

			void SetTopMostStyle ()
			{
				_styleEX |= WS_EX_TOPMOST ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_TRANSPARENT style
			//----------------------------------------------------------------------

			void SetTransparentsStyle ()
			{
				_styleEX |= WS_EX_TRANSPARENT ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_EX_WINDOWEDGE style
			//----------------------------------------------------------------------

			void SetWindowEdgeStyle ()
			{
				_styleEX |= WS_EX_WINDOWEDGE ;
			}

			//-----------------------------------------------------------
			// Sets the style using the WINAPI flags
			//
			// Parameters:
			//
			// UINT style -> The WINAPI flags.
			//-----------------------------------------------------------

			void SetStyle (UINT style)
			{
				_style = style ;
			}

			//-----------------------------------------------------------
			// Sets the extended style using the WINAPI flags
			//
			// Parameters:
			//
			// UINT style -> The WINAPI flags.
			//-----------------------------------------------------------

			void SetExtendedStyle (UINT style)
			{
				_styleEX = style ;
			}

		protected:

			BaseCreator (const std::tstring className, const HINSTANCE hInst) ;

		protected:
			HINSTANCE           _hInst ; // Instance of the program.
			const std::tstring   _className ; // Name of the Win::Class on witch the window is based.
			DWORD               _style ; // style of the window.
			DWORD		        _styleEX ; // Extended style of the window.
			int			        _x ; // Innitial x coordinate of the window.
			int			        _y ; // Innitial y coordinate of the window.
			int			        _height ; // Innitial height of the window.
			int			        _width ; // Innitial width of the window.
			HMENU		        _menu ; // Menu of the window.
			HWND		        _parent ; // parent of the window.
		} ;

		namespace dow
		{

			//-------------------------------------------------------------------
			// Win::Creator allows to create a "normal" window
			//-------------------------------------------------------------------

			class Creator : public Win::BaseCreator
			{
			public:

				Creator (const std::tstring className, const HINSTANCE hInst) ;

				//Create a Window.
				Win::dow::Handle Create (StrongPointer <Win::dow::Controller> & ctrl, const std::tstring title) const ;
			} ;

			//------------------------------------------------------------------
			// A Win::ChildCreator object is used to create a child window. 
			// Also, Win::ChildCreator is the base class of Win::ControlCreator.
			//------------------------------------------------------------------

			class ChildCreator : public Creator
			{
			public:

				ChildCreator (const std::tstring classname, const Win::Base & parent, const int id) ;
				virtual ~ChildCreator ()
				{}

				Win::dow::Handle Create (const std::tstring title) const; // Create a child window.
				Win::dow::Handle Create (StrongPointer <Win::dow::Controller> & ctrl, const std::tstring title) const
				{
					return Creator::Create (ctrl, title) ;
				}

				//---------------------------------------------------------------------
				// A child window must have a numerical id.  This method set the id.
				// 
				// Parameters:
				//
				// const int id -> Id of the child window.
				//---------------------------------------------------------------------

				void ChangeId (const int id)
				{
					_menu = reinterpret_cast <HMENU> (id) ;
				}

				//---------------------------------------------------------------------
				// Resets the style attribute of the child window.
				//---------------------------------------------------------------------

				void ResetStyle ()
				{
					_style   = WS_CHILD ;
					_styleEX = 0;
				}
			} ;
		}

		namespace Frame
		{

			//-------------------------------------------------------------------
			// Win::FrameCreator allows to create a frame window for a MDI
			// application
			//-------------------------------------------------------------------

			class Creator : public Win::BaseCreator
			{
			public:

				Creator (const std::tstring className, const HINSTANCE hInst) ;

				//Create a Window.
				Win::Frame::Handle Create (StrongPointer <Win::Frame::Controller> & ctrl, const std::tstring title) const ;

				void ResetStyle ()
				{
					_style   = WS_CLIPCHILDREN;
					_styleEX = 0 ;
				}
			} ;
		}

		namespace MDIChild
		{

			//-------------------------------------------------------------------
			// Win::MDIChildCreator allows to create a MDI child window for a MDI
			// application
			//-------------------------------------------------------------------

			class Creator
			{
			public: 
				Creator (const std::tstring className, const Win::Base & parent) ;

				void SetPosition (const int x, const int y, const int width, const int height) ;

			void ResetStyle ()
			{
				_mdiCreate.style= 0;
			}

			//----------------------------------------------------------------------
			// Sets the WS_BORDER style
			//----------------------------------------------------------------------

			void SetBorderStyle()
			{
				_mdiCreate.style |= WS_BORDER ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_BORDER and WS_CAPTION style
			//----------------------------------------------------------------------

			void SetCaptionStyle()
			{
				_mdiCreate.style |= WS_CAPTION ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_CHILD style
			//----------------------------------------------------------------------

			void SetChildStyle()
			{
				_mdiCreate.style |= WS_CHILD ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_CLIPCHILDREN style
			//----------------------------------------------------------------------

			void SetClipChildrenStyle()
			{
				_mdiCreate.style |= WS_CLIPCHILDREN ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_CLIPSIBLINGS style
			//----------------------------------------------------------------------

			void SetClipSiblingsStyle()
			{
				_mdiCreate.style |= WS_CLIPSIBLINGS ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_DISABLED style
			//----------------------------------------------------------------------

			void SetDisabledStyle()
			{
				_mdiCreate.style |= WS_DISABLED ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_DLGFRAME style
			//----------------------------------------------------------------------

			void SetDlgFrameStyle()
			{
				_mdiCreate.style |= WS_DLGFRAME ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_HSCROLL style
			//----------------------------------------------------------------------

			void SetHorizontalScrollStyle()
			{
				_mdiCreate.style |= WS_HSCROLL ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_BORDER style
			//----------------------------------------------------------------------

			void SetGroupStyle()
			{
				_mdiCreate.style |= WS_GROUP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_ICONIC style
			//----------------------------------------------------------------------

			void SetIconicStyle()
			{
				_mdiCreate.style |= WS_ICONIC ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MAXIMISE style
			//----------------------------------------------------------------------

			void SetMaximizeStyle()
			{
				_mdiCreate.style |= WS_MAXIMIZE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MAXIMISEBOX style
			//----------------------------------------------------------------------

			void SetMaximizeBoxStyle()
			{
				_mdiCreate.style |= WS_MAXIMIZEBOX ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MINIMISE style
			//----------------------------------------------------------------------

			void SetMinimizeStyle()
			{
				_mdiCreate.style |= WS_MINIMIZE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_MINIMISEBOX style
			//----------------------------------------------------------------------

			void SetMinimizeBoxStyle()
			{
				_mdiCreate.style |= WS_MINIMIZEBOX ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_OVERLAPPED style
			//----------------------------------------------------------------------

			void SetOverlappedStyle()
			{
				_mdiCreate.style |= WS_OVERLAPPED ;
			}

				//----------------------------------------------------------------------
			// Sets the WS_OVERLAPPEDWINDOW style
			//----------------------------------------------------------------------

			void SetOverlappedWindowStyle()
			{
				_mdiCreate.style |= WS_OVERLAPPEDWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_POPUP style
			//----------------------------------------------------------------------

			void SetPopupStyle()
			{
				_mdiCreate.style |= WS_POPUP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_POPUPWINDOW style
			//----------------------------------------------------------------------

			void SetPopupWindowStyle()
			{
				_mdiCreate.style |= WS_POPUPWINDOW ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_SYSMENU and WS_CAPTION style
			//----------------------------------------------------------------------

			void SetSysMenuStyle()
			{
				_mdiCreate.style |= WS_SYSMENU | WS_CAPTION;
			}

			//----------------------------------------------------------------------
			// Sets the WS_TABSTOP style
			//----------------------------------------------------------------------

			void SetTabStopStyle()
			{
				_mdiCreate.style |= WS_TABSTOP ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_THICKFRAME style
			//----------------------------------------------------------------------

			void SetThickFrameStyle()
			{
				_mdiCreate.style |= WS_THICKFRAME ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_VISIBLE style
			//----------------------------------------------------------------------

			void SetVisibleStyle()
			{
				_mdiCreate.style |= WS_VISIBLE ;
			}

			//----------------------------------------------------------------------
			// Sets the WS_VERTICALSCROLL style
			//----------------------------------------------------------------------

			void SetVerticalScrollStyle()
			{
				_mdiCreate.style |= WS_VSCROLL ;
			}

			Win::MDIChild::Handle Create (StrongPointer <Win::MDIChild::Controller> & ctrl, const std::tstring title) ;

			protected:
				MDICREATESTRUCT _mdiCreate ; // Data concerning the creation of a MDI child window.
				HWND	        _parent ; // parent of the window.
			} ;
		}

		namespace Client
		{

			//-------------------------------------------------------------------
			// Win::ClientCreator allows to create a client window for a MDI
			// application
			//-------------------------------------------------------------------

			class Creator : public Win::dow::ChildCreator
			{
			public:
				//---------------------------------------------------------------------
				// Constructor.  Fill the data members with default values.
				// 
				// Parameters:
				//
				// const Win::dow::Handle & parent     -> Parent of the window.
				// const std::tstring className -> Each window are based on a Win::Class
				//                                object.  This a the name of the
				//								  Win::Class object.
				// const int id                -> Id of the child window.
				// const int idFirstChild	   -> Id of the first MDI child window that
				//								  will be created
				// const HMENU menu			   -> the Window popup Menu of the frame window.
				//---------------------------------------------------------------------

				Creator (const Win::Base & parent, const int id, const int idFirstChild, const HMENU windowMenu)
					: ChildCreator (TEXT ("MDICLIENT"), parent, id)
				{
					_style					   = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN ;
					_x						   = 0 ;
					_y						   = 0 ;
					_width					   = 0 ;
					_height					   = 0 ;
					_clientCreate.hWindowMenu  = windowMenu ;
					_clientCreate.idFirstChild = idFirstChild ;
				}

				Win::Client::Handle Create () ; // Create a client window.

				//---------------------------------------------------------------------
				// Resets the style attribute of the client window.
				//---------------------------------------------------------------------

				void ResetStyle ()
				{
					_style = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN ;
				}

				//---------------------------------------------------------------------
				// Sets the MDIS_ALLCHILDSTYLES style.
				//---------------------------------------------------------------------

				void SetAllChildStyles ()
				{
					_style |= MDIS_ALLCHILDSTYLES ;
				}

				//---------------------------------------------------------------------
				// Sets the handle of the window popup menu of the frame window.
				// 
				// Parameters:
				//
				// const HMENU menu -> Handle of the window popup menu.
				//---------------------------------------------------------------------

				void SetWindowMenu (const Win::Menu::Bar::Handle menu)
				{
					_clientCreate.hWindowMenu = menu ;
				}

				//---------------------------------------------------------------------
				// Change the id of the first MDI child window that will be created.
				// 
				// Parameters:
				//
				// const int id -> Id of the first MDI child window.
				//---------------------------------------------------------------------

				void ChangeFirstChildId (const int idFirstChild)
				{
					_clientCreate.idFirstChild = idFirstChild ;
				}

			private:
				CLIENTCREATESTRUCT _clientCreate ;
			} ;
		}
	}

#endif