import random
import copy
from typing import List, Dict


def importData(dataPath: str) -> Dict:
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
        'PassengerRequest': [[i, i + data['NumParcel'] + data['NumPassenger']]
                             for i in range(1, data['NumPassenger'] + 1)],
        'ParcelRequest': [[i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']]
                          for i in range(1, data['NumParcel'] + 1)]
    }
    data['Request'] = [0] * (2 * (data['NumParcel'] + data['NumPassenger']) + 1)
    for i, value in enumerate(data['Quantity']):
        data['Request'][i + 1 + data['NumParcel']] = value
        data['Request'][i + 1 + 2 * data['NumParcel'] + data['NumPassenger']] = -value

    return data


def calculateRouteDistance(route: List[int], matrix: List[List[int]]) -> int:
    if not route: return 0
    distance = 0
    for i in range(len(route) - 1):
        distance += matrix[route[i]][route[i + 1]]
    return distance


def isFeasible(routes: List[List[int]], data: Dict) -> bool:
    for idx, route in enumerate(routes):
        if not route or route[0] != 0 or route[-1] != 0:
            return False

        # Check capacity constraints
        current_load = 0
        visited = set()
        for i, point in enumerate(route):
            current_load += data['Request'][point]
            if current_load < 0 or current_load > data['Capacity'][idx]:
                return False
            if point != 0 and point in visited:
                return False
            visited.add(point)

            # Check passenger direct trip constraint
            for req in data['Delivery']['PassengerRequest']:
                if point == req[0] and (i + 1 >= len(route) or route[i + 1] != req[1]):
                    return False

            # Check parcel delivery order
            for req in data['Delivery']['ParcelRequest']:
                if point == req[1] and req[0] not in route[:i]:
                    return False

    # Check if all requests are served
    all_points = set()
    for route in routes:
        all_points.update(route[1:-1])  # Exclude depot
    for req in data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']:
        if req[0] not in all_points or req[1] not in all_points:
            return False

    return True


def initialSolution(data: Dict) -> List[List[int]]:
    taxis = [[0] for _ in range(data['NumTaxis'])]
    all_requests = data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']
    random.shuffle(all_requests)

    for req in all_requests:
        assigned = False
        for taxi_idx in random.sample(range(data['NumTaxis']), data['NumTaxis']):
            route = taxis[taxi_idx].copy()
            route = route[:-1] + req + [0]  # Insert request before final depot
            taxis[taxi_idx] = route
            if isFeasible(taxis, data):
                assigned = True
                break
            else:
                taxis[taxi_idx] = route[:-3] + [0]  # Revert if not feasible
        if not assigned:
            # If can't assign, try splitting routes
            for taxi_idx in random.sample(range(data['NumTaxis']), data['NumTaxis']):
                route = taxis[taxi_idx]
                for pos in range(1, len(route)):
                    new_route = route[:pos] + req + route[pos:-1] + [0]
                    taxis[taxi_idx] = new_route
                    if isFeasible(taxis, data):
                        assigned = True
                        break
                if assigned:
                    break
            if not assigned:
                taxis[0] = [0] + req + [0]  # Fallback to first taxi

    return taxis


def swap_nodes(route: List[int], i: int, j: int) -> List[int]:
    new_route = route.copy()
    new_route[i], new_route[j] = new_route[j], new_route[i]
    return new_route


def relocate_node(route: List[int], i: int, j: int) -> List[int]:
    new_route = route.copy()
    node = new_route.pop(i)
    new_route.insert(j, node)
    return new_route


def two_opt(route: List[int], i: int, j: int) -> List[int]:
    new_route = route[:i] + route[i:j + 1][::-1] + route[j + 1:]
    return new_route


