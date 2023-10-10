/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Eduardo Hernandez
 * Date        : 9/19/2023
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honors System.
 ******************************************************************************/
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath> 

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);
    

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;


private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
        
    sieve();
}

/**
 * @brief display primes in the format specified 
 * uses a variable decrement to print each line. When decrement hits 1, that means we are on the last prime allowed in that line
 * if the number is the max prime, it will print it with no space fater it 
 */
void PrimesSieve::display_primes() const {
    
    const int max_prime_width = num_digits(max_prime_),
    primes_per_row = 80 / (max_prime_width + 1);
    int decrement = primes_per_row;

   if(primes_per_row > num_primes_){
        for(int i = 2; i <= limit_; i++){
                if(is_prime_[i] == true){
                    if(i == max_prime_){
                        cout << setw(0) << i;
                    }
                    else{
                        cout << i << " ";
                    }
                }
            }
        }

    else{
        for(int i = 2; i <= limit_; i++){
            if(is_prime_[i] == true){
                if(i == max_prime_){
                    cout << setw(0) << i;
                }else{
                      if(decrement == 1){
                        cout << setw(max_prime_width) << i << endl;
                        decrement = primes_per_row;
                        }
                        else{
                            cout << setw(max_prime_width) << i << " ";
                            decrement--;

                        }
                    }
                }
            }
        }
    }
    
     
    
    // TODO: write code to display the primes in the format specified in the
    // requirements document.



/**
 * @brief sieve algorithm taken from pseudocode
 * it will mark all multiples of i in the current iteration as false
 * the remainding true elements are the prime numbers, the prime number is their index starting at 2
 */
void PrimesSieve::sieve() {
  


    //initialize array of booleans first
    for(int i = 0; i <= limit_; i++){
        is_prime_[i] = true;
    }

    //sieves algorithm
    for(int i = 2; i <= sqrt(limit_); i++){
        if (is_prime_[i] == true){
            for(int j = i * i; j <= limit_; j+=i){
                is_prime_[j] = false;
            }

        }
    }
    
    //get number of primes 
    num_primes_ = 0;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i] == true){
            num_primes_++;
        
        }
    }
    
    // find max prime 
    
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i] == true) {
            max_prime_ = i;
        }
    }
 
    cout << endl << "Number of primes found: " << num_primes_ << endl;

    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
}

/**
 * @brief will count the number of digits of a number
 * for each division by 10, the counter increments by 1, returning the total digits when finished
 * @param num 
 * @return int 
 */
int PrimesSieve::num_digits(int num) {


    int count = 0;
    int total = num;
    while (total> 0){
        total = total / 10;
        count ++;


    }
    return count;

    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    return 0;
}

/**
 * @brief will count the number of primes that are in the range (2,n inclusive)
 * when the value of the array is true, that means the number is prime
 * @return int 
 */


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
    PrimesSieve primes (limit);
    cout << "Primes up to " << limit_str << ":" << endl;
    primes.display_primes();

    return 0;
}
