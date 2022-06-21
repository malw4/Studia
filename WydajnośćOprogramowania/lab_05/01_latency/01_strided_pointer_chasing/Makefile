# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
LOADER = $(CCOMP)

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3 -DPAPI_TEST

PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/
INC = -I$(PAPI_HOME)

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a -L. -lpapi_driver

all: strided_pointer_chasing run

strided_pointer_chasing: strided_pointer_chasing.o papi_set_user_events.o
	$(LOADER) $(OPT) strided_pointer_chasing.o papi_set_user_events.o -o strided_pointer_chasing.exe $(LIB)

strided_pointer_chasing.o: strided_pointer_chasing.c
	$(CCOMP) -c $(OPT) strided_pointer_chasing.c $(INC)

papi_set_user_events.o:  papi_set_user_events.c papi_driver.h
	$(CCOMP) -c $(OPT) papi_set_user_events.c $(INC)

run:
	./strided_pointer_chasing.exe 

clean:
	rm -f *.o strided_pointer_chasing.exe
