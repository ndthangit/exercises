from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
import math


def create_data_model():
    """Tạo dữ liệu từ input"""
    data = {}

    # Thông tin cơ bản từ dòng đầu tiên: 6 2 48 4
    data['num_vehicles'] = 2  # m: số lượng xe
    data['num_customers'] = 48  # n: số lượng khách hàng
    data['num_depots'] = 4  # t: số lượng depot

    # Thông tin về duration và capacity cho mỗi depot
    data['max_duration'] = [500, 500, 500, 500]
    data['vehicle_capacities'] = [200, 200, 200, 200]

    # Tọa độ các điểm (bao gồm cả depot và khách hàng)
    data['locations'] = [
        (-29.730, 64.136), (-30.664, 5.463), (51.642, 5.469), (-13.171, 69.336),
        (-67.413, 68.323), (48.907, 6.274), (5.243, 22.260), (-65.002, 77.234),
        (-4.175, -1.569), (23.029, 11.639), (25.482, 6.287), (-42.615, -26.392),
        (-76.672, 99.341), (-20.673, 57.892), (-52.039, 6.567), (-41.376, 50.824),
        (-91.943, 27.588), (-65.118, 30.212), (18.597, 96.716), (-40.942, 83.209),
        (-37.756, -33.325), (23.767, 29.083), (-43.030, 20.453), (-35.297, -24.896),
        (-54.755, 14.368), (-49.329, 33.374), (57.404, 23.822), (-22.754, 55.408),
        (-56.622, 73.340), (-38.562, -3.705), (-16.779, 19.537), (-11.560, 11.615),
        (-46.545, 97.974), (16.229, 9.320), (1.294, 7.349), (-26.404, 29.529),
        (4.352, 14.685), (-50.665, -23.126), (-22.833, -9.814), (-71.100, -18.616),
        (-7.849, 32.074), (11.877, -24.933), (-18.927, -23.730), (-11.920, 11.755),
        (29.840, 11.633), (12.268, -55.811), (-37.933, -21.613), (42.883, -2.966),
        (4.163, 13.559), (21.387, 17.105), (-36.118, 49.097), (-31.201, 0.235)  # depots
    ]

    # Nhu cầu của khách hàng
    data['demands'] = [12, 8, 16, 5, 12, 5, 13, 20, 13, 18, 7, 6, 9, 9, 4, 25, 5, 17,
                       3, 16, 25, 21, 14, 19, 14, 6, 16, 9, 20, 13, 10, 16, 19, 22,
                       14, 10, 11, 15, 13, 15, 8, 22, 24, 3, 25, 19, 21, 10, 0, 0, 0, 0]

    # Thời gian phục vụ
    data['service_times'] = [2, 7, 21, 24, 1, 17, 6, 5, 7, 1, 4, 10, 2, 16, 23, 18,
                             3, 15, 13, 10, 4, 23, 20, 10, 4, 2, 23, 6, 8, 10, 7, 1,
                             21, 6, 4, 13, 9, 22, 22, 18, 10, 25, 23, 4, 9, 17, 10, 17,
                             0, 0, 0, 0]

    # Time windows
    data['time_windows'] = [
        (399, 525), (121, 299), (389, 483), (204, 304), (317, 458), (160, 257),
        (170, 287), (215, 321), (80, 233), (90, 206), (397, 525), (271, 420),
        (108, 266), (340, 462), (226, 377), (446, 604), (444, 566), (434, 557),
        (319, 460), (192, 312), (414, 572), (371, 462), (378, 472), (308, 477),
        (329, 444), (269, 377), (398, 494), (257, 416), (198, 294), (375, 467),
        (200, 338), (456, 632), (72, 179), (182, 282), (159, 306), (321, 500),
        (322, 430), (443, 564), (207, 348), (457, 588), (203, 382), (75, 167),
        (459, 598), (174, 332), (130, 225), (169, 283), (115, 232), (414, 531),
        (0, 1000), (0, 1000), (0, 1000), (0, 1000)  # depots
    ]

    # Chỉ số của các depot
    data['depot_indices'] = [48, 49, 50, 51]

    # Tính ma trận khoảng cách
    data['distance_matrix'] = compute_distance_matrix(data['locations'])

    return data


