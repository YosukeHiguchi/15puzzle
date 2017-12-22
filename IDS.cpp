#include <bits/stdc++.h>
#include <time.h>

#include "state.hpp"

using namespace std;

const string goal = "123456789abcdef-";

bool ids();

int main() {
    clock_t tic, toc;

    int shuffle;
    cout << "Input shuffle counts >> ";
    cin >> shuffle;

    State first = state_get_random(goal, shuffle);
}

bool ids() {
    
}

void show_time(clock_t t) {
    printf("%-8s%f [s]\n", "time:", (double)(t) / CLOCKS_PER_SEC);
}
