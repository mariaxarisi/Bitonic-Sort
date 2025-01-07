import os
import matplotlib.pyplot as plt

# Paths for the files
MPI_PATH = os.path.join(os.path.dirname(__file__), 'results.txt')
QSORT_PATH = os.path.join(os.path.dirname(__file__), 'qsort-serial.txt')
SAVE_DIR = os.path.join(os.path.dirname(__file__), '../assets')
SAVE_PATH = os.path.join(SAVE_DIR, 'speed.png')

# Data extraction from results.txt
with open(MPI_PATH, 'r') as file:
    data = file.read()

lines = data.splitlines()
results = {}
current_p = None

for line in lines:
    line = line.strip()
    if line.startswith("WHEN p"):
        current_p = int(line.split("=")[1].strip())
        results[current_p] = {"q": [], "time": []}
    elif line.startswith("q ="):
        q = int(line.split("=")[1].strip())
        results[current_p]["q"].append(q)
    elif line.startswith("Time:"):
        time = float(line.split(":")[1].strip().split()[0])
        results[current_p]["time"].append(time)


# Data extraction from qsort-serial.txt
qsort_results = {"Q": [], "bitonic_time": [], "qsort_time": []}

with open(QSORT_PATH, 'r') as file:
    lines = file.readlines()

current_q = None
previous_lines = ["", ""]

for line in lines:
    line = line.strip()
    if line.startswith("Q ="):
        current_q = int(line.split("=")[1].strip())
        qsort_results["Q"].append(current_q)
    elif line.startswith("Time:") and "Serial Bitonic Sort" in previous_lines[0]:
        bitonic_time = float(line.split(":")[1].strip().split()[0])
        qsort_results["bitonic_time"].append(bitonic_time)
    elif line.startswith("Time:") and "QSort" in previous_lines[0]:
        qsort_time = float(line.split(":")[1].strip().split()[0])
        qsort_results["qsort_time"].append(qsort_time)
    previous_lines = [previous_lines[1], line]

# Calculate numbers per second for results
for p in results:
    results[p]["numbers_per_sec"] = []
    for q, time in zip(results[p]["q"], results[p]["time"]):
        numbers_per_sec = 2 ** (p + q) / time
        results[p]["numbers_per_sec"].append(numbers_per_sec)

# Calculate numbers per second for qsort_results
qsort_results["bitonic_numbers_per_sec"] = []
qsort_results["qsort_numbers_per_sec"] = []

for q, bitonic_time, qsort_time in zip(qsort_results["Q"], qsort_results["bitonic_time"], qsort_results["qsort_time"]):
    bitonic_numbers_per_sec = 2 ** q / bitonic_time
    qsort_numbers_per_sec = 2 ** q / qsort_time
    qsort_results["bitonic_numbers_per_sec"].append(bitonic_numbers_per_sec)
    qsort_results["qsort_numbers_per_sec"].append(qsort_numbers_per_sec)

# Plotting
plt.figure(figsize=(10, 6))

for p in results:
    plt.plot(results[p]["q"], results[p]["numbers_per_sec"], label=f'Distributed Bitonic p={p}')

plt.plot(qsort_results["Q"], qsort_results["bitonic_numbers_per_sec"], label='Serial Bitonic', linestyle='--')
plt.plot(qsort_results["Q"], qsort_results["qsort_numbers_per_sec"], label='QSort', linestyle='--')

plt.xlim(21, 27)
plt.xlabel('q value')
plt.ylabel('Numbers per second')
plt.title('Speed Comparison')
plt.legend(loc='lower right')
plt.grid(True)
plt.savefig(SAVE_PATH)
plt.show()