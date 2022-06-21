# kompilator c
CCOMP = gcc
#CCOMP = icc

# konsolidator
LOADER = $(CCOMP)

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3 -fopenmp -p
OPT = -O3 -fopenmp
OPT0 = -O3 -fopenmp
OPT3 = -O3 -fopenmp

MY_CORE = 6

# PAPI
#PAPI_HOME = /home/krzysztof/Pobrane/papi-6.0.0/src_gcc
PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src
#PAPI_HOME = /home/krzysztof/Pobrane/papi-6.0.0/src_icc

PAPI_DRIVER_HOME = ./papi_driver_mth

# pliki naglowkowe
#INC = -I../pomiar_czasu
#INC = -I/opt/intel/mkl/8.1/include/
INC = -I$(PAPI_HOME)

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
#LIB = -lm  -L/opt/intel/mkl/8.1/lib/32 -lmkl -lmkl_lapack
LIB = -L. -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a  -lpapi_driver_mth -pthread

# zaleznosci i komendy

all: mat_vec_test_opt_papi mat_vec_test_opt run_test

mat_vec_test_opt_papi: mat_vec_test_papi.o mat_vec_opt_papi.o  papi_set_user_events_mth.o
	$(LOADER) $(OPT3) mat_vec_test_papi.o mat_vec_opt_papi.o  papi_set_user_events_mth.o -o mat_vec_test_opt_papi.exe $(LIB) -DPAPI_TEST

mat_vec_test_opt: mat_vec_test.o mat_vec_opt.o 
	$(LOADER) $(OPT3) mat_vec_test.o mat_vec_opt.o papi_set_user_events_mth.o  -o mat_vec_test_opt.exe $(LIB)

mat_vec_test.o: mat_vec_test.c  papi_driver_mth.h
	$(CCOMP) -c $(OPT3) mat_vec_test.c $(INC)

mat_vec_test_papi.o: mat_vec_test.c  papi_driver_mth.h
	$(CCOMP) -c $(OPT3) mat_vec_test.c -o mat_vec_test_papi.o $(INC) -DPAPI_TEST

mat_vec_opt_papi.o: mat_vec.c  papi_driver_mth.h
	$(CCOMP) -c $(OPT3) mat_vec.c  $(INC) -o mat_vec_opt_papi.o  -DPAPI_TEST

mat_vec_opt.o: mat_vec.c  papi_driver_mth.h
	$(CCOMP) -c $(OPT3) mat_vec.c  $(INC) -o mat_vec_opt.o

papi_set_user_events_mth.o:  papi_set_user_events_mth.c papi_driver_mth.h 
	$(CCOMP) -c $(OPT3) papi_set_user_events_mth.c $(INC)


run_test:
	@echo ''
	@echo 'running mat_vec test with compiler option -O3'
	numactl -C $(MY_CORE) ./mat_vec_test_opt.exe
	@echo ''
	@echo 'running mat_vec test with compiler option -O3 and PAPI'
	numactl -C $(MY_CORE) ./mat_vec_test_opt_papi.exe

run_valgrind:
	numactl -C $(MY_CORE) valgrind --tool=cachegrind ./mat_vec_test_opt.exe

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
