SHELL = /bin/sh

# C compiler
# kompilator C
CCOMP = icc
#CCOMP = gcc

# linker
# konsolidator
LINKER = icc
#LINKER = gcc

# options:
# opcje:

# version for debugging
# wersja do debugowania
# OPT = -g -DDEBUG

# optimized version
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -mavx2 -march=core-avx2
#OPT = -O3 -march=core-avx2 
#OPT = -O3

# location for header files
# katalog z plikami naglowkowymi
INC = -I../utd_time_unix

# locations for libraries and options for linking libraries
# katalogi bibliotek i opcje dołączania bibliotek
LIB = -L../utd_time_unix -lm -lpthread

# dependencies and commands 
# zaleznosci i komendy
all: latency_throughput_scalar_flops latency_throughput_vector_flops latency_throughput_multithreaded_vector_flops

latency_throughput_scalar_flops: latency_throughput_scalar_flops.o ../utd_time_unix/uts_time.o
	$(LINKER) $(OPT) latency_throughput_scalar_flops.o ../utd_time_unix/uts_time.o -o latency_throughput_scalar_flops $(LIB)

latency_throughput_scalar_flops.o: latency_throughput_scalar_flops.c ../utd_time_unix/uth_time.h
	$(CCOMP) -c $(OPT) latency_throughput_scalar_flops.c $(INC)

latency_throughput_vector_flops: latency_throughput_vector_flops.o ../utd_time_unix/uts_time.o
	$(LINKER) $(OPT) latency_throughput_vector_flops.o ../utd_time_unix/uts_time.o -o latency_throughput_vector_flops $(LIB)

latency_throughput_vector_flops.o: latency_throughput_vector_flops.c ../utd_time_unix/uth_time.h
	$(CCOMP) -c $(OPT) latency_throughput_vector_flops.c $(INC)

latency_throughput_multithreaded_vector_flops: latency_throughput_multithreaded_vector_flops.o ../utd_time_unix/uts_time.o
	$(LINKER) $(OPT) latency_throughput_multithreaded_vector_flops.o ../utd_time_unix/uts_time.o -o latency_throughput_multithreaded_vector_flops $(LIB)

latency_throughput_multithreaded_vector_flops.o: latency_throughput_multithreaded_vector_flops.c ../utd_time_unix/uth_time.h
	$(CCOMP) -c $(OPT) latency_throughput_multithreaded_vector_flops.c $(INC)

../utd_time_unix/uts_time.o: ../utd_time_unix/uts_time.c ../utd_time_unix/uth_time.h
	$(CCOMP) -c $(OPT)  ../utd_time_unix/uts_time.c -o ../utd_time_unix/uts_time.o $(INC)

clean:
	rm -f *.o
