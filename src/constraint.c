#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "board.h"
#include "functions.h"
#include "affect.h"

/* CONSTRAINTS MONO-PELICAN */

//Function for 1 pelican with only 1 constraint :
int mono_pelican(struct board *b, struct affect *a, int p1, int c){
  int i;
  int pos;
  //Look for the position of the pelican p1 on the board
  for(i=0; i<num_positions(b); i++){
    if( (*a).pelicans[i]==p1){
      pos = i;
      /* Test if the constraint c is respected
         Return True (1) or False (0) */
      return (has_tag(b,pos,c));
    }
  }
  //If the pelican isn't on the board :
  printf("The pelican doesn't exist !\n");
  return 42; //Because 42
}

//Function with 2 constraints (A or B) :
int mono_pelican_2_OR(struct board *b, struct affect *a, int p1, int c1, int c2){
  return (mono_pelican(b,a,p1,c1) || mono_pelican(b,a,p1,c2));
}
 
//Function with 2 constraints (A & B) :
int mono_pelican_2_AND(struct board *b, struct affect *a, int p1, int c1, int c2){
  return (mono_pelican(b,a,p1,c1) && mono_pelican(b,a,p1,c2));
}


//Examples of functions with only 1 constraint with differents tags :
int in_north(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_NORTH);
}

int in_south(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_SOUTH);
}

int in_west(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_WEST);
}

int in_east(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_EAST);
}

int in_corner(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_CORNER);
}

int in_cercle_1(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_CERCLE_1);
}

int in_cercle_2(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_CERCLE_2);
}

int in_cercle_3(struct board *b, struct affect *a, int p1){
  return mono_pelican(b,a,p1,TAG_CERCLE_3);
}

int in_north_or_south(struct board *b, struct affect *a, int p1){
  return mono_pelican_2_OR(b,a,p1,TAG_NORTH,TAG_SOUTH);
}

int in_north_and_corner(struct board *b, struct affect *a, int p1){
  return mono_pelican_2_AND(b,a, p1, TAG_NORTH,TAG_CORNER);
}



/* CONSTRAINTS BI-PELICAN */

//Function for 2 pelicans :
int bi_pelican(struct board *b, struct affect *a, int p1, int p2, int c1, int c2){
  int i;
  int j;
  int pos1;
  int pos2;
  //Look for the position of the pelican p1 on the board
  for(i=0; i<num_positions(b); i++){
    for (j=0; j<num_positions(b); j++){
     
      if( (*a).pelicans[i]==p1 && (*a).pelicans[j]==p2){
        pos1 = i;
        pos2 = j;
        /* Test if the constraint is respected
           Return True (1) or False (0) */
        return (has_tag(b,pos1,c1) && has_tag(b,pos2,c2));
      }
    }
  }
  //If the pelicans don't on the board :
  printf("The pelicans don't exist !\n");
  return 42; //Because 42
}

 
//Function for 2 pelicans with the same constraint :
int bi_pelican_same(struct board *b, struct affect *a, int p1, int p2, int c){
  return (bi_pelican(b,a,p1,p2,c,c));
}

//Function for 2 pelicans with differents constraints :
int bi_pelican_diff(struct board *b, struct affect *a, int p1, int p2, int c1, int c2){
  return (bi_pelican(b,a,p1,p2,c1,c2));
}

//TODO 
//Function for 2 pelicans with opposite constraints

//Function for 2 pelicans with a first same constraint and a second constraint of distance
int bi_pelican_sd(struct board *b, struct affect *a, int p1, int p2, int c){
  int i;
  int j;
  int pos1;
  int pos2;

  if(p1==p2) 
    return 0; //To avoid infinite loop with the distance function ! 

  //Look for the position of the pelican p1 on the board
  for(i=0; i<num_positions(b); i++){
    for (j=0; j<num_positions(b); j++){
     
      if( (*a).pelicans[i]==p1 && (*a).pelicans[j]==p2){
        pos1 = i;
        pos2 = j;
        /* Test if the constraint is respected
           Return True (1) or False (0) */
        return (has_tag(b,pos1,c) && has_tag(b,pos2,c) && distance(b,pos1,pos2)==1);
      }
    }
  }
  //If the pelicans don't on the board :
  printf("The pelicans don't exist !\n");
  return 42; //Because 42
}



