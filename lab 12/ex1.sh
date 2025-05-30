#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename=$1;

if [ ! -f "$filename" ]; then
    echo "Not a valid file"
    exit 1
fi

n=$(grep "</aixm:Route>" $filename | wc -l)

echo "number of routes : $n"

a=$(grep "<aixm:militaryUse>" $filename | sort --unique | wc -l)

echo "number of unique military uses: $a"

for u in $(grep "<aixm:militaryUse>" $filename | sort --unique); do
    echo "$u $(grep $u $filename | wc -l)"
done

