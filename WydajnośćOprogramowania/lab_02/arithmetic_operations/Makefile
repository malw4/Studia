SHELL = /bin/sh

# C compiler
# kompilator C
CCOMP = gcc
#CCOMP = icc

# linker
# konsolidator
LINKER = $(CCOMP)

# options:
# opcje:

# version for debugging
# wersja do debugowania
# OPT = -g -DDEBUG

# optimized version for time measurements
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3 -mavx
#OPT = -O3 -march=core-avx2 -openmp
OPT = -O3 

# PAPI
# PAPI_HOME = /home/krzysztof/Pobrane/papi-6.0.0/src_gcc
PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

# location for header files
# katalog z plikami naglowkowymi
INC = -I../utd_time_unix -I../utd_papi_driver -I$(PAPI_HOME)

# locations for libraries and options for linking libraries
# katalogi bibliotek i opcje dołączania bibliotek
LIB = -L../utd_time_unix -lutl_time -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a -L../utd_papi_driver -lpapi_driver

# dependencies and commands 
# zaleznosci i komendy
all: arithmetic_operation branch_prediction_papi

arithmetic_operation: arithmetic_operation.o 
	$(LINKER) $(OPT) arithmetic_operation.o -o arithmetic_operation $(LIB)

arithmetic_operation.o: arithmetic_operation.c ../utd_time_unix/uth_time.h 
	$(CCOMP) -c $(OPT) arithmetic_operation.c $(INC)

branch_prediction_papi: branch_prediction_papi.o papi_set_user_events.o
	$(LINKER) $(OPT) branch_prediction_papi.o  papi_set_user_events.o -o branch_prediction_papi $(LIB)

branch_prediction_papi.o: arithmetic_operation.c ../utd_time_unix/uth_time.h ../utd_papi_driver/papi_driver.h
	$(CCOMP) -c $(OPT) arithmetic_operation.c -DPAPI_TEST -o branch_prediction_papi.o $(INC)

papi_set_user_events.o: papi_set_user_events.c ../utd_papi_driver/papi_driver.h
	$(CCOMP) -c $(OPT) papi_set_user_events.c  $(INC)
clean:
	rm -f *.o

clean_papi_lib:
	rm -f ../utd_papi_driver/*.o ../utd_papi_driver/*.a

recreate_papi_lib:
	rm -f ../utd_papi_driver/*.o ../utd_papi_driver/*.a
	$(CCOMP) -c $(OPT) ../utd_papi_driver/papi_driver.c -o ../utd_papi_driver/papi_driver.o $(INC)
	ar -rs ../utd_papi_driver/libpapi_driver.a ../utd_papi_driver/papi_driver.o

recreate_time_lib:
	rm -f ../utd_time_unix/*.o ../utd_time_unix/*.a
	$(CCOMP) -c $(OPT) ../utd_time_unix/uts_time.c -o ../utd_time_unix/uts_time.o $(INC)
	ar -rs ../utd_time_unix/libutl_time.a ../utd_time_unix/uts_time.o
