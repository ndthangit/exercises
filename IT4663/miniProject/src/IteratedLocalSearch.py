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

    def initialSolution():
        taxis = [[] for _ in range(data['NumTaxis'])]
        for point in range(1, 2*(data['NumPassenger']+data['NumParcel'])+1):
            # Chọn ngẫu nhiên một taxi
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
    def calculateError(routes):
        error_count = 0
        problematic_points = {
            'scheduleError': [],
            'pointError': []
        }
        point_in_route ={}
        error_cap = {}


        for idx, route in enumerate(routes):
            cap = 0
            for point in route:
                # Check capacity constraints
                cap += data['Request'][point]
                point_in_route[point] = idx

                if cap < 0 or cap > data['Capacity'][idx]:
                    error_count += 1
                    error_cap[idx] = 1

            # Check passenger requests (pickup must be immediately before dropoff)
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

            # Check parcel requests (pickup must come before dropoff)
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

    # def initialSolution():
    #     taxis = [[] for _ in range(data['NumTaxis'])]
    #     all_requests = []
    #     for req in data['Delivery']['PassengerRequest']:
    #         all_requests.append((req[0], req[1]))
    #     for req in data['Delivery']['ParcelRequest']:
    #         all_requests.append((req[0], req[1]))
    #
    #     random.shuffle(all_requests)
    #     for i, req in enumerate(all_requests):
    #         taxi_idx = i % data['NumTaxis']
    #         taxis[taxi_idx].append(req[0])
    #         taxis[taxi_idx].append(req[1])
    #
    #     for i in range(data['NumTaxis']):
    #         taxis[i].insert(0, 0)
    #         taxis[i].append(0)
    #
    #     return taxis

    check1 = [
            [0, 1, 7, 2, 8, 3, 9, 4, 5, 6, 11, 10, 12, 0],
            [0, 0]
        ]
    # check2 = [
    #         [0, 8, 6, 5, 11, 12, 0],
    #         [0, 1, 9, 3, 2, 7, 4, 10, 0]
    #     ]
    # print(calculateError(check1))
    # print(calculateError(check2))
    # print(isFeasible(check1))
    # print(isFeasible(check2))
    # print(initialSolution())
    # print(isFeasible(initialSolution()))
    # print(calculateTotalRoute(initialSolution()))




    # def generateNeighbors(solution, error_cap):
    #     neighbors = []
    #
    #     idx = random.randint(0, len(solution) - 1)
    #
    #     solution_copy = copy.deepcopy(solution)
    #     if idx in error_cap and error_cap[idx] == 1:
    #         dropoff = random.randint(2 * data['NumPassenger']+ data['NumParcel'] + 1, 2 * data['NumPassenger']+  2*data['NumParcel'] )
    #         pickup = dropoff - data['NumPassenger'] - data['NumParcel']
    #         solution_copy[idx].remove(dropoff)
    #         for i in range(solution_copy[idx].index(pickup), len(solution_copy[idx])):
    #             solution_copy[idx].insert(i, dropoff)
    #             neighbors.append(solution_copy)
    #     return neighbors
    # def neighborhood1(solution, error_cap):
    #     neighbors = []
    #
    #     idx = random.randint(0, len(solution) - 1)
    #
    #     if idx in error_cap and error_cap[idx] == 1:
    #         solution_copy = copy.deepcopy(solution)
    #
    #         # Lấy tất cả các điểm dropoff trong route[idx] và thuộc phạm vi yêu cầu
    #         possible_dropoffs = [
    #             point for point in solution_copy[idx]
    #             if 2 * data['NumPassenger'] + data['NumParcel'] + 1 <= point <= 2 * data['NumPassenger'] + 2 * data[
    #                 'NumParcel']
    #         ]
    #
    #         if not possible_dropoffs:  # Nếu không có điểm dropoff nào thỏa mãn
    #             return neighbors
    #
    #         dropoff = random.choice(possible_dropoffs)  # Chọn ngẫu nhiên 1 điểm dropoff hợp lệ
    #         pickup = dropoff - data['NumParcel'] - data['NumPassenger']  # Tính điểm pickup tương ứng
    #
    #         if pickup in solution_copy[idx]:
    #             solution_copy[idx].remove(dropoff)
    #             pickup_pos = solution_copy[idx].index(pickup)
    #
    #             for i in range(pickup_pos + 1, len(solution_copy[idx])):
    #                 new_solution = copy.deepcopy(solution_copy)
    #                 new_solution[idx].insert(i, dropoff)
    #                 neighbors.append(new_solution)
    #
    #     return neighbors
    def neighborhood1(solution, error_cap):
        neighbors = []
        route_indices = [i for i in range(len(solution)) if i in error_cap and error_cap[i] == 1]
        if not route_indices:
            return neighbors

        idx = random.choice(route_indices)
        route = solution[idx]

        # Đảm bảo route có ít nhất 2 điểm (0 và 0)
        if len(route) < 2:
            return neighbors

        passenger_dropoffs = []
        parcel_dropoffs = []

        # Chỉ xét các điểm không phải điểm đầu/cuối (0)
        for point in route[1:-1]:
            if 2 * data['NumPassenger'] + data['NumParcel'] + 1 <= point <= 2 * data['NumPassenger'] + 2 * data[
                'NumParcel']:
                if point <= 2 * data['NumPassenger'] + data['NumParcel']:
                    passenger_dropoffs.append(point)
                else:
                    parcel_dropoffs.append(point)

        if passenger_dropoffs:
            dropoff = random.choice(passenger_dropoffs)
            pickup = dropoff - data['NumParcel'] - data['NumPassenger']

            if pickup in route[1:-1]:  # Chỉ xét các điểm không phải 0
                for new_pos in range(1, len(route) - 1):
                    if new_pos == route.index(pickup):
                        continue

                    new_solution = copy.deepcopy(solution)
                    new_route = new_solution[idx]
                    new_route.remove(pickup)
                    new_route.remove(dropoff)
                    new_route.insert(new_pos, pickup)
                    new_route.insert(new_pos + 1, dropoff)

                    # Đảm bảo điểm đầu/cuối vẫn là 0
                    if new_route[0] != 0 or new_route[-1] != 0:
                        new_route[0], new_route[-1] = 0, 0

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

                    if new_route[0] != 0 or new_route[-1] != 0:
                        new_route[0], new_route[-1] = 0, 0

                    neighbors.append(new_solution)

        return neighbors
    def neighborhood2(solution, error_cap):
        neighbors = []

        # Select a random route
        route_idx = random.randint(0, len(solution) - 1)
        route = solution[route_idx]

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
            for new_pickup_pos in range(1, len(route) - 1):
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

                neighbors.append(new_solution)
        else:
            # Xử lý bình thường cho Parcel
            for new_pos in range(1, dropoff_pos):
                if new_pos == pickup_pos:
                    continue

                new_solution = copy.deepcopy(solution)
                new_route = new_solution[route_idx]
                new_route.remove(pickup)
                new_route.insert(new_pos, pickup)
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

        # Bỏ qua điểm đầu/cuối (0) khi tìm cặp
        valid_pairs = []
        for i in range(1, len(source_route) - 1):
            pickup = source_route[i]
            if pickup > data['NumPassenger'] + data['NumParcel']:
                continue

            if 0 < pickup <= data['NumPassenger']:
                dropoff = pickup + data['NumParcel'] + data['NumPassenger']
                if i + 1 < len(source_route) - 1 and source_route[i + 1] == dropoff:
                    valid_pairs.append((pickup, dropoff))
            else:
                dropoff = pickup + data['NumParcel'] + data['NumPassenger']
                if dropoff in source_route[i + 1:-1]:
                    valid_pairs.append((pickup, dropoff))

        if not valid_pairs:
            return neighbors

        pickup, dropoff = random.choice(valid_pairs)
        target_route_idx = random.choice([i for i in range(len(solution)) if i != source_route_idx])

        new_solution = copy.deepcopy(solution)
        source_route = new_solution[source_route_idx]
        target_route = new_solution[target_route_idx]

        source_route.remove(pickup)
        source_route.remove(dropoff)

        # Luôn chèn trước điểm 0 cuối cùng
        insert_pos = len(target_route) - 1

        if 0 < pickup <= data['NumPassenger']:
            target_route.insert(insert_pos, pickup)
            target_route.insert(insert_pos + 1, dropoff)
        else:
            target_route.insert(insert_pos, pickup)
            dropoff_pos = random.randint(insert_pos + 1, len(target_route) - 1)
            target_route.insert(dropoff_pos, dropoff)

        # Đảm bảo cả 2 route vẫn có 0 ở đầu/cuối
        if source_route[0] != 0 or source_route[-1] != 0:
            source_route[0], source_route[-1] = 0, 0
        if target_route[0] != 0 or target_route[-1] != 0:
            target_route[0], target_route[-1] = 0, 0

        neighbors.append(new_solution)
        return neighbors

    def generateNeighbors(solution, error_cap):
        neighbors = []

        neighbors.extend(neighborhood1(solution, error_cap))
        neighbors.extend(neighborhood2(solution, error_cap))
        neighbors.extend(neighborhood3(solution, error_cap))
        return neighbors



    def iteratedLocalSearch(solution, max_iterations=100000, max_time=10):
        start_time = time.time()

        best_solution = copy.deepcopy(solution)
        best_error, best_problematic_points, best_point_in_route, best_error_cap = calculateError(best_solution)

        iteration = 0
        while iteration < max_iterations and (time.time() - start_time) < max_time and best_error > 0:
            # current_solution = copy.deepcopy(best_solution)
            neighbor_solution = generateNeighbors(best_solution, best_error_cap )

            for solution in neighbor_solution:
                current_error, problematic_points, point_in_route, error_cap = calculateError(solution)

                if current_error < best_error:

                    best_solution = copy.deepcopy(solution)
                    best_error = current_error
                elif current_error == best_error:
                    if calculateTotalRoute( solution) < calculateTotalRoute(best_solution):
                        best_solution = copy.deepcopy(solution)
                        best_error = current_error

            iteration += 1

        return best_solution


    # print(initialSolution())
    # print(iteratedLocalSearch(initialSolution(), max_iterations=100000, max_time=30))

    start_time = time.time()

    solution = iteratedLocalSearch(initialSolution(),max_time=5)
    end_time = time.time()

    # print(f"Time: {end_time - start_time}")
    # print(calculateTotalRoute(solution))


    print(data['NumTaxis'])
    for route in solution:
        print(len(route))
        print(' '.join(map(str, route)))


if __name__ == "__main__":
    main()
