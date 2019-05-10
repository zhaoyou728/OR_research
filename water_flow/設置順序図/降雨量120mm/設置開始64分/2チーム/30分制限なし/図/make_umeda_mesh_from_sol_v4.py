#
# Usage: python make_umeda_mesh_from_sol.py [Gurobi sol_file_path] [start_time] [pdf_file_path]
#

import sys
import re
import numpy as np
import matplotlib.pyplot as plt

argvs = sys.argv
argc = len(argvs)

layer = []
team = []
mesh_data = []
time_data = []
quiver_data = []

x_data = {}
t_data = {}

sol_file_path = argvs[1]
start_time = (float)(argvs[2])
map_file_path = argvs[3]

data_file_path = "umeda_mesh_data_org.csv"

x_width = 2
y_width = 2

whity_with_flow = [1592, 1813, 10688, 8169, 10635, 10417, 8236, 6205, 6686, 3527, 8210, 8643, 10955, 11356, 12593, 13107, 11087, 15365, 14140, 17207, 15728]
whity_without_flow = [9883, 10129, 10367, 11856, 12848, 12224, 13037, 14461, 11407, 12670, 13420, 14605, 16008, 16230]
whity_with_flow_time = [85, 86, 112, 90, 85, 94, 75, 64, 93, 106, 109, 78, 95, 95, 98, 100, 84, 102, 80, 97, 77]

quiver_color = ['darkgreen', 'chocolate', 'darkviolet', 'darkred', 'darkorange', 'darkgray']

def make_layer_team_data(sol_file_path):
    f = open(sol_file_path)
    for line in f:
        m = re.search(r'd[\(\[]([0-9]*),([a-z]*)[\)\]]', line)
        if m:
            if m.group(1) not in layer:
                layer.append(m.group(1))
            if m.group(2) not in team:
                team.append(m.group(2))
    f.close()
    print(layer)
    print(team)

def extract_x_data(sol_file_path):
    f = open(sol_file_path)
    for line in f:
        m = re.search(r'x[\(\[]([0-9]*),([0-9]*),([a-z]*)[\)\]] ([1-9].*)', line)
        if m and (float)(m.group(4)) > 0.5:
            x_data[(m.group(2), m.group(3))] = m.group(1)
            print(m.group(2), m.group(3))
    f.close()
    print(x_data)

def extract_t_data(sol_file_path):
    f = open(sol_file_path)
    for line in f:
        line = line.rstrip()
        m = re.search(r't[\(\[]([0-9]*),([a-z]*)[\)\]] (.*)', line)
        if m:
            t_data[(m.group(1), m.group(2))] = (float)(m.group(3))
    f.close()
    print(t_data)

def make_time_data():
    for l in layer:
        for t in team:
            my_key = (l, t)
            if my_key in x_data:
                ent = x_data[my_key]
                fin_time = t_data[my_key] + start_time
                idx = whity_with_flow.index((int)(ent))
                time_data.append([(int)(ent), fin_time, whity_with_flow_time[idx]])
                print(ent + ',' + (str)(fin_time) + ',' + (str)(whity_with_flow_time[idx]))

def make_quiver_data():
    t_idx = -1
    for t in team:
        t_idx = t_idx + 1
        prev = x_data[('0', t)]
        for l in range(1, len(layer)):
            my_key = ((str)(l), (str)(t))
            print(my_key)
            if my_key in x_data:
                next = x_data[my_key]
                quiver_data.append([(int)(prev), (int)(next), quiver_color[t_idx]])
                print(prev + ',' + next + ',' + quiver_color[t_idx])
                prev = next
            else:
                break
    print(quiver_data)

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
    ent_cnt = 0
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
            ent_pos = -1
            for i in range(len(time_data)):
                if d[0] == (int)(time_data[i][0]):
                    ent_pos = i
                    break
            if (float)(time_data[i][1]) > (float)(time_data[i][2]):
                plt.fill([x, x + x_width * 3.0, x + x_width * 3.0, x], [y, y, y + y_width * 3.0, y + y_width * 3.0], color="red")
                plt.text(x + 6, y + 6, (str)(d[0]), fontsize = 6, color="red")
                plt.text(x_max - 125 + (ent_cnt % 2) * 50, y_max - 25 - (int)(ent_cnt/2) * 10, '(' + (str)(d[0]) + ') ' + "{0:.2f}".format((float)(time_data[i][1])) + '/' + (str)(time_data[i][2]), fontsize = 6, color="red")
            else:
                plt.fill([x, x + x_width * 1.5, x + x_width * 1.5, x], [y, y, y + y_width * 1.5, y + y_width * 1.5], color="lime")
                plt.text(x + 4, y, (str)(d[0]), fontsize = 6, color="green")
                plt.text(x_max - 125 + (ent_cnt % 2) * 50, y_max - 25 - (int)(ent_cnt/2) * 10, '(' + (str)(d[0]) + ') ' + "{0:.2f}".format((float)(time_data[i][1])) + '/' + (str)(time_data[i][2]), fontsize = 6, color="green")
            ent_cnt = ent_cnt + 1
##            plt.text(x + 4, y, (str)(d[0]), fontsize = 6)
#        if d[0] in whity_without_flow:
#            plt.fill([x, x + x_width * 1.5, x + x_width * 1.5, x], [y, y, y + y_width * 1.5, y + y_width * 1.5], color="blue")
##            plt.text(x + 4, y, (str)(d[0]), fontsize = 6)
    print("Done.")

def append_quiver_data():
    print("Making quiver data...")
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

make_layer_team_data(sol_file_path)
extract_x_data(sol_file_path)
extract_t_data(sol_file_path)
make_time_data()
make_quiver_data()

mesh_num = read_map_data(data_file_path)
make_map_data(mesh_num, 300, 550, 300, 600)
append_quiver_data()
draw_map(map_file_path)