//Examples of functions for 2 pelicans with differents tags :
int in_front_of(struct board *b, struct affect *a, int p1, int p2){
  return (bi_pelican_diff(b,a,p1,p2,TAG_NORTH,TAG_SOUTH) || bi_pelican_diff(b,a,p1,p2,TAG_WEST,TAG_EAST)  || bi_pelican_diff(b,a,p1,p2,TAG_SOUTH,TAG_NORTH) ||  bi_pelican_diff(b,a,p1,p2,TAG_EAST,TAG_WEST));
}

int on_same_side(struct board *b, struct affect *a, int p1, int p2){
  return (bi_pelican_same(b,a,p1,p2,TAG_NORTH) || bi_pelican_same(b,a,p1,p2,TAG_SOUTH) || bi_pelican_same(b,a,p1,p2,TAG_WEST) || bi_pelican_same(b,a,p1,p2,TAG_EAST) );
}

int same_angle(struct board *b, struct affect *a, int p1, int p2){
  return (bi_pelican_sd(b,a,p1,p2,TAG_CORNER));
}

int same_cercle(struct board *b, struct affect *a, int p1, int p2){
  return (bi_pelican_same(b,a,p1,p2,TAG_CERCLE_1) || bi_pelican_same(b,a,p1,p2,TAG_CERCLE_2) || bi_pelican_same(b,a,p1,p2,TAG_CERCLE_3));
}




/* APPLY CONSTRAINT */

// Apply constraint (n,p1,p2) on board b with affectation a and returns a boolean telling if the constraint is verified
int apply_constraint(struct board *b, struct affect *a, int n, int p1, int p2){
    switch (n) {  
    case 0:
      return 1;
    case 1 :
      return in_north(b,a,p1);
    case 2 :
      return in_south(b,a,p1);
    case 3 :
      return in_west(b,a,p1);
    case 4 :
      return in_east(b,a,p1);
    case 5 :
      return in_corner(b,a,p1);
    case 6 :
      return in_north_or_south(b,a,p1);
    case 7 :
      return in_north_and_corner(b,a,p1);
    case 8 :
      return in_front_of(b,a,p1,p2);
 //Constraints for board 2 :
    case 9 :
      return on_same_side(b,a,p1,p2);
    case 10 :
      return same_angle(b,a,p1,p2);
 //Constraints for board 2 & 3:
    case 11 :
      return same_cercle(b,a,p1,p2);
    case 12 :
      return in_cercle_1(b,a,p1);
    case 13 :
      return in_cercle_2(b,a,p1);
    case 14 :
      return in_cercle_3(b,a,p1);
    }
    printf("Warning : You ask a contraint mono-pelican with two pelicans in argument !\n");
  return 42;
}



// Apply constraint recursive (n,p1,p2) on board b with affectation a and returns a boolean telling if the constraint is verified
// At the call of the function, tab must be created and size=0 (they will be usefull to detect cycles)
int apply_constraint_rec(struct board *b, struct affect *a, int n, int p1, int p2, int *tab, int size){

  int j;  
 //Board where we will stock the number of pelican p1  
  tab[size]=p1;
  size++;
  for(j=1; j<size-1; j++){
    //If a number is twice in the board : it's mean we are in a cycle 
    if (tab[j]==tab[size-1])
      return 1; //Our choice : if we are in a cycle that's mean all the pelicans want the same constraint, so the constraint is verified
  }

  switch (n) {
  case 0:
    return 1;
  case 1 :
    return in_north(b,a,p1);
  case 2 :
    return in_south(b,a,p1);
  case 3 :
    return in_west(b,a,p1);
  case 4 :
     return in_east(b,a,p1);
  case 5 :
    return in_corner(b,a,p1);
  case 6 :
    return in_north_or_south(b,a,p1);
  case 7 :
    return in_north_and_corner(b,a,p1);
  case 8 :
    return (apply_constraint_rec(b,a,recover_constraint(a,p2),p1,recover_p2(a,p2), tab, size)); //p1 wants the same constraint than p2
  case 9:
    return (!(apply_constraint_rec(b,a,recover_constraint(a,p2),p1,recover_p2(a,p2), tab, size))); //p1 wants the opposite constraint than p2
  case 10 :
    return in_front_of(b,a,p1,p2);
  //Constraints for board 2 :
  case 11 :
    return on_same_side(b,a,p1,p2);
  case 12 :
    return same_angle(b,a,p1,p2);
 //Constraints for board 2 & 3:
  case 13 :
    return same_cercle(b,a,p1,p2);
  case 14 :
    return in_cercle_1(b,a,p1);
  case 15 :
    return in_cercle_2(b,a,p1);
  case 16 :
    return in_cercle_3(b,a,p1);
  }
  printf("Warning : You ask a contraint mono-pelican with two pelicans in argument !\n");
  return 42;
}



