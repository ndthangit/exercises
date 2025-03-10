import sys

from ortools.linear_solver import pywraplp


# def importData(dataPath):
#     data = {}
#     with open(dataPath, 'r') as f:
#         n, k, q = f.readline().split()
#         data['NumPoint'] = int(n)
#         data['NumTruck'] = int(k)
#         data['Capacity'] = int(q)
#         data['Request'] = [int(x) for x in f.readline().split()]
#         data['Request'].insert(0, 0)  # Ensure request array aligns with 1-based indexing
#         data['Matrix'] = []
#         for _ in range(data['NumPoint'] + 1):
#             data['Matrix'].append([int(x) for x in f.readline().split()])
#     return data

def importData(dataPath):
    data ={}
    with open(dataPath, 'r') as f:
        n,m,k = f.readline().split()
        data['NumParcel'] =int(n)
        data['NumPassenger'] =int(m)
        data['NumTaxis'] =int(k)
        data['Quantity']= [int (x) for x in f.readline().split()]
        data['Capacity']=[int (x) for x in f.readline().split()]


        data['Matrix']=[]
        for x in range(2 * (data ['NumParcel'] + data['NumPassenger']) + 1):
            data['Matrix'].append([int (x) for x in f.readline().split()])

    data['Depot']=0

    data['Delivery'] = {
        'PassengerRequest': [],
        'ParcelRequest': []
    }

    # Passenger request
    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

    # Parcel request
    for i in range(1, data['NumParcel'] + 1):
        data['Delivery']['ParcelRequest'].append(
            [i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']])

    data['Request']= [0]*(2 * (data['NumParcel'] + 2*data['NumPassenger'])+1)
    for i in data['Quantity']:
        data['Request'][i + data['NumParcel']] = i
        data['Request'][i + 2 * data['NumParcel'] + data['NumPassenger']] = -i

    return data


def check_next_point(next_client, vehicle):
    if next_client > 0 and visited[next_client]:
        return False
    if cur_capacity[vehicle] + request[next_client] > data['Capacity'][vehicle]:
        return False
    return True


def try_schedule(point, vehicle):
    global cur_route, min_route, num_visited

    if point == 0:
        if vehicle < num_trucks:
            try_schedule(first_point[vehicle + 1], vehicle + 1)
        return

    for next_client in range(num_clients + 1):
        if check_next_point(next_client, vehicle):
            visited[next_client] = True
            next_point[vehicle] = next_client
            cur_route += data['Matrix'][point][next_client]
            cur_capacity[vehicle] += request[next_client]
            num_visited += 1

            if next_client > 0:
                predict = cur_route + (num_clients + nbr - num_visited) * dis_min
                if predict < min_route:
                    try_schedule(next_client, vehicle)
            else:
                if vehicle == num_trucks:
                    if (num_clients + nbr) == num_visited:
                        min_route = min(min_route, cur_route)
                else:
                    predict = cur_route + (num_clients + nbr - num_visited) * dis_min
                    if predict < min_route:
                        try_schedule(first_point[vehicle + 1], vehicle + 1)

            visited[next_client] = False
            cur_route -= data['Matrix'][point][next_client]
            cur_capacity[vehicle] -= request[next_client]
            num_visited -= 1


def check_first_point(point, vehicle):
    if point == 0:
        return True
    if visited[point]:
        return False
    if cur_capacity[vehicle] + request[point] > data['Capacity'][vehicle]:
        return False
    return True


def try_first_point(vehicle):
    global nbr, cur_route, num_visited
    s = 0
    if first_point[vehicle - 1] > 0:
        s = first_point[vehicle - 1] + 1

    for client in range(s, num_clients + 1):
        if check_first_point(client, vehicle):
            first_point[vehicle] = client
            if client > 0:
                num_visited += 1
            visited[client] = True
            cur_route += data['Matrix'][0][client]
            cur_capacity[vehicle] += request[client]

            if vehicle < num_trucks:
                try_first_point(vehicle + 1)
            else:
                nbr = num_visited
                try_schedule(first_point[1], 1)

            if client > 0:
                num_visited -= 1
            visited[client] = False
            cur_route -= data['Matrix'][0][client]
            cur_capacity[vehicle] -= request[client]


if __name__ == "__main__":
    sys.setrecursionlimit(10 ** 6)

    data = importData('test/test1.txt')
    solver = pywraplp.Solver.CreateSolver('SCIP')

