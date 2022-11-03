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
// #include <iostream>

struct Solution {
    vector<int> nums;
    vector<int> operationPositions;
    vector<char> operations;
};

vector<char> OPERATIONS = {'+', '-', '*', '/'};
// vector<char> OPERATIONS = {'+', '*'};

double popDoubleVector(vector<double>& vec) {
    double last = vec.back();
    vec.pop_back();
    return last;
}

double evaluateCountdown(string exp) {
    vector<double> stack;
    stack.reserve(6);
    int n = exp.size(), front = 0, back = 0;
    bool added = false;
    for (int i = 1; i < n; i++) {
        if (exp[i] >= '0' && exp[i] <= '9' || exp[i] == '.') {
            if (added) {
                front = i, back = i;
                added = false;
            }
            else {
                back++;
            }
        }
        else if (exp[i] == ' ') {
            if (!added) {
                added = true;
                double ans = stod(exp.substr(front, back - front + 1));
                stack.emplace_back(ans);
            }
        }
        else {
            double a = popDoubleVector(stack);
            double b = popDoubleVector(stack);
            if (exp[i] == '+') {
                stack.emplace_back(a + b);
            }
            else if (exp[i] == '-') {
                stack.emplace_back(b - a);
            }
            else if (exp[i] == '*') {
                stack.emplace_back(a * b);
            }
            else if (exp[i] == '/') {
                if (a == 0) {
                    throw -1;
                }
                stack.emplace_back(b / a);
            }
        }
    }
    return stack.back();
}

