/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Eric Stazzone
 * Date        : September 30th, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways,result;
	if (num_stairs <= 0){
		vector<int> stair; //base case
		ways.push_back(stair);
	}
	else{
		for (int i = 1; i < 4; i++){
			if (num_stairs >= i){
				result = get_ways(num_stairs - i); //recursion
				for (unsigned int j = 0; j<result.size(); j++){
					result[j].insert(result[j].begin(), i); //inserts the path at the beginning of the left
				}
				ways.insert(ways.end(), result.begin(), result.end()); //adds the path in ways
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	if (ways.size() == 1){
			cout << "1 way to climb 1 stair." << endl; //1 way can only account for 1 stair therefore it is the only case
	}
	else{
		int counter = 0;
		for (unsigned int j = 0; j<ways[0].size(); j++){ //finding # of stairs
			counter = counter + ways[0][j];
		}
		cout << ways.size() << " ways to climb " << counter << " stairs." << endl;
	}
	int max_width = 0;
	int max = ways.size();
	while (max !=0){
		max = max / 10; //counts the # digits in max
		++max_width;
	}
	for (unsigned int i = 0; i<ways.size(); i++){
		cout << setw(max_width) << i+1 << ". [";
		for(unsigned int j = 0; j<ways[i].size(); j++){
			if (j == ways[i].size()-1){
				cout << ways[i][j];
			}
			else{
				cout << ways[i][j] << ", "; //prints out 1 way to climb
			}
		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	if (argc!=2){
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	int n;
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss>>n) || n<=0){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	vector<vector<int>> stairs = get_ways(n);
	display_ways(stairs);
	iss.clear();
	return 0;
}
