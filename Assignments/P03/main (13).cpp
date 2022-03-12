///////////////////////////////////////////////////////////////////////////////
//
// Author:           Allison Ricketts
// Label:            P03
// Title:            Program 03 - Processing in Trie Tree Time
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       This program searches through a Trie Tree for a word in our dictionary and times how long it takes for the process to complete.
//
// Code Inspiration:
//    https://www.geeksforgeeks.org/pattern-searching-using-trie-suffixes/
//    https://www.geeksforgeeks.org/trie-insert-and-search/
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
 * Trie
 * 
 * Description:
 *      struct for building nodes for our tree
 *      
 */
struct Trie{
  Trie *chars[26];    //the number of characters in our nodes
  bool isLeaf;

  //node constuctor
  Trie(char k){
      this->isLeaf = false;
      for(int i = 0; i < 26; i++){
        this->chars[i] = NULL;
  }}
};

/**
 * Tries
 * 
 * Description:
 *        performs all tasks needed to search and find words in our tree
 *
 * Private Methods:
        - Trie* root
        -int    count
 * 
 * Public Methods:
 *      - Tries()
        - void    insert();
        - Trie*   search();
        - void    findAll();
        - void    findWord();
 * 
 * Usage: 
 *      - See main program
 *      
 */
class Tries{
  private:
    Trie* root;
    int count = 0;

  public:
    fstream infile;

/**
 * Tries()
 * 
 * Description:
 *      Our default constructor
 *      
 */
    Tries(){
      root = new Trie('0');
      }

/**
 * Insert
 * 
 * Description:
 *      Inserts new node onto tree
 *      
 */
    void insert(string key){
      Trie* current = root;    //start at root
      char k;
        for(int i = 0; i < key.length(); i++){    //loop for whole length og key
          if(current->chars[key[i] - 65] == NULL){    //make sure to subtract 65
          key[i] = k;
            //creats new node if tree is empty
          current->chars[key[i] - 65] = new Trie(k);
        }
      current = current->chars[key[i] - 65];    //tavels to next node
    }
    current->isLeaf = true;  //new leaf
  }

  /**
 * Search
 * 
 * Description:
 *      looks through our tree and brings back the correct node we are looking for
 *      
 */
  Trie* search(string key){
    Trie* current = root;    //start from the root

    for(int i = 0; i < key.length(); i++){    //loop for length of word
      if ( current->chars[key[i]-65] == NULL){
      return NULL;
      } 
      //travels to next node
      current = current->chars[key[i]-65];
      }
     return current;    //returns current node
  }


  vector<string> results;    //our vector for our results

/**
 * findAll
 * 
 * Description:
 *      finds all the results and pushes them to a vector
 *      
 */
   void findAll(Trie*& current, string key){
    if(current->isLeaf){
      
      results.push_back(key);    //pushes onto vector
      count++;    //how many results
    }
     for(int i = 0; 1 < 26; i++){
       if(current->chars[i]){
         //finding sum of ascii character
         //https://www.geeksforgeeks.org/find-the-sum-of-the-ascii-values-of-characters-which-are-present-at-prime-positions/
         findAll(current->chars[1],key+char(i+97));    
       }
     }
   } 
    vector<string> findAll(string key){
      Trie* trie = search(key);  //node points to key
      //clear the vector
      results.clear(); 
      findAll(trie,key);  //recursion
      return results;
    
  }

/**
 * findWord
 * 
 * Description:
 *      very similar to runGetch from P02, tracks our tree and gives our results
 *      
 */
     void findWord(){
      Timer T;    //our timer
      char k;     //the individual letters in the keyward
      string key;   //our full key word
      vector<string> results;

       cout << "Enter word here: " << endl;

      while(k != 'Z'){    //Z kills program
        k = getch();    //take k and run it through our getch function
         auto start = chrono::steady_clock::now();  //start timing beginning of action
        //makes backspace work
        key.push_back(k);
        cout << "Your Word: " << key << endl << endl;
        results = findAll(key);
        auto end = chrono::steady_clock::now();   //end action timer
            cout << termcolor::red <<count << "Total Words Found in Elapsed Time: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;    //print nanoseconds used to finish action
        if(count >= 10){
        for(int i = 0; i < 10; i++){
          cout << results[i] << ", "; 
        }
      }
            cout << endl;
            count = 0;    //word count
            cout << endl;
          }
        }
    
};

 /**
 * findAll
 * 
 * Description:
 *      Also almost identical to main from P02
 *      
 */
int main() {
  Tries trie;
  string key;
  vector<string> lastResult;

  ifstream infile;  //to read our text file
  char k;
  Timer T;
  infile.open("dictionary.txt");    //open file
  
  auto start = chrono::steady_clock::now();  //start timer

  //as reads file to key keep looping
  while(infile >> key){
    trie.insert(key);   //adds element to list
  }

  auto end = chrono::steady_clock::now();   //ends timer

  trie.findWord();
}