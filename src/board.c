#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "board.h"
#include <time.h>

/* INIT BOARD */

struct board init_board_1(){
  //Board initialisation 4 positions, Tags and neighbours attribution
  struct board b={.num_positions=4,\
                  .num_neighbours=2,\
		  .id=1,\
                  .neighbours={{1,3},{0,2},{1,3},{0,2}},\
                  .positions={{1,5}, {4,5}, {2,5}, {3,5}}};
  return b;
}


struct board init_board_2(){
  /*Board initialisation 8 positions "2 north 3 east 1 south 2 west", Tags and neighbours attribution*/

  struct board b={.num_positions=8,\
                  .num_neighbours=2,\
		  .id=2,\
                  .neighbours={{1,7},{0,2},{1,3},	\
                               {2,4},{3,5},{4,6},	\
                               {5,7},{6,0}},		\
                  .positions={ {1,5},{1,5},{4,5},{4},	\
                               {4,5},{2,5},{3,5},{3,5}}} ;  
  return b;
}

struct board init_board_3(){
  /*Board initialisation 16 positions "graphe planaire 5-régulier de diamètre 3", Tags and neighbours attribution
    Each position have 5 neighbours*/

  struct board b={.num_positions=16,\
                  .num_neighbours=5,\
		  .id=3,\
                  .neighbours={{1,3,4,7,8},{0,2,4,5,9},{1,3,5,6,10},\
                               {0,2,6,7,11},{0,1,8,9,12},{1,2,9,10,13},\
                               {2,3,10,11,14},{0,3,8,11,15},{0,4,7,12,15},\
                               {1,4,5,12,13},{2,5,6,13,14},{3,6,7,14,15},\
                               {4,8,9,13,15},{5,9,10,12,14},{6,10,11,13,15},\
                               {7,8,11,12,14}},\
                  .positions={ {1,5},{1,5},{2,5},{2,5},\
                               {1,8},{4,8},{2,8},{3,8},\
                               {3,7},{4,7},{4,7},{3,7},\
			       {1,6},{4,6},{2,6},{3,6}}} ;  
  return b;
}

/* FONCTIONS RELATIVES TO THE STRUCT BOARD */


unsigned int distance(const struct board *b, unsigned int x, unsigned int y){
  /*Calculate the distance between two positions x and y.
    The distance max is 3.
    If x and y are neighbours, the distance is 1.
    Else if x and y have a neighbour in common, the distance is 2.
    Else the distance is 3.
   */
  int i;
  int k;
  int z;
  int dist=0;
  if (x==y){
    printf("La tête à Toto !");
    return dist;
  }
  for(i=0;i<(*b).num_neighbours;i++){
    if(y==(*b).neighbours[x][i])
      return 1;
  }
  for(i=0;i<(*b).num_neighbours;i++){
    for(k=0;k<(*b).num_neighbours;k++){
      if((*b).neighbours[(*b).neighbours[x][i]][k]==y){
        return 2;
      }
    }
  }
  
  for(i=0;i<(*b).num_neighbours;i++){
    for(k=0;k<(*b).num_neighbours;k++){
      for(z=0;z<(*b).num_neighbours;z++){
	if((*b).neighbours[(*b).neighbours[(*b).neighbours[x][i]][k]][z]==y){
	  return 3;
	}
      }
    }
    
  }
  return 4;
}

unsigned int num_positions(const struct board *b){
  return (*b).num_positions;
}

int has_tag(const struct board *b,unsigned int position, unsigned int tag){
  int i;
  for(i=0; i<MAX_TAG; i++){
    if((*b).positions[position][i]==tag){
      return 1;
    }
  }
  return 0;
}


void print_board(const struct board *b){
  int n=num_positions(b);

  for (int i=0; i<n; i++){
    printf("Position %2d : [", i);
    for (int j=0; j<MAX_TAG; j++){
      printf("%2d", (*b).positions[i][j]);
     
    }
    printf("]\n");
  }
}
