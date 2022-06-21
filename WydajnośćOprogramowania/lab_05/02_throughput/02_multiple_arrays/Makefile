# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
#LOADER = gcc
LOADER = icc

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3 -march=core-avx2

PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/
INC = -I$(PAPI_HOME)

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a -L. -lpapi_driver

all: multiple_arrays_scalar run_scalar multiple_arrays_vector run_vector

multiple_arrays_scalar: multiple_arrays_scalar.o papi_set_user_events.o
	$(LOADER) $(OPT) -no-vec multiple_arrays_scalar.o papi_set_user_events.o -o multiple_arrays_scalar.exe $(LIB)

multiple_arrays_scalar.o: multiple_arrays.c
	$(CCOMP) -c $(OPT) -no-vec multiple_arrays.c $(INC) -o multiple_arrays_scalar.o

multiple_arrays_vector: multiple_arrays_vector.o papi_set_user_events.o
	$(LOADER) $(OPT) multiple_arrays_vector.o papi_set_user_events.o -o multiple_arrays_vector.exe $(LIB)

multiple_arrays_vector.o: multiple_arrays.c
	$(CCOMP) -c $(OPT) multiple_arrays.c $(INC) -o multiple_arrays_vector.o

papi_set_user_events.o:  papi_set_user_events.c papi_driver.h 
	$(CCOMP) -c $(OPT) papi_set_user_events.c $(INC)

run_scalar:
	./multiple_arrays_scalar.exe 

run_vector:
	./multiple_arrays_vector.exe

clean:
	rm -f *.o multiple_arrays_scalar.exe multiple_arrays_vector.exe
