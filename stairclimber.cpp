/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Eduardo Hernandez
 * Date        :  30th september 2023
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * @brief Gets the possible ways to reach stair n by using a recursive call (n-1) + (n-2) + (n-3)
 * 
 * @param num_stairs 
 * @return vector< vector<int> > 
 */
vector< vector<int> > get_ways(int num_stairs) {

    if (num_stairs <= 0){
        return vector<vector<int>>(1, vector<int>()); //return statement in case input is zero 
    }

    vector<vector<int>> ways; 
    for(int i = 1; i < 4; i++){
        if(num_stairs >=i){
            vector<vector<int>> result = get_ways(num_stairs-i); 
            for(size_t j = 0; j < result.size(); j++){
                result[j].insert(result[j].begin(),i); 
            }
            ways.insert(ways.end(), result.begin(), result.end()); 
        }
    }

    return ways;
 
}


void display_ways(const std::vector<std::vector<int>>& ways) {
    // Calculate the maximum width needed for numbering
    int max_width = static_cast<int>(std::to_string(ways.size()).length());

    for (size_t i = 0; i < ways.size(); i++) {
        // Print the index with padding to match the maximum width
        std::cout << std::setw(max_width) << i + 1 << ". [";

        // Print the elements in the current way
        for (size_t j = 0; j < ways[i].size(); j++) {
            std::cout << ways[i][j];
            if (j < ways[i].size() - 1) {
                std::cout << ", ";
            }
        }

        // Print the closing bracket and move to the next line
        std::cout << "]" << std::endl;
    }
}
int main(int argc, char * const argv[]) {

    //check for wrong number of arguments 
    if(argc != 2){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    int num_stairs; 
    //check for wrong datatype 
    if(!(istringstream(argv[1]) >> num_stairs)){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1; 
    }
    //check for wront integer values
    if(num_stairs <= 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    vector<vector<int>> ways = get_ways(num_stairs);
    
    if(num_stairs == 1){ //input will slightly change if numstairs is equal to 1
        cout << ways.size() << " way to climb " << num_stairs << " stair." << endl;
        display_ways(ways);

    }else{ 
        cout << ways.size() << " ways to climb " << num_stairs << " stairs." << endl;
         display_ways(ways);

    }

    return 0;

    }