/* OVER APPROXIMATION */


//Function to simplify the function over_approximation
void tag_front_of (int t_mult[][MAX_POS][MAX_POS], struct board *b){
  int j;
  int k=0;
  int l;

  for (j=0; j<num_positions(b); j++){
    k=0;
    //Pelican in north 
    if (has_tag(b,j,1)){
      for (l=0; l<num_positions(b); l++){
	if (has_tag(b,l,2)){
	  t_mult[0][j][k]=l; //write the position with the goods tags in t
	  k++;
	}
      }
    }
    //Pelican in south
    if (has_tag(b,j,2)){
      for (l=0; l<num_positions(b); l++){
	if (has_tag(b,l,1)){
	  t_mult[0][j][k]=l; //write the position with the goods tags in t
	  k++;
	}
      }
    }
    //Pelican in west
    if (has_tag(b,j,3)){
      for (l=0; l<num_positions(b); l++){
	if (has_tag(b,l,4)){
	  t_mult[0][j][k]=l; //write the position with the goods tags in t
	  k++;
	}
      }
    }
    //Pelican in east
    if (has_tag(b,j,4)){
      for (l=0; l<num_positions(b); l++){
	if (has_tag(b,l,3)){
	  t_mult[0][j][k]=l; //write the position with the goods tags in t
	  k++;
	}
      }
    }  
  }

}


//Function to simplify the function over_approximation
void tag_same_side (int t_mult[][MAX_POS][MAX_POS], struct board *b){
  int i;
  int j;
  int k=0;
  int l;
  for (j=0; j<num_positions(b); j++){
    k=0;
    for (i=1; i<=4; i++){
      if (has_tag(b,j,i)){
	for (l=0; l<num_positions(b); l++){
	  if (has_tag(b,l,i) ){
	    t_mult[1][j][k]=l; //write the position with the goods tags in t	    
	    k++;
	  }
	}
      }
    }
  }
}

//Function to simplify the function over_approximation
void tag_same_angle (int t_mult[][MAX_POS][MAX_POS], struct board *b){
  int i;
  int j;
  int k=0;
 
  for (j=0; j<num_positions(b); j++){
    k=0;
    if (has_tag(b,j,5)){
      for (i=0; i<(b->num_neighbours); i++){
	if ( has_tag(b,(b->neighbours[j][i]),5) ){
	  t_mult[2][j][k]=(b->neighbours[j][i]); //write the position with the goods tags in t
	  k++;
	}
      }
    }
  }
}

//Function to simplify the function over_approximation
void tag_same_cercle (int t_mult[][MAX_POS][MAX_POS], struct board *b){
  int i;
  int j;
  int k=0;
  int l;
  for (j=0; j<num_positions(b); j++){
    k=0;
    for (i=6; i<=8; i++){
      if (has_tag(b,j,i)){
	for (l=0; l<num_positions(b); l++){
	  if (has_tag(b,l,i)){
	    t_mult[3][j][k]=l; //write the position with the goods tags in t
	    k++;
	  }
	}
      }
    }
  }
}




