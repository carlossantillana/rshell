#!/bin/sh

make -C ..
./../bin/rshell << 'EOF'
(ls && ls) && ls ### ls
exit
EOF

printf "\n"
ls
