#include "baseline.h"
#include "improved.h"

int main() {
    vector<int> values = {3, 7, 11, 15, 19};
    int target = 30;

    BaselineSolver solver1(values, target);
    solver1.solve();
    solver1.print();

    BaselineSolver solver2(values, 100);
    solver2.solve();
    solver2.print();

    ImprovedSolver solver3(values, target);
    solver3.solve();
    solver3.print();

    ImprovedSolver solver4(values, 100);
    solver4.solve();
    solver4.print();
}
