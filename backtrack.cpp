#include <bits/stdc++.h>
#include "debug.hpp"

using namespace std;

const string goal = "123456789abcdef-";

priority_queue<State, vector<State>, greater<State>> pq;
vector<State> closed;
//unordered_set<string> closed;

int h0(State state);
int h1(State state);

int main() {
    State first = state_get_random(goal, 10);

    pq.push(first);

    cout << "Problem: " << endl;
    state_show(first.st);
    cout << "Steps: " << endl;

    int loop_cnt = 0;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.st == goal) {
            vector<string> out;
            State back = current;
            out.push_back(back.st);

            while (1) {
                for (int i = 0; i < closed.size(); i++) {
                    if (back.parent == closed[i].st) {
                        back = closed[i];
                        break;
                    }
                }

                if (back.parent == "") break;

                out.push_back(back.st);
            }

            for (int i = out.size() - 1; i >= 0; i--) {
                cout << out.size() - i << endl;
                state_show(out[i]);
            }

            break;
        }

        closed.push_back(current);

        for (int i = 0; i < 4; i++) {
            State next = current;

            if (move_panel(next, i)) {
                int j;
                for (j = 0; j < closed.size(); j++) {
                    if (closed[j].st == next.st) break;
                }

                if (j == closed.size()) {
                    next.parent = current.st;
                    next.depth = current.depth + 1;
                    next.cost = next.depth + h0(next);
                    pq.push(next);
                }
            }
        }

        loop_cnt++;
    }
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