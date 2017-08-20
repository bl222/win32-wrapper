//------------------------------------
// Set to 0 for ASCII, 1 for UNICODE
//------------------------------------
#define ___ENABLEUNICODE___ 0

#if ___ENABLEUNICODE___ == 1

	#define UNICODE
	#define _UNICODE
#endif

//----------------------------------------------------------
// When the compiler see something like this
// #pragma chMSG (fix this later) it outputs a line like this:
// c:\aaa\aaa\aaa.h (33) : Fix this later in the compilation 
// process.  This is a rather useful macro for work in progress
//----------------------------------------------------------
#define chSTR2(x) #x
#define chSTR(x) chSTR2(x)
#define chMSG(desc) message(__FILE__ "(" chSTR(__LINE__) "):" #desc)