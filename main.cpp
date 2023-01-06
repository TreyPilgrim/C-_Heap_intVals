/*
 * Name: Trey Fullwood
 * NetID: rf802
 * Class: Data Structures Section 01
 * Assignment: Program 04
 * Description:
 *      Create a min or max heap depending on command line inputs
 *
 * Inputs:
 *      exit – exits the program
 *      load <file> - parses the contents of file as if they were entered in the text-based interface
 *      build <type> <int> <int> <int> <int> … <int> – creates the specified heap from the list of integers following the command using build heap;
 *                                                     <type> is either min or max; as an example build min 30 40 10 15 18 9 creates a min  heap containing the values 30, 40, 10, 15, 18, and 9.
 *      remove <type>- removes the root from the specified heap; <type> is either min or max.
 *      clear <type> - removes all the values for the specified heap.
 *      display <type> <count> - displays some or all the contents of the specified heap. If <count> is an integer, then display will remove and display that many values from the specified heap;
 *                               if <count> is all, then display will remove and display every value in the specified heap.
 *
 */
#include "Tokenizer.h"
#include "MaxHeap.h"
#include "MinHeap.h"
#include <vector>
#include <fstream>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

// Function Prototypes
void spacer();
void displayVector (vector <int> heap);
bool setVector(vector <int> &heap, int &num, Tokenizer &tkn);
bool processText(istream& is, MaxHeap& maxHeap, MinHeap& minHeap, bool interactive = true);

int main()
{
    MinHeap minHeap;
    MaxHeap maxHeap;
    processText(cin, maxHeap, minHeap);
    return 0;

}

// Function Declarations
// Divide loop iterations
void spacer()
{
    cout << "-----------------------------------------------------\n";
    cout << ">> ";
}

// Display vector
void displayVector (vector <int> heap)
{
    for (int i{0}; i < heap.size(); i++)
    {
        cout << heap.at(i) << " ";
    }
}
// Set the unbuilt heap
bool setVector(vector <int> &heap, int &num, Tokenizer &tkn)
{
    while (tkn.readInteger(num))
    {
        heap.push_back(num);
    }

    string str;
    if (!tkn.readInteger(num) && tkn.readWord(str))
        return false;

    cout << "The numbers: ";
    displayVector(heap);
    cout << "will be entered into the heap" << endl;
    return true;
}

// Process Text
bool processText(istream& is, MaxHeap& maxHeap, MinHeap& minHeap, bool interactive)
{

    vector <int> heap {};
    string line;
    string command;
    string type, arg1;
    int num;
    Tokenizer tkn;
    while (true)
    {
        if (!interactive)
        {
            if (is.eof()) return true;
        }
        else
            spacer();

        getline(is, line);
        tkn.setString(line);

        tkn.readWord(command);
        if (command == "exit") // Command == exit
        {
            cout << "Exiting ...." << endl;
            return false;
        }
        else if (command == "load") // Command == load
        {
            // load expects a filename .. so read one more word
            if (!tkn.readWord(type)) {
                cout << "Missing file name" << endl;
                continue; // skip back to the top of the read loop
            }
            ifstream fin;
            bool status = true;
            fin.open(type);
            if (fin.is_open())
            {
                // keeping in mind the note about the definition for the processText function
                // the following line of code is closer to
                // status = processText(fin, b, false);
                status = processText(fin, maxHeap, minHeap, false);
            }
            else { cout << "Failed to open the file" << endl; }
            fin.close();
            if (!status) return false;
        }
        else if (command == "build") // Command == Build
        {
            tkn.readWord(type);

            {

                if(!setVector(heap, num, tkn))
                {
                    cout << "Operation Canceled" << endl;
                    heap.clear();
                    continue;
                }

                if(type == "min") // Build MinHeap
                    minHeap.buildHeap(heap);
                else if (type == "max") // Build MaxHeap
                    maxHeap.buildHeap(heap);
                else // otherwise, cancel
                {
                    cout << "Invalid input...\n";
                    cout << "Operation canceled\n";
                }

                heap.clear();
            }

            continue;

        }
        else if (command == "remove") // Command == remove
        {
            tkn.readWord(type);
            int root;
            bool done;

            if (type == "min") // Min heap
                minHeap.remove(root);
            else if (type == "max") // Max Heap
                maxHeap.remove(root);
            else // otherwise
            {
                cout << "Invalid input...\n";
                cout << "Operation canceled\n";
                continue;
            }

            cout << root << " has been removed from the " << type << " heap\n";

            continue;
        }
        else if (command == "clear") // Command == clear
        {
            tkn.readWord(type);

            if (type == "min")
                minHeap.clear();
            else if (type == "max")
                maxHeap.clear();
            else
            {
                cout << "Invalid input...\n";
                cout << "Operation canceled\n";
            }
            continue;

        }
        else if (command == "display") // Command == display
        {
            tkn.readWord(type);

            // Min Heap
            if (type == "min")
            {
                if (tkn.readInteger(num))
                {
                    // Display range
                    if(!minHeap.displayRange(num, cout))
                    {
                        cout << "Heap is empty... " << endl;
                    }
                    continue;
                }

                tkn.readWord(arg1);

                // Display all
                if (arg1 == "all")
                {
                    if(!minHeap.displayHeap(cout))
                    {
                        cout << "Heap is empty..." << endl;
                        continue;
                    }
                }
                else
                {
                    cout << "Invalid input...\n";
                    cout << "Operation canceled\n";
                    continue;
                }

            }
            else if (type == "max") // Max Heap
            {
                if (tkn.readInteger(num))
                {
                    // Display Range
                    if(!maxHeap.displayRange(num, cout))
                        cout << "Heap is empty..." << endl;
                    continue;
                }

                tkn.readWord(arg1);

                // Display all
                if (arg1 == "all")
                {
                    if(!maxHeap.displayHeap(cout))
                        cout << "Heap is empty..." << endl;
                }
                else
                {
                    cout << "Invalid input...\n";
                    cout << "Operation canceled\n";
                }

            }
            else
            {
                cout << "Invalid input...\n";
                cout << "Operation canceled\n";
            }

            continue;

        }
        else // Otherwise, ignore invalid inputs
        {
            cout << "Invalid input...\n";
            cout << "Operation canceled\n";
        }
    }


}