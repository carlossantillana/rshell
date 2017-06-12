#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pid_t pid;
int mypipe[2];
int ret;
char buf[20];
piped{
  ret = pipe(mypipe);
  if (ret == -1){
    perror("pipe");
    exit(1);

  }
  pid = fork();
  if (pid == 0){
    write(mypipe[1], "testing", 7);

  }
  else {
    printf("Parent Process\n");
    read(mypipe[0], buf, 15);
    printf("buf: %s\n", buf );
  }

}
