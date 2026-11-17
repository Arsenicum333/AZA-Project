#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <string>

#include "baseline.h"
#include "improved.h"

using namespace std;
using namespace std::chrono;

const int SEED = 67;
const double TIMEOUT_MS = 10000;

void genSolvable(mt19937& randGen, int n, vector<int>& values, int& target) {
    uniform_int_distribution<int> valueDist(1, 100);
    values.resize(n);

    for (int& v : values)
        v = valueDist(randGen);

    uniform_int_distribution<int> sizeDist(1, n);
    int k = sizeDist(randGen);
    vector<int> idx(n);

    for (int i = 0; i < n; i++)
        idx[i] = i;

    shuffle(idx.begin(), idx.end(), randGen);
    target = 0;

    for (int i = 0; i < k; i++)
        target += values[idx[i]];
}

void genRandom(mt19937& randGen, int n, vector<int>& values, int& target) {
    uniform_int_distribution<int> valueDist(1, 100);
    values.resize(n);
    int total = 0;

    for (int& v : values) {
        v = valueDist(randGen);
        total += v;
    }

    uniform_int_distribution<int> targetDist(1, total);
    target = targetDist(randGen);
}

void genUnsatisfiable(mt19937& randGen, int n, vector<int>& values, int& target) {
    uniform_int_distribution<int> valueDist(1, 25);
    values.resize(n);
    int total = 0;

    for (int& v : values) {
        v = 4 * valueDist(randGen);
        total += v;
    }

    target = (total / 8) * 4 + 2;
}

int main() {
    mt19937 randGen(SEED);

    cout << "Seed = " << SEED << "\n\n";
    cout << "n\tinstance\tfound\tA_calls\tA_ms\tB_calls\tB_ms\n";
    cout << "--------------------------------------------------------------\n";

    for (int n : {20, 25, 30}) {
        for (int type = 0; type < 3; type++) {
            vector<int> values;
            int target = 0;
            string name;

            if (type == 0) {
                genSolvable(randGen, n, values, target);
                name = "solvable";
            } else if (type == 1) {
                genRandom(randGen, n, values, target);
                name = "random/mixed";
            } else if (type == 2) {
                genUnsatisfiable(randGen, n, values, target);
                name = "unsatisfiable";
            }

            // Baseline: 3 runs, median
            double timeA[3];
            int callsA = 0;
            bool foundA = false;
            vector<int> solutionA;

            for (int run = 0; run < 3; run++) {
                BaselineSolver solver(values, target);
                auto t0 = steady_clock::now();
                solver.solve();
                auto t1 = steady_clock::now();
                timeA[run] = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
                callsA = solver.getCalls();
                foundA = solver.hasSolution();
                solutionA = solver.solution();
            }

            sort(timeA, timeA + 3);

            // Improved: 3 runs, median
            double timeB[3];
            int callsB = 0;
            bool foundB = false;
            vector<int> solutionB;

            for (int run = 0; run < 3; run++) {
                ImprovedSolver solver(values, target);
                auto t0 = steady_clock::now();
                solver.solve();
                auto t1 = steady_clock::now();
                timeB[run] = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
                callsB = solver.getCalls();
                foundB = solver.hasSolution();
                solutionB = solver.solution();
            }

            sort(timeB, timeB + 3);

            // Table row
            cout << n << "\t" << name << "\t" << (foundA ? "yes" : "no") << "\t";
            cout << callsA << "\t";

            if (timeA[1] > TIMEOUT_MS) cout << "TIMEOUT";
            else printf("%.3f", timeA[1]);

            cout << "\t" << callsB << "\t";

            if (timeB[1] > TIMEOUT_MS) cout << "TIMEOUT";
            else printf("%.3f", timeB[1]);

            cout << "\n";

            // Show exact inputs
            cout << "\n" << "    values=[";
            for (int v : values) cout << v << ",";
            cout << "] target=" << target << "\n\n";

            if (foundA) {
                cout << "    A solution: ";
                for (int i : solutionA) cout << values[i] << " ";
                cout << "\n";
            }

            if (foundB) {
                cout << "    B solution: ";
                for (int i : solutionB) cout << values[i] << " ";
                cout << "\n\n";
            }
        }
    }

    return 0;
}
