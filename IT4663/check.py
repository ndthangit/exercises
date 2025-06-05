from ortools.sat.python import cp_model

model: cp_model.CpModel = cp_model.CpModel()
solver: cp_model.CpSolver = cp_model.CpSolver()

n, m, b = map(int, input().split())
edges = [[int(1e10) for i in range(n)] for j in range(n)]
for i in range(m):
    u, v, c = map(int, input().split())
    edges[u-1][v-1] = c

x = {(i, j):model.new_bool_var(f'x[{i}][{j}]') for i in range(n) for j in range(n) if edges[i][j]!=int(1e10)}
y = {(i, j):model.new_bool_var(f'y[{i}][{j}]') for i in range(n) for j in range(n) if edges[i][j]!=int(1e10)}
marks_x = [model.new_bool_var(f'marks_x{i}') for i in range(n)]
marks_y = [model.new_bool_var(f'marks_y{i}') for i in range(n)]
for start in range(n):
    for end in range(n):
        if edges[start][end] != int(1e10):
            if start != end:
                model.Add(x[(start, end)] + y[(start, end)] <= 1)
            else:
                model.Add(x[(start, end)] == 0)
                model.Add(y[(start, end)] == 0)
model.Add(sum(marks_x[i] for i in range(1, n-1)) <=b)
model.Add(sum(marks_y[i] for i in range(1, n-1)) <=b)

for i in range(n):
    if i == 0:
        model.Add(sum([x[(i, j)] for j in range(n) if edges[i][j] != int(1e10)]) == 1)
        model.Add(sum([y[(i, j)] for j in range(n) if edges[i][j] != int(1e10)]) == 1)
    elif i == n-1:
        model.Add(sum([x[(j, i)] for j in range(n) if edges[j][i] != int(1e10)]) == 1)
        model.Add(sum([y[(j, i)] for j in range(n) if edges[j][i] != int(1e10)]) == 1)
    else:
        model.Add(sum([x[(j, i)] for j in range(n) if edges[j][i] != int(1e10)]) == marks_x[i])
        model.Add(sum([x[(i, j)] for j in range(n) if edges[i][j] != int(1e10)]) == marks_x[i])
        model.Add(sum([y[(j, i)] for j in range(n) if edges[j][i] != int(1e10)]) == marks_y[i])
        model.Add(sum([y[(i, j)] for j in range(n) if edges[i][j] != int(1e10)]) == marks_y[i])
model.Minimize(sum([(y[(i, j)] + x[(i, j)])*edges[i][j] for i in range(n) for j in range(n) if i!=j and edges[i][j] != int(1e10)]))
status = solver.Solve(model)

if status == cp_model.OPTIMAL:
    print(int(solver.ObjectiveValue()))

    # In các cạnh xij = 1
    print("\nCác cạnh trong đường đi x:")
    for (i, j), var in x.items():
        if solver.Value(var) == 1:
            print(f"x[{i + 1}][{j + 1}] = 1 (trọng số: {edges[i][j]})")

    # In các cạnh yij = 1
    print("\nCác cạnh trong đường đi y:")
    for (i, j), var in y.items():
        if solver.Value(var) == 1:
            print(f"y[{i + 1}][{j + 1}] = 1 (trọng số: {edges[i][j]})")

    # In các đỉnh được đánh dấu
    print("\nCác đỉnh được đánh dấu trong x:")
    for i in range(n):
        if solver.Value(marks_x[i]) == 1:
            print(f"Đỉnh {i + 1} được đánh dấu trong x")

    print("\nCác đỉnh được đánh dấu trong y:")
    for i in range(n):
        if solver.Value(marks_y[i]) == 1:
            print(f"Đỉnh {i + 1} được đánh dấu trong y")
else:
    print('NOT_FEASIBLE')
