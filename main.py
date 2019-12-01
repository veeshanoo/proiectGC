import matplotlib.pyplot as plt
from lxml.doctestcompare import strip
from random import randrange


def rc():
    return randrange(100) / 255


coord = []

initial_coord = []
viewx = 0
viewy = 0

fin = open("snake.in", "r")
n = int(fin.readline())
poly = []
for el in range(0, n):
    line = strip(fin.readline())
    print(line.split(" "))
    (x, y) = line.split(" ")

    initial_coord.append([float(x), float(y)])

(viewx, viewy) = strip(fin.readline()).split(" ")

fin.close()

with open("tst.out", "r") as fin:
    for line in fin.readlines():
        (fi, se) = line.split(" ")
        coord.append([float(fi), float(se)])
        # print(fi, se)

initial_coord.append(initial_coord[0])
coord.append(coord[0])  # repeat the first point to create a 'closed loop'

xs, ys = zip(*coord)  # create lists of x and y values
ixs, iys = zip(*initial_coord)

viewx = float(viewx)
viewy = float(viewy)

plt.figure()
print(viewx, viewy)

plt.fill(xs, ys, color="red")
plt.plot(ixs, iys, color="green")

# fig, ax = plt.subplots()
ax = plt.gca()

circle = plt.Circle((viewx, viewy), 0.01, color='yellow')
# for point in coord:
#     plt.fill([viewx, point[0]], [viewy, point[1]], color="black")

triangles = [[[viewx, viewy], coord[i], coord[i + 1]] for i in range(0, len(coord) - 1)]

for tr in triangles:
    plt.fill([x[0] for x in tr], [x[1] for x in tr], color=(rc(), rc(), rc()))

ax.add_artist(circle)

plt.show()  # if you need...
