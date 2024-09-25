#!/usr/bin/env bash

echo ":: Install dependencies..."
cd ./mdbook-pdf
bun i
bunx playwright install chromium
cd ..

echo ":: Backup book.toml..."
cp book.toml book.toml.bak
cat >>book.toml <book-pdf.toml

echo ":: Build..."
mdbook build
cp book/pdf/output-toc.pdf book/html

echo ":: Restore book.toml..."
mv book.toml.bak book.toml
