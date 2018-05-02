 #include <stdio.h>
#include "../src/define.h"
#include "../src/functions.h"
#include "../src/board.h"
#include "../src/affect.h"
#include "../src/constraint.h"
#include "../src/solver.h"
#include "../src/z3solver.h"
#include "test_function.h"

#define NORMAL "\033[0m"
#define RED "\033[00;31m"
#define GREEN "\033[1;32m"

void print_test(int count_error, char *name){
  /*print resultat of the test*/
  if (count_error==0){
    printf("*Test %s:" GREEN " OK\n\n" NORMAL ,name);
  }
  else{
    printf("*Test %s:" RED " FAILED" NORMAL ,name);
    printf("\t(%d error)\n\n",count_error);
  }
}

void print_sub_test(int error, char *name){
  /*print  resultat of the subtest*/
  if (error==0){
    printf("\t\t\t -Sub test %s:" GREEN " OK\n" NORMAL ,name);
  }
  else{
    printf("\t\t\t -Sub test %s:" RED " FAILED\n" NORMAL ,name);
  }
}

int test_distance(const struct board *b3, const struct board *b2){
  /*return the number of error of the test*/
  int i;
  int j;
  int count_error=0;
  int error=0;
  printf("Test distance: \n");

  /* TEST 1 */
  //Test sur le board 3
  int len_tab=16;
  int distances[16][16]={{0,1,2,1,1,2,2,1,1,2,3,2,2,3,3,2},\
			    {4,0,1,2,1,1,2,2,2,1,2,3,2,2,3,3},\
			    {4,4,0,1,2,1,1,2,3,2,1,2,3,2,2,3},\
			    {4,4,4,0,2,2,1,1,2,3,2,1,3,3,2,2},\
			    {4,4,4,4,0,2,3,2,1,1,3,3,1,2,3,2},\
			    {4,4,4,4,4,0,2,3,3,1,1,3,2,1,2,3},\
			    {4,4,4,4,4,4,0,2,3,3,1,1,3,2,1,2},\
			    {4,4,4,4,4,4,4,0,1,3,3,1,2,3,2,1},\
			    {4,4,4,4,4,4,4,4,0,2,3,2,1,2,2,1},\
			    {4,4,4,4,4,4,4,4,4,0,2,3,1,1,2,2},\
			    {4,4,4,4,4,4,4,4,4,4,0,2,2,1,1,2},\
			    {4,4,4,4,4,4,4,4,4,4,4,0,2,2,1,1},\
			    {4,4,4,4,4,4,4,4,4,4,4,4,0,1,2,1},\
			    {4,4,4,4,4,4,4,4,4,4,4,4,4,0,1,2},\
			    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,1},\
			    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0}}; //4 = Error 
  
  for(i=0;i<len_tab;i++){
    for(j=i+1;j<len_tab;j++){//we compare only the right side of distances
      if(distances[i][j]!=distance(b3,i,j)){
	count_error++;
        error=1;
      }
    }
  }
  
  print_sub_test(error,"1  ");
  error=0;

  /* TEST 2 */
  //Test sur le board 2
  len_tab=7;
  int distances2[8][8]={{0,1,2,3,4,3,2,1},\
		       {5,0,1,2,3,4,3,2},\
			{5,5,0,1,2,3,4,3},\
		       {5,5,5,0,1,2,3,4},\
		       {5,5,5,5,0,1,2,3},\
		       {5,5,5,5,5,0,1,2},\
			{5,5,5,5,5,5,0,1}}; //5 = Error 
  
  for(i=0;i<len_tab;i++){
    for(j=i+1;j<len_tab;j++){
      if(distances2[i][j]!=distance(b2,i,j)){
	count_error++;
        error=1;
      }
    }
  }
  
  print_sub_test(error,"2  ");
  error=0;
  
  return count_error;
}

int test_has_tag(const struct board *b){
  /*return the number of error of the test*/
  int count_error=0;
  int i;
  for(i=0;i<4;i++){
    if(!has_tag(b,i,5))
      count_error++;
  }
  for(i=4;i<7;i++){
    if(!has_tag(b,i,8))
      count_error++;
  }
  for(i=8;i<12;i++){
    if(!has_tag(b,i,7))
      count_error++;
  }
  for(i=12;i<15;i++){
    if(!has_tag(b,i,6))
      count_error++;
  }
  return count_error++;
}


