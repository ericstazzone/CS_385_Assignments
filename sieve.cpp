/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Eric Stazzone
 * Date        : September 15th, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    num_primes_ = count_num_primes(); //returns the number of primes in the array
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
	cout << endl;
	cout << "Number of primes found: " << num_primes() << endl;
	const int max_prime_width = num_digits(max_prime_),
	 primes_per_row = 80 / (max_prime_width + 1);
	cout << "Primes up to " << limit_ << ":" << endl;
	int i = 0;
	bool check = false; //check to see if it is the last prime in the array
	if (num_primes() < primes_per_row){ //if the number of primes is less than the limit size of the console
			while (i < limit_+1){
				if (is_prime_[i] == true){ //if it is a prime
					if (i == max_prime_){ //if it is the max prime
						cout << i << endl; //end the loop
						i++;
					}
					else{
						cout << i << " "; //continue list and add a space
						i++;
					}
				}
				else{
					i++;
				}
			}
		}
	else{
		int rowcount = 0; //checks to see how many elements are in 1 row
		while(i<limit_+1 && check == false){
			if (is_prime_[i] == true){
				if (rowcount == primes_per_row){
					rowcount = 0; //if has reached the max number of primes per row, then it shifts to the next row
					cout << "\n";
				}
				if (i == max_prime_){
					cout << setw(max_prime_width) << i; //spaces out each element in the row to the max prime width
					check = true;
				}
				else{
					cout << setw(max_prime_width) << i;
					if (rowcount+1 != primes_per_row){ //make sure not to add a space at the end of the last prime in the row
						cout << " ";
					}
					i++;
					rowcount++;
				}
			}
			else{
				i++;
			}
		}
	}
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int x = 0;
	for (int i = 0; i<=limit_; i++){
		if (is_prime_[i] == true){
			x++;
		}
	}
    return x;
}

void PrimesSieve::sieve() {
	num_primes_ = 0;
	max_prime_ = limit_+1;
	is_prime_[0] = false;
	is_prime_[1] = false;
	for (int i = 2; i < limit_+1; i++){ //setting all primes to true
		is_prime_[i] = true;
	}

	for (int i = 0; i<sqrt(limit_); i++){
		if (is_prime_[i] == true){ //sieve of e alg
			for (int j = pow(i,2); j<limit_+1; j=j+i){
				is_prime_[j] = false;
			}
		}
	}

	for (int counter = 0; counter<=limit_; counter++){
		if (is_prime_[counter] == true){
			max_prime_ = counter;
		}
	}
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int c = 0;
	while (num !=0){
		num = num / 10; //counts the # digits in number
		++c;
	}
    return c;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve output = PrimesSieve(limit); //output call
    output.display_primes();
    return 0;
}
