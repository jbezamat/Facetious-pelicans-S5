#ifndef AFFECT_H
#define AFFECT_H

/* CONSTRAINT */

struct constraint{
  int n;
  int p1;
  int p2;
};

/* AFFECT */

struct affect {
  /*Struct which give the affectation and constraints of pelicans on the board.
    Pelicans are define by a color, represented by an integer.
    The table "pelicans" : table of integer where the index represent the positions and the values represent the number of pelicans*/
  int pelicans[MAX_POS];
  int num_pelicans;
  int id;
  struct constraint tab_constraints[MAX_POS]; // Warning ! tab_constraints[n] correspond at the pelican with number n+1
};

/* INIT AFFECT */

struct affect init_affect(struct board *, int);
struct affect init_affect_random(struct board *, int);

/* FUNCTIONS RELATIVES TO AFFECT */

int num_pelicans(const struct affect *);

/* FUNCTIONS RELATIVES TO CONSTRAINT */

int recover_constraint(struct affect *, int);
int recover_p2(struct affect *, int);
struct constraint random_constraint(struct affect *, int);
void constraint_affect(struct affect *);

#endif
