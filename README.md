Parallel AES Encryption (OpenMP & MPI)
## Medium Article

A detailed explanation of the project, performance analysis, and results
are available in the Medium article:

👉 https://medium.com/@zeycerensahin/parallel-aes-encryption-using-openmp-and-mpi-a6e2edba396e

## ReadMe
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
