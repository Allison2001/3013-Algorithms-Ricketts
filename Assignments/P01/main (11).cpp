
///////////////////////////////////////////////////////////////////////////////
//
// Author:           Allison Ricketts
// Label:            P01
// Title:            Program 01 - Resizable Array Based Stack
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       This program takes a list of values and by analyzing   //       the numbers to judge if they were odd or even which    //       dictates weather the number is added or removed from   //       the stack.
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack that is resizable due to given values
 * 
 * Public Methods:
 *      - ArrayStack()
        - ArrayStack(double,double,double,double)
        - bool    Empty()
        - bool    Full()
        - int     Peek()
        - int     Pop()
        - void    Print()
        - bool    Push(int x)
        - void    containerGrow()
        - void    containerShrink()
        - void    setFullThresh()
        - void    setEmptyThresh()
        - void    setGrowThresh()
        - void    setShrinkThresh()
        - void    getFullThresh()
        - void    getEmptyThresh()
        - void    getGrowThresh()
        - void    getShrinkThresh()
        - void    checkResize()
 *      
 */
class ArrayStack {
public:
    int *A;  // pointer to array of int's
    int top;
    int size;
    int resize;

    double FullThresh;
    double EmptyThresh;
    double GrowThresh;
    double ShrinkThresh;
    
    ifstream infile;
    ofstream outfile;


    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack() {
        size = 10;
        A = new int[size];

        FullThresh = 0.85;
        EmptyThresh = 0.15;
        GrowThresh = 2.0;
        ShrinkThresh = 0.5;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - double Full
        - double Empty
        - double Grow
        - double Shrink
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(double Full, double Empty, double Grow, double Shrink) {
        size = 10;      //default size
        resize = 0;     //default resize
        A = new int[size];
        top = -1;

        FullThresh = Full;
        EmptyThresh = Empty;
        GrowThresh = Grow;
        ShrinkThresh = Shrink;
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
    bool Full() {
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {
        checkResize();
        if (! Empty()) {
            return A[top--];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Print() {
        for (int i = 0; i <= top; i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x) {
        checkResize();
        if (Full()) {
            containerGrow();
        }
        if (!Full()) {
            A[++top] = x;

            //checkResize();
            return true;
        }

        return false;
    }

    /**
  * Public void: containerGrow
  * 
  * Description:
  *      Resizes the container for the stack by growing by 2 times
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void containerGrow() {
        int newSize = size * GrowThresh;    // double size of original
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }

    /**
  * Public void: containerShrink
  * 
  * Description:
  *      Resizes the container for the stack by halving
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void containerShrink() {
        int newSize = size * ShrinkThresh;    // halfs size of original
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }

    //setters and getters for our thresholds
    void setFullThresh(double v){
      FullThresh = v;
    }
    void setEmptyThresh(double v){
      EmptyThresh = v;
    }
    void setGrowThresh(double v){
      GrowThresh = v;
    }
    void setShrinkThresh(double v){
      ShrinkThresh = v;
    }
    double getFull(){
      return FullThresh;
    }
    double getEmpty(){
      return EmptyThresh;
    }
    double getGrow(){
      return GrowThresh;
    }
    double getShrink(){
      return ShrinkThresh;
    }

    /**
  * Public void: checkResize
  * 
  * Description:
  *      checks the values and assigns if they need to push or pop
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void checkResize(){
      double arraySize = (top + 1) / size;

      if(arraySize >= GrowThresh){  //if size gets over 85% capacity then array will grow
        containerGrow();
      } else if(arraySize <= ShrinkThresh){   //if size gets under 15% capacity then array will shrink
        containerShrink();
      }
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char **argv) {
    ifstream infile;
    string filename;
    ArrayStack stack;
    int r = 0;
    stack = ArrayStack();

    //what we print to display data
    cout << "###################################################" << endl;
      cout << "Assignment 4 - Resizing the Stack" << endl;
      cout << "CMPS 3013" << endl;
      cout << "Allison Ricketts" << endl << endl;

      cout << "Config Params: " << endl;
      cout << "Full Threshold: " << stack.FullThresh << endl;
      cout << "Shrink Threshold: " << stack.EmptyThresh << endl;
      cout << "Grow Ratio: " << stack.GrowThresh << endl;
      cout << "Shrink Ratio: " << stack.ShrinkThresh << endl << endl;

      cout << "Max Stack Size: " << stack.size << endl;
      cout << "End Stack Size: " << stack.size << endl;
      cout << "Stack Resized: " << stack.size << endl;
      cout << "###################################################";

    
    //functions to run when given command
    switch(argc){
      case 1:
      filename = argv[1];
      break;

      case 2:
      stack.setFullThresh(stod(argv[2]));
      break;

      case 3:
      stack.setEmptyThresh(stod(argv[3]));
      break;

      case 4:
      stack.setGrowThresh(stod(argv[4]));
      break;

      case 5:
      stack.setShrinkThresh(stod(argv[5]));
      break;
    } 

    
    infile.open(filename);    //open file
    infile.close();           //close file
    return 0;
}