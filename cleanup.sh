#!/bin/bash

echo ""
echo "=============================================="
echo "Cleaning the residual files and old builds"
echo "=============================================="
echo ""

make clean
make mrproper
rm -rf $(pwd)/arch/arm/boot/Image
rm -rf $(pwd)/compiled_files/*
