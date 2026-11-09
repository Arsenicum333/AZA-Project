#pragma once
#include <iostream>
#include <vector>

using namespace std;

class ImprovedSolver {
private:
    vector<int> values;
    vector<int> result;
    vector<int> candidates;
    vector<int> suffix;
    int n;
    int target;
    int calls;
    bool isSolution;

    void search(int index, int currentSum);

public:
    ImprovedSolver(const vector<int>& values, int target);

    void solve();
    void print() const;

    bool hasSolution() const;
    const vector<int>& solution() const;
    int getCalls() const;
};
