from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
import comparison
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

    # Passenger request
    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

    # Parcel request
    for i in range(1, data['NumParcel'] + 1):
        data['Delivery']['ParcelRequest'].append(
            [i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']])


    data['Request']= [0]*(2 * (data['NumParcel'] + 2*data['NumPassenger'])+1)
    for i in data['Quantity']:
        data['Request'][i + data['NumParcel']] = i
        data['Request'][i + 2 * data['NumParcel'] + data['NumPassenger']] = -i

    return data
# print(importData("test/test2.txt"))

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
    for i in data['Quantity']:
        data['Request'][i + n] = i
        data['Request'][i + 2 * n + m] = -i

    return data


def print_solution(data, manager, routing, solution):
    """Prints solution on console."""
    print(f"Objective: {solution.ObjectiveValue()}")
    print(f"Number of vehicles: {data['NumTaxis']}")
    total_distance = 0
    for vehicle_id in range(data["NumTaxis"]):

        index = routing.Start(vehicle_id)
        plan_output = f"Route for vehicle {vehicle_id}:\n"
        route_distance = 0
        numPoint=1
        while not routing.IsEnd(index):
            plan_output += f" {manager.IndexToNode(index)} -> "
            previous_index = index
            index = solution.Value(routing.NextVar(index))
            route_distance += routing.GetArcCostForVehicle(
                previous_index, index, vehicle_id
            )
            numPoint+=1
        plan_output += f"{manager.IndexToNode(index)}\n"
        plan_output += f"Distance of the route: {route_distance}m\n"
        plan_output += f"Length of route: {numPoint}\n"

        print(plan_output)
        total_distance += route_distance
    print(f"Total Distance of all routes: {total_distance}m")

def print_out_put(data, manager, routing, solution):
    # print(data['NumTaxis'])
    routes=[]
    for vehicle_id in range(data["NumTaxis"]):
        index = routing.Start(vehicle_id)
        plan_output = ""
        numPoint = 1
        route=[]
        while not routing.IsEnd(index):
            route.append(manager.IndexToNode(index))
            index = solution.Value(routing.NextVar(index))
            numPoint += 1
        route.append(manager.IndexToNode(index))
        plan_output += f"{numPoint}\n"
        for i in route:
            plan_output += f"{i} "
        # print(plan_output)
        routes.append(route)
    return routes

def find_solution(data):

    manager = pywrapcp.RoutingIndexManager(
        len(data["Matrix"]), data["NumTaxis"], data["Depot"]
    )

    # Create Routing Model.
    routing = pywrapcp.RoutingModel(manager)

    # Define cost of each arc.
    def distance_callback(from_index, to_index):
        """Returns the manhattan distance between the two nodes."""
        # Convert from routing variable Index to distance matrix NodeIndex.
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data['Matrix'][from_node][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)
    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

    # Add Distance constraint.
    dimension_name = "Distance"
    routing.AddDimension(
        transit_callback_index,
        0,  # no slack
        3000,  # vehicle maximum travel distance
        True,  # start cumul to zero
        dimension_name,
    )
    distance_dimension = routing.GetDimensionOrDie(dimension_name)
    distance_dimension.SetGlobalSpanCostCoefficient(100)

    # Define Transportation Constraints.
    for request in data['Delivery']['PassengerRequest']:
        pickup_index = manager.NodeToIndex(request[0])
        delivery_index = manager.NodeToIndex(request[1])
        routing.AddPickupAndDelivery(pickup_index, delivery_index)

        routing.solver().Add(
            routing.NextVar(pickup_index) == delivery_index
        )
        routing.solver().Add(
            routing.VehicleVar(pickup_index) == routing.VehicleVar(delivery_index)
        )
        routing.solver().Add(
            distance_dimension.CumulVar(pickup_index) + 1 <= distance_dimension.CumulVar(delivery_index)
        )

    for request in data['Delivery']['ParcelRequest']:
        pickup_index = manager.NodeToIndex(request[0])
        delivery_index = manager.NodeToIndex(request[1])
        routing.AddPickupAndDelivery(pickup_index, delivery_index)
        routing.solver().Add(
            routing.VehicleVar(pickup_index) == routing.VehicleVar(delivery_index)
        )
        routing.solver().Add(
            distance_dimension.CumulVar(pickup_index)
            <= distance_dimension.CumulVar(delivery_index)
        )

    # Add Capacity constraint.
    def demand_callback(from_index):
        """Returns the demand of the node."""
        # Convert from routing variable Index to demands NodeIndex.
        from_node = manager.IndexToNode(from_index)
        return data['Request'][from_node]

    demand_callback_index = routing.RegisterUnaryTransitCallback(demand_callback)
    routing.AddDimensionWithVehicleCapacity(
        demand_callback_index,
        0,  # null capacity slack
        data["Capacity"],  # vehicle maximum capacities
        True,  # start cumul to zero
        "Capacity",
    )

    # Setting first solution heuristic.
    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.RoutingSearchStatus.ROUTING_SUCCESS
    )


    search_parameters.time_limit.FromSeconds(60)

    # Solve the problem.
    solution = routing.SolveWithParameters(search_parameters)

    # Print solution on console.
    if solution:
        print_solution(data, manager, routing, solution)
        route1 = print_out_put(data, manager, routing, solution)
        # print(comparison.route_distance(data['Matrix'], route1))
        return print_out_put(data, manager, routing, solution)
    else:
        return None


def main():
    """Entry point of the program."""
    # Instantiate the data problem.
    # data = importData("test/test5.txt")
    # print(comparison.route_distance_from_path(data['Matrix'], "result/test5.txt"))
    # data = importData2()
    # find_solution(data)
    for i in range(1,2):
        data = importData(f"test/test{i}.txt")
        # print(comparison.route_distance_from_path(data['Matrix'], f"result/test{i}.txt"))
        route = find_solution(data)
        print(f"Output {i}: {comparison.route_distance(data['Matrix'],route)}, Result {i}: {comparison.route_distance_from_path(data['Matrix'], f'result/test{i}.txt')}")

    # print(data['Matrix'][0][4])
    # print(data['Matrix'][4][6])
    # print(data['Matrix'][6][10])
    # print(data['Matrix'][10][3])
    # print(data['Matrix'][3][9])
    # print(data['Matrix'][9][12])
    # print(data['Matrix'][12][2])
    # print(data['Matrix'][2][8])
    # print(data['Matrix'][8][0])


if __name__ == "__main__":
    main()