//Stocks in boards the possibles positions for each constraint
void write_over_approximation(int t[][MAX_POS], int t_mult[][MAX_POS][MAX_POS], struct board *b){
  
  int j;
  int k;
  int n;


  // FIRST TAB : ONLY ONE LIST OF POSSIBLES POSITIONS FOR A CONSTRAINT (=> MONO-PELICAN CONSTRAINTS)
  //Constraints 1 to 5 (north, south, east, west, corner)
  
  for (n=1; n<=5; n++){ 
    k=0;
    for (j=0; j<num_positions(b); j++){
      if (has_tag(b,j,n)){
	t[n][k]=j; //write the position with the good tag in t
	k++;
      }
    }
  }
  
  //Constraint in_north_or_south
  k=0;
  for (j=0; j<num_positions(b); j++){
    if (has_tag(b,j,1) || has_tag(b,j,2)){
      t[6][k]=j; //write the position with the goods tags in t
      k++;
    }
  }
  
  
  //Constraint in_north_and_corner
  k=0;
  for (j=0; j<num_positions(b); j++){
    if (has_tag(b,j,1) &&  has_tag(b,j,5)){
      t[7][k]=j; //write the position with the goods tags in t
      k++;
    }
  }
  
  //Constraint in_cercle_1
  k=0;
  for (j=0; j<num_positions(b); j++){
    if (has_tag(b,j,6)){
      t[8][k]=j; //write the position with the goods tags in t
      k++;
    }
  }
  
  //Constraint in_cercle_2
  k=0;
  for (j=0; j<num_positions(b); j++){
    if (has_tag(b,j,7)){
      t[9][k]=j; //write the position with the goods tags in t
      k++;
    }
  }
  
  //Constraint in_cercle_3
  k=0;
  for (j=0; j<num_positions(b); j++){
    if (has_tag(b,j,8)){
	t[10][k]=j; //write the position with the goods tags in t
	k++;
    }
  }
  
  // SECOND TAB : SEVERAL LISTS OF POSSIBLES POSITIONS FOR A CONSTRAINT (=>BI-PELICAN CONSTRAINTS)
  // (DEPENDING THE INITIAL POSITION OF THE PELICAN)
  
  //Constraint in_front_of 
  tag_front_of(t_mult, b);
  
  //Constraint on_same_side
  tag_same_side(t_mult, b);

  //Constraint same_angle    
  tag_same_angle(t_mult, b);

  //Constraint same_cercle
  tag_same_cercle(t_mult, b);
  
  
}


/* PRINT CONSTRAINTS */
//Print the names of constraint for each pelican
void aff_constraint(int n, int p1, int p2){

  switch (n) {
  case 0:
    printf("    The pelican %d has no constraint.\n",p1);
    break;
  case 1 :
    printf("    The pelican %d wants to be in north.\n",p1);
    break;
  case 2 :
    printf("    The pelican %d wants to be in south.\n",p1);
    break;
  case 3 :
    printf("    The pelican %d wants to be in weast.\n",p1);
    break;
  case 4 :
    printf("    The pelican %d wants to be in east.\n",p1);
    break;
  case 5 :
    printf("    The pelican %d wants to be in a corner.\n",p1);
    break; 
  case 6 :
    printf("    The pelican %d wants to be in north or south.\n",p1);
    break;
  case 7 :
    printf("    The pelican %d wants to be in north and corner.\n",p1);
    break;
  case 8 :
    printf("    The pelican %d wants the same constraint than pelican %d.\n",p1,p2);
    break;
  case 9:
    printf("    The pelican %d wants the opposite constraint than pelican %d.\n",p1,p2);
    break;
  case 10 :
    printf("    The pelican %d wants to be in front of pelican %d.\n",p1,p2);
    break;
  case 11 :
    printf("    The pelican %d wants to be on same side than pelican %d.\n",p1,p2);
    break;
  case 12 :
    printf("    The pelican %d wants to be in the same angle than pelican %d.\n",p1,p2);
    break;
  case 13 :
    printf("    The pelican %d wants to be in the same cercle than pelican %d.\n",p1,p2);
    break;
  case 14 :
    printf("    The pelican %d wants to be in cercle 1.\n",p1);
    break;
  case 15 :
    printf("    The pelican %d wants to be in cercle 2.\n",p1);
    break;
  case 16 :
    printf("    The pelican %d wants to be in cercle 3.\n",p1);
    break;
  }
 
}
