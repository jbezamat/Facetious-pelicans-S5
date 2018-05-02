#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int factorielle(int n)
{
   if(n == 0)
      return 1;
   else
      return n*factorielle(n-1);
}

void print_tab(int *t,int n){
  int i;
  for(i=0;i<n;i++){
    printf("%3d ",t[i]);
  }
  printf("\n");
}

//Function which give an random integer in [0,c[
int rand_c(int c){
  srand(clock());
  return rand()%c;
}

//Give the next permutation of an integer table
int next_permutation(int *tab, int l){
  //Find longest non-increasing suffix
  int i = l-1; //l=lenght of tab
  
  while( (i>0) && tab[i-1]>=tab[i])
    i--;
  //Now i is the head index of the suffix

  //Are we at the last permutation already ?
  if (i <= 0)
    return 0;

  //Let tab[i-1] be the pivot
  //Find rightmost element that exceeds the pivot
  int j = l-1;
  while (tab[j]<=tab[i-1])
    j--;
  //Now the value tab[j] will become the new pivot
  //Assertion: j>=i

  //Swap the pivot with j
  int tmp = tab[i-1];
  tab[i-1]=tab[j];
  tab[j]=tmp;

  //Reverse the suffix
  j=l-1;
  while (i<j) {
    tmp = tab[i];
    tab[i]=tab[j];
    tab[j]=tmp;
    i++;
    j--;
  }

  //Succesfully computed the next permutation
  return 1;

}
