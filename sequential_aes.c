#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "aes.h"

double now() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main() {
    int num_blocks = 1000000; // 1M blocks = 16MB
    uint8_t key[16] = {0};
    uint8_t roundKeys[16];
    AES_key_expansion(key, roundKeys);

    uint8_t* input = malloc(num_blocks * 16);
    uint8_t* output = malloc(num_blocks * 16);

    // Fill input with dummy data
    for (int i = 0; i < num_blocks * 16; i++)
        input[i] = i % 256;

    double start = now();

    for (int i = 0; i < num_blocks; i++)
        AES_encrypt_block(input + i*16, output + i*16, roundKeys);

    double end = now();
    double sec = end - start;

    double mb = (num_blocks * 16) / (1024.0 * 1024.0);
    double throughput = mb / sec;

    printf("Sequential AES time: %.4f sec\n", sec);
    printf("Throughput: %.2f MB/s\n", throughput);

    return 0;
}
