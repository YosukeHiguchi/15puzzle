#pragma once

#include <iostream>

using namespace std;


#define N 4

inline string state_get_initial(int shuffle) {

}

inline void state_show(string state) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << state[i * N + j] << " ";
        }
        cout << endl;
    }
}