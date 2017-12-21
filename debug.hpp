#pragma once

#include <iostream>
#include "time.h"

#define N 4

using namespace std;


typedef struct {
    string parent = "";
    string st = "";
    int blank = -1;
    int depth = -1;
    int cost = -1;
} State;

bool operator>(const State &lhs, const State &rhs) {
    return lhs.cost > rhs.cost;
}

inline bool move_panel(string &state, int move);
inline State state_get_random(string s, int shuffle);
inline void state_show(State state);

bool move_panel(State &state, int move) {
    int idx = state.blank;
    int target = -1;

    switch (move) {
        case 0: // up
            if (idx / N > 0) target = idx - N;
            break;
        case 1: // down
            if (idx / N < N - 1) target = idx + N;
            break;
        case 2: // left
            if (idx % N > 0) target = idx - 1;
            break;
        case 3: // right
            if (idx % N < N - 1) target = idx + 1;
            break;
    }

    if (target != -1) {
        swap(state.st[idx], state.st[target]);
        state.blank = target;
        return true;
    }

    return false;
}

State state_get_random(string s, int shuffle) {
    State ret;

    ret.st = s;
    ret.depth = 0;
    ret.cost = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '-') {
            ret.blank = i;
            break;
        }
    }

    srand((unsigned)time(NULL));
    int vec[4] = {1, -1, 2, -2};
    int r, bef_vec;

    for (int c = 0; c < shuffle; c++) {
        do {
            r = rand() % 4;
        } while (c != 0 && vec[r] == -1 * bef_vec);

        if (move_panel(ret, r)) {
            bef_vec = vec[r];
        } else {
            c--;
        }
    }

    return ret;
}

void state_show(string s) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << s[i * N + j] << " ";
        }
        cout << endl;
    }
    //cout << state.cost << endl;
    cout << endl;
}