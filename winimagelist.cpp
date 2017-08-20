#include "winimagelist.h"

//---------------------------------------------------------------------
// Add a DDB to the image list
//
// Return value:  Index of the added image.
//
// Parameters:
//
// Win::Bitmap::DDB::StrongHandle bitmap -> Handle to the image that is added
// Win::Bitmap::DDB::StrongHandle mask -> Handle to the mask of the image
//---------------------------------------------------------------------
int Win::ImageListHandle::Add (Win::Bitmap::DDB::StrongHandle bitmap, Win::Bitmap::DDB::StrongHandle mask)
{
	int i = ImageList_Add (_h, bitmap, mask) ;

	if (i == -1)
		throw Win::Exception (TEXT("Error, could not add a DDB bitmap to the image list")) ;

	return i ;
}

//---------------------------------------------------------------------
// Add a DIB section to the image list
//
// Return value:  Index of the added image.
//
// Parameters:
//
// Win::Bitmap::DIBSection::StrongHandle bitmap -> Handle to the image that is added
// Win::Bitmap::DIBSection::StrongHandle mask -> Handle to the mask of the image
//---------------------------------------------------------------------

int Win::ImageListHandle::Add (Win::Bitmap::DIBSection::StrongHandle bitmap, Win::Bitmap::DIBSection::StrongHandle mask)
{
	int i = ImageList_Add (_h, bitmap, mask) ;

	if (i == -1)
		throw Win::Exception (TEXT("Error, could not add a DIB section bitmap to the image list")) ;

	return i ;
}

//---------------------------------------------------------------------
// Add a DDB to the image list
//
// Return value:  Index of the added image.
//
// Parameters:
//
// Win::Bitmap::DDB::StrongHandle bitmap -> Handle to the image that is added
// Win::Color & color -> Color that must rendered invisible
//---------------------------------------------------------------------

int Win::ImageListHandle::Add (Win::Bitmap::DDB::StrongHandle bitmap, Win::Color & color)
{
	int i = ImageList_AddMasked (_h, bitmap, color.GetColorRef ()) ;

	if (i == -1)
		throw Win::Exception (TEXT("Error, could not add a DDB bitmap to the masked image list")) ;

	return i ;
}

//---------------------------------------------------------------------
// Add a DIB section to the image list
//
// Return value:  Index of the added image.
//
// Parameters:
//
// Win::Bitmap::DIBSection::StrongHandle bitmap -> Handle to the image that is added
// Win::Color & color -> Color that must rendered invisible
//---------------------------------------------------------------------

int Win::ImageListHandle::Add (Win::Bitmap::DIBSection::StrongHandle bitmap, Win::Color & color)
{
	int i = ImageList_AddMasked (_h, bitmap, color.GetColorRef ()) ;

	if (i == -1)
		throw Win::Exception (TEXT("Error, could not add a DDB bitmap to the masked image list")) ;

	return i ;
}

//---------------------------------------------------------------------
// Add an icon to the image list
//
// Return value:  Index of the added image.
//
// Parameters:
//
// Win::Icon::StrongHandle icon -> Handle of the icon
//---------------------------------------------------------------------

int Win::ImageListHandle::AddIcon (Win::Icon::StrongHandle icon)
{
	int i = ImageList_AddIcon (_h, icon) ;

	if (i == -1)
		throw Win::Exception (TEXT("Error, could not add an icon") );

	return i ;
}

//---------------------------------------------------------------------
// Replace an image from the list by a new DDB
//
//
// Parameters:
//
// int index -> Index of the image to be replaced.
// Win::Bitmap::DDB::StrongHandle bitmap -> Handle to the image that is added
// Win::Color & color -> Color that must rendered invisible
//---------------------------------------------------------------------

