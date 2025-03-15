from ortools.linear_solver import pywraplp

def creat_data_model():
    [n,a,b,c] = list(map(int, input().split()))
    S = list(map(int, input().split()))
    W = list(map(int, input().split()))
    P = list(map(int, input().split()))
    return n,a,b,c,S,W,P
def main():
    n, a, b, c, S, W, P = creat_data_model()
    # Create the mip solver with the SCIP backend.
    solver = pywraplp.Solver.CreateSolver("GLOP")
    if not solver:
        return

    infinity = solver.infinity()
    # x and y are integer non-negative variables.
    varis= [solver.IntVar(0.0, infinity, "x"+str(i)) for i in range(n)]


    # print("Number of variables =", solver.NumVariables())

    # x + 7 * y <= 17.5.

    # x <= 3.5.
    sumSeed =0
    for i in range(n):
        sumSeed += varis[i]*S[i]
    solver.Add(sumSeed <= b)
    sumWater =0
    for i in range(n):
        sumWater += varis[i]*W[i]
    solver.Add(sumWater <= c)

    sumPlant =0
    for i in range(n):
        sumPlant += varis[i]
    solver.Add(sumPlant <= a)
    # Maximize x + 10 * y.
    sum =0
    for i in range(n):
        sum += varis[i]*(P[i])
    solver.Maximize(sum)

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print(f"{solver.Objective().Value():.2f}")
        for i in range(n):
            print(f"{varis[i].solution_value():.2f}")

    else:
        print("The problem does not have an optimal solution.")

    # print("\nAdvanced usage:")
    # print(f"Problem solved in {solver.wall_time():d} milliseconds")
    # print(f"Problem solved in {solver.iterations():d} iterations")
    # print(f"Problem solved in {solver.nodes():d} branch-and-bound nodes")


if __name__ == "__main__":
    main()