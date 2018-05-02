#ifndef Z3SOLVER_H
#define Z3SOLVER_H

void declare_const(FILE *, struct board *, int);
void at_least_one_pos(FILE *, struct board *, int);
void at_max_one_pos(FILE *, struct board *, int);

//Functions to simplify the code of write_constraint function
void write_mono_constraint(FILE *, int , int , struct board *, int [][MAX_POS], int);
void write_mult_approx(FILE *, int , int, int , struct board *, int [][MAX_POS][MAX_POS], int);

void write_same_constraint(FILE *, int, int , struct board *, struct affect *, int [][MAX_POS], int [][MAX_POS][MAX_POS], int, int);
void write_opp_constraint(FILE *, int, int , struct board *, struct affect *, int [][MAX_POS], int [][MAX_POS][MAX_POS], int, int);

//Write the constraint n on the pelican p (depending of the board)
void write_constraint(FILE *, int, int, int, struct board *, struct affect *, int [][MAX_POS], int [][MAX_POS][MAX_POS], int, int);

//Function in case of the first solution is not possible
void other_solution(struct board *, struct affect *, int [][MAX_POS], int [][MAX_POS][MAX_POS], int, int [MAX_POS]);

/* FUNCTION SOLVER 
   Write the file.smt2 for z3*/
void z3_solver(struct board *, struct affect *, int, int [MAX_POS]);


int aff_res(int, struct board *, int [MAX_POS]);

#endif
