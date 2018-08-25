#!/usr/bin/env python3

import sys
import numpy
import matplotlib.pyplot as plt

sys.path.append('..')

from tools import CDF

data = [
    numpy.loadtxt("queue1.csv"),
    numpy.loadtxt("queue2.csv"),
    numpy.loadtxt("queue3.csv"),
    numpy.loadtxt("moodycamel_queue.csv")
]

cdfs = list(map(lambda series: CDF(series), data))

plt.figure(figsize=(4.2, 4.2))

for cdf in cdfs:
    plt.plot(cdf.x(), cdf.y())

plt.xlabel('elements per second [M]')
plt.ylabel('CDF')
plt.xlim([0, 10])
plt.grid(True)
plt.legend(['Q1', 'Q2', 'Q3', 'MC'], loc=4)
plt.margins(0)
plt.savefig("queue_comparison_cdf.pdf", dpi=300)

medians = list(map(lambda series: numpy.median(series), data))
print(medians)

plt.figure(figsize=(4.2, 4.2))
plt.bar(numpy.arange(4), medians)
plt.xticks(numpy.arange(4), ('Q1', 'Q2', 'Q3', 'MC'))
plt.ylabel('elements per second [M]')
plt.savefig("queue_comparison_median.pdf", dpi=300)
