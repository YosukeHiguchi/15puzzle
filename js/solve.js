globalFunc();

function astar() {
    var queue = [];
    var closed = new Set();
    var track = new Map();

    queue.push(main_state);
    track.set(main_state["st"], null);

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
            main_state = current;
            break;
        }

        closed.add(current["st"]);

        for (var i = 0; i < 4; i++) {
            var next = Object.assign({}, current);

            if (move_panel(next, i, false)) {
                if (!closed.has(next["st"])) {
                    next["depth"]++;
                    next["cost"] = next["depth"] + f(next["st"]);
                    queue.push(next);
                    track.set(next["st"], current["st"]);
                }
            }
        }
    }

    var backtrack = [];
    var parent = goal;
    while (parent != null) {
        backtrack.push(parent);
        parent = track.get(parent);
    }

    return backtrack;
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