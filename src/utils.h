#ifndef UTILS_H  // If UTILS_H is not defined
#define UTILS_H  // Define UTILS_H

#include <string>
#include <vector>

class CountdownSolution {
   private:
    std::string solution;
    int value;

   public:
    CountdownSolution() : solution(), value(0) {}

    CountdownSolution(const std::string& solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {}

    const std::string& getSolution() const { return solution; }

    int getValue() const { return value; }
};

std::vector<char> OPERATIONS = {'+', '-', '*', '/'};

#endif  // UTILS_H