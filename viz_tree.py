import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
sns.set()
def moving_average(x, w):
    return np.convolve(x, np.ones(w), 'valid') / w

data = pd.read_csv('time_tree_random.txt', header=None, sep=' ')

nb = []
#print(data.shape)
for i in range(1, data.shape[1]):
    j = 1
    nb.append(np.ndarray(data[data[0] == 0].shape[0], dtype=float))
    while (True):
        data_tmp = data[data[0] == j]
        if(data_tmp.shape[0] <= 0):
            nb[i-1]/=(j-1)
            break
        j+=1
        nb[i-1] += np.array(data_tmp[i])

index = 6
labels = ['insert - O(log(N))', 'contains - O(log(N))', 'remove - O(log(N))', 'insert - O(log(N))', 'contains - O(log(N))', 'remove - O(log(N))']
min_v = [0,0,0,0,0,0,0]
max_v = [5000,2000,3000,5000,2000,3000]
plt.scatter(nb[0], nb[index], s=1, alpha=1)
plt.ylim(0, max_v[index-1])
plt.xlabel('number of elements')
plt.ylabel('execution time')
plt.suptitle(labels[index-1])
plt.show()