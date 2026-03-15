#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
int main() {
  int fd[2];
  int a, b, c;
  int four_ac;
  int b_square;
  double result;
  printf("enter a, b, c: ");
  scanf("%d %d %d", &a, &b, &c);
  pipe(fd);
  if (fork() == 0) {
    close(fd[0]);
    four_ac = 4 * a * c;
    write(fd[1], &four_ac, sizeof(four_ac));
    close(fd[1]);
  }
  else {
    close(fd[1]);
    read(fd[0], &four_ac, sizeof(four_ac));
    b_square = b * b;
    result = sqrt(b_square - four_ac);
    printf("Result = %.2f", result);
    close(fd[0]);
  }
  return 0;
}

