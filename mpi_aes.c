#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <mpi.h>
#include "aes.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_blocks = 1000000;
    int local_blocks = num_blocks / size;

    uint8_t key[16] = {0};
    uint8_t roundKeys[16];
    AES_key_expansion(key, roundKeys);

    uint8_t* input = NULL;
    if (rank == 0)
        input = malloc(num_blocks * 16);

    uint8_t* local_input = malloc(local_blocks * 16);
    uint8_t* local_output = malloc(local_blocks * 16);

    if (rank == 0)
        for (int i = 0; i < num_blocks * 16; i++)
            input[i] = i % 256;

    double start = MPI_Wtime();

    MPI_Scatter(input, local_blocks*16, MPI_BYTE,
                local_input, local_blocks*16, MPI_BYTE,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < local_blocks; i++)
        AES_encrypt_block(local_input + i*16, local_output + i*16, roundKeys);

    MPI_Gather(local_output, local_blocks*16, MPI_BYTE,
               input, local_blocks*16, MPI_BYTE,
               0, MPI_COMM_WORLD);

    double end = MPI_Wtime();
    double sec = end - start;

    if (rank == 0) {
        double mb = (num_blocks * 16) / (1024.0 * 1024.0);
        double throughput = mb / sec;

        printf("MPI AES (%d ranks) time: %.4f sec\n", size, sec);
        printf("Throughput: %.2f MB/s\n", throughput);
    }

    MPI_Finalize();
    return 0;
}
