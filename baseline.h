#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BaselineSolver {
private:
    vector<int> values;
    vector<int> result;
    vector<int> candidates;
    int n;
    int target;
    int calls;
    bool isSolution;

    void search(int index, int currentSum);

public:
    BaselineSolver(const vector<int>& values, int target);

    void solve();
    void print() const;

    bool hasSolution() const;
    const vector<int>& solution() const;
    int getCalls() const;
};
