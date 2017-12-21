#include <bits/stdc++.h>
#include "state.hpp"

using namespace std;

const string goal = "123456789abcdef-";

void ids(string state, int level, int limit, int space);

int main() {
    string state = state_get_random(goal, 20);

    int i = 0;
    while (1) {

        idastar(state, 0, i, 15);

        i++;
    }
}

void idastar(string state, int level, int limit, int space) {

}

