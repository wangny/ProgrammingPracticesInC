#include "function.h"

int main()
{
    State s = {2, 1, 3};
    SwapSort prob1(s);
    prob1.solve(4);
    prob1.show_solutions();
    cout << "\n";

    State t = {6, 1, 3, 4, 5, 2};
    SwapSort prob2(t);
    prob2.solve(4);
    prob2.show_solutions();
    cout << "\n";

    State r = {2, 1, 3, 5, 4};
    SwapSort prob3(r);
    prob3.solve(4);
    prob3.show_solutions();
    cout << "\n";
}
