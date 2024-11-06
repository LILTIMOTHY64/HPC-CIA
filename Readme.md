# AES and DES Encryption: Serial vs. Parallel Implementations
- Keerthivasan.M
- Nalin S.V
- Nareshkumar.R
- Venkat Saran

This project contains two C++ programs that demonstrate the performance of **AES** and **DES** encryption algorithms in both serial and parallel implementations. By comparing execution times, we can analyze the performance impact of parallelizing encryption tasks using OpenMP.

## Files

1. **`Serial.cpp`** - Serial implementation of AES and DES encryption.
2. **`Parallel.cpp`** - Parallel implementation of AES and DES encryption using OpenMP.
3. **Output Files**:
   - `aes_serial.txt` - Execution times for AES encryption in serial.
   - `des_serial.txt` - Execution times for DES encryption in serial.
   - `aes_parallel.txt` - Execution times for AES encryption in parallel.
   - `des_parallel.txt` - Execution times for DES encryption in parallel.

## Prerequisites

1. **OpenSSL** library (for AES and DES encryption functions)
2. **OpenMP** (for parallelization in `Parallel.cpp`)
3. **g++** compiler

To install OpenSSL:
```bash
sudo apt-get install libssl-dev
```

## Compilation

Compile the programs with OpenSSL and OpenMP support:

```bash
# Serial program
g++ Serial.cpp -o Serial -lssl -lcrypto

# Parallel program (requires OpenMP)
g++ Parallel.cpp -o Parallel -fopenmp -lssl -lcrypto
```

## Running the Programs

1. **Serial Execution**
   ```bash
   ./Serial
   ```
   This will output timing data to `aes_serial.txt` and `des_serial.txt`.

2. **Parallel Execution**
   ```bash
   ./Parallel
   ```
   This will output timing data to `aes_parallel.txt` and `des_parallel.txt`.

## Code Overview

### AES and DES Functions

- **AES** encryption (`AES_encrypt_decrypt_serial` and `AES_encrypt_decrypt_parallel`):
  - Encrypts data in blocks of 16 bytes (AES block size).
  - Uses a 128-bit key for encryption.

- **DES** encryption (`DES_encrypt_decrypt_serial` and `DES_encrypt_decrypt_parallel`):
  - Encrypts data in blocks of 8 bytes (DES block size).
  - Uses the first 8 bytes of the 16-byte key for DES.

### Performance Measurement

Each encryption function runs with different data sizes (from 1MB up to 10MB) to measure execution time. The times are recorded and saved to output files for later analysis.

## Parallelization Details

- **OpenMP** is used to parallelize AES and DES encryption by dividing the data blocks among threads.
- AES and DES encryption in `Parallel.cpp` use `#pragma omp parallel for` to assign blocks to different threads, which enhances performance for larger data sizes.

## Output

Each output file contains two columns:
- **Data size (in MB)**.
- **Execution time (in seconds)**.

Example content of `aes_serial.txt`:
```
1 0.0234
2 0.0456
3 0.0678
...
```

