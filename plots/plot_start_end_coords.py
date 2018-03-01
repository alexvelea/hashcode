import numpy as np
import matplotlib
matplotlib.use('tkagg')
import matplotlib.pyplot as plt
import random
matplotlib.rcParams['axes.unicode_minus'] = False
fig, ax = plt.subplots()


# constants
stop_after = -1 # stop after stop_after points added
put_percent = 10 # add only 1 / put_percent points


# read first line
r, c, f, n, b, t = raw_input().split(' ')
r, c, f, n, b, t = [int(x) for x in [r, c, f, n, b, t]]

# add a yellow point at (r, c) to see where the graph ends
ax.plot(r, c, 'yo')

# read other lines
counter = 0
for i in range(n):
    a, b, x, y, s, f = raw_input().split(' ')
    a, b, x, y, s, f = [int(x) for x in [a, b, x, y, s, f]]

    # don't put too much, it's taking time to render; jump some of them
    if random.random() > (1.0 / put_percent):
        continue

    # plot point (a, b) with 'ro' ('r' from red, 'o' from put a point there)
    ax.plot(a, b, 'ro')
    ax.plot(x, y, 'bo')
    counter += 1

    # stop after stop_after prints
    if counter == stop_after:
        break

plt.show()
