
let stepA = 0
let solved = false
let tmp2 = 0
let tmp = 0
let array = [4, 3, 1, 2, 5]

input.onButtonPressed(Button.A, function () {
    let a = array.slice(0, array.length);
    tmp = a[stepA]
    a[stepA] = a[stepA + 1]
    a[stepA + 1] = tmp
    array = a
    stepA += 1
    if (stepA > 3) {
        stepA = 0
    }
})
input.onButtonPressed(Button.B, function () {
    let b = array.slice(0, array.length);
    tmp2 = b[0]
    b[0] = b[4]
    b[4] = tmp2
    array = b
})

basic.forever(function () {
    if (!solved) {
        for (let i = 0; i < 5; i++) {
            let count = 0
            for (let j = 0; j < 5; j++) {
                if (count < array[i]) {
                    led.plot(i, j)
                    count += 1
                } else {
                    led.unplot(i, j)
                }
            }

        }
    }
    else {
        basic.showString("5842")
    }

    solved = array[0] < array[1] && array[1] < array[2] && array[2] < array[3] && array[3] < array[4]
})
