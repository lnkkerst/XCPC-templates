#!/usr/bin/env bash
#
mdbook build

cd book
git init
git config user.name "lnkkerst"
git config user.email "lnkkerst04@gmail.com"
git add .
git commit -m 'deploy'
git branch -M gh-pages
git remote add origin git@github.com:lnkkerst/XCPC-templates.git

git push -u -f origin gh-pages
