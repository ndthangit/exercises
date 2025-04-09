from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
import math
def import_data_vrp(data_path):
    data = {}
    with open(data_path, 'r') as f:
        # Đọc dòng đầu tiên
        type_vrp, m, n, t = f.readline().split()
        data['Type'] = int(type_vrp)
        data['NumVehicles'] = int(m)
        data['NumCustomers'] = int(n)
        data['NumDaysOrDepotsOrVehicleTypes'] = int(t)
        print(data['Type'])

        # Đọc thông tin D, Q cho từng depot/ngày/loại xe
        data['RouteInfo'] = []
        for _ in range(int(t)):
            D, Q = map(int, f.readline().split())
            data['RouteInfo'].append((D, Q))

        data['Points'] = []
        for _ in range(int(n)):
            parts = f.readline().split()
            data['Points'].append({
                'ID': int(parts[0]),
                'X': float(parts[1]),
                'Y': float(parts[2]),
                'ServiceDuration': int(parts[3]),
                'Demand': int(parts[4]),
                'Frequency': parts[5],
                'VisitCombinations': parts[7:7 + int(parts[6])],
                'TimeWindow': (parts[-2], parts[-1]) if parts[-2] is not None and parts[-1] is not None else None
            })

        data['Depots'] =[]
        for _ in range(int(t)):
            parts = f.readline().split()
            data['Depots'].append({
                'ID': int(parts[0]),
                'X': float(parts[1]),
                'Y': float(parts[2]),
                'ServiceDuration': int(parts[3]),
                'Demand': int(parts[4]),
                'Frequency': parts[5],
                'VisitCombinations': parts[7:7 + int(parts[6])],
                'TimeWindow': (parts[-2], parts[-1]) if parts[-2] is not None and parts[-1] is not None else None
            })
    return data


def create_data_model(data, index):
    model = {}
    """Tạo mô hình dữ liệu cho bài toán"""
    model['depot'] = 0

    # Initialize locations with depots
    model['locations'] = data['Points'].copy()  # Use copy to avoid modifying original data

    # Add the specific point as a single-element list
    model['locations'].insert(0,data['Points'][index])  # Changed from extend to append

    model['max_time'] = sum(data['RouteInfo'][v][0] for v in range(data['NumDaysOrDepotsOrVehicleTypes']))
    model['vehicle_capacities'] = [data['RouteInfo'][v][1] for v in range(data['NumVehicles'])]
    model['num_vehicles'] = data['NumVehicles']
    model['forbidden_nodes'] = []
    model['demands'] = [p['Demand'] for p in model['locations']]
    model['service_times'] = [p['ServiceDuration'] for p in model['locations']]
    model['distance_matrix'] = compute_distance_matrix(model)  # Changed to use model instead of data
    return model


def compute_distance_matrix(model):  # Changed parameter to model
    """Tính ma trận khoảng cách Euclidean giữa các điểm"""
    print(len(model['locations']))
    distance_matrix = []
    for from_loc in model['locations']:
        distances = []
        for to_loc in model['locations']:
            dist = ((from_loc['X'] - to_loc['X']) ** 2 +
                    (from_loc['Y'] - to_loc['Y']) ** 2) ** 0.5
            distances.append(float(dist))
        distance_matrix.append(distances)
    return distance_matrix
def print_solution(data, manager, routing, solution):
    """In kết quả ra màn hình"""
    total_distance = 0
    total_load = 0
    for vehicle_id in range(data['num_vehicles']):
        index = routing.Start(vehicle_id)
        plan_output = f'Route for vehicle {vehicle_id}:\n'
        route_distance = 0
        route_load = 0
        while not routing.IsEnd(index):
            node_index = manager.IndexToNode(index)
            route_load += data['demands'][node_index]
            plan_output += f' {node_index} Load({route_load}) -> '
            previous_index = index
            index = solution.Value(routing.NextVar(index))
            route_distance += routing.GetArcCostForVehicle(
                previous_index, index, vehicle_id)
        plan_output += f' {manager.IndexToNode(index)} Load({route_load})\n'
        plan_output += f'Distance of the route: {route_distance}m\n'
        plan_output += f'Load of the route: {route_load}\n'
        print(plan_output)
        total_distance += route_distance
        total_load += route_load
    print(f'Total distance of all routes: {total_distance}m')
    print(f'Total load of all routes: {total_load}')

def main():
    """Entry point of the program."""
    # Instantiate the data problem.
    io = import_data_vrp("./Cordeau/Cordeau/pr01")
    data = create_data_model(io,0)
    print(len(data['distance_matrix']))
    print(data['service_times'])
    print(data['demands'])
    print(data['vehicle_capacities'])
    print(data['max_time'])
    manager = pywrapcp.RoutingIndexManager(
        len(data['distance_matrix']), data['num_vehicles'], data['depot']
    )


    # Tạo routing model
    routing = pywrapcp.RoutingModel(manager)

    # Tạo hàm chi phí (khoảng cách)
    def distance_callback(from_index, to_index):
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data['distance_matrix'][from_node][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)
    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

    # Thêm ràng buộc tải trọng
    # def demand_callback(from_index):
    #     from_node = manager.IndexToNode(from_index)
    #     return data['demands'][from_node]
    #
    # demand_callback_index = routing.RegisterUnaryTransitCallback(demand_callback)
    # routing.AddDimensionWithVehicleCapacity(
    #     demand_callback_index,
    #     0,  # Không có slack
    #     data['vehicle_capacities'],  # Dung lượng xe
    #     True,  # Bắt đầu đếm từ 0
    #     'Capacity')

    def time_callback(from_index, to_index):
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data['distance_matrix'][from_node][to_node] + data['service_times'][from_node]

    time_callback_index = routing.RegisterTransitCallback(time_callback)

    routing.AddDimension(
        time_callback_index,
        data['max_time'],  # Slack time
        data['max_time'],  # Maximum time per vehicle
        False,  # Don't start at 0
        'Time')
    time_dimension = routing.GetDimensionOrDie('Time')

    for node in range(0, len(data['distance_matrix'])):
        if node != 0 and node != len(data['distance_matrix'])-1:
            routing.AddDisjunction([manager.NodeToIndex(node)], data['service_times'][node])

    for node in range(1, len(data['distance_matrix']) - 1):
        index = manager.NodeToIndex(node)
        time_dimension = routing.GetDimensionOrDie('Time')
        # Thêm penalty dựa trên service time và khoảng cách
        penalty = int(data['service_times'][node])  # Phạt dựa trên thời gian phục vụ
        routing.AddDisjunction([index], penalty)
        # Thêm ràng buộc thời gian nếu có time window
        if data['locations'][node]['TimeWindow']:
            start, end = data['locations'][node]['TimeWindow']
            time_dimension.CumulVar(index).SetRange(int(start), int(end))

    # Thiết lập chiến lược tìm kiếm
    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC)

    # Giải bài toán
    solution = routing.SolveWithParameters(search_parameters)

    # In kết quả
    if solution:
        print_solution(data, manager, routing, solution)
    else:
        print("Không tìm thấy giải pháp!")

if __name__ == '__main__':
    main()