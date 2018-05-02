#include <stdio.h>
#include "../src/define.h"
#include "../src/board.h"
#include "../src/affect.h"
#include "../src/constraint.h"
#include "test_function.h"



int main(int argc, char *argv[]){
  struct board b3=init_board_3();
  struct board b2=init_board_2();
  
  int count_error=test_distance(&b3,&b2);
  print_test(count_error,"distance total");
  
  count_error=test_has_tag(&b3);
  print_test(count_error,"has_tag");
  
  count_error=test_next_permutation();
  print_test(count_error,"next_permuation total");
  
  struct board b1=init_board_1();
  struct affect a1=init_affect(&b1, 4);//We affect 4 pelicans on the board 1
  
  
  struct affect a2=init_affect(&b2, 8);//We affect 8 pelicans on the board 2
  
  count_error=test_solver(&b1,&a1,&b2,&a2);
  print_test(count_error,"solver total");

  count_error=test_z3solver(&b1,&a1,&b2,&a2);
  print_test(count_error,"z3solver total");
  return 0;
}
