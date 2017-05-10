RSHELL

Licensing information: READ LICENSE

Project source can be downloaded at https://github.com/csant019/rshell.git

Author and contribution list:
Jonathan Woolf
Carlos Santillana

All bug reports can be sent to jwool003@ucr.edu and csant019@ucr.edu

How to run the program:
In terminal:
1. git clone http://github.com/yourusername/rshell.git
2. cd rshell
3. make
4. bin/rshell

Summary:

rshell attempts to mimic a bash terminal shell. rshell accepts bash command executables that exist in /bin

ls mimics the GNU ls command and is functional for the "-a", "-l", and "-R" flags.

cp mimics the cp bash command.

cat prints out file

Functionality:

rshell does virtually everything the bash shell does, save for some subtleties.
For example, it will not perform the cd command.

Sample output as follows:

Please enter a command:
$

Bugs:

Multiple exits required occasionally
Multiple connectors not accepted
