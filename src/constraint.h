#ifndef CONSTRAINT_H
#define CONSTRAINT_H

/* CONSTRAINTS MONO-PELICAN */

//Function with only 1 constraint :
int mono_pelican(struct board *, struct affect *, int, int);
//Function with A or B constraints :
int mono_pelican_2_OR(struct board *, struct affect *, int, int, int);
//Function with A & B constraints :
int mono_pelican_2_AND(struct board *, struct affect *, int, int, int);

//Functions with only 1 constraint with differents tags :
int in_north(struct board *, struct affect *, int);
int in_south(struct board *, struct affect *, int);
int in_west(struct board *, struct affect *, int);
int in_east(struct board *, struct affect *, int);
int in_corner(struct board *, struct affect *, int);
int in_cercle_1(struct board *, struct affect *, int);
int in_cercle_2(struct board *, struct affect *, int);
int in_cercle_3(struct board *, struct affect *, int);
int in_north_or_south(struct board *, struct affect *, int);
int in_north_and_corner(struct board *, struct affect *, int);

/* CONSTRAINTS BI-PELICAN */

//Function for 2 pelicans :
int bi_pelican(struct board *, struct affect *, int, int, int, int);
//Function for 2 pelicans with the same constraint :
int bi_pelican_same(struct board *, struct affect *, int, int, int);
//Function for 2 pelicans with differents constraints :
int bi_pelican_diff(struct board *, struct affect *, int, int, int, int);
//Function for 2 pelicans with a first same constraint and a second constraint of distance
int bi_pelican_sd(struct board *, struct affect *, int, int, int);

//Examples of functions for 2 pelicans with differents tags :
int in_front_of(struct board *, struct affect *, int, int);
int on_same_side(struct board *, struct affect *, int, int);
int same_angle(struct board *, struct affect *, int, int);
int same_cercle(struct board *, struct affect *, int, int);

/* APPLY CONSTRAINT */
int apply_constraint(struct board *, struct affect *, int, int, int);
int apply_constraint_rec(struct board *, struct affect *, int , int, int, int *, int);


/* OVER APPROXIMATION */
//Function to simplify the function over_approximation
void tag_front_of (int [][MAX_POS][MAX_POS], struct board *);
void tag_same_side (int [][MAX_POS][MAX_POS], struct board *);
void tag_same_angle (int [][MAX_POS][MAX_POS], struct board *);
void tag_same_cercle (int [][MAX_POS][MAX_POS], struct board *);
void write_over_approximation(int [][MAX_POS], int [][MAX_POS][MAX_POS], struct  board *);


/* PRINT CONSTRAINTS */
void aff_constraint(int, int, int);

#endif
