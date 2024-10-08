#!/bin/bash

set -e

cat > .git/hooks/pre-commit <<EOF
#!/bin/sh
./contrib/format-all.sh --check
EOF

chmod +x .git/hooks/pre-commit
