#include "MinHeap.h"
#include <iostream>
using namespace std;
void MinHeap::bubbleUp(int index)
{
    if (index == 0)
        return;
    else
    {
        int parent {(index -1) / 2};
        if (heap[index] < heap[parent])
        {
            swap(index, parent);
            bubbleUp(parent);
        }
    }
}

void MinHeap::bubbleDown(int index)
{
    int min;
    int lChild = 2 * index + 1;
    int rChild = lChild + 1;

    if (lChild < elements - 1)
        return;
    else if (rChild < elements - 1)
        min = lChild;
    else {
        min = (heap[lChild] < heap[rChild]) ? lChild : rChild;
    }

    min = (heap[index] < heap[min]) ? index : min;

    if (min != index)
    {
        swap (index, min);
        bubbleDown(min);
    }
}

void MinHeap::swap(int index1, int index2)
{
    int firstDex {heap[index1]};
    int secondDex {heap[index2]};

    heap [index1] = secondDex;
    heap [index2] = firstDex;
}

void MinHeap::reallocate()
{
    int* old {this->heap};
    this->size *= 2;
    heap = new int[this->size];

    for (int i {0}; i < this->elements; i++)
        heap[i] = old[i];

    delete[] old;
}

void MinHeap::setElements(int num)
{
    this->elements = num;
}

void MinHeap::setHeap(std::vector<int> &pile)
{
    // Make sure heap is big enough
    while (pile.size() > this->size)
    {
        this->reallocate();
    }

    // Assign heap elements
    for (int i {0}; i < pile.size(); i++)
    {
        heap[i] = pile.at(i);
    }
}

/*
 *                      // Public Functions //
 */
// Destructor
MinHeap::~MinHeap()
{
    delete this->heap;
    elements = 0;
    size = 20;

    cout << "Have a great break!" << endl;
}
/*
 * Bool Return Type
 */
bool MinHeap::peek()
{
    if (elements == 0)
        return false;

    return true;
}

bool MinHeap::remove(int& value)
{
    // Return false if empty heap
    if (elements == 0)
        return false;

    // Update # of elements
    elements--;

    value = heap[0];
    heap[0] = heap[elements];
    bubbleDown(0);

    if (elements == 0)
        delete heap;

    return true;
}

// Remove all values and display values
bool MinHeap::displayHeap(std::ostream &os)
{
    if (elements == 0)
        return false;

    int num;
    int mass {this->elements};

    for (int i {0}; i < mass; i++)
    {
        this->remove(num);

        os << i + 1 << ": " << num << endl;
    }

    return true;
}

// Display a range of the heap
bool MinHeap::displayRange(int num, std::ostream &os)
{
    // return false if empty heap
    if (!peek())
        return false;

    int gonner;

    for(int i{0}; i < num; i++)
    {
        if (!this->peek())
        {
            os << "There were fewer elements than expected" << endl;
            return true;
        }

        this->remove(gonner);

        os << i + 1 << ": " << gonner << endl;
    }

    return true;
}

/*
 * Void Return Type
 */
void MinHeap::add(int value)
{
    if (elements == this->size)
        this->reallocate();

    this->heap[elements] = value;
    bubbleUp(elements);
    elements++;

}
// Build Heap functionality
void MinHeap::buildHeap(std::vector <int> &pile)
{
    // Enter values into Heap
    this->setElements(pile.size());
    this->setHeap(pile);

    // Build min heap
    for (int i {this->elements / 2}; i >= 0; i--)
        bubbleDown(i);
}

// Clear heap
void MinHeap::clear()
{
    int num;

    while (this->peek())
    {
        this->remove(num);
        cout << num << " has been removed from the heap" << endl;
    }
}
