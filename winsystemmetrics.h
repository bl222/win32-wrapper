//-------------------------------------------------------------------------
// This file contain a class that encapsulate the GetSystemMetrics function.
//-------------------------------------------------------------------------

#if !defined (WINSYSTEMMETRICS_H)

	#define WINSYSTEMMETRICS_H
	#include "useunicode.h"
	#include <windows.h>

	namespace Win
	{

		//------------------------------------------------------------------
		//  This class encapsulate teh GetSystemMetrics function for "easier"
		// usage.
		//------------------------------------------------------------------
		class SystemMetrics
		{
		public:
		
			enum Boot {Normal = 0, Safe = 1, SafeNetwork = 2} ;

			static Win::SystemMetrics::Boot GetCleanBoot () {return static_cast <Win::SystemMetrics::Boot> (::GetSystemMetrics (SM_CLEANBOOT)) ;}

//	static int GetNbMonitors         () {return ::GetSystemMetrics (SM_CMONITORS) ;} 

			//------------------------------------------------------------------
			//  The following methods all returns a int and take no parameters
			//------------------------------------------------------------------
			static int GetNbMouseButtons     () {return ::GetSystemMetrics (SM_CMOUSEBUTTONS) ;} 
			static int GetBorderWidth        () {return ::GetSystemMetrics (SM_CXBORDER) ;} 
			static int GetBorderHeight       () {return ::GetSystemMetrics (SM_CYBORDER) ;} 
			static int GetCursorWidth        () {return ::GetSystemMetrics (SM_CXCURSOR) ;} 
			static int GetCursorHeight       () {return ::GetSystemMetrics (SM_CYCURSOR) ;}
			static int GetDoubleClickWidth   () {return ::GetSystemMetrics (SM_CXDOUBLECLK) ;} 
			static int GetDoubleClickHeight  () {return ::GetSystemMetrics (SM_CYDOUBLECLK) ;}
			static int GetDragWidth          () {return ::GetSystemMetrics (SM_CXDRAG) ;} 
			static int GetDragHeight         () {return ::GetSystemMetrics (SM_CYDRAG) ;} 
			static int GetEdgeWidth          () {return ::GetSystemMetrics (SM_CXEDGE) ;} 
			static int GetEdgeHeight         () {return ::GetSystemMetrics (SM_CYEDGE) ;} 
			static int GetFixedFrameWidth    () {return ::GetSystemMetrics (SM_CXFIXEDFRAME) ;} 
			static int GetFixedFrameHeight   () {return ::GetSystemMetrics (SM_CYFIXEDFRAME) ;} 
			static int GetFullScreenWidth    () {return ::GetSystemMetrics (SM_CXFULLSCREEN) ;} 
			static int GetFullScreenHeight   () {return ::GetSystemMetrics (SM_CYFULLSCREEN) ;} 
			static int GetHScrollWidth       () {return ::GetSystemMetrics (SM_CXHSCROLL) ;} 
			static int GetHScrollHeight      () {return ::GetSystemMetrics (SM_CYHSCROLL) ;} 
			static int GetHThumbWidth        () {return ::GetSystemMetrics (SM_CXHTHUMB) ;} 
			static int GetIconWidth          () {return ::GetSystemMetrics (SM_CXICON) ;} 
			static int GetIconHeight         () {return ::GetSystemMetrics (SM_CYICON) ;} 
			static int GetIconSpacingWidth   () {return ::GetSystemMetrics (SM_CXICONSPACING) ;} 
			static int GetIconSpacingHeight  () {return ::GetSystemMetrics (SM_CYICONSPACING) ;} 
			static int GetMaximizedWidth     () {return ::GetSystemMetrics (SM_CXMAXIMIZED) ;} 
			static int GetMaximizedHeight    () {return ::GetSystemMetrics (SM_CYMAXIMIZED) ;} 
			static int GetMaxTrackWidth      () {return ::GetSystemMetrics (SM_CXMAXTRACK) ;} 
			static int GetMaxTrackHeight     () {return ::GetSystemMetrics (SM_CYMAXTRACK) ;} 
			static int GetMenuCheckWidth     () {return ::GetSystemMetrics (SM_CXMENUCHECK) ;} 
			static int GetMenuCheckHeight    () {return ::GetSystemMetrics (SM_CYMENUCHECK) ;} 
			static int GetMenuSizeWidth      () {return ::GetSystemMetrics (SM_CXMENUSIZE) ;} 
			static int GetMenuSizeHeight     () {return ::GetSystemMetrics (SM_CYMENUSIZE) ;} 
			static int GetMinWidth           () {return ::GetSystemMetrics (SM_CXMIN) ;} 
			static int GetMinTrackHeight     () {return ::GetSystemMetrics (SM_CYMIN) ;} 
			static int GetMinimizedWidth     () {return ::GetSystemMetrics (SM_CXMINIMIZED) ;} 
			static int GetMinimizedHeight    () {return ::GetSystemMetrics (SM_CYMINIMIZED) ;} 
			static int GetMinSpacingWidth    () {return ::GetSystemMetrics (SM_CXMINSPACING) ;} 
			static int GetMinSpacingHeight   () {return ::GetSystemMetrics (SM_CYMINSPACING) ;} 
			static int GetScreenWidth        () {return ::GetSystemMetrics (SM_CXSCREEN) ;} 
			static int GetScreenHeight       () {return ::GetSystemMetrics (SM_CYSCREEN) ;} 
			static int GetSizeFrameWidth     () {return ::GetSystemMetrics (SM_CXSIZEFRAME) ;} 
			static int GetSizeFrameHeight    () {return ::GetSystemMetrics (SM_CYSIZEFRAME) ;} 
			static int GetSmallIconkWidth    () {return ::GetSystemMetrics (SM_CXSMICON) ;} 
			static int GetSmallIconHeight    () {return ::GetSystemMetrics (SM_CYSMICON) ;} 
			static int GetSmallSizeWidth     () {return ::GetSystemMetrics (SM_CXSMSIZE) ;} 
			static int GetSmallSizHeight     () {return ::GetSystemMetrics (SM_CYSMSIZE) ;} 
//	static int GetVirtualScreenWidth () {return ::GetSystemMetrics (SM_CXVIRTUALSCREEN) ;} 
//	static int GetVirtualScreenHeight() {return ::GetSystemMetrics (SM_CYVIRTUALSCREEN) ;} 
			static int GetVScrollWidth       () {return ::GetSystemMetrics (SM_CXVSCROLL) ;} 
			static int GetVScrollHeight      () {return ::GetSystemMetrics (SM_CYVSCROLL) ;} 
			static int GetVThumbHeight       () {return ::GetSystemMetrics (SM_CYVTHUMB) ;} 
			static int GetCaptionHeight      () {return ::GetSystemMetrics (SM_CYCAPTION) ;} 
			static int GetKanjiWindowHeight  () {return ::GetSystemMetrics (SM_CYKANJIWINDOW) ;} 
			static int GetMenuHeight         () {return ::GetSystemMetrics (SM_CYMENU) ;} 
			static int GetSmallCaptionHeight () {return ::GetSystemMetrics (SM_CYSMCAPTION) ;} 			
//	static int getXCoorVirtualScreen () {return ::GetSystemMetrics (SM_XVIRTUALSCREEN) ;}
//	static int getYCoorVirtualScreen () {return ::GetSystemMetrics (SM_YVIRTUALSCREEN) ;}

			//------------------------------------------------------------------
			//  The following methods all returns a bool and take no parameters
			//------------------------------------------------------------------

			static bool DoubleByteCharSetEnabled () {return ::GetSystemMetrics (SM_DBCSENABLED) == TRUE ;}
			static bool IsDebutVersion           () {return ::GetSystemMetrics (SM_DEBUG) == TRUE ;}
			static bool IsMenuDropRightAlign     () {return ::GetSystemMetrics (SM_MENUDROPALIGNMENT) == TRUE ;}
//	static bool IsMidEasternAbled        () {return ::GetSystemMetrics (SM_MIDEASTERNABLED) == TRUE ;}
			static bool IsMousePresent           () {return ::GetSystemMetrics (SM_MOUSEPRESENT) == TRUE ;}
//	static bool IsMouseWheelPresent      () {return ::GetSystemMetrics (SM_MOUSEWHEELPRESENT) == TRUE;}
			static bool IsNetworkPresent         () {return (::GetSystemMetrics (SM_MOUSEPRESENT) & 0x00000001) != 0 ;}
			static bool IsPenWindows             () {return ::GetSystemMetrics (SM_PENWINDOWS) == TRUE ;}
			static bool IsSecure                 () {return ::GetSystemMetrics (SM_SECURE) == TRUE ;}
//	static bool IsSameDisplayFormat      () {return ::GetSystemMetrics (SM_SAMEDISPLAYFORMAT) == TRUE ;}
			static bool IsShowSound              () {return ::GetSystemMetrics (SM_SHOWSOUNDS) == TRUE ;}
			static bool IsSlowMachine            () {return ::GetSystemMetrics (SM_SLOWMACHINE) == TRUE ;}
			static bool IsMouseButtonSwapped     () {return ::GetSystemMetrics (SM_SWAPBUTTON) == TRUE ;}

		} ;

	}

#endif

