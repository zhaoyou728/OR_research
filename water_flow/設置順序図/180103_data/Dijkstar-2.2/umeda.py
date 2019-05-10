from dijkstar import Graph, find_path

data_file_path = "../umeda_mesh_data_org.csv"
#target_vertex_file_path = "./60_pump_inactive.txt"
#shortest_path_file_path = "./60_inactive_shortest_path.txt"

mesh_org_data = []
mesh_data = []
target_vertex = []

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
        mesh_org_data.append(d)
    f.close()
    print("Done.")
    return mesh_num

def make_route_data(mesh_num):
    print("Making route org data...")
    for d in mesh_org_data:
        if d[0] % 100 == 0:
            print("(route org) mesh: " + (str)(d[0]) + "/" + (str)(mesh_num))
        if d[7] >= 12:
            continue
        for i in range(1, 5):
            if d[i] <= mesh_num and mesh_org_data[d[i] - 1][7] < 12:
                if [d[0], d[i]] not in mesh_data:
                    mesh_data.append([d[0], d[i]])
                if [d[i], d[0]] not in mesh_data:
                    mesh_data.append([d[i], d[0]])
    print("Done.")
    ##
    print("Deleting wall part...")
    for d in mesh_org_data:
        if d[9] == 1:
            if [d[0], d[2]] in mesh_data:
                print("Deleting [" + (str)(d[0]) + ", " + (str)(d[2]) + "]" )
                mesh_data.remove([d[0], d[2]])
            if [d[2], d[0]] in mesh_data:
                print("Deleting [" + (str)(d[2]) + ", " + (str)(d[0]) + "]" )
                mesh_data.remove([d[2], d[0]])
        if d[8] == 1:
            if [d[0], d[3]] in mesh_data:
                print("Deleting [" + (str)(d[0]) + ", " + (str)(d[3]) + "]" )
                mesh_data.remove([d[0], d[3]])
            if [d[3], d[0]] in mesh_data:
                print("Deleting [" + (str)(d[3]) + ", " + (str)(d[0]) + "]" )
                mesh_data.remove([d[3], d[0]])
    print("Done.")

def make_target_vertex_list(target_vertex_file_path):
    target_vertex.clear()
    print("Reading " + target_vertex_file_path + "...")
    f = open(target_vertex_file_path, 'r')
    for line in f:
        line = line.rstrip()
        target_vertex.append((int)(line))
    f.close()
#    f = open(shortest_path_file_path, 'w')
#    for i in range(len(target_vertex)):
#        for j in range(i + 1, len(target_vertex)):
#            f.write('[' + (str)(target_vertex[i]) + ', ' + (str)(target_vertex[j]) + ']\n')
#    f.write((str)(target_vertex))
#    f.close()
    print("Done.")

def find_shortest_path(shortest_path_file_path):
    graph = Graph()
#graph.add_edge(1, 2, {'cost': 1})
#graph.add_edge(2, 3, {'cost': 2})
#nodes, edges, costs, total_cost = find_path(graph, 1, 3, cost_func=cost_func)
    for md in mesh_data:
        graph.add_edge(md[0], md[1], {'cost': 2})
#    graph.add_edge('a', 'b', {'cost': 1})
#    graph.add_edge('b', 'c', {'cost': 2})
    cost_func = lambda u, v, e, prev_e: e['cost']
    
#    nodes, edges, costs, total_cost = find_path(graph, 'a', 'c', cost_func=cost_func)
    f = open(shortest_path_file_path, 'w')
    for i in range(len(target_vertex)):
        for j in range(i + 1, len(target_vertex)):
            nodes, edges, costs, total_cost = find_path(graph, target_vertex[i], target_vertex[j], cost_func=cost_func)
            f.write('@ [' + (str)(target_vertex[i]) + ', ' + (str)(target_vertex[j]) + '] ' + (str)(total_cost) + '\n')
            f.write((str)(nodes))
            f.write('\n')
    f.close()
#    print(edges)
#    print(costs)

##############################

mesh_num = read_map_data(data_file_path)
make_route_data(mesh_num)

#target_vertex_file_path_list = ['60_pump_active.txt', '60_pump_inactive.txt', '120_pump_active.txt', '120_pump_inactive.txt', '180_pump_active.txt', '180_pump_inactive.txt']
#shortest_path_file_path_list = ['60_active_spath.txt', '60_inactive_spath.txt', '120_active_spath.txt', '120_inactive_spath.txt', '180_active_spath.txt', '180_inactive_spath.txt']
target_vertex_file_path_list = ['whity_120_with_pump.txt']
shortest_path_file_path_list = ['whity_120_with_pump_spath.txt']

for i in range(len(target_vertex_file_path_list)):
    make_target_vertex_list(target_vertex_file_path_list[i])
    find_shortest_path(shortest_path_file_path_list[i])

##############################
