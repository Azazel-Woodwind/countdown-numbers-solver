
#include <limits>
#include <string>
#include <vector>

#include "../utils.h"
#include "Solver.h"

using std::numeric_limits;
using std::string;
using std::vector;

struct Entree {
    double num;
    string exp;

    Entree() {}

    Entree(double numIn, const string& expIn) : num(numIn), exp(expIn) {}
};

class CountdownDnCSolver : public CountdownSolver {
   private:
    double diff;
    double val;
    string ans;

    vector<Entree> reduce(const vector<Entree>& vec, int i, int j,
                          double result, string& exp) {
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
        for (int i = 0; i < (int)nums.size() - 1; i++) {
            // std::cout << i << std::endl;
            for (int j = i + 1; j < nums.size(); j++) {
                for (char operation : OPERATIONS) {
                    double result;
                    if (operation == '+' || operation == '*') {
                        if (operation == '+') {
                            result = nums[i].num + nums[j].num;
                        } else {
                            result = nums[i].num * nums[j].num;
                        }
                        string exp =
                            nums[i].exp + " " + nums[j].exp + " " + operation;
                        updateSol(result, exp, target);
                        // std::cout << "{ ";
                        // for (auto e : nums) {
                        //     std::cout << e.num << " ";
                        // }
                        // std::cout << "}" << std::endl;
                        if (nums.size() > 2) {
                            solve(reduce(nums, i, j, result, exp), target);
                        }
                    } else {
                        string exp;
                        double result2;
                        if (operation == '-') {
                            result = nums[i].num - nums[j].num;
                            result2 = -1 * result;
                        } else if (nums[i].num == 0 || nums[j].num == 0) {
                            if (nums[i].num == 0 && nums[j].num == 0) {
                                continue;
                            }
                            result = 0;
                            if (nums[i].num == 0) {
                                exp = nums[i].exp + " " + nums[j].exp + " /";
                            } else {
                                exp = nums[j].exp + " " + nums[i].exp + " /";
                            }
                            updateSol(result, exp, target);
                            if (nums.size() > 2) {
                                solve(reduce(nums, i, j, result, exp), target);
                            }
                            continue;
                        } else {
                            result = nums[i].num / nums[j].num;
                            result2 = 1 / result;
                        }
                        exp = nums[i].exp + " " + nums[j].exp + " " + operation;
                        string exp2 =
                            nums[j].exp + " " + nums[i].exp + " " + operation;
                        updateSol(result, exp, target);
                        updateSol(result2, exp2, target);
                        if (nums.size() > 2) {
                            vector<Entree> temp =
                                reduce(nums, i, j, result, exp);
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

   public:
    CountdownDnCSolver() {}

    CountdownSolution solve(const vector<int>& numbers, int target) override {
        diff = numeric_limits<double>::max();
        for (int num : numbers) {
            int newDiff = abs(target - num);
            if (newDiff == 0) {
                return CountdownSolution(std::to_string(num), num);
            } else if (newDiff < diff) {
                diff = newDiff;
                ans = std::to_string(num);
            }
        }

        vector<Entree> nums(numbers.size());
        for (int i = 0; i < numbers.size(); i++) {
            nums[i].num = numbers[i];
            nums[i].exp = std::to_string(numbers[i]);
        }

        try {
            solve(nums, target);
        } catch (int err) {
        }

        return CountdownSolution(ans, val);
    }
};
