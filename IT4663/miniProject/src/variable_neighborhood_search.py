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

    def calculateMaxRoute(routes):
        return max(calculateRouteDistance(route) for route in routes)

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

    # Neighborhood structures for VNS
    def swap_neighborhood(solution):
        """Swap two requests between different taxis"""
        new_solution = copy.deepcopy(solution)
        if len(new_solution) < 2:
            return new_solution

        i, j = random.sample(range(len(new_solution)), 2)
        route_i = new_solution[i][1:-1]
        route_j = new_solution[j][1:-1]

        if len(route_i) >= 2 and len(route_j) >= 2:
            # Find request pairs (pickup and drop)
            k = random.randint(0, len(route_i) - 2) // 2 * 2
            l = random.randint(0, len(route_j) - 2) // 2 * 2

            # Swap the requests
            req_i = [route_i[k], route_i[k + 1]]
            req_j = [route_j[l], route_j[l + 1]]

            new_solution[i][k + 1:k + 3] = req_j
            new_solution[j][l + 1:l + 3] = req_i

        return new_solution if isFeasible(new_solution) else solution

    def relocate_neighborhood(solution):
        """Move a request from one taxi to another"""
        new_solution = copy.deepcopy(solution)
        if len(new_solution) < 2:
            return new_solution

        i, j = random.sample(range(len(new_solution)), 2)
        route_i = new_solution[i][1:-1]

        if len(route_i) >= 2:
            k = random.randint(0, len(route_i) - 2) // 2 * 2
            req = [route_i[k], route_i[k + 1]]

            # Remove from original route
            new_solution[i].pop(k + 1)
            new_solution[i].pop(k)

            # Insert into new route at random position
            insert_pos = random.randint(1, len(new_solution[j]) - 1)
            new_solution[j][insert_pos:insert_pos] = req

        return new_solution if isFeasible(new_solution) else solution

    def reverse_neighborhood(solution):
        """Reverse a segment of a route"""
        new_solution = copy.deepcopy(solution)
        i = random.randint(0, len(new_solution) - 1)
        route = new_solution[i][1:-1]

        if len(route) >= 4:
            start = random.randint(0, len(route) - 4) // 2 * 2
            end = random.randint(start + 2, len(route)) // 2 * 2
            segment = new_solution[i][start + 1:end + 1]
            new_solution[i][start + 1:end + 1] = segment[::-1]

        return new_solution if isFeasible(new_solution) else solution

    def two_opt_neighborhood(solution):
        """2-opt optimization for a single route"""
        new_solution = copy.deepcopy(solution)
        i = random.randint(0, len(new_solution) - 1)
        route = new_solution[i][1:-1]

        if len(route) >= 4:
            # Select two distinct edges to break
            a, c = sorted(random.sample(range(len(route) - 1), 2))
            b = a + 1
            d = c + 1

            # Reverse the segment between b and c
            new_route = route[:a + 1] + route[b:c + 1][::-1] + route[d:]
            new_solution[i] = [0] + new_route + [0]

        return new_solution if isFeasible(new_solution) else solution

    def local_search(solution, neighborhood_func):
        """Local search using a specific neighborhood"""
        best_solution = copy.deepcopy(solution)
        best_distance = calculateMaxRoute(best_solution)

        improved = True
        while improved:
            improved = False
            candidate = neighborhood_func(best_solution)
            candidate_distance = calculateMaxRoute(candidate)

            if candidate_distance < best_distance:
                best_solution = candidate
                best_distance = candidate_distance
                improved = True

        return best_solution

    def variable_neighborhood_search(max_iterations=1000, max_time=30):
        start_time = time.time()
        current_solution = initialSolution()
        best_solution = copy.deepcopy(current_solution)
        best_distance = calculateMaxRoute(best_solution)

        # Define neighborhood structures in order of increasing complexity
        neighborhoods = [
            swap_neighborhood,
            relocate_neighborhood,
            reverse_neighborhood,
            two_opt_neighborhood
        ]

        iteration = 0
        while iteration < max_iterations and (time.time() - start_time) < max_time:
            k = 0  # Start with first neighborhood
            while k < len(neighborhoods):
                # Shaking: generate a random neighbor in k-th neighborhood
                shaken = neighborhoods[k](current_solution)

                # Local search in the same neighborhood
                candidate = local_search(shaken, neighborhoods[k])
                candidate_distance = calculateMaxRoute(candidate)

                # Neighborhood change condition
                if candidate_distance < best_distance:
                    best_solution = copy.deepcopy(candidate)
                    best_distance = candidate_distance
                    current_solution = candidate
                    k = 0  # Back to first neighborhood
                else:
                    k += 1  # Try next neighborhood

                iteration += 1

        return best_solution

    solution = variable_neighborhood_search()

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()