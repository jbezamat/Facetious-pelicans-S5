CFLAGS= -Wall -std=c99

main: define.o board.o functions.o affect.o constraint.o solver.o z3solver.o main.o
	gcc $(CFLAGS) define.o board.o main.o functions.o affect.o constraint.o solver.o z3solver.o -o main

test: define.o functions.o board.o affect.o constraint.o solver.o z3solver.o ../tst/test_function.o ../tst/main_test.o
	gcc $(CFLAGS) define.o functions.o board.o affect.o constraint.o solver.o z3solver.o ../tst/test_function.o ../tst/main_test.o -o test

define.o: define.c define.h
	gcc $(CFLAGS) -c define.c

board.o: board.c board.h
	gcc $(CFLAGS) -c board.c

functions.o: functions.c functions.h
	gcc $(CFLAGS) -c functions.c

affect.o: affect.c affect.h
	gcc $(CFLAGS) -c affect.c

constraint.o: constraint.c constraint.h
	gcc $(CFLAGS) -c constraint.c

solver.o: solver.c solver.h
	gcc $(CFLAGS) -c solver.c

z3solver.o: z3solver.c z3solver.h
	gcc $(CFLAGS) -c z3solver.c

../tst/test_function.o: ../tst/test_function.c ../tst/test_function.h
	gcc $(CFLAGS) -c ../tst/test_function.c -o ../tst/test_function.o

../tst/main_test.o: define.h board.h functions.h ../tst/main_test.c
	gcc $(CFLAGS) -c ../tst/main_test.c -o ../tst/main_test.o

main.o: main.c define.h board.h functions.h affect.h constraint.h solver.h z3solver.h 
	gcc $(CFLAGS) -c main.c

ex:
	./main 

clear:
	rm -f *.o
	rm -f ../tst/*.o
