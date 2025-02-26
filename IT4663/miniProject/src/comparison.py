def route_distance(data, result):
    total_distance=0
    for route in result:
        for i in range(len(route)-1):
            total_distance+=data[route[i]][route[i+1]]
    return total_distance

def route_distance_from_path(data, path):
    routes=[]
    with open(path, 'r') as f:
        n = f.readline().strip()
        for i in range(int(n)):
            k= f.readline().split()
            route= [int (x) for x in f.readline().split()]
            routes.append(route)

    return route_distance(data,routes)