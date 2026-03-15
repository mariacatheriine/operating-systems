#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
int main() {
  int fd1[2], fd2[2];
  char s1[50], s2[50], s3[50];
  char fin[200];
  pipe(fd1);
  pipe(fd2);
  printf("enter three strings: ");
  scanf("%s %s %s", s1, s2, s3);
  if (fork() == 0) {
    close(fd1[1]);
    close(fd2[0]);
    read(fd1[0], fin, sizeof(fin));
    char r1[50], r2[50], r3[50];
    sscanf(fin, "%s %s %s", r1, r2, r3);
    char temp[200] = "";
    strcat(temp, r1);
    strcat(temp, " ");
    strcat(temp, r2);
    strcat(temp, " ");
    strcat(temp, r3);
    write(fd2[1], temp, sizeof(temp));
    close(fd1[0]);
    close(fd2[1]);
  }
  else {
    close(fd1[0]);
    close(fd2[1]);
    sprintf(fin, "%s %s %s", s1, s2, s3);
    write(fd1[1], fin, sizeof(fin));
    read(fd2[0], fin, sizeof(fin));
    for (int i = 0; fin[i] != '\0'; i++) {
      if (islower(fin[i]))
        fin[i] = toupper(fin[i]);
      else if (isupper(fin[i]))
        fin[i] = tolower(fin[i]);
    }
  printf("Final Output: %s\n", fin);
  close(fd1[1]);
  close(fd2[0]);
  }
  return 0;
}