string constructRPNExp(const vector<int>& nums, const vector<int>& operationPositions, const vector<char> operations) {
    if (operationPositions.size() == 0) {
        return intToString(nums[0]);
    }
    string newSol = "";
    int i = 0, operationPosPointer = 0, numsPointer = 0, operationPointer = 0, n = nums.size();
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
    return newSol;
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

void updateSol3(int target, double& diff, int& val, Solution& sol, const vector<int>& nums, const vector<int>& operationPositions, const vector<char> operations) {
    if (operations.size() != operationPositions.size()) {
        return;
    }

    double evaluation, newDiff;
    vector<double> stack;
    stack.reserve(6);
    int i = 0, operationPosPointer = 0, numsPointer = 0, operationPointer = 0, n = nums.size();
    while (i < n + n - 1) {
        if (i == operationPositions[operationPosPointer]) {
            double a = popDoubleVector(stack);
            double b = popDoubleVector(stack);
            if (operations[operationPointer] == '+') {
                stack.emplace_back(a + b);
            }
            else if (operations[operationPointer] == '-') {
                stack.emplace_back(b - a);
            }
            else if (operations[operationPointer] == '*') {
                stack.emplace_back(a * b);
            }
            else if (operations[operationPointer] == '/') {
                if (a == 0) {
                    return;
                }
                stack.emplace_back(b / a);
            }
            
            operationPointer++;
            operationPosPointer++;
        }
        else {
            stack.emplace_back(nums[numsPointer++]);
        }
        i++;
    }
    
    evaluation = stack.back();
    newDiff = target - evaluation;
    if (newDiff == 0) {
        sol.nums = nums;
        sol.operationPositions = operationPositions;
        sol.operations = operations;
        val = evaluation;
        throw -1;
    }
    if (newDiff < 0) {
        newDiff *= -1;
    }
    if (newDiff < diff) {
        diff = newDiff;
        sol.nums = nums;
        sol.operationPositions = operationPositions;
        sol.operations = operations;
        val = evaluation;
    }
}

void updateSol2(int target, double& diff, int& val, Solution& sol, const vector<int>& nums, const vector<int>& operationPositions) {
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

void updateSol1(int target, double& diff, int& val, Solution& sol, const vector<int>& nums) {
    int n = nums.size();
    int rpnLength = n + n - 1;
    for (int a = n; a > 1; a--) {
        updateSol2(target, diff, val, sol, nums, {a});
        if (n == 2) {
            continue;
        }
        for (int b = n + 1; b > a && b > 3 && b < rpnLength; b--) {
            updateSol2(target, diff, val, sol, nums, {a, b});
            if (n == 3) {
                continue;
            }
            for (int c = n + 2; c > b && c > 5 && c < rpnLength; c--) {
                updateSol2(target, diff, val, sol, nums, {a, b, c});
                if (n == 4) {
                    continue;
                }
                for (int d = n + 3; d > c && d > 7 && d < rpnLength; d--) {
                    updateSol2(target, diff, val, sol, nums, {a, b, c, d});
                    if (n == 5) {
                        continue;
                    }
                    for (int e = n + 4; e > d && e > 9 && e < rpnLength; e--) {
                        updateSol2(target, diff, val, sol, nums, {a, b, c, d, e});
                    }
                }
            }
        }
    }
}

CountdownSolution solveCountdownProblemV1(const vector<int>& numbers, int target) {
    double diff = INT32_MAX;
    int n = numbers.size(), val, newDiff;
    Solution sol;
    try {
        for (int a = 0; a < n; a++) {
            newDiff = abs(target - numbers[a]);
            if (newDiff < diff) {
                diff = newDiff;
                val = numbers[a];
                sol.nums = {numbers[a]};
                sol.operationPositions = {};
                sol.operations = {};
                if (newDiff == 0) {
                    throw -1;
                }
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
    }
    catch (int err) {

    }
    
    return CountdownSolution(constructRPNExp(sol.nums, sol.operationPositions, sol.operations), val);
}

struct Entree {
    double num;
    string exp;

    Entree() {}

    Entree(double numIn, const string& expIn) : num(numIn), exp(expIn) {}
};

double diff = INT32_MAX;
double val;
string ans;

vector<Entree> reduce(const vector<Entree>& vec, int i, int j, double result, string& exp) {
    vector<Entree> copy(vec.size() - 1);
    int pointer = 0;
    for (int index = 0; index < vec.size(); index++) {
        if (index == i || index == j) {
            continue;
        }
        copy[pointer++] = vec[index];
    }
    copy.back() = {result, exp};
    return copy;
}

void updateSol(double result, string& exp, int target) {
    double newDiff = target - result;

    if (newDiff < 0) {
        newDiff *= -1;
    }
    if (newDiff < diff) {
        diff = newDiff;
        ans = exp;
        val = result;
        if (newDiff == 0) {
            throw -1;
        }
    }
}

void solve(const vector<Entree>& nums, int target) {
    // std::cout << nums.size() << std::endl;
    for (int i = 0; i < (int) nums.size() - 1; i++) {
        // std::cout << i << std::endl;
        for (int j = i + 1; j < nums.size(); j++) {
            for (char operation : OPERATIONS) {
                double result;
                if (operation == '+' || operation == '*') {
                    if (operation == '+') {
                        result = nums[i].num + nums[j].num;
                    }
                    else {
                        result = nums[i].num * nums[j].num;
                    }
                    string exp = nums[i].exp + " " + nums[j].exp + " " + operation;
                    updateSol(result, exp, target);
                    // std::cout << "{ ";
                    // for (auto e : nums) {
                    //     std::cout << e.num << " ";
                    // }
                    // std::cout << "}" << std::endl;
                    if (nums.size() > 2) {
                        solve(reduce(nums, i, j, result, exp), target);
                    }
                }
                else {
                    string exp;
                    double result2;
                    if (operation == '-') {
                        result = nums[i].num - nums[j].num;
                        result2 = -1 * result;
                    }
                    else if (nums[i].num == 0 || nums[j].num == 0) {
                        if (nums[i].num == 0 && nums[j].num == 0) {
                            continue;
                        }
                        result = 0;
                        if (nums[i].num == 0) {
                            exp = nums[i].exp + " " + nums[j].exp + " /";
                        }
                        else {
                            exp = nums[j].exp + " " + nums[i].exp + " /";
                        }
                        updateSol(result, exp, target);
                        if (nums.size() > 2) {
                            solve(reduce(nums, i, j, result, exp), target);
                        }
                        continue;
                    }
                    else {
                        result = nums[i].num / nums[j].num;
                        result2 = 1 / result;
                    }
                    exp = nums[i].exp + " " + nums[j].exp + " " + operation;
                    string exp2 = nums[j].exp + " " + nums[i].exp + " " + operation;
                    updateSol(result, exp, target);
                    updateSol(result2, exp2, target);
                    if (nums.size() > 2) {
                        vector<Entree> temp = reduce(nums, i, j, result, exp); 
                        solve(temp, target);
                        temp.pop_back();
                        temp.emplace_back(result2, exp2);
                        solve(temp, target);
                    }
                }
            }
        }
    }
}

CountdownSolution solveCountdownProblemV2(const vector<int>& numbers, int target) {
    diff = INT32_MAX;
    for (int num : numbers) {
        int newDiff = abs(target - num);
        if (newDiff == 0) {
            return CountdownSolution(intToString(num), num);
        }
        else if (newDiff < diff) {
            diff = newDiff;
            ans = intToString(num);
        }
    }

    vector<Entree> nums(numbers.size());
    for (int i = 0; i < numbers.size(); i++) {
        nums[i].num = numbers[i];
        nums[i].exp = intToString(numbers[i]);
    }
    // vector<Entree> nums;
    // nums.reserve(numbers.size());
    // for (int num : numbers) {
    //     nums.emplace_back(num, intToString(num));
    // }
    
    try {
        solve(nums, target);
    }
    catch (int err) {}

    return CountdownSolution(ans, val);
}

CountdownSolution solveCountdownProblem(const vector<int>& numbers, int target) {
    return solveCountdownProblemV2(numbers, target);
}

// Do not edit below this line


#endif
