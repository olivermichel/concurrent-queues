#!/usr/bin/env python3

# import matplotlib
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("out/queue5_detail.csv")
print(data.max())

# simple buffer size plot
plt.plot(data)
plt.show()
