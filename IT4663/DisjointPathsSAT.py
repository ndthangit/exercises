from ortools.linear_solver import pywraplp

def importData():
    data = {}
    n, m = map(int, input().split())  # Read n (number of nodes) and m (number of edges)
    data['NumNodes'] = n
    data['NumEdges'] = m
    data['edges'] = []  # List to store edges
    data['cost'] = {}  # Dictionary to store edge costs

    for _ in range(m):
        u, v, c = map(int, input().split())  # Read each edge with its cost
        data['edges'].append((u, v))  # Add the edge as a tuple
        data['cost'][(u, v)] = c  # Store the cost of the edge

    return data


def main():

    data = importData()

    model = pywraplp.Solver.CreateSolver("SAT")

    # Creates the model.
    # model = cp_model.CpModel()

    x = [[model.IntVar(0, 1, f'next x {i} {j}') for i in range(data['NumNodes']+1)] for j in range(data['NumNodes']+1)]
    y = [[model.IntVar(0, 1, f'next y {i} {j}') for i in range(data['NumNodes']+1)] for j in range(data['NumNodes']+1)]
    model.Add(sum(x[1][i] for i in range(1,data['NumNodes']+1)) == 1)
    model.Add(sum(y[1][i] for i in range(1,data['NumNodes']+1)) == 1)

    model.Add(sum(x[i][data['NumNodes']] for i in range(1,data['NumNodes']+1)) == 1)
    model.Add(sum(y[i][data['NumNodes']] for i in range(1,data['NumNodes']+1)) == 1)

    for point in range(2,data['NumNodes']):
        model.Add(sum(x[point][i] for i in range(2,data['NumNodes']+1)) == sum(x[i][point] for i in range(1,data['NumNodes'])))
        model.Add(sum(y[point][i] for i in range(2,data['NumNodes']+1)) == sum(y[i][point] for i in range(1,data['NumNodes'])))



    for i in range(data['NumNodes']+1):
        for j in range(data['NumNodes']+1):
            if (i,j) in data['edges']:

                model.Add(x[i][j] + y[i][j] <= 1)
            else:
                model.Add(x[i][j] == 0)
                model.Add(y[i][j] == 0)

    model.Minimize(
            sum(data['cost'][(i, j)] *( x[i][j]+ y[i][j]) for i in range(1, data['NumNodes'] + 1)
                for j in range(1, data['NumNodes'] + 1) if (i, j) in data['cost'])
        )
    # solver = cp_model.CpSolver()
    status = model.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print(f"{model.Objective().Value():.0f}")

        # for i in range(1,data['NumNode']+1):
        #     print(f"{solver.Value(color[i])}",end=" ")
    else:
        print("NOT_FEASIBLE")


if __name__ == "__main__":
    main()