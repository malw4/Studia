# compiler
#CCOMP = icc
CCOMP = gcc

MY_CORE = 4

#DEF_FREQ = 'NOMINAL_FREQUENCY=3.6' # 9700KF
DEF_FREQ = 'NOMINAL_FREQUENCY=2.2' # ESTERA 

# linker
LINKER = $(CCOMP)

# for debugging/profiling
# OPT = -g -DDEBUG -p
#for gcc
OPT = -O3  -fopenmp -march=core-avx2 -D$(DEF_FREQ)
OPT_NO_VEC = -O3  -fopenmp -march=core-avx2 -D$(DEF_FREQ)
# for icc
#OPT = -O3  -qopenmp -march=core-avx2 -D$(DEF_FREQ)
#OPT_NO_VEC = -O3  -qopenmp -no-vec -march=core-avx2 -D$(DEF_FREQ)

# PAPI
#PAPI_HOME = /home/krzysztof/PAPI/papi_6.0.0/src
#PAPI_HOME = /home/krzysztof/papi/papi-5.6.0/src
#PAPI_HOME = /home/krzysztof/Pobrane/papi-6.0.0/src_icc
PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src

PAPI_DRIVER_HOME = ../papi_driver_mth

# pliki naglowkowe
#INC = -I/opt/intel/mkl/10.2.4.032/include
INC = -I$(PAPI_HOME) -I$(PAPI_DRIVER_HOME)

# AMD
#LIB = -L$(MKLROOT)  -lmkl_lapack -lmkl_core -lmkl_intel_lp64 -lmkl_intel_thread  -lguide -lpthread -lm
# centos 7
LIB =   -L. -lm -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a  -lpapi_driver_mth -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread

all: mat_mul_driver.exe mat_mul_driver_papi.exe run

# zaleznosci i komendy
mat_mul_driver.exe: mat_mul_driver.o mat_mul_par.o # mat_mul_avx_1.o mat_mul_avx_2.o 
	$(LINKER) $(OPT) mat_mul_driver.o mat_mul_par.o -o mat_mul_driver.exe $(LIB) # mat_mul_avx_1.o mat_mul_avx_2.o

mat_mul_driver_papi.exe: mat_mul_driver_papi.o mat_mul_par_papi.o papi_set_user_events_mth.o #mat_mul_avx_1.o mat_mul_avx_2.o
	$(LINKER) $(OPT) mat_mul_driver_papi.o mat_mul_par_papi.o  papi_set_user_events_mth.o -o mat_mul_driver_papi.exe $(LIB) #mat_mul_avx_1.o mat_mul_avx_2.o

mat_mul_driver.o: mat_mul_driver.c sizes.h
	$(CCOMP) -c $(OPT) mat_mul_driver.c $(INC)

mat_mul_driver_papi.o: mat_mul_driver.c sizes.h
	$(CCOMP) -c $(OPT) -DPAPI_TEST mat_mul_driver.c -o mat_mul_driver_papi.o $(INC)

mat_mul_par.o: mat_mul_par_papi.c sizes.h
	$(CCOMP) -c  $(OPT) mat_mul_par_papi.c -o mat_mul_par.o $(INC)

mat_mul_par_papi.o: mat_mul_par_papi.c sizes.h
	$(CCOMP) -c  $(OPT) mat_mul_par_papi.c -DPAPI_TEST $(INC)

papi_set_user_events_mth.o:  papi_set_user_events_mth.c papi_driver_mth.h 
	$(CCOMP) -c $(OPT) papi_set_user_events_mth.c $(INC)

run:
	numactl -C $(MY_CORE) perf stat -d -d -d ./mat_mul_driver.exe
#	export KMP_AFFINITY=scatter
#	export OMP_NUM_THREADS=20
#	./mat_mul_driver.exe
#run:
# setenv GOMP_AFFINITY "0,1,2,3"
# setenv KMP_AFFINITY "proclist=[0,1,2,3],explicit"

run_papi:
	numactl -C $(MY_CORE) ./mat_mul_driver_papi.exe

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
