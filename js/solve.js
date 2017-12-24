var first;

function main() {
    first = state_get_random(goal, 0);

    canvas_draw_panel(first["st"]);

//    astar(first);
}

function astar(first) {
    var queue = [];
    var closed = new Set();

    queue.push(first);

    while (queue.length > 0) {
        var min = queue[0]["cost"], minIdx = 0;
        for (var i = 0; i < queue.length; i++) {
            if (queue[i]["cost"] < min) {
                min = queue[i]["cost"];
                minIdx = i;
            }
        }

        var current = queue[minIdx];
        queue.splice(minIdx, 1);

        if (current["st"] == goal) {
            console.log(current);
            canvas_draw_panel(current["st"]);
            break;
        }

        closed.add(current["st"]);

        for (var i = 0; i < 4; i++) {
            var next = Object.assign({}, current);

            if (move_panel(next, i)) {
                if (!closed.has(next["st"])) {
                    next["depth"]++;
                    next["cost"] = next["depth"] + f(next["st"]);
                    queue.push(next);
                }
            }
        }
    }
}

function f(s) {
    var cnt = 0;
    var len = N * N;

    for (var i = 0; i < len; i++) {
        if (goal.charAt(i) == '-') continue;

        for (var j = 0; j < len; j++) {
            if (goal.charAt(i) == s.charAt(j)) {
                cnt = cnt + Math.abs(j % N - i % N) + Math.abs(Math.floor(j / N) - Math.floor(i / N));
                break;
            }
        }
    }

    return cnt;
}