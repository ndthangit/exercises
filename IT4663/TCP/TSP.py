"""Simple Travelling Salesperson Problem (TSP) between cities."""

from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
import time


def create_data_model(dataPath):
    """Stores the data for the problem."""
    data = {}
    with open(dataPath, 'r') as f:
        n = int(f.readline())
        data['distance_matrix'] = []
        for i in range(n):
            data['distance_matrix'].append([int(x) for x in f.readline().split()])
        data['num_vehicles'] = 1
        data['depot'] = 0
    return data
def create_data():
    data = {}
    n = int(input())
    data['NumPoint'] = n
    data['distance_matrix'] = []
    for i in range(n):
        a = list(map(int, input().split()))
        data['distance_matrix'].append(a)
    data['num_vehicles'] = 1
    data['depot'] = 0

    return data




def print_solution(manager, routing, solution):
    """Prints solution on console."""
    # print(f"Objective: {solution.ObjectiveValue()} miles")
    index = routing.Start(0)
    # plan_output = "Route for vehicle 0:\n"
    plan_output = ""
    route_distance = 0
    cout =0
    while not routing.IsEnd(index):
        plan_output += f"{manager.IndexToNode(index)+1} "
        previous_index = index
        index = solution.Value(routing.NextVar(index))
        route_distance += routing.GetArcCostForVehicle(previous_index, index, 0)
        cout += 1
    # plan_output += f" {manager.IndexToNode(index)}\n"
    print(cout)
    print(plan_output)
    # plan_output += f"Route distance: {route_distance}miles\n"


def main():

    """Entry point of the program."""
    # Instantiate the data problem.
    # data = create_data_model("input.txt")
    data = create_data()


    # Create the routing index manager.
    manager = pywrapcp.RoutingIndexManager(
        len(data["distance_matrix"]), data["num_vehicles"], data["depot"]
    )

    # Create Routing Model.
    routing = pywrapcp.RoutingModel(manager)


    def distance_callback(from_index, to_index):
        """Returns the distance between the two nodes."""
        # Convert from routing variable Index to distance matrix NodeIndex.
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data["distance_matrix"][from_node][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)

    # Define cost of each arc.
    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

    # Setting first solution heuristic.
    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC
    )

    # Solve the problem.
    start_time = time.time()
    solution = routing.SolveWithParameters(search_parameters)
    end_time = time.time()

    # Print solution on console.
    if solution:
        print_solution(manager, routing, solution)
        # print(f"Time: {end_time - start_time}s")


if __name__ == "__main__":
    main()
    #1000*1000 result: 22410