def compute_distance_matrix(locations):
    """Tính ma trận khoảng cách Euclidean"""
    n = len(locations)
    matrix = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if i != j:
                x1, y1 = locations[i]
                x2, y2 = locations[j]
                matrix[i][j] = int(math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2) * 100)
    return matrix


def print_solution(data, manager, routing, solution):
    """In kết quả"""
    total_distance = 0
    total_load = 0
    for vehicle_id in range(data['num_vehicles'] * data['num_depots']):
        index = routing.Start(vehicle_id)
        plan_output = f'Route for vehicle {vehicle_id} (Depot {vehicle_id // data["num_vehicles"]}):\n'
        route_distance = 0
        route_load = 0
        route_time = 0

        while not routing.IsEnd(index):
            node_index = manager.IndexToNode(index)
            route_load += data['demands'][node_index]
            plan_output += f' {node_index} Load({route_load}) Time({route_time}) -> '
            previous_index = index
            index = solution.Value(routing.NextVar(index))
            route_distance += routing.GetArcCostForVehicle(previous_index, index, vehicle_id)
            route_time += (data['distance_matrix'][manager.IndexToNode(previous_index)][
                               manager.IndexToNode(index)] // 100 +
                           data['service_times'][node_index])
        node_index = manager.IndexToNode(index)
        plan_output += f' {node_index} Load({route_load}) Time({route_time})\n'
        plan_output += f'Distance of the route: {route_distance / 100:.2f} units\n'
        plan_output += f'Load of the route: {route_load}\n'
        print(plan_output)
        total_distance += route_distance
        total_load += route_load
    print(f'Total distance of all routes: {total_distance / 100:.2f} units')
    print(f'Total load of all routes: {total_load}')


def main():
    """Giải bài toán MDVRPTW"""
    # Khởi tạo data
    data = create_data_model()

    # Tạo routing index manager
    manager = pywrapcp.RoutingIndexManager(
        len(data['distance_matrix']),
        data['num_vehicles'] * data['num_depots'],
        data['depot_indices'])

    # Tạo routing model
    routing = pywrapcp.RoutingModel(manager)

    # Định nghĩa cost của mỗi cung
    def distance_callback(from_index, to_index):
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data['distance_matrix'][from_node][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)
    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

    # Thêm ràng buộc capacity
    def demand_callback(from_index):
        from_node = manager.IndexToNode(from_index)
        return data['demands'][from_node]

    demand_callback_index = routing.RegisterUnaryTransitCallback(demand_callback)
    routing.AddDimensionWithVehicleCapacity(
        demand_callback_index,
        0,  # không có slack
        data['vehicle_capacities'] * data['num_depots'],
        True,  # bắt đầu từ 0
        'Capacity')

    # Thêm ràng buộc time window
    def time_callback(from_index, to_index):
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return (data['distance_matrix'][from_node][to_node] // 100 +
                data['service_times'][from_node])

    time_callback_index = routing.RegisterTransitCallback(time_callback)
    routing.AddDimension(
        time_callback_index,
        1000,  # slack tối đa
        500,  # maximum time per vehicle
        False,  # không bắt đầu từ 0
        'Time')
    time_dimension = routing.GetDimensionOrDie('Time')

    # Thêm time windows
    for node in range(len(data['time_windows'])):
        if node < data['num_customers']:
            index = manager.NodeToIndex(node)
            time_dimension.CumulVar(index).SetRange(
                data['time_windows'][node][0],
                data['time_windows'][node][1])

    # Thiết lập tham số giải
    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC)
    search_parameters.local_search_metaheuristic = (
        routing_enums_pb2.LocalSearchMetaheuristic.GUIDED_LOCAL_SEARCH)
    search_parameters.time_limit.seconds = 30

    # Giải bài toán
    solution = routing.SolveWithParameters(search_parameters)

    # In kết quả
    if solution:
        print_solution(data, manager, routing, solution)
    else:
        print('No solution found!')


if __name__ == '__main__':
    main()