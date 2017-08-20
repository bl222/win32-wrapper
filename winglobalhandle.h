//-------------------------------------------------------------------------
// This file contain a class that encapsulate a windows handle (HWND)
//-------------------------------------------------------------------------

#if !defined (WINGLOBALHANDLE_H)

	#define WINGLOBALHANDLE_H
	#include "useunicode.h"
	#include "winhandle.h"

	namespace Win
	{
		namespace Global
		{
			//------------------------------------------------------------------
			// Win::Global::Disposal is used to destroy a global handle on memory
			// Used only internaly by winlib, not by users.
			//------------------------------------------------------------------

			struct Disposal
			{
				static void Dispose (HGLOBAL h)
				{
					::GlobalFree (h) ;
				}
			} ;

			//------------------------------------------------------------------
			// Represents a handle on a global block of memory.
			//------------------------------------------------------------------

			class Handle : public Sys::Handle <HGLOBAL>
			{
			public:
				
				//------------------------------------------------------------------
				// Represents a handle on a global block of memory.
				//------------------------------------------------------------------

				Handle (HGLOBAL h = NULL)
					: Sys::Handle <HGLOBAL> (h)
				{}

				//------------------------------------------------------------------
				// Obtains the size of the memory block represented by the handle.
				//------------------------------------------------------------------

				unsigned int GetSize ()
				{
					return ::GlobalSize (_h) ;
				}
			} ;

			typedef Sys::StrongHandle <Win::Global::Handle, Win::Global::Disposal> StrongHandle ;  // Strong handle owning the global memory block.

			//------------------------------------------------------------
			// Win::Global::Locker is used lock a global handle
			// thus obtaining a pointer on the data.  When an object is 
			// created, the handle is locked.  When the object is destroy,
			// the handle is unlock.
			//------------------------------------------------------------

			class Lock
			{
			public:

				//------------------------------------------------------------
				// Constructor.  Lock the handle.
				//
				// Parameters:
				//
				// const Win::Global::Handle hGlobal -> Handle that will be locked.
				// void ** data					     -> Will point on the data of the 
				//										handle.
				//------------------------------------------------------------

				Lock (const Win::Global::Handle hGlobal, void ** data)
					: _handle (hGlobal)
				{
					*data = ::GlobalLock (_handle) ;
				}

				//------------------------------------------------------------
				// Destructor.  Unlock the handle
				//------------------------------------------------------------

				~Lock ()
				{
					::GlobalUnlock (_handle) ;
				}

			private:

				Win::Global::Handle _handle ; // The handle that is locked/unlock.

			} ;

			//------------------------------------------------------------------
			// Win::Global::Creator is used to create a global handle.
			//------------------------------------------------------------------

			class Creator
			{
			public:
				//------------------------------------------------------------------
				// constructor.
				//------------------------------------------------------------------

				Creator ()
				{}

				//------------------------------------------------------------------
				// Sets the GMEM_FIXED flag.
				//------------------------------------------------------------------

				void SetFixed ()
				{
					_flag = GMEM_FIXED ;
				}

				//------------------------------------------------------------------
				// Sets the GMEM_MOVEABLE flag.
				//------------------------------------------------------------------

				void SetMoveable ()
				{
					_flag = GMEM_MOVEABLE ;
				}

				//------------------------------------------------------------------
				// Sets the GMEM_SHARE flag.
				//------------------------------------------------------------------

				void SetShare ()
				{
					_flag = GMEM_SHARE ;
				}

				//------------------------------------------------------------------
				// Sets the GMEM_ZEROINIT flag.
				//------------------------------------------------------------------

				void SetZeroInit ()
				{
					_flag = GMEM_ZEROINIT ;
				}

				//-----------------------------------------------------------
				// Sets the flag  using the WINAPI flags
				//
				// Parameters:
				//
				// UINT flag -> The WINAPI flags.
				//-----------------------------------------------------------

				void SetFlag (UINT flag)
				{
					_flag = flag ;
				}

				Win::Global::StrongHandle Create (DWORD size) ;

				static 	Win::Global::StrongHandle Create (DWORD size, UINT flag = GHND) ;


				static Win::Global::Handle CreateClipboardHandle (DWORD size) ;

			private:

				UINT _flag ;

			} ;
		}
	}

#endif