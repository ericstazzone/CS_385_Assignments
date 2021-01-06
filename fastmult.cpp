/*******************************************************************************
 * Name          : fastmult.cpp
 * Author        : Eric Stazzone
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : November 26, 2020
 * Description   : Implements the fast multiplication algorithm; divide and conquer.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

string add(const string &a, const string &b){
	string n1 = a;
	string n2 = b;
	reverse(n1.begin(), n1.end());
	reverse(n2.begin(), n2.end());

}

string subtract(const string &a, const string &b){
	string result = "";
	int lenA = a.length();
	int lenB = b.length();

	return "0";
}

string multiply(const string &a, const string &b){
	return "0";
}

string fastmult(const string &a, const string &b){
	return "0";
}

int main(int argc, char *argv[]){
	istringstream iss;
	string n1, n2;
	cout << "Enter the first factor: ";
	cin >> n1;
	cout << "Enter the second factor: ";
	cin >> n2;
	string stringAns = add(n1,n2);
	stringstream stringToIntAns(stringAns);
	int printAns = 0;
	stringToIntAns >> printAns;
	cout << printAns << endl;
}





