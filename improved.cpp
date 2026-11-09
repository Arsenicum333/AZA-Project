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

    void search(int index, int currentSum) {
        calls++;

        if (isSolution) return;
        if (currentSum + suffix[index] < target) return;
        if (currentSum > target) return;

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

public:
    ImprovedSolver(const vector<int>& values, int target)
    : values(values), n((int)values.size()), target(target), calls(0), isSolution(false) {
        suffix.resize(n + 1);
        suffix[n] = 0;

        for (int i = n - 1; i >= 0; i--)
            suffix[i] = suffix[i + 1] + values[i];
    }

    void solve() {
        result.clear();
        candidates.clear();
        calls = 0;
        isSolution = false;
        search(0, 0);
    }

    void print() const {
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

    bool hasSolution() const {return isSolution;}
    const vector<int>& solution() const {return result;}
    int getCalls() const {return calls;}
};

int main() {
    vector<int> values = {3, 7, 11, 15, 19};
    int target = 30;

    ImprovedSolver solver1(values, target);
    solver1.solve();
    solver1.print();

    ImprovedSolver solver2(values, 100);
    solver2.solve();
    solver2.print();
}
