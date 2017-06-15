RSHELL

Licensing information: READ LICENSE

Project source can be downloaded at https://github.com/csant019/rshell.git

Author and contribution list:
Jonathan Woolf
Carlos Santillana

All bug reports can be sent to jwool003@ucr.edu and csant019@ucr.edu

How to run the program:
In terminal:
1. git clone https://github.com/csant019/rshell.git
2. cd rshell
3. make
4. bin/rshell

Summary:

rshell attempts to mimic a bash terminal shell. rshell accepts bash command executables that exist in /bin

Functionality:

rshell does virtually everything the bash shell does, save for some subtleties.
For example, it will not perform the cd command.

The following commands work as expected: ls (including  -a, -l, and -R),
cp, cat, echo, printf, mkdir, rmdir. git

Sample output as follows:

Please enter a command:
$ echo A && echo B || echo C && echo D
A
B
D
$

Bugs:
1. Git commit -m "Comment here" - Can only have one word written within quotes
2. Backwards semicolons ")(" do not produce error message if not the first command
3. After calling pipe the dollar sign prompt disappears, however; it still executes commands as it should.
4. The command "tee" does not work
