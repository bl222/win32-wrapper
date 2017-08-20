#if !defined (STRONGPOINTER_H)

#define STRONGPOINTER_H
#include "useunicode.h"
#include <cassert>

//------------------------------------------------------------------------
// StrongArrayPointer acts like an array.  It is use for the concept of
// resource management.  Basicly, a StrongArrayPointer own the dynamic data
// that is assigned to it.  When the StrongArrayPointer object goes out of
// scope, the dynamic data is deleted.  The dynamic data can only be owned
// by one strong pointer, so StrongPointer use transfer semantics instead
// of copy semantics.
//------------------------------------------------------------------------

template <class T>
class StrongArrayPointer
{
public:

	//------------------------------------------------------------------------
	// Constructor.  Creates a "empty" array.
	//------------------------------------------------------------------------

	StrongArrayPointer ()
		: _ptr  (NULL),
		  _size (0)
	{}

	//------------------------------------------------------------------------
	// Constructor.  Creates a array of the specified size.
	//
	// parameter:
	//
	// const unsigned int size -> Desired size for the array.
	//------------------------------------------------------------------------

	StrongArrayPointer (const unsigned int size)
		: _size (size)
	{
		assert (size != 0) ;
		_ptr = new T [size] ;
		_size = size ;
	}

	//------------------------------------------------------------------------
	// Destructor.
	//------------------------------------------------------------------------

	~StrongArrayPointer ()
	{
		Free () ;
	}

	//------------------------------------------------------------------------
	// Destroys the current array and create a new one of the specified size
	//
	// parameter:
	//
	// const unsigned int size -> Desired size for the array.
	//------------------------------------------------------------------------

	void ReAllocate (const unsigned int size)
	{
		Free () ;
		_ptr = new T [size] ;
		_size = size ;
	}

	//------------------------------------------------------------------------
	// Changes the size of the array while keeping the old data (unless shrunken, then
	// can lose data).
	//
	// parameter:
	//
	// const unsigned int size -> the new size.
	//------------------------------------------------------------------------

	void Resize (const unsigned int size)
	{
		assert (size != 0) ;

		T * tmp = new T [_size] ;

		unsigned int i = 0 ;
		
		// preserve the data
		for (; i < _size ; i++)
			tmp [i] = _ptr [i] ;

		Free () ;

		_ptr = new T [size] ;

		// restore the data 
		for (i = 0 ; i < _size ; i++)
			_ptr [i] = tmp [i] ;

		_size = size ;

		delete [] tmp ;


	}

	//------------------------------------------------------------------------
	// Adds a certain number of cell to the array, the data is not lost.
	//
	// parameter:
	//
	// const unsigned int nb -> The number of cells to be added.
	//------------------------------------------------------------------------

	void Grow (const unsigned int nb)
	{
		assert (nb != 0) ;
		Resize (_size + nb) ;
	}

	//------------------------------------------------------------------------
	// Obtains the size of the array.
	//
	// return value:  The size of the array.
	//------------------------------------------------------------------------

	unsigned int GetSize () const
	{
		return _size ;
	}

	//------------------------------------------------------------------------
	// Obtains a Weak (normal pointer on the array.
	//
	// Return value:  A weak pointer on the array.
	//------------------------------------------------------------------------

	T* Get () const throw ()
	{
		return _ptr ;
	}

	//------------------------------------------------------------------------
	// The StrongArrayPointer give up ownership of the dynamic data without deleting
	// it.  The data is not deleted, instead a weak (normal) pointer pointing
	// to it is returned
	//
	// Return value:  A weak pointer on the dynamic data.
	//------------------------------------------------------------------------

	T* Release () throw ()
	{
		T * tmp = _ptr;
		_ptr = NULL ;
		return tmp ;
	}

	//------------------------------------------------------------------------
	// Tranfers ownership of dynamic data from one StrongArrayPointer to another.
	//
	// Return value:  A reference on a StrongArrayPointer (*this)

	//
	// parameters:
	//
	// StrongArrayPointer<T> & rhs -> The StrongPointer giving up ownership of its
	//							       array.
	//------------------------------------------------------------------------

	StrongArrayPointer<T>& operator= (StrongArrayPointer<T> & rhs) throw()
	{
		if (rhs._ptr != _ptr)
		{
			Free () ;
			_ptr  = rhs.Release () ;
			_size = rhs._size ; 
			rhs._size = 0 ;
		}

		return *this ;
	}

	//------------------------------------------------------------------------
	// Obtains a certain value of the array.
	//
	// Return value:  A reference on one of the value of the array.
	//
	// parameter:
	//
	// const unsigned int i -> The desired value (0 = first).
	//------------------------------------------------------------------------

