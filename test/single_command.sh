#!/bin/sh

make -C ..
./../rshell << 'EOF'
ls
echo hello
mkdir one
exit
EOF

printf "\n"
ls
rm -rf  one
