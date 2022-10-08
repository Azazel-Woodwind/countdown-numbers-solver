#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>
#include <vector>

// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

// TODO: write code here:
using std::string;
using std::vector;

vector<char> OPERATIONS = {'+', '-', '*', '/'};

double popDoubleVector(vector<double>& vec) {
    double last = vec.back();
    vec.pop_back();
    return last;
}

double evaluateCountdown(string exp) {
    vector<double> stack;
    string temp = "";
    int n = exp.size();
    for (int i = 0; i <= n; i++) {
        if (i == n || exp[i] == ' ') {
            if (temp == "+") {
                stack.push_back(popDoubleVector(stack) + popDoubleVector(stack));
            }
            else if (temp == "-") {
                double a = popDoubleVector(stack);
                double b = popDoubleVector(stack);
                stack.push_back(b - a);
            }
            else if (temp == "*") {
                stack.push_back(popDoubleVector(stack) * popDoubleVector(stack));
            }
            else if (temp == "/") {
                double a = popDoubleVector(stack);
                double b = popDoubleVector(stack);
                if (a == 0) {
                    throw -1;
                }
                stack.push_back(b / a);
            }
            else {
                stack.push_back(stod(temp));
            }
            temp = "";
        }
        else {
            temp += exp[i];
        }
    }
    return stack.back();
}

bool containsDuplicates(const vector<int>& nums) {
    vector<int> count(6);
    for (int num : nums) {
        if (count[num]++ == 1) {
            return true;
        }
    }
    return false;
}

void updateSol3(int target, int& diff, int& val, string& sol, const vector<int>& nums, const vector<int>& operationPositions, const vector<char> operations) {
    if (operations.size() != operationPositions.size()) {
        return;
    }

    string newSol = "";
    int i = 0, operationPosPointer = 0, numsPointer = 0, operationPointer = 0, evaluation, newDiff, n = nums.size();
    while (1) {
        if (i == n + n - 2) {
            newSol += operations[operationPointer];
            break;
        }
        if (i == operationPositions[operationPosPointer]) {
            newSol += operations[operationPointer++];
            newSol += " ";
            operationPosPointer++;
        }
        else {
            newSol += intToString(nums[numsPointer++]) + " ";
        }
        i++;
    }
    try {
        evaluation = evaluateCountdown(newSol); 
    }
    catch (int err) {
        return;
    }
    newDiff = abs(target - evaluation);
    if (newDiff < diff) {
        diff = newDiff;
        sol = newSol;
        val = evaluation;
    }
}

void updateSol2(int target, int& diff, int& val, string& sol, const vector<int>& nums, const vector<int>& operationPositions) {
    if (operationPositions.size() != nums.size() - 1) {

        return;
    }

    for (int a = 0; a < OPERATIONS.size(); a++) {
        updateSol3(target, diff, val, sol, nums, operationPositions, {OPERATIONS[a]});
        for (int b = 0; b < OPERATIONS.size() && operationPositions.size() > 1; b++) {
            updateSol3(target, diff, val, sol, nums, operationPositions, {OPERATIONS[a], OPERATIONS[b]});
            for (int c = 0; c < OPERATIONS.size() && operationPositions.size() > 2; c++) {
                updateSol3(target, diff, val, sol, nums, operationPositions, {OPERATIONS[a], OPERATIONS[b], OPERATIONS[c]});
                for (int d = 0; d < OPERATIONS.size() && operationPositions.size() > 3; d++) {
                    updateSol3(target, diff, val, sol, nums, operationPositions, {OPERATIONS[a], OPERATIONS[b], OPERATIONS[c], OPERATIONS[d]});
                    for (int e = 0; e < OPERATIONS.size() && operationPositions.size() > 4; e++) {
                        updateSol3(target, diff, val, sol, nums, operationPositions, {OPERATIONS[a], OPERATIONS[b], OPERATIONS[c], OPERATIONS[d], OPERATIONS[e]});
                    }
                }
            }
        }
    }
}

void updateSol1(int target, int& diff, int& val, string& sol, const vector<int>& nums) {
    int n = nums.size();
    int rpnLength = n + n - 1;
    for (int a = n; a > 1; a--) {
        updateSol2(target, diff, val, sol, nums, {a});
        for (int b = a + 1; b > a && b > 3 && b < rpnLength; b--) {
            updateSol2(target, diff, val, sol, nums, {a, b});
            for (int c = b + 1; c > b && c > 5 && c < rpnLength; c--) {
                updateSol2(target, diff, val, sol, nums, {a, b, c});
                for (int d = c + 1; d > c && d > 7 && d < rpnLength; d--) {
                    updateSol2(target, diff, val, sol, nums, {a, b, c, d});
                    for (int e = d + 1; e > d && e > 9 && e < rpnLength; e--) {
                        updateSol2(target, diff, val, sol, nums, {a, b, c, d, e});
                    }
                }
            }
        }
    }
}


CountdownSolution solveCountdownProblem(vector<int> numbers, int target) {
    int diff = INT32_MAX, n = numbers.size(), val, newDiff;
    string sol;
    for (int a = 0; a < n; a++) {
        newDiff = abs(target - numbers[a]);
        if (newDiff < diff) {
            diff = newDiff;
            val = numbers[a];
            sol = intToString(numbers[a]);
        }
        for (int b = 0; b < n; b++) {
            if (containsDuplicates({a, b})) {
                continue;
            }
            updateSol1(target, diff, val, sol, {numbers[a], numbers[b]});
            for (int c = 0; c < n; c++) {
                if (containsDuplicates({a, b, c})) {
                    continue;
                }
                updateSol1(target, diff, val, sol, {numbers[a], numbers[b], numbers[c]});
                for (int d = 0; d < n; d++) {
                    if (containsDuplicates({a, b, c, d})) {
                        continue;
                    }
                    updateSol1(target, diff, val, sol, {numbers[a], numbers[b], numbers[c], numbers[d]});
                    for (int e = 0; e < n; e++) {
                        if (containsDuplicates({a, b, c, d, e})) {
                            continue;
                        }
                        updateSol1(target, diff, val, sol, {numbers[a], numbers[b], numbers[c], numbers[d], numbers[e]});
                        for (int f = 0; f < n; f++) {
                            if (containsDuplicates({a, b, c, d, e, f})) {
                                continue;
                            }
                            updateSol1(target, diff, val, sol, {numbers[a], numbers[b], numbers[c], numbers[d], numbers[e], numbers[f]});
                        }
                    }
                }
            }
        }
    }

    return CountdownSolution(sol, val);
}

// Do not edit below this line


#endif