	T& operator [] (const unsigned int i) 
	{
		assert (i >= 0 && i < _size) ;
		return _ptr [i] ;
	}

	//------------------------------------------------------------------------
	// Obtains a certain value of the array. (used in const method).
	//
	// Return value:  A constant reference on one of the value of the array.
	//
	// parameter:
	//
	// const unsigned int i -> The desired value (0 = first).
	//------------------------------------------------------------------------

	const T& operator [] (const unsigned int i) const
	{
		assert (i >= 0 && i < _size) ;
		return _ptr [i] ;
	}

private:

	void Free ()
	{
		if (_ptr)
		{
			delete [] _ptr ;
			_ptr = NULL ;
		}
	}

private:

	T *          _ptr ; // Points on a dynamic array
	unsigned int _size ; // Size of the array.
} ;

//------------------------------------------------------------------------
// StrongPointer acts like a pointer.  It is use for the concept of
// resource management.  Basicly, a StrongPointer own the dynamic data
// that is assigned to it.  When the StrongPointer object goes out of
// scope, the dynamic data is deleted.  The dynamic data can only be owned
// by one strong pointer, so StrongPointer use transfer semantics instead
// of copy semantics. StrongPointer are lige auto_ptr, but in VC++ 6.0,
// auto_ptr contains a "bug", so I implemented StrongPointer to replace
// them.
//------------------------------------------------------------------------

template <class T>
class StrongPointer
{
public:

	//------------------------------------------------------------------------
	// Exlplicit constructor.  Gives to the StrongPointer object ownerships
	// of new dynamic data.
	//
	// Parameters:
	//
	// T* ptr -> Points on the dynamic data.  Only use expresion like
	//			 StrongPointer<int> str (new int) ;
	//------------------------------------------------------------------------

	explicit StrongPointer (T * ptr = NULL) throw () 
		: _ptr (ptr)
	{}

	//------------------------------------------------------------------------
	// Transfer constructor.  The StrongPointer passed as a parameter gives
	// up ownership of its dynamic data and the new StrongPointer receive 
	// owndership of the data.
	//
	// Parameters:
	//
	// StrongPointer<T> & rhs -> The StrongPointer giving up ownership
	//------------------------------------------------------------------------

	StrongPointer (StrongPointer<T> & rhs) throw ()
		: _ptr (rhs.Release ())
	{}

	//------------------------------------------------------------------------
	// Destructor.  Deletes the dynamic data.
	//------------------------------------------------------------------------

	~StrongPointer () throw ()
	{
		Free () ;
	}

	void Init (T* rhs) 
	{
		_ptr = rhs ;
	}

	//------------------------------------------------------------------------
	// Obtains a Weak (normal pointer on the dynamic data.
	//
	// Return value:  A weak pointer on the dynamic data.
	//------------------------------------------------------------------------

	T* Get () const throw ()
	{
		return _ptr ;
	}

	//------------------------------------------------------------------------
	// The StrongPointer give up ownership of the dynamic data without deleting
	// it.  The data is not deleted, instead a weak (normal) pointer pointing
	// to it is returned
	//
	// Return value:  A weak pointer on the dynamic data.
	//------------------------------------------------------------------------

	T* Release () throw ()
	{
		T * tmp = _ptr;
		_ptr = NULL ;
		return tmp ;
	}

	//------------------------------------------------------------------------
	// Tranfers ownership of dynamic data from one StrongPointer to another.
	//
	// Return value:  A reference on a StrongPointer (*this)

	//
	// parameters:
	//
	// StrongPointer<T> & rhs -> The StrongPointer giving up ownership of its
	//							 dynamic data.
	//------------------------------------------------------------------------

	StrongPointer<T>& operator=(StrongPointer<T> & rhs) throw()
	{
		if (rhs._ptr != _ptr)
		{
			Free () ;
			_ptr = rhs.Release () ;
		}

		return *this ;
	}

	//------------------------------------------------------------------------
	// Same use as the * operator for normal pointers.
	//------------------------------------------------------------------------

	T&  operator*  () const throw()
	{
		return *_ptr ;
	}

	//------------------------------------------------------------------------
	// Same use as the -> operator for normal pointers.
	//------------------------------------------------------------------------

    T* operator-> () const throw()
	{
		return _ptr ;
	}

private:

	void Free () throw ()
	{
		if (_ptr)
		{
			delete _ptr ;
			_ptr = NULL ;	
		}
	}

private:
	
	T * _ptr ;
} ;

#endif