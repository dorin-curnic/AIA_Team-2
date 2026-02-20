import os
import subprocess
import re
from collections import defaultdict
import statistics

algorithms = ["insertion", "shell", "intro", "merge", "radix"]
sizes = [100, 1000, 10000, 100000, 1000000]
types = ["random", "asc", "desc", "half-sorted", "mixed"]
trials = 5

results = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))

print("Starting benchmarks...")
for alg in algorithms:
    print(f"Running {alg}...")
    for size in sizes:
        # Skip excessive times for insertion sort
        if alg == "insertion" and size > 10000:
            print(f"  Skipping {alg} for size {size} (too slow)")
            continue
        print(f"  Size: {size}")
        for typ in types:
            input_file = f"data/input_{size}_{typ}.txt"
            if not os.path.exists(input_file):
                continue
            for t in range(trials):
                cmd = f".\sorter.exe -a {alg} -s {size} -i {input_file}"
                try:
                    output = subprocess.check_output(cmd, shell=True, text=True)
                    match = re.search(r"Sort Time \(Computation\):\s+(\d+)", output)
                    if match:
                        time_us = int(match.group(1))
                        results[alg][size][typ].append(time_us)
                except subprocess.CalledProcessError:
                    pass

print("Writing results to benchmark_results.md...")
with open("benchmark_results.md", "w") as f:
    for alg in algorithms:
        f.write(f"### {alg.capitalize()} Sort\n\n")
        f.write("| Size | Random (µs) | Ascending (µs) | Descending (µs) | Half-Sorted (µs) | Mixed (µs) |\n")
        f.write("|---|---|---|---|---|---|\n")
        for size in sizes:
            row = [str(size)]
            for typ in types:
                times = results[alg].get(size, {}).get(typ, [])
                if times:
                    avg = statistics.median(times) # Use median to filter outliers
                    row.append(f"{avg:.0f}")
                else:
                    row.append("N/A")
            f.write("| " + " | ".join(row) + " |\n")
        f.write("\n")
print("Done!")
