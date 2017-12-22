#include <bits/stdc++.h>
#include <time.h>

#include "state.hpp"

using namespace std;

const string goal = "123456789abcdef-";

long long int ida_itr = 0;

bool ids(State first, int limit);
void show_time(clock_t t);

int main(int argv, char* argc[]) {
    clock_t tic, toc;
    State first;

    if (argv > 1 && argc[1][0] == '1') {
        string s; // 80 moves: -c9dfbae78624351
        cout << "Input solvable puzzle >> ";
        cin >> s;
        first = state_set(s);
    } else {
        int shuffle;
        cout << "Input shuffle counts >> ";
        cin >> shuffle;
        first = state_get_random(goal, shuffle);
    }

    cout << "\nTarget puzzle:" << endl;
    state_show(first);

    cout << "\nSolving puzzle by IDS...\n";
    tic = clock();
    for (int limit = 0; limit < 80 && !ids(first, limit); limit++);
    toc = clock();
    show_time(toc - tic);
}

bool ids(State first, int limit) {
    vector<State> stack;
    unordered_map<string, int> closed;
    long long int loop_cnt = 0;

    stack.push_back(first);

    while (!stack.empty()) {
        State current = stack.back();
        stack.pop_back();

        if (current.st == goal) {
            printf("%-5s : %d\n", "moves", current.depth);
            printf("%-5s : %lld\n", "iters", loop_cnt + ida_itr);

            return true;
        }

        closed[current.st] = current.depth;

        if (current.depth == limit) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            State next = current;

            if (move_panel(next, i)) {
                if (!closed[next.st] || current.depth < closed[next.st]) {
                    next.depth = current.depth + 1;
                    next.cost = next.depth + 0;
                    stack.push_back(next);
                }
            }
        }

        loop_cnt++;
    }

    ida_itr += loop_cnt;

    return false;
}

void show_time(clock_t t) {
    printf("%-5s : %f [s]\n", "time", (double)(t) / CLOCKS_PER_SEC);
}
