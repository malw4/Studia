SHELL = /bin/sh

# C compiler
# kompilator C
CCOMP = icc

# linker
# konsolidator
LINKER = $(CCOMP)

# options:
# opcje:

PAPI_HOME = /home/students_wo/common_files/papi-6.0.0/src
PAPI_DRIVER_HOME = ../papi_driver_mth

# version for debugging
# wersja do debugowania
# OPT = -g -DDEBUG

# optimized version
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3 -mavx2 -march=core-avx2
#OPT = -O3 -march=core-avx2 
OPT = -O3 -march=core-avx2 

# location for header files
# katalog z plikami naglowkowymi
INC = -I$(PAPI_HOME)

# locations for libraries and options for linking libraries
# katalogi bibliotek i opcje dołączania bibliotek
LIB =  -lm -lpthread -L$(PAPI_HOME) $(PAPI_HOME)/libpapi.a -L. -lpapi_driver_mth

# dependencies and commands 
# zaleznosci i komendy
all:  scalability_vector_flops scalability_vector_flops_papi run

scalability_vector_flops: scalability_vector_flops.o 
	$(LINKER) $(OPT) scalability_vector_flops.o  -o scalability_vector_flops.exe $(LIB)

scalability_vector_flops_papi: scalability_vector_flops_papi.o  papi_set_user_events_mth.o
	$(LINKER) $(OPT) scalability_vector_flops_papi.o  papi_set_user_events_mth.o -o scalability_vector_flops_papi.exe $(LIB)

scalability_vector_flops.o: scalability_vector_flops.c 
	$(CCOMP) -c $(OPT) scalability_vector_flops.c $(INC) 

scalability_vector_flops_papi.o: scalability_vector_flops.c papi_driver_mth.h
	$(CCOMP) -c $(OPT) scalability_vector_flops.c $(INC) -DPAPI_TEST -o scalability_vector_flops_papi.o

papi_set_user_events_mth.o:  papi_set_user_events_mth.c papi_driver_mth.h
	$(CCOMP) -c $(OPT) papi_set_user_events_mth.c $(INC)

run:
	./scalability_vector_flops.exe

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
