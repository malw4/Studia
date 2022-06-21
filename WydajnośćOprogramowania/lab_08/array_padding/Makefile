# kompilator c
#CCOMP = icc
CCOMP = gcc

# konsolidator
LOADER = $(CCOMP)

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3 -qopenmp -march=core-avx2 
OPT = -O3 -fopenmp -march=core-avx2 

# PAPI
#PAPI_HOME = /home/krzysztof/papi/papi-5.6.0/src
#PAPI_HOME = /home/krzysztof/Pobrane/papi-6.0.0/src_icc
PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

PAPI_DRIVER_HOME = ../papi_driver_mth

# pliki naglowkowe
#INC = -I../pomiar_czasu
INC = -I$(PAPI_HOME) -I$(PAPI_DRIVER_HOME)

# biblioteki
#LIB = -L../pomiar_czasu -lm
#LIB = -L/opt/intel//mkl/8.1/lib/em64t -lmkl_em64t
#LIB = -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -liomp5 -lmkl_core -lmkl_intel_thread -lm
LIB = -L. -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a -L$(PAPI_DRIVER_HOME) -lpapi_driver_mth -pthread


# zaleznosci i komendy
all:  array_padding_test_papi run_papi 

array_padding_test: array_padding_test.o pomiar_czasu.o
	$(LOADER) $(OPT) array_padding_test.o pomiar_czasu.o  -o array_padding_test.exe $(LIB)

array_padding_test.o: array_padding_test_papi.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) array_padding_test_papi.c $(INC) -o array_padding_test.o

array_padding_test_papi: array_padding_test_papi.o pomiar_czasu.o papi_set_user_events_mth.o
	$(LOADER) $(OPT) array_padding_test_papi.o pomiar_czasu.o  papi_set_user_events_mth.o -o array_padding_test_papi.exe $(LIB)

array_padding_test_papi.o: array_padding_test_papi.c  papi_driver_mth.h pomiar_czasu.h
	$(CCOMP) -c $(OPT) -DPAPI_TEST array_padding_test_papi.c $(INC) -o array_padding_test_papi.o

pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

papi_set_user_events_mth.o:  papi_set_user_events_mth.c papi_driver_mth.h 
	$(CCOMP) -c $(OPT) papi_set_user_events_mth.c $(INC)

run_papi:
	./array_padding_test_papi.exe 

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
