#include <openssl/aes.h>
#include <openssl/des.h>
#include <omp.h>
#include <iostream>
#include <chrono>
#include <cstring> // Include this header for memcpy

void AES_encrypt_decrypt_parallel(unsigned char *input, unsigned char *output, AES_KEY *key, int size) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < size; i += AES_BLOCK_SIZE) {
        AES_encrypt(input + i, output + i, key);
    }
}

void DES_encrypt_decrypt_parallel(unsigned char *input, unsigned char *output, DES_key_schedule *key, int size) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < size; i += DES_KEY_SZ) {
        DES_ecb_encrypt((DES_cblock *)(input + i), (DES_cblock *)(output + i), key, DES_ENCRYPT);
    }
}

int main() {
    const int dataSize = 1024 * 1024 * 10; // 1MB input size

    unsigned char key[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    
    unsigned char *input = new unsigned char[dataSize];
    unsigned char *output = new unsigned char[dataSize];
    memset(input, 0, dataSize); // Example input initialization

    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    DES_cblock des_key;
    DES_key_schedule des_schedule;
    memcpy(des_key, key, 8);  // Copy the first 8 bytes of the key to des_key
    DES_set_key_unchecked(&des_key, &des_schedule);

    // Parallel AES Encryption with larger input size
    auto start = std::chrono::high_resolution_clock::now();
    AES_encrypt_decrypt_parallel(input, output, &aes_key, dataSize);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "AES Parallel Time (1MB): " << duration.count() << " seconds\n";

    // Parallel DES Encryption with larger input size
    start = std::chrono::high_resolution_clock::now();
    DES_encrypt_decrypt_parallel(input, output, &des_schedule, dataSize);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "DES Parallel Time (1MB): " << duration.count() << " seconds\n";

    delete[] input;
    delete[] output;

    return 0;
}
