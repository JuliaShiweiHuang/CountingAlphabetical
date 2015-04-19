/* 
 * Developer: Shiwei Huang
 * Purpose: Read a .txt file and count the unique words frequency based on alphabetical order;
 * Input: A valid file name of a file that contains arbitrary text, endint with "DONE". Valid punctuation include the set {'.', '!', '?', ':', ';', ','}.
 * User also enter 'low' and 'high' frequency.
 * Output: An aligned table showing each unique word and its frequency based on alphabetical order. Words that appear once are displayed, 10 per line.
 * Finally, after user input of 'low' and 'high', words are displayed based on the frequency order from high to low.
 *
 */
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct myNode {
/* Make a Data Structure which is a node.
 * Node contains three parts: 
 * 1. string word to store all unique words.
 * 2. int frequency to store the frequencies of the words.
 * 3. a pointer
 */
	string word;
	int frequency;
	myNode *next;
};

class trout {
	bool checkPunctuation (string );
	bool checkCapital (string );
	myNode *head, *newNode, *cur, *prev; // *cur and * prev are for checking repectative tokens;
	myNode *curAlpha, *prevAlpha; // *curAlpha and *prevAlpha are for checking the token position given the condition that token is not repectative;

public:
	void readText (string );
	void displayStats ( );
	void displayStats ( int, int );
};

/*******************************************************************************************/

int main () {
	trout myList; // instance of the trout class
	string fileName; // user's input file name
	int low, high;

	cout << "Enter file name: ";
	cin >> fileName;

	myList.readText (fileName);
	myList.displayStats ();

	cout << endl;
	cout << "Enter low count: ";
	cin >> low;
	cout << "Enter high count: ";
	cin >> high;
	myList.displayStats ( low, high );

	return 0;

}

/*******************************************************************************************/

bool trout :: checkCapital ( string token ) {
	char ch = token [0]; 
	return isupper (ch); 
}

bool trout :: checkPunctuation ( string token ) {
	char c = token [token.size()-1];
	if ( c == '.' || c == '!' || c == '?' || c == ':' || c == ';' || c == ',' ) {
		return true; 
	}

	else {
		return false;
	}
}

/*******************************************************************************************/

void trout :: readText ( string file ) {
/*
 * Method to read the input text and store all of the unique words based on alphabetical order. 
 * Precondition: file is a valid string
 * Postcondition: myNode contains all of the unique words && words frequency based on alphabetical order
 *
 */
	ifstream inFP; // input file pointer
	inFP.open ( file.c_str() );
	string token; // current token being processed
	if ( ! inFP ) {
		cout << "Error - file " << file << " not found! " << endl;
	} else {
		inFP >> token;
		bool hasPunctuation = checkPunctuation ( token );
		if ( hasPunctuation ) {
			token = token.substr ( 0, token.length()-1 );
		}

		bool hasCapital = checkCapital ( token );
		if ( hasCapital ) {
			token [0] =  tolower ( token[0] ); 
		}

	// Making variable declaration;
		head = NULL;
		while ( token != "DONE" ) {
			//bool now = true;
			cur = head; // this [searching algorithm] will always start from head
			bool found = false;
			prev = NULL;

			while ( cur != NULL && !found ) { // "!found" same as "found == false"
				// [Search Repectative Token Algorithm]: check if there's a match in the linked list
				if ( cur -> word == token ) {
					cur -> frequency = cur -> frequency + 1; // if there is a match, so update the frequency
					found = true; // this will end the loop
				}
				else { // if there's no match in the current linked list node, move onto the next node;
					prev = cur;
					cur = cur -> next; 
				}
				
			}
		    
		    // if there was no match in the currently entire linked list, add the token to a new node and update the frequency
			if ( found == false ) {
				newNode = new myNode;
				newNode -> word = token;
				newNode -> frequency = 1;
				newNode -> next = NULL;

				// if the new token is the first node, 'head' pointer points to the first node
				if ( head == NULL ) {
					head = newNode;
					cur = newNode;
				}
				else {
					curAlpha = head;
					prevAlpha = NULL;
					bool foundAlpha = false;
					
					while ( curAlpha != NULL && !foundAlpha ) { // [Searching Alphatical Algorithm] 
						if ( token < curAlpha -> word ) {
							foundAlpha = true; // if new token is alphabetically front, stop the while loop at current position
						}

						else { // if new token is alphabetically next, move to next node
							prevAlpha = curAlpha;
							curAlpha = curAlpha -> next;
						}
					}

					// [Inserting Algorithm]
					if ( prevAlpha != NULL ) { // if the pointer prevAlpha does not points to the end, inserting at middle/ end;
						newNode -> next = curAlpha;
						prevAlpha -> next = newNode;
					} 
					else { // inserting in the beginning
						newNode -> next = head;
						head = newNode;
					}

				}

				inFP >> token;

				bool hasPunctuation = checkPunctuation ( token );

				if ( hasPunctuation && token != "DONE" ) {
					token = token.substr ( 0, token.length()-1 );
				}

				bool hasCapital = checkCapital ( token );

				if ( hasCapital && token != "DONE" ) {
					token [0] = tolower ( token[0] );
				}

			} // if
			
			else { // if there is a repectative token, read next word from the file
				inFP >> token;
				bool hasPunctuation = checkPunctuation ( token );

				if ( hasPunctuation && token != "DONE" ) {
					token = token.substr ( 0, token.length()-1 );
				}

				bool hasCapital = checkCapital ( token );

				if ( hasCapital && token != "DONE" ) {
					token [0] = tolower ( token[0] );
				}
			} // while
			
		} // while
	} // else

} // readText

