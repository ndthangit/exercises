import time

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

    # Passenger data['Request']
    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

    # Parcel data['Request']
    for i in range(1, data['NumParcel'] + 1):
        data['Delivery']['ParcelRequest'].append(
            [i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']])


    data['Request']= [0]*(2 * (data['NumParcel'] + 2*data['NumPassenger'])+1)
    for i, value in enumerate(data['Quantity']):
        data['Request'][i + 1 + data['NumParcel']] = value
        data['Request'][i + 1 + 2 * data['NumParcel'] + data['NumPassenger']] = -value

    return data
def importData2():
    data = {}

    n, m, k = map(int, input().split())
    data['NumParcel'] = n
    data['NumPassenger'] = m
    data['NumTaxis'] = k

    data['Quantity'] = list(map(int, input().split()))
    data['Capacity'] = list(map(int, input().split()))

    data['Matrix'] = [list(map(int, input().split())) for _ in range(2 * (n + m) + 1)]

    data['Depot'] = 0

    data['Delivery'] = {
        'PassengerRequest': [[i, i + n + m] for i in range(1, m + 1)],
        'ParcelRequest': [[i + n, i + 2 * n + m] for i in range(1, n + 1)]
    }

    data['Request'] = [0] * (2 * (n + 2 * m) + 1)
    for i, value in enumerate(data['Quantity']):
        data['Request'][i + 1 + data['NumParcel']] = value
        data['Request'][i + 1 + 2 * data['NumParcel'] + data['NumPassenger']] = -value

    return data
def main():
    # dataPath = "test/test5.txt"  # Replace with your actual data file path
    # data = importData(dataPath)
    # print(data['Request'])
    # print(data['Delivery']['ParcelRequest'])
    data = importData2()
    num_clients = 2 * (data['NumParcel'] + data['NumPassenger'])

    disMin = float('inf')
    for row in data['Matrix']:
        for dis in row:
            if dis < disMin and dis != 0:
                disMin = dis

    visited = [False] * (num_clients + 1)
    firstPoint = [0] * (data['NumTaxis'] + 1)
    nextPoint = [0] * (num_clients + 1)
    curCapacity = [0] * (data['NumTaxis'] + 1)
    num_visited = 0
    minRoute = float('inf')
    curRoute = 0
    nbr = 0
    count =0

    vehicleVar = [0] * (num_clients + 1)
    best_vehicleVar = [-1] * (num_clients + 1)  # Lưu trạng thái tốt nhất của vehicleVar
    best_nextPoint = [0] * (num_clients + 1)    # Lưu trạng thái tốt nhất của nextPoint

    best_routes = []

    def save_routes():
        nonlocal best_routes, best_vehicleVar, best_nextPoint
        routes = []
        for truck in range(1, data['NumTaxis'] + 1):
            route = [0]
            current = firstPoint[truck]
            while current != 0:
                route.append(current)
                current = nextPoint[current]
            route.append(0)
            routes.append(route)
        best_routes = routes
        best_vehicleVar = vehicleVar.copy()  # Lưu lại vehicleVar khi tìm thấy lời giải tốt
        best_nextPoint = nextPoint.copy()     # Lưu lại nextPoint khi tìm thấy lời giải tốt

    firstPoint[0] = 0

    def check_nextPoint(curClient, nextClient, vehicle):
        if nextClient > 0 and visited[nextClient]:
            return False

        if curCapacity[vehicle] + data['Request'][nextClient] > data['Capacity'][vehicle - 1]:
            return False

        if curCapacity[vehicle] + data['Request'][nextClient] < 0:
            return False

        for req in data['Delivery']['PassengerRequest']:
            if curClient == req[0]:
                if nextClient == req[1]:
                    return True
                else:
                    return False
        for req in data['Delivery']['ParcelRequest']:
            if nextClient == req[1] :
                if  visited[req[0]] == False:
                    return False

                if vehicleVar[req[0]] != vehicle  :
                    return False

        return True

    def try_schedule(point, vehicle):
        nonlocal num_visited, curRoute, minRoute, nbr, best_routes, best_vehicleVar, count
        if point == 0:
            if vehicle < data['NumTaxis']:
                try_schedule(firstPoint[vehicle + 1], vehicle + 1)
            return
        for next_client in range(num_clients + 1):
            if check_nextPoint(point, next_client, vehicle):
                visited[next_client] = True
                vehicleVar[next_client] = vehicle
                nextPoint[point] = next_client
                curRoute += data['Matrix'][point][next_client]
                curCapacity[vehicle] += data['Request'][next_client]
                num_visited += 1

                if next_client > 0:
                    predict = curRoute + (num_clients + nbr - num_visited) * disMin
                    if predict < minRoute:
                        try_schedule(next_client, vehicle)
                else:
                    if vehicle == data['NumTaxis']:
                        count += 1
                        if (num_clients + nbr) == num_visited:
                            if curRoute < minRoute:
                                minRoute = curRoute
                                save_routes()  # Cập nhật best_routes và best_vehicleVar
                    else:
                        predict = curRoute + (num_clients + nbr - num_visited) * disMin
                        if predict < minRoute:
                            try_schedule(firstPoint[vehicle + 1], vehicle + 1)

                visited[next_client] = False
                vehicleVar[next_client] = -1
                curRoute -= data['Matrix'][point][next_client]
                curCapacity[vehicle] -= data['Request'][next_client]
                num_visited -= 1

    def check_firstPoint(point, vehicle):
        if point == 0:
            return True
        if point > data['NumPassenger']+data['NumParcel']:
            return False
        if visited[point]:
            return False
        if curCapacity[vehicle] + data['Request'][point] > data['Capacity'][vehicle - 1]:
            return False
        if curCapacity[vehicle] + data['Request'][point] < 0:
            return False
        return True

    def try_firstPoint(vehicle):
        nonlocal num_visited, curRoute, minRoute, nbr
        s = 0
        if firstPoint[vehicle - 1] > 0:
            s = firstPoint[vehicle - 1] + 1
        for client in range(s,num_clients + 1):
            if check_firstPoint(client, vehicle):
                firstPoint[vehicle] = client
                vehicleVar[client] = vehicle
                if client > 0:
                    num_visited += 1
                visited[client] = True
                curRoute += data['Matrix'][0][client]
                curCapacity[vehicle] += data['Request'][client]
                # Gán các điểm trong cùng request cho cùng xe
                for req in data['Delivery']['PassengerRequest']:
                    if client == req[0]:
                        vehicleVar[req[1]] = vehicle
                    elif client == req[1]:
                        vehicleVar[req[0]] = vehicle
                for req in data['Delivery']['ParcelRequest']:
                    if client == req[0]:
                        vehicleVar[req[1]] = vehicle
                    elif client == req[1]:
                        vehicleVar[req[0]] = vehicle

                if vehicle < data['NumTaxis']:
                    try_firstPoint(vehicle + 1)
                else:
                    nbr = num_visited
                    try_schedule(firstPoint[1], 1)

                if client > 0:
                    num_visited -= 1
                visited[client] = False
                vehicleVar[client] = -1
                curRoute -= data['Matrix'][0][client]
                curCapacity[vehicle] -= data['Request'][client]

    start_time  = time.time()

    try_firstPoint(1)
    end_time = time.time()
    # print(f"Time: {end_time - start_time}")
    # print(f"Count: {count}")
    # print(calculate_route_distance(data,best_routes[0],best_routes[1]))
    # print("Minimal total travel distance:", minRoute)
    # for i, route in enumerate(best_routes):
    #     print(f"Vehicle {i + 1}: {' -> '.join(map(str, route))}")
    #
    # # In ra best_vehicleVar thay vì vehicleVar
    # print("\nVehicle assignment for each point (0 is depot):")
    # print("\nNext point information:")
    # for point in range(num_clients + 1):
    #     print(
    #         f"Point {point} -> Next: {best_nextPoint[point]} (Vehicle: {best_vehicleVar[point] if best_vehicleVar[point] != -1 else 'Not assigned'})")
    print(data['NumTaxis'])
    for i, route in enumerate(best_routes):
        print(len(route))
        print(f"{' '.join(map(str, route))}")


if __name__ == "__main__":
    main()
