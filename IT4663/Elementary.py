from ortools.sat.python import cp_model

def importData():
    n, m, k, s, t = map(int, input().split())  # Read n and m from the first line
    edges = []
    for i in range(m):
        a,b,c = map(int, input().split())
        edges.append((a,b,c))
    for_edges =[]
    for i in range(k):
        a,b,c,d = map(int, input().split())
        for_edges.append(((a,b),(c,d)))
    return n, m, k, s, t, edges, for_edges


def main():
    n, m, k, s, t, edges, for_edges = importData()
    # Creates the model.
    model = cp_model.CpModel()

    x = [[model.NewIntVar(0, 1, f'next {i} {j}') for i in range(n + 1)] for j in range(n + 1)]

    model.AddAllDifferent([x[i][j] for i in range(3) for j in range(3)])

    # model.Minimize(obj)

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(f"{solver.ObjectiveValue():.0f}")

        # for i in range(1,data['NumNode']+1):
        #     print(f"{solver.Value(color[i])}",end=" ")
    else:
        print("No solution found.")


if __name__ == "__main__":
    main()