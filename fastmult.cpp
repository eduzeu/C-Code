/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Eduardo Hernandez 
 * Version     : 1.0
 * Date        : 11/12/2023
 * Description : Karatsuba algorithm 
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <cstring>
#include <string>
#include <cmath> 

using namespace std;

/**
 * @brief add two numbers as strings. It has been implemented like this so that it can handle very large numbers without exceeding 
 * 
 * @param a 
 * @param b 
 * @return string 
 */
string add(const string& a, const string& b) {
    string result;
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int x, y;

        //getting current rightmost digit
        if (i >= 0) {
            x = a[i] - '0';
            i--;
        } else {
            x = 0;
        }
        //getting current rightmost digit
        if (j >= 0) {
            y = b[j] - '0';
            j--;
        } else {
            y = 0;
        }

        int sum = x + y + carry;
        carry = sum / 10;
        sum %= 10;

        char digit = char((sum + '0'));
        result = digit + result;
    }

    return result;
}

/**
 * @brief subtract two string representing integers. Implemented this way so it does not overflow with very large numbers
 * 
 * @param a 
 * @param b 
 * @return string 
 */
string subtract(const string& a, const string& b) {
    string result;
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0) {
        int x,y;
        
          if (i >= 0) {
            x = a[i] - '0';
            i--;
        } else {
            x = 0;
        }

        if (j >= 0) {
            y = b[j] - '0';
            j--;
        } else {
            y = 0;
        }

        int diff = x - y - carry;

        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result = char(diff + '0') + result;
    }

    // Remove leading zeros
    size_t lz = result.find_first_not_of('0');
    string subtract =  (lz != string::npos) ? result.substr(lz) : "0";
    return subtract;
}

/**
 * @brief padd leading zeros if numbers are not of same length 
 * 
 * @param a 
 * @param b 
 */
void get_equal_length(string &a, string &b) { 
    string zero = "0";
    while (a.length() != b.length()) {
        if (a.length() < b.length()) {
            a = zero + a;
        } else if (a.length() > b.length()) {
            b = zero + b;
        }
    }
}

/**
 * @brief multiply string representations handling the overflow
 * 
 * @param a 
 * @param b 
 * @return string 
 */
string multiply(const string& a, const string& b) {
    string result;
    long long len_a = a.length();
    long long len_b = b.length();
    result.resize(len_a + len_b, '0');

    for (int i = len_a - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len_b - 1; j >= 0; --j) {
            int temp = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
            result[i + j + 1] = temp % 10 + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }

    // Remove leading zeros
    size_t pos = result.find_first_not_of('0');
    string multy =  (pos != string::npos) ? result.substr(pos) : "0";
    return multy;
}

/**
 * @brief recursive karatsuba alrorithm
 * 
 * @param a 
 * @param b 
 * @return string 
 */
string karatsuba_algorithm(const string& a, const string& b){

    //base case, when numbers are 1 digit just multiply them 
    if (a.length() <= 1 || b.length() <= 1) {
        return multiply(a,b);
    }

    int n = max(a.length(), b.length());
    int m = n / 2;

    string a0 = a.substr(0, a.length() - m);
    string a1 = a.substr(a.length() - m);
    string b0 = b.substr(0, b.length() - m);
    string b1 = b.substr(b.length() - m);

    string ac = karatsuba_algorithm(a0, b0);
    string bd = karatsuba_algorithm(a1, b1);
    string ac_plus_bd = karatsuba_algorithm(add(a0, a1), add(b0, b1));
    string ac_plus_bd_minus_bd = subtract(subtract(ac_plus_bd, ac), bd);

    string result = add(add(ac + string(m * 2, '0'), ac_plus_bd_minus_bd + string(m, '0')), bd);

    size_t pos = result.find_first_not_of('0');

    return (pos != string::npos) ? result.substr(pos) : "0"; 

}

int main(int argc, char *argv[]){ 

    string a(argv[1]);
    string b(argv[2]);

    get_equal_length(a, b);
    string test = karatsuba_algorithm(a, b);
    cout << test << endl;

    if(test == multiply(a, b)){
        cout << "Karatsuba working!" << endl; 
    }else{
        cout << "something went wrong!" << endl; 
    }
    return 0; 
}

