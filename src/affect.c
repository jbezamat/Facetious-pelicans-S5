#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "board.h"
#include "affect.h"
#include "functions.h"


/* INIT AFFECT */

struct affect init_affect(struct board *b, int num) {
  /*First affectation on the board
    Board b : board we use to place the pelicans
    num : number of pelicans we want to place
   */
  int n=num_positions(b);
  int res_scanf=0;
  int c;
  while ((num>n) || (num<0)){ //Number of pelicans we want to place <= number of positions on the board
    printf("The number of pelicans need to be inferior or equal of the number of positions(%d) \n",n);
    printf("Please enter a new number of pelicans: ");
    res_scanf=scanf("%d",&num);
   
    if (res_scanf!=1){
      printf("Wrong Entry please retry\n");
      num=-1;
  
      while ((c = getchar ()) != '\n' && c != EOF);//To delete buffer
    }
  }


  //Simple affectation of the pelicans
  struct affect a={.num_pelicans=num,.id=b->id};
  int i;
  int k=num;
  for(i=num_positions(b)-1; i>=0; i--){ //i= piaf number
    if(k>0){  //We order the affectation table for the next_permutation 
      a.pelicans[i]=k;
      k--;
    }else{ //We need to put the '0' before the number of pelicans
      a.pelicans[i]=0; 
    }
  }
  return a;
}


struct affect init_affect_random(struct board *b, int num) {
  /*Random affectation initialisation on the board
    Board b : board we use to place the pelicans
    num : number of pelicans we want to place
  */
  int n=num_positions(b);
  int res_scanf=0;
  int c;
  while ((num>n) || (num<0)){ //Number of pelicans we want to place <= number of positions on the board
    printf("The number of pelicans need to be inferior or equal of the number of positions(%d) \n",n);
    printf("Please enter a new number of pelicans: ");
    res_scanf=scanf("%d",&num);
   
    if (res_scanf!=1){
      printf("Wrong Entry please retry\n");
      num=-1;
     
      while ((c = getchar ()) != '\n' && c != EOF);//To delete buffer
    }
  }

  struct affect a={.num_pelicans=num,.id=b->id};

  int i;
  int j;
 
 
  //This table stock the numbers we want to use for random affectation
  int t[n];
  for (i=0; i<n ; i++){
    t[i]=i;
    a.pelicans[i]=0;
  }
  int pos=0;
  int index_pos=0;
 
  for(j=1; j<(num+1); j++){ //j= piaf number
    //Now we can use the function rand only with the numbers we haven't use yet
    index_pos = rand_c(n);
    pos=t[index_pos];
    a.pelicans[pos]=j;
    n=n-1;

    //Exchange position of number used and last number of table t
    int tmp=t[n];
    t[n]=t[index_pos];
    t[index_pos]=tmp;
  }
  return a;
}


/* FUNCTIONS RELATIVES TO AFFECT */

int num_pelicans(const struct affect *a){
  return  (*a).num_pelicans;
}

/* FUNCTIONS RELATIVES TO CONSTRAINT */

//Return the number of constraint n of the pelican p
int recover_constraint(struct affect *a, int p){
  return (*a).tab_constraints[p-1].n;
}

//Return the number of associate pelican to the constraint of pelican p
int recover_p2(struct affect *a, int p){
  return (*a).tab_constraints[p-1].p2;
}

//Give a number of constraint (and of a second pelican if necessary) for the pelican p1
//Stock them in the struct constraint
struct constraint random_constraint(struct affect *a, int p1){
  int num;
  if (a->id==1)
    num=NUM_CONSTRAINTS_1;
  else if(a->id==2)
    num=NUM_CONSTRAINTS_2;
  else if(a->id==3)
    num=NUM_CONSTRAINTS_3;

  int n = rand_c(num)+1; //Give a random number between 1 & NUM_CONSTRAINTS for the number of constraint
  int p2;
  if (n>7 && n<14){
    do
      {
        p2 = rand_c(num_pelicans(a))+1;
	if(num_pelicans(a)==1){ //if we have only one pelican
	  p2=p1;
	  break; //..to avoid infinite loop
	}
      } while (p1==p2);
  } else
    p2=0;
  struct constraint c={n,p1,p2};
  
  return c;
}

//Create a random affectation for all the pelicans on the board
void constraint_affect(struct affect *a){
  int i=0;

  for (i=0; i<=num_pelicans(a) ; i++){
    (*a).tab_constraints[i]=random_constraint(a, i+1); // Because tab_constraints[n] correspond at the pelican with number n+1
    }

}
