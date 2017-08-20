#include "wincontroller.h"
#include "winctrleventhandlers.h"

//-------------------------------------------------------------------------
// Represents the WM_COMMAND message for menus and keyboard accelerators.
//
// Parameters:
//
// const int id             -> Id of the menu or accelerator that caused 
//							   the message.
// const bool isAccelerator -> True if the message was caused by an 
//                             accelerator, else false.
//-------------------------------------------------------------------------

bool Win::BaseController::OnControl (Win::dow::Handle & control, const int id, const int notificationCode)
{
	
	std::map <HWND, ControlEventHandler *>::iterator iter = _ctrlMap.find (control);
	assert(iter != _ctrlMap.end ());
	ControlEventHandler * ctrlHandler = iter->second;

	switch (notificationCode)
	{
		case BN_CLICKED:
			{
			BaseButtonEventHandler * buttonHandler = dynamic_cast<BaseButtonEventHandler *> (ctrlHandler);
			assert(buttonHandler != NULL);
			
			buttonHandler->CallOnClick (*this);
			return true;
			}
			break;

	}
	return false ;
}