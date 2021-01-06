/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Patrick Juliano and Eric Stazzone
 * Version     : 1.0
 * Date        : October 30, 2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long total = 0;
	for (int i=0; i<length; i++) {
		for (int j=i+1; j<length; j++) {
			if (array[i] > array[j]) {
				total++;
			}
		}
	}
	return total;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	vector<int> scratch(length);
	return mergesort(array, &scratch[0], 0, length - 1);
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long total = 0;
	if (low < high) {
		int mid = low + (high - low) / 2;
		total += mergesort(array, scratch, low, mid) + mergesort(array, scratch, mid + 1, high);
		int L = low;
		int H = mid + 1;
		for (int i=low; i<=high; i++) {
			if ((L <= mid) && ((H > high) || (array[L] <= array[H]))){
				scratch[i] = array[L];
				L++;
			} else {
				total += mid - L + 1;
				scratch[i] = array[H];
				H++;
			}
		}
		for (int i=low; i<=high; i++) {
			array[i] = scratch[i];
		}
	}
	return total;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	istringstream argiss;
	if (argc > 2) {
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
	if (argc == 2) {
		string option;
		argiss.str(argv[1]);
		argiss >> option;
		if (option != "slow") {
			cerr << "Error: Unrecognized option '" << option << "'." << endl;
			return 1;
		}
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (str == "") {
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }

    // TODO: produce output
    cout << "Number of inversions: ";
    if (argc == 2) {
    	cout << count_inversions_slow(&values[0], values.size()) << endl;
    } else {
    	cout << count_inversions_fast(&values[0], values.size()) << endl;
    }
    return 0;
}
