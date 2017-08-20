#include "winshellnamespace.h"

//-----------------------------------------------------------------
//  This file contains classes that allow using and navigating the 
//  Shell Namespace
//-----------------------------------------------------------------

#if !defined (WINSHELLNAMESPACE_H)

#define WINSHELLNAMESPACE_H
#include "winshellbase.h"
#include "winexception.h"

namespace ShellAPI
{
	class Desktop: public ShellAPI::SmartInterfacePtr <IShellFolder>
	{
	public:
		Desktop ()
		{
			if (SHGetDesktopFolder (& _p) != NOERROR)
				throw Win::Exception (TEXT("HGetDesktopFolder failed"));
		}
	};

}

#endif