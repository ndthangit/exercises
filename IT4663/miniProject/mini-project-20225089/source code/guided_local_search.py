import copy
import random
import time
import math

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

def main():
    data = importData2()
    # data = importData('test/test5.txt')

    def calculateRouteDistance(route):
        distance = 0
        for i in range(len(route) - 1):
            distance += data['Matrix'][route[i]][route[i + 1]]
        return distance

    def calculateTotalRoute(routes):
        return sum(calculateRouteDistance(route) for route in routes)

    def calculateError(routes):
        error_count = 0
        problematic_points = {'scheduleError': [], 'pointError': [], 'capacityError': []}
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
                    problematic_points['capacityError'].append((idx, point))
            for req in data['Delivery']['PassengerRequest']:
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
            for req in data['Delivery']['ParcelRequest']:
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

    def initialSolution():
        taxis = [[] for _ in range(data['NumTaxis'])]
        for point in range(1, 2 * (data['NumPassenger'] + data['NumParcel']) + 1):
            taxi_idx = random.randint(0, data['NumTaxis'] - 1)
            taxis[taxi_idx].append(point)
        for i in range(data['NumTaxis']):
            taxis[i].insert(0, 0)
            taxis[i].append(0)
        best_error, best_problematic_points, best_point_in_route, best_error_cap = calculateError(taxis)
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

    # def generateNeighbors(solution, error_cap):
    #     neighbors = []
    #     idx = random.randint(0, len(solution) - 1)
    #     if idx in error_cap and error_cap[idx] == 1:
    #         solution_copy = copy.deepcopy(solution)
    #         possible_dropoffs = [
    #             point for point in solution_copy[idx]
    #             if 2 * data['NumPassenger'] + data['NumParcel'] + 1 <= point <= 2 * data['NumPassenger'] + 2 * data['NumParcel']
    #         ]
    #         if not possible_dropoffs:
    #             return neighbors
    #         dropoff = random.choice(possible_dropoffs)
    #         pickup = dropoff - data['NumParcel'] - data['NumPassenger']
    #         if pickup in solution_copy[idx]:
    #             solution_copy[idx].remove(dropoff)
    #             pickup_pos = solution_copy[idx].index(pickup)
    #             for i in range(pickup_pos + 1, len(solution_copy[idx])):
    #                 new_solution = copy.deepcopy(solution_copy)
    #                 new_solution[idx].insert(i, dropoff)
    #                 neighbors.append(new_solution)
    #     return neighbors
    def neighborhood1(solution, error_cap):
        neighbors = []
        route_indices = [i for i in range(len(solution)) if i in error_cap and error_cap[i] == 1]
        if not route_indices:
            return neighbors

        idx = random.choice(route_indices)
        route = solution[idx]

        # Kiểm tra và đảm bảo route hợp lệ (bắt đầu và kết thúc bằng 0)
        if len(route) < 2 or route[0] != 0 or route[-1] != 0:
            return neighbors

        # Chỉ xử lý các điểm không phải 0
        passenger_dropoffs = []
        parcel_dropoffs = []
        for point in route[1:-1]:  # Bỏ qua điểm đầu và cuối (0)
            if 2 * data['NumPassenger'] + data['NumParcel'] + 1 <= point <= 2 * data['NumPassenger'] + 2 * data[
                'NumParcel']:
                if point <= 2 * data['NumPassenger'] + data['NumParcel']:
                    passenger_dropoffs.append(point)
                else:
                    parcel_dropoffs.append(point)

        if passenger_dropoffs:
            dropoff = random.choice(passenger_dropoffs)
            pickup = dropoff - data['NumParcel'] - data['NumPassenger']

            if pickup in route[1:-1]:
                for new_pos in range(1, len(route) - 1):
                    if new_pos == route.index(pickup):
                        continue

                    new_solution = copy.deepcopy(solution)
                    new_route = new_solution[idx]

                    # Xóa cả pickup và dropoff (không bao giờ xóa điểm 0)
                    new_route.remove(pickup)
                    new_route.remove(dropoff)

                    # Chèn lại và đảm bảo không chèn vào vị trí 0 đầu/cuối
                    new_route.insert(new_pos, pickup)
                    new_route.insert(new_pos + 1, dropoff)

                    # Kiểm tra và xóa các điểm 0 ở giữa nếu có
                    new_route = [0] + [p for p in new_route[1:-1] if p != 0] + [0]
                    neighbors.append(new_solution)
            return neighbors

        if parcel_dropoffs:
            dropoff = random.choice(parcel_dropoffs)
            pickup = dropoff - data['NumParcel'] - data['NumPassenger']

            if pickup in route[1:-1]:
                pickup_pos = route.index(pickup)
                for new_pos in range(pickup_pos + 1, len(route) - 1):
                    if route[new_pos] == dropoff:
                        continue

                    new_solution = copy.deepcopy(solution)
                    new_route = new_solution[idx]
                    new_route.remove(dropoff)
                    new_route.insert(new_pos, dropoff)

                    # Đảm bảo không có 0 ở giữa
                    new_route = [0] + [p for p in new_route[1:-1] if p != 0] + [0]
                    neighbors.append(new_solution)

        return neighbors

    def neighborhood2(solution, error_cap):
        neighbors = []

        # Select a random route
        route_idx = random.randint(0, len(solution) - 1)
        route = solution[route_idx]

        # Kiểm tra nếu tuyến đường quá ngắn hoặc không có điểm 0 ở cuối
        if len(route) < 2 or route[-1] != 0:
            return neighbors

        # Lọc điểm pickup (tận dụng điều kiện <= n + m)
        max_pickup = data['NumPassenger'] + data['NumParcel']
        route_pickups = [point for point in route if 0 < point <= max_pickup]

        if not route_pickups:
            return neighbors

        pickup = random.choice(route_pickups)

        # Xác định dropoff tương ứng
        if pickup <= data['NumPassenger']:  # Passenger pickup
            dropoff = pickup + data['NumParcel'] + data['NumPassenger']
            is_passenger = True
        else:  # Parcel pickup
            dropoff = pickup + data['NumParcel'] + data['NumPassenger']
            is_passenger = False

        if dropoff not in route:
            return neighbors

        pickup_pos = route.index(pickup)
        dropoff_pos = route.index(dropoff)

        if is_passenger:
            # Xử lý đặc biệt cho Passenger: di chuyển cả pickup và dropoff
            for new_pickup_pos in range(1, len(route) - 2):  # Đảm bảo chừa chỗ cho dropoff và điểm 0
                if new_pickup_pos == pickup_pos:
                    continue

                new_solution = copy.deepcopy(solution)
                new_route = new_solution[route_idx]

                # Remove both pickup and dropoff
                new_route.remove(pickup)
                new_route.remove(dropoff)

                # Insert pickup at new position and dropoff right after
                new_route.insert(new_pickup_pos, pickup)
                new_route.insert(new_pickup_pos + 1, dropoff)

                # Đảm bảo điểm 0 ở cuối
                if new_route[-1] != 0:
                    new_route.remove(0)
                    new_route.append(0)

                neighbors.append(new_solution)
        else:
            # Xử lý bình thường cho Parcel
            for new_pos in range(1, dropoff_pos):  # Không chèn vào vị trí cuối
                if new_pos == pickup_pos:
                    continue

                new_solution = copy.deepcopy(solution)
                new_route = new_solution[route_idx]
                new_route.remove(pickup)
                new_route.insert(new_pos, pickup)

                # Đảm bảo điểm 0 ở cuối
                if new_route[-1] != 0:
                    new_route.remove(0)
                    new_route.append(0)

                neighbors.append(new_solution)

        return neighbors

    def neighborhood3(solution, error_cap):
        neighbors = []
        if len(solution) < 2:
            return neighbors

        route_indices = list(range(len(solution)))
        if error_cap:
            faulty_routes = [i for i in route_indices if i in error_cap]
            if faulty_routes:
                route_indices = faulty_routes

        source_route_idx = random.choice(route_indices)
        source_route = solution[source_route_idx]

        # Kiểm tra route nguồn hợp lệ
        if len(source_route) < 2 or source_route[0] != 0 or source_route[-1] != 0:
            return neighbors

        valid_pairs = []
        for i in range(1, len(source_route) - 1):  # Bỏ qua điểm 0 đầu/cuối
            pickup = source_route[i]
            if pickup > data['NumPassenger'] + data['NumParcel']:
                continue

            if 0 < pickup <= data['NumPassenger']:
                dropoff = pickup + data['NumParcel'] + data['NumPassenger']
                if i + 1 < len(source_route) - 1 and source_route[i + 1] == dropoff:
                    valid_pairs.append((pickup, dropoff))
            else:
                dropoff = pickup + data['NumParcel'] + data['NumPassenger']
                if dropoff in source_route[i + 1:-1]:  # Chỉ xét đến phần tử kế cuối
                    valid_pairs.append((pickup, dropoff))

        if not valid_pairs:
            return neighbors

        pickup, dropoff = random.choice(valid_pairs)
        target_route_idx = random.choice([i for i in range(len(solution)) if i != source_route_idx])
        target_route = solution[target_route_idx]

        # Kiểm tra route đích hợp lệ
        if len(target_route) < 2 or target_route[0] != 0 or target_route[-1] != 0:
            return neighbors

        new_solution = copy.deepcopy(solution)
        source_route = new_solution[source_route_idx]
        target_route = new_solution[target_route_idx]

        # Xóa cặp khỏi route nguồn (không bao giờ xóa điểm 0)
        source_route.remove(pickup)
        source_route.remove(dropoff)

        # Chèn vào route đích trước điểm 0 cuối cùng
        insert_pos = len(target_route) - 1

        if 0 < pickup <= data['NumPassenger']:
            target_route.insert(insert_pos, pickup)
            target_route.insert(insert_pos + 1, dropoff)
        else:
            target_route.insert(insert_pos, pickup)
            dropoff_pos = random.randint(insert_pos + 1, len(target_route) - 1)
            target_route.insert(dropoff_pos, dropoff)

        # Đảm bảo không có 0 ở giữa cả 2 route
        new_solution[source_route_idx] = [0] + [p for p in source_route[1:-1] if p != 0] + [0]
        new_solution[target_route_idx] = [0] + [p for p in target_route[1:-1] if p != 0] + [0]

        neighbors.append(new_solution)
        return neighbors

    def generateNeighbors(solution, error_cap):
        neighbors = []

        neighbors.extend(neighborhood1(solution, error_cap))
        neighbors.extend(neighborhood2(solution, error_cap))
        neighbors.extend(neighborhood3(solution, error_cap))
        return neighbors

    def calculateAugmentedObjective(solution, penalties, lambda_param=0.3):
        error_count, problematic_points, _, _ = calculateError(solution)
        total_distance = calculateTotalRoute(solution)
        penalty_sum = 0
        for req in problematic_points['pointError']:
            penalty_key = tuple(req)
            penalty_sum += penalties.get(penalty_key, 0)
        for req in problematic_points['scheduleError']:
            penalty_key = tuple(req)
            penalty_sum += penalties.get(penalty_key, 0)
        for cap_error in problematic_points['capacityError']:
            penalty_key = cap_error
            penalty_sum += penalties.get(penalty_key, 0)
        return total_distance + lambda_param * penalty_sum

    def updatePenalties(solution, penalties, lambda_param=0.3):
        _, problematic_points, _, _ = calculateError(solution)
        features = []
        utilities = []
        total_distance = calculateTotalRoute(solution)
        for req in problematic_points['pointError'] + problematic_points['scheduleError']:
            penalty_key = tuple(req)
            utility = 1.0 / (1 + penalties.get(penalty_key, 0))
            features.append(penalty_key)
            utilities.append(utility)
        for cap_error in problematic_points['capacityError']:
            penalty_key = cap_error
            utility = 1.0 / (1 + penalties.get(penalty_key, 0))
            features.append(penalty_key)
            utilities.append(utility)
        if utilities:
            max_utility = max(utilities)
            for i, feature in enumerate(features):
                if math.isclose(utilities[i], max_utility):
                    penalties[feature] = penalties.get(feature, 0) + 1
        return penalties

    def guidedLocalSearch(solution, max_iterations=100000, max_time=30, lambda_param=0.3):
        start_time = time.time()
        best_solution = copy.deepcopy(solution)
        best_error, _, _, best_error_cap = calculateError(best_solution)
        penalties = {}
        best_objective = calculateAugmentedObjective(best_solution, penalties, lambda_param)

        iteration = 0
        while iteration < max_iterations and (time.time() - start_time) < max_time and best_error > 0:
            neighbor_solutions = generateNeighbors(best_solution, best_error_cap)
            for neighbor in neighbor_solutions:
                current_error, _, _, current_error_cap = calculateError(neighbor)
                current_objective = calculateAugmentedObjective(neighbor, penalties, lambda_param)
                if current_objective < best_objective:
                    best_solution = copy.deepcopy(neighbor)
                    best_error = current_error
                    best_error_cap = current_error_cap
                    best_objective = current_objective
                elif math.isclose(current_objective, best_objective) and current_error < best_error:
                    best_solution = copy.deepcopy(neighbor)
                    best_error = current_error
                    best_error_cap = current_error_cap
                    best_objective = current_objective
            penalties = updatePenalties(best_solution, penalties, lambda_param)
            iteration += 1

        return best_solution

    start_time = time.time()
    solution = guidedLocalSearch(initialSolution())
    end_time = time.time()
    # print(f"Guided Local Search took {end_time - start_time} seconds.")
    # print(calculateTotalRoute(solution))

    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))

if __name__ == "__main__":
    main()
