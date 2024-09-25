#!/usr/bin/env bash

while IFS= read -r line; do
  name=$(echo $line | cut -d' ' -f1)
  version=$(echo $line | cut -d' ' -f2)

  echo "Installing $name version $version..."
  cargo binstall --version $version -y $name

done <./deps.lock
