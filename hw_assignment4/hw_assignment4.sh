#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 <text_file>"
  exit 1
fi

INPUT_FILE="$1"
OUTPUT_DIR="digit_dicts"

mkdir -p "$OUTPUT_DIR"

rm -f "$OUTPUT_DIR"/[0-9].txt

for digit in {0..9}; do
  grep "^$digit" "$INPUT_FILE" | sort > "$OUTPUT_DIR/$digit.txt"
done

echo "Dictionary files created in the '$OUTPUT_DIR' directory."

