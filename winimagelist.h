//-----------------------------------------------------------------
//  This file contains classes that allow using an image list
//-----------------------------------------------------------------

#if !defined (WINIMAGELIST_H)

	#define WINIMAGELIST_H
		#include "useunicode.h"
	#include "wincommoncontrol.h"
	#include "wincontrol.h"
	#include "winicon.h"
	#include "windrawingtool.h"

	namespace Win
	{

		//------------------------------------------------------------------
		// ImageListDisposal is used to destroy a an image list, 
		//  Used only internaly by winlib, not by users.
		//------------------------------------------------------------------

		struct ImageListDisposal
		{
			static void Dispose (HIMAGELIST h)
			{
				::ImageList_Destroy (h) ;
			}
		} ;

		//------------------------------------------------------------------
		// Data structure containing information about an image in a image list
		//------------------------------------------------------------------

		class ImageListData : public Sys::Struct <IMAGEINFO>
		{
		public:

			//---------------------------------------------------------------------
			// Constructor. Data members are initialized to 0.
			//---------------------------------------------------------------------

			ImageListData ()
				: Sys::Struct <IMAGEINFO> ()
			{}

			//---------------
			// Constructor.
			//---------------
			ImageListData (const IMAGEINFO info)
				: Sys::Struct <IMAGEINFO> (info)
			{}

			//---------------------------------------------------------------------
			// Obtains the handle of the image
			//
			// Return value:  The handle of the image from the image list
			//---------------------------------------------------------------------

			Win::Bitmap::DDB::Handle GetBitmapHandle()
			{
				return _struct.hbmImage ;
			}

			//---------------------------------------------------------------------
			// Obtains the handle of the mask of the image
			//
			// Return value:  The handle of the mask of the image from the image list
			//---------------------------------------------------------------------

			Win::Bitmap::DDB::Handle GetMaskHandle()
			{
				return _struct.hbmMask ;
			}

			//---------------------------------------------------------------------
			// Obtains a rectangle containing the coordiantes of the image
			//
			// Return value:  A Win::Rect object.
			//---------------------------------------------------------------------

			Win::Rect GetRect ()
			{
				return _struct.rcImage ;
			}
		} ;

		//---------------------------------------------------------------------
		// Object represents a weak handle to an imagle list.
		//---------------------------------------------------------------------

		class ImageListHandle : public Sys::Handle <HIMAGELIST>
		{
		public:

			//---------------------------------------------------------------------
			// Constructor
			//---------------------------------------------------------------------

			ImageListHandle (HIMAGELIST h = NULL)
				: Sys::Handle <HIMAGELIST> (h)
			{}

			int Add (Win::Bitmap::DDB::StrongHandle bitmap, Win::Bitmap::DDB::StrongHandle mask = NULL) ;
			int Add (Win::Bitmap::DIBSection::StrongHandle bitmap, Win::Bitmap::DIBSection::StrongHandle mask = NULL) ;
			int Add (Win::Bitmap::DDB::StrongHandle bitmap, Win::Color & color) ;
			int Add (Win::Bitmap::DIBSection::StrongHandle bitmap, Win::Color & color) ;
			int AddIcon (Win::Icon::StrongHandle icon) ;
			void Replace (int index, Win::Bitmap::DDB::StrongHandle bitmap, Win::Bitmap::DDB::StrongHandle mask = NULL);
			void Replace (int index, Win::Bitmap::DIBSection::StrongHandle bitmap, Win::Bitmap::DIBSection::StrongHandle mask = NULL) ;
			int ReplaceIcon (int index, Win::Icon::StrongHandle icon) ;

			//---------------------------------------------------------------------
			// Sets the size of the images contained in the image list.
			//
			// Parameters:
			//
			// const int width -> new width of the images.
			// const int height -> new height of the images.
			//---------------------------------------------------------------------

			void SetImageSize (const int width, const int height)
			{
				if (ImageList_SetIconSize (_h, width, height) == 0)
					throw Win::Exception (TEXT("Error, could not set the size of the images in the image list")) ;
			}

			//---------------------------------------------------------------------
			// Changes the number of images in the images list
			//
			// Parameters:
			//
			// const int size -> The new size
			//---------------------------------------------------------------------

			void Resize (const int size)
			{
				if (ImageList_SetImageCount (_h,size) == 0)
					throw Win::Exception (TEXT("Error, could not resize the image list")) ;
			}

			//---------------------------------------------------------------------
			// Sets one of the images as an overlay image
			//
			// Parameters:
			//
			// const int indexImage -> Index of the image that will be overlay
			// const int indexOverlay -> Index of the now overlay (1 to 4)
			//---------------------------------------------------------------------

			void SetOverlayImage (const int indexImage, const int indexOverlay)
			{
				if (ImageList_SetOverlayImage (_h, indexImage, indexOverlay))
					throw Win::Exception (TEXT("Error, could not set an overlay image in the image list")) ;
			}

			//---------------------------------------------------------------------
			// Sets the invisible color of the image
			//
			// Parameters:
			//
			// Win::Color color -> The new color
			//---------------------------------------------------------------------

			void SetBackgroundColor (Win::Color color) 
			{
				if (ImageList_SetBkColor (_h, color.GetColorRef ()))
					throw Win::Exception (TEXT("Error, could not set the background color")) ;
			}

			//---------------------------------------------------------------------
			// Gets the invisible color of the image
			//
			// return value: The backgroun color
			//---------------------------------------------------------------------

			Win::Color GetBackgroundColor ()
			{
				return ImageList_GetBkColor (_h) ;
			}


			
			//---------------------------------------------------------------------
			// Copy an image of an image list
			//
			// Parameters:
			//
			// const int indexDest -> Where the image will be copied
			// const int index -> The image that will be copied
			//---------------------------------------------------------------------

			void Copy (const int indexDest, const int indexSource)
			{
				if (ImageList_Copy (_h, indexDest, _h, indexSource,ILCF_MOVE) == 0)
					throw Win::Exception (TEXT("Error, could not copy the image")) ;
			}

			//---------------------------------------------------------------------
			// Swap 2 images in the image list
			//
			// Parameters:
			//
			// const int indexDest -> Index of the first image to be swapped
			// const int index -> Index of the second image to be swapped
			//---------------------------------------------------------------------

			void Swap (const int indexDest, const int indexSource)
			{
				if (ImageList_Copy (_h, indexDest, _h, indexSource,ILCF_SWAP) == 0)
					throw Win::Exception (TEXT("Error, could not swap the image")) ;
			}

			//---------------------------------------------------------------------
			// Obtains an icon from the image list.
			//
			// Return value:  An icon handle.
			// Parameters:
			//
			// const int indexDest -> Where the image will be copied
			// const int index -> The image that will be copied
			//---------------------------------------------------------------------

			Win::Icon::StrongHandle GetIcon (int index, UINT flag)
			{
				return Win::Icon::StrongHandle (ImageList_GetIcon (_h, index, flag)) ;
			}

			//---------------------------------------------------------------------
			// Gets the size of the images in the list
			//
			// Parameters:
			//
			// int & width -> Will contain the width of the images
			// int & height -> Will contain the height of the images
			//---------------------------------------------------------------------

			void GetIconSize (int & width, int & height) 
			{
				if (ImageList_GetIconSize (_h, &width, &height) == 0)
					throw Win::Exception (TEXT("Error, could not get the size of the images in the image list")) ;
			}

			//---------------------------------------------------------------------
			// Obtains the number of images in the image list.
			//
			// Return value:  The number of images.
			//---------------------------------------------------------------------

			int GetNbImage ()
			{
				return ImageList_GetImageCount (_h) ;
			}

			//---------------------------------------------------------------------
			// Removes an image from the image list.
			//
			// Parameters:
			//
			// const int index -> Index of the image to be removed.
			//---------------------------------------------------------------------

			void RemoveImage (const int index)
			{
				if (ImageList_Remove (_h, index) == 0)
					throw Win::Exception (TEXT("Error, could not remove a image from the image list")) ;
			}

			//---------------------------------------------------------------------
			// Removes all images
			//---------------------------------------------------------------------

			void RemoveAllImages ()
			{
				if (ImageList_Remove (_h, -1) == 0)
					throw Win::Exception (TEXT("Error, could not remove all images from the image list")) ;
			}

			//---------------------------------------------------------------------
			// Obtains information about a image from the image list
			//
			// Parameters:
			//
			// const int index -> Index of the image
			// Win::ImageListData -> Will contain the information of the image.
			//---------------------------------------------------------------------

			void GetImageListData(const int index, Win::ImageListData & data)
			{
				if (::ImageList_GetImageInfo (_h, index, data) == 0)
					throw Win::Exception (TEXT("Error, could not get the image data")) ;
			}

			Win::ImageListData GetImageLisData (const int index) ;

		} ;

		// Strong handle to an image list
		typedef Sys::StrongHandle <Win::ImageListHandle, Win::ImageListDisposal> ImageListStrongHandle ;

		//---------------------------------------------------------------------
		// Object allowing to drag an image from an image list.
		//---------------------------------------------------------------------

		class ImageListDragger 
		{
		public:

			//---------------------------------------------------------------------
			// Constructor.
			//
			// Parameters:
			//
			// Win::Base hwnd -> Handle to the window on witch the drawing occurs
			// Win::ImageListHandle h -> Handle to an image list
			// const int index -> index of the image
			// const int xHotspot -> x point of the hotspot
			// const int yHotspot -> y point of the hotspot
			//---------------------------------------------------------------------

			ImageListDragger ( Win::Base hwnd, Win::ImageListHandle h,const int index, const int xHotspot, const int yHotspot)
				: _hwnd (hwnd)
			{
				::ImageList_BeginDrag (h, index, xHotspot, yHotspot) ;
			}

			//---------------------------------------------------------------------
			// Destructor
			//---------------------------------------------------------------------

			~ImageListDragger ()
			{
				::ImageList_EndDrag () ;
			}

			//---------------------------------------------------------------------
			// Start a drag operation
			//
			// Parameters:
			//
			// const int x -> The x coordinate were the drag begin
			// const int y -> The y coordinate were the drag begin
			//---------------------------------------------------------------------

			void EnterDrag (const int x, const int y)
			{
				if (ImageList_DragEnter (_hwnd, x, y) == 0)
					throw Win::Exception (TEXT("Error, could not enter dragging operation")) ;
			}

			//---------------------------------------------------------------------
			// Stop the dragging operation
			//---------------------------------------------------------------------

			void LeaveDrag ()
			{
				if (ImageList_DragLeave(_hwnd) == 0)
					throw Win::Exception (TEXT("Error, could not enter dragging operation")) ;
			}

			//---------------------------------------------------------------------
			// Move the dragging image.
			//
			// Parameters:
			//
			// const int x -> The new x coordinate
			// const int y -> The new y coordinate
			//---------------------------------------------------------------------

			void Move (const int x, const int y)
			{
				if (ImageList_DragMove(x, y) == 0)
					throw Win::Exception (TEXT("Error, could not move the dragged image")) ;
			}

			//---------------------------------------------------------------------
			// Show or hide the dragged image
			//
			// Parameters:
			//
			// bool show -> True must show the image, false must hide it
			//---------------------------------------------------------------------

			void ShowNoLock (bool show = true)
			{
				if (ImageList_DragShowNolock(show) == 0)
					throw Win::Exception (TEXT("Error, could not show/hide the dragged image")) ;
			}

			//---------------------------------------------------------------------
			// Gets the handle, position and hotspot of the dragged image
			//
			// Return value:  Handle of the dragged image
			//
			// Parameters:
			//
			// Win::Point * pos -> Will contain the position
			// Win::Point * hotspot -> Will contain the hotspot
			//---------------------------------------------------------------------
			Win::ImageListHandle GetDragImage (Win::Point * pos = NULL, Win::Point * hotspot = NULL)
			{
				if (ImageList_GetDragImage(reinterpret_cast <POINT *> (pos), reinterpret_cast <POINT *> (hotspot)) == 0)
					throw Win::Exception (TEXT("Error, could not get the dragged image")) ;
			}

			//---------------------------------------------------------------------
			// Sets the dragged image.
			//
			// Parameters:
			//
			// Win::ImageList Handle h -> Handle of the image list
			// const int index -> Index of the image from the image list
			// const int xHotspot -> X coordinate of the hotspot
			// const int yHotspot -> Y coordinate of the hotspot
			//---------------------------------------------------------------------
			void SetDragCursorImage (Win::ImageListHandle h, const int index, const int xHotspot, const int yHotspot) 
			{
				if (ImageList_SetDragCursorImage(h, index, xHotspot, yHotspot) == 0)
					throw Win::Exception (TEXT("Error, could not set the dragged image")) ;
			}


		private:

			Win::Base _hwnd ;
		} ;

		//---------------------------------------------------------------------
		// Object used to create a Image List
		//---------------------------------------------------------------------
		class ImageListCreator 
		{
			static Win::ImageListStrongHandle Create (const int width, const int height, const int initial, const int maxGrow, const UINT flag) ;
			static Win::ImageListStrongHandle Duplicate (Win::ImageListHandle hc) ;
			static Win::ImageListStrongHandle Merge (Win::ImageListHandle h1, const int index1, Win::ImageListHandle h2, const int index2, const int offsetX, const int offsetY) ;

		} ;

	}

#endif