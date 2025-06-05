import copy
import random
import time


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

    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

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
    dataPath = "test/test5.txt"  # Replace with your actual data file path
    data = importData(dataPath)
    # data = importData2()

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
                if point in visited:
                    return False
                visited.add(point)

                if point in all_points:
                    return False
                all_points.add(point)

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

    def localSearch(solution):
        best_solution = copy.deepcopy(solution)
        best_max_distance = max(calculateRouteDistance(route) for route in best_solution)

        improved = True
        while improved:
            improved = False

            for i in range(len(solution) - 1):
                for j in range(i + 1, len(solution)):
                    route_i = solution[i][1:-1]
                    route_j = solution[j][1:-1]

                    for k in range(0, len(route_i), 2):
                        req_i = [route_i[k], route_i[k + 1]]
                        for l in range(0, len(route_j), 2):
                            req_j = [route_j[l], route_j[l + 1]]
                            new_solution = copy.deepcopy(solution)
                            new_solution[i][k + 1:k + 3] = req_j
                            new_solution[j][l + 1:l + 3] = req_i

                            if isFeasible(new_solution):
                                max_dist = max(calculateRouteDistance(route) for route in new_solution)
                                if max_dist < best_max_distance:
                                    best_solution = new_solution
                                    best_max_distance = max_dist
                                    improved = True

            for i in range(len(solution)):
                route = solution[i][1:-1]
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

                        if isFeasible(new_solution):
                            max_dist = max(calculateRouteDistance(route) for route in new_solution)
                            if max_dist < best_max_distance:
                                best_solution = new_solution
                                best_max_distance = max_dist
                                improved = True

            solution = best_solution
        return best_solution

    def generateNeighbor(solution):
        new_solution = copy.deepcopy(solution)
        operation = random.choice(['swap', 'relocate'])

        if operation == 'swap' and len(new_solution) >= 2:
            i, j = random.sample(range(len(new_solution)), 2)
            route_i = new_solution[i][1:-1]
            route_j = new_solution[j][1:-1]
            if len(route_i) >= 2 and len(route_j) >= 2:
                k = random.randint(0, len(route_i) - 2) // 2 * 2
                l = random.randint(0, len(route_j) - 2) // 2 * 2
                req_i = [route_i[k], route_i[k + 1]]
                req_j = [route_j[l], route_j[l + 1]]
                new_solution[i][k + 1:k + 3] = req_j
                new_solution[j][l + 1:l + 3] = req_i

        elif operation == 'relocate' and len(new_solution) >= 2:
            i, j = random.sample(range(len(new_solution)), 2)
            route_i = new_solution[i][1:-1]
            if len(route_i) >= 2:
                k = random.randint(0, len(route_i) - 2) // 2 * 2
                req = [route_i[k], route_i[k + 1]]
                new_solution[i].pop(k + 1)
                new_solution[i].pop(k)
                l = random.randint(0, len(new_solution[j]) - 2)
                new_solution[j][l + 1:l + 1] = req

        return new_solution

    def tabuSearch(max_iterations=1000, max_time=30, tabu_tenure=10):
        start_time = time.time()
        current_solution = initialSolution()
        current_solution = localSearch(current_solution)
        best_solution = copy.deepcopy(current_solution)
        best_max_distance = max(calculateRouteDistance(route) for route in best_solution)

        tabu_list = []
        iteration = 0

        while iteration < max_iterations and (time.time() - start_time) < max_time:
            best_neighbor = None
            best_neighbor_distance = float('inf')
            best_move = None

            for _ in range(10):  # Evaluate multiple neighbors
                neighbor = generateNeighbor(current_solution)
                if not isFeasible(neighbor):
                    continue
                max_dist = max(calculateRouteDistance(route) for route in neighbor)

                move = tuple(tuple(route) for route in neighbor)
                if move not in tabu_list or max_dist < best_max_distance:  # Aspiration criterion
                    if max_dist < best_neighbor_distance:
                        best_neighbor = neighbor
                        best_neighbor_distance = max_dist
                        best_move = move

            if best_neighbor is not None:
                current_solution = best_neighbor
                tabu_list.append(best_move)
                if len(tabu_list) > tabu_tenure:
                    tabu_list.pop(0)

                if best_neighbor_distance < best_max_distance:
                    best_solution = copy.deepcopy(best_neighbor)
                    best_max_distance = best_neighbor_distance

            iteration += 1

        return best_solution

    solution = tabuSearch()

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()