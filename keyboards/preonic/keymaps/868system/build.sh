#!/bin/sh

_previous_shasum=`shasum ../../../../.build/preonic_rev3_drop_\`qmk config user.name | cut -d'=' -f 2\`.bin`

qmk clean
sync

git submodule sync --recursive
git submodule update --init --recursive --progress

git checkout dev
git fetch --all
git pull origin dev
git pull upstream master --no-edit

sync

qmk compile --keyboard preonic/rev3_drop
sync

echo
echo previous: $_previous_shasum
echo ' current:' `shasum ../../../../.build/preonic_rev3_drop_\`qmk config user.name | cut -d'=' -f 2\`.bin`
echo
