#!/bin/sh

_previous_shasum=`shasum ../../../../../.build/ymdk_ymd09_\`qmk config user.name | cut -d'=' -f 2\`.elf`

qmk clean
sync

git submodule sync --recursive
git submodule update --init --recursive --progress

git checkout dev
git fetch --all
git pull origin dev
git pull upstream master --no-edit

sync

qmk compile
sync

echo
echo previous: $_previous_shasum
echo ' current:' `shasum ../../../../../.build/ymdk_ymd09_\`qmk config user.name | cut -d'=' -f 2\`.elf`
echo
