#include <stdlib.h>
#include <stdio.h>
#include "define.h"
#include "board.h"
#include "affect.h"
#include "constraint.h"
#include "z3solver.h"
#include "functions.h"
#include <string.h>

//Declare the boolean variables in the file.smt2
void declare_const(FILE *f, struct board *b, int n){
  int i;
  int j;
  
  for(i=1; i<=n; i++){
    for(j=0; j<=(num_positions(b)-1); j++){
      fprintf(f, "(declare-const p%d_c%d Bool)\n", i, j);
    }
  }

} 

//Check if there is at least one position for each pelican in the file.smt2
void at_least_one_pos(FILE *f, struct board *b, int n){
  int i;
  int j;

  fprintf(f, "(assert (and");
  for(i=1; i<=n; i++){
    fprintf(f, " (or");
    for(j=0; j<=(num_positions(b)-1); j++){
      fprintf(f, " p%d_c%d", i, j);
    }
    fprintf(f, ")");
  }
  fprintf(f,"))\n");

}

//Check if there is at max one position for each pelican in the file.smt2
void at_max_one_pos(FILE *f, struct board *b, int n){
  int i;
  int j;
  int k;
  
  for(j=0; j<=(num_positions(b)-1); j++){  
    fprintf(f, "(assert (and");
    for(i=1; i<=n; i++){  
      fprintf(f, " (implies p%d_c%d (and",i,j);
      for(k=1; k<=n; k++){
	if (k!=i)
	  fprintf(f, " (not p%d_c%d)",k, j);
      }
      fprintf(f, "))");
    }
    fprintf(f, "))\n");
  }
  
}

//Functions to simplify the code of write_constraint function
//Write mono-pelican constraint
void write_mono_approx(FILE *f, int index, int p, struct board *b, int t1[][MAX_POS], int cpt2){
  int i;
  
  if(cpt2==0)
    fprintf(f,"(assert");
  else  //Constraint n=9 (opposite constraint)
    fprintf(f,"(assert (not");
  
  fprintf(f, " (or");
  for (i=0; i<num_positions(b); i++){
    if (t1[index][i]==-1){
      break;
    }
    fprintf(f," p%d_c%d", p, t1[index][i]);
  }

  
  if(cpt2==0)
    fprintf(f, "))\n");
  else  //Constraint n=9 (opposite constraint)
    fprintf(f,")))\n");

}

//Write bi-pelican constraint
void write_mult_approx(FILE *f, int index, int p1, int p2, struct board *b, int t2[][MAX_POS][MAX_POS], int cpt2){
  int i=0;
  int k;

  
  if(cpt2==0)
    fprintf(f,"(assert");
  else  //Constraint n=9 (opposite constraint)
    fprintf(f,"(assert (not");
  
  fprintf(f, " (and");

  if (index==3) //Only for constraint "same_cercle" because the four first lines are empty
      i=4;
    
  while (i<num_positions(b)){
    
    if ((t2[index][i][0]==-1) )
      break;
      
    fprintf(f, " (implies p%d_c%d (or", p1, i);
    
    for (k=0; k<num_positions(b); k++){
      if (t2[index][i][k]==-1){
	break;
      }
      fprintf(f," p%d_c%d", p2, t2[index][i][k]);
    }
    fprintf(f, "))");
    i++;
  }

  if(cpt2==0)
    fprintf(f, "))\n");
  else  //Constraint n=9 (opposite constraint)
    fprintf(f,")))\n");
}

void write_same_constraint(FILE *f, int p1, int q, struct board *b, struct affect *a, int t1[][MAX_POS], int t2[][MAX_POS][MAX_POS], int cpt1, int cpt2){

  int n = recover_constraint(a,q);
  int p2 = recover_p2(a,q);
  cpt1++;
  write_constraint(f,n,p1,p2,b,a,t1,t2, cpt1,cpt2);
}

void write_opp_constraint(FILE *f, int p1, int q, struct board *b, struct affect *a, int t1[][MAX_POS], int t2[][MAX_POS][MAX_POS], int cpt1, int cpt2){

  int n = recover_constraint(a,q);
  int p2 = recover_p2(a,q);
  cpt2++;
  write_constraint(f,n,p1,p2,b,a,t1,t2, cpt1, cpt2);
}

