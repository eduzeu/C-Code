#include <iostream>
using namespace std;

void pass_by_reference(int &x) {

x = 10;

}

int main(void) {

int x = 5;

pass_by_reference(x);

cout << x;

return 0;

}

