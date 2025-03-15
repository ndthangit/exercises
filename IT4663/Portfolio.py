from ortools.linear_solver import pywraplp


def create_data_model():
    a, n, m, alpha = map(int, input().split())
    alpha = alpha / 100.0
    choice = list(map(int, input().split()))
    investigation = list(map(int, input().split()))
    negativeRating = list(map(lambda x: int(x) / 100, input().split()))
    positiveRating = list(map(lambda x: int(x) / 100, input().split()))
    maxInvestigation = list(map(int, input().split()))
    return a, n, m, alpha, choice, investigation, positiveRating, negativeRating, maxInvestigation


def main():
    a, n, m, alpha, choice, investigation, positiveRating, negativeRating, maxInvestigation = create_data_model()
    # print(positiveRating)
    # print(alpha)
    # Create the mip solver with the SCIP backend.
    solver = pywraplp.Solver.CreateSolver("SAT")
    if not solver:
        return

    infinity = solver.infinity()

    # Define integer decision variables
    varis = [solver.IntVar(0, infinity, f"x{i}") for i in range(n)]

    sumInvestigation = [0] * m
    for i in range(n):
        sumInvestigation[choice[i] - 1] += varis[i]

    for i in range(m):
        solver.Add(sumInvestigation[i] <= maxInvestigation[i])

    for i in range(n):
        solver.Add(varis[i] <= investigation[i])

    sumMoney =0
    for i in range(n):
        sumMoney += varis[i]
    solver.Add(sumMoney <= a)

    tu = solver.Sum(varis[i] * negativeRating[i] for i in range(n))
    mau = solver.Sum(varis[i] for i in range(n))

    solver.Add(tu <= alpha * mau)


    objective = solver.Sum(varis[i] * positiveRating[i] for i in range(n))
    solver.Maximize(objective)

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print(f"{solver.Objective().Value():.1f}")
        # for i in range(n):
        #     print(f"{varis[i].solution_value():.1f}")
    else:
        print("-1")


if __name__ == "__main__":
    main()
