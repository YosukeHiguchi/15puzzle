#include <bits/stdc++.h>
#include "state.hpp"

using namespace std;

const string goal = "123456789abcdef-";

int astar(State first, int (*f)(State));
int h0(State state);
int h1(State state);
int h2(State state);

int main() {
    int shuffle;
    cout << "Input shuffle counts >> ";
    cin >> shuffle;

    State first = state_get_random(goal, shuffle);

    cout << "Problem: " << endl;
    state_show(first);

    cout << "\nSolving with h0...\n";
    astar(first, h0);
    cout << "\nSolving with h1...\n";
    astar(first, h1);
    cout << "\nSolving with h2...\n";
    astar(first, h2);
}

int astar(State first, int (*f)(State)) {
    priority_queue<State, vector<State>, greater<State>> pq;
    unordered_set<string> closed;

    pq.push(first);

    int loop_cnt = 0;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.st == goal) {
            //state_show(current);
            cout << "moves: " << current.depth << endl;
            break;
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

    cout << "iters: " << loop_cnt << endl;
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