import pandas as pd
import matplotlib.pyplot as plt

plt.figure(figsize=(10, 6))
df = pd.read_csv("memory_bandwidth.csv")
plt.plot(df["Array Size (bytes)"], df["Bandwidth (GB/s)"], marker='o', linestyle='-', color='b')
plt.axvline(32000,label = "L1d",color ="yellow")
plt.axvline(1024000,label = "L2",color ="lightgreen")
plt.axvline(25344000,label = "L3",color ="red")
plt.xscale("log",base = 2)
plt.title("Memory Bandwidth vs. Array Size")
plt.xlabel("Array Size (bytes)")
plt.ylabel("Bandwidth (GB/s)")
plt.savefig("memory_bandwidth_plot.png")