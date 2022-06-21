# kompilator c
#CCOMP = icc
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

all: random_pointer_chasing run

random_pointer_chasing: random_pointer_chasing.o papi_set_user_events.o
	$(LOADER) $(OPT) random_pointer_chasing.o papi_set_user_events.o -o random_pointer_chasing.exe $(LIB)

random_pointer_chasing.o: random_pointer_chasing.c
	$(CCOMP) -c $(OPT) random_pointer_chasing.c $(INC)

papi_set_user_events.o:  papi_set_user_events.c papi_driver.h 
	$(CCOMP) -c $(OPT) papi_set_user_events.c $(INC)

run:
	./random_pointer_chasing.exe 

clean:
	rm -f *.o random_pointer_chasing.exe
