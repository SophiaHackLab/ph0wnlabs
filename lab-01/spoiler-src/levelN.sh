#!/bin/bash

# Check if the level number is passed as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 levelN (e.g., level1, level2, level3)"
  exit 1
fi

LEVEL=$1
LEVEL_FILE="${LEVEL}.c"

# Check if the level file exists
if [ ! -f "$LEVEL_FILE" ]; then
  echo "Error: ${LEVEL_FILE} not found."
  exit 1
fi

# Backup the original file to restore later
cp "$LEVEL_FILE" "${LEVEL_FILE}.bak"

# Step 1: Add a main() function to the level file
echo "Patching ${LEVEL_FILE} to add main()..."

# Add a main function wrapper to the level file
cat <<EOL > ${LEVEL_FILE}
#include <stdio.h>

// Include the base64.h if necessary
#include "base64.h"

int ${LEVEL}();

int main() {
    printf("Running ${LEVEL}...\n");
    ${LEVEL}();  // Call the level function
    return 0;
}
EOL

cat "${LEVEL_FILE}.bak" >> ${LEVEL_FILE}

#cat ${LEVEL_FILE}

# Step 2: Compile the level to produce the executable
echo "Compiling ${LEVEL}..."
gcc ${LEVEL_FILE} -o "$LEVEL"

# Step 3: Restore the original level file (remove main())
echo "Restoring the original ${LEVEL_FILE}..."
mv "${LEVEL_FILE}.bak" "$LEVEL_FILE"


