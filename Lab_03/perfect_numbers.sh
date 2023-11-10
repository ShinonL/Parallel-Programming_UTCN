#!/bin/bash
# Spawns $1 instances of the program $2

instances=$1
program=$2
A=$3
B=$4

for i in `seq 1 $instances`
do
    start_i=$((A+(B-A)*(i-1)/instances))
    end_i=$((A+(B-A)*i/instances-1))
    $program $start_i $end_i &
done
wait

# N = 1
# $ time bash perfect_numbers.sh 1 ./perfect_numbers 1 100000
# 6 28 496 8128
# 
# real    0m0.067s
# user    0m0.067s
# sys     0m0.000s

# N = 4
# $ time bash perfect_numbers.sh 4 ./perfect_numbers 1 100000
# 6 28 496 8128
# 
# 
# 
# 
# real    0m0.039s
# user    0m0.101s
# sys     0m0.000s

# S4 = T1 / T4 = 0.067 / 0.039 = 1.7179487179487179487179487179487
# E4 = S4 / 4 = 1.7179487179487179487179487179487 / 4 = 0.42948717948717948717948717948718