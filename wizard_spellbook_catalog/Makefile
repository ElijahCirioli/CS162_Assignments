CC = g++ -std=c++11
exe_file = catalog
$(exe_file): wizard_catalog.o prog.o
	$(CC)  wizard_catalog.o prog.o -o $(exe_file)
wizard_catalog.o:  wizard_catalog.cpp
	$(CC) -c  wizard_catalog.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp
clean:
	rm -f  *.o  *.out $(exe_file)