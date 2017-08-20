#if !defined (WINSTRUCT_H)

	#define WINSTRUCT_H
	#include "useunicode.h"
	#include <windows.h>

	namespace Sys
	{
		//------------------------------------------------------------------
		// Sys::Struct is a template used to encapsulate various windows
		// structure.  Users of winlib do not use Sys::Struct directly,
		// but rather the class inheriting from Sys::Struct.
		//------------------------------------------------------------------

		template <class BaseStruct>
		class Struct
		{
		public:

			//------------------------------------------------------------------
			// Sets all the data members of a windows structure to 0.
			//------------------------------------------------------------------

			void Clear ()
			{
				memset (&_struct, 0, sizeof(*this)) ;
			}
	
			//------------------------------------------------------------------
			// Innitialyse a SysStruct descendent with the coresponding
			// classic windows structure.
			//------------------------------------------------------------------

			void operator = (BaseStruct & data)
			{
				if (&_struct != &data)
					::CopyMemory (&_struct, &data, sizeof (data)) ;
			}

			//------------------------------------------------------------------
			// Makes Sys::Struct compatible with the windows API.
			//------------------------------------------------------------------

			operator const BaseStruct * () const
			{
				return &_struct ;
			}

			//------------------------------------------------------------------
			// Makes Sys::Struct compatible with the windows API.
			//------------------------------------------------------------------

			operator BaseStruct * ()
			{
				return &_struct ;
			}

		protected:

			//------------------------------------------------------------------
			// Constructor.
			//------------------------------------------------------------------

			Struct ()
			{
				Clear () ;
			}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Sys::Struct win a classic windows
			// structure.
			//------------------------------------------------------------------

			Struct (const BaseStruct & data)
			{
				::CopyMemory (&_struct, &data, sizeof (data)) ;
			}

			//------------------------------------------------------------------
			// Constructor.  Creates a new Sys::Struct object from another
			// Sys::Struct object.
			//------------------------------------------------------------------

			Struct (const Struct<BaseStruct> & data)
			{
				::CopyMemory (&_struct, &data, sizeof (data)) ;
			}

		protected:

			BaseStruct _struct ;
		} ;

	}

#endif