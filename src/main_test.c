#include <stdio.h>
#include "../src/define.h"
#include "../src/board.h"
#include "test_function.h"



int main(int argc, char *argv[]){
  struct board b=init_board_2();
  
  int count_error=test_distance(&b);
  print_test(count_error,"distance");
  
  count_error=test_has_tag(&b);
  print_test(count_error,"has_tag");
  
  count_error=test_next_permutation();
  print_test(count_error,"next_permuation");
  
  
  
  return 0;
}
