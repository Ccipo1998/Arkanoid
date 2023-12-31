
#pragma once

#include <stdlib.h>
#include <cstring>
#include <stdexcept>

template <class T>
class List
{

public:

    /*
	@brief
	Default constructor for list
	*/
    List();

    /*
	@brief
	Current list size getter
	*/
    unsigned int GetSize();

    /*
	@brief
	Add an element at the end of the list
    @param element: the element to add
	*/
    void Add(T element);

    /*
	@brief
	Insert an element in a specific position of the list
    @param element: the element to insert
    @param index: the position of the element in the list
	*/
    void Insert(T element, unsigned int index);

    /*
	@brief
	Remove the element in a specific position from the list
    @param index: the position of the element to remove
	*/
    void Remove(unsigned int index);

    /*
    @brief
    Return a reference to the element at a specific position in the list
    @param index: the position of the element to get
    */
    T& operator[](unsigned int index);

    ~List();

private:

    T* elements;
    unsigned int size;

};

#pragma region DEFINITIONS

template <class T>
List<T>::List()
    : elements(nullptr)
    , size(0)
    {}

template <class T>
unsigned int List<T>::GetSize()
{
    return this->size;
}

template <class T>
void List<T>::Add(T element)
{
    T* newElements = (T*)realloc(this->elements, sizeof(T) * (this->size + 1));
    
    // realloc failing
    if (newElements == nullptr)
    {
        // TODO log
        return;
    }

    this->elements = newElements;
    this->elements[this->size] = element;
    ++this->size;
}

template <class T>
void List<T>::Insert(T element, unsigned int index)
{
    // bound check
    if (this->size <= index)
        return;

    T* newElements = (T*)realloc(this->elements, sizeof(T) * (this->size + 1));
    
    // realloc failing
    if (newElements == nullptr)
    {
        // TODO log
        return;
    }

    this->elements = newElements;
    memmove(&this->elements[index + 1], &this->elements[index], sizeof(T) * (this->size - index));
    this->elements[index] = element;
    ++this->size;
}

template <class T>
void List<T>::Remove(unsigned int index)
{
    // bound check
    if (this->size <= index)
        return;

    // last item removed
    if (this->size == 1)
    {
        delete this->elements[0];
        delete this->elements;

        this->elements = nullptr;
        --this->size;

        return;
    }

    // copy of the element to remove
    T element = this->elements[index];
    
    memmove(&this->elements[index], &this->elements[index + 1], sizeof(T) * (this->size - index - 1));

    T* newElements = (T*)realloc(this->elements, sizeof(T) * (this->size - 1));
    
    // realloc failing
    if (newElements == nullptr)
    {
        // TODO log

        // restore value
        memmove(&this->elements[index + 1], &this->elements[index], sizeof(T) * (this->size - index - 1));
        this->elements[index] = element;

        return;
    }

    this->elements = newElements;
    delete element;
    --this->size;
}

template <class T>
T& List<T>::operator[](unsigned int index)
{
    // bound check
    if (this->size <= index)
    {
        // TODO log e error handling and abort

        //throw std::runtime_error("Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    return this->elements[index];
}

template <class T>
List<T>::~List()
{
    // destroy each element of the list
    for (unsigned int i = 0; i < this->size; ++i)
        delete this->elements[i];

    // destroy the pointer to the elements
    if (this->elements != nullptr)
        delete this->elements;
}

#pragma endregion DEFINITIONS
