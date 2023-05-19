import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
sns.set()
def moving_average(x, w):
    return np.convolve(x, np.ones(w), 'valid') / w

data = pd.read_csv('time_hashSet.txt', header=None, sep=' ')

nb = []
for i in range(1, data.shape[1]):
    j = 0
    nb.append(np.ndarray(data[data[0] == 0].shape[0], dtype=float))
    while (True):
        data_tmp = data[data[0] == j]
        if(data_tmp.shape[0] <= 0):
            nb[i-1]/=j
            break
        j+=1
        nb[i-1] += np.array(data_tmp[i])

load = np.array(sorted(nb[2]/nb[1]))

cond = (load>0.6) & (load < 0.7)

for i in range(3, len(nb)):
    nb[i] = np.array([x for _,x in sorted(zip(nb[2]/nb[1],nb[i]))])
for i in range(len(nb)):
    nb[i] = nb[i][cond]

load = load[cond]
#data = data[::1000]
#r = data[(data[1]/data[2] > 0.6) & (data[1]/data[2] < 0.8)]
#insTime = [x for _,x in sorted(zip(nb[2]/nb[1],nb[9]))]
#plt.scatter(nb[2]/nb[1], nb[8], s=1, alpha=0.3)


index = 12
labels = ['insert', 'contains existent', 'contains nonexistent', 'remove existent', 'remove nonexistent', 'insert', 'contains existent', 'contains nonexistent', 'remove existent', 'remove nonexistent']

max_v = [10000, 10000, 10000,10000, 250, 250, 3500, 5200,10000, 250, 250, 3500, 5200]
min_v = [0, 0, 0, 4600, 100, 100, 1800,2600,4600, 100, 100, 1800,2600]
plt.scatter(nb[0], nb[index], c=load, s=40, alpha=0.5,edgecolors=None,cmap='magma')
plt.colorbar(label = 'load factor')
plt.xlabel('number of elements')
plt.ylabel('execution time')
plt.suptitle(labels[index-3])
plt.ylim(min_v[index],max_v[index])

#plt.scatter(moving_average(load, 200), moving_average(nb[3], 200), s=1, alpha=0.5)

plt.show()