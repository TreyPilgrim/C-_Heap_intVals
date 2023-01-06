#pragma once
#include <iostream>
#include <vector>
class MaxHeap
{
private:
    int size {20};
    int* heap;
    int elements {0};

    void bubbleUp(int index);
    void bubbleDown(int index);
    void swap (int index1, int index2);
    void setElements(int num);
    void setHeap (std::vector<int> &pile);
    void reallocate();

public:

    MaxHeap(int elements):
            heap(new int [this->size]), elements(elements) {}

    MaxHeap():
            heap (new int [this->size]) {}

    ~MaxHeap();

    bool peek();
    bool remove(int &value);
    bool displayHeap(std::ostream &os);
    bool displayRange(int num, std::ostream &os);

    void add (int value);
    void buildHeap(std::vector <int> &pile);
    void clear();
};