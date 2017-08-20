#include "winmetafile.h"

//--------------------------------------------------------------------
// Transfers ownership of a metafile handle from a 
// Win::EnhanceMetafile::Handle object to another.
// 
// Parameters:
//
// Win::EnhanceMetafile::Handle -> Object giving up its ownership.
//--------------------------------------------------------------------

void Win::EnhanceMetafile::Handle::operator = (Win::EnhanceMetafile::Handle & meta)
{
	if (meta._meta != _meta)
	{
		Free () ; // Free the handle in case it was already used.
		_meta = meta.Release () ;
	}
}

bool Win::EnhanceMetafile::Handle::GetDescription (std::tstring & desc) 
{
	int len = ::GetEnhMetaFileDescription (_meta, 0, NULL) ;

	if (!len)
		return false ;
	
	desc.reserve (len + 1) ;
	desc.resize (len) ;

	return ::GetEnhMetaFileDescription (_meta, len, &desc[0]) != GDI_ERROR ;
					
}

//--------------------------------------------------------------------
// Used by Win::EnhanceMetafile::EnumController to enumerate records.
// 
// Parameters:
//
// HDC hdc                      -> Destination pof the metafile.
// HANDLETABLE * handleTable    -> Points on the table of handle used 
//								   by the metafile
// CONST ENHMETARECORD * record -> Pointson the current record.
// int iHandles                 -> Number of handle in the table.
// LPARAM data                  -> Points on a controller defining the
//								   behavior of the enumeration.
//--------------------------------------------------------------------

int CALLBACK Win::EnhanceMetafile::EnhMetaFileProc (HDC hdc, HANDLETABLE * handleTable, CONST ENHMETARECORD * record, int iHandles, LPARAM data)
{
	Win::Canvas						       canvas (hdc) ;
	Win::EnhanceMetafile::HandleTable      table  (handleTable, iHandles) ;
	Win::EnhanceMetafile::Record           recordCopy (record) ;
	Win::EnhanceMetafile::EnumController * ctrl = reinterpret_cast <Win::EnhanceMetafile::EnumController *> (data) ;

	return ctrl->Enumeration (canvas, table, recordCopy) ;
}

//---------------------------------------------------------------------
// Constructor. Creates an.EnhanceMetafileRecord with nbParam parameters
//
// Parameters:
//
// const int nbParam -> Number of parameters.
//---------------------------------------------------------------------

Win::EnhanceMetafile::Record::Record (const int nbParam)
	: _record (NULL)
{
		// Make sure size is valid.
	assert (nbParam > 0 ) ;

	// Create new ENHMETARECORD.
	_record = reinterpret_cast <ENHMETARECORD *> 
			  (malloc (sizeof (ENHMETARECORD) + (nbParam - 1) * sizeof (DWORD))) ;

	_record->nSize = sizeof (*_record) ;
}

//---------------------------------------------------------------------
// Constructor. Creates an.EnhanceMetafileRecord by copying the data
// from a ENHMETARECORD object.
//
// Parameters:
//
// ENHMETARECORD * record -> Points on the data being copyed..
//---------------------------------------------------------------------

Win::EnhanceMetafile::Record::Record (const ENHMETARECORD * record)
{
	// Makes sure pointer is valid.
	assert (record != NULL) ;

	// Create new ENHMETARECORD.
	_record = reinterpret_cast <ENHMETARECORD *> 
			  (malloc (record->nSize)) ;

	::CopyMemory (_record, record, record->nSize) ;
}

//---------------------------------------------------------------------
// Constructor. Creates an EnhanceMetafileRecord by copying the data
// from another EnhanceMetafileRecord object.
//
// Parameters:
//
// EnhanceMetafileRecord & record -> Object being copyed..
//---------------------------------------------------------------------

Win::EnhanceMetafile::Record::Record (Record & record)
{
	// Makes sure object if valid.
	assert (record._record != NULL) ;

	// Create new ENHMETARECORD.
	_record = reinterpret_cast <ENHMETARECORD *> 
			  (malloc (record._record->nSize)) ;

	::CopyMemory (_record, record._record, record._record->nSize) ;
}
