# Compiler definitions
CC      = gcc
MPICC   = mpicc

# Compiler flags
CFLAGS  = -O2 -Wall
OMPFLAG = -fopenmp

# Targets
SEQ     = seq
OMP     = omp
MPI     = mpi

# Source files
AES_SRC = aes.c
SEQ_SRC = sequential_aes.c
OMP_SRC = omp_aes.c
MPI_SRC = mpi_aes.c

# Default target
all: $(SEQ) $(OMP) $(MPI)

# Sequential AES
$(SEQ): $(SEQ_SRC) $(AES_SRC)
	$(CC) $(CFLAGS) $^ -o $@

# OpenMP AES
$(OMP): $(OMP_SRC) $(AES_SRC)
	$(CC) $(CFLAGS) $(OMPFLAG) $^ -o $@

# MPI AES
$(MPI): $(MPI_SRC) $(AES_SRC)
	$(MPICC) $(CFLAGS) $^ -o $@

# Run targets
run-seq: $(SEQ)
	./$(SEQ)

run-omp: $(OMP)
	./$(OMP)

run-mpi: $(MPI)
	mpirun -np 4 ./$(MPI)

# Clean
clean:
	rm -f $(SEQ) $(OMP) $(MPI)

.PHONY: all clean run-seq run-omp run-mpi
