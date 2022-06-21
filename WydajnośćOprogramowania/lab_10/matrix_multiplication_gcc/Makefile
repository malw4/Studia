# compiler
#CCOMP = icc
CCOMP = gcc

# linker
LINKER = $(CCOMP)

# for debugging/profiling
# OPT = -g -DDEBUG -p
#for gcc
OPT = -O3  -fopenmp -march=core-avx2
OPT_NO_VEC = -O3  -fopenmp -march=core-avx2
# for icc
#OPT = -O3  -qopenmp -march=core-avx2
#OPT_NO_VEC = -O3  -qopenmp -no-vec -march=core-avx2

#INC = -I/opt/intel/mkl/10.2.4.032/include

# AMD
#LIB = -L$(MKLROOT)  -lmkl_lapack -lmkl_core -lmkl_intel_lp64 -lmkl_intel_thread  -lguide -lpthread -lm
# centos 7
LIB = -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm

all: mat_mul_driver.exe run

# zaleznosci i komendy
mat_mul_driver.exe: mat_mul_driver.o mat_mul_par.o mat_mul_avx_1.o mat_mul_avx_2.o 
	$(LINKER) $(OPT) mat_mul_driver.o mat_mul_par.o mat_mul_avx_1.o mat_mul_avx_2.o -o mat_mul_driver.exe $(LIB)

mat_mul_driver.o: mat_mul_driver.c sizes.h
	$(CCOMP) -c $(OPT) mat_mul_driver.c $(INC)

mat_mul_par.o: mat_mul_par.c sizes.h
	$(CCOMP) -c  $(OPT_NO_VEC) mat_mul_par.c $(INC)

mat_mul_avx_1.o: mat_mul_avx_1.c sizes.h
	$(CCOMP) -c  $(OPT_NO_VEC) mat_mul_avx_1.c $(INC)

mat_mul_avx_2.o: mat_mul_avx_2.c sizes.h
	$(CCOMP) -c  $(OPT_NO_VEC) mat_mul_avx_2.c $(INC)

run:
	export KMP_AFFINITY=scatter
	export OMP_NUM_THREADS=20
	./mat_mul_driver.exe

clean:
	rm -f *.o *~ *.exe

#run:
# setenv GOMP_AFFINITY "0,1,2,3"
# setenv KMP_AFFINITY "proclist=[0,1,2,3],explicit"
