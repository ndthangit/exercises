#PYTHON 
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


def calculateRouteDistance(data, route):
    distance = 0
    for i in range(len(route) - 1):
        distance += data['Matrix'][route[i]][route[i + 1]]
    return distance


def calculateTotalRoute(data, routes):
    return sum(calculateRouteDistance(data, route) for route in routes)


def initialSolution(data):
    taxis = [[] for _ in range(data['NumTaxis'])]
    for point in range(1, 2 * (data['NumPassenger'] + data['NumParcel']) + 1):
        taxi_idx = random.randint(0, data['NumTaxis'] - 1)
        taxis[taxi_idx].append(point)

    for i in range(data['NumTaxis']):
        taxis[i].insert(0, 0)
        taxis[i].append(0)

    best_error, best_problematic_points, best_point_in_route, best_error_cap = calculateError(data, taxis)

    for [pickup, dropoff] in best_problematic_points['pointError'] + best_problematic_points['scheduleError']:
        if pickup <= data['NumPassenger']:
            taxis[best_point_in_route[dropoff]].remove(dropoff)
            taxis[best_point_in_route[pickup]].insert(
                taxis[best_point_in_route[pickup]].index(pickup) + 1, dropoff)
            best_point_in_route[dropoff] = best_point_in_route[pickup]
            best_error -= 1
        else:
            taxis[best_point_in_route[dropoff]].remove(dropoff)
            taxis[best_point_in_route[pickup]].insert(-1, dropoff)
            best_point_in_route[dropoff] = best_point_in_route[pickup]
            best_error -= 1

    return taxis


def calculateError(data, routes):
    error_count = 0
    problematic_points = {
        'scheduleError': [],
        'pointError': []
    }
    point_in_route = {}
    error_cap = {}

    for idx, route in enumerate(routes):
        cap = 0
        for point in route:
            cap += data['Request'][point]
            point_in_route[point] = idx

            if cap < 0 or cap > data['Capacity'][idx]:
                error_count += 1
                error_cap[idx] = 1

        for req in [r for r in data['Delivery']['PassengerRequest'] if
                    r not in problematic_points['pointError'] and r not in problematic_points['scheduleError']]:
            if req[0] in route and req[1] in route:
                x = route.index(req[0])
                y = route.index(req[1])
                if y != x + 1:
                    error_count += 1
                    problematic_points['pointError'].append(req)
            elif req[0] in route and req[1] not in route:
                error_count += 1
                problematic_points['scheduleError'].append(req)
            elif req[0] not in route and req[1] in route:
                error_count += 1
                problematic_points['scheduleError'].append(req)

        for req in [r for r in data['Delivery']['ParcelRequest'] if
                    r not in problematic_points['pointError'] and r not in problematic_points['scheduleError']]:
            if req[0] in route and req[1] in route:
                x = route.index(req[0])
                y = route.index(req[1])
                if y < x:
                    error_count += 1
                    problematic_points['pointError'].append(req)
            elif req[0] in route and req[1] not in route:
                error_count += 1
                problematic_points['scheduleError'].append(req)
            elif req[0] not in route and req[1] in route:
                error_count += 1
                problematic_points['scheduleError'].append(req)

    return error_count, problematic_points, point_in_route, error_cap


def isFeasible(data, solution):
    error_count, _, _, _ = calculateError(data, solution)
    return error_count == 0


def neighborhood1(data, solution, error_cap):
    """Move a random point to a different taxi's route"""
    neighbors = []
    if not error_cap:
        return neighbors

    # Select a random taxi with capacity issues
    idx = random.choice(list(error_cap.keys()))
    route = solution[idx]

    # Find all pickup points in this route
    pickups = []
    for req in data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']:
        if req[0] in route:
            pickups.append(req[0])

    if not pickups:
        return neighbors

    # Select a random pickup point
    pickup = random.choice(pickups)
    current_pos = route.index(pickup)

    # Generate new positions for the pickup (must come before its dropoff)
    dropoff = None
    for req in data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']:
        if req[0] == pickup:
            dropoff = req[1]
            break

    if dropoff not in route:
        return neighbors

    dropoff_pos = route.index(dropoff)

    # Possible new positions for pickup (must be before dropoff)
    possible_positions = [i for i in range(1, dropoff_pos) if i != current_pos]

    if not possible_positions:
        return neighbors

    # Create neighbors by moving pickup to new positions
    for new_pos in random.sample(possible_positions, min(3, len(possible_positions))):  # Try up to 3 random positions
        new_solution = copy.deepcopy(solution)
        new_solution[idx].remove(pickup)
        new_solution[idx].insert(new_pos, pickup)
        neighbors.append(new_solution)

    return neighbors


