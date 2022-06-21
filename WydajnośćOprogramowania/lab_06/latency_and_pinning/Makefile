# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
#LOADER = gcc
LOADER = icc

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3 -lpthread

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack

all: random_pointer_chasing_mth run_mth

random_pointer_chasing_mth: random_pointer_chasing_mth.o 
	$(LOADER) $(OPT) random_pointer_chasing_mth.o -o random_pointer_chasing_mth.exe $(LIB)

random_pointer_chasing_mth.o: random_pointer_chasing_mth.c
	$(CCOMP) -c $(OPT) random_pointer_chasing_mth.c $(INC)


run_mth:
	./random_pointer_chasing_mth.exe 

clean:
	rm -f *.o
