//-----------------------------------------------------------------
// This file contains classes encapsulating metafiles.
//-----------------------------------------------------------------

#if !defined (WINMETAFILE_H)

	#define WINMETAFILE_H
	#include "useunicode.h"
	#include "wincanvas.h"

	

	namespace Win
	{
		namespace EnhanceMetafile
		{
			class Canvas ;
			class Record ;
			
			//---------------------------------------------------------------------------
			// Win::EnhanceMetafile::Data  encapsulates a ENHMETAHEADER structure through 
			// inheritance.  a A Win::EnhanceMetafileHeader object contains various 
			// parameters describing a metafile.
			//
			// Data members of ENHMETAHEADER:
			//
			//	DWORD iType			 -> always 1.
			//	DWORD nSize			 -> Size of the srtucture.
			//	RECTL rclBounds		 -> Bounding rectangle in pixel.
			//	RECTL rclFrame		 -> size of image in 0.01 millimeters.
			//	DWORD dSignature     -> "EMF"
			//	DWORD nVersion		 -> 0x00010000
			//	DWORD nBytes		 -> Size of the file in byte.
			//	DWORD nRecords		 -> Number of records in the file.
			//	WORD  nHandles       -> Number of hndles in the handle table.
			//	WORD  sReserved      -> Reserved.
			//	DWORD nDescription   -> Lenght of the description string.
			//	DWORD offDescription -> Offset of the description string in file.
			//	DWORD nPalEntries    -> Number of palette entries.
			//	SIZEL szlDevice		 -> resolution of the device in pixel
			//	SIZEL szlMillimeters -> resolution of the device in millimeters
			//---------------------------------------------------------------------------

			class Data : public Sys::Struct <ENHMETAHEADER>
			{
			public:

				//---------------------------------------------------------------------
				// Constructor. Data members are initialized to 0.
				//---------------------------------------------------------------------

				Data ()
					: Sys::Struct <ENHMETAHEADER> ()
				{}

				Data (const ENHMETAHEADER data)
					: Sys::Struct <ENHMETAHEADER> (data)
				{}

				//---------------------------------------------------------------------
				// Gets the bounding rectangle in pixel.
				//
				// Return value:  The bounding rectangle.
				//---------------------------------------------------------------------

				Win::Rect GetBoundingRect () const
				{
					return _struct.rclBounds ;
				}

				//---------------------------------------------------------------------
				// Gets the size of the image in 0.01 millimeters..
				//
				// Return value:  The size of the image in a Win::Rext object.
				//---------------------------------------------------------------------

				Win::Rect GetFrameRect () const
				{
					return _struct.rclFrame ;
				}

				//---------------------------------------------------------------------
				// Gets the size of the file in bytes.
				//
				// Return value:  The size of the file.
				//---------------------------------------------------------------------

				DWORD GetFileSize () const
				{
					return _struct.nBytes ;
				}

				//---------------------------------------------------------------------
				// Gets the number of records.
				//
				// Return value:  The number of records.
				//---------------------------------------------------------------------

				DWORD GetRecordsNumber () const
				{
					return _struct.nRecords ;
				}
				
				//---------------------------------------------------------------------
				// Gets the number of handless.
				//
				// Return value:  The number of handles.
				//---------------------------------------------------------------------

				DWORD GetHandlesNumber () const
				{
					return _struct.nHandles ;
				}

				//---------------------------------------------------------------------
				// Gets the lenght of the description string.
				//
				// Return value:  The lenght in caracters..
				//---------------------------------------------------------------------

				DWORD GetDescriptionLenght () const 
				{
					return _struct.nDescription ;
				}

				//---------------------------------------------------------------------
				// Gets the offset of the description string in the file.
				//
				// Return value:  The offset of the string.
				//---------------------------------------------------------------------

				DWORD GetDescriptionOffset () const 
				{
					return _struct.offDescription ;
				}

				//---------------------------------------------------------------------
				// Gets the number of records.
				//
				// Return value:  The number of records.
				//---------------------------------------------------------------------

				DWORD GetPalEntryNumber () const 
				{
					return _struct.nPalEntries ;
				}

				//---------------------------------------------------------------------
				// Gets the resolution of the device in pixel.
				//
				// Return value:  The resolution in pixel.
				//---------------------------------------------------------------------

				Win::Size DevicePixelResolution () const
				{
					return _struct.szlDevice ;
				}

				//---------------------------------------------------------------------
				// Gets the resolution of the device in millimeters.
				//
				// Return value:  The resolution in millimeters.
				//---------------------------------------------------------------------

				Win::Size DeviceMillimeterResolution () const
				{
					return _struct.szlMillimeters ;
				}
			} ;

			//-----------------------------------------------------------------
			// Win::EnhanceMetafile::Handle represents an handle on an enhance 
			// metafile.  Such an handle can be created from loading a metafile 
			// or indirectly by creating a metafile with a 
			// Win::EnhanceMetafile::Canvas object.
			//-----------------------------------------------------------------

			class Handle
			{
				friend class Win::EnhanceMetafile::Canvas ;

			public:

				//-----------------------------------------------------------------
				// Constructor.  Simply set the handle to 0.
				//-----------------------------------------------------------------

				Handle () 
					: _meta (NULL)
				{}

				//------------------------------------------------------------------
				// Constructor.   Loads a metafile.
				// 
				// Parameters:
				//
				// const std::tstring filename -> Name of the file.
				//------------------------------------------------------------------

				Handle (const std::tstring filename)
					: _meta (::GetEnhMetaFile (filename.c_str ()))
				{
					if (!_meta)  // Could not load
						throw Win::Exception (TEXT("Could not load a metafile")) ;
				}

				//------------------------------------------------------------------
				// Transfer constructor.  Transfer ownership of a metafile handle from
				// a old Win::EnhanceMetafile::Handle object to the new 
				// Win::EnhanceMetafile::Handle object.  The old object will be 
				// invalidated.
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle & meta -> The object giving up 
				//										  ownership of
				//										  a metafile handle.
				//------------------------------------------------------------------

				Handle (Win::EnhanceMetafile::Handle & meta)
					: _meta (meta.Release ())
				{}

				//------------------------------------------------------------------
				// Destructor.  Deletes the metafile handle contained in the 
				// Win::EnhanceMetafile::Handle.
				//------------------------------------------------------------------

				~Handle ()
				{
					Free () ;
				}

				//------------------------------------------------------------------
				// Loads a metafile.
				// 
				// Parameters:
				//
				// const std::tstring filename -> Name of the file.
				//------------------------------------------------------------------

				void Load (std::tstring filename)
				{
					Free () ;
					_meta = ::GetEnhMetaFile (filename.c_str ()) ;

					if (!_meta)  // Could not load
						throw Win::Exception (TEXT("Could not load a bitmap from resource")) ;
				}

				void operator = (Win::EnhanceMetafile::Handle & meta) ;

				//------------------------------------------------------------------
				// Obtains information on the metafile.
				// 
				// Return value:  True if the method succeed, else false.
				//
				// Parameters:
				//
				// Win::EnhanceMetafile::Header & info -> Will contain the info on
				//										  the metafile.
				//------------------------------------------------------------------

				bool GetInfo (Win::EnhanceMetafile::Data & info) 
				{
					return ::GetEnhMetaFileHeader (_meta, sizeof (ENHMETAHEADER), 
											reinterpret_cast <ENHMETAHEADER *> (&info)) != 0;
				}

				bool GetDescription (std::tstring & desc) ;

				//--------------------------------------------------------------------
				// Gives up ownership of the metafile handle.  The object becomes 
				// invalid.
				// 
				// Return value :  The metafile handle.
				//--------------------------------------------------------------------

				HENHMETAFILE Release ()
				{
					// The handle encapsulate in the object is set to 0 and
					// its old value is returned.
					HENHMETAFILE h = _meta ;
					_meta           = NULL ;
					return h ;
				}

				//--------------------------------------------------------------------
				// Obtains the handle of the metafile.  Used for compatibility 
				// with the WinAPI.
				//--------------------------------------------------------------------

				operator HENHMETAFILE () const 
				{
					return _meta ;
				}

			private:

				//--------------------------------------------------------------------
				// Deletes the metafile handle.
				//--------------------------------------------------------------------

				void Free ()
				{
					if (_meta) // Makes sure the handle is valid.
						::DeleteEnhMetaFile (_meta) ;
				}

				//-------------------------------------------------------------------
				// Used only by Win::EnhanceMetafile::Handle.
				//-------------------------------------------------------------------

				void SetHandle (HENHMETAFILE meta)
				{
					_meta = meta ;
				}

			private:

				HENHMETAFILE _meta ;
			} ;

			//-------------------------------------------------------------------
			// Win::EnhanceMetafile::Canvas represents a special canvas used to
			// create a metafile.
			//-------------------------------------------------------------------

			class Canvas : public Win::Canvas
			{
			public:

				//-------------------------------------------------------------------
				// Constructor.  Creates a memory metafile.
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle & meta -> Will contain the handle of
				//										  the metafile being created.
				// const HDC refHdc                    -> Reference device.
				// const Win::Rect const * rect        -> Dimention of the picture.
				//-------------------------------------------------------------------

				Canvas (Win::EnhanceMetafile::Handle & meta, const HDC refHdc = NULL, const Win::Rect * const rect = NULL)
					: Win::Canvas (::CreateEnhMetaFile (refHdc, NULL, reinterpret_cast <CONST RECT *> (rect),NULL)),
					  _meta (meta)
				{}

				//-------------------------------------------------------------------
				// Constructor.  Creates a  metafile on disk
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle & meta -> Will contain the handle of
				//										  the metafile being created.
				// const HDC refHdc                    -> Reference device.
				// const Win::Rect const * rect        -> Dimention of the picture.
				// std::tstring filemame				   -> Name for the metafile.
				// std::tstring desc					   -> Description of the metafile.
				//-------------------------------------------------------------------

				Canvas (Win::EnhanceMetafile::Handle & meta, std::tstring filename, std::tstring desc, const HDC refHdc = NULL, const Win::Rect * const rect = NULL)
					: Win::Canvas (::CreateEnhMetaFile (refHdc, filename.c_str (), reinterpret_cast <CONST RECT *> (rect),desc.c_str ())),
					  _meta (meta)
				{
					if (!_h)
						throw Win::Exception (TEXT("Could not create a metafile")) ; 
				}

				//-------------------------------------------------------------------
				// Destructor.  Destroy de device context and innitialise the handle.
				//-------------------------------------------------------------------

				~Canvas ()
				{
					_meta.SetHandle (::CloseEnhMetaFile (_h)) ;
				}

			private:

				Win::EnhanceMetafile::Handle & _meta ; // Will contain the handle of the metafile after the dc is destroyed.
			} ;

			//-------------------------------------------------------------------
			// Win::EnhanceMetafile::Player Allows to display a metafile on a
			// device context.
			//-------------------------------------------------------------------

			class Player
			{
			public:

				//-------------------------------------------------------------------
				// Constructor.
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle meta -> The metafile that will be 
				//										played.
				//-------------------------------------------------------------------

				Player (const HENHMETAFILE meta = NULL)
					: _meta (meta)
				{}

				//-------------------------------------------------------------------
				// Sets the metafile that will be played.
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle meta -> The metafile that will be 
				//										played.
				//-------------------------------------------------------------------

				void SetMetafile (const HENHMETAFILE meta)
				{
					_meta = meta ;
				}

				//----------------------------------------------------------------------
				// Sets the bounding rectangle in which the metafile will be displayed.
				// 
				// Parameters:
				//
				// const Win::Rect & rect -> The bounding rectangle.
				//----------------------------------------------------------------------

				void SetBoundingRect (const Win::Rect & rect)
				{
					_boundingRect = rect ;
				}

				//----------------------------------------------------------------------
				// Sets the bounding rectangle in which the metafile will be displayed.
				// 
				// Parameters:
				//
				// const int top    -> The y coordinate of the top-left corner.
				// const int left   -> The x coordinate of the top-left corner.
				// const int bottom -> The y coordinate of the bottom-right corner.
				// const int right  -> The x coordinate of the bottom-right corner.
				//----------------------------------------------------------------------

				void SetBoundingRect (const int top, const int left, const int bottom, const int right)
				{
					_boundingRect.SetTop    (top) ;
					_boundingRect.SetLeft   (left) ;
					_boundingRect.SetBottom (top) ;
					_boundingRect.SetRight  (right) ;
				}

				//----------------------------------------------------------------------
				// Plays the metafile thus displaying it.
				// 
				// Parameters:
				//
				// const HDC dest ->  Represents the device on which the metafile will be
				//					  displayed.
				//----------------------------------------------------------------------

				void Play (const HDC dest)
				{
					::PlayEnhMetaFile (dest, _meta, reinterpret_cast <CONST RECT *> (&_boundingRect)) ;
				}

			private:

				HENHMETAFILE _meta ; // Metafile that will be played.
				Win::Rect    _boundingRect ; // Bounding rectangle for the metafile.

			} ;

			int CALLBACK EnhMetaFileProc (HDC hdc, HANDLETABLE * handleTable, CONST ENHMETARECORD * record, int iHandles, LPARAM data) ;

			//-------------------------------------------------------------------
			// Win::EnhanceMetafile::HandleTable is only used by 
			// Win::EnhanceMetafile::EnumController with the Enumerate method.
			// Should never be used anywhere else!
			//-------------------------------------------------------------------

			class HandleTable
			{

				friend int CALLBACK Win::EnhanceMetafile::EnhMetaFileProc (HDC hdc, HANDLETABLE * handleTable, CONST ENHMETARECORD * record, int iHandles, LPARAM data) ;
				friend class Win::EnhanceMetafile::Record ;

			public:

				//-------------------------------------------------------------------
				// Gets the type of one of the handle of the table.
				//
				// Parameters:
				//
				// const int noHandle -> Number of the handle (first is 0).
				//-------------------------------------------------------------------

				DWORD GetType (const int noHandle) const
				{
					assert (noHandle >= 0) ;
					return ::GetObjectType (_table->objectHandle [noHandle]) ;
				}

				//-------------------------------------------------------------------
				// Gets info on one of the brush handle.
				//
				// Return value: If the method suceed >0, 0 if the method fail, <0
				// if the "buffer" was too small to contain all the data.
				//
				// Parameters:
				//
				// const int noHandle           -> Number of the handle (first is 0).
				// Win::LogicalBrush & logBrush -> Will contain the info.
				//-------------------------------------------------------------------

				int GetBrushData (const int noHandle, Win::Brush::Data & logBrush) const
				{
					assert (noHandle >= 0) ;
					return ::GetObject (reinterpret_cast <HBRUSH> (_table->objectHandle [noHandle]),
										sizeof(LOGBRUSH), 
										reinterpret_cast <LOGBRUSH *> (&logBrush)) ; 
				}

				//-------------------------------------------------------------------
				// Gets info on one of the pen handle.
				//
				// Return value: If the method suceed >0, 0 if the method fail, <0
				// if the "buffer" was too small to contain all the data.
				//
				// Parameters:
				//
				// const int noHandle        -> Number of the handle (first is 0).
				// Win::LogicalPen & logPen  -> Will contain the info.
				//-------------------------------------------------------------------

				int GetPenData (const int noHandle, Win::Pen::Data & logPen) const
				{
					assert (noHandle >= 0) ;
					return ::GetObject (reinterpret_cast <HPEN> (_table->objectHandle [noHandle]),
										sizeof(LOGPEN), 
										reinterpret_cast <LOGPEN *> (&logPen)) ; 
				}

			/*	//-------------------------------------------------------------------
				// Gets info on one of the extended pen handle.
				//
				// Return value: If the method suceed >0, 0 if the method fail, <0
				// if the "buffer" was too small to contain all the data.
				//
				// Parameters:
				//
				// const int noHandle                -> Number of the handle 
				//										(first is 0).
				// Win::LogicalExtendedPen & logPen  -> Will contain the info.
				//-------------------------------------------------------------------

				int GetExtendedPenData (const int noHandle, Win::ExtendedPen::Data & logPen) const
				{
					assert (noHandle >= 0) ;
					return ::GetObject (reinterpret_cast <HPEN> (_table->objectHandle [noHandle]),
										sizeof(EXTLOGPEN), 
										reinterpret_cast <EXTLOGPEN *> (&logPen)) ; 
				}*/

				//-------------------------------------------------------------------
				// Gets info on one of the font handle.
				//
				// Return value: If the method suceed >0, 0 if the method fail, <0
				// if the "buffer" was too small to contain all the data.
				//
				// Parameters:
				//
				// const int noHandle          -> Number of the handle (first is 0).
				// Win::LogicalFont & logFont  -> Will contain the info.
				//-------------------------------------------------------------------

				int GetFontData (const int noHandle, Win::Font::Data & logFont) const
				{
					assert (noHandle >= 0) ;
					return ::GetObject (reinterpret_cast <HFONT> (_table->objectHandle [noHandle]),
										sizeof(LOGFONT), 
										reinterpret_cast <LOGFONT *> (&logFont)) ; 
				}

				//-------------------------------------------------------------------
				// Gets info on one of the bitmap handle.
				//
				// Return value: If the method suceed >0, 0 if the method fail, <0
				// if the "buffer" was too small to contain all the data.
				//
				// Parameters:
				//
				// const int noHandle              -> Number of the handle (first is 0).
				// Win::LogicalBitmap & logBitmap  -> Will contain the info.
				//-------------------------------------------------------------------

				int GetBitmapData (const int noHandle, Win::Bitmap::DDB::Data & logBitmap) const
				{
					assert (noHandle >= 0) ;
					return ::GetObject (reinterpret_cast <HBITMAP> (_table->objectHandle [noHandle]),
										sizeof(BITMAP), 
										reinterpret_cast <BITMAP *> (&logBitmap)) ; 
				}

				//-------------------------------------------------------------------
				// Gets the number of entries for one of the palette handle.
				//
				// Return value: If the method suceed >0, 0 if the method fail, <0
				// if the "buffer" was too small to contain all the data.
				//
				// Parameters:
				//
				// const int noHandle     -> Number of the handle (first is 0).
				// const int & nbEntries  -> Will contain the info.
				//-------------------------------------------------------------------

				int GetNumPaletteEntries (const int noHandle, int & nbEntries) const
				{
					assert (noHandle >= 0) ;
					return ::GetObject (reinterpret_cast <HPALETTE> (_table->objectHandle [noHandle]),
										sizeof(WORD), 
										reinterpret_cast <WORD *> (&nbEntries)) ; 
				}

				//-------------------------------------------------------------------
				// Gets the number of handle in the table.
				//
				// Return value: The number of table.
				//-------------------------------------------------------------------

				int GetNbHandle () const
				{
					return _nbHandle ;
				}

			private:

				//-------------------------------------------------------------------
				// Constructor.  Create a handle table. Private so its can only be
				// used with Win::EnhanceMetafile::EnumController.
				//
				// Parameters:
				//
				// HANDLETABLE * table -> Points on the handle table.
				// const int nbHandle  -> The number of handle in the table. 
				//-------------------------------------------------------------------

				HandleTable (HANDLETABLE * table, const int nbHandle)
					: _table    (table),
					  _nbHandle (nbHandle)
				{}

			private:

				HANDLETABLE * _table ; // Points on the handle table.
				int           _nbHandle ; // Number of handle in the table.
				
			} ;

			//---------------------------------------------------------------------------
			// Win::EnhanceMetafileRecord encapsulates a ENHMETARECORD structure through 
			// pointer data member.  A Win::LogicalPalette object represents a record in a
			// metafile.
			//
			// Data members of ENHMETARECORD:
			//
			// iType -> Type of the record (EMF_LINE, EMF_RECTANGLE, ect).
			// nSize -> Size of the structure.
			// nParm -> Parameters of the record (variable number).
			//---------------------------------------------------------------------------

			class Record
			{
			public:

				Record (const int nbParam) ;
				Record (const ENHMETARECORD * record) ;
				Record (Record & record) ;

				//---------------------------------------------------------------------
				// Destructor.  Free the memory used by the object.
				//---------------------------------------------------------------------

				~Record ()
				{
					if (_record)  // Must point on a ENHMETARECORD.
						free (_record) ;
				}

				//---------------------------------------------------------------------
				// Gets the type of the record.
				//
				// Return value:  The type of the record.
				//---------------------------------------------------------------------

				DWORD GetType () const
				{
					return _record->iType ;
				}

				//---------------------------------------------------------------------
				// Gets the size of the object.
				//
				// Return value:  The size of the object.
				//---------------------------------------------------------------------

				DWORD GetSize () const 
				{
					return _record->nSize ;
				}

				//---------------------------------------------------------------------
				// Gets one of the parameters of the record..
				//
				// Return value:  The desired parameter.
				//
				// Parameter:
				//
				// const int nbParam -> The desired parameter (first is 0).
				//---------------------------------------------------------------------

				DWORD GetParameter (const int nbParam)
				{
					assert (nbParam >= 0) ;
					return _record->dParm [nbParam] ;
				}

				//---------------------------------------------------------------------
				// Changes the type of the record.
				//
				// Parameter:
				//
				// const int type -> The new type.
				//---------------------------------------------------------------------

				void SetType (const int type)
				{
					_record->iType = type ;
				}

				//---------------------------------------------------------------------
				// Play the record.
				//
				// Parameter:
				//
				// const HDC hdc -> Destination of the metafile.
				// Win::EnhanceMetafile::HandleTable & table -> Handles used by the metafile.
				//---------------------------------------------------------------------

				void Play (const HDC hdc, Win::EnhanceMetafile::HandleTable & table)
				{
					::PlayEnhMetaFileRecord (hdc, table._table, _record, table._nbHandle) ;
				}

			private:

				ENHMETARECORD * _record ; // Points on a ENHMETAFILE.
			} ;


			//-------------------------------------------------------------------
			// Win::EnhanceMetafile::EnumController replaces the metafile 
			// enumeration procedure from traditionnal Windows programming.
			// Simply create a new class inheriting from 
			// Win::EnhanceMetafile::EnumController and implement the Enumeration
			// method.
			//-------------------------------------------------------------------

			class EnumController
			{
				
				friend int CALLBACK Win::EnhanceMetafile::EnhMetaFileProc (HDC hdc, HANDLETABLE * handleTable, CONST ENHMETARECORD * record, int iHandles, LPARAM data) ;

			public:
				//-------------------------------------------------------------------
				// Constructor.
				//-------------------------------------------------------------------

				EnumController ()
				{}

				//-------------------------------------------------------------------
				// Destructor.
				//-------------------------------------------------------------------

				virtual ~EnumController ()
				{}

				//-------------------------------------------------------------------
				// This method define the what happens during enumaration of the 
				// records of a metafile.
				// 
				// Return value:  False to stop enumaration, else false.
				//
				// Parameters:
				//
				// Win::Canvas & canvas						 -> Destination of the 
				//												metafile.
				// Win::EnhanceMetafile::HandleTable & table -> Table of handle used
				//												by the metafile.
				// Win::EnhanceMetafileRecord & record       -> Current record.
				//-------------------------------------------------------------------

				virtual bool Enumeration (Win::Canvas & canvas, Win::EnhanceMetafile::HandleTable & table, Win::EnhanceMetafile::Record & record) throw ()
				{return false ;}
			} ;

			//-------------------------------------------------------------------
			// Win::EnhanceMetafile::Enumerator Allows to enumerate a metafile.
			//-------------------------------------------------------------------

			class Enumerator
			{
			public:

				//-------------------------------------------------------------------
				// Constructor.
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle meta -> The metafile that will be 
				//										enumerated.
				//-------------------------------------------------------------------

				Enumerator (const HENHMETAFILE meta = NULL)
					: _meta (meta)
				{}

				//-------------------------------------------------------------------
				// Sets the metafile that will be enumerated.
				// 
				// Parameters:
				//
				// Win::EnhanceMetafile::Handle meta -> The metafile that will be 
				//										enumerated.
				//-------------------------------------------------------------------

				void SetMetafile (const HENHMETAFILE meta)
				{
					_meta = meta ;
				}

				//----------------------------------------------------------------------
				// Sets the bounding rectangle in which the metafile will be displayed.
				// 
				// Parameters:
				//
				// const Win::Rect & rect -> The bounding rectangle.
				//----------------------------------------------------------------------

				void SetBoundingRect (const Win::Rect & rect)
				{
					_boundingRect = rect ;
				}

				//----------------------------------------------------------------------
				// Sets the bounding rectangle in which the metafile will be displayed.
				// 
				// Parameters:
				//
				// const int top    -> The y coordinate of the top-left corner.
				// const int left   -> The x coordinate of the top-left corner.
				// const int bottom -> The y coordinate of the bottom-right corner.
				// const int right  -> The x coordinate of the bottom-right corner.
				//----------------------------------------------------------------------

				void SetBoundingRect (const int top, const int left, const int bottom, const int right)
				{
					_boundingRect.SetTop    (top) ;
					_boundingRect.SetLeft   (left) ;
					_boundingRect.SetBottom (top) ;
					_boundingRect.SetRight  (right) ;
				}

				//----------------------------------------------------------------------
				// Enumerates the metafile.
				// 
				// Parameters:
				//
				// Win::Canvas & canvas						   -> The destination of the 
				//												  metafile.
				// Win::EnhanceMetafile::EnumController & ctrl -> Controller defining
				//												  the behavior of the
				//												  enumeration.
				//----------------------------------------------------------------------				

				void Enumerate (Win::Canvas & canvas, Win::EnhanceMetafile::EnumController & ctrl)
				{
					::EnumEnhMetaFile (canvas, _meta, EnhMetaFileProc, 
									   reinterpret_cast <Win::EnhanceMetafile::EnumController *> (&ctrl),
									   reinterpret_cast <RECT *> (&_boundingRect)) ;
				}

			private:

				HENHMETAFILE _meta ; // Metafile that will be played.
				Win::Rect    _boundingRect ; // Bounding rectangle for the metafile.
			} ;
		}
	}

#endif