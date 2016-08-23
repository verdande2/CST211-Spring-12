/************************************************************************
* Class: Array
*
* Purpose: This class represents a 1 dimensional dynamic array that can 
*		have any length and any integer-valued starting index. It is 
*		templated so that it can allow any datatype for the array.
*
* Manager functions:	
* 	Array()
* 		Constructs a 0-size 1D array with a starting index of 0 	
*	Array(int length, int start_index = 0)
*		Constructs a length-size 1D array with a starting index of start_index
*	Array(Array const& copy)
*		Copy constructor
*	operator=(Array const& copy)
*		Overloaded operator= function
*	~Array()
*		Destructor, deletes the dynamic array
*
* Methods:		
*	operator[](int index)
*		Overloaded bracket operator used to resolve addresses at given index. 
*		Takes into consideration start_index. Used for assignment and value 
*		retrieval.
*	getStartIndex()
*		Returns the start index
*	setStartIndex(int start_index)
*		Sets the start index to start_index
*	getLength()
*		Returns the current length of the array
*	setLength(int length)
*		Sets the length of the array to length. 
*************************************************************************/
#pragma once

#include "Exception/Exception.cpp" // it finds the h file fine

template <class T>
class Array
{
	private:
		T* m_array;
		unsigned m_length;
		int m_start_index;

	public:
		Array();
		Array(unsigned length, int start_index);
		Array(Array<T> const& copy);
		~Array();

		Array& operator=(Array<T> const& rhs);
		T& operator[](int index);
		T const& operator[](int index) const;

		int getStartIndex() const;
		void setStartIndex(int start_index);

		unsigned getLength() const;
		void setLength(unsigned length);

		void Purge(void);

		void Append(T const& data);
		void Prepend(T const& data);
};

/**********************************************************************	
* Array()
* Purpose: This function is the default constructor for the Array class. 
*		It defaults to a length of 0 and a starting index of 0.
*
* Entry:
*		None.
*
* Exit: Constructs an Array with the above default settings.
************************************************************************/
template <class T>
Array<T>::Array() : m_length(0), m_array(nullptr), m_start_index(0)
{

}

/**********************************************************************	
* Array(int length, int start_index)
* Purpose: This function is the 2-arg constructor for the Array class. 
*		It sets the length and start_index to the corresponding parameters.
*
* Entry:
*	Parameters:
*		length: (int) The length of the array.
*		start_index: (int) The starting index of the array.
*
* Exit: Constructs an Array with the above parameters.
************************************************************************/
template <class T>
Array<T>::Array(unsigned length, int start_index = 0) : m_length(length), m_start_index(start_index), m_array(new T[length])
{

}

/**********************************************************************	
* Array(Array const& copy)
* Purpose: This function is the copy constructor for the Array class.
*
* Entry:
*	Parameters:
*		copy: (Array) The Array to copy from.
*
* Exit: Constructs a copy of the passed in Array.
************************************************************************/
template <class T>
Array<T>::Array(Array<T> const& copy) : m_length(copy.m_length), m_start_index(copy.m_start_index), m_array(new T[m_length])
{
	for(unsigned i = 0; i < m_length; ++i)
	{
		m_array[i] = copy.m_array[i];
	}
}

/**********************************************************************	
* ~Array()
* Purpose: This function is the destructor for the Array class. It 
*		cleans up the array storing the array's elements.
*
* Entry:
*		None.
*
* Exit: Resets the Array to default values and frees up any memory.
************************************************************************/
template <class T>
Array<T>::~Array()
{
	if(m_array)
	{
		delete [] m_array;
		m_array = nullptr;
	}

	m_length = 0;
	m_start_index = 0;
}

/**********************************************************************	
* Array<T>& operator=(Array const& rhs)
* Purpose: This function is the assignment operator for the Array class.
*
* Entry:
*	Params:
*		rhs: (Array) The right hand side of the assignment.
*
* Exit: Assigns the left hand Array the values/members of the right hand 
*		Array via deep copy. Also returns the left hand Array by reference.
************************************************************************/
template <class T>
Array<T>& Array<T>::operator=(Array<T> const& rhs)
{
	if(&rhs != this)
	{
		if(rhs.m_length)
		{
			if(m_length != rhs.m_length)
			{
				// if m_array was already populated, kill the current contents
				if(m_array)
				{
					delete [] m_array;
				}
				m_array = new T[rhs.m_length];
			}


			// copy array elements over
			for(unsigned i = 0; i < rhs.m_length; ++i)
			{
				m_array[i] = rhs.m_array[i];
			}
		}
		// copy members over
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;
	}
	return *this;
}

