SHELL = /bin/sh

# C compiler
# kompilator C
CCOMP = gcc

# linker
# konsolidator
LINKER = gcc

# options:
# opcje:

# version for debugging
# wersja do debugowania
# OPT = -g -DDEBUG

# optimized version
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# location for header files
# katalog z plikami naglowkowymi
INC = -I../utd_time_unix

# locations for libraries and options for linking libraries
# katalogi bibliotek i opcje dołączania bibliotek
LIB = -L../utd_time_unix -lm

# dependencies and commands 
# zaleznosci i komendy
time_test: time_test.o ../utd_time_unix/uts_time.o
	$(LINKER) $(OPT) time_test.o ../utd_time_unix/uts_time.o -o time_test $(LIB)

time_test.o: time_test.c ../utd_time_unix/uth_time.h
	$(CCOMP) -c $(OPT) time_test.c $(INC)

../utd_time_unix/uts_time.o: ../utd_time_unix/uts_time.c ../utd_time_unix/uth_time.h
	$(CCOMP) -c $(OPT)  ../utd_time_unix/uts_time.c -o ../utd_time_unix/uts_time.o $(INC)

clean:
	rm -f *.o
