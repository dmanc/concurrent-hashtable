# coding: utf-8

import matplotlib as mpl
mpl.use('Agg')
import numpy as np
import matplotlib.pyplot as plt


x = np.array((0, 1, 2, 4, 8, 16))
print(x)

fig, ax = plt.subplots()


y1 = np.loadtxt('./data/coarse0.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm0.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine0.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 100% W')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/100.png')
plt.show()
plt.clf()


#50%

y1 = np.loadtxt('./data/coarse1.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm1.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine1.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 50% W')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/50.png')
plt.show()
plt.clf()

#25%

y1 = np.loadtxt('./data/coarse2.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm2.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine2.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 25% W')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/25.png')
plt.show()
plt.clf()

#25%

y1 = np.loadtxt('./data/coarse3.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm3.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine3.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 0% W')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/0.png')
plt.show()
plt.clf()
