//-----------------------------------------------------------------
//  This file contains classes that allow using static controls.
//-----------------------------------------------------------------

#if !defined (WINCOMMONCONTROL_H)

	#define WINCOMMONCONTROL_H
	#include "useunicode.h"
	#include <windows.h>
	#include <commctrl.h>
	#include "wincontrol.h"

	namespace Win
	{

		//-----------------------------------------------------------------
		//  Not use directly.  Classed inherit from this one to be able to
		//  load various Common Control vrom the DLL.
		//-----------------------------------------------------------------
		class UsingCommonControl
		{
		protected:

			UsingCommonControl (DWORD icc) ;
		} ;

		//-------------------------------------------------------------------------
		// Helper for the various common control creators.
		//-------------------------------------------------------------------------	

		class CommonControlCreator : public ControlCreator
		{
		public:

			//-------------------------------------------------------------------------
			// Constructor.  
			//-------------------------------------------------------------------------

			CommonControlCreator (const std::tstring classname, const Win::Base parent, int id)
				: ControlCreator (classname, parent, id)
			{}



			//-------------------------------------------------------------------------
			// The following methods all serve the same purpose.  They set one of the 
			// style of the future StatusBarHandle control.
			//-------------------------------------------------------------------------

			void SetTopStyle			  () {_style |= CCS_TOP ;}
			void SetLeftStyle			  () {_style |= CCS_LEFT ;}
			void SetRightStyle			  () {_style |= CCS_RIGHT ;}
			void SetBottomStyle			  () {_style |= CCS_BOTTOM ;}
			void SetAdjustableStyle		  () {_style |= CCS_ADJUSTABLE ;}
			void SetNoDividerStyle        () {_style |= CCS_NODIVIDER ;}
			void SetNoMoveXStyle          () {_style |= CCS_NOMOVEX ;}
			void SetNoMoveYStyle          () {_style |= CCS_NOMOVEY ;}
			void SetNoParentAlignStyle    () {_style |= CCS_NOPARENTALIGN ;}
			void SetNoResizeStyle         () {_style |= CCS_NORESIZE ;}
			void SetVertStyle             () {_style |= CCS_VERT ;}


		} ;
	}

#endif