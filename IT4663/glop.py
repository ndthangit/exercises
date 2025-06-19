from ortools.linear_solver import pywraplp

def main():
   solver = pywraplp.Solver.CreateSolver("SAT")
   if not solver:
       return

   infinity = solver.infinity()
   n = 6  # Define the number of variables

   x = [solver.IntVar(0, infinity, f"x{i}") for i in range(n)]
   solver.Add(2 * x[0] - 3 * x[1] + x[2] + x[3] == 4)
   solver.Add(x[0] - 1 * x[1] + x[4] == 7)
   solver.Add(3 * x[0] - 2 * x[1] + 6 * x[2] + x[5] == 10)

   objective = solver.Objective()
   objective.SetCoefficient(x[0], -3)
   objective.SetCoefficient(x[1], -2)
   objective.SetCoefficient(x[2], 7)
   objective.SetMaximization()

   status = solver.Solve()

   if status == pywraplp.Solver.OPTIMAL:
       print(f"{solver.Objective().Value():.1f}")
       for i in range(n):
           print(f"{x[i].solution_value():.1f}", end=" ")
   else:
       print("NOT_OPTIMAL")

if __name__ == "__main__":
   main()