# Simple debugger in C++

Starts and traces a given program by reporting its system calls and handling its signals,
the bash script runs and checks the program results.

you can Run the program with:
```
make clean
./picodb <Executable program name>
```
also with the command ```./bash_script``` that uses 
```./picodb readfile < data.txt > OUTPUT”``` and data.txt containts the following commands for picodb(CLI):
```

t all
b off
r stdout output_read
r stdin input_read
go
r stdout output_fread
r stdin input_fread
go
quit
```

included Makefile:
```
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
```

