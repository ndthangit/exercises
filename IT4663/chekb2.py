# PYTHON
# PYTHON
from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp


def create_data_model():
    data = {}
    n, q = map(int, input().split())
    data['num'] = n
    data['cap'] = q
    data['matrix'] = []
    for i in range(2 * n + 1):
        c = list(map(int, input().split()))
        data['matrix'].append(c)
    data['req'] = [0] * (2 * data['num'] + 1)
    for i in range(1, n + 1):
        data['req'][i] = 1
        data['req'][i + n] = -1
    return data


def print_out(data, manager, routing, solution):
    print(data['num'])
    index = routing.Start(0)
    plan = []
    while not routing.IsEnd(index):
        pre = index

        index = solution.Value(routing.NextVar(index))
        # plan += f"{manager.IndexToNode(index)} "
        plan.append(index)
    plan.remove(plan[-1])
    for i in plan:
        print(i, end=" ")
    # print(' '.join(map))


data = create_data_model()
manager = pywrapcp.RoutingIndexManager(
    len(data['matrix']), 1, 0
)

routing = pywrapcp.RoutingModel(manager)


def distance_callback(from_node, to_node):
    from_node = manager.IndexToNode(from_node)
    to_node = manager.IndexToNode(to_node)
    return data['matrix'][from_node][to_node]


transit_callback_index = routing.RegisterTransitCallback(distance_callback)
routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)


def demand_callback(from_node):
    from_node = manager.IndexToNode(from_node)
    return data['req'][from_node]


demand_callback_index = routing.RegisterUnaryTransitCallback(demand_callback)
routing.AddDimensionWithVehicleCapacity(
    demand_callback_index,
    0,
    [data['cap']],
    True,
    'Capacity'
)
[routing.AddPickupAndDelivery(manager.NodeToIndex(i), manager.NodeToIndex(i+data['num'])) for i in range(1, data['num'] + 1)]

search_parameters = pywrapcp.DefaultRoutingSearchParameters()
search_parameters.first_solution_strategy = (
    routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC
)
solution = routing.SolveWithParameters(search_parameters)
if solution:
    print_out(data, manager, routing, solution)
