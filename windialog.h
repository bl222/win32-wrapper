//-----------------------------------------------------------------
//  This file contains classes that allow using dialogs boxes.
//-----------------------------------------------------------------

#if !defined (WINDIALOG_H)

	#define WINDIALOG_H

	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include "win.h"
	#include "winlogdrawingtool.h"
	#include "winupcast.h"
	#include "wincanvas.h"


	namespace Win
	{
		namespace Dialog
		{
			typedef Win::dow::Handle Handle;
			BOOL CALLBACK ModalProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;
			BOOL CALLBACK ModelessProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;

			class Controller ;

			//----------------------------------------------------------------------
			// In traditional Window programming, every dialog box has a 
			// dialog procedure that offers treatment for the messages received by
			// the There.  The dialog procedure  is similar to the window procedure
			// yet different.  Like for window procedure, there are controller 
			// object giving indirect access to predefined dialog procedure.  There 
			// is Win::Dialog::ModalController for modal dialog and 
			// Win:;Dialog::ModelessController for modeless dialog.  
			// Win::Dialog::Controller is used to provide basic functionality to 
			// those 2 classes through inheritance.
			//----------------------------------------------------------------------

			class Controller
			{
				friend BOOL CALLBACK Win::Dialog::ModalProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;
				friend BOOL CALLBACK Win::Dialog::ModelessProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;

			public:

				//----------------------------------------------------------------------
				// Destructor.
				//----------------------------------------------------------------------

				virtual ~Controller () 
				{}

				//-------------------------------------------------------------------
				// The following methods represents various dialog messages.  The
				// return value for each of them has the same meaning unless
				// else wise specified.
				// 
				// Return value:  True is the message is processed, else false.
				//-------------------------------------------------------------------


				//-------------------------------------------------------------------
				// Represents the WM_INITDIALOG message.
				//
				// Return value:  True, the dialog receive default keyboard support 
				//				  from the system, else false.
				//
				// Parameters:
				//
				// Win::Base dlg -> Dialog receiving the message
				//-------------------------------------------------------------------

				virtual bool OnInitDialog (Win::Base dlg) throw ()
				{
					return true ;
				}

				//-------------------------------------------------------------------
				// Represents the WM_COMMAND message.
				//
				// Parameters:
				//
				// Win::Base dlg         -> Handle of the control.
				// const int id         -> Id of the control.
				// const int notifyCode -> Notification code from the control.
				//-------------------------------------------------------------------

				virtual bool OnCommand (const int id, const bool isAccelerator) throw ()
				{return false ;}

				virtual bool OnControl (Win::Base & control, const int id, const int notificationCode) throw ()
				{return false ;}

				//-------------------------------------------------------------------
				// Represents the WM_NOTIFY message.
				//
				// Parameters:
				//
				// Win::Base dlg -> Handle of the control.
				// const int id -> Id of the control.
				// NMHDR * hdr  -> Points on a structure containing various 
				//				   informations.
				//-------------------------------------------------------------------

				virtual bool OnNotify (Win::Base dlg, const int id, NMHDR * hdr) throw ()
				{
					return false ;
				}

				//-------------------------------------------------------------------------
				// Represents the WM_VSCROLL message when it's NOT send by a 
				// scrollbar control.  
				//
				// Parameters:
				//
				// const int thumbPos         -> Position of the thumb of the scrollbar.
				// const int notificationCode -> Represent the type of scrolling being
				//								 requested.
				//-------------------------------------------------------------------------

				virtual bool OnVerticalScroll (const int thumbPos, const int notificationCode) throw ()
				{
					return false ;
				}

				//-------------------------------------------------------------------------
				// Represents the WM_VSCROLL message when it's sent by a 
				// scrollbar control.  
				//
				// Parameters:
				//
				// Win::Base scrollHandle      -> Handle of the scrollbar control.
				// const int scrollId         -> Id of the scrollbar.
				// const int thumbPos         -> Position of the thumb of the scrollbar.
				// const int notificationCode -> Represent the type of scrolling being
				//								 requested.
				//-------------------------------------------------------------------------

				virtual bool OnControlVerticalScroll (Win::Base scrollHandle, const int scrollId, const int thumbPos, const int notificationCode) throw ()
				{
					return false ;
				}

				virtual void EndOk () throw () = 0 ;
				virtual void EndCancel () throw ()= 0 ;

			protected:

				//-------------------------------------------------------------------------
				// Obtains the handle of the dialog.
				//
				// Return value: The dialog handle.
				//-------------------------------------------------------------------------

				Win::Base GetWindow () const throw () 
				{
					return _dlg ; 
				}


			private:

				//-------------------------------------------------------------------------
				// Sets the dialog handle.
				// Parameters:
				//
				// Win::Base dlg -> Handle of the dialog.
				//-------------------------------------------------------------------------

				void SetWindow (Win::Dialog::Handle dlg) 
				{
					_dlg = dlg ; 
				}

			protected:

				Win::Dialog::Handle _dlg ; // Dialog owning the controller.

			} ;

			namespace Modal
			{
				//----------------------------------------------------------------------
				// Win::Dialog::ModalController allow indirect access to the dialog
				// procedure for modal dialog.  Use this to intercept message for a 
				// modal dialog.
				//----------------------------------------------------------------------

				class Controller: public Win::Dialog::Controller
				{
				protected:

					//----------------------------------------------------------------------
					// Use this to destroy the dialog after the user pressed the ok button.
					//----------------------------------------------------------------------

					void EndOk () throw () 
					{ 
						::EndDialog (GetWindow (), 1) ; 
					}

					//----------------------------------------------------------------------
					// Use this to destroy the dialog after the user pressed the cancel
					// button.
					//----------------------------------------------------------------------

					void EndCancel () throw () 
					{
						::EndDialog (GetWindow (), 0) ; 
					}
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::OpenFileName encapsulates an OPENFILENAME struct.  
				// In order to create a Open or Save As common dialog, one of these 
				// object is needed.
				//----------------------------------------------------------------------

				class OpenFileNameData : private OPENFILENAME
				{
				public:

					OpenFileNameData () ;

					//----------------------------------------------------------------------
					// Sets all the data members of the OPENFILENAME struct to 0.
					//----------------------------------------------------------------------

					void Clear ()
					{
						memset (this, 0, sizeof (*this)) ;
					}

					//----------------------------------------------------------------------
					// Sets the owner of the common dialog to be created.
					//
					// Parameters :
					//
					// const HWND owner -> The future owner of the common dialog.
					//----------------------------------------------------------------------

					void SetOwner (const Win::Base owner)
					{
						hwndOwner  = owner ;
					}

					//----------------------------------------------------------------------
					// Sets the instance of the program. Not always necessary
					//
					// Parameters :
					//
					// const HINSTANCE instance -> Instance of the program.
					//----------------------------------------------------------------------

					void SetInstance (const HINSTANCE instance)
					{
						hInstance  = instance ;
					}

					//----------------------------------------------------------------------
					// Sets the NULL terminated filter string.
					//
					// Parameters :
					//
					// TCHAR * str -> The NULL terminated filter string.
					//----------------------------------------------------------------------

					void SetFilter (TCHAR * str)
					{
						lpstrFilter = str ;
					}

					//----------------------------------------------------------------------
					// Sets the index of the selected filter.
					//
					// Parameters :
					//
					// const DWORD index -> The index of the filter to be selected.
					//----------------------------------------------------------------------

					void SetFilterIndex (const DWORD index)
					{
						nFilterIndex = index ;
					}

					//----------------------------------------------------------------------
					// Sets the innitial file name
					//
					// Parameters :
					//
					// const std::tstring str -> The file name.
					//----------------------------------------------------------------------

					void SetFileName (const std::tstring str)
					{
						::lstrcpyn (_fileName, str.c_str (), MAX_PATH) ;
					}

					//----------------------------------------------------------------------
					// Sets the innitial file name title.  Does not include the path.
					//
					// Parameters :
					//
					// const std::tstring str -> The file title.
					//----------------------------------------------------------------------

					void SetFileTitle (const std::tstring str)
					{
						::lstrcpyn (_fileTitle, str.c_str (), MAX_PATH) ;
					}

					//----------------------------------------------------------------------
					// Sets the innitial directory
					//
					// Parameters :
					//
					// const std::tstring str -> The innitial directory.
					//----------------------------------------------------------------------

					void SetInitialDirectory (const std::tstring str)
					{
						lpstrInitialDir   = str.c_str() ;
					}

					//----------------------------------------------------------------------
					// Sets the title of the future common dialog box.
					//
					// Parameters :
					//
					// const std::tstring str -> The desired title.
					//----------------------------------------------------------------------

					void SetTitle (const std::tstring str)
					{
						lpstrTitle = str.c_str() ;
					}

					//----------------------------------------------------------------------
					// Sets the default extention used when the user does not specify one.
					//
					// Parameters :
					//
					// const std::tstring str -> The desired default extention.
					//----------------------------------------------------------------------

					void SetDefaultExtention (const std::tstring str)
					{
						lpstrDefExt = str.c_str() ;
					}

					//----------------------------------------------------------------------
					// Sets the custom data that is pased to the hook procedure (if used).
					//
					// Parameters :
					//
					// const DWORD data -> The custom data
					//----------------------------------------------------------------------

					void SetCustomData (const DWORD data)
					{
						lCustData  = data ;
					}

					//----------------------------------------------------------------------
					// Sets the desired hook procedure.
					//
					// Parameters :
					//
					// const LPOFNHOOKPROC hook -> A pointer on the hook procedure.
					//----------------------------------------------------------------------

					void SetHookProc (const LPOFNHOOKPROC hook)
					{
						lpfnHook = hook ;
					}

					//----------------------------------------------------------------------
					// Sets a dialog template name.
					//
					// Parameters :
					//
					// const std::tstring str -> The template name.
					//----------------------------------------------------------------------

					void SetTemplateName (const std::tstring str)
					{
						lpTemplateName  = str.c_str() ;
					}

					//----------------------------------------------------------------------
					// Resets the Flags.
					//----------------------------------------------------------------------

					void resetFlags ()
					{
						Flags = 0;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ALLOWMULTISELECT Flags
					//----------------------------------------------------------------------

					void SetAllowMultiSelectFlags ()
					{
						Flags |= OFN_ALLOWMULTISELECT ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_CREATEPROMPT Flags
					//----------------------------------------------------------------------

					void SetCreatePromptFlags ()
					{
						Flags |= OFN_ALLOWMULTISELECT ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLEHOOK Flags
					//----------------------------------------------------------------------

					void SetEnableHookFlags ()
					{
						Flags |= OFN_ENABLEHOOK ;
					}
					
					//----------------------------------------------------------------------
					// Sets the OFN_ENABLESIZING Flags
					//----------------------------------------------------------------------

					void SetEnableSizingFlags ()
					{
						Flags |= OFN_ENABLESIZING ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateFlags ()
					{
						Flags |= OFN_ENABLETEMPLATE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATEHANDLE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateHandleFlags ()
					{
						Flags |= OFN_ENABLETEMPLATEHANDLE ;
					}
					
					//----------------------------------------------------------------------
					// Sets the OFN_EXPLORER Flags
					//----------------------------------------------------------------------

					void SetExplorerFlags ()
					{
						Flags |= OFN_EXPLORER ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_EXTENTIONDIFFERENT Flags
					//----------------------------------------------------------------------

					void SetExtentionDifferentFlags ()
					{
						Flags |= OFN_EXTENSIONDIFFERENT ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_FILEMUSTEXIST Flags
					//----------------------------------------------------------------------

					void SetFileMustExistFlags ()
					{
						Flags |= OFN_FILEMUSTEXIST ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_HIDEREADONLY Flags
					//----------------------------------------------------------------------

					void SetHideReadOnlyFlags ()
					{
						Flags |= OFN_HIDEREADONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_LONGNAMES Flags
					//----------------------------------------------------------------------

					void SetLongNamesFlags ()
					{
						Flags |= OFN_LONGNAMES ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOCHANGEDIR Flags
					//----------------------------------------------------------------------

					void SetNoChangeDirFlags ()
					{
						Flags |= OFN_NOCHANGEDIR ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NODEREFERENCELINKS Flags
					//----------------------------------------------------------------------

					void SetNoDereferenceLinksFlags ()
					{
						Flags |= OFN_NODEREFERENCELINKS ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOLONGNAMES Flags
					//----------------------------------------------------------------------

					void SetNoLongNamesFlags ()
					{
						Flags |= OFN_NOLONGNAMES ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NONetworkButton Flags
					//----------------------------------------------------------------------

					void SetNoNetworkButtonFlags ()
					{
						Flags |= OFN_NONETWORKBUTTON ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOREADONLYRETURN Flags
					//----------------------------------------------------------------------

					void SetNoReadOnlyReturnFlags ()
					{
						Flags |= OFN_NOREADONLYRETURN ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOTESTFILECREATE Flags
					//----------------------------------------------------------------------

					void SetNoTestFileCreateFlags ()
					{
						Flags |= OFN_NOTESTFILECREATE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOVALIDATE Flags
					//----------------------------------------------------------------------

					void SetNoValidate ()
					{
						Flags |= OFN_NOVALIDATE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_OVERWRITEPROMPT Flags
					//----------------------------------------------------------------------

					void SetOverWritePromptFlags ()
					{
						Flags |= OFN_OVERWRITEPROMPT ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_PATHMUSTEXIST Flags
					//----------------------------------------------------------------------

					void SetPathMustExistFlags ()
					{
						Flags |= OFN_PATHMUSTEXIST ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_READONLY Flags
					//----------------------------------------------------------------------

					void SetReadOnlyFlags ()
					{
						Flags |= OFN_READONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_SHAREAWARE Flags
					//----------------------------------------------------------------------

					void SetNoShareAwareFlags ()
					{
						Flags |= OFN_SHAREAWARE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_SHOWHELP Flags
					//----------------------------------------------------------------------

					void SetShowHelpFlags ()
					{
						Flags |= OFN_SHOWHELP ;
					}

					//-----------------------------------------------------------
					// Sets the flag  using the WINAPI flags
					//
					// Parameters:
					//
					// UINT flag -> The WINAPI flags.
					//-----------------------------------------------------------

					void SetFlag (DWORD flag)
					{
						Flags = flag ;
					}

					//----------------------------------------------------------------------
					// Obtains the name of the file chosen by the user.
					//
					// Return value: The file name.
					//----------------------------------------------------------------------

					std::tstring GetFileName()
					{
						std::tstring str = _fileName ;
						return str ;
					}

					//----------------------------------------------------------------------
					// Obtains the title of the file chosen by the user.
					//
					// Return value: The file title.
					//----------------------------------------------------------------------

					std::tstring GetFileTitle()
					{
						std::tstring str = _fileTitle ;
						return str ;
					}

				private:
					TCHAR _fileName [MAX_PATH] ; //Contains the name of the choosen file.
					TCHAR _fileTitle [MAX_PATH] ; // Contains the title of the choosen file.
				};

				//---------------------------------------------------------------------------
				// Win::Dialog::Modal::FontInfo encapsulates a LOGFONT structure through private 
				// inheritance. It is use to obtain the information on the font selected by the
				// user with choose font dialog.
				//
				// Data members of LOGFONT:
				//
				// lfHeight                -> Height of the characters.
				// lfWidth                 -> Width of the characters.
				// lfEscapement            -> Angle, in tenth of degree, between the 
				//							  escapement vector and the x-axis.
				// lfOrientation		   -> Orientation of the font.
				// lfWeight                -> Determines if the characters are bold.
				// lfItalic                -> Determines if the characters are italic.
				// lfUnderline             -> Determines if the characters are underlined.
				// lfStrikeOut             -> Determines if the characters are strike out.
				// lfCharSet               -> The char set used by the font.
				// lfOutPrecision          -> The output precision of the font.
				// lfClipPrecision         -> The clipping precision of the font.
				// lfQuality               -> The output quality of the font.
				// lfPitchAndFamily        -> The pitch and the family of the font.
				// lfFaceName[LF_FACESIZE] -> Typeface name of the font.
				//---------------------------------------------------------------------------

				class FontInfo : public Sys::Struct <LOGFONT>
				{
				public:

					//---------------------------------------------------------------------
					// Constructor. Data members are initialized to 0.
					//---------------------------------------------------------------------

					FontInfo () 
						: Sys::Struct <LOGFONT> ()
					{}

					FontInfo (const LOGFONT & font)
						: Sys::Struct <LOGFONT> ()
					{}
		
					//-------------------------------------------------------------------
					// Obtains the height of the font.
					// 
					// Return value:  The lfHeight data member of the LOGFONT structure.
					//-------------------------------------------------------------------

					LONG GetHeight () const 
					{
						return _struct.lfHeight ; 
					}

					//-------------------------------------------------------------------
					// Obtains the width of the font.
					// 
					// Return value:  The lfWidth data member of the LOGFONT structure.
					//-------------------------------------------------------------------

					LONG GetWidth () const 
					{
						return _struct.lfWidth ; 
					}

					//-------------------------------------------------------------------
					// Obtains the escapement of the font.
					// 
					// Return value:  The lfEscapement data member of the LOGFONT 
					// structure.
					//-------------------------------------------------------------------

					LONG GetEscapement () const 
					{
						return _struct.lfEscapement ; 
					}

					//-------------------------------------------------------------------
					// Obtains the orientation of the font.
					// 
					// Return value:  The lfOrientation data member of the LOGFONT 
					// structure.
					//-------------------------------------------------------------------

					LONG GetOrientation () const 
					{
						return _struct.lfOrientation ; 
					}

					//-------------------------------------------------------------------
					// Obtains the weight of the font.
					// 
					// Return value:  The lfWeight data member of the LOGFONT structure.
					//-------------------------------------------------------------------

					LONG GetWeight () const 
					{
						return _struct.lfWeight ; 
					}

					//-------------------------------------------------------------------
					// Determines if the font is italic.
					// 
					// Return value:  True if the font is italic, else false.
					//-------------------------------------------------------------------

					bool IsItalic () const 
					{
						return _struct.lfItalic == TRUE ; 
					}

					//-------------------------------------------------------------------
					// Determines if the font is underlined.
					// 
					// Return value:  True if the font is underlined, else false.
					//-------------------------------------------------------------------

					bool IsUnderline () const 
					{
						return _struct.lfUnderline == TRUE ; 
					}

					//-------------------------------------------------------------------
					// Determines if the font is strike out.
					// 
					// Return value:  True if the font is strike out, else false.
					//-------------------------------------------------------------------

					bool IsStrikeOut () const 
					{
						return _struct.lfStrikeOut == TRUE ; 
					}

					//-------------------------------------------------------------------
					// Obtains the char set of the font.
					// 
					// Return value:  The lfCharSet data member of the LOGFONT structure.
					//-------------------------------------------------------------------

					Win::Font::CharSet GetCharSet () const 
					{
						return static_cast <Win::Font::CharSet> (_struct.lfCharSet) ;
					}

					//-------------------------------------------------------------------
					// Obtains the output precision of the font.
					// 
					// Return value:  The lfOutPrecision data member of the LOGFONT 
					// structure.
					//-------------------------------------------------------------------

					Win::Font::OutPrecis GetOutPrecision () const 
					{
						return static_cast <Win::Font::OutPrecis> (_struct.lfOutPrecision) ; 
					}

					//-------------------------------------------------------------------
					// Obtains the clip precision of the font.
					// 
					// Return value:  The lfClipPrecision data member of the LOGFONT 
					// structure.
					//-------------------------------------------------------------------

					Win::Font::ClipPrecis GetClipPrecision () const 
					{
						return static_cast <Win::Font::ClipPrecis> (_struct.lfClipPrecision) ; 
					}

					//-------------------------------------------------------------------
					// Obtains the quality of the font.
					// 
					// Return value:  The lfQuality data member of the LOGFONT 
					// structure.
					//-------------------------------------------------------------------

					Win::Font::Quality GetQuality () const 
					{
						return static_cast <Win::Font::Quality> (_struct.lfQuality) ; 
					}

					//-------------------------------------------------------------------
					// Obtains the pitch of the font.
					// 
					// Return value:  The low byte of the lfPitchAndFamily data member 
					// of the LOGFONT structure.
					//-------------------------------------------------------------------

					Win::Font::Pitch GetPitch () const 
					{
						return static_cast <Win::Font::Pitch> (_struct.lfPitchAndFamily & 0x03) ;
					}
					
					//-------------------------------------------------------------------
					// Obtains the family of the font.
					// 
					// Return value:  The high byte of the lfPitchAndFamily data member 
					// of the LOGFONT structure.
					//-------------------------------------------------------------------

					Win::Font::Family GetFamily () const 
					{
						return static_cast <Win::Font::Family> (_struct.lfPitchAndFamily & 0xF0) ;
					}

					//-------------------------------------------------------------------
					// Obtains the face name of the font.
					// 
					// Return value:  The lfFaceName data member of the LOGFONT 
					// structure.
					//-------------------------------------------------------------------

					const std::tstring GetFaceName () const 
					{
						return _struct.lfFaceName ;
					} 

					//-------------------------------------------------------------------
					// Changes the height of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG height -> The new height.
					//-------------------------------------------------------------------

					void SetHeight (const LONG height) 
					{
						_struct.lfHeight = height ;
					}

					//-------------------------------------------------------------------
					// Changes the width of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG width -> The new width.
					//-------------------------------------------------------------------

					void SetWidth (const LONG width)  
					{
						_struct.lfWidth = width ;
					}

					//-------------------------------------------------------------------
					// Changes the escapement of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG escapement -> The new escapement.
					//-------------------------------------------------------------------

					void SetEscapement (const LONG escapement) 
					{
						_struct.lfEscapement = escapement ;
					}

					//-------------------------------------------------------------------
					// Changes the orientation of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG orientation -> The new orientation.
					//-------------------------------------------------------------------

					void SetOrientation (const LONG orientation) 
					{
						_struct.lfOrientation = orientation ;
					}

					//-------------------------------------------------------------------
					// Changes the weight of the font that will be created.
					// 
					// Parameters:
					//
					// const LONG weight -> The new weight.
					//-------------------------------------------------------------------

					void SetWeight (const LONG weight) 
					{
						_struct.lfWeight = weight ;
					}

					//-------------------------------------------------------------------
					// Changes the italic of the font that will be created.
					// 
					// Parameters:
					//
					// const bool italic -> If true the font is made italic, else
					//                      the font is made not italic.
					//-------------------------------------------------------------------

					void SetItalic (const bool italic = true) 
					{
						_struct.lfItalic = italic ;
					}

					//-------------------------------------------------------------------
					// Changes the underline of the font that will be created.
					// 
					// Parameters:
					//
					// const bool under -> If true the font is made underline, else
					//                      the font is made not underline.
					//-------------------------------------------------------------------

					void SetUnderline (const bool under = true) 
					{
						_struct.lfUnderline = under ;
					}

					//-------------------------------------------------------------------
					// Makes the Win::Font::Data object strike out or not.
					// 
					// Parameters:
					//
					// const bool strike -> If true the font is made strike out, else
					//                      the font is made not strike out.
					//-------------------------------------------------------------------

					void SetStrikeOut (const bool strike = true) 
					{
						_struct.lfStrikeOut = strike ;
					}

					//-------------------------------------------------------------------
					// Changes the charset of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE charset -> The new char set.
					//-------------------------------------------------------------------

					void SetCharSet (const Win::Font::CharSet charset) 
					{
						_struct.lfCharSet = charset ;
					}

					//-------------------------------------------------------------------
					// Changes the output precision of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE precision -> The new output precision.
					//-------------------------------------------------------------------

					void SetOutPrecision (const Win::Font::OutPrecis precision) 
					{
						_struct.lfOutPrecision = precision ;
					}

					//-------------------------------------------------------------------
					// Changes the clip precision of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE precision -> The new clip precision.
					//-------------------------------------------------------------------

					void SetClipPrecision (const Win::Font::ClipPrecis precision) 
					{
						_struct.lfClipPrecision = precision ;
					}

					//-------------------------------------------------------------------
					// Changes the quality of the font that will be created.
					// 
					// Parameters:
					//
					// const BYTE quality -> The new quality.
					//-------------------------------------------------------------------

					void SetQuality (const Win::Font::Quality quality) 
					{
						_struct.lfQuality = quality ;
					}

					//-------------------------------------------------------------------
					// Changes the pitch of the font that will be created.
					// 
					// Parameters:
					//
					// const Win::Font::Pitch pitch -> The new pitch.
					//-------------------------------------------------------------------

					void SetPitch (const Win::Font::Pitch pitch) 
					{
						_struct.lfPitchAndFamily &= 0xFC ;
						_struct.lfPitchAndFamily |= pitch ;
					}

					//-------------------------------------------------------------------
					// Changes the family of the font that will be created.
					// 
					// Parameters:
					//
					// const Win::Font::Pitch pitch -> The new family.
					//-------------------------------------------------------------------

					void SetFamily (const Win::Font::Family family) 
					{
						_struct.lfPitchAndFamily &= 0x02 ;
						_struct.lfPitchAndFamily |= family ;
					}

					//-------------------------------------------------------------------
					// Changes the face name of the font that will be created.
					// 
					// Parameters:
					//
					// const std::tstring faceName -> The new face name.
					//-------------------------------------------------------------------

					void SetFaceName (const std::tstring faceName) 
					{
						::_tcscpy (_struct.lfFaceName, faceName.c_str ()) ;
					}

					void SetAllData (const std::tstring face, const Win::Font::CharSet charSet, const int height, const int width, const int escapement, const int orientation, 
						     const Win::Font::Weight weight, const bool italic, const bool underline, const bool strikeOut, 
						     const Win::Font::OutPrecis outputPrescision, const Win::Font::ClipPrecis clipPrescision, const Win::Font::Quality quality, 
						     const Win::Font::Pitch pitch, const Win::Font::Family family) ;
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::ChooseFontData encapsulates an CHOOSEFONT struct.  
				// In order to create a font common dialog, one of these object is 
				// needed.
				//----------------------------------------------------------------------

				class ChooseFontData : private CHOOSEFONT
				{
				public:

					ChooseFontData () ;

					//----------------------------------------------------------------------
					// Sets all the data members of the CHOOSEFONT struct to 0.
					//----------------------------------------------------------------------

					void Clear ()
					{
						memset (this, 0, sizeof(*this)) ;
					}

					//----------------------------------------------------------------------
					// Sets the owner of the common dialog to be created.
					//
					// Parameters :
					//
					// const HWND owner -> The future owner of the common dialog.
					//----------------------------------------------------------------------

					void SetOwner (const Win::Base owner)
					{
						hwndOwner  = owner ;
					}

					//----------------------------------------------------------------------
					// Sets the device context of the printer whose font will be listed.
					//
					// Parameters :
					//
					// const HDC hdc -> Device context of the printer.
					//----------------------------------------------------------------------

					void SetHdc (const Win::Canvas & hdc)
					{
						hDC = hdc ;
					}

					//----------------------------------------------------------------------
					// Sets info on the initial font the common dialog will display.
					//
					// Parameters :
					//
					// const Win::LogicalFont & lfont -> Contains info on the initial font.
					//----------------------------------------------------------------------

					void SetInitLogFont (const Win::Dialog::Modal::FontInfo & lfont)
					{
						_font = lfont ;
					}

					//----------------------------------------------------------------------
					// Sets size of the font in tenth of a points.
					//
					// Parameters :
					//
					// const int size -> Size of the font.
					//----------------------------------------------------------------------

					void SetPointSize (const int size)
					{
						iPointSize = size ;
					}

					//----------------------------------------------------------------------
					// Sets the color of the font.
					//
					// Parameters :
					//
					// const Win::Color & color -> Color of the font.
					//----------------------------------------------------------------------

					void SetRGBColor (const Win::Color & color)
					{
						rgbColors = color.GetColorRef() ;
					}

					//----------------------------------------------------------------------
					// Sets the custom data that is pased to the hook procedure (if used).
					//
					// Parameters :
					//
					// const LPARAM data -> The custom data
					//----------------------------------------------------------------------

					void SetCustomData (const LPARAM data)
					{
						lCustData  = data ;
					}

					//----------------------------------------------------------------------
					// Sets the desired hook procedure.
					//
					// Parameters :
					//
					// const LPOFNHOOKPROC hook -> A pointer on the hook procedure.
					//----------------------------------------------------------------------

					void SetHookProc (const LPOFNHOOKPROC hook)
					{
						lpfnHook = hook ;
					}

					//----------------------------------------------------------------------
					// Sets a dialog template name.
					//
					// Parameters :
					//
					// const std::tstring str -> The template name.
					//----------------------------------------------------------------------

					void SetTemplateName (const std::tstring str)
					{
						lpTemplateName  = str.c_str() ;
					}

					//----------------------------------------------------------------------
					// Sets the instance of the program. Not always necessary
					//
					// Parameters :
					//
					// const HINSTANCE instance -> Instance of the program.
					//----------------------------------------------------------------------

					void SetInstance (const HINSTANCE instance)
					{
						hInstance  = instance ;
					}

					//----------------------------------------------------------------------
					// Sets the minimum size that can be selected.
					//
					// Parameters :
					//
					// const int max -> The minimum size.
					//----------------------------------------------------------------------

					void SetMinSize (const int min)
					{
						nSizeMin = min ;
					}

					//----------------------------------------------------------------------
					// Sets the maximum size that can be selected.
					//
					// Parameters :
					//
					// const int max -> The maximum size.
					//----------------------------------------------------------------------

					void SetMaxSize (const int max)
					{
						nSizeMin = max ;
					}

					//----------------------------------------------------------------------
					// Resets the Flags.
					//----------------------------------------------------------------------

					void resetFlags ()
					{
						Flags = 0;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLEHOOK Flags
					//----------------------------------------------------------------------

					void SetEnableHookFlags ()
					{
						Flags |= CF_ENABLEHOOK ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateFlags ()
					{
						Flags |= CF_ENABLETEMPLATE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATEHANDLE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateHandleFlags ()
					{
						Flags |= CF_ENABLETEMPLATEHANDLE ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_APPLY Flags
					//----------------------------------------------------------------------

					void SetApplyFlags ()
					{
						Flags |= CF_APPLY ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_ANSIONLY Flags
					//----------------------------------------------------------------------

					void SetAnsiOnlyFlags ()
					{
						Flags |= CF_ANSIONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_BOTH Flags
					//----------------------------------------------------------------------

					void SetBothFlags ()
					{
						Flags |= CF_BOTH ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_TTONLY Flags
					//----------------------------------------------------------------------

					void SetTrueTypeOnlyFlags ()
					{
						Flags |= CF_TTONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_EFFECTS Flags
					//----------------------------------------------------------------------

					void SetEffectsFlags ()
					{
						Flags |= CF_EFFECTS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_FIXEDPITCHONLY Flags
					//----------------------------------------------------------------------

					void SetFixedPitchOnlyFlags ()
					{
						Flags |= CF_FIXEDPITCHONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_FORCEFONTEXIST Flags
					//----------------------------------------------------------------------

					void SetForceFontExistFlags ()
					{
						Flags |= CF_FORCEFONTEXIST ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_APPLY Flags
					//----------------------------------------------------------------------

					void SetInitLogFontsStructFlags ()
					{
						Flags |= CF_INITTOLOGFONTSTRUCT ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_LIMITSIZE Flags
					//----------------------------------------------------------------------

					void SetLimitSize ()
					{
						Flags |= CF_LIMITSIZE ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOOEMFONTS Flags
					//----------------------------------------------------------------------

					void SetNoOEMFontsFlags ()
					{
						Flags |= CF_NOOEMFONTS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOFACESEL Flags
					//----------------------------------------------------------------------

					void SetNoFaceSelFlags ()
					{
						Flags |= CF_NOFACESEL ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOSCRIPTSEL Flags
					//----------------------------------------------------------------------

					void SetNoScriptSelFlags ()
					{
						Flags |= CF_NOSCRIPTSEL ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOSTYLESEL Flags
					//----------------------------------------------------------------------

					void SetNoStyleSelFlags ()
					{
						Flags |= CF_NOSTYLESEL ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOSIZESEL Flags
					//----------------------------------------------------------------------

					void SetNoSizeSelFlags ()
					{
						Flags |= CF_NOSIZESEL ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOSIMULATIONS Flags
					//----------------------------------------------------------------------

					void SetNoSimulationsFlags ()
					{
						Flags |= CF_NOSIMULATIONS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOVECTORFONTS Flags
					//----------------------------------------------------------------------

					void SetNoVectorFontsFlags ()
					{
						Flags |= CF_NOVECTORFONTS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_NOVERTFONTS Flags
					//----------------------------------------------------------------------

					void SetNoVertFontFlags ()
					{
						Flags |= CF_NOVERTFONTS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_PRINTERFONTS Flags
					//----------------------------------------------------------------------

					void SetPrinterFontsFlags ()
					{
						Flags |= CF_PRINTERFONTS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_SCALABLEONLY Flags
					//----------------------------------------------------------------------

					void SetScalableOnlyFlags ()
					{
						Flags |= CF_SCALABLEONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_SCREENFONTS Flags
					//----------------------------------------------------------------------

					void SetScreenFontsFlags ()
					{
						Flags |= CF_SCREENFONTS ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_SCRIPTONLY Flags
					//----------------------------------------------------------------------

					void SetScriptOnlyFlags ()
					{
						Flags |= CF_SCRIPTSONLY ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_SELECTSCRIPT Flags
					//----------------------------------------------------------------------

					void SetSelectScriptFlags ()
					{
						Flags |= CF_SELECTSCRIPT ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_SHOWHELP Flags
					//----------------------------------------------------------------------

					void SetShowHelpFlags ()
					{
						Flags |= CF_SHOWHELP ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_USESTYLE Flags
					//----------------------------------------------------------------------

					void SetUseStyleFlags ()
					{
						Flags |= CF_USESTYLE ;
					}

					//----------------------------------------------------------------------
					// Sets the CF_WYSIWYG Flags
					//----------------------------------------------------------------------

					void SetWYSIWYGFlags ()
					{
						Flags |= CF_WYSIWYG ;
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
						Flags = flag ;
					}

					//----------------------------------------------------------------------
					// Obtains the data about the selected font.
					//
					// Parameters :
					//
					// Win::LogicalFont & lfont -> Will contain the data on the font.
					//----------------------------------------------------------------------

					void GetLogFont (Win::Dialog::Modal::FontInfo & lfont) const
					{
						lfont = _font ;
					}

					//----------------------------------------------------------------------
					// Obtains the data about the selected font.
					// 
					// Return value:  the data about the selected font.
					//----------------------------------------------------------------------

					Win::Dialog::Modal::FontInfo GetLogFont () const
					{
						return _font;
					}
				private:

					Win::Dialog::Modal::FontInfo _font ; // Will contain the info on the selected font.

				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::ChooseFontData encapsulates an CHOOSECOLOR struct.  
				// In order to create a color common dialog, one of these object is 
				// needed.
				//----------------------------------------------------------------------

				class ChooseColorData : private CHOOSECOLOR
				{
				public:

					ChooseColorData () ;

					//----------------------------------------------------------------------
					// Sets all the data members of the CHOOSEFONT struct to 0.
					//----------------------------------------------------------------------

					void Clear ()
					{
						memset (this, 0, sizeof(*this)) ;
					}

					//----------------------------------------------------------------------
					// Sets the owner of the common dialog to be created.
					//
					// Parameters :
					//
					// const HWND owner -> The future owner of the common dialog.
					//----------------------------------------------------------------------

					void SetOwner (const Win::Base owner)
					{
						hwndOwner  = owner ;
					}

					//----------------------------------------------------------------------
					// Sets the instance of the program. Not always necessary
					//
					// Parameters :
					//
					// const HINSTANCE instance -> Instance of the program.
					//----------------------------------------------------------------------

					void SetInstance (const HWND temp)
					{
						hInstance  = temp ;
					}

					//----------------------------------------------------------------------
					// Sets the initial color selected in the color common dialog.
					//
					// Parameters :
					//
					// const Win::Color & color -> The initial color.
					//----------------------------------------------------------------------

					void SetInitColor (const Win::Color & color)
					{
						rgbResult = color.GetColorRef () ;
					}

					//----------------------------------------------------------------------
					// Sets the custom data that is pased to the hook procedure (if used).
					//
					// Parameters :
					//
					// const LPARAM data -> The custom data
					//----------------------------------------------------------------------

					void SetCustomData (const DWORD data)
					{
						lCustData  = data ;
					}

					//----------------------------------------------------------------------
					// Sets the desired hook procedure.
					//
					// Parameters :
					//
					// const LPOFNHOOKPROC hook -> A pointer on the hook procedure.
					//----------------------------------------------------------------------

					void SetHookProc (const LPOFNHOOKPROC hook)
					{
						lpfnHook = hook ;
					}

					//----------------------------------------------------------------------
					// Sets a dialog template name.
					//
					// Parameters :
					//
					// const std::tstring str -> The template name.
					//----------------------------------------------------------------------

					void SetTemplateName (const std::tstring str)
					{
						lpTemplateName  = str.c_str () ;
					}

					//----------------------------------------------------------------------
					// Resets the Flags.
					//----------------------------------------------------------------------

					void resetFlags ()
					{
						Flags = 0;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLEHOOK Flags
					//----------------------------------------------------------------------

					void SetEnableHookFlags ()
					{
						Flags |= CC_ENABLEHOOK ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateFlags ()
					{
						Flags |= CC_ENABLETEMPLATE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATEHANDLE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateHandleFlags ()
					{
						Flags |= CC_ENABLETEMPLATEHANDLE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ANYCOLOR Flags
					//----------------------------------------------------------------------

					void SetAnyColorFlags ()
					{
						Flags |= CC_ANYCOLOR ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_FULLOPEN Flags
					//----------------------------------------------------------------------

					void SetFullOpenFlags ()
					{
						Flags |= CC_FULLOPEN;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_PREVENTFULLOPEN Flags
					//----------------------------------------------------------------------

					void SetPreventFullOpenFlags ()
					{
						Flags |= CC_PREVENTFULLOPEN ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_RGBINIT Flags
					//----------------------------------------------------------------------

					void SetRGBInitFlags ()
					{
						Flags |= CC_RGBINIT ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_SHOWHELP Flags
					//----------------------------------------------------------------------

					void SetShowHelpFlags ()
					{
						Flags |= CC_SHOWHELP ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_SOLIDCOLOR Flags
					//----------------------------------------------------------------------

					void SetSolidColorFlags ()
					{
						Flags |= CC_SOLIDCOLOR ;
					}

					//-----------------------------------------------------------
					// Sets the flag  using the WINAPI flags
					//
					// Parameters:
					//
					// UINT flag -> The WINAPI flags.
					//-----------------------------------------------------------

					void SetFlag (DWORD flag)
					{
						Flags = flag ;
					}

					//----------------------------------------------------------------------
					// Obtains the color selected by the user.
					//
					// Return value: The selected color.
					//----------------------------------------------------------------------

					Win::RGBColor GetSelectColor () const
					{
						return rgbResult ;
					}

					void GetCustomColor (Win::Color defColor [], const int count = 16) const;

				private:

					COLORREF _defColor [16] ; // Will contain the custom color.
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::Modal allows to create a modal dialog.
				//----------------------------------------------------------------------

				class Creator
				{
				public:

					//----------------------------------------------------------------------
					// .Constructor.  Creates a modal dialog.
					//
					// Parameters:
					//
					// const Win::Base & win        -> Window owning the dialog box.
					// const int id                -> Id of the dialog resource.
					// Win::ModalController & ctrl -> Controller of the dialog box
					//----------------------------------------------------------------------

					Creator (const Win::Base & win, const int id, Win::Dialog::Modal::Controller & ctrl)
					{
						_result = DialogBoxParam (win.GetInstance (), MAKEINTRESOURCE (id), win,
												  (DLGPROC) ModalProc, (LPARAM) & ctrl);
					}

					//----------------------------------------------------------------------
					// Determines if the dialog was closed with the ok or cancel button.
					//
					// Return value:  True if closed with ok, else false.
					//----------------------------------------------------------------------

					bool IsOk () const 
					{ 
						return (_result == -1) ? false : _result != 0 ; 
					}

				private:

					int	_result ; // Used to determine if od or cancel was pressed.
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::OpenFile allows to create a open common dialog.
				//----------------------------------------------------------------------

				class OpenFileCreator
				{
				public:

					//----------------------------------------------------------------------
					// Constructor.  Creates a common open dialog.
					//
					// Parameters:
					//
					// Win::Dialog::OpenFileNameData & data -> Used to create the dialog.
					//----------------------------------------------------------------------

					OpenFileCreator (Win::Dialog::Modal::OpenFileNameData & data)
					{
						_result = ::GetOpenFileName (reinterpret_cast <LPOPENFILENAME> (&data)) ;
					}

					//----------------------------------------------------------------------
					// Determines if the dialog was closed with the ok or cancel button.
					//
					// Return value:  True if closed with ok, else false.
					//----------------------------------------------------------------------

					bool IsOk () const 
					{ 
						return (_result == -1)? false: _result != 0 ; 
					}

				private:

					int	_result ; // Used to determine if od or cancel was pressed.
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::SaveFile allows to create a Save As common dialog.
				//----------------------------------------------------------------------

				class SaveFileCreator
				{
				public:

					//----------------------------------------------------------------------
					// Constructor.  Creates a common save dialog.
					//
					// Parameters:
					//
					// Win::Dialog::OpenFileNameData & data -> Used to create the dialog.
					//----------------------------------------------------------------------

					SaveFileCreator (Win::Dialog::Modal::OpenFileNameData & data)
					{
						_result = ::GetSaveFileName (reinterpret_cast<LPOPENFILENAME> (&data));
					}

					//----------------------------------------------------------------------
					// Determines if the dialog was closed with the ok or cancel button.
					//
					// Return value:  True if closed with ok, else false.
					//----------------------------------------------------------------------

					bool IsOk () const 
					{
						return (_result == -1)? false: _result != 0 ; 
					}

				private:

					int	_result ; // Used to determine if od or cancel was pressed.
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::ChooseColor allows to create a color common dialog.
				//----------------------------------------------------------------------

				class ChooseColorCreator
				{
				public:
					//----------------------------------------------------------------------
					// Constructor.  Creates a common color dialog.
					//
					// Parameters:
					//
					// Win::Dialog::OpenFileNameData & data -> Used to create the dialog.
					//----------------------------------------------------------------------

					ChooseColorCreator (Win::Dialog::Modal::ChooseColorData & data)
					{
						_result = ::ChooseColor (reinterpret_cast<LPCHOOSECOLOR> (&data));
					}

					//----------------------------------------------------------------------
					// Determines if the dialog was closed with the ok or cancel button.
					//
					// Return value:  True if closed with ok, else false.
					//----------------------------------------------------------------------

					bool IsOk () const 
					{ 
						return (_result == -1)? false: _result != 0 ; 
					}

				private:

					int	_result ; // Used to determine if od or cancel was pressed.
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::ChooseFont allows to create a font common dialog.
				//----------------------------------------------------------------------


				class ChooseFontCreator
				{
				public:

					//----------------------------------------------------------------------
					// Constructor.  Creates a common font dialog.
					//
					// Parameters:
					//
					// Win::Dialog::OpenFileNameData & data -> Used to create the dialog.
					//----------------------------------------------------------------------

					ChooseFontCreator (Win::Dialog::Modal::ChooseFontData & data)
					{
						_result = ::ChooseFont (reinterpret_cast<LPCHOOSEFONT> (&data));
					}

					//----------------------------------------------------------------------
					// Determines if the dialog was closed with the ok or cancel button.
					//
					// Return value:  True if closed with ok, else false.
					//----------------------------------------------------------------------

					bool IsOk () const 
					{ 
						return (_result == -1)? false: _result != 0 ; 
					}

				private:

					int	_result ; // Used to determine if od or cancel was pressed.
				} ;
			}

			namespace Modeless
			{
				//----------------------------------------------------------------------
				// Win::Dialog::ModelessController allow indirect access to the dialog
				// procedure for modeless dialog.  Use this to intercept message for a 
				// modeless dialog.
				//----------------------------------------------------------------------

				class Controller: public Win::Dialog::Controller
				{
				protected:

					//----------------------------------------------------------------------
					// Use this to destroy the dialog after the user pressed the ok button.
					//----------------------------------------------------------------------

					void EndOk () throw ()
					{ 
						::DestroyWindow (GetWindow ()) ; 
					}

					//----------------------------------------------------------------------
					// Use this to destroy the dialog after the user pressed the cancel
					// button.
					//----------------------------------------------------------------------

					void EndCancel () throw () 
					{
						::DestroyWindow (GetWindow ()) ; 
					}
				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::FindReplaceData encapsulates an FINDREPLACE struct.  
				// In order to create a find or a replace common dialog, one of these 
				// object is needed.
				//----------------------------------------------------------------------

				class FindReplaceData : private FINDREPLACE
				{
				public:
					
					FindReplaceData () ;

					//----------------------------------------------------------------------
					// Sets all the data members of the CHOOSEFONT struct to 0.
					//----------------------------------------------------------------------

					void Clear ()
					{
						memset (this, 0, sizeof(*this)) ;
					}

					//----------------------------------------------------------------------
					// Sets the owner of the common dialog to be created.
					//
					// Parameters :
					//
					// const HWND owner -> The future owner of the common dialog.
					//----------------------------------------------------------------------

					void SetOwner (const Win::Base owner)
					{
						hwndOwner  = owner ;
					}

					//----------------------------------------------------------------------
					// Sets the instance of the program. Not always necessary
					//
					// Parameters :
					//
					// const HINSTANCE instance -> Instance of the program.
					//----------------------------------------------------------------------

					void SetInstance (const HINSTANCE instance)
					{
						hInstance  = instance ;
					}

					void SetFindWhatLen (const WORD len) ;
					void SetReplaceWidthLen (const WORD len) ;

					//----------------------------------------------------------------------
					// Sets the string to be found or replaced.
					//
					// Parameters :
					//
					// const std::tstring str -> The string tobe found or replace.
					//----------------------------------------------------------------------

					void SetFindString (const std::tstring str)
					{
						_find = str ;
					}

					//----------------------------------------------------------------------
					// Sets the replacement string.
					//
					// Parameters :
					//
					// const std::tstring str -> The replacement string..
					//----------------------------------------------------------------------

					void SetReplaceString (const std::tstring str)
					{
						_replace = str ;
					}

					//----------------------------------------------------------------------
					// Sets the custom data that is pased to the hook procedure (if used).
					//
					// Parameters :
					//
					// const LPARAM data -> The custom data
					//----------------------------------------------------------------------

					void SetCustomData (const LPARAM data)
					{
						lCustData  = data ;
					}

					//----------------------------------------------------------------------
					// Sets the desired hook procedure.
					//
					// Parameters :
					//
					// const LPOFNHOOKPROC hook -> A pointer on the hook procedure.
					//----------------------------------------------------------------------

					void SetHookProc (const LPOFNHOOKPROC hook)
					{
						lpfnHook = hook ;
					}

					//----------------------------------------------------------------------
					// Sets a dialog template name.
					//
					// Parameters :
					//
					// const std::tstring str -> The template name.
					//----------------------------------------------------------------------

					void SetTemplateName (const std::tstring str)
					{
						lpTemplateName  = str.c_str() ;
					}

					//----------------------------------------------------------------------
					// Resets the Flags.
					//----------------------------------------------------------------------

					void resetFlags ()
					{
						Flags = 0;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLEHOOK Flags
					//----------------------------------------------------------------------

					void SetEnableHookFlags ()
					{
						Flags |= FR_ENABLETEMPLATE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_ENABLETEMPLATEHANDLE Flags
					//----------------------------------------------------------------------

					void SetEnableTemplateHandleFlags ()
					{
						Flags |= FR_ENABLETEMPLATEHANDLE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_DIALOGTERM Flags
					//----------------------------------------------------------------------

					void SetDialogTermFlags ()
					{
						Flags |= FR_DIALOGTERM ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_DOWN Flags
					//----------------------------------------------------------------------

					void SetDownFlags ()
					{
						Flags |= FR_DOWN ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_FINDNEXT Flags
					//----------------------------------------------------------------------

					void SetFindNextFlags ()
					{
						Flags |= FR_FINDNEXT ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_HIDEUPDOWN Flags
					//----------------------------------------------------------------------

					void SetHideUpDownFlags ()
					{
						Flags |= FR_HIDEUPDOWN ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_HIDEMATCHCASE Flags
					//----------------------------------------------------------------------

					void SetHideMatchCaseFlags ()
					{
						Flags |= FR_HIDEMATCHCASE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_HIDEWHOLEWORD Flags
					//----------------------------------------------------------------------

					void SetHideWholeWordFlags ()
					{
						Flags |= FR_HIDEWHOLEWORD ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_MATCHCASE Flags
					//----------------------------------------------------------------------

					void SetMatchCaseFlags ()
					{
						Flags |= FR_MATCHCASE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOMATCHCASE Flags
					//----------------------------------------------------------------------

					void SetNoMatchCaseFlags ()
					{
						Flags |= FR_NOMATCHCASE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOUPDOWN Flags
					//----------------------------------------------------------------------

					void SetNoUpDownFlags ()
					{
						Flags |= FR_NOUPDOWN ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_REPLACE Flags
					//----------------------------------------------------------------------

					void SetReplaceFlags ()
					{
						Flags |= FR_REPLACE ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_NOWHOLEWORD Flags
					//----------------------------------------------------------------------

					void SetNoWholeWordFlags ()
					{
						Flags |= FR_NOWHOLEWORD ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_REPLACEALL Flags
					//----------------------------------------------------------------------

					void SetReplaceAllFlags ()
					{
						Flags |= FR_REPLACEALL ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_SHOWHELP Flags
					//----------------------------------------------------------------------

					void SetShowHelpFlags ()
					{
						Flags |= FR_SHOWHELP ;
					}

					//----------------------------------------------------------------------
					// Sets the OFN_WHOLEWORD Flags
					//----------------------------------------------------------------------

					void SetWholeWordFlags ()
					{
						Flags |= FR_WHOLEWORD ;
					}

					//-----------------------------------------------------------
					// Sets the flag  using the WINAPI flags
					//
					// Parameters:
					//
					// UINT flag -> The WINAPI flags.
					//-----------------------------------------------------------

					void SetFlag (DWORD flag)
					{
						Flags = flag ;
					}

					//----------------------------------------------------------------------
					// Obtains the string to be found or replaced.
					//
					// Return value:  The string to be found or replace.
					//----------------------------------------------------------------------

					std::tstring GetFindString () const 
					{
						return _find ;
					}

					//----------------------------------------------------------------------
					// Obtains the replacement string.
					//
					// Return value:  The replacement string.
					//----------------------------------------------------------------------

					std::tstring GetReplaceString () const 
					{
						return _replace ;
					}

					//----------------------------------------------------------------------
					// Determines if the dialog was closed (terminated).
					//
					// Return value:  True if the dialog was closed, else false.
					//----------------------------------------------------------------------

					bool IsDialogTerminated () const 
					{
						return (Flags & FR_DIALOGTERM) != 0 ;
					}

					//----------------------------------------------------------------------
					// Determines if the find next button was pressed.
					//
					// Return value:  True if the find next button was pressed, else false.
					//----------------------------------------------------------------------

					bool IsFindNext () const 
					{
						return (Flags & FR_FINDNEXT) != 0 ;
					}

					//----------------------------------------------------------------------
					// Determines if the replace button was pressed.
					//
					// Return value:  True if the replace button was pressed, else false.
					//----------------------------------------------------------------------

					bool IsReplace () const 
					{
						return (Flags & FR_REPLACE) != 0 ;
					}

					//----------------------------------------------------------------------
					// Determines if the replace all button was pressed.
					//
					// Return value:  True if the replace all button was pressed, else false.
					//----------------------------------------------------------------------

					bool IsReplaceAll () const 
					{
						return (Flags & FR_REPLACEALL) != 0 ;
					}

				private:

					std::tstring _find ; // Will contain the string to be found or replace.
					std::tstring _replace ; // Will contain the replacement string.
				} ;


				typedef Win::dow::Handle Handle;

				//----------------------------------------------------------------------
				// Win::Dialog::Modal allows to create a modeless dialog.
				//----------------------------------------------------------------------

				class Creator
				{
				public:

					Creator (Win::Base parent, const int id)
						: _parent (parent),
						  _id (id)
					{}

					Win::Dialog::Modeless::Handle Create (StrongPointer <Win::Dialog::Modeless::Controller> & ctrl) ;

					//----------------------------------------------------------------------
					// Changes the id of the dialog box that will be created.
					//----------------------------------------------------------------------

					void SetId (const int id)
					{
						_id = id ;
					}

					//----------------------------------------------------------------------
					// Changes the parent of the dialog box that will be created.
					//----------------------------------------------------------------------

					void SetId (const Win::Base parent)
					{
						_parent = parent ;
					}

				private:

					Win::Base _parent ;
					int				 _id ;
				};

				//----------------------------------------------------------------------
				// Win::Dialog::Find allows to create a find common dialog.
				//----------------------------------------------------------------------

				class FindCreator
				{
				public:

					Win::Dialog::Modeless::Handle Create (Win::Dialog::Modeless::FindReplaceData & data) ;

				} ;

				//----------------------------------------------------------------------
				// Win::Dialog::Replace allows to create a replace common dialog.
				//----------------------------------------------------------------------

				class ReplaceCreator
				{
				public:

					Win::Dialog::Modeless::Handle Create (Win::Dialog::Modeless::FindReplaceData & data) ;


				} ;
			}

	

		}
	}

#endif