/*
 * MyVector.h declares and implements the MyVector class behaviour.
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    /*
     * Constructs a new empty vector.
     */
    MyVector();

    /*
     * THis destructor frees the memory that was allocated internally by the list.
     */
    ~MyVector();

    /*
     * Copy constructor
     */
    MyVector(const MyVector& other);

    /*
     * Copy assignment
     */
    MyVector& operator =(const MyVector& other);

    /*
     * Pushes a given element to the end of the vector.
     */
    void push_back(const T&);

    /*
     * Removes the last element of the vector.
     */
    void pop_back();

    /*
     * Returns the element at the given 0-based index of the vector.
     */
    T& operator[](unsigned i);

    /*
     * Returns the element at the given 0-based index of the vector.
     */
    const T& operator[](unsigned i)const;

    /*
     * Returns true if the are no elements in the vecotr.
     */
    bool empty()const;

    /*
     * Returns a pointer to the beginning of the vector.
     */
    T* begin();

    /*
     * Returns a pointer to the end of the vector.
     */
    T* end();

    /*
     * Removes all elements from the vector.
     */
    void clear();

    /*
     * Returns the number of elements in the vector.
     */
    unsigned size()const;

private:

    unsigned numberOfElements;
    unsigned capacity;

    T *storage;

    /*
     * This helper copies the elements of other into this vector.
     */
    void copyOther(const MyVector& other);

    /*
     * This helper resizes the vector's internal array buffer if necessary.
     */
    void checkResize();

    /*
     * This helper throws an out_of_range exception if the given index is not between
     * the given min/max indexes, inclusive.
     */
    void checkIndex(unsigned i, unsigned min, unsigned max) const;
};


template<typename T>
MyVector<T>::MyVector(){
    numberOfElements = 0;
    capacity = 1;
    storage = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    if (&other != this) {
        copyOther(other);
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (&other != this) {
        delete[] storage;
        copyOther(other);
    }
    return *this;

}

template<typename T>
void MyVector<T>::copyOther(const MyVector& other) {
    numberOfElements = other.numberOfElements;
    capacity = other.capacity;
    storage = new T[capacity];
    for(unsigned i = 0; i < other.size(); i++) {
        storage[i] = other.storage[i];
    }
}


template<typename T>
void MyVector<T>::push_back(const T& e){
    if(numberOfElements == capacity) {

        T* newStorage = new T[capacity*2];
        for(unsigned i = 0; i < numberOfElements; i++) {
            newStorage[i] = storage[i];
        }
        delete [] storage;
        storage = newStorage;
        capacity *= 2;
    }

    storage[numberOfElements] = e;
    numberOfElements++;
}

template<typename T>
void MyVector<T>::pop_back(){
    if(!empty()) {
        numberOfElements--;
        if(numberOfElements == capacity/2) {

            T* newStorage = new T[capacity/2];
            for(unsigned i = 0; i<numberOfElements; i++) {
                newStorage[i] = storage[i];
            }
           delete[] storage;
            storage = newStorage;
            capacity /= 2;
        }
    }
}

template<typename T>
void MyVector<T>::checkResize() {
    bool resizeNecessary = false;
    T* newStorage;
    if(numberOfElements == capacity) {
        resizeNecessary = true;
        capacity *= 2;
    } else if(numberOfElements == capacity/2) {
        resizeNecessary = true;
        capacity /= 2;
    }
    if (resizeNecessary) {
        newStorage = new T[capacity];
        for(unsigned i = 0; i<numberOfElements; i++) {
            newStorage[i] = storage[i];
        }
       delete[] storage;
       storage = newStorage;
    }
}



template<typename T>
T& MyVector<T>::operator[](unsigned i){
    checkIndex(i, 0, numberOfElements-1);
    return storage[i];

}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    checkIndex(i, 0, numberOfElements-1);
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    delete[] storage;
    capacity = 1;
    numberOfElements = 0;
    storage = new T[capacity];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){

    return &storage[0];

}

template<typename T>
T* MyVector<T>::end(){
    return &storage[numberOfElements];
}

template<typename T>
void MyVector<T>::checkIndex(unsigned i, unsigned min, unsigned max)const {
    if (i < min || i > max) {
        throw std::out_of_range("Index " + std::to_string(i)
                                      + " out of range; (must be between "
                                      + std::to_string(min) + " and "
                                      + std::to_string(max) + ")");
    }
}

#endif // MY_VECTOR_H
