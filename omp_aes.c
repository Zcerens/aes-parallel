#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <omp.h>
#include "aes.h"

int main() {
    int num_blocks = 1000000; // 1M blocks = 16MB
    uint8_t key[16] = {0};
    uint8_t roundKeys[16];
    AES_key_expansion(key, roundKeys);

    uint8_t* input = malloc(num_blocks * 16);
    uint8_t* output = malloc(num_blocks * 16);

    for (int i = 0; i < num_blocks * 16; i++)
        input[i] = i % 256;

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < num_blocks; i++)
        AES_encrypt_block(input + i*16, output + i*16, roundKeys);

    double end = omp_get_wtime();
    double sec = end - start;

    double mb = (num_blocks * 16) / (1024.0 * 1024.0);
    double throughput = mb / sec;

    int threads = omp_get_max_threads();

    printf("OpenMP AES (%d threads) time: %.4f sec\n", threads, sec);
    printf("Throughput: %.2f MB/s\n", throughput);

    return 0;
}
