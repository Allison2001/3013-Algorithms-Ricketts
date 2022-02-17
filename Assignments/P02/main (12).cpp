///////////////////////////////////////////////////////////////////////////////
//
// Author:           Allison Ricketts
// Label:            P02
// Title:            Program 02 - Processing in Linear Time
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       This program searches a dictionary database letter by letter, telling
//        you how many words are left to fit the letters that you input and
//        how long it takes for that action to run.
//
/////////////////////////////////////////////////////////////////////////////////

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/**
 * wordNode
 * 
 * Description:
 *      struct for building nodes for linked lists
 *      
 */
struct wordNode{
  string data;
  wordNode* next;
  //establishes data and points next to NULL
  wordNode(string d){
    data = d;
    next = NULL;
  }
  //declares data and next as d and n
  wordNode(string d, wordNode* n){
    data = d;
    next = n;
  }
};

/**
 * WordList
 * 
 * Description:
 *        performs all tasks needed to search and find words in our database
 *
 * Private Methods:
        - wordNode* head
        -int    size
 * 
 * Public Methods:
 *      - WordList()
        - void    newNode();
        - void    tailNode();
        - void    deleteNode();
        - void    print();
        - void    runGetch();
 * 
 * Usage: 
 *      - See main program
 *      
 */
class WordList{
  private:
    wordNode* head;  //our top node
    int size = 0;    //intitalizing size
    int count = 0;
    vector<string> word;
    int words = 0;

  public:

  /**
 * WordList
 * 
 * Description:
 *      Our default constuctor
 *      
 */
    WordList(){
      head = NULL;    //pointing head to NULL
    }

    
/**
 * newNode
 * 
 * Description:
 *      stores our new letter into a new node
 *      
 */
    void newNode(string data){
      //creat a temp pointer to hold a temp value
      wordNode* temp = new wordNode(data);
      temp->data = data;    //temp data = data
      temp->next = head;    //node after temp is head
      head = new wordNode(data,head);   //head now hold data and head
    }

    /**
 * tailNode
 * 
 * Description:
 *      creats new node at end of list
 *      
 */
    void tailNode(string data){
      //if the head is the last node it becomes the new node
      if(!head){
        head = new wordNode(data);
      } else{
        wordNode* temp = head;  //otherwise the next new temp node becomes head
          //if next node is not empty temp becomes next node
          while(temp->next != NULL){    
            temp = temp->next;
          }
          temp->next = new wordNode(data);  //temp node = new node
      }
    }

  /**
 * deleteNode
 * 
 * Description:
 *      removes node from list
 *      
 */
    void deleteNode(string key){
      //if head does not = NULL and data = key
      if(!head && head->data == key){
        wordNode* temp = head;    //temp points to head
        head = head->next;        //value in head gets pushed to next
        delete temp;              //delete temp pointer
      } else{
        wordNode* temp = head;    //temp = head
        wordNode* temp2 = NULL;   //second temp to hold first temp
        while(temp != NULL){      //if firest temp does not = NULL
          if(temp->data == key){
            temp2->next = temp->next;   //temp2 essentially = temp
            delete temp;
          }
          temp2 = temp;
          temp = temp->next;
        }
      cout << "The word " << termcolor::red << key << termcolor::reset << "cannot be found" << endl; //make key red
      }
    }

    /**
 * Print
 * 
 * Description:
 *      prints our list and information
 *      
 */
    void print(){
      //print only the first 10 terms
      if(count >= 10){
        for(int i = 0; i < 10; i++){
          cout << word[i] << ", "; 
        }
      }
      //prints the number of words that are stored in database
      cout << "\nTotal Words: " << count;
    }

    /**
 * runGetch
 * 
 * Description:
 *      tracks our letters (characters) and searchs our database
 *      
 */
    void runGetch(){
      Timer T;    //our timer
      char k;     //the individual letters in the keyward
      string key;   //our full key word
      wordNode* temp = head;
      
      cout << "Enter word here: " << endl;

      while(k != 'Z'){    //Z kills program
        k = getch();    //take k and run it through our getch function
         auto start = chrono::steady_clock::now();  //start timing beginning of action
        //makes backspace work
        if(k==127){
          key.pop_back();
          cout<< key << endl;
          //lemgth of key
          while(temp != NULL){
            if(temp->data.substr(0,key.length()) == key.substr(0,key.length())){
              word.push_back(temp->data);
              count++;
              temp = temp->next;
            } else
              temp = temp->next;
            }
          } else{
            //the number of words that fit our parameters
            key.push_back(k);
            cout << termcolor::green << "Word: " << termcolor::reset << key << endl << endl;
            while(temp != NULL){
              if(temp->data.substr(0,key.length()) == key.substr(0,key.length())){
                word.push_back(temp->data);
                count++;
                temp = temp->next;
              } else
                temp = temp->next;
              }
            }
            auto end = chrono::steady_clock::now();   //end action timer
            print();    //print list
            cout << endl;
            count = 0;    //word count
            cout << endl;
            cout << termcolor::red << "Elapsed time in nanoseconds: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;    //print nanoseconds used to finish action
            temp = head;
          }
        }
};

int main() {
  WordList word;
  string key;

  ifstream infile;  //to read our text file
  char k;
  Timer T;

  auto start = chrono::steady_clock::now();  //start timer

  infile.open("dictionary.txt");    //open file

  //as reads file to key keep looping
  while(infile >> key){
    word.tailNode(key);   //adds element to list
  }

  auto end = chrono::steady_clock::now();   //ends timer

  word.runGetch();
}
