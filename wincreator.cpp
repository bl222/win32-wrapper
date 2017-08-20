#include "wincreator.h"

//---------------------------------------------------------------------
// Constructor.  Fill the data members with default values.
// 
// Parameters:
//
// const std::tstring className -> Each window are based on a Win::Class
//                                object.  This a the name of the
//								  Win::Class object.
// const HINSTANCE hInst       -> Instance of the program.
//---------------------------------------------------------------------

Win::BaseCreator::BaseCreator (const std::tstring className, const HINSTANCE hInst)
	: _hInst (hInst),
	  _className (className),
	  _style (0),
	  _styleEX (0),
	  _x (CW_USEDEFAULT),
	  _y (CW_USEDEFAULT),
	  _height (CW_USEDEFAULT),
	  _width (CW_USEDEFAULT),
	  _menu (NULL),
	  _parent (NULL)
{}



//-------------------------------------------------------------------
// The SetPosition method set the initial position and size of 
// the window.
//
// Parameters:
//
// const int x      -> Initial x coordinate. (CW_USEDEFAULT by default)
// const int y      -> Initial y coordinate. (CW_USEDEFAULT by default)
// const int width  -> Initial width. (CW_USEDEFAULT by default)
// const int height -> Initial height. (CW_USEDEFAULT by default)
//-------------------------------------------------------------------

void Win::BaseCreator::SetPosition (const int x, const int y, const int width, const int height)
{
	_x      = x ;
	_y      = y ;
	_width  = width ;
	_height = height ;
}

//----------------------------------------------------------------------
// Specify a menu resource to the window.  The menu resource
// is identified by a numerical id.
// 
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program.
// const int id              -> Id of the menu resource.
//---------------------------------------------------------------------

void Win::BaseCreator::SetMenu (const HINSTANCE hInstance, const int id)
{
	_menu = ::LoadMenu (hInstance, MAKEINTRESOURCE(id)) ;

	// Could not load a menu.
	if (!_menu)
		throw Win::Exception (TEXT("Could not attach a menu")) ;
}

//----------------------------------------------------------------------
// Specify a menu resource to the window.  The menu resource
// is identified by a string.
// 
// Parameters:
//
// const HINSTANCE hInstance -> Instance of the program.
// const int name            -> Name of the menu resource.
//---------------------------------------------------------------------

void Win::BaseCreator::SetMenu (const HINSTANCE hInstance, const std::tstring name)
{
	_menu = ::LoadMenu (hInstance, name.c_str ()) ;

	// Could not load a menu.
	if (!_menu)
		throw Win::Exception (TEXT("Could not attach a menu")) ;
}

//---------------------------------------------------------------------
// Constructor.  Fill the data members with default values.
// 
// Parameters:
//
// const std::tstring className -> Each window are based on a Win::Class
//                                object.  This a the name of the
//								  Win::Class object.
// const HINSTANCE hInst       -> Instance of the program.
//---------------------------------------------------------------------

Win::dow::Creator::Creator (const std::tstring className, const HINSTANCE hInst)
	: BaseCreator (className, hInst)
{
	/*_style = 0;
	_styleEX = 0;*/
}

//---------------------------------------------------------------------
// Create a window.
// 
// Return value:  The handle of the created window.
//
// Parameters:
//
// Win::Controller & controller -> Controller of the window.  A 
//                                 Win::Controller object represent the
//                                 Window procedure.
// const std::tstring title      -> Title of the window.
//---------------------------------------------------------------------

Win::dow::Handle Win::dow::Creator::Create(StrongPointer <Win::dow::Controller> & ctrl, const std::tstring title) const
{
	HWND hwnd ;
			
	hwnd = ::CreateWindowEx (_styleEX, _className.c_str (),
							 title.c_str (), _style, _x,
							 _y, _width, _height,
							 _parent, _menu, _hInst,
							 &ctrl ) ;

	// Error during the creation.
	if(!hwnd)
		throw Win::Exception (TEXT("Error, the window could not be created")) ;
			
	return hwnd ;
}

//---------------------------------------------------------------------
// Constructor.  Fill the data members with default values.
// 
// Parameters:
//
// const std::tstring className -> Each window are based on a Win::Class
//                                object.  This a the name of the
//								  Win::Class object.
// const HINSTANCE hInst       -> Instance of the program.
//---------------------------------------------------------------------

Win::Frame::Creator::Creator (const std::tstring className, const HINSTANCE hInst)
	: BaseCreator (className, hInst)
{
	_style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN ;
}


//---------------------------------------------------------------------
// Creates a frame window for a MDI application.
// 
// Return value:  The handle of the created window.
//
// Parameters:
//
// Win::FrameController & controller -> Controller of the window.  A 
//										Win::Controller object represent the
//										Window procedure.
// const std::tstring title			 -> Title of the window.
//---------------------------------------------------------------------

