#include "winclass.h"
#include "wndproc.h"

//----------------------------------------------------------------------
// Constructor.  Fill the encapsulated WNDCLASSEX structure with default
// value.
// 
// Parameters:
//
// const std::tstring & className -> Name of the Win::Class object.
//									This name identify each Win::Class
//									uniquely.
// const HINSTANCE hInst		 -> Handle to the instance of the 
//									program.
//---------------------------------------------------------------------

Win::Class::Class (const std::tstring & className, const HINSTANCE hInst)
: _name (className)
{
	_wndClass.lpfnWndProc   = Win::Proc ;
	_wndClass.cbSize        = sizeof (WNDCLASSEX) ;
	_wndClass.hInstance     = hInst ;
	_wndClass.lpszClassName = _name.c_str () ;
	_wndClass.hIcon         = NULL;
	_wndClass.hIconSm       = NULL ;
	_wndClass.hCursor       = ::LoadCursor (NULL, IDC_ARROW) ;
	_wndClass.hbrBackground = reinterpret_cast <HBRUSH> (::GetStockObject(WHITE_BRUSH)) ;
	_wndClass.style         = 0 ;
	_wndClass.lpszMenuName  = NULL ;
	_wndClass.cbClsExtra    = 0 ;
	_wndClass.cbWndExtra    = 0 ;

}

//----------------------------------------------------------------------
// Constructor.  Fill the encapsulated WNDCLASSEX structure with default
// value.
// 
// Parameters:
//
// const std::tstring & className -> Name of the Win::Class object.
//									This name identify each Win::Class
//									uniquely.
// const HINSTANCE hInst		 -> Handle to the instance of the 
//									program.
//---------------------------------------------------------------------

Win::FrameClass::FrameClass (const std::tstring & className, const HINSTANCE hInst)
	: Class (className, hInst)
{
	_wndClass.lpfnWndProc   = Win::FrameProc ;
}

//----------------------------------------------------------------------
// Constructor.  Fill the encapsulated WNDCLASSEX structure with default
// value.
// 
// Parameters:
//
// const std::tstring & className -> Name of the Win::Class object.
//									This name identify each Win::Class
//									uniquely.
// const HINSTANCE hInst		 -> Handle to the instance of the 
//									program.
//---------------------------------------------------------------------

Win::MDIChildClass::MDIChildClass (const std::tstring & className, const HINSTANCE hInst)
	: Class (className, hInst)
{
	_wndClass.lpfnWndProc = Win::MDIChildProc ;
}
