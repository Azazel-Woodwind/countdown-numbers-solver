#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "../utils.h"

class CountdownSolver {
   public:
    virtual CountdownSolution solve(const std::vector<int>& numbers,
                                    int target) = 0;
};

#endif  // SOLVER_H