# kompilator c
#CCOMP = gcc
CCOMP = icc

# konsolidator
LOADER = $(CCOMP)

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3 -fopenmp -p
OPT = -O3
OPT0 = -O0
OPT3 = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
#LIB = -L/opt/intel//mkl/8.1/lib/em64t -lmkl_em64t
#LIB = -L/opt/intel//mkl/8.1/lib/32 -lmkl_ia32

# zaleznosci i komendy

all: mat_vec_test_no_opt mat_vec_test_opt run_test

mat_vec_test_no_opt: mat_vec_test.o mat_vec_no_opt.o pomiar_czasu.o
	$(LOADER) $(OPT0) mat_vec_test.o mat_vec_no_opt.o pomiar_czasu.o -o mat_vec_test_no_opt.exe $(LIB)

mat_vec_test_opt: mat_vec_test.o mat_vec_opt.o pomiar_czasu.o
	$(LOADER) $(OPT3) mat_vec_test.o mat_vec_opt.o pomiar_czasu.o -o mat_vec_test_opt.exe $(LIB)

mat_vec_test.o: mat_vec_test.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) mat_vec_test.c $(INC)

mat_vec_no_opt.o: mat_vec.c
	$(CCOMP) -c $(OPT0) mat_vec.c -o mat_vec_no_opt.o

mat_vec_opt.o: mat_vec.c
	$(CCOMP) -c $(OPT3) mat_vec.c -o mat_vec_opt.o

pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

run_test:
	@echo ''
	@echo 'running mat_vec test with compiler option -O0'
	./mat_vec_test_no_opt.exe
	@echo ''
	@echo 'running mat_vec test with compiler option -O3'
	./mat_vec_test_opt.exe

clean:
	rm -f *.o *~ *.exe
