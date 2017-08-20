#include "wincustomres.h"
#include "winexception.h"

//---------------------------------------------------------------------------
//  Constructor.  Uses LoadResource to get a handle on the custom resource.
//
// Parameters:
// 
// const HINSTANCE hInstance -> Instance of the program.
// const int id              -> Numerical id of the resource.
// const std::tstring type    -> Type of custum resource.
//---------------------------------------------------------------------------

Win::CustomRes::CustomRes (HINSTANCE hInstance, int id, const std::tstring type)
{
	_res = ::LoadResource(hInstance, ::FindResource (hInstance, MAKEINTRESOURCE (id), type.c_str ())) ;
	
	// Could not load the resource.
	if (!_res) 
		throw Win::Exception (TEXT("Could not load a custom ressource")) ;

	_ptr = ::LockResource (_res) ;
}

//------------------------------------------------------------------------
// Obtains the next long value from the custom resource
//
// Return value:  A next long value.
//------------------------------------------------------------------------

long Win::CustomRes::ReadLong () 
{
	long * p = reinterpret_cast <long *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next unsigned long value from the custom resource
//
// Return value:  A next unsigned long value.
//------------------------------------------------------------------------

unsigned long Win::CustomRes::ReadUnsignedLong () 
{
	unsigned long * p = reinterpret_cast <unsigned long *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next short value from the custom resource
//
// Return value:  A next short value.
//------------------------------------------------------------------------

short Win::CustomRes::ReadShort () 
{
	short * p = reinterpret_cast <short *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next unsigned short value from the custom resource
//
// Return value:  A next unsigned short value.
//------------------------------------------------------------------------

unsigned short Win::CustomRes::ReadUnsignedShort () 
{
	unsigned short * p = reinterpret_cast <unsigned short *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next char value from the custom resource
//
// Return value:  A next char value.
//------------------------------------------------------------------------

TCHAR Win::CustomRes::ReadChar () 
{
	TCHAR * p = reinterpret_cast <TCHAR *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next unsigned char value from the custom resource
//
// Return value:  A next unsigned char value.
//------------------------------------------------------------------------

BYTE Win::CustomRes::ReadByte () 
{
	BYTE * p = reinterpret_cast <unsigned char *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next bool value from the custom resource
//
// Return value:  A next bool value.
//------------------------------------------------------------------------

bool Win::CustomRes::ReadBool () 
{
	bool * p = reinterpret_cast <bool *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next float value from the custom resource
//
// Return value:  A next float value.
//------------------------------------------------------------------------

float Win::CustomRes::ReadFloat () 
{
	float * p = reinterpret_cast <float *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next double value from the custom resource
//
// Return value:  A next double value.
//------------------------------------------------------------------------

double Win::CustomRes::ReadDouble () 
{
	double * p = reinterpret_cast <double *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}

//------------------------------------------------------------------------
// Obtains the next wide char value from the custom resource
//
// Return value:  A next wide char value.
//------------------------------------------------------------------------

wchar_t Win::CustomRes::ReadWideChar ()
{
	wchar_t * p = reinterpret_cast <wchar_t *> (_ptr) ;

	_ptr = ++p;
	--p ;

	return *p ;
}