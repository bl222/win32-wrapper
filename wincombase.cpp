#include "wincombase.h"

//------------------------------------------------------
// Show an error message related to an HRESULT value in a message
// box
//------------------------------------------------------

void COM::HResultException::Show ()
{
	std::tstring tmpMsg ;

	tmpMsg = _str;
	if (FAILED (_hr))
	{
			TCHAR * msg;
			::FormatMessage (
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			_hr,
			MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<TCHAR *> (& msg),
			0,
			NULL);
					
		tmpMsg += msg ;

		::MessageBox (NULL, tmpMsg.c_str(), TEXT("Exception"), MB_ICONEXCLAMATION | MB_OK) ;

		::LocalFree (msg);
	}
}


//------------------------------------------------------
// Obtains an error message related to an HRESULT value in string
//------------------------------------------------------

std::tstring COM::HResultException::GetErrorMessage ()
{
	std::tstring tmpMsg ;

	tmpMsg = _str;
	if (FAILED (_hr))
	{
		TCHAR * msg;
		::FormatMessage (
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		_hr,
		MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<TCHAR *> (& msg),
		0,
		NULL);

		tmpMsg += msg ;

		::LocalFree (msg);
	}
							
	return tmpMsg ;
}

//------------------------------------------------------
// Constructor.  Creates an object from a certain class.
//
// Parameters:
//
// CLSID const & classId -> Id of the class of the object
// bool running -> True if there is already one of these object running else false.
//------------------------------------------------------

COM::SmartObject::SmartObject (CLSID const & classId, bool running)
    :_iUnk (NULL)
{
    HRESULT hr = S_OK;
    if (running)
    {
        ::GetActiveObject (classId, NULL, & _iUnk);
    }
    if (_iUnk ==NULL)
    {
        hr = ::CoCreateInstance (
                   classId,
                   0,
                   CLSCTX_SERVER,
                   IID_IUnknown,
                   (void**)& _iUnk);
    }
    if (FAILED (hr))
        throw HResultException (hr, TEXT("Couldn't create instance"));
}

//------------------------------------------------------
// Obtains an Interface from the object
//
// Return value:  A void pointer on the interface.
//
// Parameters:
//
// IID const & iid -> Id of the desired Interface.
//------------------------------------------------------

void * COM::SmartObject::AcquireInterface (IID const & iid)
{
    void * p = NULL;
    HRESULT hr = _iUnk->QueryInterface (iid, & p);
    if (FAILED (hr))
    {
        if (hr == E_NOINTERFACE)
            throw TEXT("No such interface");
        else
            throw HResultException (hr, TEXT("Couldn't acquire interface"));
    }
    return p;
}

 
