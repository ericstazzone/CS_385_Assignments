/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Patrick Juliano and Eric Stazzone
 * Date        : October 19, 2020
 * Description : Solving the water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;
struct State { // Struct to represent state of water in the jugs.
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
		a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

	string to_string() { // String representation of state in tuple form.
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

string bfs(int a, int b, int c, int d, int e, int f) {
	queue <State *> q;
	State * start = new State(0, 0, c, "Initial state. (0, 0, " + to_string(c) + ")");
	q.push(start);
	State * goal = new State(d, e, f, "Final state.");

	vector<vector<State *>> v = vector<vector<State *>>(a+1,vector<State *>(b+1, nullptr));

	while (!(q.empty())) {
		State * current = q.front();
		q.pop();
		if (current->to_string() == goal->to_string()) {
			// return backtracked solution
			// Follow pointers to each state's parent until the parent is the null pointer
			// Add each state to a vector
			// Iterate through the vector, printing the states and their directions
			vector<State *> visited;
			State * temp = current;
			while (temp != nullptr) {
				visited.insert(visited.begin(), temp);
				temp = temp->parent;
			}
			for (long unsigned int i=0; i<visited.size(); i++) { // loop over vector delete everything inside it
				cout << visited[i]->directions << endl;
			}
			delete start;
			delete goal;
			for (int i=0; i<a+1; i++) {
				for (int j=0; j<b+1; j++) {
					delete v[i][j];
				}
			}
			return "";
		}
		int newA;
		int newB;
		int newC;
		int pour;
		string amount;
		// C to A
		if ((current->c != 0) && (current->a != a)) {
			int room = a - current->a;
			if (current->c <= room) {
				newA = current->a + current->c;
				newC = 0;
				pour = current->c;
			} else {
				newA = a;
				newC = current->c - room;
				pour = room;
			}
			if (pour == 1){
				amount = " gallon ";
			} else {
				amount = " gallons ";
			}
			State * newState = new State (newA, current->b, newC, "Pour " + to_string(pour) + amount + "from C to A. (" + to_string(newA) + ", " + to_string(current->b) + ", " + to_string(newC) + ")");
			newState->parent = current;
			if (v[newState->a][newState->b] == nullptr) {
				v[newState->a][newState->b] = newState;
				q.push(newState);
			} else {
				delete newState;
			}
		}

		// B to A
		if ((current->b != 0) && (current->a != a)) {
			int room = a - current->a;
			if (current->b <= room) {
				newA = current->a + current->b;
				newB = 0;
				pour = current->b;
			} else {
				newA = a;
				newB = current->b - room;
				pour = room;
			}
			if (pour == 1){
				amount = " gallon ";
			} else {
				amount = " gallons ";
			}
			State * newState = new State (newA, newB, current->c, "Pour " + to_string(pour) + amount + "from B to A. (" + to_string(newA) + ", " + to_string(newB) + ", " + to_string(current->c) + ")");
			newState->parent = current;
			if (v[newState->a][newState->b] == nullptr) {
				v[newState->a][newState->b] = newState;
				q.push(newState);
			} else {
				delete newState;
			}
		}

		// C to B
		if ((current->c != 0) && (current->b != b)) {
			int room = b - current->b;
			if (current->c <= room) {
				newB = current->b + current->c;
				newC = 0;
				pour = current->c;
			} else {
				newB = b;
				newC = current->c - room;
				pour = room;
			}
			if (pour == 1){
				amount = " gallon ";
			} else {
				amount = " gallons ";
			}
			State * newState = new State (current->a, newB, newC, "Pour " + to_string(pour) + amount + "from C to B. (" + to_string(current->a) + ", " + to_string(newB) + ", " + to_string(newC) + ")");
			newState->parent = current;
			if (v[newState->a][newState->b] == nullptr) {
				v[newState->a][newState->b] = newState;
				q.push(newState);
			} else {
				delete newState;
			}
		}

		// A to B
		if ((current->a != 0) && (current->b != b)) {
			int room = b - current->b;
			if (current->a <= room) {
				newB = current->b + current->a;
				newA = 0;
				pour = current->a;
			} else {
				newB = b;
				newA = current->a - room;
				pour = room;
			}
			if (pour == 1){
				amount = " gallon ";
			} else {
				amount = " gallons ";
			}
			State * newState = new State (newA, newB, current->c, "Pour " + to_string(pour) + amount + "from A to B. (" + to_string(newA) + ", " + to_string(newB) + ", " + to_string(current->c) + ")");
			newState->parent = current;
			if (v[newState->a][newState->b] == nullptr) {
				v[newState->a][newState->b] = newState;
				q.push(newState);
			} else {
				delete newState;
			}
		}

		// B to C
		if ((current->b != 0) && (current->c != c)) {
			int room = c - current->c;
			if (current->b <= room) {
				newC = current->c + current->b;
				newB= 0;
				pour = current->b;
			} else {
				newC = c;
				newB = current->b - room;
				pour = room;
			}
			if (pour == 1){
				amount = " gallon ";
			} else {
				amount = " gallons ";
			}
			State * newState = new State (current->a, newB, newC, "Pour " + to_string(pour) + amount + "from B to C. (" + to_string(current->a) + ", " + to_string(newB) + ", " + to_string(newC) + ")");
			newState->parent = current;
			if (v[newState->a][newState->b] == nullptr) {
				v[newState->a][newState->b] = newState;
				q.push(newState);
			} else {
				delete newState;
			}
		}

		//A to C
		if ((current->a != 0) && (current->c != c)) {
			int room = c - current->c;
			if (current->a <= room) {
				newC = current->c + current->a;
				newA= 0;
				pour = current->a;
			} else {
				newC = c;
				newA = current->a - room;
				pour = room;
			}
			if (pour == 1){
				amount = " gallon ";
			} else {
				amount = " gallons ";
			}
			State * newState = new State (newA, current->b, newC, "Pour " + to_string(pour) + amount + "from A to C. (" + to_string(newA) + ", " + to_string(current->b) + ", " + to_string(newC) + ")");
			newState->parent = current;
			if (v[newState->a][newState->b] == nullptr) {
				v[newState->a][newState->b] = newState;
				q.push(newState);
			} else {
				delete newState;
			}
		}

	}
	delete start;
	delete goal;
	for (int i=0; i<a+1; i++) {
		for (int j=0; j<b+1; j++) {
			delete v[i][j];
		}
	}
	cout << "No solution." << endl;
	return "";
}

int main(int argc, char * const argv[]) {
	int parameters[6];	// Interpret as {<cap A>, <cap B>, <cap C>, <goal A>, <goal B>, <goal C>}
	string jugs[] = {"A", "B", "C"};
	istringstream iss;

	if (argc != 7) {	// Checks for invalid argument count
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	for (int i = 0; i < 3; i++) {	// Checks for invalid capacities
		iss.str(argv[i + 1]);
		if ((!(iss >> parameters[i])) || (parameters[i] < 1)) {
			cerr << "Error: Invalid capacity '" << argv[i + 1] << "' for jug " << jugs[i] << "." << endl;
			return 1;
		}
		iss.clear();
	}
	for (int i = 0; i < 3; i++) {	// Checks for invalid goals
		iss.str(argv[i + 4]);
		if ((!(iss >> parameters[i + 3])) || (parameters[i + 3] < 0)) {
			cerr << "Error: Invalid goal '" << argv[i + 4] << "' for jug " << jugs[i] << "." << endl;
			return 1;
		}
		iss.clear();
	}
	for (int i = 0; i < 3; i++) {
		if (parameters[i + 3] > parameters[i]) {	// Checks for goals exceeding respective capacities
			cerr << "Error: Goal cannot exceed capacity of jug " << jugs[i] << "." << endl;
			return 1;
		}
	}
	if (parameters[3] + parameters[4] + parameters[5] != parameters[2]) {	// Checks if total goal exceeds capacity of jug C
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	bfs(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], parameters[5]);
}
