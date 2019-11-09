CC = g++ -std=c++11
OMP = -fopenmp
CCFLAGS  =  -O -Wall -ftemplate-depth-150
 
IDFLAGS     = -I. -I/home/marin/Lib/ula/include -I/home/marin/Lib/ula/include/ula #-I/usr/local/include 
LIBS_LAPACK = -lgfortran -lm -llapack -lblas #-lfftw3
.C:
	$(CC) $(OMP) $(CCFLAGS) $@.C -o $@ $(LDFLAGS) $(IDFLAGS) $(LIBS_LAPACK) 

clean:
	\rm *~ 
