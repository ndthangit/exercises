import copy
import random
import time
import math


def importData(dataPath):
    data = {}
    with open(dataPath, 'r') as f:
        n, m, k = f.readline().split()
        data['NumParcel'] = int(n)
        data['NumPassenger'] = int(m)
        data['NumTaxis'] = int(k)
        data['Quantity'] = [int(x) for x in f.readline().split()]
        data['Capacity'] = [int(x) for x in f.readline().split()]

        data['Matrix'] = []
        for x in range(2 * (data['NumParcel'] + data['NumPassenger']) + 1):
            data['Matrix'].append([int(x) for x in f.readline().split()])

    data['Depot'] = 0

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

    data['Request'] = [0] * (2 * (data['NumParcel'] + 2 * data['NumPassenger']) + 1)
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
    data = importData2()

    def calculateRouteDistance(route):
        distance = 0
        for i in range(len(route) - 1):
            distance += data['Matrix'][route[i]][route[i + 1]]
        return distance

    def calculateTotalRoute(routes):
        return sum(calculateRouteDistance(route) for route in routes)

    def calculateMaxRouteDistance(routes):
        return max(calculateRouteDistance(route) for route in routes)

    def isFeasible(routes):
        all_points = set()

        for idx, route in enumerate(routes):
            cap = 0
            visited = set()

            for point in route:
                # Check duplicate points in the same route
                if point in visited:
                    return False
                visited.add(point)

                # Check duplicate points across routes
                if point in all_points:
                    return False
                all_points.add(point)

                # Check capacity
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
                    if y < x:
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

    def generateNeighbor(solution):
        neighbor = copy.deepcopy(solution)
        operation = random.choice(['swap', 'relocate', 'reverse'])

        if operation == 'swap' and len(neighbor) >= 2:
            i, j = random.sample(range(len(neighbor)), 2)
            route_i = neighbor[i][1:-1]  # Exclude depot
            route_j = neighbor[j][1:-1]
            if len(route_i) >= 2 and len(route_j) >= 2:
                k = random.randint(0, len(route_i) - 2) // 2 * 2  # Ensure pickup point
                l = random.randint(0, len(route_j) - 2) // 2 * 2
                req_i = [route_i[k], route_i[k + 1]]
                req_j = [route_j[l], route_j[l + 1]]
                neighbor[i][k + 1:k + 3] = req_j
                neighbor[j][l + 1:l + 3] = req_i

        elif operation == 'relocate' and len(neighbor) >= 2:
            i, j = random.sample(range(len(neighbor)), 2)
            route_i = neighbor[i][1:-1]
            if len(route_i) >= 2:
                k = random.randint(0, len(route_i) - 2) // 2 * 2
                req = [route_i[k], route_i[k + 1]]
                neighbor[i].pop(k + 1)
                neighbor[i].pop(k)
                l = random.randint(0, len(neighbor[j]) - 2)
                neighbor[j][l + 1:l + 1] = req

        elif operation == 'reverse':
            i = random.randint(0, len(neighbor) - 1)
            route = neighbor[i][1:-1]
            if len(route) > 3:
                start = random.randint(0, len(route) - 2) // 2 * 2
                end = random.randint(start + 2, len(route)) // 2 * 2
                neighbor[i][start + 1:end + 1] = neighbor[i][start + 1:end + 1][::-1]

        return neighbor if isFeasible(neighbor) else solution

    def simulatedAnnealing(initial_temp=1000, cooling_rate=0.995, min_temp=1, max_iterations=10000, max_time=30):
        start_time = time.time()
        current_solution = initialSolution()
        current_cost = calculateMaxRouteDistance(current_solution)
        best_solution = copy.deepcopy(current_solution)
        best_cost = current_cost

        temp = initial_temp
        iteration = 0

        while temp > min_temp and iteration < max_iterations and (time.time() - start_time) < max_time:
            neighbor = generateNeighbor(current_solution)
            neighbor_cost = calculateMaxRouteDistance(neighbor)

            cost_diff = neighbor_cost - current_cost

            # If neighbor is better or accepted by probability
            if cost_diff < 0 or random.random() < math.exp(-cost_diff / temp):
                current_solution = neighbor
                current_cost = neighbor_cost

                if current_cost < best_cost:
                    best_solution = copy.deepcopy(current_solution)
                    best_cost = current_cost

            temp *= cooling_rate
            iteration += 1

        return best_solution

    solution = simulatedAnnealing()

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()