#if !defined (UNICODEHELPER_H)

	#define UNICODEHELPER_H

	//----------------------------------------------------------
	// File defining useful unicode Macro for std::string and WinMain
	// More specifically,it defines macro tstring and tostringstream for string
	// and tWinMain, this makes it easier to write code that will
	// work for both ASCII and Unicode
	//----------------------------------------------------------
	#include "useunicode.h"
	#include <string>
	#include <sstream>

	#if defined (UNICODE) // Set tWinMain, tstring tostringstream, tistringstream and tstringstream to unicode mode

		#define tWinMain wWinMain

		namespace std
		{
			typedef std::wstring        tstring;
			typedef std::wostringstream tostringstream;
			typedef std::wistringstream tistringstream;
			typedef std::wstringstream  tstringstream;
		}

	#else // Set tWinMain, tstring tostringstream, tistringstream and tstringstream to ASCII mode

		#define tWinMain WinMain

		namespace std
		{
			typedef std::string tstring ;
			typedef std::ostringstream tostringstream;
			typedef std::istringstream tistringstream;
			typedef std::stringstream  tstringstream;
		}

	#endif

#endif


