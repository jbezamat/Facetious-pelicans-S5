/*DESCRIPTION OF THE PROJECT ORGANIZATION*/

This project is divided in 4 folders :

DOC :
-distances.ods (file used in one of our tests)

RAPPORT :
-Rapport_Bezamat_Plages.pdf

SRC :
The differents files of our code :
-Makefile
-affect.c / affect.h (all definitions and functions relatives to the struct affect)
-board.c / board.h (all definitions and functions relatives to the struct board)
-constraint.c /constraint.h (functions using the struct board & affect and representing the concept of constraints)
-define.c / define.h (define variables of our code)
-functions.c / functions.h (functions not connected to any struct but usefull in others parts of the code)
-main.c
-solver.c / solver.h (first solver)
-z3solver.c / z3solver.h (second solver using z3)

The folder and the copy of the executable solver "z3"

TST :
-main_test.c
-test_function.c / test_function.h (all the tests of our functions)


/*HOW TO USE OUR PROJECT ? */

GAME :
First, you need to be in the folder "src" and write "make" to build the executable.

Now you have 3 possibilities with 2 options. We create a board of 4, 8 and 16 positions.
To play the game "Pelican Cove" on the board of 4, 8 or 16 :
You steel need to be in the folder "src" (or indicate the path) and write respectively in the console :
    "./main 4 P S" 	 
    "./main 8 P S"	 
    "./main 16 P S"	 
With :
     P=number of pelicans you want to place on the board (of course P must be inferior at the number of postions on the board)
     S=0 if you want to use the first solver or S=1 if you want to use the z3 solver.

The constraint affectation will be done automatically and randomly.

If you use the first solver you will have all the solutions, if they exist. Therefore, using the first solver with the board of 16 positions might take a (very) long time.
In the other hand with the z3 solver you will have only one solution, but if the first solution is not possible, you will have an other satisfying a maximum of constraints.

TESTS :
First, you need to be in the folder "src" and write "make test" to build the executable.
Then only write "./test" in the console and you will see the results of our tests.

CLEAR:
Write "make clear" to remove all "file".o in src/ and tst/
