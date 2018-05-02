#include <stdio.h>
#include "../src/define.h"
#include "../src/functions.h"
#include "../src/board.h"
#include "test_function.h"

#define NORMAL "\033[0m"
#define RED "\033[00;31m"
#define GREEN "\033[1;32m"

void print_test(int count_error, char *name){
  if (count_error==0){
    printf("Test %s:" GREEN " OK\n" NORMAL ,name);
  }
  else{
    printf("Test %s:" RED " FAILED" NORMAL ,name);
    printf("\t(%d error)\n",count_error);
  }
}

void print_sub_test(int error, char *name){
  if (error==0){
    printf("\t\t\t -Sub test %s:" GREEN " OK\n" NORMAL ,name);
  }
  else{
    printf("\t\t\t -Sub test %s:" RED " FAILED\n" NORMAL ,name);
  }
}

int test_distance(const struct board *b){
  int i;
  int j;
  int count_error=0;
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
    for(j=i+1;j<len_tab;j++){
      if(distances[i][j]!=distance(b,i,j))
	count_error++;
    }
  }
  return count_error;
}

int test_has_tag(const struct board *b){
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
  printf("Test next_permutation: \n");
  int count_error=0;
  int error=0;

  int tab[5]={0,1,2,3,4};
  int next_tab[5]={1,1,2,4,3};
  int l=5;
  next_permutation(tab,l);
  
  int i;  
  for(i=0;i<l;i++){
    if(tab[i]!=next_tab[i]){
      count_error++;
      error=1;
      break;
    }
  }
  print_sub_test(error,"1");
 
  return count_error;
}
