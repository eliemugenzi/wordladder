/* TODO - IMPROVE 
 * if no ladder exist -  message
 */

/*
 * File: ladder2.cpp
 * ----------------------
 * This program finds a minimal word ladder between two words.
 * A word ladder is a connection from one word to another formed 
 * by changing one letter at a time with the constraint that at each 
 * step the sequence of letters still forms a valid word. 
 * 
 * For example, here is a word ladder connecting "slow" to "fast".
 * slow > flow > flaw > flat > fiat > fist > fast
 * Based on Data Structures Assignment of Word ladder,
 * By Lecturer Theoneste Murangira, March '23 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <set>
using namespace std;

/* Constants */
const int ALPHA_LENGTH = 26;

/* Prototypes */
void getWords(string &word1, string &word2);
void printWordLadder(string word1, string word2);

/* Main function */
int main() {
    
  string word1, word2;
  getWords(word1, word2); 
  printWordLadder(word1, word2);
    
  return 0;
}

/*
 * Function: getWords
 * Usage: getWords(word1, word2)
 * -----------------------------
 * This function takes two strings as parameter (passed by reference), 
 * prompts the user for her input and stores her answer in those two
 * parameters.
 *
 * The user must enter strings of same length, otherwise the function
 * keeps asking for new words.
 */

void getWords(string &word1, string &word2) {
  while (true) {
    cout << "Please enter a word: ";
    cin>>word1;
    
    cout << "Please enter another word of the same length: ";
    cin>>word2;
    
    if (word1.length() == word2.length()) {
      break;
    }
    cout << "Please enter two words with the same length." << endl;
  }
}


/* Function: printWordLadder
 * Usage: printWordLadder(word1, word2) 
 * ------------------------------
 * This function takes two strings as parameters and prints the 
 * minimal word ladder between two words.
 * 
 * A word ladder is a connection from one word to another formed 
 * by changing one letter at a time with the constraint that at each 
 * step the sequence of letters still forms a valid word.
 */

void printWordLadder(string word1, string word2){
    
    // creates an empty queue of stacks
    queue<stack<string> > myQueue;
    
    //Create a stack which will contain a final word ladder
    stack<string> wordladder;
    
    // creates and adds a stack containing word1 to the queue
    stack<string> myStack;
    myStack.push(word1);
    myQueue.push(myStack);
    
    // creates two sets: one for the dictionary and one for the tested words
    string token;
    ifstream dictionary("dictionary.txt");
    set<string> myDictionary;
    set<string> testedWords;
    
    if(dictionary.is_open()) {
      
	      while (dictionary >> token) {
	    	myDictionary.insert(token);
	      }
	      
	      // while the queue is not empty:
	      while (!(myQueue.empty())) {
	        
	        // dequeue the partial-ladder stack from the front of the queue.
			stack<string> ladder = myQueue.front();
			myQueue.pop();
			string word = ladder.top();
		        
			// if the word on top of the stack is the destination word:
			if (word == word2) {
			
			  // Yeey! output the elements of the stack as the solution.
			  cout << "The ladder from " << word1 << " to " << word2 << " is \n";
			 
			  //Copy the ladder stack to worldladder to take it in the order.
			  while(!ladder.empty()){
			  	wordladder.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!wordladder.empty()){
			  	cout<<wordladder.top()<<" > ";
			  	wordladder.pop();
			  }
		} 
		else {
			  // for each valid English word that is a "neighbor" (differs by 1 letter) of the word on top of the stack:
			  string test;
			  for (int i = 0; i < word.size(); i++) {
			    for (char j = 'a'; j <= 'z'; j++) {
			    test = word.substr(0, i) + j + word.substr(i + 1);
		            
			    // if that word is an english word
			    if (myDictionary.count(test)) {
			      
			      // if that neighbor word has not already been used in a ladder before:
			      if (!testedWords.count(test)) {
				
						// create a copy of the current ladder stack.
						stack<string> copy = ladder;
				                
						// put the neighbor word on top of the copy stack.
						copy.push(test);
				                
						// add the copy stack to the end of the queue.
						myQueue.push(copy);
			      }
			    }
		            
			    // Add test to tested words because it is already used.
			    testedWords.insert(test);
			}
		}
	      }
	    }
    } else {
      cerr << "Couldn't open the dictionary" << endl;
    }
    
    
}
