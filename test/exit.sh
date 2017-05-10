#!/bin/sh

make -c ..
./../bin/rshell << 'EOF'
mkdir test
test -e test
[ -e test ]
test -e test && ls
[ -e test ] && ls
exit
EOF

printf "\n"

make -C ..
./../bin/rshell << 'EOF'
echo hello
echo checking exit
exit
EOF

printf "\n"
rm -r test
ls

