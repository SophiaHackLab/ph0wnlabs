#!/usr/bin/env bash

# Define the expected passwords for each level
PASSWORDS=("ph0wn2026" "starport" "top_floor" "qrcode-solution.txt" )

# Path to the crackme binary
CRACKME="./crackme"

# Check if the binary exists
if [[ ! -x $CRACKME ]]; then
    echo "Error: $CRACKME not found or not executable."
    exit 1
fi

# Use expect to automate interaction with the binary
expect <<EOF
    set timeout -1

    # Start the crackme binary
    spawn $CRACKME

    # Level 1
    expect "Apartment tag:" {
        send "${PASSWORDS[0]}\r"
    }

    # Level 2
    expect "Business card:" {
        send "${PASSWORDS[1]}\r"
    }

    # Level 3
    expect "Floor:" {
        send "${PASSWORDS[2]}\r"
    }

    # Level 4
    expect "Filename:" {
        send "${PASSWORDS[3]}\r"
    }

    # Wait for the program to finish
    expect eof
EOF
