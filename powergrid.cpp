/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : Eric Stazzone
 * Date        : December 16, 2020
 * Description : Establish powergrid in city by using minimal wire.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct Line { //Struct to represent the road, its start/end points, weight and name
	int v1;
	int v2;
	long weight;
	string street;

};

bool sortByWeight(Line v1, Line v2){
	return v1.weight < v2.weight;
}

bool sortByStreet(Line v1, Line v2){
	return v1.street < v2.street;
}

int findNoCycle(int x, vector<int>&MSTparent){
	while (MSTparent[x]!=x){
		x = MSTparent[x];
	}
	return x;
}

void MSToutput(long** matrix, int vertices, vector<Line>&weights){

	vector<Line> MST;
	vector<int> MSTparent;
	Line min;
	int parentv1;
	int parentv2;

	sort(weights.begin(),weights.end(),sortByWeight);

	for (int i =0; i<vertices; i++){
		MSTparent.insert(MSTparent.begin()+i,i);
	}

	for (long unsigned int i = 0; i<weights.size(); i++){
		parentv1 = weights[i].v1;
		parentv2 = weights[i].v2;
		Line temp;
		temp.v1 = parentv1;
		temp.v2 = parentv2;
		temp.weight = weights[i].weight;
		temp.street = weights[i].street;
		int u1 = findNoCycle(parentv1, MSTparent);
		int u2 = findNoCycle(parentv2, MSTparent);

		if (u1!=u2){
			MST.push_back(temp);
		}

		MSTparent[u1] = u2;
	}

	long totalweight = 0;

	for (long unsigned int i = 0; i<MST.size(); i++){
		totalweight = totalweight + MST[i].weight;
	}

	sort(MST.begin(), MST.end(), sortByStreet);

	cout<<"Total wire length (meters): " << totalweight << endl;

	for(long unsigned int i = 0; i < MST.size(); i++){
		cout << MST[i].street << " [" << MST[i].weight << "]" << endl;
	}
}

int main(int argc, char *argv[]) {
	if ((argc <= 1) || (argc >= 3)) {
			cerr << "Usage: ./powergrid <input file>" << endl;
			return 1;
	}

	string line;
	ifstream file (argv[1]);

	if (!(file.is_open())) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}

	int vertices;
	int lineNum = 1;
	istringstream iss;
	getline(file, line);
	iss.str(line);

	if (!(iss >> vertices) || (vertices <= 0) || (vertices >= 1001)) {
		cerr << "Error: Invalid number of vertices '" << line << "' on line " << lineNum << "." << endl;
		return 1;
	}

	//Initialize data structure for parsing data
	long** matrix = new long*[vertices];
	for (int i = 0; i< vertices; i++){
		matrix[i] = new long[vertices];
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			matrix[i][j] = numeric_limits<long>::max();
		}
	}

	string**matrixStreet = new string*[vertices];
	for (int i = 0; i< vertices; i++){
		matrixStreet[i] = new string[vertices];
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			matrixStreet[i][j] = "";
		}
	}

	int vertCheck = 0;
	string v1Str = "";
	string v2Str = "";
	string weightStr = "";
	string streetStr = "";
	int commas = 0;
	bool weightError = false;
	bool numberError1 = false;
	bool numberError2 = false;
	int edgeDataCount = 1;
	int v1 = 0;
	int v2 = 0;
	int weight = 0;

	while(getline(file, line)){
		lineNum++;
		bool streetCheck=true;
		for (int i = 0; i < (int)line.length(); i++) {
			if (line[i] == ',') {
				commas++;
				edgeDataCount++;
			}

			else if (commas == 0){
				if (isblank(line[i])){
					continue;
				}
				if (!(isdigit(line[i])) ) {
					numberError1 = true;
				}
				v1Str += line[i];
			}

			else if (commas == 1){
				if (isblank(line[i])){
					continue;
				}
				if (!(isdigit(line[i]))) {
					numberError2 = true;
				}
				v2Str += line[i];
			}
			else if (commas == 2){
				if (isblank(line[i])){
					continue;
				}
				if (!(isdigit(line[i]))) {
					weightError = true;
				}
				weightStr += line[i];
			}

			else if (commas == 3){
				if (isblank(line[i]) && streetCheck){
					continue;
				}
				streetCheck = false;
				streetStr += line[i];
			}

			else{
				cerr << "Error: Invalid edge data '" << line << "' on line " << lineNum << "." << endl;
				for (int i = 0; i < vertices; i++) {
					delete[] matrix[i];
					delete[] matrixStreet[i];
				}
				delete[] matrix;
				delete[] matrixStreet;
				return 1;
			}
		}

		if (edgeDataCount <= 3 || edgeDataCount >= 5){
			cerr << "Error: Invalid edge data '" << line << "' on line " << lineNum << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}
		if (numberError1){
			cerr << "Error: Starting vertex '" << v1Str << "' on line " << lineNum << " is not among valid values 1-" << vertices << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}
		v1 = stoi(v1Str);

		if (v1 <= 0 || v1 >= vertices+1){
			cerr << "Error: Starting vertex '" << v1Str << "' on line " << lineNum << " is not among valid values 1-" << vertices << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}

		if (numberError2){
			cerr << "Error: Ending vertex '" << v2Str << "' on line " << lineNum << " is not among valid values 1-" << vertices << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}
		v2 = stoi(v2Str);
		if (v2 <= 0 || v2 >= vertices+1){
			cerr << "Error: Ending vertex '" << v2Str << "' on line " << lineNum << " is not among valid values 1-" << vertices << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}

		if (weightError){
			cerr << "Error: Invalid edge weight '" << weightStr << "' on line " << lineNum << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}
		weight = stoi(weightStr);
		if (weight <= 0) {
			cerr << "Error: Invalid edge weight '" << weightStr << "' on line " << lineNum << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}

		if (v1 == v2){
			cout << "No solution." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
				delete[] matrixStreet[i];
			}
			delete[] matrix;
			delete[] matrixStreet;
			return 1;
		}

		matrix[v1-1][v2-1] = (long)weight;
		matrixStreet[v1-1][v2-1] = streetStr;

		v1Str = "";
		v2Str = "";
		weightStr = "";
		streetStr = "";
		commas = 0;
		weightError = false;
		numberError1 = false;
		numberError2 = false;
		edgeDataCount = 1;

		vertCheck++;
	}

	if (vertCheck != vertices){
		cout << "No solution." << endl;
		for (int i = 0; i < vertices; i++) {
			delete[] matrix[i];
			delete[] matrixStreet[i];
		}
		delete[] matrix;
		delete[] matrixStreet;
		return 1;
	}

	vector<Line> parent;
	Line road;

	for (int i = 0; i<vertices; i++){
		for (int j = 0; j<vertices; j++){
			if (matrix[i][j]!= numeric_limits<long>::max()){
				road.v1 = i;
				road.v2 = j;
				road.weight = matrix[i][j];
				road.street = matrixStreet[i][j];
				parent.push_back(road);
			}
		}
	}

	MSToutput(matrix, vertices, parent);

	for (int i = 0; i < vertices; i++) {
			delete[] matrix[i];
			delete[] matrixStreet[i];
		}

	delete[] matrix;
	delete[] matrixStreet;

	return 0;
}
