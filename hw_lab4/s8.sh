#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File $file not found! Skipping."
        continue
    fi
    
    awk -F: '{if (NF >= 3) $3=$1; print}' OFS=: "$file" > temp_file && mv temp_file "$file"
done

echo "Processing complete."

