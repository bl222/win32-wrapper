#include "wincolor.h"

//----------------------------------------------------------------------
// Obtains the red, green and blue values of the Win::Color object.
//
// Parameters:
// 
// unsigned short & red   -> Will contain the red value after the call.
// unsigned short & green -> Will contain the green value after the call.
// unsigned short & blue  -> Will contain the blue value after the call.
//----------------------------------------------------------------------

void Win::RGBColor::GetRGB (unsigned short & red, unsigned short & green, unsigned short & blue) const 
{
	red   = GetRed () ;
	green = GetGreen () ;
	blue  = GetBlue () ;
}