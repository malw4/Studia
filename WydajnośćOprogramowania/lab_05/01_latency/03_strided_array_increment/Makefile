# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
#LOADER = gcc
LOADER = icc

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -lm

all: strided_array_increment run

strided_array_increment: strided_array_increment.o 
	$(LOADER) $(OPT) strided_array_increment.o -o strided_array_increment.exe $(LIB)

strided_array_increment.o: strided_array_increment.c
	$(CCOMP) -c $(OPT) strided_array_increment.c $(INC)


run:
	./strided_array_increment.exe 

clean:
	rm -f *.o strided_array_increment.exe
