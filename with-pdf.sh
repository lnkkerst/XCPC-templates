#!/usr/bin/env bash

echo ":: Install dependencies..."
cd ./mdbook-pdf
bun i
cd ..

echo ":: Backup book.toml..."
cp book.toml book.toml.bak
cat >>book.toml <book-pdf.toml

echo ":: Build..."
mdbook build

today=$(date +%Y%m%d)

echo ":: Restore book.toml..."
mv book.toml.bak book.toml
