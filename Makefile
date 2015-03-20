CC = g++
all :	picodb 
picodb : main.o functions.o CLI_functions.o header.h
	$(CC) -o picodb main.o functions.o CLI_functions.o
	
main.o : main.cpp header.h
	$(CC) -c main.cpp
	
functions.o : functions.cpp header.h
	$(CC) -c functions.cpp 

CLI_functions.o : CLI_functions.cpp header.h
	$(CC) -c CLI_functions.cpp 	

clean :	
	rm -f picodb main.o functions.o CLI_functions.o OUTPUT output_read output_fread

	
