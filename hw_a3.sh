#!/bin/bash

# Check if two parameters are given
if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <Month> <Day>"
    exit 1
fi

month=$1
day=$2

logfile="log.txt"  # Change this if your log file is named differently

awk -v month="$month" -v day="$day" '
BEGIN {
    intervals[0] = "00:00-03:59"
    intervals[1] = "04:00-07:59"
    intervals[2] = "08:00-11:59"
    intervals[3] = "12:00-15:59"
    intervals[4] = "16:00-19:59"
    intervals[5] = "20:00-23:59"

    for (i = 0; i < 6; i++) {
        sum[i] = 0
        count[i] = 0
    }
}
($1 == month && $2 == day) {
    hour = substr($3, 1, 2) + 0
    idx = int(hour / 4)
    sum[idx] += $4
    count[idx]++
}
END {
    for (i = 0; i < 6; i++) {
        if (count[i] > 0)
            avg = sum[i] / count[i]
        else
            avg = 0
        printf "%s : Average Users = %.2f\n", intervals[i], avg
    }
}
' "$logfile"

