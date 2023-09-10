import statistics
import matplotlib.pyplot as plt
import numpy as np

mean =[]
stdev = []

dt = open("readings00.txt","r").read().splitlines()
li = [int(i) for i in dt]
mean.append(round(statistics.mean(li)))
stdev.append(round(statistics.stdev(li)))

dt = open("readings01.txt","r").read().splitlines()
li = [int(i) for i in dt]
mean.append(round(statistics.mean(li)))
stdev.append(round(statistics.stdev(li)))

dt = open("readings02.txt","r").read().splitlines()
li = [int(i) for i in dt]
mean.append(round(statistics.mean(li)))
stdev.append(round(statistics.stdev(li)))

dt = open("readings03.txt","r").read().splitlines()
li = [int(i) for i in dt]
mean.append(round(statistics.mean(li)))
stdev.append(round(statistics.stdev(li)))

x = np.arange(4)
ax = plt.subplot(111)
ax.bar(x-0.125, mean, width=0.25, color='b', align='center', label="Mean")
ax.bar(x+0.125, stdev, width=0.25, color='g', align='center', label="Standard Deviation")
ax.legend()
plt.xticks(range(4))
plt.title("Central tendencies of number of cycles for memory access\nProcess runs on Node 0")
plt.ylabel("CPU clock cycles")
plt.xlabel("Node number of memory access")
plt.show()