/**********************************************************************	
* T& operator[](int index)
* Purpose: This function serves to interpret the index and return the 
*		the requested element. It can then be either retrieved, 
*		or used for assignment. If the index is out of bounds, an 
*		exception will be thrown.
*
* Entry:
*	Params:
*		index: (int) The index of the requested element. Note: This does 
*				take into consideration the starting index.
*
* Exit: Returns a reference to the requested element.
************************************************************************/
template <class T>
T const& Array<T>::operator[](int index) const
{
	if(index > m_start_index + (int)m_length - 1)
	{
		throw Exception("Index out of bounds: Index too high.");
	}

	if (index < m_start_index)
	{
		throw Exception("Index out of bounds: Index too low.");
	}

	return m_array[index-m_start_index];
}
template <class T>
T& Array<T>::operator[](int index)
{
	if(index > m_start_index + (int)m_length - 1)
	{
		throw Exception("Index out of bounds: Index too high.");
	}

	if (index < m_start_index)
	{
		throw Exception("Index out of bounds: Index too low.");
	}

	return m_array[index-m_start_index];
}

/**********************************************************************	
* int getStartIndex()
* Purpose: This function returns the starting index for the array.
*
* Entry:
*		None.
*
* Exit: Returns the starting index of the array (int).
************************************************************************/
template <class T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

/**********************************************************************	
* setStartIndex(int start_index)
* Purpose: This function sets the starting index for the array.
*
* Entry:
*	Params:
*		start_index: (int) The starting index to set.
*
* Exit: The starting index of the array is set to the parameter, start_index.
************************************************************************/
template <class T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index;
}

/**********************************************************************	
* int getLength()
* Purpose: This function returns the length of the array.
*
* Entry:
*		None.
*
* Exit: Returns the length of the array (int).
************************************************************************/
template <class T>
unsigned Array<T>::getLength() const
{
	return m_length;
}

/**********************************************************************	
* setLength(int length)
* Purpose: This function sets the length of the array.
*
* Entry:
*	Params:
*		length: (int) The desired length of the array.
*
* Exit: The m_length is set to length, and the array is resized (if the 
*		length is different than current) to the given length. If length 
*		is smaller than current length, extra elements will be deleted.
************************************************************************/
template <class T>
void Array<T>::setLength(unsigned length)
{
	T* new_array = nullptr;

	if(length < 0)
	{
		throw Exception("Cannot set array length to a negative value.");
	}

	if(length == 0)
	{
		Purge();
	}
	else if(length < m_length)
	{
		new_array = new T[length];
			
		// copy over old data up to new length
		unsigned i = 0;
		for(i = 0; i < length; ++i)
		{
			new_array[i] = m_array[i];
		}

		// clean up old
		delete [] m_array;

		// set array equal to the new array
		m_array = new_array;
		m_length = length;
	}
	else if(length > m_length)
	{
		new_array = new T[length];
			
		// copy over old data
		unsigned i = 0;
		for(i = 0; i < m_length; ++i)
		{
			new_array[i] = m_array[i];
		}

		// if there is new data, zero it out
		for(unsigned j = i; j < length; ++j)
		{
			new_array[j] = T();
		}

		// clean up old data
		delete [] m_array;

		// set array equal to the new array
		m_array = new_array;
		m_length = length;
	}
	else
	{
		// same length, do nothing
	}
}


template <class T>
void Array<T>::Purge(void)
{
	if(m_length)
	{
		delete [] m_array;
		m_array = nullptr;
	}

	m_length = 0;
}

template <class T>
void Array<T>::Append(T const& data)
{
	unsigned new_length = m_length+1;
	SetLength(new_length);

	m_array[new_length-1] = data;
}


template <class T>
void Array<T>::Prepend(T const& data)
{
	T new_T(data);

	unsigned new_length = m_length+1;
	T* new_array = new T[new_length]

	unsigned i = 0;
	new_array[i++] = new_T;

	for(; i < new_length; ++i)
	{
		new_array[i] = m_array[i-1];
	}
	delete [] m_array;

	m_array = new_array;
	++m_length;
}