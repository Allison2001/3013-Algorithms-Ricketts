/*****************************************************************************
*                    
*  Author:           Allison Ricketts
*  Title:            A03B
*  Course:           3013 Algorithms
*  Semester:         Spring 2022
* 
*  Description:
*        The program impliments a linked list while overloading the + and [] opperators 
* 
*****************************************************************************/
#include <iostream>

using namespace std;

int A[100];

/**
 * Node
 * 
 * Description:
 *      Holds the values and the pointers to build our nodes
 * 
 * Public Methods:
 *      Node()
 */
struct Node {
    int x;        //delcares x
    Node *next;   //pointer pointing to next
    Node() {      //giving x and next values
        x = -1;
        next = NULL;
    }
    Node(int n) {   //builds nodes
        x = n;
        next = NULL;
    }
};

/**
 * Class Name: List
 * 
 * Description:
 *      Holds the functions that will allow us to add, insert, remove nodes from a list and also override operators and print
 * 
 * Public Methods:
 *              List
 *      void    Push()
        void    Insert()
        void    PrintTail()
        string  List()
        int     Pop()
        List    Operator+()
        int     Operator[]()
        friend  ostream &operator<<()
 * 
 */
class List {
private:
    Node *Head;     //pointer to head
    Node *Tail;     //pointer to tail
    int Size;

public:
    /**
     * Public : List
     * 
     * Description:
     *      Constuctor
     * 
     * Returns:
     *      nothing
     */
    List() {        //set default values
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public : Push
     * 
     * Description:
     *      Adds a value/node onto our linked list
     * 
     * Params:
     *      int val
     * 
     * Returns:
     *      - void
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public : Insert
     * 
     * Description:
     *      Adds a value/node into our linked list in a chosen position
     * 
     * Params:
     *      int val
     * 
     * Returns:
     *      - void
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public : PrintTail
     * 
     * Description:
     *      Prints our last value in the list
     * 
     * Params:
     *      
     * 
     * Returns:
     *      - void
     */
    void PrintTail() {
        cout << Tail->x << endl;
    }

    /**
     * Public : Print
     * 
     * Description:
     *      Prints our list
     * 
     * Params:
     *      
     * 
     * Returns:
     *      - list
     */
    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    /**
     * Public : Pop
     * 
     * Description:
     *      Removes a value/node onto our linked list
     * 
     * Params:
     *      
     * 
     * Returns:
     *      - 0
     */
    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }

    /**
     * Public : Operator+
     * 
     * Description:
     *      Overrides the + opperator to take 2 lists and to push them both onto one new list
     * 
     * Params:
     *      const List &Rhs
     * 
     * Returns:
     *      - NewList
     */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    /**
     * Public : Operator[]
     * 
     * Description:
     *      Implementation of [] operator.  This function returns an int value as if the list were an array.
     * 
     * Params:
     *      int index
     * 
     * Returns:
     *      - Temp->x
            - os
     */
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);  //Pushes value in i onto L1
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);   //Pushes value in i onto L2
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;  //L3 = L1 and L2 together
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}