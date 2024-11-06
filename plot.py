import matplotlib.pyplot as plt

def read_data(filename):
    sizes, times = [], []
    with open(filename, 'r') as f:
        for line in f:
            size, time = map(float, line.split())
            sizes.append(size)
            times.append(time)
    return sizes, times

# Load data
aes_serial_sizes, aes_serial_times = read_data("aes_serial.txt")
aes_parallel_sizes, aes_parallel_times = read_data("aes_parallel.txt")
des_serial_sizes, des_serial_times = read_data("des_serial.txt")
des_parallel_sizes, des_parallel_times = read_data("des_parallel.txt")

# Plot AES Performance
plt.figure(figsize=(10, 5))
plt.plot(aes_serial_sizes, aes_serial_times, label='AES Serial', marker='o')
plt.plot(aes_parallel_sizes, aes_parallel_times, label='AES Parallel', marker='o')
plt.xlabel('Data Size (MB)')
plt.ylabel('Time (seconds)')
plt.title('AES Performance: Serial vs Parallel')
plt.legend()
plt.grid(True)
plt.savefig("aes_performance.png")
plt.show()

# Plot DES Performance
plt.figure(figsize=(10, 5))
plt.plot(des_serial_sizes, des_serial_times, label='DES Serial', marker='o')
plt.plot(des_parallel_sizes, des_parallel_times, label='DES Parallel', marker='o')
plt.xlabel('Data Size (MB)')
plt.ylabel('Time (seconds)')
plt.title('DES Performance: Serial vs Parallel')
plt.legend()
plt.grid(True)
plt.savefig("des_performance.png")
plt.show()
