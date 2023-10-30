/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Eduardo Hernandez 
 * Version     : 1.0
 * Date        : 10/31/2023
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
#include <string> 

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long num = 0;
    for(int i = 0; i < length-1 ; i++){
        for(int j = i+1; j < length; j++){
            if(array[i] > array[j]){
                num +=1; 
            }
        }
    }
    return num;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    long num = 0;
    int *arr = new int[length];

    num = mergesort(array, arr, 0, length-1);

    delete[] arr;
  
    return num; 
}

long merge(int arr[], int scratch[], int low, int mid, int high){
    
    int j = low;
    int k = mid+ 1;
    int i = low; 
    long inversions = 0; 
    while(j <= mid && k <= high){
        if(arr[j] <= arr[k]){
            scratch[i++] = arr[j++];
        }
        else{
            scratch[i++] = arr[k++];
            inversions = inversions + (mid -j + 1); //update count 
        }
    }
  
    for(int a = j; a <= mid; a++){
        scratch[i++] = arr[a];
    }

    for(int b = k; b <= high; b++){
        scratch[i++] = arr[b];

    }
    //copy B[lo..hi] back into A[lo..hi]

    for(int i = low; i <= high; i++){
        arr[i] = scratch[i];
    }
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long count = 0; 
    if(low < high){
        int mid = low + (high - low)/2;
        count += mergesort(array, scratch, low, mid);//recursion on left side 
        count += mergesort(array, scratch, mid+1, high); //recursion on right side 
        count += merge(array, scratch, low, mid, high);
        
    }
    return count;
}

/**
 * @brief function created to check for correct input, takes ascii value of the string and compares it to slow, which should be the right type
 * 
 * @param slow 
 * @return int 
 */
int ascii(string slow){
    int total = 0;
    for(string::size_type i = 0; i < slow.length(); i++){
        total += slow[i];
    }
    return total; 
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" << endl; 
        return 1; 
    }

    if (argc == 2) {
    //453 is the ascii score of word "slow"
        if(ascii(argv[1]) != 453){
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
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
    
    int* val = &values[0];
    int vec_size = values.size(); 
    // int num; 

    if(vec_size == 0){
        cerr << "Error: Sequence of integers not received." << endl; 
        return 1; 
    }


  
    long n = count_inversions_slow(val, vec_size);
    long m = count_inversions_fast(val, vec_size);

    // TODO: produce output
    if(argc == 2){
        cout << "Number of inversions (slow): " << n << endl; 
    }else if(argc == 1){
        cout << "Number of inversions (fast): " << m << endl; 
    }

    return 0;
}
