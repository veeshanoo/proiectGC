import matplotlib.pyplot as plt

coord = []

initial_coord = []
viewx = 0
viewy = 0

with open("tst.in", "r") as fin:
    for line in fin.readlines()[:-1]:
        if len(line.split(" ")) != 2:
            continue
        (fi, se) = line.split(" ")
        initial_coord.append([float(fi), float(se)])


with open("tst.in", "r") as fin:
    (viewx, viewy) = fin.readlines()[-1].split(" ")
# (viewx, viewy) = fin.readlines()[-1].split(" ")

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

circle = plt.Circle((viewx, viewy), 0.2, color='black')

ax.add_artist(circle)

plt.show()  # if you need...
