# kompilator c
#CCOMP = gcc
CCOMP = gcc

# konsolidator
#LOADER = gcc
LOADER = gcc

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3

# PAPI
PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/
INC = -I$(PAPI_HOME)

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -L. -lutl_time -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a  -lpapi_driver


#all: cache_line_size_array_increment cache_line_size_array_increment_papi run_papi run
all: cache_line_size_array_increment run

cache_line_size_array_increment: cache_line_size_array_increment.o 
	$(LOADER) $(OPT) cache_line_size_array_increment.o -o cache_line_size_array_increment.exe $(LIB)

cache_line_size_array_increment.o: cache_line_size_array_increment.c
	$(CCOMP) -c $(OPT) cache_line_size_array_increment.c $(INC)


cache_line_size_array_increment_papi: cache_line_size_array_increment_papi.o papi_set_user_events.o
	$(LOADER) $(OPT) cache_line_size_array_increment_papi.o  papi_set_user_events.o -o cache_line_size_array_increment_papi.exe $(LIB)

cache_line_size_array_increment_papi.o: cache_line_size_array_increment.c uth_time.h papi_driver.h
	$(CCOMP) -c $(OPT) -DPAPI_TEST cache_line_size_array_increment.c $(INC) -o cache_line_size_array_increment_papi.o

papi_set_user_events.o:  papi_set_user_events.c papi_driver.h 
	$(CCOMP) -c $(OPT) papi_set_user_events.c $(INC)

run:
	./cache_line_size_array_increment.exe 

run_papi:
	./cache_line_size_array_increment_papi.exe 

clean:
	rm -f *.o