def neighborhood2(data, solution, error_cap):
    """Swap two points between different taxis"""
    neighbors = []
    if not error_cap:
        return neighbors

    # Select a random taxi with capacity issues
    idx = random.choice(list(error_cap.keys()))
    route = solution[idx]

    # Find all dropoff points in this route
    dropoffs = []
    for req in data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']:
        if req[1] in route:
            dropoffs.append(req[1])

    if not dropoffs:
        return neighbors

    # Select a random dropoff point
    dropoff = random.choice(dropoffs)
    current_pos = route.index(dropoff)

    # Find its corresponding pickup
    pickup = None
    for req in data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']:
        if req[1] == dropoff:
            pickup = req[0]
            break

    if pickup not in route:
        return neighbors

    pickup_pos = route.index(pickup)

    # Possible new positions for dropoff (must be after pickup for parcels, immediately after for passengers)
    if dropoff in [req[1] for req in data['Delivery']['PassengerRequest']]:  # Passenger dropoff
        # Must be immediately after pickup
        new_solution = copy.deepcopy(solution)
        new_solution[idx].remove(dropoff)
        new_solution[idx].insert(pickup_pos + 1, dropoff)
        neighbors.append(new_solution)
    else:  # Parcel dropoff
        possible_positions = [i for i in range(pickup_pos + 1, len(route) - 1) if i != current_pos]
        if possible_positions:
            for new_pos in random.sample(possible_positions, min(3, len(possible_positions))):
                new_solution = copy.deepcopy(solution)
                new_solution[idx].remove(dropoff)
                new_solution[idx].insert(new_pos, dropoff)
                neighbors.append(new_solution)

    return neighbors


def neighborhood3(data, solution, error_cap):
    """Rearrange points within the same taxi to fix capacity issues"""
    neighbors = []
    if not error_cap:
        return neighbors

    # Select a random taxi with capacity issues
    idx = random.choice(list(error_cap.keys()))
    route = solution[idx]

    # Find all request pairs in this route
    requests = []
    for req in data['Delivery']['PassengerRequest'] + data['Delivery']['ParcelRequest']:
        if req[0] in route and req[1] in route:
            requests.append(req)

    if not requests:
        return neighbors

    # Select a random request pair
    req = random.choice(requests)
    pickup, dropoff = req[0], req[1]

    # Find all other taxis that could receive this pair
    for other_idx in range(data['NumTaxis']):
        if other_idx != idx:
            # Generate possible insertion points (must maintain passenger/parcel constraints)
            other_route = solution[other_idx]

            if dropoff in [r[1] for r in data['Delivery']['PassengerRequest']]:  # Passenger
                # Must insert pickup and dropoff together, with dropoff immediately after
                for insert_pos in range(1, len(other_route)):
                    new_solution = copy.deepcopy(solution)
                    new_solution[idx].remove(pickup)
                    new_solution[idx].remove(dropoff)
                    new_solution[other_idx].insert(insert_pos, pickup)
                    new_solution[other_idx].insert(insert_pos + 1, dropoff)
                    neighbors.append(new_solution)
            else:  # Parcel
                # Can insert pickup and dropoff at any positions, as long as pickup comes before dropoff
                for pickup_pos in range(1, len(other_route)):
                    for dropoff_pos in range(pickup_pos + 1, len(other_route)):
                        new_solution = copy.deepcopy(solution)
                        new_solution[idx].remove(pickup)
                        new_solution[idx].remove(dropoff)
                        new_solution[other_idx].insert(pickup_pos, pickup)
                        new_solution[other_idx].insert(dropoff_pos, dropoff)
                        neighbors.append(new_solution)

    return neighbors


def variableNeighborhoodSearch(data, initial_solution, max_iterations=100000, max_time=30):
    start_time = time.time()
    best_solution = copy.deepcopy(initial_solution)
    best_error, _, _, best_error_cap = calculateError(data, best_solution)

    neighborhoods = [neighborhood1, neighborhood2, neighborhood3]
    current_neighborhood = 0

    iteration = 0
    while iteration < max_iterations and (time.time() - start_time) < max_time and best_error > 0:
        # Generate neighbors from current neighborhood
        neighbors = neighborhoods[current_neighborhood](data, best_solution, best_error_cap)

        if not neighbors:
            current_neighborhood = (current_neighborhood + 1) % len(neighborhoods)
            continue

        # Evaluate all neighbors
        for neighbor in neighbors:
            current_error, _, _, error_cap = calculateError(data, neighbor)

            if current_error < best_error:
                best_solution = copy.deepcopy(neighbor)
                best_error = current_error
                best_error_cap = error_cap
                current_neighborhood = 0  # Reset to first neighborhood
                break
            elif current_error == best_error:
                if calculateTotalRoute(data, neighbor) < calculateTotalRoute(data, best_solution):
                    best_solution = copy.deepcopy(neighbor)
                    best_error_cap = error_cap
                    current_neighborhood = 0  # Reset to first neighborhood
                    break

        # If no improvement, move to next neighborhood
        else:
            current_neighborhood = (current_neighborhood + 1) % len(neighborhoods)

        iteration += 1

    return best_solution


def main():
    data = importData2()
    # data = importData('test/test5.txt')
    start_time = time.time()
    initial_solution = initialSolution(data)
    solution = variableNeighborhoodSearch(data, initial_solution)
    end_time = time.time()

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()