Win::Frame::Handle Win::Frame::Creator::Create(StrongPointer <Win::Frame::Controller> & ctrl, const std::tstring title) const
{
	HWND hwnd ;
				
	hwnd = ::CreateWindowEx (_styleEX, _className.c_str (),
							 title.c_str (), _style, _x,
							 _y, _width, _height,
							 _parent, _menu, _hInst,
							 &ctrl) ;

	// Error during the creation.
	if(!hwnd)
		throw Win::Exception (TEXT("Error, the window could not be created")) ;
			
	return hwnd ;
}

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
//---------------------------------------------------------------------

Win::MDIChild::Creator::Creator (const std::tstring className, const Win::Base & parent)
	: _parent (parent)
{
	_mdiCreate.szClass = className.c_str () ;
	_mdiCreate.hOwner  = parent.GetInstance () ;
	_mdiCreate.szTitle = TEXT(" ") ;
	_mdiCreate.x       = CW_USEDEFAULT ;
	_mdiCreate.y       = CW_USEDEFAULT ;
	_mdiCreate.cx      = CW_USEDEFAULT ;
	_mdiCreate.cy      = CW_USEDEFAULT ;
	_mdiCreate.style   = 0 ;
	_mdiCreate.lParam  = 0 ;
}

//-------------------------------------------------------------------
// The SetPosition method set the initial position and size of 
// the window.
//
// Parameters:
//
// const int x      -> Initial x coordinate. (CW_USEDEFAULT by default)
// const int y      -> Initial y coordinate. (CW_USEDEFAULT by default)
// const int width  -> Initial width. (CW_USEDEFAULT by default)
// const int height -> Initial height. (CW_USEDEFAULT by default)
//-------------------------------------------------------------------

void Win::MDIChild::Creator::SetPosition (const int x, const int y, const int width, const int height)
{
	_mdiCreate.x       = x ;
	_mdiCreate.y       = y ;
	_mdiCreate.cx      = width ;
	_mdiCreate.cy      = height ;
}

//---------------------------------------------------------------------
// Creates a MDI child window for a MDI application.
// 
// Return value:  The handle of the created window.
//
// Parameters:
//
// Win::MDIChildController & ctrl -> Controller of the window.  A 
//										Win::Controller object represent the
//										Window procedure.
// const std::tstring title		  -> Title of the window.
//---------------------------------------------------------------------

Win::MDIChild::Handle Win::MDIChild::Creator::Create (StrongPointer <Win::MDIChild::Controller> & ctrl, const std::tstring title)
{
	HWND hwnd ;
	_mdiCreate.lParam  = reinterpret_cast <LPARAM> (&ctrl) ;
	_mdiCreate.szTitle = title.c_str () ; 

	hwnd = reinterpret_cast <HWND> (::SendMessage (_parent, WM_MDICREATE, 0, 
												(LPARAM) (LPMDICREATESTRUCT) &_mdiCreate)) ;
		
	// Error during the creation.
	if(!hwnd)
		throw Win::Exception (TEXT("Error, the MDI child window could not be created")) ;

	return hwnd ;
}

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
//---------------------------------------------------------------------

Win::dow::ChildCreator::ChildCreator (const std::tstring classname, const Win::Base & parent, const int id)
	: Creator (classname, parent.GetInstance ()) 
{
	_style = WS_CHILD ;
	_parent = parent ;
	_menu = reinterpret_cast <HMENU> (id) ;
}



//---------------------------------------------------------------------
// This is used to create a window control.  Should not be used
// directly.
// 
// Return value:  The handle of the created control.
//
// Parameters:
//
// const std::tstring title      -> Title of the window.
//---------------------------------------------------------------------

Win::dow::Handle Win::dow::ChildCreator::Create (const std::tstring title) const
{
	HWND hwnd = ::CreateWindowEx (_styleEX, _className.c_str (), title.c_str(),
								  _style, _x, _y, _width, _height,
								  _parent, _menu, _hInst, NULL) ;

	if(!hwnd)
		throw Win::Exception (TEXT("Error, the child window could not be created")) ;

	return hwnd ;
}

//---------------------------------------------------------------------
// This is used to create a client window for a MDI application.
// 
// Return value:  The handle of the created MDI client window.
//
// Parameters:
//
// const std::tstring title      -> Title of the window.
//-------------------------------------------------------------------

Win::Client::Handle Win::Client::Creator::Create ()
{
	HWND hwnd = ::CreateWindowEx (_styleEX, _className.c_str (), NULL,
								  _style, _x, _y, _width, _height,
								  _parent, _menu, _hInst, 
								  reinterpret_cast <PSTR> (&_clientCreate)) ;

	if(!hwnd)
		throw Win::Exception (TEXT("Error, the client window could not be created")) ;

	return hwnd ;
}


