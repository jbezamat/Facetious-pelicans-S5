#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

int test_distance(const struct board *,const struct board *);
int test_has_tag(const struct board *);
void print_test(int , char*);
void print_sub_test(int, char*);
int test_next_permutation();
int test_solver(struct board *, struct affect *, struct board * , struct affect *);
int test_z3solver(struct board*, struct affect *, struct board *, struct affect *);
#endif
