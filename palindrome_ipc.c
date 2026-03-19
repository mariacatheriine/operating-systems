#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
int main() {
  int fd1[2], fd2[2];
  char str[50], rev[50];
  pipe(fd1);
  pipe(fd2);
  printf("enter a string: ");
  scanf("%s", str);
  if (fork() == 0) {
  close(fd1[1]);
  close(fd2[0]);
  read(fd1[0], str, sizeof(str));
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    rev[i] = str[len - i - 1];
  }
  rev[len] = '\0';
  write(fd2[1], rev, sizeof(rev));
  close(fd1[0]);
  close(fd2[1]);
  }
  else {
    close(fd1[0]);
    close(fd2[1]);
    write(fd1[1], str, sizeof(str));
    read(fd2[0], rev, sizeof(rev));
    if (strcmp(str, rev) == 0)
      printf("the string is a palindrome\n");
    else
      printf("the string is NOT a palindrome\n");
  close(fd1[1]);
  close(fd2[0]);
  }
  return 0;
}
