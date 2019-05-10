import numpy as np
import matplotlib.pyplot as plt

mesh_data = []
data_file_path = "umeda_mesh_data_org.csv"
quiver_file_path = "quiver_data_st64_t6_30_obj.csv"
map_file_path = "quiver_data_st64_t6_30_obj.pdf"
x_width = 2
y_width = 2

whity_with_flow = [1592, 1813, 10688, 8169, 10635, 10417, 8236, 6205, 6686, 3527, 8210, 8643, 10955, 11356, 12593, 13107, 11087, 15365, 14140, 17207, 15728]
whity_without_flow = [9883, 10129, 10367, 11856, 12848, 12224, 13037, 14461, 11407, 12670, 13420, 14605, 16008, 16230]

def read_map_data(data_file_path):
    print("Reading " + data_file_path + "...")
    mesh_num = 0
    f = open(data_file_path)
    for line in f:
        mesh_num += 1
        line = line.rstrip()
        d = line.split(',')
        for i in range(10):
            d[i] = (int)(d[i])
        for i in range(10,len(d)):
            d[i] = (float)(d[i])
        mesh_data.append(d)
    f.close()
    print("Done.")
    return mesh_num

def make_map_data(mesh_num, x_min = 0, x_max = 9999, y_min = 0, y_max = 9999):
    print("Making drawing data...")
    plt.axes().set_aspect('equal', 'datalim')
    fig, ax = plt.subplots()
    ax.tick_params(labelbottom="off", bottom="off")
    ax.tick_params(labelleft="off", left="off")
    for d in mesh_data:
        if d[0] % 100 == 0:
            print("(map) mesh: " + (str)(d[0]) + "/" + (str)(mesh_num))
        x = d[5]
        y = d[6]
        if x < x_min or x >= x_max or y < y_min or y >= y_max:
            continue
        if d[1] > mesh_num:
            plt.plot([x + 1, x + 1], [y, y + 1], color = 'k', linestyle = '-', linewidth = '0.5')
        if d[2] > mesh_num or d[9] == 1:
            plt.plot([x, x + 1], [y, y], color = 'k', linestyle = '-', linewidth = '0.5')
        if d[3] > mesh_num or d[8] == 1:
            plt.plot([x, x], [y, y + 1], color = 'k', linestyle = '-', linewidth = '0.5')
        if d[4] > mesh_num:
            plt.plot([x, x + 1], [y + 1, y + 1], color = 'k', linestyle = '-', linewidth = '0.5')
#        if d[7] == 1:
#            plt.fill([x, x + x_width * 1.5, x + x_width * 1.5, x], [y, y, y + y_width * 1.5, y + y_width * 1.5], color="green")
#            plt.text(x + 4, y, (str)(d[0]), fontsize = 6)
        if d[0] in whity_with_flow:
            plt.fill([x, x + x_width * 1.5, x + x_width * 1.5, x], [y, y, y + y_width * 1.5, y + y_width * 1.5], color="red")
        if d[0] == 8236 or d[0] == 6205:
            plt.fill([x, x + x_width * 3.0, x + x_width * 3.0, x], [y, y, y + y_width * 3.0, y + y_width * 3.0], color="lime")
##            plt.text(x + 4, y, (str)(d[0]), fontsize = 6)
#        if d[0] in whity_without_flow:
#            plt.fill([x, x + x_width * 1.5, x + x_width * 1.5, x], [y, y, y + y_width * 1.5, y + y_width * 1.5], color="blue")
##            plt.text(x + 4, y, (str)(d[0]), fontsize = 6)
    print("Done.")

def make_quiver_data(quiver_file_path):
    print("Making quiver data...")
    quiver_data = []
    f = open(quiver_file_path)
    for line in f:
        line = line.rstrip()
        q = line.split(',')
        for i in range(len(q) - 1):
            q[i] = (int)(q[i])
        quiver_data.append(q)
    f.close()
    for q in quiver_data:
        s = q[0]
        d = q[1]
        sx = mesh_data[s - 1][5]
        sy = mesh_data[s - 1][6]
        dx = mesh_data[d - 1][5]
        dy = mesh_data[d - 1][6]
        plt.quiver(sx, sy, dx - sx, dy - sy, angles='xy', scale_units='xy', color=q[2], scale = 1.0, width=0.003)
    print("Done.")

def draw_map(map_file_path):
    print("Drawing " + map_file_path + "...")
    plt.savefig(map_file_path)
    print("Done.")

##############################

mesh_num = read_map_data(data_file_path)

make_map_data(mesh_num, 300, 550, 300, 600)
#make_map_data(mesh_num)

make_quiver_data(quiver_file_path)

draw_map(map_file_path)
