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

                # Check capacity constraints
                cap += data['Request'][point]
                if cap < 0 or cap > data['Capacity'][idx]:
                    return False

            # Check passenger requests (pickup must be immediately before dropoff)
            for req in data['Delivery']['PassengerRequest']:
                if req[0] in route and req[1] in route:
                    x = route.index(req[0])
                    y = route.index(req[1])
                    if y != x + 1:
                        return False

            # Check parcel requests (pickup must come before dropoff)
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

    def guidedLocalSearch(max_iterations=1000, max_time=30, lambda_param=0.1):
        start_time = time.time()

        # Initialize solution
        current_solution = initialSolution()
        best_solution = copy.deepcopy(current_solution)
        best_max_distance = calculateMaxRouteDistance(best_solution)

        # Initialize penalties
        features = []
        for route_idx in range(len(current_solution)):
            for i in range(1, len(current_solution[route_idx]) - 1):
                features.append((route_idx, current_solution[route_idx][i]))
        penalties = {feature: 0 for feature in features}

        iteration = 0
        while iteration < max_iterations and (time.time() - start_time) < max_time:
            # Calculate augmented objective function
            def augmented_objective(solution):
                max_dist = calculateMaxRouteDistance(solution)
                penalty_sum = 0
                for route_idx in range(len(solution)):
                    for i in range(1, len(solution[route_idx]) - 1):
                        node = solution[route_idx][i]
                        penalty_sum += penalties.get((route_idx, node), 0)
                return max_dist + lambda_param * penalty_sum

            # Local search with augmented objective
            improved = True
            while improved:
                improved = False

                # Try all possible request swaps between routes
                for i in range(len(current_solution) - 1):
                    for j in range(i + 1, len(current_solution)):
                        route_i = current_solution[i][1:-1]  # Exclude depot
                        route_j = current_solution[j][1:-1]

                        for k in range(0, len(route_i), 2):  # Step by 2 for pickup-dropoff pairs
                            req_i = [route_i[k], route_i[k + 1]]
                            for l in range(0, len(route_j), 2):
                                req_j = [route_j[l], route_j[l + 1]]
                                new_solution = copy.deepcopy(current_solution)
                                # Swap the request pairs
                                new_solution[i][k + 1:k + 3] = req_j
                                new_solution[j][l + 1:l + 3] = req_i

                                if isFeasible(new_solution):
                                    current_obj = augmented_objective(current_solution)
                                    new_obj = augmented_objective(new_solution)
                                    if new_obj < current_obj:
                                        current_solution = new_solution
                                        improved = True
                                        # Update best solution if actual max distance is better
                                        current_max_dist = calculateMaxRouteDistance(current_solution)
                                        if current_max_dist < best_max_distance:
                                            best_solution = copy.deepcopy(current_solution)
                                            best_max_distance = current_max_dist

                # Try relocating requests within same route
                for i in range(len(current_solution)):
                    route = current_solution[i][1:-1]  # Exclude depot
                    for k in range(0, len(route), 2):
                        req = [route[k], route[k + 1]]
                        for l in range(0, len(route), 2):
                            if k == l:
                                continue
                            new_solution = copy.deepcopy(current_solution)
                            new_solution[i].pop(k + 1)
                            new_solution[i].pop(k)
                            insert_pos = l if l < k else l - 2
                            new_solution[i][insert_pos + 1:insert_pos + 1] = req

                            if isFeasible(new_solution):
                                current_obj = augmented_objective(current_solution)
                                new_obj = augmented_objective(new_solution)
                                if new_obj < current_obj:
                                    current_solution = new_solution
                                    improved = True
                                    # Update best solution if actual max distance is better
                                    current_max_dist = calculateMaxRouteDistance(current_solution)
                                    if current_max_dist < best_max_distance:
                                        best_solution = copy.deepcopy(current_solution)
                                        best_max_distance = current_max_dist

            # Feature selection and penalty update
            if iteration % 10 == 0:  # Update penalties periodically
                # Calculate utility for each feature (distance * (1 + penalty))
                utilities = {}
                for route_idx in range(len(current_solution)):
                    for i in range(1, len(current_solution[route_idx]) - 1):
                        node = current_solution[route_idx][i]
                        # Find the distance contribution of this node
                        prev_node = current_solution[route_idx][i - 1]
                        next_node = current_solution[route_idx][i + 1]
                        dist_contribution = (data['Matrix'][prev_node][node] +
                                             data['Matrix'][node][next_node])
                        utilities[(route_idx, node)] = dist_contribution * (1 + penalties.get((route_idx, node), 0))

                # Select features with maximum utility to penalize
                if utilities:
                    max_utility = max(utilities.values())
                    for feature, utility in utilities.items():
                        if utility == max_utility:
                            penalties[feature] = penalties.get(feature, 0) + 1

            iteration += 1

        return best_solution

    solution = guidedLocalSearch()

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()