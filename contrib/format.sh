#!/bin/sh

script_dir="$(cd -- "$(dirname -- "$0")" && pwd -P)"
exec python3 "$script_dir/format.py" "$@"
