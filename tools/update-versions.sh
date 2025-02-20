#!/usr/bin/env bash

set -eux -o pipefail

VERSION=$1

GIT_ROOT=$(git rev-parse --show-toplevel)
cd "$GIT_ROOT"

# Strip suffixes (e.g. "-rc.1") from the version for cmake.
VERSION="${VERSION%-*}"

# Update VERSION in CMakeLists.txt.
sed -i -e "s/^  VERSION [0-9.]*$/  VERSION $VERSION/" CMakeLists.txt
