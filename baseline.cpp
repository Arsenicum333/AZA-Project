#include "baseline.h"

BaselineSolver::BaselineSolver(const vector<int>& values, int target)
: values(values), n((int)values.size()), target(target), calls(0), isSolution(false) {}

void BaselineSolver::solve() {
    result.clear();
    candidates.clear();
    calls = 0;
    isSolution = false;
    search(0, 0);
}

void BaselineSolver::search(int index, int currentSum) {
    calls++;

    if (index == n) {
        if (currentSum == target) {
            result = candidates;
            isSolution = true;
        }

        return;
    }

    candidates.push_back(index);
    search(index + 1, currentSum + values[index]);
    candidates.pop_back();

    search(index + 1, currentSum);
}

void BaselineSolver::print() const {
    if (isSolution) {
        cout << "Solution found: ";

        for (int i = 0; i < (int)result.size(); i++) {
            if (i > 0) cout << " ";
            cout << values[result[i]];
        }

        cout << "\n";
    } else {
        cout << "No solution\n";
    }

    cout << "Total calls: " << calls << "\n";
}

bool BaselineSolver::hasSolution() const {return isSolution;}
const vector<int>& BaselineSolver::solution() const {return result;}
int BaselineSolver::getCalls() const {return calls;}
