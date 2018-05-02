#include <stdlib.h>
#include <stdio.h>
#include "define.h"
#include "functions.h"
#include "board.h"
#include "affect.h"
#include "solver.h"
#include "constraint.h"
#include "z3solver.h"

//Functions to simplify the main
void print_constraint(struct affect *a){
  int i;
  int n;
  int p1;
  int p2;
  //Print the number of pelicans and their constraints on the console
  for(i=0; i<num_pelicans(a) ; i++){
    n=(*a).tab_constraints[i].n;
    p1=(*a).tab_constraints[i].p1;
    p2=(*a).tab_constraints[i].p2;
    aff_constraint(n,p1,p2);
  }

}

void first_solver_call(struct board *b, struct affect *a){
  printf("\nUtilisation of the first solver :\n");
  int resultats[MAX_POS][MAX_POS];
  int num_solutions = solver(b,a,resultats);
  int k;
  int l;
  if (num_solutions==0)
    printf("No possible solution\n");
  else {
    for (k=0; k<num_solutions; k++){
      printf("Possible affectation :\n");
      for(l=0;l<num_positions(b);l++){
	printf("    Pelican %d at position %d\n",resultats[k][l],l);
      }
    }
  }
}

void z3_solver_call(struct board *b, struct affect *a, int n){
  printf("\nUtilisation of the z3 solver :\n");
  int resultats[MAX_POS];
  z3_solver(b,a, n, resultats);
  printf("One possible solution :\n");
  int k;
  for (k=0; k<num_positions(b); k++)
    printf("    Pelican %2d at position %2d\n",resultats[k],k);
  
}

/* MAIN PROGRAMME */

int main (int argc, char *argv[]){

  if(argc>2){

    int board_choice=atoi(argv[1]);
    int number_pelicans=atoi(argv[2]);
    int solver_choice=atoi(argv[3]);

    //Board 4
    if (board_choice==4){
      printf("Board choice : 4 positions\n");
      struct board b=init_board_1();
      
      printf("\nRandom constraints affectation on the %d pelicans...\n",number_pelicans);
      struct affect a = init_affect(&b,number_pelicans);
      constraint_affect(&a);

      print_constraint(&a);

      if (solver_choice==0)
	first_solver_call(&b,&a);
      else if (solver_choice==1)
	z3_solver_call(&b,&a,number_pelicans);
      else
	printf("HELP : The command line must look like './main a b c' with a,b and c integers.\nLook at the READ.ME for more explanations.\n");
    }
    //Board 8
    else if (board_choice==8){
      printf("Board choice : 8 positions\n");
      struct board b=init_board_2();
      
      printf("\nRandom constraints affectation on the %d pelicans...\n",number_pelicans);
      struct affect a = init_affect(&b,number_pelicans);
      constraint_affect(&a);

      print_constraint(&a);
      
      if (solver_choice==0)
	first_solver_call(&b,&a);
      else if (solver_choice==1)
	z3_solver_call(&b,&a,number_pelicans);
      else
	printf("HELP : The command line must look like './main a b c' with a,b and c integers.\nLook at the READ.ME for more explanations.\n");  
    }
    //Board 16
    else if (board_choice==16){
      printf("Board choice : 16 positions\n");
      struct board b=init_board_3(); 
      
      printf("\nRandom constraints affectation on the %d pelicans...\n",number_pelicans);
      struct affect a = init_affect(&b,number_pelicans);
      constraint_affect(&a);
      
      print_constraint(&a);

      if (solver_choice==0)
	first_solver_call(&b,&a);
      else if (solver_choice==1)
	z3_solver_call(&b,&a,number_pelicans);
      else
	printf("HELP : The command line must look like './main a b c' with a,b and c integers.\nLook at the READ.ME for more explanations.\n");
    }
    else
      printf("HELP : The command line must look like './main a b c' with a,b and c integers.\nLook at the READ.ME for more explanations.\n");
  }
  else
    printf("HELP : The command line must look like './main a b c' with a,b and c integers.\nLook at the READ.ME for more explanations.\n");

  return EXIT_SUCCESS;
}

  
