#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int sumPositiveIntegers(const vector<int>& nums) {
    int sum = 0;
    for (int num : nums) {
        if (num > 0) {
            sum += 1;
        }
    }
    return sum;
}

int main() {
    ifstream input("SOLVE.INP");
    ofstream output("SOLVE.ans");

    vector<int> nums;
    int num;

    while (input >> num) {
        nums.push_back(num);
    }

    output << sumPositiveIntegers(nums) << endl;

    return 0;
}
