#!/usr/bin/env bash
echo "Creating build directory.."
mkdir -p build
cd build
echo "Building project..."
cmake ..
echo "Linking project files..."
make Client
make Server
make Editor
cd ..
echo "Installing game files to chosen directory..."
mkdir -p $1
cp Client $1
cp Server $1
cp Editor $1
cp font.ttf $1
cp -r resources $1
cp -r config $1
cp -r levels $1
echo "Cleaning build files..."
rm Client
rm Server
rm Editor
rm -rf build
echo "Installation finished, enjoy our game!"