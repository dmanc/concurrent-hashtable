# coding: utf-8

import matplotlib as mpl
mpl.use('Agg')
import numpy as np
import matplotlib.pyplot as plt


x = np.array((0, 1, 2, 4, 8, 16))
print(x)

fig, ax = plt.subplots()


y1 = np.loadtxt('./data/coarse00.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm00.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine00.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 100% W (no resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/100noresizing.png')
plt.show()
plt.clf()


#50%

y1 = np.loadtxt('./data/coarse10.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm10.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine10.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 50% W (no resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/50noresizing.png')
plt.show()
plt.clf()

#25%

y1 = np.loadtxt('./data/coarse20.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm20.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine20.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 25% W (no resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/25noresizing.png')
plt.show()
plt.clf()

#25%

y1 = np.loadtxt('./data/coarse30.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm30.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine30.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 0% W (no resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/0noresizing.png')
plt.show()
plt.clf()


"""" RESIZING """

y1 = np.loadtxt('./data/coarse01.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm01.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine01.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 100% W (resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/100resizing.png')
plt.show()
plt.clf()


#50%

y1 = np.loadtxt('./data/coarse11.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm11.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine11.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 50% W (resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/50resizing.png')
plt.show()
plt.clf()

#25%

y1 = np.loadtxt('./data/coarse21.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm21.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine21.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 25% W (resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/25resizing.png')
plt.show()
plt.clf()

#25%

y1 = np.loadtxt('./data/coarse31.txt', delimiter='\n', unpack=True)
y2 = np.loadtxt('./data/stm31.txt', delimiter='\n', unpack=True)
y3 = np.loadtxt('./data/fine10.txt', delimiter='\n', unpack=True)

print(y1)
print(y2)
print(y3)

index = np.arange(5)
bar_width = 0.2

plt.xticks(index, (1, 2, 4, 8, 16))
plt.title('Scalability 0% W (resizing)')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup vs. Sequential')
plt.bar(index+bar_width*0-.2, y1, width=bar_width, align='center', color='r', label='coarse')
plt.bar(index+bar_width*1-.2, y2, width=bar_width, align='center', color='g', label='stm')
plt.bar(index+bar_width*2-.2, y3, width=bar_width, align='center', color='b', label='fine')
leg = plt.legend(loc='upper left')

# Change to location of the legend.

plt.tight_layout()
plt.savefig('./graphs/0resizing.png')
plt.show()
plt.clf()
