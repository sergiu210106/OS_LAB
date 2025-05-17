#!/bin/bash


if [ -z "$1" ]; then
	echo "Usage: $0 <username>"
	exit 1
fi

username="$1"

section=$(echo "$username" | cut -c3-4)

digits=$(echo "$username" | grep -o "[0-9]")

sum=0
for digit in $digits; do
	sum=$((sum+digit))
done

echo "Section is: " $section
echo "Sum of digits is: " $sum

