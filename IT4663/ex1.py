# from ortools.linear_solver import pywraplp
#
#
# def LinearProgrammingExample():
#     """Linear programming sample."""
#     # Instantiate a Glop solver, naming it LinearExample.
#     solver = pywraplp.Solver.CreateSolver("GLOP")
#     if not solver:
#         return
#
#     # Create the two variables and let them take on any non-negative value.
#     x1 = solver.NumVar(0, solver.infinity(), "x1")
#     x2 = solver.NumVar(0, solver.infinity(), "x2")
#     x3 = solver.NumVar(0, solver.infinity(), "x3")
#     x4 = solver.NumVar(0, solver.infinity(), "x4")
#
#
#     print("Number of variables =", solver.NumVariables())
#
#     # Constraint 0: x + 2y <= 14.
#     solver.Add(x1+x2-x3-x4<=4.0)
#     solver.Add(x1+x2-x3-x4 >= 4.0)
#
#     # Constraint 1: 3x - y >= 0.
#     solver.Add(x1+x3+x4  >= 7.0)
#     solver.Add(x1+x3+x4  <= 7.0)
#
#     # Constraint 2: x - y <= 2.
#     solver.Add(2*x1+x2 <= 2.0)
#     solver.Add( 2 * x1+ x2 >= 2.0)
#
#
#     print("Number of constraints =", solver.NumConstraints())
#
#     # Objective function: 3x + 4y.
#     solver.Maximize( x1 +2*x2 -x3 +x4)
#
#     # Solve the system.
#     print(f"Solving with {solver.SolverVersion()}")
#     status = solver.Solve()
#
#     if status == pywraplp.Solver.OPTIMAL:
#         print("Solution:")
#         print(f"Objective value = {solver.Objective().Value():0.1f}")
#         print(f"x = {x1.solution_value():0.1f}")
#         print(f"x = {x2.solution_value():0.1f}")
#         print(f"x = {x3.solution_value():0.1f}")
#         print(f"x = {x4.solution_value():0.1f}")
#     else:
#         print("The problem does not have an optimal solution.")
#
#     print("\nAdvanced usage:")
#     print(f"Problem solved in {solver.wall_time():d} milliseconds")
#     print(f"Problem solved in {solver.iterations():d} iterations")
#
#
# LinearProgrammingExample()
# from ortools.sat.python import cp_model
from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
def create_data_model():
    data = {}
    n= int(input())
    data['NumPoint'] = n
    matrix = []
    for i in range(n):
        a =list(map(int, input().split()))
        matrix.append(a)
    data['Matrix'] = matrix
    return data
data = create_data_model()
def printsol(data, manager,routing,solution):
    print(solution.ObjectiveValue())

manager = pywrapcp.RoutingIndexManager(
    len(data['Matrix']), 1, 0
)
routing =pywrapcp.RoutingModel(manager)
def distance_calback(from_node, to_node):
    from_node = manager.IndexToNode(from_node)
    to_node = manager.IndexToNode(to_node)
    return data['Matrix'][from_node][to_node]
transit_callback_index= routing.RegisterTransitCallback(distance_calback)
routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)
dimension_name ="distance"
search_parameter = pywrapcp.DefaultRoutingSearchParameters()
search_parameter.first_solution_strategy =(
    routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC
)
solution = routing.SolveWithParameters(search_parameter)
if solution:
    printsol(data, manager,routing,solution)