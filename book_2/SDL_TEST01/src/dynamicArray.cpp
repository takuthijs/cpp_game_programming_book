#include "dynamicArray.hpp"


DynamicArray::DynamicArray(int size):mSize(size),mArray(nullptr){
    mArray = new int [mSize];
}

DynamicArray::~DynamicArray(){
    delete[] mArray;
}

