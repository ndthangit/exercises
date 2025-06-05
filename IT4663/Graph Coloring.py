from ortools.sat.python import cp_model

def importData():
    data = {}
    n, m = map(int, input().split())  # Read n and m from the first line
    data['NumNode'] = n  # Number of nodes
    data['NumEdge'] = m  # Number of edges
    data['edges'] = []  # List to store edges

    for _ in range(m):
        u, v = map(int, input().split())  # Read each edge
        data['edges'].append((u, v))  # Add the edge as a tuple to the list

    return data


def main():
    data = importData()

    # Creates the model.
    model = cp_model.CpModel()

    # X[i]: điểm tiếp theo của điểm i trên lộ trình, i = 1, 2, …, N+K
    color = [model.NewIntVar(0,99999, f"color{i}") for i in range(data['NumNode']+1)]
    obj = model.NewIntVar(0,99999, "obj")
    for i in range(data['NumNode']+1):
        model.add(obj>= color[i])

    for edge in data['edges']:
        model.add(color[edge[0]] != color[edge[1]])
    for i in range(1, data['NumNode']+1):
        model.Add(color[i] > 0)

    model.Minimize(obj)

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(f"{solver.ObjectiveValue():.0f}")

        for i in range(1,data['NumNode']+1):
            print(f"{solver.Value(color[i])}",end=" ")
    else:
        print("No solution found.")


if __name__ == "__main__":
    main()