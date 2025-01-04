import os
import matplotlib.pyplot as plt

FILE_PATH = os.path.join(os.path.dirname(__file__), 'results.txt')

SAVE_DIR = os.path.join(os.path.dirname(__file__), '../assets')
SAVE_PATH = os.path.join(SAVE_DIR, 'results.png')

# Data extraction
with open(FILE_PATH, 'r') as file:
    data = file.read()

# Parsing the data
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

# Plotting
plt.figure(figsize=(10, 8))
for p, values in results.items():
    plt.plot(values["q"], values["time"], marker='o', label=f'p = {p}')

plt.xlabel('q (2^q numbers per process)')
plt.ylabel('Execution Time (sec)')
plt.title('Execution Time vs q for different number of processes 2^p')
plt.legend()
plt.grid(True)
plt.savefig(SAVE_PATH)
plt.show()