void Win::ImageListHandle::Replace (int index, Win::Bitmap::DDB::StrongHandle bitmap, Win::Bitmap::DDB::StrongHandle mask)
{
	int i = ImageList_Replace (_h, index,  bitmap, mask) ;

	if (i == NULL)
		throw Win::Exception (TEXT("Error, could not replace a DDB bitmap to the image list")) ;

}

//---------------------------------------------------------------------
// Replace an image from the list by a new DIBSection
//
// Parameters:
//
// int index -> Index of the image to be replaced.
// Win::Bitmap::DIBSection::StrongHandle bitmap -> Handle to the image that is added
// Win::Color & color -> Color that must rendered invisible
//---------------------------------------------------------------------

void Win::ImageListHandle::Replace (int index, Win::Bitmap::DIBSection::StrongHandle bitmap, Win::Bitmap::DIBSection::StrongHandle mask)
{
	int i = ImageList_Replace (_h, index,  bitmap, mask) ;

	if (i == NULL)
		throw Win::Exception (TEXT("Error, could not replace a DDB bitmap to the image list")) ;
}

//---------------------------------------------------------------------
// Replace an image from the list by a new icon
//
// Return value:  Index of the added image.
//
// Parameters:
//
// int index -> Index of the image to be replaced.
// Win::Icon::StrongHandle -> Handle to the image that is added
// Win::Color & color -> Color that must rendered invisible
//---------------------------------------------------------------------

int Win::ImageListHandle::ReplaceIcon (int index, Win::Icon::StrongHandle icon)
{
	int i = ImageList_ReplaceIcon (_h, index, icon) ;
	
	if (i == -1)
		throw Win::Exception (TEXT("Error, could not replace an image by an icon")) ;

				return i ;
}

//---------------------------------------------------------------------
// Obtains information about a image from the image list
//
// Return value:  The information on the image.
//
// Parameters:
//
// const int index -> Index of the image
//---------------------------------------------------------------------

Win::ImageListData Win::ImageListHandle::GetImageLisData (const int index)
{
	Win::ImageListData  data ;

	if (::ImageList_GetImageInfo (_h, index, data) == NULL)
		throw Win::Exception (TEXT("Error, could not get the image data")) ;

	return data ;
}

//---------------------------------------------------------------------
// Creates an image list
// 
// Return value: Strong handle to the image list
//
// Parameters:
// 
// const int width -> Width of the image
// const int height -> Height of the image
// const int maxgrow -> Maximum automatic growth of the image list
// const UINT flag -> Various options about the image list
//---------------------------------------------------------------------
Win::ImageListStrongHandle Win::ImageListCreator::Create (const int width, const int height, const int initial, const int maxGrow, const UINT flag)
{
	HIMAGELIST h = ImageList_Create (width, height, flag, initial, maxGrow) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not create an image list")) ;

	return Win::ImageListStrongHandle (h) ;
}

//---------------------------------------------------------------------
// Creates a duplicate of an image list that already exists
// 
// Return value: Strong handle to the image list
//
// Parameters:
// 
// Win::ImageListHandle hc -> The image list that is being duplicated.
//---------------------------------------------------------------------
Win::ImageListStrongHandle Win::ImageListCreator::Duplicate (Win::ImageListHandle hc)
{
	HIMAGELIST h = ImageList_Duplicate (hc) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not duplicate an image list")) ;

	return Win::ImageListStrongHandle (h) ;			
}

//---------------------------------------------------------------------
// Merge 2 image list
// 
// Return value: Strong handle to the image list
//---------------------------------------------------------------------

Win::ImageListStrongHandle Win::ImageListCreator::Merge (Win::ImageListHandle h1, const int index1, Win::ImageListHandle h2, const int index2, const int offsetX, const int offsetY)
{
	HIMAGELIST h = ImageList_Merge (h1, index1, h2, index2, offsetX, offsetY) ;

	if (h == NULL)
		throw Win::Exception (TEXT("Error, could not merge an image list")) ;

	return Win::ImageListStrongHandle (h) ;	
			
}