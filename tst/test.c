#include <stdio.h>
#include <stdlib.h>
#define MAX_POS 10

#define NORMAL "\033[00m"
#define RED "\033[00;31m"
#define GREEN "\033[1;32m"

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

void print_tab(int *t,int n){
  int i;
  for(i=0;i<n;i++){
    printf("%3d ",t[i]);
  }
  printf("\n");
}

int main(){
  
  int num_positions=3;
  int tab[3]={1,2,3};
  int i;
  for(i=0;i<10;i++){
     printf("return : %d\n",next_permutation(tab,num_positions));
     print_tab(tab,3);
  }
printf("Salut " RED "EN rouge " NORMAL " normal" GREEN "GREEN" NORMAL);
 
  return EXIT_SUCCESS;
}
