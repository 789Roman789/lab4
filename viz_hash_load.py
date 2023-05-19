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

for i in range(3, len(nb)):
    nb[i] = np.array([x for _,x in sorted(zip(nb[2]/nb[1],nb[i]))])

#load = load[cond]
#data = data[::1000]
#r = data[(data[1]/data[2] > 0.6) & (data[1]/data[2] < 0.8)]
#insTime = [x for _,x in sorted(zip(nb[2]/nb[1],nb[9]))]
index = 12
plt.scatter(load, nb[index], s=2, alpha=0.15)
max_v = [13000, 300, 300, 5000, 8000, 13000, 300, 300, 5000, 8000]
min_v = [0, 50, 50, 0, 0, 0, 50, 50, 0, 0]
labels = ['insert', 'contains existent', 'contains nonexistent', 'remove existent', 'remove nonexistent', 'insert', 'contains existent', 'contains nonexistent', 'remove existent', 'remove nonexistent']
plt.suptitle(labels[index-3])
plt.ylim(min_v[index-3], max_v[index-3])
plt.xlabel("load factor")
plt.ylabel("execution time")


#plt.scatter(moving_average(load, 200), moving_average(nb[3], 200), s=1, alpha=0.5)

plt.show()