int test_next_permutation(){
  /*return the number of error of the test*/
  printf("Test next_permutation: \n");
  int count_error=0;
  int error=0;
  
  /* TEST 1.1 */
  //5 positions

  int tab1[5]={0,1,2,3,4};
  int next_tab1[5]={0,1,2,4,3};//Normally after next_permutation [0,1,2,3,4] become [0,1,2,4,3]
  int l=5;
  next_permutation(tab1,l);
  
  int i;  
  for(i=0;i<l;i++){
    if(tab1[i]!=next_tab1[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"1.1");
  
  error=0;
  
  /* TEST 1.2 */
  //next_tab1=[0,1,3,2,4]
  next_tab1[2]=3;
  next_tab1[3]=2;
  next_tab1[4]=4;
  next_permutation(tab1,l);  

  for(i=0;i<l;i++){
    if(tab1[i]!=next_tab1[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"1.2");
  
  error=0;
  
    /* TEST 1.3 */
  //next_tab1=[0,1,3,4,2]
  next_tab1[3]=4;
  next_tab1[4]=2;
  next_permutation(tab1,l);
  
  for(i=0;i<l;i++){
    if(tab1[i]!=next_tab1[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"1.3");
  
  error=0;

  /* TEST 2.1 */
  //all permutation of {1,2,3}
  int tab2[3]={1,2,3};
  int next_tab2[3]={1,3,2};
  l=3;
  next_permutation(tab2,l);
 
  for(i=0;i<l;i++){
    if(tab2[i]!=next_tab2[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"2.1");
  
  error=0;
  
  /* TEST 2.2 */
  //next_tab2=[2,1,3]
  next_tab2[0]=2;
  next_tab2[1]=1;
  next_tab2[2]=3;
  l=3;
  next_permutation(tab2,l);

  for(i=0;i<l;i++){
    if(tab2[i]!=next_tab2[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"2.2");
  
  error=0;

  /* TEST 2.3 */
  //next_tab2=[2,3,1]
  next_tab2[1]=3;
  next_tab2[2]=1;
  l=3;
  next_permutation(tab2,l);

  for(i=0;i<l;i++){
    if(tab2[i]!=next_tab2[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"2.3");
  
  error=0;
  
  /* TEST 2.4 */
  //next_tab2=[3,1,2]
  next_tab2[0]=3;
  next_tab2[1]=1;
  next_tab2[2]=2;
  l=3;
  next_permutation(tab2,l);

  for(i=0;i<l;i++){
    if(tab2[i]!=next_tab2[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"2.4");
  
  error=0;

  /* TEST 2.5 */
  //next_tab2=[3,2,1]
  next_tab2[0]=3;
  next_tab2[1]=2;
  next_tab2[2]=1;
  l=3;
  next_permutation(tab2,l);

  for(i=0;i<l;i++){
    if(tab2[i]!=next_tab2[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"2.5");
  
  error=0;
  
  /* TEST 3 */
  //tab with 0 and l<len(tab)
  int tab3[7]={1,2,3,0,0,0,0};
  int next_tab3[7]={1,3,2,0,0,0,0};
  l=3;
  next_permutation(tab3,l);
 
  for(i=0;i<l;i++){
    if(tab3[i]!=next_tab3[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"3  ");
  
  error=0;

  /* TEST 4 */
  int tab4[7]={0,1,2,3,0,0,0};
  int next_tab4[7]={0,1,3,2,0,0,0};
  l=4;
  next_permutation(tab4,l);
 
  for(i=0;i<l;i++){
    if(tab4[i]!=next_tab4[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"4  ");
  
  error=0;
  
  /* TEST 5.1 */
  int tab5[3]={0,0,1};
  int next_tab5[3]={0,1,0};
  l=3;
  next_permutation(tab5,l);
 
  for(i=0;i<l;i++){
    if(tab5[i]!=next_tab5[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"5.1");
  
  error=0;
 
  /* TEST 5.2 */
  next_tab5[0]=1;
  next_tab5[1]=0;
  next_permutation(tab5,l);
 
  for(i=0;i<l;i++){
    if(tab5[i]!=next_tab5[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"5.1");
  
  error=0;
 
  return count_error;
}

int test_solver(struct board *b,struct affect *a,struct board *b2,struct affect *a2){
   /*return the number of error of the test*/
  //print:
  printf("Test solver: \n");
  int count_error=0;
  int error=0;
  
  /* TEST 1.1 */
  //We add constraints to pelicans:
  struct constraint c1={2,1,0};
  a->tab_constraints[0]=c1;
    
  struct constraint c2={1,2,0};
  a->tab_constraints[1]=c2;

  struct constraint c3={4,3,0};
  a->tab_constraints[2]=c3;

  struct constraint c4={3,4,0};
  a->tab_constraints[3]=c4;

  
  //solver
  int resultats[24][MAX_POS]={{0}}; //4!=24 to save all solution on a 4 position-board
  int expect_result[24][4]={{2,3,1,4}}; //4! solutions
  solver(b,a,resultats);
  
  int i;  
  for(i=0;i<4;i++){
    if(resultats[0][i]!=expect_result[0][i]){
      count_error++;
      error=1;
      break;
    }
  }

  print_sub_test(error,"1.1");
  error=0;
  
  /* TEST 1.2 */
  //We delete the constraint of pelican 4:
  
  c4.n=0;
  a->tab_constraints[3]=c4;
  //solver
  solver(b,a,resultats);
  
  for(i=0;i<4;i++){
    if(resultats[0][i]!=expect_result[0][i]){
      count_error++;
      error=1;
      break;
    }
  }

  print_sub_test(error,"1.2");
  error=0;
  
  /* TEST 1.3 */
  //We delete the constraint of pelican 3:
  
  c3.n=0;
  a->tab_constraints[2]=c3;

  
  //solver
  solver(b,a,resultats);
  expect_result[1][0]=2;
  expect_result[1][1]=4;
  expect_result[1][2]=1;
  expect_result[1][3]=3;

  int j;
  int end_for=0;
  for(j=0;j<24;j++){
    for(i=0;i<4;i++){
       if(resultats[j][i]!=expect_result[j][i]){
	count_error++;
	error=1;
	end_for=1;
	break;
      }
    }
    if(end_for==1)
      break;
  }

  print_sub_test(error,"1.3");
  error=0;
  
   /* TEST 1.4 */
  //We delete the constraint of pelican 2:
  
  c2.n=0;
  a->tab_constraints[1]=c2;

  
  //solver
  solver(b,a,resultats);
  
  expect_result[2][0]=3;
  expect_result[2][1]=2;
  expect_result[2][2]=1;
  expect_result[2][3]=4;

  expect_result[3][0]=3;
  expect_result[3][1]=4;
  expect_result[3][2]=1;
  expect_result[3][3]=2;

  expect_result[4][0]=4;
  expect_result[4][1]=2;
  expect_result[4][2]=1;
  expect_result[4][3]=3;

  expect_result[5][0]=4;
  expect_result[5][1]=3;
  expect_result[5][2]=1;
  expect_result[5][3]=2;

  
  end_for=0;
  for(j=0;j<24;j++){
    for(i=0;i<4;i++){
       if(resultats[j][i]!=expect_result[j][i]){
	count_error++;
	error=1;
	end_for=1;
	break;
      }
    }
    if(end_for==1)
      break;
  }

  print_sub_test(error,"1.4");
  error=0;
  
    /* TEST 1.5 */
  //We delete the constraint of pelican 3:
  
  c4.n=0;
  a->tab_constraints[0]=c4;

  
  //solver
  solver(b,a,resultats);
  expect_result[0][0]=1;
  expect_result[0][1]=2;
  expect_result[0][2]=3;
  expect_result[0][3]=4;

  end_for=0;
  for(j=0;j<24;j++){
    for(i=0;i<4;i++){
      if(resultats[j][i]!=expect_result[0][i]){
	count_error++;
	error=1;
	end_for=1;
	break;
      }
    }
    if(end_for==1)
      break;
    next_permutation(expect_result[0],4);
  }

  print_sub_test(error,"1.5");
  error=0;

  /* TEST 2.1 */
  //new constraints

  c1.n=6; //north or south
  c2.n=7; //north and corner
  c3.n=10; //in front of
  c3.p2=4;
  c4.n=4; //East

  a->tab_constraints[0]=c1;
  a->tab_constraints[1]=c2;
  a->tab_constraints[2]=c3;
  a->tab_constraints[3]=c4;
  
  //solver
  solver(b,a,resultats);
  expect_result[0][0]=2;
  expect_result[0][1]=4;
  expect_result[0][2]=1;
  expect_result[0][3]=3;

  end_for=0;
  for(j=0;j<1;j++){
    for(i=0;i<4;i++){
      if(resultats[j][i]!=expect_result[j][i]){
	count_error++;
	error=1;
	end_for=1;
	break;
      }
    }
    if(end_for==1)
      break;
  }

  print_sub_test(error,"2.1");
  error=0;
  
  /* TEST 2.2 */
  //new constraints

  c1.n=3; //West
  c2.n=9; //opposite constraint than 1
  c2.p2=1;
  c3.n=6; //North or south
  c4.n=8; //same constraint than 3
  c4.p2=3;

  a->tab_constraints[0]=c1;
  a->tab_constraints[1]=c2;
  a->tab_constraints[2]=c3;
  a->tab_constraints[3]=c4;
  
  //solver
  solver(b,a,resultats);
  expect_result[0][0]=3;
  expect_result[0][1]=2;
  expect_result[0][2]=4;
  expect_result[0][3]=1;

  expect_result[1][0]=4;
  expect_result[1][1]=2;
  expect_result[1][2]=3;
  expect_result[1][3]=1;

  end_for=0;
  for(j=0;j<2;j++){
    for(i=0;i<4;i++){
      if(resultats[j][i]!=expect_result[j][i]){
	count_error++;
	error=1;
	end_for=1;
	break;
      }
    }
    if(end_for==1)
      break;
  }

  print_sub_test(error,"2.2");
  error=0;
  
  /* TEST 3.1 */
  //Board 3
  
  int resultats2[40320][MAX_POS]={{0}}; //8!=40320 to save all solution on a 8 position-board
  int expect_result2[40320][8]={{5,7,1,4,8,6,2,3},{5,7,1,4,8,6,3,2},{5,7,1,8,4,6,2,3},{5,7,1,8,4,6,3,2},\
				{5,7,4,1,8,6,2,3},{5,7,4,1,8,6,3,2},{5,7,4,8,1,6,2,3},{5,7,4,8,1,6,3,2},\
				{5,7,8,1,4,6,2,3},{5,7,8,1,4,6,3,2},{5,7,8,4,1,6,2,3},{5,7,8,4,1,6,3,2},\
				{7,5,1,4,8,6,2,3},{7,5,1,4,8,6,3,2},{7,5,1,8,4,6,2,3},{7,5,1,8,4,6,3,2},\
				{7,5,4,1,8,6,2,3},{7,5,4,1,8,6,3,2},{7,5,4,8,1,6,2,3},{7,5,4,8,1,6,3,2},\
				{7,5,8,1,4,6,2,3},{7,5,8,1,4,6,3,2},{7,5,8,4,1,6,2,3},{7,5,8,4,1,6,3,2}}; //8! solutions
 
  c1.n=4;
  a2->tab_constraints[0]=c1;
  c2.n=3;
  a2->tab_constraints[1]=c2;
  c3.n=8;
  c3.p2=2;
  a2->tab_constraints[2]=c3;
  c4.n=11;
  c4.p2=1;
  a2->tab_constraints[3]=c4;
  
  struct constraint c5={1,5,0};
  a2->tab_constraints[4]=c5;
    
  struct constraint c6={10,6,5};
  a2->tab_constraints[5]=c6;

  struct constraint c7={10,7,6};
  a2->tab_constraints[6]=c7;

  struct constraint c8={4,8,0};
  a2->tab_constraints[7]=c8;
   
  //solver
  solver(b2,a2,resultats2);
  
  end_for=0;
  for(j=0;j<24;j++){
    for(i=0;i<8;i++){
      if(resultats2[j][i]!=expect_result2[j][i]){
	count_error++;
	error=1;
	end_for=1;
	break;
      }
    }
    if(end_for==1)
      break;
  }

  print_sub_test(error,"3.1");
  error=0;
 

  return count_error;
}

int test_z3solver(struct board *b,struct affect *a,struct board *b2,struct affect *a2){
  /*return the number of error of the test*/ 
  //print:
  printf("Test z3solver: \n");
  int count_error=0;
  int error=0;
  
  /* TEST 1.1 */
  //We add constraints to pelicans:
  struct constraint c1={2,1,0};
  a->tab_constraints[0]=c1;
    
  struct constraint c2={1,2,0};
  a->tab_constraints[1]=c2;

  struct constraint c3={4,3,0};
  a->tab_constraints[2]=c3;

  struct constraint c4={3,4,0};
  a->tab_constraints[3]=c4;

  
  //solver
  int resultats[MAX_POS]={0};
  int expect_result[24][4]={{2,3,1,4}}; //4! solutions max
  z3_solver(b,a,a->num_pelicans,resultats);
  
  int i;  
  for(i=0;i<4;i++){
    if(resultats[i]!=expect_result[0][i]){
      error=1;
      break;
    }
  }
  if(error==1)
    count_error++;

  print_sub_test(error,"1.1");
  error=0;
  
  /* TEST 1.2 */
  //We delete the constraint of pelican 4:
  
  c4.n=0;
  a->tab_constraints[3]=c4;
  //solver
  z3_solver(b,a,a->num_pelicans,resultats);
  
  for(i=0;i<4;i++){
    if(resultats[i]!=expect_result[0][i]){
      error=1;
      break;
    }
  }
  if(error==1)
    count_error++;

  print_sub_test(error,"1.2");
  error=0;
  
  /* TEST 1.3 */
  //We delete the constraint of pelican 3:
  
  c3.n=0;
  a->tab_constraints[2]=c3;

  
  //solver
  z3_solver(b,a,a->num_pelicans,resultats);
  expect_result[1][0]=2;
  expect_result[1][1]=4;
  expect_result[1][2]=1;
  expect_result[1][3]=3;

  int j;
  int counter=0;
  //we compare all possible solution (expect_result) with the solution return by z3_solver
  for(j=0;j<24;j++){
    for(i=0;i<4;i++){
      if(resultats[i]!=expect_result[j][i]){
	error=1;
	counter=0;
	break;
      }
      else{
	counter++;
      }
    }
    if(counter==4){//if one of z3 solutions is the same than expect solution 
      error=0;
      break;
    }
    counter=0;
  }
  if(error==1)
    count_error++;

  print_sub_test(error,"1.3");
  error=0;
  
   /* TEST 1.4 */
  //We delete the constraint of pelican 2:
  
  c2.n=0;
  a->tab_constraints[1]=c2;

  
  //solver
  z3_solver(b,a,a->num_pelicans,resultats);
  
  expect_result[2][0]=3;
  expect_result[2][1]=2;
  expect_result[2][2]=1;
  expect_result[2][3]=4;

  expect_result[3][0]=3;
  expect_result[3][1]=4;
  expect_result[3][2]=1;
  expect_result[3][3]=2;

  expect_result[4][0]=4;
  expect_result[4][1]=2;
  expect_result[4][2]=1;
  expect_result[4][3]=3;

  expect_result[5][0]=4;
  expect_result[5][1]=3;
  expect_result[5][2]=1;
  expect_result[5][3]=2;

  counter=0;

  for(j=0;j<24;j++){
    for(i=0;i<4;i++){
      if(resultats[i]!=expect_result[j][i]){
	error=1;
	counter=0;
	break;
      }
      else{
	counter++;
      }
    }
    if(counter==4){//if one of z3 solutions is the same than expect solution 
      error=0;
      break;
    }
    counter=0;
  }
  if(error==1)
    count_error++;
  
  print_sub_test(error,"1.4");
  error=0;
  
    /* TEST 1.5 */
  //We delete the constraint of pelican 3:
  
  c4.n=0;
  a->tab_constraints[0]=c4;

  
  //solver
  z3_solver(b,a,a->num_pelicans,resultats);
  expect_result[0][0]=1;
  expect_result[0][1]=2;
  expect_result[0][2]=3;
  expect_result[0][3]=4;

  counter=0;
  for(j=0;j<24;j++){
    for(i=0;i<4;i++){
      if(resultats[i]!=expect_result[0][i]){
	error=1;
	counter=0;
	break;
      }
      else{ 
	counter++;
      }
    }
    next_permutation(expect_result[0],4); //All permutation is a solution
    if(counter==4){//if one of z3 solutions is the same than expect solution 
      error=0;
      break; 
    }
    counter=0;
  }
  if(error==1)
    count_error++;

  print_sub_test(error,"1.5");
  error=0;

  /* TEST 2.1 */
  //new constraints

  c1.n=6; //north or south
  c2.n=7; //north and corner
  c3.n=10; //in front of
  c3.p2=4;
  c4.n=4; //East

  a->tab_constraints[0]=c1;
  a->tab_constraints[1]=c2;
  a->tab_constraints[2]=c3;
  a->tab_constraints[3]=c4;
  
  //solver
  z3_solver(b,a,a->num_pelicans,resultats);
  expect_result[0][0]=2;
  expect_result[0][1]=4;
  expect_result[0][2]=1;
  expect_result[0][3]=3;

  
  for(j=0;j<1;j++){
    for(i=0;i<4;i++){
      if(resultats[i]!=expect_result[j][i]){
	error=1;
	counter=0;
	break;
      }
      else{
	counter++;
      }
    }
  
    if(counter==4){//if one of z3 solutions is the same than expect solution 
      error=0;
      break;
    }
    counter=0;
  }
  if(error==1)
    count_error++;
  
  /* TEST 2.2 */
  //new constraints

  c1.n=3; //West
  c2.n=9; //opposite constraint than 1
  c2.p2=1;
  c3.n=6; //North or south
  c4.n=8; //same constraint than 3
  c4.p2=3;

  a->tab_constraints[0]=c1;
  a->tab_constraints[1]=c2;
  a->tab_constraints[2]=c3;
  a->tab_constraints[3]=c4;
  
  //solver
  z3_solver(b,a,a->num_pelicans,resultats);
  expect_result[0][0]=3;
  expect_result[0][1]=2;
  expect_result[0][2]=4;
  expect_result[0][3]=1;

  expect_result[1][0]=4;
  expect_result[1][1]=2;
  expect_result[1][2]=3;
  expect_result[1][3]=1;

  counter=0;

  for(j=0;j<2;j++){
    for(i=0;i<4;i++){
      if(resultats[i]!=expect_result[j][i]){
	error=1;
	counter=0;
	break;
      }
      else{
	counter++;
      }
    }
    if(counter==4){//if one of z3 solutions is the same than expect solution 
      error=0;
      break;
    }
    counter=0;
  }
  if(error==1)
    count_error++;
  print_sub_test(error,"2.2");
  error=0;
  
  /* TEST 3.1 */
  //Board 3
  
  int resultats2[MAX_POS]={0}; //8!=40320 to save all solution on a 8 position-board
  int expect_result2[40320][8]={{5,7,1,4,8,6,2,3},{5,7,1,4,8,6,3,2},{5,7,1,8,4,6,2,3},{5,7,1,8,4,6,3,2},\
				{5,7,4,1,8,6,2,3},{5,7,4,1,8,6,3,2},{5,7,4,8,1,6,2,3},{5,7,4,8,1,6,3,2},\
				{5,7,8,1,4,6,2,3},{5,7,8,1,4,6,3,2},{5,7,8,4,1,6,2,3},{5,7,8,4,1,6,3,2},\
				{7,5,1,4,8,6,2,3},{7,5,1,4,8,6,3,2},{7,5,1,8,4,6,2,3},{7,5,1,8,4,6,3,2},\
				{7,5,4,1,8,6,2,3},{7,5,4,1,8,6,3,2},{7,5,4,8,1,6,2,3},{7,5,4,8,1,6,3,2},\
				{7,5,8,1,4,6,2,3},{7,5,8,1,4,6,3,2},{7,5,8,4,1,6,2,3},{7,5,8,4,1,6,3,2}}; //8! solutions
 
  c1.n=4;
  a2->tab_constraints[0]=c1;
  c2.n=3;
  a2->tab_constraints[1]=c2;
  c3.n=8;
  c3.p2=2;
  a2->tab_constraints[2]=c3;
  c4.n=11;
  c4.p2=1;
  a2->tab_constraints[3]=c4;
  
  struct constraint c5={1,5,0};
  a2->tab_constraints[4]=c5;
    
  struct constraint c6={10,6,5};
  a2->tab_constraints[5]=c6;

  struct constraint c7={10,7,6};
  a2->tab_constraints[6]=c7;

  struct constraint c8={4,8,0};
  a2->tab_constraints[7]=c8;
   
  //solver
  z3_solver(b2,a2,a2->num_pelicans,resultats2);

  counter=0;
  for(j=0;j<24;j++){
    for(i=0;i<8;i++){
      if(resultats2[i]!=expect_result2[j][i]){
	error=1;
	counter=0;
	break;
      }
      else{
	counter++;
      }
    }
    if(counter==8){//if one of z3 solutions is the same than expect solution 
      error=0;
      break;
    }
    counter=0;
  }
  if(error==1)
    count_error++;
  
  print_sub_test(error,"3.1");

  return count_error;
}
