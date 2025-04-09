from ortools.linear_solver import pywraplp


def create_data_model():
    mapping = {
        "A": 0,
        "B": 1,
        "AB": 2,
        "O": 3
    }
    data ={}
    n = int(input())
    data['num_people'] = n
    for _ in range(n):
        parts = input().split()
        idx = int(parts[0])
        bt = int(mapping[parts[1]])
        f = int(parts[2])
        m = int(parts[3])
        data['people'][idx] = {"blood": bt, "parent1": f, "parent2": m}

    return data




def main():
    n, m, dl, du, c, a, low, up = create_data_model()
    # print(c)
    # print(positiveRating)
    # print(alpha)
    # Create the mip solver with the SCIP backend.
    solver = pywraplp.Solver.CreateSolver("SAT")
    if not solver:
        return

    infinity = solver.infinity()

    x = [solver.IntVar(-infinity, infinity, f"x{i}") for i in range(n)]
    for i in range(n):
        solver.Add(x[i] >= dl[i])
        solver.Add(x[i] <= du[i])
    for i in range(m):
        sum = 0
        for j in range(n):
            sum += a[i][j] * x[j]
        solver.Add(sum >= low[i])
        solver.Add(sum <= up[i])


    objective = solver.Sum(x[i]*c[i] for i in range(n))
    solver.Maximize(objective)

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print(f"{solver.Objective().Value():.1f}")
        for i in range(n):
            print(f"{x[i].solution_value():.1f}", end=" ")
    else:
        print("NOT_OPTIMAL")


if __name__ == "__main__":
    main()
