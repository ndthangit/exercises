from ortools.linear_solver import pywraplp
def importData():
    n,m = map(int, input().split())
    sochuyengia = list(map(int, input().split()))
    chiphi = list(map(int, input().split()))
    matrix =[]
    for i in range(m):
        dong = list(map(int, input().split()))
        matrix.append(dong)
    return n,m,sochuyengia,chiphi,matrix

n,m,sochuyengia,chiphi,matrix = importData()
model = pywraplp.Solver.CreateSolver("SAT")

x = [[model.IntVar(0,1,f"x[{i},{j}]") for i in range(n)] for j in range(m)]
y = [model.IntVar(0,1,f"y[{i}]") for i in range(m)]

for i in range(n):
    model.Add(sum(x[j][i] for j in range(m))>=sochuyengia[i])
    for  j in range(m):
        model.Add(x[j][i] <= matrix[j][i])
for i in range(m):
    model.Add(sum(x[i][j] for j in range(n))<= y[i]*n)

model.Minimize(sum(
    chiphi[i] * y[i] for i in range(m)
))


status = model.Solve()

if status == pywraplp.Solver.OPTIMAL:
    print(f"{model.Objective().Value():0.0f}")
    for i in range(n):
        for j in range(m):
            if x[j][i].solution_value() == 1:
                print(f"linh vuc {i} chuyen gia {j} {x[j][i].solution_value()} ")

else:
    print("NOT_OPTIMAL")

