#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 user1 [user2 ...]"
    exit 1
fi

logged_in_users=$(who | awk '{print $1}')

for user in "$@"; do
    if echo "$logged_in_users" | grep -qw "$user"; then
        echo "$user is currently connected."
    fi
done

