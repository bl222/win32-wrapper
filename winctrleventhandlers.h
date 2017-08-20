//-----------------------------------------------------------------
//  This file contains classes that allow using status bar controls.
//-----------------------------------------------------------------

#if !defined (WINCTRLEVENTHANDLERS_H)

	#define WINCTRLEVENTHANDLERS_H

	#include "wincontroller.h"
	namespace Win
	{
		
		struct ControlEventHandler
		{
			virtual ~ControlEventHandler ()
			{}
		};

		struct BaseButtonEventHandler : public ControlEventHandler
		{
			virtual ~BaseButtonEventHandler ()
			{}
			virtual void CallOnClick (BaseController & ctrl) = 0;
		};

		template <class T>
		struct PushButtonEventHandler : public BaseButtonEventHandler
		{
			typedef  void (T::*OnClickPointer)();
			#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
			typedef typename T ControllerType;
			PushButtonEventHandler()
			{
				OnClick = NULL;
			}
			OnClickPointer OnClick;

			void CallOnClick (BaseController & ctrl)
			{	
				T & caller =  dynamic_cast <T&> (ctrl);
				// \call member funciton pointer here
				//CALL_MEMBER_FN(T, OnClick) (); // Donc Work, check!
				(caller.*OnClick)();
			}
		};
	}

#endif