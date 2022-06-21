# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
#LOADER = gcc
LOADER = icc

# opcje optymalizacji:
#OPT = -fast 
#OPT = -O3 -march=core-avx2 -fopenmp
OPT = -O3 -march=core-avx2 -qopenmp
#OPT = -g -openmp

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -lm

all: memory_scalability_scalar run_scalar memory_scalability_vector run_vector

memory_scalability_scalar: memory_scalability_scalar.o 
	$(LOADER) $(OPT) -no-vec memory_scalability_scalar.o -o memory_scalability_scalar.exe $(LIB)

memory_scalability_scalar.o: memory_scalability.c
	$(CCOMP) -c $(OPT) -no-vec memory_scalability.c $(INC) -o memory_scalability_scalar.o

memory_scalability_vector: memory_scalability_vector.o 
	$(LOADER) $(OPT) memory_scalability_vector.o -o memory_scalability_vector.exe $(LIB)

memory_scalability_vector.o: memory_scalability.c
	$(CCOMP) -c $(OPT) memory_scalability.c $(INC) -o memory_scalability_vector.o


run_scalar:
	./memory_scalability_scalar.exe 

run_vector:
	./memory_scalability_vector.exe

clean:
	rm -f *.o *~ *.exe
