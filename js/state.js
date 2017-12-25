globalFunc();

function move_panel(state, move, anim) {
    var idx = state["blank"];
    var target = -1;

    switch (move) {
        case 0: // up
            if (Math.floor(idx / N) > 0) target = idx - N;
            break;
        case 1: // down
            if (Math.floor(idx / N) < N - 1) target = idx + N;
            break;
        case 2: // left
            if (idx % N > 0) target = idx - 1;
            break;
        case 3: // right
            if (idx % N < N - 1) target = idx + 1;
            break;
    }

    if (target != -1) {
        var newstr = "";
        for (var i = 0; i <  N * N; i++) {
            if (i == idx || i == target) {
                newstr += (i == idx)? state["st"].charAt(target): state["st"].charAt(idx);
            } else {
                newstr += state["st"].charAt(i);
            }
        }

        if (anim) {
            var cnt = 0;
            var str = state["st"];
            var intervalID = setInterval(function(){
                swap(cnt++, idx, str, target, move)
                if (cnt >= 6) clearInterval(intervalID);
            }, 10);
            // setTimeout(function() {
            //     clearInterval(intervalID);
            //     canvas_draw_panel(newstr);
            // }, 60);
        }

        state["st"] = newstr;
        state["blank"] = target;

        return true;
    }

    return false;
}

function state_set(s) {
    var ret = {};

    ret["st"] = s;
    ret["depth"] = 0;
    ret["cost"] = 0;
    for (var i = 0; i < s.length; i++) {
        if (s.charAt(i) == "-") {
            ret["blank"] = i;
            break;
        }
    }

    return ret;
}

function state_get_random(s, shuffle) {
    var ret = {};

    ret["st"] = s;
    ret["depth"] = 0;
    ret["cost"] = 0;
    for (var i = 0; i < s.length; i++) {
        if (s.charAt(i) == "-") {
            ret["blank"] = i;
            break;
        }
    }

    var vec = [1, -1, 2, -2];
    var r, bef_vec;
    for (var c = 0; c < shuffle; c++) {
        do {
            r = getRandomInt(0, 3);
        } while (c != 0 && vec[r] == -1 * bef_vec);

        if (move_panel(ret, r, false)) {
            bef_vec = vec[r];
        } else {
            c--;
        }
    }

    return ret;
}

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}