#!/bin/sh

make -C ..
./../rshell << 'EOF'
ls -a; echo hello; mkdir test
exit
EOF

printf "\n"
ls
rm -rf test


