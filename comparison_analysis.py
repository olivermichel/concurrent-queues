#!/usr/bin/env python3

import matplotlib
import numpy as np
import matplotlib.pyplot as plt

#
# import sys
# import numpy
# import matplotlib.pyplot as plt

# sys.path.append('..')

# from tools import CDF

format = { 'names': ('count', 'time', 'throughput'), 'formats': ('u4','f4','f4') }

data = {
    'queue1': np.loadtxt("out/queue1.csv", dtype=format, delimiter=','),
    'queue2': np.loadtxt("out/queue2.csv", dtype=format, delimiter=','),
    'queue3': np.loadtxt("out/queue3.csv", dtype=format, delimiter=','),
    'moodycamel_queue': np.loadtxt("out/moodycamel_queue.csv", dtype=format, delimiter=',')
}

plt.hist(
    [data['queue1'][:]['throughput'],
     data['queue2'][:]['throughput'],
     data['queue3'][:]['throughput'],
     data['moodycamel_queue'][:]['throughput']],
    normed=True, cumulative=True, histtype='step')
plt.xlabel('elements per second [M]')
plt.ylabel('CDF')
plt.show()

#
# cdfs = list(map(lambda series: CDF(series), data))
#
# plt.figure(figsize=(4.2, 4.2))
#
# for cdf in cdfs:
#     plt.plot(cdf.x(), cdf.y())
#
# plt.xlabel('elements per second [M]')
# plt.ylabel('CDF')
# plt.xlim([0, 10])
# plt.grid(True)
# plt.legend(['Q1', 'Q2', 'Q3', 'MC'], loc=4)
# plt.margins(0)
# plt.savefig("queue_comparison_cdf.pdf", dpi=300)
#
# medians = list(map(lambda series: numpy.median(series), data))
# print(medians)
#
# plt.figure(figsize=(4.2, 4.2))
# plt.bar(numpy.arange(4), medians)
# plt.xticks(numpy.arange(4), ('Q1', 'Q2', 'Q3', 'MC'))
# plt.ylabel('elements per second [M]')
# plt.savefig("queue_comparison_median.pdf", dpi=300)