//Write the constraint n on the pelican p (depending of the board)
void write_constraint(FILE *f, int n, int p1, int p2, struct board *b, struct affect *a, int t1[][MAX_POS], int t2[][MAX_POS][MAX_POS], int cpt1, int cpt2){

  
  switch(n){  
  case 1: //in_north
    write_mono_approx(f,1,p1,b,t1, cpt2);
    break;
  case 2: //in_south
    write_mono_approx(f,2,p1,b,t1, cpt2);
    break;
  case 3: //in_east
    write_mono_approx(f,3,p1,b,t1, cpt2);
    break;
  case 4: //in_west
    write_mono_approx(f,4,p1,b,t1,cpt2);
    break;
  case 5: //in_corner
    write_mono_approx(f,5,p1,b,t1, cpt2);
    break;
  case 6: //in_north_or_south
    write_mono_approx(f,6,p1,b,t1, cpt2);
    break;  
  case 7 : //in_north_and_corner
    write_mono_approx(f,7,p1,b,t1, cpt2);
    break;
  case 8:  //p1 wants the same constraint than p2
    if(cpt1>num_positions(b)) //Warning : In case of cycle : break
      break;
    write_same_constraint(f,p1,p2,b,a,t1,t2,cpt1, cpt2);
    break;
  case 9:  //p1 wants the opposite constraint than p2
    if(cpt2>num_positions(b)) //Warning : In case of cycle : break
      break;
    write_opp_constraint(f,p1,p2,b,a,t1,t2,cpt1, cpt2);
    break;
  case 10 : //in_front_of
    write_mult_approx(f,0,p1,p2,b,t2, cpt2);
    break;
    //Constraints for board 2 !
  case 11 : //on_same_side
    write_mult_approx(f,1,p1,p2,b,t2, cpt2);
    break;
  case 12 : //same_angle
    write_mult_approx(f,2,p1,p2,b,t2, cpt2);
    break;
  case 13 : //same_cercle
    write_mult_approx(f,3,p1,p2,b,t2, cpt2);
    break;
  case 14 : //in_cercle_1
    write_mono_approx(f,8,p1,b,t1, cpt2);
    break;
  case 15 : //in_cercle_2
    write_mono_approx(f,9,p1,b,t1, cpt2);
    break;
  case 16 : //in_cercle_3
    write_mono_approx(f,10,p1,b,t1, cpt2);
    break;
  }

}



//Function in case of the first solution is not possible
//Will looking for an other solution (satisfying a maximum number of constraints)
void other_solution(struct board *b, struct affect *a, int t1[][MAX_POS], int t2[][MAX_POS][MAX_POS], int num_pelicans, int resultats[MAX_POS]){

  int n=num_pelicans;
  int res=0;
  int cpt=0;
  int cond=1;
  int j;
  int k;
  //Counters used for cycles with constraints 8 & 9 (same and opposite constraint of a pelican)
  int cpt1=0;
  int cpt2=0;  
  //Initialisation of the board which contain the pelicans and their numbers
  int t[n];
  //Initialisation of the board we will use to know which constraint to delete (with next_permutation)
  int t01[n];
  int i;
  for (i=0; i<n; i++){
    t[i]=i+1;
    t01[i]=1; //1=write the constraint / 0=don't
  }
    
  
  //Double loop
  while(cpt<num_pelicans){ //stop condition :  no more constraint to delete
    while(cond){ //stop condition : end of permutation
    FILE *file ;
    file = fopen("file.smt2","w");
    
    declare_const(file, b,num_pelicans);
    at_least_one_pos(file, b,num_pelicans);
    at_max_one_pos(file, b,num_pelicans);
    
    //Counters used for cycles with constraints 8 & 9 (same and opposite constraint of a pelican)
    cpt1=0;
    cpt2=0;
      
    //For : Write the constraints 
    for (j=0; j<n; j++){
      if (t01[j]==1) //else t01=0 => deleted constraint
	write_constraint(file, recover_constraint(a,t[j]), t[j], recover_p2(a,t[j]), b, a, t1, t2,cpt1,cpt2);
    }
      
    fprintf(file, "(check-sat)\n");
    fprintf(file, "(get-model)\n");
    
    fclose(file);
    
    system("./z3 file.smt2 > out.txt");
    res = aff_res(num_pelicans,b,resultats);
   
    //If there is a solution : exit the first while !
    if (res==1)
      break; 
    
    cond=next_permutation(t01,n);

    }
    
    //If there is a solution : exit the secod (and last) while !
    if (res==1)
      break; 

    cond=1;
    //We recreate the table of number of constraints deleted in the right order
    for(k=0; k<=cpt; k++)
      t01[k]=0;
    for(k=cpt+1; k<n; k++)
      t01[k]=1;
    cpt++;
  }
  
  printf("This solution satisfies %d constraint(s).\n", n-cpt);
}


/* FUNCTION SOLVER 
   Write the file.smt2 for z3*/
