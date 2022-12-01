// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:

    unsigned numberOfElements;
    unsigned capacity;

    T *storage;
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
        numberOfElements = other.numberOfElements;
        capacity = other.capacity;
        storage = new T[capacity];
        for(unsigned i = 0; i < other.size(); i++) {
            storage[i] = other.storage[i];
        }
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (&other != this) {

        numberOfElements = other.numberOfElements;
        capacity = other.capacity;
        delete[] storage;
        storage = new T[capacity];
        for(unsigned i = 0; i < other.size(); i++) {
            storage[i] = other.storage[i];
        }
    }
    return *this;

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
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
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

#endif // MY_VECTOR_H
