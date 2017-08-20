//-----------------------------------------------------------------
//  This file contains classes that allow using COM.
//-----------------------------------------------------------------

#if !defined (WINCOMBASE_H)

#define WINCOMBASE_H
	#include "useunicode.h"
#include <windows.h>
#include "winunicodehelper.h"

namespace COM
{
	//------------------------------------------------------
	// Exception class linked to HRESULT value
	//------------------------------------------------------
	class HResultException
	{
	public:

		//------------------------------------------------------
		// Constructor
		//------------------------------------------------------

		HResultException (HRESULT hr, TCHAR const * str = NULL)
			: _hr (hr), 
			  _str (str)
		{}

		//------------------------------------------------------
		// Obtains the HRESULT value
		//
		// Return value:  A HRESULT value linked to the exception
		//------------------------------------------------------

		HRESULT GetError () const
		{
			return _hr ;
		}

		void Show () ;
		std::tstring GetErrorMessage () ;

	private:
		HRESULT     _hr;
		TCHAR const * _str;
	};

	//------------------------------------------------------
	// Class used to inidcate the usage of com
	//------------------------------------------------------

	class UseCom
	{
	public:

		//------------------------------------------------------
		// Constructor, Innitialize COM
		//------------------------------------------------------

		UseCom () 
		{
			HRESULT err = CoInitialize (NULL);
			if (err != S_OK)
				throw TEXT("Couldn't initialize COM");
		}

		//------------------------------------------------------
		// Destructor, unitialize com
		//------------------------------------------------------

		~UseCom () 
		{ 
			CoUninitialize (); 
		}
	};

	//------------------------------------------------------
	// Base class representing a COM object
	//------------------------------------------------------

	class Object
	{
	public:
		virtual void * AcquireInterface (IID const & iid) = 0;

	private:
		//Object (Object const & p) {}
		void operator = (Object const & p) {}
	};

	//------------------------------------------------------
	// Generic COM object, used to encapsulate any COM object
	// you want.
	//------------------------------------------------------

	class SmartObject: public COM::Object
	{
	public:
		SmartObject (CLSID const & classId, bool running = false);

		//------------------------------------------------------
		// Destructor
		//------------------------------------------------------

		~SmartObject ()
		{
			if (_iUnk)
				_iUnk->Release ();
		}
		void * AcquireInterface (IID const & iid);

	private:
		IUnknown * _iUnk;
		SmartObject (SmartObject const & p) {}
		void operator = (SmartObject const & p) {}
	};

	//------------------------------------------------------
	// Base class representing a COM Interface
	//------------------------------------------------------

	template<class I>class SmartInterface
	{
	public:

		//------------------------------------------------------
		// Destructor.  Release the interface
		//------------------------------------------------------

		~SmartInterface ()
		{
			if (_i)
				_i->Release ();
		}

		//------------------------------------------------------
		// Operator used to access easyli to the "real" COM interface
		//------------------------------------------------------
		I * operator-> () { return _i; }
	protected:

		//------------------------------------------------------
		// Constructor
		//------------------------------------------------------

		SmartInterface () 
			: _i (NULL) 
		{}

		//------------------------------------------------------
		// Constructor.  innitialize the object with an Interface
		//
		// Parameter:
		// 
		// void * i -> Points on an Interface.
		//------------------------------------------------------

		SmartInterface (void * i)
		{
			_i = static_cast<I*> (i);
		}
	
	protected:
		I * _i;

	private:

		SmartInterface (SmartInterface const & p) {}
		void operator = (SmartInterface const & p) {}
	};

	//------------------------------------------------------
	// Generic COM interface.  Obtains an interface from a
	// com object.
	//------------------------------------------------------

	template<class I, IID const * iid>class SmartObjInterface: public SmartInterface<I>
	{
	public:

		//------------------------------------------------------
		// Constructor.  Obtains the interface from a COM object.
		//------------------------------------------------------
		SmartObjInterface (Object & obj)
			: SFace<I> (obj.AcquireInterface (*iid))
		{}

	private:

		SmartObjInterface (SmartObjInterface const & p) {}
		void operator = (SmartObjInterface const & p) {}
	};
}

#endif
