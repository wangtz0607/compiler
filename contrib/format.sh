#!/bin/sh

script_dir="$(cd -- "$(dirname -- "$0")" && pwd -P)"
exec "$script_dir/python.sh" "$script_dir/format.py" "$@"
