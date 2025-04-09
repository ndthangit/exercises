
from ortools.constraint_solver import pywrapcp
from ortools.constraint_solver import routing_enums_pb2


def create_data_model():
    """Stores the data for the problem."""
    data = {}
    n = int(input())
    data['passenger'] = n
    data["time_windows"] = [[0,100000]]
    data["request"] = [0]

    for i in range(n):
        a, b, c = map(int, input().split())
        data["time_windows"].append([a, b])
        data["request"].append(c)

    data["time_matrix"] = []
    for i in range(n + 1):
        row = list(map(int, input().split()))
        data["time_matrix"].append(row)

    data["num_vehicles"] = 1
    data["depot"] = 0
    return data


def print_solution(manager, routing, solution):
    """Prints solution on console."""
    print(f"Objective: {solution.ObjectiveValue()} miles")
    index = routing.Start(0)
    plan_output = "Route for vehicle 0:\n"
    route_distance = 0
    time_dimension = routing.GetDimensionOrDie("Time")

    while not routing.IsEnd(index):
        node_index = manager.IndexToNode(index)
        time_var = time_dimension.CumulVar(index)
        plan_output += f" {node_index} time ({solution.Min(time_var)},{solution.Max(time_var)}) ->"
        previous_index = index
        index = solution.Value(routing.NextVar(index))
        route_distance += routing.GetArcCostForVehicle(previous_index, index, 0)
    plan_output += f" {manager.IndexToNode(index)}\n"
    print(plan_output)
    plan_output += f"Route distance: {route_distance}miles\n"

def print_output(manager, routing, solution):
    s = []
    index = routing.Start(0)
    while not routing.IsEnd(index):
        s.append(manager.IndexToNode(index))
        index = solution.Value(routing.NextVar(index))
    s.append(manager.IndexToNode(index))

    N = len(s) - 2  # Bỏ qua kho bắt đầu và kết thúc
    print(N)
    print(" ".join(map(str, s[1:-1])))  # In ra các điểm trung gian


def main():
    """Entry point of the program."""
    # Instantiate the data problem.
    data = create_data_model()

    # Create the routing index manager.
    manager = pywrapcp.RoutingIndexManager(
        len(data["time_matrix"]), data["num_vehicles"], data["depot"]
    )

    # Create Routing Model.
    routing = pywrapcp.RoutingModel(manager)

    def distance_callback(from_index, to_index):
        """Returns the distance between the two nodes."""
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data["time_matrix"][from_node][to_node] + data["request"][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)

    # Define cost of each arc.
    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

    # # Add Time Windows constraint.
    time = "Time"
    routing.AddDimension(
        transit_callback_index,
        0,  # allow waiting time
        100000,  # maximum time per vehicle
        False,  # Don't force start cumul to zero.
        time,
    )
    time_dimension = routing.GetDimensionOrDie(time)
    #
    # # Add time window constraints for each location except depot.
    for location_idx, time_window in enumerate(data["time_windows"]):
        if location_idx == 0:
            continue
        index = manager.NodeToIndex(location_idx )
        time_dimension.CumulVar(index).SetRange(time_window[0], time_window[1])
    #
    # # Add time window constraints for each vehicle start node.
    depot_idx = data["depot"]
    for vehicle_id in range(data["num_vehicles"]):
        index = routing.Start(vehicle_id)
        time_dimension.CumulVar(index).SetRange(
            data["time_windows"][depot_idx][0], data["time_windows"][depot_idx][1]
        )
    for i in range(data["num_vehicles"]):
        routing.AddVariableMinimizedByFinalizer(
            time_dimension.CumulVar(routing.Start(i))
        )
        routing.AddVariableMinimizedByFinalizer(time_dimension.CumulVar(routing.End(i)))

    # Setting first solution heuristic.
    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC
    )

    # Solve the problem.
    solution = routing.SolveWithParameters(search_parameters)

    # Print solution on console.
    if solution:
        # print_output(manager, routing, solution)
        print_solution(manager, routing, solution)
    else:
        print("Không tìm thấy lời giải")


if __name__ == "__main__":
    main()