Parallel AES Encryption (OpenMP & MPI)

This project implements a performance-oriented parallel version of AES
encryption using OpenMP and MPI. AES blocks are encrypted independently
to exploit block-level parallelism on shared-memory and distributed-memory
systems.

The project includes three versions:

Sequential AES
OpenMP-based parallel AES
MPI-based parallel AES

A simplified AES kernel is used to focus on performance evaluation rather
than cryptographic correctness.

### Build

make

### Run

make run-seq
export OMP_NUM_THREADS=12 && make run-omp
make run-mpi
