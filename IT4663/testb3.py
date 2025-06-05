#PYTHON
from ortools.sat.python import cp_model
def read_input():
    data = """40 117 4
26 21 16 
25 23 35 
1 31 37 
26 39 20 
39 24 4 
18 35 26 
39 33 49 
12 25 25 
28 21 40 
9 17 32 
12 34 22 
11 14 18 
4 30 1 
3 40 35 
11 23 31 
16 22 20 
1 33 40 
7 28 25 
16 40 47 
5 3 1 
18 37 15 
11 7 44 
23 36 37 
13 1 6 
12 36 40 
32 14 37 
26 7 48 
19 4 3 
39 37 9 
22 21 29 
6 34 42 
22 39 20 
33 6 39 
16 26 25 
23 13 46 
40 29 45 
17 9 15 
34 25 50 
14 28 38 
23 40 36 
26 20 9 
2 20 40 
35 32 43 
9 7 46 
14 21 29 
27 15 29 
26 4 28 
2 13 19 
8 29 33 
14 5 50 
21 20 11 
21 29 21 
18 39 37 
4 40 3 
36 38 4 
10 28 35 
32 34 27 
40 17 17 
21 13 8 
3 25 26 
8 6 39 
23 37 46 
36 22 41 
8 15 9 
19 24 44 
8 24 37 
29 1 47 
20 7 27 
15 20 16 
21 15 9 
38 31 49 
24 32 38 
23 12 35 
21 24 23 
23 30 3 
36 15 25 
2 1 50 
11 13 15 
30 26 42 
27 39 46 
28 38 2 
9 34 35 
22 6 14 
11 40 4 
21 8 12 
4 28 25 
27 23 19 
2 3 7 
17 22 16 
1 13 47 
17 40 3 
8 37 30 
5 38 29 
11 33 42 
6 21 22 
7 20 31 
40 32 13 
39 36 45 
10 9 31 
27 25 17 
11 8 37 
28 24 35 
16 4 4 
17 33 25 
20 13 6 
15 26 37 
28 17 25 
29 18 32 
16 18 43 
32 35 43 
1 29 20 
34 8 27 
27 20 22 
31 36 41 
5 26 30 
40 11 1 
1 22 27 

"""
    lines = data.strip().split("\n")
    n, m, b = map(int, lines[0].split())
    E = []
    InA = [[] for _ in range(n + 1)]
    OutA = [[] for _ in range(n + 1)]
    for line in lines[1:]:
        u, v, w = map(int, line.strip().split())
        OutA[u].append((v, w))
        InA[v].append((u, w)) # viết thường v
        E.append((u, v, w))
    return n, m,b, InA, OutA, E

n, m,b, InA, OutA, E = read_input()

model = cp_model.CpModel()

x={}
y={}
for [i,j,w] in E:
    x[i,j]=model.NewIntVar(0,1,"")
    y[i,j] = model.NewIntVar(0,1,"")

MAX=100
obj = model.NewIntVar(0,MAX,"")

s,t=1,n

for i in range(1,n+1):
    if i!=s and i!=t:
        model.Add( sum(x[j,i] for j, _ in InA[i]) == sum(x[i,j] for j, _ in OutA[i]))
        model.Add( sum(y[j,i] for j, _ in InA[i]) == sum(y[i,j] for j, _ in OutA[i]))

model.Add(sum(x[s,j] for j,_ in OutA[s])==1)
model.Add(sum(x[j,t] for j,_ in InA[t])==1)
model.Add(sum(y[s,j] for j,_ in OutA[s])==1)
model.Add(sum(y[j,t] for j,_ in InA[t])==1)

for i,j,w in E:
    model.Add(x[i,j]+y[i,j] <=1)

model.Add(sum(x[u,v] for (u,v,_) in E) <= b+1)
model.Add(sum(y[u,v] for (u,v,_) in E) <= b+1)

obj=0
obj = sum((x[i,j]+y[i,j])*w for i,j,w in E)
model.Minimize(obj)


solver= cp_model.CpSolver()

status = solver.Solve(model)

if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
    print(round(solver.ObjectiveValue())) # thêm round
    # Print edges where xij = 1
    print("\nEdges with xij = 1:")
    for (i, j, w) in E:
        if solver.Value(x[i, j]) == 1:
            print(f"x_{i}_{j} = 1 (weight: {w})")

    # Print edges where yij = 1
    print("\nEdges with yij = 1:")
    for (i, j, w) in E:
        if solver.Value(y[i, j]) == 1:
            print(f"y_{i}_{j} = 1 (weight: {w})")

else:
    print("NOT_FEASIBLE")
