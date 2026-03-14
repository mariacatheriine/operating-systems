#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
  pid_t pid = fork();
  if (pid == 0) {
    char *args[] = {"./myadder", "10", "20", NULL};
    execvp(args[0], args);
  }
  else {
    wait(NULL);
    printf("parent process completed\n");
  }
  return 0;
}
