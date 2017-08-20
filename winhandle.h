#if !defined (WINHANDLE_H)

	#define WINHANDLE_H
	#include "useunicode.h"
	#include <windows.h>

	namespace Sys
	{

		//------------------------------------------------------------------
		// Sys::Handle is a template used to encapsulate various windows
		// handle.  A Sys::Handle object is used praticly the same way as
		// a normal window handle, but there is some extra functionality 
		// added.  A Sys::Handle does not "own" the windows handle, so when
		// a SysHandle object goes out of scope, the windows handle still
		// exist.  Sys::Handle should not be used directly by users, it is 
		// use by winlib to create various type of Handle object like pens,
		// brush, windows, ect.
		//------------------------------------------------------------------
		
		template <class NormalHandle>
		class Handle
		{
		public:
			typedef typename NormalHandle Type ; 

			//------------------------------------------------------------------
			// Constructor.  Creates a Sys::Handle object from a normal windows
			// handle.
			//
			// Parameters:
			// 
			// NormalHandle h -> The normal windows handle used to create the
			//					 object.
			//------------------------------------------------------------------

			Handle (NormalHandle h = NULL)
				: _h (h)
			{}

			//------------------------------------------------------------------
			// Determines if the Sys::Handle object is Null (0).
			// 
			// Return value:  True if the object is Null, else false.
			//------------------------------------------------------------------

			bool IsNull () const 
			{
				return _h == NULL;
			}

			//--------------------------------------------------------------------
			// Converts the Sys::Handle object into a normal windows handle
			// Used for compatibility with the WinAPI.
			//--------------------------------------------------------------------

			operator NormalHandle () const
			{
				return _h ;
			}

			//--------------------------------------------------------------------
			// Gives a new value to the Sys::Handle.  
			// 
			// Parameters:
			// 
			// NormalHandle h -> The new windows handle that will be contained in
			//					 the object.
			//--------------------------------------------------------------------

			void Init (NormalHandle h = NULL)
			{
				_h = h ;
			}

			//--------------------------------------------------------------------
			// Compares the handle contained in the Sys::Handle object and another
			// normal windows handle in order to find out if they are the same.
			// 
			// Return Value:  True if the two handle are the same, else false.
			//
			// Parameters:
			// 
			// NormalHandle h -> The normal windows handle used for comparison
			//--------------------------------------------------------------------

			bool operator == (NormalHandle h)
			{
				return _h == h ;
			}

			//--------------------------------------------------------------------
			// Compares the handle contained in the Sys::Handle object and another
			// normal windows handle in order to find out if they are the different.
			// 
			// Return Value:  True if the two handle are the same, else false.
			//
			// Parameters:
			// 
			// NormalHandle h -> The normal windows handle used for comparison
			//--------------------------------------------------------------------

			bool operator != (NormalHandle h)
			{
				return _h != h ;
			}



		protected:	

			NormalHandle _h ; // Normal windows handle being encapsulated.
		} ; 

		//------------------------------------------------------------------
		// Sys::Disposal is a template used to define how a Sys::StrongHandle
		// object will destroy its normal windows handle.  Used only internaly
		// by winlib, not by users.
		//------------------------------------------------------------------

		template <class BaseHandle>
		struct Disposal
		{
			//------------------------------------------------------------------
			// This method will be implemented to destroy an handle.
			//------------------------------------------------------------------
			static void Dispose  (BaseHandle) ;

		} ;


		
		//------------------------------------------------------------------
		// Sys::StrongHandle is a template used to encapsulate various windows
		// handle.  A Sys::StrongHandle "own" the windows handle, so when
		// a Sys::StrongHandle object goes out of scope, the windows handle
		// is destroyed.  Sys::StrongHandle should not be used directly by 
		// users, it is use by winlib to create various type of Handle object
		// like pens, brush, windows, ect. the class DisposalPolicy in the
		// template is used to define how to destroy the handle.  Users
		// of winlib do not need to worry about it or even know of its existence.
		//------------------------------------------------------------------

		template <class BaseHandle, class DisposalPolicy = Disposal<BaseHandle> >
		class StrongHandle : public BaseHandle
		{
		public:

			//------------------------------------------------------------------
			// Do NOT use this constructor.  Its creates a Sys::StrongHandle
			// from a normal windows handle, thus breaking the resource mangement
			// rules of ownership.  This constructor is used by winlib internally
			// to create various type of StrongHandle.  While it might be better
			// design to have this constructor being private or protected, it 
			// would have made the code for winlib quite more complex, so its
			// remains public but must not be used in your code.
			//
			// Parameters:
			// 
			// NormalHandle h -> The normal windows handle used to create the
			//					 object.
			//------------------------------------------------------------------

			StrongHandle (typename BaseHandle::Type const & h = NULL) 
				: BaseHandle (h)
			{}

			//------------------------------------------------------------------
			// Destructor.  Destroy the windows handle with DisposalPolicy if the
			// handle is not Null.
			//------------------------------------------------------------------

			~StrongHandle ()
			{	
				if (!IsNull ())
					DisposalPolicy::Dispose (_h) ;
			}

			//------------------------------------------------------------------
			// The following constructor and = operator define transfer semantics
			// for the Sys::StrongHandle.  This mean that one Sys::StrongHandle
			// gives up ownership of its windows handle in other to give it
			// to another Sys::StrongHandle object.  This means that there can
			// be only one owner for a normal windows handle, and thus that 
			// handle cannot be destroyed more than one time by accident.
			//------------------------------------------------------------------

			//------------------------------------------------------------------
			// Constructor.  Creates a Sys::StrongHandle object from another
			// Sys::StrongHandle object.
			//
			// Parameters:
			// 
			// StrongHandle & sh -> The object giving up ownership.
			//------------------------------------------------------------------

			StrongHandle (StrongHandle & sh)
				: BaseHandle (sh)
			{
				sh._h = NULL ;
			}

			//------------------------------------------------------------------
			// Transfer a normal windows handle from one Sys::StrongHandle to
			// another Sys::StrongHandle.
			//
			// Parameters:
			// 
			// StrongHandle & sh -> The object giving up ownership.
			//-------------------------------------------------------
			//------------------------------------------------------------------

			StrongHandle & operator = (StrongHandle & sh)
			{

				StrongHandle tmp = sh ;
				std::swap (_h, tmp._h) ;
				return *this ;
			}

			BaseHandle Release ()
			{
				BaseHandle h = _h ;
				_h = NULL ;

				return h ;
			}

			
		
		} ;
	}
#endif