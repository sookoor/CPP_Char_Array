#if !defined (ARRAY_C)
#define ARRAY_C

#include <stdexcept>
#include "Array.h"

#if !defined (__INLINE__)
#define INLINE 
#include "Array.inl"
#endif /* __INLINE__ */

Array::Array (size_t size) : max_size_(size), cur_size_(size), array_(new T[max_size_])
{
}

// Dynamically initialize an array.

Array::Array (size_t size, const T &default_value) : max_size_(size), cur_size_(size), array_(new T[max_size_])
{
    for (size_t i = 0; i < size; i++)
        array_[i] = default_value;
}

// The copy constructor (performs initialization). 

Array::Array (const Array &s) : max_size_(s.max_size_), cur_size_(s.size ()), array_(new T[max_size_])
{
    for (size_t i = 0; i < size (); i++)
	array_[i] = s.array_[i];
}

// Compare this array with <s> for equality.

bool
Array::operator== (const Array &s) const
{
    // Check if size()'s of the two arrays are equal.
    if (size () != s.size ())
	// If size()'s are not equal return false.
	return false;
    // If size()'s are equal compare all elements from 0 to size().
    else {
	for (size_t i = 0; i < s.size (); i++)
	    {
		if (array_[i] != s.array_[i])
		    return false;
	    }
	return true;
    }
}

// Compare this array with <s> for inequality.

bool
Array::operator!= (const Array &s) const
{
    return !(*this == s);
}

// Assignment operator (performs assignment). 

void
Array::operator= (const Array &s)
{
    if (this != &s)
        {
            // If the allocated memory is insufficient to hold the array,
            // the memory has to be deallocated and sufficient memory has
            // to be reallocated.
            if (max_size_ < s.size ())
                {
                    delete [] array_;
	            max_size_ = s.size ();
	            array_ = new T[max_size_];
                }

            for (size_t i = 0; i < s.size (); i++)
                array_[i] = s.array_[i];
            cur_size_ = s.size ();
        }
}

    // Clean up the array (e.g., delete dynamically allocated memory).

    Array::~Array (void)
    {
        delete []  array_;
    }

    // = Set/get methods.

    // Set an item in the array at location index.  Throws
    // <std::out_of_range> if index is out of range, i.e., larger than the
    // size() of the array.

    void
        Array::set (const T &new_item, size_t index)
    {
        if (in_range(index))
            array_[index] = new_item;
        else
            throw std::out_of_range("index out of range");
    }

    // Get an item in the array at location index.  Throws
    // <std::out_of_range> if index is out of range, i.e., larger than the
    // size() of the array.

    void
        Array::get (T &item, size_t index) const
    {
        if (in_range(index))
            item = array_[index];
        else
            throw std::out_of_range("index out of range");
    }

#endif /* ARRAY_C */
