
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int a, b, c, x, y, z;

struct State {
    int a, b, c;
    string directions;
    string path;
    State* parent;

    State(int _a, int _b, int _c, string _directions, State* _parent) :
        a{ _a }, b{ _b }, c{ _c }, directions{ _directions }, parent{ _parent } { 
        if (parent != nullptr) {
            ostringstream oss;
            oss << (*parent).path << _directions << " (" << _a << ", " << _b << ", " << _c << ")" << endl;
            path = oss.str();
        }
    }

    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

/**
 * @brief Get the goal state to compare it later and see if we encounter it at some point 
 * 
 * @param x 
 * @param y 
 * @param z 
 * @return State 
 */
State goal_state(int x, int y, int z) {
    return State(x, y, z, "Goal State", nullptr);
}

/**
 * @brief will print all states and their direction. No use in the actual code, but good way to debug and 
 * determine that we had everything right 
 * 
 * @param states 
 */
void printStates(const vector<State>& states) {
    for (const State& state : states) {
        cout << state.directions << " (" << state.a << ", " << state.b << ", " << state.c << ")" << endl;
    }
}

string bfs(int a, int b, int c) {
    int current_a = 0;
    int current_b = 0;
    int current_c = c;

    //create vector to keep track of visited states
    vector<State> visited_states; 

    //create queue to work on current state
    queue<State> states;

    //initialize states and add to queue
    State initialState(current_a, current_b, current_c, "Initial state." , nullptr);
    states.push(initialState);

    while (!states.empty()) {
        State current = states.front();
        states.pop();

        //return path if the current state equals goal state
        if (current.to_string() == goal_state(x, y, z).to_string()) {
            visited_states.push_back(current);
            
            //print states was used to debugg and check the vector and that they had the proper states
           // printStates(visited_states);
            cout << "Initial state. " << initialState.to_string() << endl;
            return current.path;
        }

        bool seen = false;
        // Check if the state has been seen
        for(size_t i = 0; i < visited_states.size(); i++){
            if(current.to_string() == visited_states[i].to_string()){
                seen =true; 
                break; //if seen, no need to keep checking 
            }
        }
        if(seen){
            continue;
        }

        // Mark the current state as visited
        visited_states.push_back(current);

        /************************
        try 6 ways to pour water
        *************************/

        // Pour water from C to A
        //check if c is not empty, and check if a is not full 
        if (current.a < a && current.c > 0) {
            int amount = min(current.c, a - current.a);
            int next_a = current.a + amount;
            int next_c = current.c - amount;
            if(amount == 1){
                State nextState(next_a, current.b, next_c, "Pour " + to_string(amount) + " gallon from C to A.", &current);
                states.push(nextState);
            }else{
                State nextState(next_a, current.b, next_c, "Pour " + to_string(amount) + " gallons from C to A.", &current);
                states.push(nextState);
            }
        }

        // Pour water from B to A
        //check if b is not empty, and check if a is not full 
        if (current.a < a && current.b > 0) {
            int amount = min(current.b, a - current.a);
            int next_a = current.a + amount;
            int next_b = current.b - amount;
            if(amount == 1){
                State nextState(next_a, next_b, current.c, "Pour " + to_string(amount) + " gallon from B to A.", &current);
                states.push(nextState);
            }else{
                State nextState(next_a, next_b, current.c, "Pour " + to_string(amount) + " gallons from B to A.", &current);
                states.push(nextState);
            }
        }

        // Pour water from C to B
        //check if c is not empty, and check if b is not full 
        if (current.b < b && current.c > 0) {
            int amount = min(current.c, b - current.b);
            int next_b = current.b + amount;
            int next_c = current.c - amount;
            if(amount == 1){
                State nextState(current.a, next_b, next_c, "Pour " + to_string(amount) + " gallon from C to B.", &current);
                states.push(nextState);
            }else{
                State nextState(current.a, next_b, next_c, "Pour " + to_string(amount) + " gallons from C to B.", &current);
                states.push(nextState); 
            } 
        }

        // Pour water from A to B
        //check if c is not empty, and check if b is not full 
        if (current.b < b && current.a > 0) {
            int amount = min(current.a, b - current.b);
            int next_b = current.b + amount;
            int next_a = current.a - amount;
            if (amount == 1){
                State nextState(next_a, next_b, current.c,  "Pour " + to_string(amount) +" gallon from A to B.", &current);
                states.push(nextState);
            }else{
                State nextState(next_a, next_b, current.c,  "Pour " + to_string(amount) +" gallons from A to B.", &current);
                states.push(nextState);
            }
        }

        // Pour water from B to C
        //check if b is not empty, and check if c is not full 
        if (current.c < c && current.b > 0) {
            int amount = min(current.b, c - current.c);
            int next_c = current.c + amount;
            int next_b = current.b - amount;
            if(amount == 1){
                 State nextState(current.a, next_b, next_c, "Pour " + to_string(amount) + " gallon from B to C." , &current);
            states.push(nextState);
            }else{
            State nextState(current.a, next_b, next_c, "Pour " + to_string(amount) + " gallons from B to C." , &current);
            states.push(nextState); 
            }       
        }

        // Pour water from A to C
        //check if a is not empty, and check if c is not full 
        if (current.c < c && current.a > 0) {
            int amount = min(current.a, c - current.c);
            int next_c = current.c + amount;
            int next_a = current.a - amount;
            if(amount == 1){
                State nextState(next_a, current.b, next_c, "Pour " + to_string(amount) + " gallon from A to C." , &current);
                states.push(nextState);
            }else{
                State nextState(next_a, current.b, next_c, "Pour " + to_string(amount) + " gallons from A to C." , &current);
                states.push(nextState);
            }
        }
    }
    return "No solution.";
}


int main(int argc, char* argv[]){

    // create string object 
    istringstream iss;

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


    //get initial capacities a b c


    iss.str(argv[1]);
    iss >> a; 
    iss.clear(); 

    iss.str(argv[2]);
    iss >> b; 
    iss.clear(); 

    iss.str(argv[3]);
    iss >> c; 
    iss.clear(); 


    // get goal state x y z
    iss.str(argv[4]);
    iss >> x; 
    iss.clear(); 

    iss.str(argv[5]);
    iss >> y; 
    iss.clear(); 

    iss.str(argv[6]);
    iss >> z; 
    iss.clear(); 


    goal_state(x,y,z);
    
    vector<State> visited_states; 

    printStates(visited_states);
    cout << bfs(a,b,c) << endl; 

    return 0; 
}

