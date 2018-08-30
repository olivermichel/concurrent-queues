#!/usr/bin/env python3

import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from cycler import cycler

# sys.path.append('..')

# from tools import CDF

format = { 'names': ('count', 'time', 'throughput'), 'formats': ('u4','f4','f4') }

data = {
    'queue1': np.loadtxt("out/queue1.csv", dtype=format, delimiter=','),
    'queue2': np.loadtxt("out/queue2.csv", dtype=format, delimiter=','),
    'queue3': np.loadtxt("out/queue3.csv", dtype=format, delimiter=','),
    'moodycamel_queue': np.loadtxt("out/moodycamel_queue.csv", dtype=format, delimiter=','),
    'queue4': np.loadtxt("out/queue4.csv", dtype=format, delimiter=','),
    'queue5': np.loadtxt("out/queue5.csv", dtype=format, delimiter=',')
}

#TODO: needs to go in rc file

font = {'family': 'serif', 'serif': ['Times New Roman'], 'size': 12}
lines = {'linewidth': 2}
matplotlib.rc('font', **font)
matplotlib.rc('lines', **lines)


default_cycler = (cycler(color=['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728',
                                '#9467bd', '#8c564b', '#e377c2', '#7f7f7f',
                                '#bcbd22', '#17becf']))

matplotlib.rc('axes', prop_cycle=default_cycler)
matplotlib.rc('ytick', color='#222222')
matplotlib.rc('xtick', color='#222222')
matplotlib.rc('legend', edgecolor='#222222', fontsize=11)
matplotlib.rc('figure', figsize=(6, 2.5))

for q in data:
    counts, edges = np.histogram(data[q][:]['throughput'], bins=100)
    cum = np.cumsum(counts)
    plt.plot(edges[1:], cum/cum[-1])

plt.xlabel('elements per second [M]')
plt.ylabel('CDF')
plt.xlim([0, 24])
plt.ylim([0, 1])
plt.grid(True)
plt.margins(0)
plt.legend(['linked list, locks', 'array, locks', 'linked list, lock-free', 'moodycamel',
            'array, lock-free', 'array, lock-free 2'], loc='lower right')
plt.show()
