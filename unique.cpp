/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Eduardo Hernandez
 * Date        : 09/23/2023
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

/**
 * @brief checks if all characters in string are lowercase
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    for(size_t i = 0; i < s.length(); i++){
        if(s[i] < 'a' || s[i] > 'z'){  
            return false;
        }
    }
    return true; 

}
/**
 * @brief checks if all characters in string are unique 
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool all_unique_letters(const string &s) {
    unsigned int vector = 0;
    unsigned int setter;
    
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    for(size_t i = 0; i < s.length(); i++){
        setter = 1 << (s[i] - 'a'); //place current character in position in setter
       
       

        if((setter & vector) == 0){
            vector = vector | setter; // update vector to check next case 
        }
        else{
            return false;
        }
    }
    return true;  //if the loop terminates, that means there are no repeated characters
}

 
int main(int argc, char *argv[]) {

    //check if correct number of parameters have been passed to the program
    if(argc != 2){
        cerr << "Usage: " << "./unique <string>" << endl; 
        return 1; 
    }

    //check if all characters are lowercase
    if(!(is_all_lowercase(argv[1]))){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1; 
    }

    //check if all characters are unique 
    if(!(all_unique_letters(argv[1]))){
        cerr << "Duplicate letters found." << endl;
        return 1; 
    }else{
        cout << "All letters are unique." << endl;
    }


    return 0;
}