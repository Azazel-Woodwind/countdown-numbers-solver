#include <iostream>

#include "solvers/CountdownBruteForce.h"
#include "solvers/CountdownDnC.h"

using namespace std;

int main() {
    CountdownBruteForceSolver bruteForceSolver;
    CountdownDnCSolver dncSolver;

    vector<int> numbers = {1, 2, 3, 4, 5, 6};
    int target = 100;

    CountdownSolution bruteForceSolution =
        bruteForceSolver.solve(numbers, target);

    CountdownSolution dncSolution = dncSolver.solve(numbers, target);

    cout << "Brute force solution: " << bruteForceSolution.getSolution()
         << " = " << bruteForceSolution.getValue() << endl;

    cout << "DnC solution: " << dncSolution.getSolution() << " = "
         << dncSolution.getValue() << endl;

    return 0;
}