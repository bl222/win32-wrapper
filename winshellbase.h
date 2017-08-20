//-----------------------------------------------------------------
//  This file contains classes that allow using ShellAPI.
//-----------------------------------------------------------------

#if !defined (WINSHELLAPI_H)

#define WINSHELLAPI_H
	#include "useunicode.h"
#include <shlobj.h>
#include <windows.h>
#include "winunicodehelper.h"
#include "wincombase.h"

namespace ShellAPI
{

	//------------------------------------------------------
	// Base smart pointer for shell object
	//------------------------------------------------------

	template <class T>class SmartInterfacePtr
	{
	public:

		//------------------------------------------------------
		// Destructor.  Free the Shell object.
		//------------------------------------------------------
		~SmartInterfacePtr ()
		{
			Free ();
		}

		//------------------------------------------------------
		// Allow to access the object like throught a normal pointer
		//------------------------------------------------------

		T * operator->() 
		{ 
			return _p; 
		}

		//------------------------------------------------------
		// Allow to access the object like throught a normal pointer
		//------------------------------------------------------

		T const * operator->() const
		{
			return _p; 
		}

		//------------------------------------------------------
		// Allow to access the object like throught a normal pointer
		//------------------------------------------------------

		operator T const * () const 
		{ 
			return _p; 
		}

		//------------------------------------------------------
		// Obrain a reference to the object to allow direct access
		//
		// Return value:  A reference to the object.
		//------------------------------------------------------

		T const & GetAccess () const
		{
			return *_p; 
		}

	protected:

		//------------------------------------------------------
		// Constructor.
		//------------------------------------------------------
		SmartInterfacePtr () 
			: _p (NULL) 
		{}

		//------------------------------------------------------
		// Release the Shell object.
		//------------------------------------------------------
		void Free ()
		{
			if (_p != NULL)
				_p->Release ();
			_p = NULL;
		}

		T * _p;
	private:

		//------------------------------------------------------
		// Dummy members to make sure shell object are only passed by
		// References.
		//------------------------------------------------------
		SmartInterfacePtr (SmartInterfacePtr const & p) {}
		void operator = (SmartInterfacePtr const & p) {}
	};

	//------------------------------------------------------
	// Smart pointer for shell object needing a
	// IMalloc release.
	//------------------------------------------------------

	 template <class T>
	class SmartShellPtr
	{
	public:

		//------------------------------------------------------
		// Destructor.  Free the object.
		//------------------------------------------------------

		~SmartShellPtr ()
		{
			Free ();
			_malloc->Release ();
		}

		//------------------------------------------------------
		// Allow to access the object like throught a normal pointer
		//------------------------------------------------------

		T *  operator->() 
		{ 
			return _p; 
		}

		//------------------------------------------------------
		// Allow to access the object like throught a normal pointer
		//------------------------------------------------------

		T const * operator->() const 
		{ 
			return _p; 
		}

		//------------------------------------------------------
		// Allow to access the object like throught a normal pointer
		//------------------------------------------------------

		operator T const * () const
		{
			return _p; 
		}


		//------------------------------------------------------
		// Obrain a reference to the object to allow direct access
		//
		// Return value:  A reference to the object.
		//------------------------------------------------------

		T const & GetAccess () const
		{
			return *_p; 
		}

	protected:

		//------------------------------------------------------
		// Constructor.
		//------------------------------------------------------
		SmartShellPtr ()
			: _p (NUL) 
		{
			if (SHGetMalloc (& _malloc) == E_FAIL)
				throw Exception TEXT("Couldn't obtain Shell Malloc"); 
		}

		//------------------------------------------------------
		// Release the object
		//------------------------------------------------------

		void Free ()
		{
			if (_p != NULL)
				_malloc->Free (_p);
			_p = NULL;
		}

		T * _p;
		IMalloc *  _malloc;
	private:
		SmartShellPtr (SmartShellPtr const & p) {}
		void operator = (SmartShellPtr const & p) {}
	};


}

#endif