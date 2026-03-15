#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("wrong number of arguments\n");
    return 1;
  }
  int vas_mb = atoi(argv[1]);
  int page_kb = atoi(argv[2]);
  int vaddr = atoi(argv[3]);
  int vas_bytes = vas_mb * 1024 * 1024;
  int page_bytes = page_kb * 1024;
  int num_pages = vas_bytes / page_bytes;
  int page_number = vaddr / page_bytes;
  int offset = vaddr % page_bytes;
  if (page_number >= num_pages) {
    printf("page table miss\n");
    return 0;
  }
  // simple page table having page i -> frame i
  int page_table[num_pages];
  for (int i = 0; i < num_pages; i++) 
    page_table[i] = i;
  int frame_number = page_table[page_number];
  printf("physical address = <%d, %d>", frame_number, offset);
  return 0;
}
