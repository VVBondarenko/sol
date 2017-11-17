##################
# Sol Test Suite #
##################

import strutils
import times
import os

import sol

############
# Settings #
############

const solRuns = 1_000_000 # How many runs to average.
const solPrecision = 20 # Benchmark float accuracy.
const solAlignment = 10 # Left-alignment of output.

#############
# Templates #
#############

template bench(name: string, code: stmt) =
    var start: float = 0
    var average: float = 0
    var i = 0
    while i < solRuns:
        start = epochTime()
        code
        average += (epochTime() - start)
        i += 1
    average /= solRuns
    let output = average.formatFloat(format = ffDecimal, precision = solPrecision)
    echo "[sol] Average time for " & name.align(solAlignment) & ": " & output

###################
# Main Benchmarks #
###################

var a = vec3_init(1, 2, 3)
var b = vec3_init(3, 2, 1)
var c = vec3_zero()
var f: Float = 0

bench "vec3_init":
    c = vec3_init(2, 4, 8)

bench "vec3_add":
    c = vec3_add(a, b)

bench "vec3_sub":
    c = vec3_sub(a, b)

bench "vec3_mul":
    c = vec3_mul(a, b)

bench "vec3_div":
    c = vec3_div(a, b)

bench "vec3_avg":
    c = vec3_avg(a, b)

bench "vec3_mag":
    f = vec3_mag(c)

echo a
echo b
echo c
echo f