void z3_solver(struct board *b, struct affect *a, int num_pelicans, int resultats[MAX_POS]){

  FILE *file ;
  file = fopen("file.smt2","w");

  declare_const(file, b,num_pelicans);
  at_least_one_pos(file, b,num_pelicans);
  at_max_one_pos(file, b,num_pelicans);
  
  //Over approximation needed to know the positions of each constraint :
  int t1[NUM_CONSTRAINTS_2][MAX_POS]; 
  int t2[NUM_CONSTRAINTS_2][MAX_POS][MAX_POS];
  //Initialisation of boards 
  int m,n,o;  
  for(m=0 ; m <NUM_CONSTRAINTS_2 ; m++){  
    for(n=0 ; n < MAX_POS ; n++){  
      t1[m][n]=-1; 
    }	
  }
  for (o=0 ; o <NUM_CONSTRAINTS_2; o++){ 
    for(m=0 ; m <MAX_POS ; m++){  
      for(n=0 ; n <MAX_POS ; n++){  
	t2[o][m][n]=-1; 
      }	
    }
  }

  write_over_approximation(t1,t2,b);

  //Counters used for cycles with constraints 8 & 9 (same and opposite constraint of a pelican)
  int cpt1=0;
  int cpt2=0;
  
  //Write the constraints of all pelicans in file.smt2
  int i;
  for (i=1; i<(num_pelicans+1); i++){
    write_constraint(file, recover_constraint(a,i), i, recover_p2(a,i), b, a, t1, t2,cpt1,cpt2);
    }

  fprintf(file, "(check-sat)\n");
  fprintf(file, "(get-model)\n");


  fclose(file);

  //Stock the z3 answer in the file out.txt
  system("./z3 file.smt2 > out.txt");
  int res = aff_res(num_pelicans,b,resultats);
 

  //Constraints maximisation if there is no available solution 
  if (res==0){
    printf("No possible solution.\nLooking for a solution which maximizes the number of satisfied constraints...\n");
    other_solution(b,a,t1,t2,num_pelicans, resultats);
    
    }
  
}





//Function which will stock in a table the possible solution (if there is one)
// and return an integer indicating if there is a solution or not
int aff_res(int n, struct board *b, int resultats[MAX_POS]){
  FILE *o ;
  o = fopen("out.txt","r");

  //resultas=table to stock the solution : index = positions / values of table = number of pelicans
  int k;
  for (k=0; k<num_positions(b); k++)
    resultats[k]=0; // initialisation of resultats : no pelicans placed yet (0=NO_COLOR)
  int pel;
  int posit;

  char line[100] = "" ; //char used to read the file
  char tmp[100]= "";
  char *pos=NULL ;
  int end=0;

  //There is a solution or not ?
  fgets(line, 100, o);
  
  if ( (strncmp(line,"unknown",7)==0) || (strncmp(line,"unsat",5)==0) ){
    return 0;
  
  }
  else{
    fgets(line, 100, o); 
 
    //If there is one :
    while (end<n){ //stop condition : all positions of pelicans have been stocked
      
      strcpy(tmp,fgets(line,100,o));
   
      //Stock the number of pelican and position 
      if  (strncmp(tmp,"  (define-fun ",14)==0){
	pos = strchr(tmp, 'p');
      }

      fgets(line, 100, o);
 
      //If it's a position of the model  
      if ( (strncmp(line,"    true)",9)==0) && (pos != NULL) ){

	//Several cases depending the number of pelican and position (if ther is a tens or only units)
	
	if (pos[2]=='_' && pos[5]==' '){
	  pel = pos[1] - '0'; // convert char to integer
	  posit = pos[4] - '0'; // convert char to integer
	  resultats[posit]=pel;
	  
	}
	else if (pos[2]!='_' && pos[6]==' ') {
	  pel = pos[1] - '0';
	  pel = pel*10 + (pos[2]-'0'); //because pos[1]=tens & pos[2]=unit
	  posit = pos[5] - '0';
	  resultats[posit]=pel;
	}
	 
	else if (pos[2]!='_' && pos[6]!=' '){
	  pel = pos[1] - '0';
	  pel = pel*10 + (pos[2]-'0'); //because pos[1]=tens & pos[2]=unit
	  posit = pos[5] - '0';
	  posit = posit*10 + (pos[6]-'0'); //because pos[5]=tens & pos[6]=unit
	  resultats[posit]=pel;
	}
	else if (pos[2]=='_' && pos[5]!=' ') {
	  pel = pos[1] - '0';
	  posit = pos[4] - '0';
	  posit = posit*10 + (pos[5]-'0'); //because pos[4]=tens & pos[5]=unit
	  resultats[posit]=pel;
	}
       
	end++;
      }
    }
    return 1;
   
  }
  
}
