var ctx;
const W = 400, H = 400;

var img = [];
var state_idx = {
    "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "a": 10,
    "b": 11, "c": 12, "d": 13, "e": 14, "f": 15, "-": 16
}

function canvas_init() {
    var canvas = document.getElementById("canvas");

    if (canvas.getContext) {
        ctx = canvas.getContext("2d");

        for (var i = 0; i < N * N; i++) {
            img.push(new Image());
            img[i].src = "./img/" + (i + 1) + ".png";
        }

        img[N * N - 1].onload = function() {
            main();
        }
    }
}

function canvas_draw_panel(s) {
    for (var i = 0; i < N; i++) {
        for (var j = 0; j < N; j++) {
            ctx.drawImage(img[state_idx[s.charAt(i * N + j)] - 1], 100 * j, 100 * i);
        }
    }
}

function swap(cnt, idx, state, target, move) {
    //ctx.clearRect(0, 0, W, H);

    switch (move) {
        case 0:
            ctx.drawImage(img[state_idx[state["st"].charAt(idx)] - 1], 100 * (target % 4), 100 * Math.floor(target / 4) + cnt * 20);
            ctx.drawImage(img[state_idx[state["st"].charAt(target)] - 1], 100 * (idx % 4), 100 * Math.floor(idx / 4) - cnt * 20);
            break;
        case 1:
            ctx.drawImage(img[state_idx[state["st"].charAt(idx)] - 1], 100 * (target % 4), 100 * Math.floor(target / 4) - cnt * 20);
            ctx.drawImage(img[state_idx[state["st"].charAt(target)] - 1], 100 * (idx % 4), 100 * Math.floor(idx / 4) + cnt * 20);
            break;
        case 2:
            ctx.drawImage(img[state_idx[state["st"].charAt(idx)] - 1], 100 * (target % 4) + cnt * 20, 100 * Math.floor(target / 4));
            ctx.drawImage(img[state_idx[state["st"].charAt(target)] - 1], 100 * (idx % 4) - cnt * 20, 100 * Math.floor(idx / 4));
            break;
        case 3:
            ctx.drawImage(img[state_idx[state["st"].charAt(idx)] - 1], 100 * (target % 4) - cnt * 20, 100 * Math.floor(target / 4));
            ctx.drawImage(img[state_idx[state["st"].charAt(target)] - 1], 100 * (idx % 4) + cnt * 20, 100 * Math.floor(idx / 4));
            break;
    }
}

document.onkeydown = function() {
    var e = event.keyCode;

    switch (e) {
        case 38: //up
            move_panel(first, 0);
            break;
        case 40: //down
            move_panel(first, 1);
            break;
        case 37: //left
            move_panel(first, 2);
            break;
        case 39: //right
            move_panel(first, 3);
            break;
    }
}