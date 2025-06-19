import time

from ortools.sat.python import cp_model

def importData(dataPath):
    data ={}
    with open(dataPath, 'r') as f:
        n,m,k = f.readline().split()
        data['NumParcel'] =int(n)
        data['NumPassenger'] =int(m)
        data['NumTaxis'] =int(k)
        data['Quantity']= [int (x) for x in f.readline().split()]
        data['Capacity']=[int (x) for x in f.readline().split()]

        data['Matrix']=[]
        for x in range(2 * (data ['NumParcel'] + data['NumPassenger']) + 1):
            data['Matrix'].append([int (x) for x in f.readline().split()])

        matrix = []

        for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
            row = []
            if i < 2 * (data['NumParcel'] + data['NumPassenger']) + 1:
                for j in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
                    if j > 2 * (data['NumParcel'] + data['NumPassenger']):
                        row.append(data['Matrix'][i][0])
                    else:
                        row.append(data['Matrix'][i][j])

            else:
                for j in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
                    if j > 2 * (data['NumParcel'] + data['NumPassenger']):
                        row.append(0)
                    else:
                        row.append(data['Matrix'][0][j])
            matrix.append(row)
        data['Matrix'] = matrix

    data['Depot']= 0

    data['Delivery'] = {
        'PassengerRequest': [],
        'ParcelRequest': []
    }

    # Passenger request
    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

    # Parcel request
    for i in range(1, data['NumParcel'] + 1):
        data['Delivery']['ParcelRequest'].append(
            [i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']])

    data['Request']= [0]*(2 * (data['NumParcel'] + 2*data['NumPassenger'])+1)
    for i, value in enumerate(data['Quantity']):
        data['Request'][i + 1 + data['NumParcel']] = value
        data['Request'][i + 1 + 2 * data['NumParcel'] + data['NumPassenger']] = -value

    return data

def importData2():
    data = {}

    n, m, k = map(int, input().split())
    data['NumParcel'] = n
    data['NumPassenger'] = m
    data['NumTaxis'] = k

    data['Quantity'] = list(map(int, input().split()))
    data['Capacity'] = list(map(int, input().split()))

    data['Matrix'] = [list(map(int, input().split())) for _ in range(2 * (n + m) + 1)]

    matrix = []

    for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
        row = []
        if i < 2 * (data['NumParcel'] + data['NumPassenger']) + 1:
            for j in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
                if j > 2 * (data['NumParcel'] + data['NumPassenger']):
                    row.append(data['Matrix'][i][0])
                else:
                    row.append(data['Matrix'][i][j])

        else:
            for j in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
                if j > 2 * (data['NumParcel'] + data['NumPassenger']):
                    row.append(0)
                else:
                    row.append(data['Matrix'][0][j])
        matrix.append(row)
    data['Matrix'] = matrix

    data['Depot'] = 0

    data['Delivery'] = {
        'PassengerRequest': [[i, i + n + m] for i in range(1, m + 1)],
        'ParcelRequest': [[i + n, i + 2 * n + m] for i in range(1, n + 1)]
    }

    data['Request'] = [0] * (2 * (n + 2 * m) + 1)
    for i, value in enumerate(data['Quantity']):
        data['Request'][i + 1 + data['NumParcel']] = value
        data['Request'][i + 1 + 2 * data['NumParcel'] + data['NumPassenger']] = -value

    return data
def main():
    # data = importData("test/test5.txt")
    # print(data['Request'])

    data = importData2()
    num_locations = 2 * (data['NumParcel'] + data['NumPassenger'])

    # Creates the model.
    model = cp_model.CpModel()

    # X[i]: điểm tiếp theo của điểm i trên lộ trình, i = 1, 2, …, N+K
    x = [model.NewIntVar(0, num_locations + 2* data['NumTaxis'] , f'x[{i}]') for i in range(num_locations + data['NumTaxis'] +1 )]

    ir = [model.NewIntVar(1, data['NumTaxis'], f'ir[{i}]') for i in range( num_locations + 2* data['NumTaxis'] +1)]

    # L[i]: khoảng cách tích luỹ của route chứa i từ điểm xuất phát đến điểm i, i = 1, …, N + 2K
    l = [model.NewIntVar(0, 1000000, f'L[{i}]') for i in range(num_locations + 2* data['NumTaxis'] +1)]

    # W[i]: trọng lượng tích luỹ của hàng hoá trên xe từ điểm xuất phát đến điểm i
    w = [model.NewIntVar(0, max(data['Capacity']), f'W[{i}] ') for i in range(num_locations + 2 * data['NumTaxis'] +1)]

    # Constraints
    model.AddAllDifferent(ir[num_locations+1:num_locations+ data['NumTaxis']+1])
    model.AddAllDifferent(ir[num_locations+ data['NumTaxis']+1:num_locations+ 2* data['NumTaxis']+1])
    # model.AddAllDifferent(x[1: num_locations+1])
    model.AddAllDifferent(x[1: num_locations+data['NumTaxis']+1])

    [model.add(l[i]==0) for i in range(num_locations+1, num_locations+ data['NumTaxis']+1)]

    for i in range(1,num_locations+ data['NumTaxis'] +1):
        for j in range(1,num_locations+ 2* data['NumTaxis'] +1):
            b = model.NewBoolVar(f"b[{i},{j}]")
            model.Add(x[i] == j).OnlyEnforceIf(b)
            model.Add(x[i] != j).OnlyEnforceIf(b.Not())
            model.Add(l[j]== l[i]+ data['Matrix'][i][j]).OnlyEnforceIf(b)
            model.Add(w[j]== w[i]+ data['Request'][j]).OnlyEnforceIf(b)
            model.Add(i != j).OnlyEnforceIf(b)
            model.Add(ir[i]== ir[j]).OnlyEnforceIf(b)

    for a in data['Delivery']['PassengerRequest']:
        model.Add(ir[a[0]] == ir[a[1]])
        model.Add(x[a[0]] == a[1])

    for a in data['Delivery']['ParcelRequest']:
        model.Add(ir[a[0]] == ir[a[1]])
        model.Add(l[a[0]] < l[a[1]])

    [model.Add(x[num_locations+i]>0) for i in range(1, data['NumTaxis']+1)]
    # [model.Add(x[num_locations+i]<data['NumParcel']+data['NumPassenger']+1) for i in range(1, data['NumTaxis']+1)]

    [model.Add(x[i]>0) for i in range(1, num_locations+1)]

    model.Minimize(sum(l[i] for i in range(num_locations+ data['NumTaxis']+1,num_locations+ 2*data['NumTaxis']+1)))

    start = time.time()
    solver = cp_model.CpSolver()
    status = solver.Solve(model)
    end = time.time()

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        # print(f"Time: {end - start} seconds")
        # print(f"Number of branches explored: {solver.num_branches}")
        # print(f"Number of conflicts encountered: {solver.num_conflicts}")
        # print(f"Total distance: {solver.ObjectiveValue()}")
        # print("Routes:")

        # Reconstruct routes
        routes = [[] for _ in range(data['NumTaxis'])]
        for k in range(data['NumTaxis']):
            current = num_locations + 1 + k  # Starting point for taxi k
            route = [current]
            while True:
                next_point = solver.Value(x[current])
                if next_point > num_locations + data['NumTaxis']:  # End at taxi end point
                    route.append(next_point)
                    break
                if solver.Value(ir[next_point]) == 0:  # Skip unvisited points
                    break
                route.append(next_point)
                current = next_point
            routes[k] = route


        # for k in range(data['NumTaxis']):
        #     print(f"Taxi {k+1} route: {' -> '.join(map(str, routes[k]))}")
        #
        # for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + data['NumTaxis'] + 1 ):
        #     print(f"next point {i}: {solver.Value(x[i])}")
        #
        # for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2*data['NumTaxis'] + 1):
        #     print(f"ir {i}: {solver.Value(ir[i])}")
        #
        # for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2*data['NumTaxis'] + 1):
        #     print(f"w {i}: {solver.Value(w[i])}")



        print(data['NumTaxis'])
        for k in range(data['NumTaxis']):
            routes[k][0]= 0
            routes[k][-1] = 0
            print(len(routes[k]))
            print(' '.join(map(str, routes[k])))

        # print(calculate_route_distance(data, routes[0], routes[1]))
    else:
        print("No solution found.")


if __name__ == "__main__":
    main()