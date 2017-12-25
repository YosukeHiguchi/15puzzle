globalFunc();

$(document).ready(function() {
    var canvas = document.getElementById("canvas");

    if (canvas.getContext) {
        ctx = canvas.getContext("2d");

        for (var i = 0; i < N * N; i++) {
            img.push(new Image());
            img[i].src = "./img/" + (i + 1) + ".png";
        }

        img[N * N - 1].onload = function() {

            $("#btn-shuffle").on("click", function () {
                var cnt = $("#slider").text();
                main_state = state_get_random(main_state["st"], parseInt(cnt));
                canvas_draw_panel(main_state["st"]);

                console.log(main_state);
            });

            $("#btn-solve").on("click", function () {
                key_lock = true;

                var backtrack = astar();
                var i = backtrack.length - 1;

                var intervalID = setInterval(function () {
                    if (i == 0) {
                        key_lock = false;
                        return clearInterval(intervalID);
                    }
                    swap_state(backtrack[i], backtrack[i - 1]);
                    i--;
                }, 600);
            });

            $('#slider').slider({
                formatter: function(value) {
                    return value;
                }
            });

            main_state = state_set(goal);
            canvas_draw_panel(goal);
        }
    }
});

function canvas_draw_panel(s) {
    for (var i = 0; i < N; i++) {
        for (var j = 0; j < N; j++) {
            ctx.drawImage(img[state_idx[s.charAt(i * N + j)] - 1], 100 * j, 100 * i);
        }
    }
}

function swap(cnt, idx, str, tar, move) {
    switch (move) {
        case 0:
            ctx.drawImage(img[state_idx[str.charAt(tar)] - 1], 100 * (tar % 4), 100 * Math.floor(tar / 4) + cnt * 20);
            ctx.drawImage(img[state_idx[str.charAt(idx)] - 1], 100 * (idx % 4), 100 * Math.floor(idx / 4) - cnt * 20);
            break;
        case 1:
            ctx.drawImage(img[state_idx[str.charAt(tar)] - 1], 100 * (tar % 4), 100 * Math.floor(tar / 4) - cnt * 20);
            ctx.drawImage(img[state_idx[str.charAt(idx)] - 1], 100 * (idx % 4), 100 * Math.floor(idx / 4) + cnt * 20);
            break;
        case 2:
            ctx.drawImage(img[state_idx[str.charAt(tar)] - 1], 100 * (tar % 4) + cnt * 20, 100 * Math.floor(tar / 4));
            ctx.drawImage(img[state_idx[str.charAt(idx)] - 1], 100 * (idx % 4) - cnt * 20, 100 * Math.floor(idx / 4));
            break;
        case 3:
            ctx.drawImage(img[state_idx[str.charAt(tar)] - 1], 100 * (tar % 4) - cnt * 20, 100 * Math.floor(tar / 4));
            ctx.drawImage(img[state_idx[str.charAt(idx)] - 1], 100 * (idx % 4) + cnt * 20, 100 * Math.floor(idx / 4));
            break;
    }
}

function swap_state(str1, str2) {
    var idx, tar, move;
    for (var i = 0; i < N * N; i++) {
        if (str1.charAt(i) == "-") idx = i;
        if (str2.charAt(i) == "-") tar = i;
    }

    if (idx == tar - 1) move = 3; //right
    else if (idx == tar + 1) move = 2; //left
    else if (idx == tar - 4) move = 1; //up
    else if (idx == tar + 4) move = 0; //down

    var cnt = 0;
    var intervalID = setInterval(function(){swap(cnt++, idx, str1, tar, move)}, 10);
    setTimeout(function() {
        clearInterval(intervalID);
        canvas_draw_panel(str2);
    }, 60);

}

document.onkeydown = function() {
    var e = event.keyCode;

    if (key_lock) return;

    switch (e) {
        case 38: //up
        move_panel(main_state, 0, true);
        break;
        case 40: //down
        move_panel(main_state, 1, true);
        break;
        case 37: //left
        move_panel(main_state, 2, true);
        break;
        case 39: //right
        move_panel(main_state, 3, true);
        break;
    }
}