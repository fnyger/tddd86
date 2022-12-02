// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

    unsigned size() const;

private:

    unsigned getParentIndex(unsigned index);

    int getLeftChildIndex(unsigned index);

    int getRightChildIndex(unsigned index);

    void swap(unsigned index1, unsigned index2);

};



template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){

}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);

    unsigned index = vector_array.size() - 1;
    unsigned parentIndex = getParentIndex(index);

    while(index > 0 && strictly_larger_operator(vector_array[parentIndex], vector_array[index])) {
        swap(index, parentIndex);
        index = parentIndex;
        parentIndex = getParentIndex(index);
    }
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{

    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    vector_array[0] = vector_array[vector_array.size()-1];
    vector_array.pop_back();
    int index = 0;
    while(index != -1) {
        int leftChildIndex = getLeftChildIndex(index);
        int rightChildIndex = getRightChildIndex(index);
        T currentNode = vector_array[index];

        //No children
        if(leftChildIndex == -1) {
            return;
        }


        T leftChild = vector_array[leftChildIndex];
        if(rightChildIndex == -1) { //only left children

            if(strictly_larger_operator(currentNode, leftChild)) {
                swap(leftChildIndex, index);
                index = leftChildIndex;
            }
            return;

        } else { //Two children
            int largestChildIndex;
            T rightChild = vector_array[rightChildIndex];

            if(strictly_larger_operator(rightChild, leftChild)) {
                largestChildIndex = leftChildIndex;
            } else {
                largestChildIndex = rightChildIndex;
            }
            T largestChild = vector_array[largestChildIndex];

            if(strictly_larger_operator(currentNode, largestChild)) {
                swap(largestChildIndex, index);
                index = largestChildIndex;
            } else {
                return;
            }

        }
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.size() == 0;

}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{

    return vector_array.size();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::getParentIndex(unsigned index){

    return index ? (int)((index - 1) / 2) : 0;
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::getLeftChildIndex(unsigned index){
    unsigned newIndex = 2*index+1;
    if(newIndex < size()) {
        return newIndex;
    }
    return -1;
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::getRightChildIndex(unsigned index){
    unsigned newIndex = 2*index+2;
    if(newIndex < size()) {
        return newIndex;
    }
    return -1;
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::swap(unsigned index1, unsigned index2){
    T temp = vector_array[index1];
    vector_array[index1] = vector_array[index2];
    vector_array[index2] = temp;
}

#endif // MY_PRIORITY_QUEUE_H