/*******************************************************************************************/

void trout :: displayStats () {
/*
 * Method to display my linked list based on alphabetical order
 * Precondition: myNode contains unique tokens and frequency. In addition, linked list myNode is displayed in alphabetical order
 * Postcondition: Display an aligned chart of words and frequencies based on alphabetical order
 *				  Those words that appear just once are displayed 10/line
 *
 */
	myNode * current; // pointer pointing to my current word
	myNode * currentOne;
	current = head; // pointer pointing to the head position in the beginning
	currentOne = head;

	cout << "Word           Count" << endl;
	cout << "====================" << endl;
	while ( current != NULL ) {
		
		if ( ( current -> frequency ) > 1 ) {
			cout << current -> word << setw ( 20 - current -> word.length() ) << current -> frequency << endl;
			
		}
		current = current -> next;
	}
	cout << endl;
	cout << "Words with count = 1" << endl;
	cout << "====================" << endl;
	int coutw = 0;
	while ( currentOne != NULL ) {
		if ( ( currentOne -> frequency ) == 1 ) {
			cout << currentOne -> word << " ";
			coutw += 1;
		}
		currentOne = currentOne -> next;
		if ( coutw == 10) { 
			cout << endl; // endl when 10 words have been reached
			coutw = 0;
		}
	}

	cout << endl;
	
} // displayStats

/*******************************************************************************************/

void trout :: displayStats ( int intLo, int intHi ) {
/*
 * Method to display my linked list based on user input of low and high numbers
 * Precondition: linked list contains unique tokens and frequency. In addition, linked list is ordered in alphabetical order
 * Postcondition: Display an aligned chart of words and frequencies based on ordering from words' frequency from max to min
 *
 */
	myNode * pointer;
	pointer = head;
	cout << endl;
	cout << "Word           Count" << endl;
	cout << "====================" << endl;

	for ( int i = intHi; i >= intLo; --i ) {
		pointer = head;
		while ( pointer != NULL ) {
		/* displayStats algorithm for displaying frequency by the given i
		 * If this algorithm cannot find the given frequency i, --i will lower intHi by 1
		 */
			if ( pointer -> frequency == i ) { 
				cout << pointer -> word << setw ( 20 - pointer -> word.length() ) << pointer -> frequency << endl;
				pointer = pointer -> next;  // By the given i, this algorithm will search the whole linked list 

			}
			else {
				pointer = pointer -> next; // By the given i, this algorithm will search the whole linked list 
			}
		}
	}

	cout << endl;
}
