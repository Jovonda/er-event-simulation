#!/bin/sh

# Clean Build Directory
find ./build/* ! -name ".gitignore" -exec rm -rf {} +

# Clean Out Directory
rm out/*.out