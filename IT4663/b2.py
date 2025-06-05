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
[routing.AddPickupAndDelivery(manager.NodeToIndex(i),manager.NodeToIndex(i+data['num'])) for i in range(1, data['num']+1)]

search_parameters = pywrapcp.DefaultRoutingSearchParameters()
search_parameters.first_solution_strategy = (
    routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC
)
solution = routing.SolveWithParameters(search_parameters)
if solution:
    print_out(data, manager, routing, solution)

# 3 2
# 0 8 5 1 10 5 9
# 9 0 5 6 6 2 8
# 2 2 0 3 8 7 2
# 5 3 4 0 3 2 7
# 9 6 8 7 0 9 10
# 3 8 10 6 5 0 2
# 3 4 4 5 2 2 0
#
# 3
# 3 1 4 2 6 5

# 30 56 5
# 24 30 47
# 25 23 9
# 22 2 28
# 23 7 50
# 6 15 17
# 18 23 44
# 26 24 34
# 18 26 50
# 6 30 42
# 28 18 3
# 14 25 41
# 14 22 35
# 17 15 42
# 1 9 40
# 26 2 15
# 26 5 42
# 9 29 17
# 20 4 33
# 25 28 44
# 26 23 24
# 6 17 42
# 22 13 4
# 12 15 6
# 5 3 48
# 21 24 6
# 12 21 24
# 3 30 21
# 25 9 22
# 11 13 19
# 5 27 38
# 1 8 12
# 28 29 26
# 16 6 1
# 1 17 2
# 13 19 7
# 20 6 12
# 6 10 25
# 12 2 2
# 13 25 3
# 26 22 33
# 27 8 33
# 29 27 14
# 5 11 23
# 27 5 48
# 3 17 6
# 8 1 40
# 15 12 12
# 9 12 40
# 5 20 48
# 24 3 46
# 29 2 24
# 25 11 26
# 7 11 39
# 1 25 17
# 18 8 39
# 26 15 28
#
# 321
