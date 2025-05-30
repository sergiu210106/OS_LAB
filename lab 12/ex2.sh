#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename=$1;
file2="Route2.BASELINE.xml";

cp $filename $file2

sed -n "s/'<gml:beginPosition>2022-06-16T00:00:00</gml:beginPosition>'/''<gml:beginPosition>2025-06-16T00:00:00</gml:beginPosition>'" $file2

echo "Replaced"
