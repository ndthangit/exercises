from ortools.sat.python import cp_model


def create_data_model():
    data = {}
    n, m, s, l = map(int, input().split())
    data['NumNodes'] = n
    data['NumEdges'] = m
    data['depot'] = s
    data['limit'] = l
    data['edges'] = []
    data['time'] = {}
    data['cost'] = {}
    for i in range(m):
        u, v, t, c = map(int, input().split())
        data['edges'].append([u, v])
        data['edges'].append([v, u])
        data['time'][(u, v)] = t
        data['time'][(v, u)] = t
        data['cost'][(u, v)] = c
        data['cost'][(v, u)] = c

    return data

def main():

    data = create_data_model()

    model = cp_model.CpModel()

    x = [[model.NewIntVar(0, 1, f'next {i} {j}') for i in range(data['NumNodes'] + 1)] for j in
         range(data['NumNodes'] + 1)]
    slack = [model.NewIntVar(0, data['limit'], f"slack {i}") for i in range(data['NumNodes'] + 1)]
    model.add(slack[data['depot']]==0)


    for i in range(data['NumNodes'] + 1):
        for j in range(data['NumNodes'] + 1):
            if [i, j] in data['edges']:
                model.Add(x[i][j] <= 1)
            else:
                model.Add(x[i][j] == 0)

    for point in range(1, data['NumNodes'] + 1):
        if point == data['depot']:
            continue
        model.add(sum(x[i][point] for i in range(1,data['NumNodes'] + 1)) ==1)

    M = 99999999
    for edge in data['edges']:
        model.Add(slack[edge[1]] >= slack[edge[0]] + data['time'][(edge[0], edge[1])] - M * (1 - x[edge[0]][edge[1]]))


    model.Minimize(
            sum(data['cost'][(edge[0],edge[1])] * x[edge[0]][edge[1]] for edge in data['edges'] )
        )
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(f"{solver.ObjectiveValue():.0f}")

        # for i in range(1,data['NumNode']+1):
        #     print(f"{solver.Value(color[i])}",end=" ")
    else:
        print("NOT_FEASIBLE")


if __name__ == "__main__":
    main()