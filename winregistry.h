//-----------------------------------------------------------
// This file contains classes used to interact with the registry.
//-----------------------------------------------------------

#if !defined (WINREGISTRY_H)

	#define WINREGISTRY_H
	#include "useunicode.h"
	#include "winunicodehelper.h"
	#include "winhandle.h"
	#include "winexception.h"

	namespace Win
	{
		namespace RegistryKey
		{
			//------------------------------------------------------------------
			// Win::Registry::Disposal is used to destroy a Registry key  Used only internaly by winlib, not by users.
			//------------------------------------------------------------------

			struct Disposal
			{
				static void Dispose (HKEY h)
				{
					::RegCloseKey (h) ;
				}
			} ;

			//typedef Sys::Handle <HKEY> Handle ; // Handle for a registry key.
			class Handle  : public Sys::Handle <HKEY>
			{
			public:

				//-------------------------------------------------------------------------
				// Constructor.  Set the REGISTRY key handle.
				//
				// Parameters:
				//
				// const HKEY hwnd -> Used to initialize the key handle encapsulated by 
				//					  the Win::RegistryKey::Handle object.
				//-------------------------------------------------------------------------

				Handle (const HKEY hKey = NULL)
					:  Sys::Handle <HKEY> (hKey)
				{} 

				//-------------------------------------------------------------------------
				// Deletes a subkey of the current key
				//
				// Parameters:
				//
				// const std:string subkey -> Name of the subkey to delete
				//-------------------------------------------------------------------------

				void DeleteSubKey (const std::tstring subkey)
				{
					if (::RegDeleteKey (_h, subkey.c_str ()) != ERROR_SUCCESS)
						throw Win::Exception (TEXT("Error, could not delete a subkey")) ;
				}

				//-------------------------------------------------------------------------
				// Deletes a value of the current key
				//
				// Parameters:
				//
				// const std:string valuename -> Name of the value to delete
				//-------------------------------------------------------------------------

				void DeleteValue (const std::tstring valuename)
				{
					if (::RegDeleteValue (_h, valuename.c_str ()) == ERROR_SUCCESS)
						throw Win::Exception (TEXT("Error, could not delete a value")) ;
				}

				bool EnumSubKey (DWORD index, std::tstring & keyname, std::tstring & classname,FILETIME * time = NULL, DWORD keynameLength = 255, DWORD classnameLength = 255) ;
				bool EnumValue (DWORD index, std::tstring & valuename, DWORD & type, BYTE * data, DWORD & dataLength, DWORD valuenameLength = 255) ;

				//-------------------------------------------------------------------------
				// Force writing attributes of the key to the registry
				//-------------------------------------------------------------------------

				void Flush ()
				{
					if (::RegFlushKey (_h) != ERROR_SUCCESS)
						throw Win::Exception (TEXT("Error, could not flush the key")) ;
				}

				//-------------------------------------------------------------------------
				// Notify about a change of value
				//-------------------------------------------------------------------------


				void NotifyChangeKeyValue (DWORD notifyFilter, bool watchSubtree = false, bool async = false, HANDLE event = NULL)
				{
					if (::RegNotifyChangeKeyValue (_h, watchSubtree, notifyFilter, event, async) != ERROR_SUCCESS)
						throw Win::Exception (TEXT("Error, could not notifyChangeKeyValue")) ;

				}

				void GetInfo (DWORD * nbSubkey, DWORD * maxSubkeyLength, DWORD * maxClassLength, DWORD * nbValues, DWORD * maxValueNameLength, DWORD * maxValueLength, DWORD * securityDescLength, std::tstring * classname, DWORD classnameLength, FILETIME * time = NULL) ;

				//-------------------------------------------------------------------------
				// Obtains the value of the key
				//
				// Parameters:
				//
				// std::tstring valuename -> The name of the value.
				// DWORD * type -> Will contain the type
				// BYTE * data -> Will point on the data
				// DWORD * dataLength -> Will contain the size of the data
				//-------------------------------------------------------------------------

				void GetValue (std::tstring valuename, DWORD * type, BYTE * data, DWORD * dataLength)
				{
					if (::RegQueryValueEx (_h, &valuename [0], NULL, type, data, dataLength) != ERROR_SUCCESS)
						throw Win::Exception (TEXT("Error, could not get a value")) ;
				}

				//-------------------------------------------------------------------------
				// Sets the value of the key
				//
				// Parameters:
				//
				// std::tstring valuename -> The name of the value.
				// DWORD * type -> the type
				// BYTE * data -> point on the data
				// DWORD * dataLength -> size of the data
				//-------------------------------------------------------------------------

				void SetValue (const std::tstring valuename, const DWORD type, const BYTE * data, const DWORD dataLength)
				{
					if (::RegSetValueEx (_h, valuename.c_str (), 0, type, data, dataLength) != ERROR_SUCCESS)
						throw Win::Exception (TEXT("Error, could not set a value")) ;
				}
			} ;

			typedef Sys::StrongHandle <Win::RegistryKey::Handle, Win::RegistryKey::Disposal> StrongHandle ;  // Strong handle owning the registry key.

			//-------------------------------------------------------------------------
			// Used to create a registry key
			//-------------------------------------------------------------------------

			class Creator 
			{
			public:

				static Win::RegistryKey::StrongHandle Create (Win::RegistryKey::Handle hKey, const std::tstring subkey, std::tstring classname, DWORD * disposition = NULL, DWORD options = REG_OPTION_NON_VOLATILE, REGSAM samDesired = KEY_ALL_ACCESS, bool inheritance = false) ;
			} ;

			//-------------------------------------------------------------------------
			// Used to open a registry key
			//-------------------------------------------------------------------------

			class Opener
			{
			public:

				static Win::RegistryKey::StrongHandle Open (Win::RegistryKey::Handle hKey, const std::tstring subkey, REGSAM samDesired = KEY_ALL_ACCESS) ;
			} ;
		}
	}

#endif