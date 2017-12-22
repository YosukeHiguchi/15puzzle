#include <bits/stdc++.h>
#include <time.h>

#include "state.hpp"

using namespace std;

const string goal = "123456789abcdef-";

bool astar(State first, int (*f)(State), int limit = -1);
int h0(State state);
int h1(State state);
int h2(State state);
void show_time(clock_t t);

int main() {
    clock_t tic, toc;

    int shuffle;
    cout << "Input shuffle counts >> ";
    cin >> shuffle;

    State first = state_get_random(goal, shuffle);
    //State first = state_set("-c9dfbae78624351"); // 80 moves

    cout << "Problem: " << endl;
    state_show(first);

    cout << "\nSolving puzzle by A* with h0...\n";
    tic = clock();
    astar(first, h0);
    toc = clock();
    show_time(toc - tic);

    cout << "\nSolving puzzle by A* with h1...\n";
    tic = clock();
    astar(first, h1);
    toc = clock();
    show_time(toc - tic);

    cout << "\nSolving puzzle by A* with h2...\n";
    tic = clock();
    astar(first, h2);
    toc = clock();
    show_time(toc - tic);

    cout << "\nSolving puzzle by IDA* with h0...\n";
    tic = clock();
    for (int limit = 0; limit < 80; limit++) {
        if (astar(first, h0, limit)) {
            break;
        }
    }
    toc = clock();
    show_time(toc - tic);

    cout << "\nSolving puzzle by IDA* with h1...\n";
    tic = clock();
    for (int limit = 0; limit < 80; limit++) {
        if (astar(first, h1, limit)) {
            break;
        }
    }
    toc = clock();
    show_time(toc - tic);

    cout << "\nSolving puzzle by IDA* with h2...\n";
    tic = clock();
    for (int limit = 0; limit < 80; limit++) {
        if (astar(first, h2, limit)) {
            break;
        }
    }
    toc = clock();
    show_time(toc - tic);
}

bool astar(State first, int (*f)(State), int limit) {
    priority_queue<State, vector<State>, greater<State>> pq;
    unordered_set<string> closed;

    pq.push(first);

    int loop_cnt = 0;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.st == goal) {
            //state_show(current);
            printf("%-8s%d\n", "moves:", current.depth);
            printf("%-8s%d\n", "iters:", loop_cnt);

            return true;
        }

        if (current.cost == limit) {
            continue;
        }

        closed.insert(current.st);

        for (int i = 0; i < 4; i++) {
            State next = current;

            if (move_panel(next, i)) {
                if (closed.find(next.st) == closed.end()) {
                    next.depth = current.depth + 1;
                    next.cost = next.depth + f(next);
                    pq.push(next);
                }
            }
        }

        loop_cnt++;
    }

    return false;
}

int h0(State state) {
    return 0;
}

int h1(State state) {
    int cnt = 0;
    int len = goal.length();

    for (int i = 0; i < len; i++) {
        if (state.st[i] != goal[i]) cnt++;
    }

    return cnt;
}

int h2(State state) {
    int cnt = 0;
    int glen = goal.length(), slen = state.st.length();

    for (int i = 0; i < glen; i++) {
        if (goal[i] == '-') continue;

        for (int j = 0; j < slen; j++) {
            if (goal[i] == state.st[j]) {
                cnt = cnt + abs(j % N - i % N) + abs(j / N - i / N);
                break;
            }
        }
    }

    return cnt;
}

void show_time(clock_t t) {
    printf("%-8s%f [s]\n", "time:", (double)(t) / CLOCKS_PER_SEC);
}
