/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Eric Stazzone
 * Date        : September 22nd, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise;
	for (unsigned int i = 0; i < s.size(); i++){
		if (isupper(s[i]) || isdigit(s[i])){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int vector = 0;
	unsigned int setter;
	for (unsigned int i = 0; i < s.size(); i++){
		setter = 1 << (s[i] - 'a'); //bitshift to get input character [i] in string
		if ((vector & setter) != 0){ //bitwise AND
			return false; //cut out if found
		}
		vector = vector | setter; //bitwise OR the two values together
	}
	return true; //return true if passed through string had no duplicates
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if (argc != 2){
		cerr << "Usage: ./unique <string>"; //if it isnt 1 string as input
		return 1;
	}
	if (!(is_all_lowercase(argv[1]))){
		cerr << "Error: String must contain only lowercase letters." << endl; //if the string is not in lowercase letters
		return 1;
	}
	if (all_unique_letters(argv[1])){ //result of method (true or false)
		cout << "All letters are unique." << endl;
	}
	else{
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}
