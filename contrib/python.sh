#!/bin/bash

set -e

if [[ -z "$PYTHON_COMMAND" ]]; then
    PYTHON_COMMAND="$(which python3 || which python)"
fi

exec $PYTHON_COMMAND "$@"
