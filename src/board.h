#ifndef BOARD_H
#define BOARD_H

/* BOARD */

struct board {
  /* Board creation :
     -table "positions" with tag to each position
     -table "neighbours" with names of neighbours to each position */
  int num_positions;
  int num_neighbours;
  int id; //Id of board
  int positions[MAX_POS][MAX_TAG];
  int neighbours[MAX_POS][MAX_NEIGHBOURS];
};


/* INIT BOARD */
struct board init_board_1();
struct board init_board_2();
struct board init_board_3();

/* FUNCTIONS RELATIVES TO THE STRUCT BOARD */

unsigned int distance(const struct board* , unsigned int, unsigned int);
unsigned int num_positions(const struct board*);
int has_tag(const struct board*, unsigned int, unsigned int);
void print_board(const struct board* );

#endif
