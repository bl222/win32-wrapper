#include "winregistry.h"

//-------------------------------------------------------------------------
// Enumerates all subkeys of the current key
//
// Return value:  True if there are more subkey after this one, else false
//
// Parameters:
//
// DWORD index -> Index of the subkey to enumarate
// std::tstring & keyname -> name of the key
// std::tstring & classname -> Name of the class of the key
// FILETIME * time ->Info on the time at witch the key was written to
// DWORD keynameLength -> Maximum lengthe of std::tstringacter the keyname string can receive
// DWORd classnameLength -> Maximum lenght of std::tstringacter the classname string can receive
//-------------------------------------------------------------------------

bool Win::RegistryKey::Handle::EnumSubKey (DWORD index, std::tstring & keyname, std::tstring & classname,FILETIME * time, DWORD keynameLength, DWORD classnameLength)
{
	keyname.reserve (keynameLength + 1);
	keyname.resize (keynameLength);

	classname.reserve (classnameLength + 1);
	classname.resize (classnameLength);

	int x = ::RegEnumKeyEx (_h, index, &keyname [0], &keynameLength, NULL, &classname [0], &classnameLength, time) ;

	if (x == ERROR_NO_MORE_ITEMS)
		return false;

	if (x != ERROR_SUCCESS)
		throw Win::Exception (TEXT("Error, could not enumerate a subkey")) ;

	return true ;
}

//-------------------------------------------------------------------------
// Enumerates all value of the current key
//
// Return value:  True if there are more value after this one, else false
//
// Parameters:
//
// DWORD index -> Index of the subkey to enumarate
// std::tstring & valuname -> name of the value
// DWORD & type -> Will contain the type of the value
// BYTE * data -> Will point on the data of the value
// DWORD & dataLength -> Number of byte of the data
// DWORd valuenameLength -> Maximum lenght of character the valuename string can receive
//-------------------------------------------------------------------------

bool Win::RegistryKey::Handle::EnumValue (DWORD index, std::tstring & valuename, DWORD & type, BYTE * data, DWORD & dataLength, DWORD valuenameLength)
{
	valuename.reserve (valuenameLength + 1);
	valuename.resize (valuenameLength);



	int x = ::RegEnumValue (_h, index, &valuename [0], &valuenameLength, 0, &type, data, &dataLength) ;

	if (x == ERROR_NO_MORE_ITEMS)
		return false;

	if (x != ERROR_SUCCESS)
		throw Win::Exception (TEXT("Error, could not enumerate a value") );

	return true ;
}


//-------------------------------------------------------------------------
// Obtains the info about a key
//
// Parameters:
//
// DWORD * nbSubkey        -> Will contain the number of subkey.
// DWORD * maxSubkeyLength -> Will contain the maximum length of a subkey name
// DWORD * maxClassLength -> Will contain the longest class.
// DWORD * nbValues -> Will contain the number of values of the key.
// DWORD * maxValueNameLength -> Will contain the max length for a value name.
// DWORD * maxValueLength   -> Will contain the biggest value size possible.
// DWORD * securityDescLength -> Will contai the size of the security descriptor.
// std::tstring * classname -> Will contain the name of the class.
// DWORD * classnameLength -> Will contain the length of the class name.
// FILETIME * time -> Will contain the last time at witch the registry key was modified
//-------------------------------------------------------------------------

void Win::RegistryKey::Handle::GetInfo (DWORD * nbSubkey, DWORD * maxSubkeyLength, DWORD * maxClassLength, DWORD * nbValues, DWORD * maxValueNameLength, DWORD * maxValueLength, DWORD * securityDescLength, std::tstring * classname, DWORD classnameLength, FILETIME * time)
{
	if (classname != NULL)
	{
		classname->reserve (classnameLength + 1);
		classname->resize (classnameLength);
	}

	if (::RegQueryInfoKey (_h, &((*classname)[0]), &classnameLength, 0, nbSubkey, maxSubkeyLength, maxClassLength, nbValues, maxValueNameLength, maxValueLength, securityDescLength, time) != ERROR_SUCCESS)
		throw Win::Exception (TEXT("Error, coud not get information about a key")) ;
}

Win::RegistryKey::StrongHandle Win::RegistryKey::Creator::Create (Win::RegistryKey::Handle hKey, const std::tstring subkey, std::tstring classname, DWORD * disposition, DWORD options, REGSAM samDesired, bool inheritance)
{
	SECURITY_ATTRIBUTES sa ;

	sa.nLength        = sizeof(SECURITY_ATTRIBUTES) ;
	sa.bInheritHandle = inheritance ;

	HKEY h ;

	if (::RegCreateKeyEx (hKey, subkey.c_str (), 0, &classname[0], options, samDesired, &sa, &h, disposition) != ERROR_SUCCESS)
		throw Win::Exception (TEXT("Error, could not create a registry key") );

	return Win::RegistryKey::StrongHandle (h) ;
}

Win::RegistryKey::StrongHandle Win::RegistryKey::Opener::Open (Win::RegistryKey::Handle hKey, const std::tstring subkey, REGSAM samDesired)
{

	HKEY h ;

	if (::RegOpenKeyEx (hKey, subkey.c_str (), 0, samDesired, &h) != ERROR_SUCCESS)
		throw Win::Exception (TEXT("Error, could not create a registry key")) ;

	return Win::RegistryKey::StrongHandle (h) ;
}