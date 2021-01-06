/*
 * pointers.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: user
 */

#include <iostream>
using namespace std;

void display_array(int array[], const int length){
	cout << "[";
	if (length>=1){
		cout << array[0];
	}
	for (int i=1; i<length; ++i){
		cout <<  ", " << array[i];
	}
	cout << "]" << endl;
}

void display_array_ptr(int array[], const int length){ //reference
	cout << "[";
	if (length >= 1){
		cout << *array; //will give you back the value in the 0th element in the data type
	}
	for (int *ptr = array + 1, *end = array + length; ptr < end; ++ptr){ //*ptr will give you the value in that array
		cout << ", " << *ptr;
	}
	cout << "]";
}

void pass_by_value(int x){
	x = 10;
}

void pass_by_pointer(int *x){
	*x =10;
}

void pass_by_reference(int &x){
	x = 10;
}

int main(){
	int x = 5, *z=&x; //z points to x
	cout << &x << " " << z << endl;
	cout << x << " " << *z << endl; //* means to dereference it
	int y = 6;
	cout << x << " " << y << endl;
	*z = 7; //writing in to where 7 points to (in the memory location)
	cout << x << " " << y << endl; //x is mutated to 7
	z = &y;
	*z = 7;
	cout << x << " " << y << endl; //y is mutated to 7'
	cout << &x << " " << &y << " " << z << endl;
	z--; //simplest form of pointer arithmetic, 4 bytes, decremented data
	cout << &x << " " << &y << " " << z << endl;
	z++;
	z++;
	cout << *z << endl; //points to a place in memory that is not initialized
	z += 30000;
	// cout << *z << endl; //segmentation fault (core dumped)
	// *z = 700; gdb ./pointers (runs program until it crashes)

	int *values = new int[y]; //y rn is a size of 7
	for (int i=0; i<y; i++){
		// values[i] = i; subscripting
		*(values + i) = i;
	}
	display_array(values, y);
	display_array_ptr(values, y);
	delete [] values; //required to not have any memory leaks

	x=5; //great for passing primitives
	y=6;
	pass_by_value(x);
	cout << x << " " << y << endl;

	x=5; //not good
	y=6;
	pass_by_pointer(&x);
	cout << x << " " << y << endl;

	x=5; //safer
	y=6; //pass collections by reference, or a function returning two things
	pass_by_reference(x);
	cout << x << " " << y << endl;
	return 0;
}


