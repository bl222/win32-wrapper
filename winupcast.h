#if !defined (WINUPCAST_H)

	#define WINUPCAST_H
	#include "useunicode.h"
	#include "strongpointer.h"

	//-----------------------------------------------------------------
	// This function allow casting from one type of  auto_ptr from
	// another.
	//-----------------------------------------------------------------

	template <class To, class From>	StrongPointer <To> up_cast (StrongPointer <From> & from)
	{
		return StrongPointer<To> (from.Release ()) ;
	}

#endif