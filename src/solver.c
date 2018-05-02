#include <stdio.h>
#include <stdlib.h>
#include "define.h" 
#include "functions.h"
#include "board.h"
#include "affect.h"
#include "constraint.h"

int solver(struct board *b, struct affect *a, int resultats[][MAX_POS]){
  int i=0;
  int k=0;
  int p;
  int n;
  int p1;
  int p2;
  int s=1;
  int cond=1;
  int num_solutions=0;
  int tab_rec[MAX_POS];

  
  while(cond){
    //Stop condition : all permutations done
    s=1;
    i=0;
   //In the pelicans affectation board :
    while( (i<num_positions(b)) && s){
      //Recover the number of pelican
      p=(*a).pelicans[i];
      n=(*a).tab_constraints[p-1].n; //because tab_constraints[p-1] correspond at the pelican with number p
      p1=(*a).tab_constraints[p-1].p1;
      p2=(*a).tab_constraints[p-1].p2;
      //And check if the constraint is satisfied
      s=apply_constraint_rec(b,a,n,p1,p2,tab_rec,0);
      i++;
    }
    if (s) {
      for(k=0;k<num_positions(b);k++)//write the solution in the table resultats
	resultats[num_solutions][k]=a->pelicans[k];
      num_solutions++;
    }
    cond=next_permutation((*a).pelicans, num_positions(b));
  }
  //We replace pelican in the first permutation (1,2,3,4,..) for the files functiion_test.c
  for(i=0; i<(a->num_pelicans); i++){ //j= piaf number
    a->pelicans[i]=i+1;
  }
  return num_solutions;
}


//with apply_constraint and not apply_constraint_rec
void solver_old(struct board *b, struct affect *a, int resultats[][MAX_POS]){
  int i=0;
  int k=0;
  int p;
  int n;
  int p1;
  int p2;
  int s=1;
  int cond=1;
  int num_solutions=0;
  
  while(cond){
    //Stop condition : all permutations done
    s=1;
    i=0;
   //In the pelicans affectation board :
    while( (i<num_positions(b)) && s){
      //Recover the number of pelican
      p=(*a).pelicans[i];
      n=(*a).tab_constraints[p-1].n; //because tab_constraints[p-1] correspond at the pelican with number p
      p1=(*a).tab_constraints[p-1].p1;
      p2=(*a).tab_constraints[p-1].p2;
      //And check if the constraint is satisfied
      s=apply_constraint(b,a,n,p1,p2);
      i++;
    }
    if (s) {
      //printf("Possible affectation :");
      // print_tab((*a).pelicans, num_positions(b));
      for(k=0;k<num_positions(b);k++)
	resultats[num_solutions][k]=a->pelicans[k];
      //print_tab(&resultats, 6);
      num_solutions++;
    }
    cond=next_permutation((*a).pelicans, num_positions(b));
  }
  //We replace pelican in the first permutation (1,2,3,4,..)
  for(i=0; i<(a->num_pelicans); i++){ //j= piaf number
    a->pelicans[i]=i+1;
  }
}
  
