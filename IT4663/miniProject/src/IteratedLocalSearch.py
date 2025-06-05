import copy
import random
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
    # # print(data['Request'])
    # print(data['Delivery']['ParcelRequest'])
    data = importData2()

    def calculateRouteDistance(route):
        distance = 0
        for i in range(len(route) - 1):
            distance += data['Matrix'][route[i]][route[i + 1]]
        return distance
    def calculateTotalRoute(routes):
        return sum(calculateRouteDistance(route) for route in routes)

    def isFeasible(routes):
        all_points = set()

        for idx, route in enumerate(routes):
            cap = 0
            visited = set()

            for point in route:
                # Kiểm tra trùng điểm trong cùng 1 route
                if point in visited:
                    return False
                visited.add(point)

                # Kiểm tra trùng điểm giữa các route
                if point in all_points:
                    return False
                all_points.add(point)

                # Kiểm tra dung lượng
                cap += data['Request'][point]
                if cap < 0 or cap > data['Capacity'][idx]:
                    return False

            for req in data['Delivery']['PassengerRequest']:
                if req[0] in route and req[1] in route:
                    x = route.index(req[0])
                    y = route.index(req[1])
                    if y != x + 1:
                        return False

            for req in data['Delivery']['ParcelRequest']:
                if req[0] in route and req[1] in route:
                    x = route.index(req[0])
                    y = route.index(req[1])
                    if y < x :
                        return False

        return True

    def initialSolution():
        taxis = [[] for _ in range(data['NumTaxis'])]
        all_requests = []
        for req in data['Delivery']['PassengerRequest']:
            all_requests.append((req[0], req[1]))
        for req in data['Delivery']['ParcelRequest']:
            all_requests.append((req[0], req[1]))

        random.shuffle(all_requests)
        for i, req in enumerate(all_requests):
            taxi_idx = i % data['NumTaxis']
            taxis[taxi_idx].append(req[0])
            taxis[taxi_idx].append(req[1])

        for i in range(data['NumTaxis']):
            taxis[i].insert(0, 0)
            taxis[i].append(0)

        return taxis

    # check1 = [
    #         [0, 1, 7, 3, 9, 0],
    #         [0, 2, 8, 4, 5, 10, 6, 11, 12, 0]
    #     ]
    # check2 = [
    #         [0, 8, 6, 5, 11, 12, 0],
    #         [0, 1, 9, 3, 2, 7, 4, 10, 0]
    #     ]
    # print(isFeasible(check1))
    # print(isFeasible(check2))
    # print(initialSolution())
    # print(isFeasible(initialSolution()))
    # print(calculateTotalRoute(initialSolution()))

    def localSearch(solution):
        best_solution = copy.deepcopy(solution)
        best_max_distance = max(calculateRouteDistance(route) for route in best_solution)

        improved = True
        while improved:
            improved = False

            # Try swapping entire requests between routes
            for i in range(len(solution)-1):
                for j in range(i + 1, len(solution)):
                    route_i = solution[i][1:-1]  # Exclude depot
                    route_j = solution[j][1:-1]

                    for k in range(0, len(route_i), 2):  # Step by 2 for pickup-dropoff pairs
                        req_i = [route_i[k], route_i[k + 1]]
                        for l in range(0, len(route_j), 2):
                            req_j = [route_j[l], route_j[l + 1]]
                            new_solution = copy.deepcopy(solution)
                            # Swap the request pairs
                            new_solution[i][k + 1:k + 3] = req_j
                            new_solution[j][l + 1:l + 3] = req_i

                            # if isFeasible(new_solution):
                            max_dist = max(calculateRouteDistance(route)
                                           for route in new_solution)
                            if max_dist < best_max_distance:
                                best_solution = new_solution
                                best_max_distance = max_dist
                                improved = True

            # Try relocating requests within same route
            for i in range(len(solution)):
                route = solution[i][1:-1]  # Exclude depot
                for k in range(0, len(route), 2):
                    req = [route[k], route[k + 1]]
                    for l in range(0, len(route), 2):
                        if k == l:
                            continue
                        new_solution = copy.deepcopy(solution)
                        new_solution[i].pop(k + 1)
                        new_solution[i].pop(k)
                        insert_pos = l if l < k else l - 2
                        new_solution[i][insert_pos + 1:insert_pos + 1] = req

                        # if isFeasible(new_solution):
                        max_dist = max(calculateRouteDistance(route)
                                       for route in new_solution)
                        if max_dist < best_max_distance:
                            best_solution = new_solution
                            best_max_distance = max_dist
                            improved = True

            solution = best_solution
        return best_solution

    def perturb(solution):
        perturbed = copy.deepcopy(solution)

        # Perform multiple random operations
        for _ in range(random.randint(1, 3)):
            operation = random.choice(['swap', 'relocate', 'reverse'])

            if operation == 'swap' and len(perturbed) >= 2:
                i, j = random.sample(range(len(perturbed)), 2)
                route_i = perturbed[i][1:-1]
                route_j = perturbed[j][1:-1]
                if len(route_i) >= 2 and len(route_j) >= 2:
                    k = random.randint(0, len(route_i) - 2) // 2 * 2  # Ensure pickup point
                    l = random.randint(0, len(route_j) - 2) // 2 * 2
                    req_i = [route_i[k], route_i[k + 1]]
                    req_j = [route_j[l], route_j[l + 1]]
                    perturbed[i][k + 1:k + 3] = req_j
                    perturbed[j][l + 1:l + 3] = req_i

            elif operation == 'relocate' and len(perturbed) >= 2:
                i, j = random.sample(range(len(perturbed)), 2)
                route_i = perturbed[i][1:-1]
                if len(route_i) >= 2:
                    k = random.randint(0, len(route_i) - 2) // 2 * 2
                    req = [route_i[k], route_i[k + 1]]
                    perturbed[i].pop(k + 1)
                    perturbed[i].pop(k)
                    l = random.randint(0, len(perturbed[j]) - 2)
                    perturbed[j][l + 1:l + 1] = req

            elif operation == 'reverse':
                i = random.randint(0, len(perturbed) - 1)
                route = perturbed[i][1:-1]
                if len(route) > 3:
                    start = random.randint(0, len(route) - 2) // 2 * 2
                    end = random.randint(start + 2, len(route)) // 2 * 2
                    perturbed[i][start + 1:end + 1] = perturbed[i][start + 1:end + 1][::-1]

        return perturbed if isFeasible(perturbed) else solution

    def iteratedLocalSearch(max_iterations=1000, max_time=30):
        start_time = time.time()
        current_solution = initialSolution()
        current_solution = localSearch(current_solution)
        best_solution = copy.deepcopy(current_solution)
        best_max_distance = max(calculateRouteDistance(route) for route in best_solution)

        iteration = 0
        while iteration < max_iterations and (time.time() - start_time) < max_time:
            perturbed_solution = perturb(current_solution)
            perturbed_solution = localSearch(perturbed_solution)
            current_max_distance = max(calculateRouteDistance(route)
                                       for route in perturbed_solution)

            if current_max_distance < best_max_distance:
                best_solution = copy.deepcopy(perturbed_solution)
                best_max_distance = current_max_distance
                current_solution = perturbed_solution

            iteration += 1

        return best_solution

    solution = iteratedLocalSearch()

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()