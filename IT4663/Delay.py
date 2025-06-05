from ortools.linear_solver import pywraplp


def solve(n, m, s, l, edge):
    # khai bao bo giai
    model = pywraplp.Solver.CreateSolver("SCIP")
    # khai bao bien
    x, arr = {}, {}
    for u, v, _, _ in edge:
        x[(u, v)] = model.IntVar(0, 1, f'x_{u}_{v}')

    for i in range(1, n + 1, 1):
        arr[i] = model.NumVar(0, l, f'arr_{i}')
    # khai bao rang buoc
    model.Add(arr[s] == 0)
    for v in range(1, n + 1):
        if v == s:
            continue
        model.Add(sum(x[(u, w)] for u, w, _, _ in edge if w == v) == 1)

    M = 10000000
    for u, v, t, _ in edge:
        model.Add(arr[v] >= arr[u] + t - M * (1 - x[(u, v)]))

    # khai bao ham muc tieu
    model.Minimize(sum([c * x[(u, v)] for u, v, _, c in edge]))

    # giai va in

    status = model.Solve()
    if status == pywraplp.Solver.OPTIMAL or status == pywraplp.Solver.FEASIBLE:
        print(int(model.Objective().Value()))
    else:
        print("NO_SOLUTION")


def main():
    n, m, s, l = map(int, input().split())
    edge = []
    for _ in range(m):
        u, v, t, c = input().split()
        edge.append((int(u), int(v), int(t), int(c)))
        edge.append((int(v), int(u), int(t), int(c)))
    solve(n, m, s, l, edge)


if __name__ == "__main__":
    main()