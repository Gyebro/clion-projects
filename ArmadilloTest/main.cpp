#include <iostream>

#include "armadillo"

using namespace std;
using namespace arma;

int main() {
    cout << "Armadillo version: " << arma_version::as_string() << endl;
    // Returns 5.0.1 (Ankle Biter)

    mat A(2,3);  // Too many arguments, expected 0
    A.fill(99);
    A(1,2) += 101.0;  // Called object is not a function
    A.print("A = ");
    A.set_size(4,5); // Too many arguments, expected 1
    A.fill(77);
    A.print("A = ");

    return 0;
}