#include <bits/stdc++.h>
#include "state.hpp"

using namespace std;

const string goal = "123456789abcdef-";

priority_queue<State, vector<State>, greater<State>> pq;
unordered_set<string> closed;

int h0(State state);
int h1(State state);

int main() {
    State first = state_get_random(goal, 20);

    state_show(first);
    pq.push(first);

    int loop_cnt = 0;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.st == goal) {
            state_show(current);
            cout << "steps: " << current.depth << endl;
            break;
        }

        closed.insert(current.st);

        for (int i = 0; i < 4; i++) {
            State next = current;

            if (move_panel(next, i)) {
                if (closed.find(next.st) == closed.end()) {
                    next.depth = current.depth + 1;
                    next.cost = next.depth + h1(next);
                    pq.push(next);
                }
            }
        }

        loop_cnt++;
    }

    cout << "iterations: " << loop_cnt << endl;
}

int h0(State state) {
    return 0;
}

int h1(State state) {
    int cnt = 0;

    for (int i = 0; i < goal.length(); i++) {
        if (state.st[i] != goal[i]) cnt++;
    }

    return cnt;
}