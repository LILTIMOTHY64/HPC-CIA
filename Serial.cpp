#include <openssl/aes.h>
#include <openssl/des.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstring>

void AES_encrypt_decrypt_serial(unsigned char *input, unsigned char *output, AES_KEY *key, int size) {
    for (int i = 0; i < size; i += AES_BLOCK_SIZE) {
        AES_encrypt(input + i, output + i, key);
    }
}

void DES_encrypt_decrypt_serial(unsigned char *input, unsigned char *output, DES_key_schedule *key, int size) {
    for (int i = 0; i < size; i += DES_KEY_SZ) {
        DES_ecb_encrypt((DES_cblock *)(input + i), (DES_cblock *)(output + i), key, DES_ENCRYPT);
    }
}

int main() {
    const int maxDataSize = 1024 * 1024 * 10; // Max 10MB for demonstration

    unsigned char key[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    DES_cblock des_key;
    DES_key_schedule des_schedule;
    memcpy(des_key, key, 8);  // Copy the first 8 bytes of the key to des_key
    DES_set_key_unchecked(&des_key, &des_schedule);

    std::ofstream aesSerialFile("aes_serial.txt");
    std::ofstream desSerialFile("des_serial.txt");

    for (int dataSize = 1024 * 1024; dataSize <= maxDataSize; dataSize += 1024 * 1024) {
        unsigned char *input = new unsigned char[dataSize];
        unsigned char *output = new unsigned char[dataSize];
        memset(input, 0, dataSize); // Initialize input

        // Serial AES Encryption
        auto start = std::chrono::high_resolution_clock::now();
        AES_encrypt_decrypt_serial(input, output, &aes_key, dataSize);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        aesSerialFile << dataSize / (1024 * 1024) << " " << duration.count() << "\n";

        // Serial DES Encryption
        start = std::chrono::high_resolution_clock::now();
        DES_encrypt_decrypt_serial(input, output, &des_schedule, dataSize);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        desSerialFile << dataSize / (1024 * 1024) << " " << duration.count() << "\n";

        delete[] input;
        delete[] output;
    }

    aesSerialFile.close();
    desSerialFile.close();

    return 0;
}
