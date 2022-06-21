# kompilator c
#CCOMP = gcc
CCOMP = gcc

# konsolidator
LOADER = $(CCOMP)

# opcje optymalizacji:
#OPT = -fast 
OPT = -O3 

# PAPI
#PAPI_HOME = /home/krzysztof/papi/papi-5.6.0/src
#PAPI_HOME = /home/krzysztof/Pobrane/papi-6.0.0/src_icc
PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

PAPI_DRIVER_HOME = ../papi_driver_mth

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/
INC = -I$(PAPI_HOME) -I$(PAPI_DRIVER_HOME)

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -L. -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a  -lpapi_driver_mth -pthread


all: false_sharing_test false_sharing_test_papi run_papi 

false_sharing_test: false_sharing_test.o 
	$(LOADER) $(OPT) false_sharing_test.o  -o false_sharing_test.exe $(LIB)

false_sharing_test.o: false_sharing_test_papi.c 
	$(CCOMP) -c $(OPT) false_sharing_test_papi.c $(INC) -o false_sharing_test.o

false_sharing_test_papi: false_sharing_test_papi.o papi_set_user_events_mth.o
	$(LOADER) $(OPT) false_sharing_test_papi.o  papi_set_user_events_mth.o -o false_sharing_test_papi.exe $(LIB)

false_sharing_test_papi.o: false_sharing_test_papi.c  papi_driver_mth.h
	$(CCOMP) -c $(OPT) -DPAPI_TEST false_sharing_test_papi.c $(INC) -o false_sharing_test_papi.o


papi_set_user_events_mth.o:  papi_set_user_events_mth.c papi_driver_mth.h 
	$(CCOMP) -c $(OPT) papi_set_user_events_mth.c $(INC)

run_papi:
	./false_sharing_test_papi.exe 
	./false_sharing_test.exe 

clean:
	rm -f *.o *~ *.exe

deep_clean:
	rm -f *.o *~ *.exe libpapi_driver_mth.a papi_driver_mth.h

recreate_papi_lib_mth:
	rm -f $(PAPI_DRIVER_HOME)/*_mth.o $(PAPI_DRIVER_HOME)/*_mth.a
	$(CCOMP) -c $(OPT) $(PAPI_DRIVER_HOME)/papi_driver_mth.c -o $(PAPI_DRIVER_HOME)/papi_driver_mth.o $(INC)
	ar -rs $(PAPI_DRIVER_HOME)/libpapi_driver_mth.a $(PAPI_DRIVER_HOME)/papi_driver_mth.o
	cp $(PAPI_DRIVER_HOME)/libpapi_driver_mth.a .
	cp $(PAPI_DRIVER_HOME)/papi_driver_mth.h .


clean_papi_lib_mth:
	rm -f $(PAPI_DRIVER_HOME)/*.o $(PAPI_DRIVER_HOME)/*.a $(PAPI_DRIVER_HOME)/*~