def localSearch(solution: List[List[int]], data: Dict) -> List[List[int]]:
    best_solution = copy.deepcopy(solution)
    best_max_dist = max(calculateRouteDistance(route, data['Matrix']) for route in best_solution)

    for taxi_idx in range(len(solution)):
        route = solution[taxi_idx]
        improved = True
        while improved:
            improved = False
            for i in range(1, len(route) - 2):
                for j in range(i + 1, len(route) - 1):
                    # Try swap
                    new_route = swap_nodes(route, i, j)
                    new_solution = solution.copy()
                    new_solution[taxi_idx] = new_route
                    if isFeasible(new_solution, data):
                        new_max_dist = max(calculateRouteDistance(r, data['Matrix']) for r in new_solution)
                        if new_max_dist < best_max_dist:
                            solution = new_solution
                            route = new_route
                            best_max_dist = new_max_dist
                            improved = True

                    # Try relocate
                    new_route = relocate_node(route, i, j)
                    new_solution = solution.copy()
                    new_solution[taxi_idx] = new_route
                    if isFeasible(new_solution, data):
                        new_max_dist = max(calculateRouteDistance(r, data['Matrix']) for r in new_solution)
                        if new_max_dist < best_max_dist:
                            solution = new_solution
                            route = new_route
                            best_max_dist = new_max_dist
                            improved = True

                    # Try 2-opt
                    new_route = two_opt(route, i, j)
                    new_solution = solution.copy()
                    new_solution[taxi_idx] = new_route
                    if isFeasible(new_solution, data):
                        new_max_dist = max(calculateRouteDistance(r, data['Matrix']) for r in new_solution)
                        if new_max_dist < best_max_dist:
                            solution = new_solution
                            route = new_route
                            best_max_dist = new_max_dist
                            improved = True

            if improved:
                best_solution = copy.deepcopy(solution)

    return best_solution


def perturb(solution: List[List[int]], data: Dict) -> List[List[int]]:
    perturbed_solution = copy.deepcopy(solution)
    if len(perturbed_solution) < 2:
        return perturbed_solution

    # Randomly swap points between routes
    i, j = random.sample(range(len(perturbed_solution)), 2)
    if len(perturbed_solution[i]) > 2 and len(perturbed_solution[j]) > 2:
        k = random.randint(1, len(perturbed_solution[i]) - 2)
        l = random.randint(1, len(perturbed_solution[j]) - 2)
        perturbed_solution[i][k], perturbed_solution[j][l] = perturbed_solution[j][l], perturbed_solution[i][k]

    # Randomly shuffle a route (keeping depot and passenger constraints)
    taxi_idx = random.randint(0, len(perturbed_solution) - 1)
    route = perturbed_solution[taxi_idx][1:-1]
    random.shuffle(route)
    # Reinsert passenger pairs together
    new_route = [0]
    for req in data['Delivery']['PassengerRequest']:
        if req[0] in route and req[1] in route:
            new_route.extend(req)
            route.remove(req[0])
            route.remove(req[1])
    new_route.extend(route)
    new_route.append(0)
    perturbed_solution[taxi_idx] = new_route

    return perturbed_solution


def iteratedLocalSearch(data: Dict, max_iterations: int = 1000) -> List[List[int]]:
    current_solution = initialSolution(data)
    if not isFeasible(current_solution, data):
        current_solution = initialSolution(data)  # Retry if initial solution is not feasible
    current_solution = localSearch(current_solution, data)
    best_solution = copy.deepcopy(current_solution)
    best_max_distance = max(calculateRouteDistance(route, data['Matrix']) for route in best_solution)

    for _ in range(max_iterations):
        perturbed_solution = perturb(current_solution, data)
        perturbed_solution = localSearch(perturbed_solution, data)
        if isFeasible(perturbed_solution, data):
            current_max_distance = max(calculateRouteDistance(route, data['Matrix']) for route in perturbed_solution)
            if current_max_distance < best_max_distance:
                best_solution = copy.deepcopy(perturbed_solution)
                best_max_distance = current_max_distance
        current_solution = perturbed_solution

    return best_solution


def main():
    dataPath = "test/test5.txt"  # Replace with actual data file path
    data = importData(dataPath)

    solution = iteratedLocalSearch(data)

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()