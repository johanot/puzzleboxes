let state = 0
let position = 0
let min = 10
let max = 1010
let sequence: number[] = []

function genSequence(size: number) {
    readPosition()
    for (let i = 0; i < size; i++) {
        sequence[i] = Math.randomRange(min, max)
        if (i == 0) {
            // if the podmeter is already positioned here,
            // we want to find another start number
            if (isHit(sequence[i], position)) i--
        } else {
            // if this number is too close to the previos
            // selected number, we want to get another as well
            if (isHit(sequence[i], sequence[i - 1], 100)) i--
        }
    }
}

function isHit(target: number, base: number, distance = 20) {
    return (Math.abs(base - target) < distance)
}

function readPosition() {
    position = pins.analogReadPin(AnalogPin.P1)
}

function checkPosition() {
    if (state < 0) {
        basic.showIcon(IconNames.Sad)
        music.beginMelody(music.builtInMelody(Melodies.Wawawawaa), MelodyOptions.Once)
        basic.pause(5000)
        state = 0
    }
    basic.showNumber(state)
    if (isHit(sequence[state], position)) {
        music.playTone(262, 500)
        state = state + 1
        control.inBackground(function () {
            let oldState = state
            basic.pause(15000)
            if (state == oldState) {
                // Too bad, you were too slow
                state = -1
            }
        })
    }
    if (state > 5) {
        basic.showIcon(IconNames.Heart)
        music.beginMelody(music.builtInMelody(Melodies.Entertainer), MelodyOptions.Once)
        for (let i = 0; i < 5; i++) {
            basic.showNumber(5297)
        }
        state = 0
    }
}

input.onButtonPressed(Button.A, function () {
    basic.showNumber(position)
})

input.onButtonPressed(Button.B, function () {
    for (let i = 0; i < sequence.length; i++) {
        basic.showNumber(sequence[i])
    }
})

genSequence(6)

basic.forever(function () {
    readPosition()
    checkPosition()
})

