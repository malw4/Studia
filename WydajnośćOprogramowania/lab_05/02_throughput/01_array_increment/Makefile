# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
#LOADER = gcc
LOADER = icc

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3 -march=core-avx2

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -lm

all: array_increment_scalar run_scalar array_increment_vector run_vector

array_increment_scalar: array_increment_scalar.o 
	$(LOADER) $(OPT) -no-vec array_increment_scalar.o -o array_increment_scalar.exe $(LIB)

array_increment_scalar.o: array_increment.c
	$(CCOMP) -c $(OPT) -no-vec array_increment.c $(INC) -o array_increment_scalar.o

array_increment_vector: array_increment_vector.o 
	$(LOADER) $(OPT) array_increment_vector.o -o array_increment_vector.exe $(LIB)

array_increment_vector.o: array_increment.c
	$(CCOMP) -c $(OPT) array_increment.c $(INC) -o array_increment_vector.o


run_scalar:
	./array_increment_scalar.exe 

run_vector:
	./array_increment_vector.exe

clean:
	rm -f *.o array_increment_scalar.exe array_increment_vector.exe
