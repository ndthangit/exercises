# PYTHON
from ortools.sat.python import cp_model


def create_data_model():
    n, m, x = map(int, input().split())
    edges = []
    costs = {}
    for i in range(m):
        a, b, c = map(int, input().split())
        edges.append((a, b))
        costs[(a, b)] = c
    return n, m, x, edges, costs


n, m, b, edges, costs = create_data_model()
model = cp_model.CpModel()
x = [[model.NewIntVar(0, 1, f"x{i}{j}") for j in range(n + 1)] for i in range(n + 1)]
y = [[model.NewIntVar(0, 1, f"y{i}{j}") for j in range(n + 1)] for i in range(n + 1)]

model.add(sum(x[1][j] for j in range(1, n + 1)) == 1)
model.add(sum(y[1][j] for j in range(1, n + 1)) == 1)

model.add(sum(x[j][n] for j in range(1, n + 1)) == 1)
model.add(sum(y[j][n] for j in range(1, n + 1)) == 1)

for i in range(2, n):
    model.add(sum(x[i][j] for j in range(1, n + 1)) == sum(x[j][i] for j in range(1, n+1)))
    model.add(sum(y[i][j] for j in range(1, n + 1)) == sum(y[j][i] for j in range(1, n+1)))

model.add(sum(x[i][j] for i in range(1, n + 1) for j in range(1, n + 1) if (i, j) in costs) - 1 <= b)
model.add(sum(y[i][j] for i in range(1, n + 1) for j in range(1, n + 1) if (i, j) in costs) - 1 <= b)

for i in range(n + 1):
    for j in range(n + 1):
        if (i, j) in edges:
            model.add(x[i][j] + y[i][j] <= 1)
            # model.add(y[i][j]<=1)

        else:
            model.add(x[i][j] == 0)
            model.add(y[i][j] == 0)

model.Minimize(
    sum(costs[(i, j)] * (x[i][j] + y[i][j]) for i in range(1, n + 1) for j in range(1, n + 1) if (i, j) in costs))
solver = cp_model.CpSolver()
status = solver.Solve(model)
if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
    print(f"{solver.ObjectiveValue():.0f}")
    # for i in range(1,n):
    #     print(f"{solver.value(route[i])}", end= " ")
else:
    print("NOT_FEASIBLE")
