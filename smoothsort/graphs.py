import sys
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math
import numpy as np

file = sys.argv[1]
file2 = sys.argv[2]

fs = file
fs2 = file2

f = open(fs, 'r')
f2 = open(fs2, 'r')

x, y = [0], [0]
l = 0
m,n = 0,0

for l in f:
    row = l.split()
    m += float(row[0])
    n += float(row[1])
    x.append(float(row[0]))
    y.append(float(row[1]))

x2, y2 = [0], [0]
l2 = 0
m2,n2 = 0,0

for l2 in f2:
    row = l2.split()
    m2 += float(row[0])
    n2 += float(row[1])
    x2.append(float(row[0]))
    y2.append(float(row[1]))


f.close()
f2.close()

fig, ax1 = plt.subplots(
    nrows = 1, ncols = 1,
    figsize = (12, 12)
)

t = np.linspace(0.1, max(x))
j = np.linspace(0.1, max(x))

a = np.log2(t) * t

v = t ** 2

o = j

x.pop(0)
y.pop(0)

ax1.plot(x, y, label = 'Radix')
ax1.plot(x2, y2, label = 'Smootshort')
ax1.plot(t, a, label  = 'N logN')
ax1.plot(j, o, label = 'N')


ax1.grid(which = 'major',
         color = 'k')

ax1.minorticks_on()

ax1.grid(which = 'minor',
         color = 'gray',
         linestyle = ':')

ax1.legend()

ax1.set_xlabel('Количество элементов')
ax1.set_ylabel('Затраченное время, мкс')  



plt.title("Лучший случай")
plt.show() 