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

  unsigned parentIndex(unsigned index);

  int leftChildIndex(unsigned index);

  int rightChildIndex(unsigned index);

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
    unsigned parent_index = parentIndex(index);

    while(index > 0 && strictly_larger_operator(vector_array[parent_index], vector_array[index])) {
        swap(index, parent_index);
        index = parent_index;
        parent_index = parentIndex(index);
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
        int leftChild = leftChildIndex(index);
        int rightChild = rightChildIndex(index);

        //No children
        if(leftChild == -1) {
            index = leftChild;
        } else if(rightChild == -1) { //only left children

            if(strictly_larger_operator(vector_array[index], vector_array[leftChild])) {
                swap(leftChild, index);
                index = leftChild;
            }
            index = -1;

        } else { //Two children
            int largestChildIndex;
            if(strictly_larger_operator(vector_array[rightChild], vector_array[leftChild])) {
                largestChildIndex = leftChild;
            } else {
                largestChildIndex = rightChild;
            }

            if(strictly_larger_operator(vector_array[index], vector_array[largestChildIndex])) {
                swap(largestChildIndex, index);
                index = largestChildIndex;
            } else {
                index = -1;
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
unsigned MyPriorityQueue<T,C>::parentIndex(unsigned index){

    return index ? (int)((index - 1) / 2) : 0;
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::leftChildIndex(unsigned index){
    unsigned newIndex = 2*index+1;
    if(newIndex < size()) {
        return newIndex;
    }
    return -1;
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::rightChildIndex(unsigned index){
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
