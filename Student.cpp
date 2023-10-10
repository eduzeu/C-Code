/*******************************************************************************
 * Filename: Student.cpp
 * Author  : Eduardo Hernandez
 * Version : 1.0
 * Date    : September 12, 2023
 * Description: Returns GPA of failing students.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class Student{
public:
       Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

       string getfirst() const {
        return first_;
       }

       string getLast() const {
        return last_;
       }
       string full_name() const {
        return first_ +  " " + last_;
       }

       int id() const{
        return id_;
       }
       float gpa() const{
        return gpa_;
       }

       void print_info() const {
        cout << full_name() << ", GPA: " << fixed << setprecision(2) << gpa() << ", ID: " << id() << endl;
       }
        

private:
        string first_;
        string last_;
        float gpa_;
        int id_; 

};
/**
* Takes a vector of Student objects, and returns a new vector
* with all Students whose GPA is < 1.0.
*/
vector<Student> find_failing_students(const vector<Student> &students) {
 vector<Student> failing_students;
 for(auto it = students.begin(); it != students.end(); it++){
    if(it->gpa() < 1){
        failing_students.push_back(*it);
    }
 }
 // Iterates through the students vector, appending each student whose gpa is
 // less than 1.0 to the failing_students vector.
 return failing_students;
}

/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
    for(auto it = students.begin(); it != students.end(); it++){
        it->print_info();
    }
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen. */
 

int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;


    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
        cout << "Enter student's GPA (0.0-4.0): ";
        cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);   
    
    //will check if the vector is empty and display none for students failing
    if(find_failing_students(students).empty()){
        cout << endl << "Failing students:";
        cout  << " None" << endl;
    }
    //if there are students failing, then we print them 
    else{
        cout << endl << "Failing students:" << endl;
        print_students((find_failing_students(students)));

    }
    // TODO
    // Print a space and the word 'None' on the same line if no students are failing.
    // Otherwise, print each failing student on a separate line.
 return 0;
}
