#ifndef DynamicArray_hpp
#define DynamicArray_hpp

#include <stdio.h>

class DynamicArray {
public:
    DynamicArray(int size);
    ~DynamicArray();

private:
    int* mArray;
    int mSize;
};

#endif /* DynamicArray_hpp */
