/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Patrick Juliano and Eric Stazzone
 * Date        : December 7, 2020
 * Description : Solves the all pairs shortest paths problem with Floyd's algorithm.
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

void display_table(long** const matrix, const string &label, int vertices, const bool use_letters) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			long cell = matrix[i][j];
			if ((cell < numeric_limits<unsigned int>::max()) && (cell > max_val)) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = use_letters ? to_string(max_val).length() : to_string(max(static_cast<long>(vertices), max_val)).length();
	cout << ' ';
	for (int j = 0; j < vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == numeric_limits<unsigned int>::max()) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

long** floyd(long** paths, long** intermediates, int vertices) {
	for (int k = 0; k < vertices; k++) {
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++) {
				long old = paths[i][j];
				paths[i][j] = min(paths[i][j], paths[i][k] + paths[k][j]);
				if (paths[i][j] < old) {
					intermediates[i][j] = k;
				}
			}
		}
	}
	return paths;
}

string printRecursive(int i, int j, long** intermediates) {
	if (intermediates[i][j] == numeric_limits<unsigned int>::max()) {
		cout << static_cast<char>(i + 'A') << " -> ";
		return "";
	}
	cout << printRecursive(i, (int)intermediates[i][j], intermediates) << printRecursive((int)intermediates[i][j], j, intermediates);
	return "";
}

void print(long** paths, long** intermediates, int vertices) {
	string distance;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", distance: ";
			if (paths[i][j] == numeric_limits<unsigned int>::max()) {
				cout << "infinity, path: none" << endl;
			} else {
				cout << paths[i][j] << ", path: ";
				if (i != j) {
					printRecursive(i, j, intermediates);
				}
				cout << static_cast<char>(j + 'A') << endl;
			}


			/*
			int start = i;
			int end = j;
			if (i != j) {
				cout << static_cast<char>(i + 'A') << " -> ";
			}
			while (intermediates[start][end] != numeric_limits<int>::max()) {
				cout << static_cast<char>(intermediates[start][end] + 'A') << " -> ";
				start = intermediates[start][end];
			}
			cout << static_cast<char>(j + 'A') << endl;
			*/
		}
	}
}

int main(int argc, char *argv[]) {
	if ((argc <= 1) || (argc >= 3)) {
		cerr << "Usage: ./shortestpaths <filename>" << endl;
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

	if (!(iss >> vertices) || (vertices <= 0) || (vertices >= 27)) {
		cerr << "Error: Invalid number of vertices '" << line << "' on line " << lineNum << "." << endl;
		return 1;
	}

	long** matrix = new long*[vertices];
	for (int i = 0; i < vertices; i++) {
		matrix[i] = new long[vertices];
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			} else {
				matrix[i][j] = numeric_limits<unsigned int>::max();
			}
		}
	}

	string v1Str = "";
	string v2Str = "";
	string weightStr = "";
	int spaces = 0;
	bool weightError = false;
	char v1;
	char v2;
	int weight;

	while (getline (file, line)) {
		lineNum++;

		if (line.length() < 5) {
			cerr << "Error: Invalid edge data '" << line << "' on line " << lineNum << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}
		for (int i = 0; i < (int)line.length(); i++) {
			if (isblank(line[i])) {
				spaces++;
			} else if (spaces == 0) {
				v1Str += line[i];
			} else if (spaces == 1) {
				v2Str += line[i];
			} else if (spaces == 2) {
				if (!(isdigit(line[i]))) {
					weightError = true;		// We catch the error here only to report it later down the line due to the order of precedence in the test file.
				}
				weightStr += line[i];
			} else {
				cerr << "Error: Invalid edge data '" << line << "' on line " << lineNum << "." << endl;
				for (int i = 0; i < vertices; i++) {
					delete[] matrix[i];
				}
				delete[] matrix;
				return 1;
			}
		}

		if (v1Str.length() != 1) {
			cerr << "Error: Starting vertex '" << v1Str << "' on line " << lineNum << " is not among valid values A-" << (char)(vertices + 64) << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}
		v1 = v1Str[0];
		if (!(((v1 - 64) >= 1) && ((v1 - 64) <= vertices) && isupper(v1))) {
			cerr << "Error: Starting vertex '" << v1Str << "' on line " << lineNum << " is not among valid values A-" << (char)(vertices + 64) << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}
		if (v2Str.length() != 1) {
			cerr << "Error: Ending vertex '" << v2Str << "' on line " << lineNum << " is not among valid values A-" << (char)(vertices + 64) << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}
		v2 = v2Str[0];
		if (!(((v2 - 64) >= 1) && ((v2 - 64) <= vertices) && isupper(v2))) {
			cerr << "Error: Ending vertex '" << v2Str << "' on line " << lineNum << " is not among valid values A-" << (char)(vertices + 64) << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}
		if (weightError) {
			cerr << "Error: Invalid edge weight '" << weightStr << "' on line " << lineNum << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}
		weight = stoi(weightStr);
		if (weight <= 0) {
			cerr << "Error: Invalid edge weight '" << weightStr << "' on line " << lineNum << "." << endl;
			for (int i = 0; i < vertices; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 1;
		}

		matrix[v1 - 65][v2 - 65] = (long)weight;

		v1Str = "";
		v2Str = "";
		weightStr = "";
		spaces = 0;
		weightError = false;
	}

	long** paths = new long*[vertices];
	for (int i = 0; i < vertices; i++) {
		paths[i] = new long[vertices];
	}
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			paths[i][j] = matrix[i][j];
		}
	}
	long** intermediates = new long*[vertices];
	for (int i = 0; i < vertices; i++) {
		intermediates[i] = new long[vertices];
	}
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			intermediates[i][j] = numeric_limits<unsigned int>::max();
		}
	}

	display_table(matrix, "Distance matrix:", vertices, false);
	display_table(floyd(paths, intermediates, vertices), "Path lengths:", vertices, false);
	display_table(intermediates, "Intermediate vertices:", vertices, true);
	print(paths, intermediates, vertices);

	for (int i = 0; i < vertices; i++) {
		delete[] matrix[i];
		delete[] paths[i];
		delete[] intermediates[i];
	}
	delete[] matrix;
	delete[] paths;
	delete[] intermediates;

	return 0;
}
