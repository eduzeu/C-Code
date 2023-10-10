/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Eduardo Hernandez and Nyrah Balabanian 
 * Date        : 10/20/2023
 * Description : Water jug Puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honors System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream> 
#include <limits> 
#include <vector> 

using namespace std; 


int main(int argc, char* argv[]){

    // create string object 
    istringstream iss;
    // int counter = 0;

    if(!(argc == 7)){
       cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
       return 1; 
    }

    
    for(int i = 1; i < 7; i++){
        istringstream iss;
        iss.str(argv[i]);
        int m;
        if (!(iss >> m) || m < 0 || (i == 3 && m == 0)) {
            if(i == 1){
            cerr << "Error: Invalid capacity " <<"'" << argv[i]<<"'" << " for jug A." << endl;
            return 1;
            }
            else if(i == 2){
            cerr << "Error: Invalid capacity " <<"'" << argv[i]<<"'" << " for jug B." << endl;
            return 1;
            }
            else if(i ==3){
                if(m == 0){
                cerr << "Error: Invalid capacity " <<"'" << argv[i]<<"'" << " for jug C." << endl;
                return 1;
                }
            }
            else if(i == 4){
                cerr << "Error: Invalid goal " <<"'" << argv[i] <<"'" << " for jug A." << endl;
                return 1;
            }
            else if(i == 5){
                if(m <= 0){
                cerr << "Error: Invalid goal " <<"'" << argv[i]<<"'" << " for jug B." << endl;
                return 1;
            }
            }
            else if(i == 6){
                cerr << "Error: Invalid goal " <<"'" << argv[i]<<"'" << " for jug C." << endl;
                return 1;
            }
          
        }
    
    }
    int jug_A;
    int jug_B;
    int jug_C;
    int total = 0;
    for(int i = 1; i < 7; i++){
        int n;
        iss.clear();  // Clear the stream flags and state.
        iss.str(argv[i]);
        iss >> n;
      
        if(i== 1){
            jug_A =  n;
        }
        else if(i== 2){
             jug_B = n;
        }
        else if(i== 3){
             jug_C = n;
        }
        else if(i ==4){
            if (jug_A < n){
                cerr << "Error: Goal cannot exceed capacity of jug A." << endl; 
                return 1;
            }
        }else if(i ==5){
            if (jug_B < n){
                cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
                return 1;

            }
        }else if(i ==6){
            if (jug_C < n){
                cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
                return 1; 
            }
        }

    }

    for(int i = 4; i < 7; i++){
        total = total + stoi(argv[i]);

    } 
    if(jug_C != total){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    iss.clear();  // Clear the stream flags and state.
    return 0; 
}
