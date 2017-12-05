##################
# Sol Test Suite #
##################

import strutils
import times
import os

import ../sol

############
# Settings #
############

const solRuns = 1_000_000 # How many runs to average.
const solPrecision = 20 # Benchmark float accuracy.

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
    echo "[sol] Benchmark for: " & name
    var output = average.formatFloat(format = ffDecimal, precision = solPrecision)
    echo "-> Cumulative Time: " & output
    average /= solRuns
    output = average.formatFloat(format = ffDecimal, precision = solPrecision)
    echo "-> Average Time:    " & output
    average = 1 / average
    output = average.formatFloat(format = ffDecimal, precision = solPrecision)
    echo "-> Runs Per Second: " & output

###################
# Main Benchmarks #
###################

var q = vec4_norm(vec4_init(0, 0, 1, 1))
var a = vec3_init(1, 2, 3)
var b = vec3_init(3, 2, 1)
var c = vec3_zero()
var f: Float = 0
var cross: int = 1

bench "vec3_init":
    c = vec3_init(2, 4, 8)

bench "vec3_add":
    c = a + b

bench "vec3_sub":
    c = a - b

bench "vec3_mul":
    c = a * b

bench "vec3_div":
    c = a / b

bench "vec3_avg":
    c = vec3_avg(a, b)

bench "vec3_mag":
    f = mag c

bench "vec3_rot":
    c = vec3_rot(c, q)

echo a
echo b
echo c
echo f
