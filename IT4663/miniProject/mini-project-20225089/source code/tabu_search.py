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


def calculateRouteDistance(route, data):
    distance = 0
    for i in range(len(route) - 1):
        distance += data['Matrix'][route[i]][route[i + 1]]
    return distance


def calculateTotalRoute(routes, data):
    return sum(calculateRouteDistance(route, data) for route in routes)


def calculateError(solution, data):
    error_count = 0
    for idx, route in enumerate(solution):
        cap = 0
        for point in route:
            # Check capacity constraints
            cap += data['Request'][point]
            if cap < 0 or cap > data['Capacity'][idx]:
                error_count += 1

        # Check passenger requests (pickup must be immediately before dropoff)
        for req in data['Delivery']['PassengerRequest']:
            if req[0] in route and req[1] in route:
                x = route.index(req[0])
                y = route.index(req[1])
                if y != x + 1:
                    error_count += 1

            if req[0] in route and req[1] not in route:
                error_count += 1

            if req[0] not in route and req[1] in route:
                error_count += 1

        # Check parcel requests (pickup must come before dropoff)
        for req in data['Delivery']['ParcelRequest']:
            if req[0] in route and req[1] in route:
                x = route.index(req[0])
                y = route.index(req[1])
                if y < x:
                    error_count += 1
            if req[0] in route and req[1] not in route:
                error_count += 1

            if req[0] not in route and req[1] in route:
                error_count += 1
    return error_count


def initialSolution(data):
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


def generateNeighbors(solution, data):
    neighbors = []

    # Intra-route moves (within the same route)
    for i in range(len(solution)):
        route = solution[i]
        if len(route) <= 2:  # Skip if only depot points
            continue

        # Swap two points in the same route
        for j in range(1, len(route) - 1):
            for k in range(j + 1, len(route) - 1):
                neighbor = copy.deepcopy(solution)
                neighbor[i][j], neighbor[i][k] = neighbor[i][k], neighbor[i][j]
                neighbors.append(neighbor)

        # Relocate a point within the same route
        for j in range(1, len(route) - 1):
            for k in range(1, len(route)):
                if j == k or j == k - 1:
                    continue
                neighbor = copy.deepcopy(solution)
                point = neighbor[i].pop(j)
                neighbor[i].insert(k, point)
                neighbors.append(neighbor)

    # Inter-route moves (between different routes)
    for i in range(len(solution)):
        for j in range(len(solution)):
            if i == j:
                continue

            for k in range(1, len(solution[i]) - 1):
                for l in range(1, len(solution[j])):
                    # Move point from route i to route j
                    neighbor = copy.deepcopy(solution)
                    point = neighbor[i].pop(k)
                    neighbor[j].insert(l, point)
                    neighbors.append(neighbor)

    # Special moves for passenger requests (keep pickup and dropoff together)
    for req in data['Delivery']['PassengerRequest']:
        pickup, dropoff = req
        for i in range(len(solution)):
            if pickup in solution[i] and dropoff in solution[i]:
                idx_p = solution[i].index(pickup)
                idx_d = solution[i].index(dropoff)
                if idx_d != idx_p + 1:
                    neighbor = copy.deepcopy(solution)
                    neighbor[i].pop(idx_d)
                    neighbor[i].insert(idx_p + 1, dropoff)
                    neighbors.append(neighbor)

    return neighbors


def tabuSearch(data, max_iterations=1000, tabu_tenure=10, max_time=30):
    start_time = time.time()
    current_solution = initialSolution(data)
    best_solution = copy.deepcopy(current_solution)
    best_error = calculateError(best_solution, data)

    # Tabu list: stores forbidden moves (as tuples of (move_type, attributes))
    tabu_list = []

    iteration = 0
    while iteration < max_iterations and (time.time() - start_time) < max_time and best_error > 0:
        # Generate neighbors
        neighbors = generateNeighbors(current_solution, data)

        # Evaluate neighbors and find the best non-tabu move
        best_neighbor = None
        best_neighbor_error = float('inf')

        for neighbor in neighbors:
            neighbor_error = calculateError(neighbor, data)

            # Check if move is tabu
            # (In a real implementation, we'd have a proper move representation)
            is_tabu = False
            for tabu_move in tabu_list:
                # Simplified tabu check - in practice, would compare move attributes
                if neighbor == tabu_move[1]:  # tabu_move is (move_type, solution)
                    is_tabu = True
                    break

            # Aspiration criterion: allow tabu moves if they improve the best solution
            if (not is_tabu) or (is_tabu and neighbor_error < best_error):
                if neighbor_error < best_neighbor_error:
                    best_neighbor = neighbor
                    best_neighbor_error = neighbor_error

        # If no non-tabu moves found, select the oldest tabu move
        if best_neighbor is None and tabu_list:
            best_neighbor = tabu_list.pop(0)[1]  # Remove oldest and use it
            best_neighbor_error = calculateError(best_neighbor, data)

        # Update current solution
        if best_neighbor is not None:
            current_solution = best_neighbor
            current_error = best_neighbor_error

            # Add move to tabu list (simplified - would store move attributes)
            tabu_list.append(('move', copy.deepcopy(current_solution)))

            # Keep tabu list size limited
            if len(tabu_list) > tabu_tenure:
                tabu_list.pop(0)

            # Update best solution if improved
            if current_error < best_error:
                best_solution = copy.deepcopy(current_solution)
                best_error = current_error

        iteration += 1

    return best_solution


def main():
    # dataPath = "test/test5.txt"  # Replace with your actual data file path
    # data = importData(dataPathath)
    data = importData2()

    solution = tabuSearch(data)

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()
