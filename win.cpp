#include "win.h"
#include "wincontroller.h"
#include "wndproc.h"

//-------------------------------------------------------------------------
// Return the caption of the window represented by the Win::dow::Handle object.
//
// Return value:  The caption of the window.
//-------------------------------------------------------------------------

std::tstring Win::Base::GetText () const 
{
	int len = GetTextLenght ();
	std::tstring str;

	// Copy the caption in str.
	if (len > 0)
	{
		str.reserve (len + 1);
		str.resize (len);
		GetText (&str [0], len + 1);
	}
	
	return str;
}

//---------------------------------------------------------------------------------------
// Subclass the window represented by the Win::dow::Handle object. This mean giving
// it a new window procedure through a subclass controller.
//
// Parameters:
//
// SubController * subCtrl -> Point on the new controller (or rather subclass controller)
//                            of the window.
//---------------------------------------------------------------------------------------

void Win::Base::SubClass (StrongPointer <SubController> & subCtrl)
{
	// get previous window procedure and controller 
	ProcPtr prevProc = Win::GetLong<ProcPtr> (_h, GWL_WNDPROC);
	Win::BaseController * prevCtrl = Win::GetLong<Win::BaseController *> (_h);

	// remember them in the new controller
	subCtrl->Init (_h, prevProc, prevCtrl);

	// attach new controller to window
	Win::SetLong<Win::BaseController *> (_h, subCtrl.Release ());

	// attach new window procedure to window
	Win::SetLong<ProcPtr> (_h, SubProcedure, GWL_WNDPROC);
}

void Win::Base::UnSubClass ()
{
	// Get the current subclass controller
	Win::SubController * pCtrl = Win::GetLong<SubController *> (_h);

	// restore previous window procedure and controller (if any)
	Win::SetLong<ProcPtr> (_h, pCtrl->GetPrevProc (), GWL_WNDPROC);
	Win::SetLong<Win::BaseController *> (_h, pCtrl->GetPrevController ());

	pCtrl->Init (NULL,NULL,NULL) ;

	if (pCtrl)
		delete pCtrl;
}

//-------------------------------------------------------------------------
// Remove the menu bar of the window represented by the Win::dow::Handle object.
//
// Return value:  An object representing the menu bar.
//-------------------------------------------------------------------------

Win::Menu::Bar::StrongHandle Win::Base::RemoveMenuBar () const
{
	HMENU menu ;

	menu = ::GetMenu (_h) ;
	::SetMenu (_h, NULL) ;

	return Win::Menu::Bar::StrongHandle (menu) ;
}

//-------------------------------------------------------------------------
// Return the parent of the window represented by the Win::dow::Handle object.
//
// Return value:  A Win::dow::Handle object encapsulating the handle of the parent
//-------------------------------------------------------------------------

Win::Client::Handle Win::MDIChild::Handle::GetParent () 
{ 
	return ::GetParent (_h) ; 
}

BOOL CALLBACK Win::ChildEnumProc (HWND hwnd, LPARAM data)
{

	Win::ChildEnumController * ctrl = reinterpret_cast <Win::ChildEnumController *> (data) ;
	Win::dow::Handle                   win ;

	win.Init (hwnd) ;

	return ctrl->Enumeration (win) ;
}