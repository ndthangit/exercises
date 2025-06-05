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
    for i in data['Quantity']:
        data['Request'][i + data['NumParcel']] = i
        data['Request'][i + 2 * data['NumParcel'] + data['NumPassenger']] = -i

    return data


def main():
    data = importData("test/test5.txt")
    num_locations = 2 * (data['NumParcel'] + data['NumPassenger'])

    # Creates the model.
    model = cp_model.CpModel()

    # X[i]: điểm tiếp theo của điểm i trên lộ trình, i = 1, 2, …, N+K
    x = [model.NewIntVar(0, num_locations + 2* data['NumTaxis'] , f'x[{i}]') for i in range(num_locations + data['NumTaxis'] +1 )]

    ir = [model.NewIntVar(0, data['NumTaxis'], f'ir[{i}]') for i in range( num_locations + 2* data['NumTaxis'] +1)]
    # xe 0 là nhưng điểm bị bỏ qua

    # L[i]: khoảng cách tích luỹ của route chứa i từ điểm xuất phát đến điểm i, i = 1, …, N + 2K
    l = [model.NewIntVar(0, 1000000, f'L[{i}]') for i in range(num_locations + 2* data['NumTaxis'] +1)]

    # W[i]: trọng lượng tích luỹ của hàng hoá trên xe từ điểm xuất phát đến điểm i
    w = [model.NewIntVar(0, max(data['Capacity']), f'W[{i}] ') for i in range(num_locations + 2 * data['NumTaxis'] +1)]

    # Constraints
    # 1. khởi tạo ban đầu
    from_nodes = range(1, num_locations + data['NumTaxis'] + 1)
    to_nodes = set(range(1, num_locations + 2 * data['NumTaxis'] + 1)) - set(
        range(num_locations + 1, num_locations + data['NumTaxis'] + 1))
    start_nodes = range(num_locations+1, num_locations + data['NumTaxis'] + 1)
    end_nodes = range(num_locations+1+data['NumTaxis'], num_locations + 2*data['NumTaxis'] + 1)

    print(list(from_nodes))
    print(sorted(to_nodes))
    print(list(start_nodes))
    print(list(end_nodes))

    model.add(ir[0] == 0)
    for i in start_nodes:
        model.add(ir[i] != 0)
    for i in end_nodes:
        model.add(ir[i] != 0)

    for start_node in range(num_locations + 1, num_locations + data['NumTaxis'] + 1):
        model.Add(l[start_node] == 0)
    # model.Add(ir[start_node] > 0)

    for start_node in start_nodes:
        model.Add(w[start_node] == 0)

    # điểm bắt đầu
    model.AddAllDifferent(ir[num_locations+1: num_locations+ data['NumTaxis'] + 1])
    # điểm kết thúc
    for i in range(1, data['NumTaxis'] + 1):
        model.Add(ir[num_locations + i] == ir[num_locations + data['NumTaxis'] + i])

    # Constraint: Các điểm thường (1..num_locations) không được trỏ đến điểm bắt đầu taxi
    for i in range(1, num_locations + 1):
        for j in range(num_locations + 1, num_locations + data['NumTaxis'] + 1):
            model.Add(x[i] != j)

    # thiết lập bắt đầu và kết thúc
    for i in start_nodes:
        model.Add(ir[i] == ir[i + data['NumTaxis']])

    # 4. No self-loops
    for i in range(1, num_locations + data['NumTaxis'] + 1):
        model.Add(x[i] != i)

    # 3. All nodes must have different next points (except depot)
    model.AddAllDifferent(x[1:num_locations + data['NumTaxis'] + 1])

    # Fixed code
    for from_node in from_nodes:
        for to_node in to_nodes:
            b = model.NewBoolVar(f'b_taxis_{from_node}_{to_node}')
            model.Add(x[from_node] == to_node).OnlyEnforceIf(b)
            model.Add(x[from_node] != to_node).OnlyEnforceIf(b.Not())
            model.Add(ir[from_node] == ir[to_node]).OnlyEnforceIf(b)


    # 6. Distance accumulation
    for i in range(1, num_locations + data['NumTaxis'] + 1):
        for j in range(1, num_locations + 2 * data['NumTaxis'] + 1):
            b = model.NewBoolVar(f'b_dist_{i}_{j}')
            model.Add(x[i] == j).OnlyEnforceIf(b)
            model.Add(x[i] != j).OnlyEnforceIf(b.Not())
            model.Add(l[j] == l[i] + data['Matrix'][i][j]).OnlyEnforceIf(b)

    # 8. Passenger request constraint: pickup and drop-off must be consecutive
    for pickup, dropoff in data['Delivery']['PassengerRequest']:
        model.Add(x[pickup] == dropoff)


    # 10. Ensure all pickup and drop-off points are visited exactly once (incoming and outgoing arcs)
    for j in range(1, num_locations  + 1):
        # Outgoing arc: each node j has exactly one successor
        outgoing = [model.NewBoolVar(f'out_{j}_is_{i}') for i in range(num_locations + 2 *data['NumTaxis'] + 1)]
        for i in range(num_locations + 2 * data['NumTaxis'] + 1):
            if i in to_nodes:
                model.Add(x[j] == i).OnlyEnforceIf(outgoing[i])
                model.Add(x[j] != i).OnlyEnforceIf(outgoing[i].Not())
            else:
                model.Add(outgoing[i] == 0)
        model.Add(sum(outgoing) == 1)

        # Incoming arc: each node j has exactly one predecessor
        incoming = [model.NewBoolVar(f'in_{j}_is_{i}') for i in range( num_locations + data['NumTaxis'] + 1)]
        for i in range(num_locations +  data['NumTaxis'] + 1):
            if i in from_nodes:
                model.Add(x[i] == j).OnlyEnforceIf(incoming[i])
                model.Add(x[i] != j).OnlyEnforceIf(incoming[i].Not())
            else:
                model.Add(incoming[i] == 0)
        model.Add(sum(incoming) == 1)

    # 11. Ensure taxi start nodes are used
    for i in start_nodes:
        outgoing = [model.NewIntVar(f'taxi_out_{i}_{j}') for j in range(num_locations + 2 * data['NumTaxis'] + 1)]

        for j in range(num_locations + 2 * data['NumTaxis'] + 1):
            if j in to_nodes:
                model.Add(x[i] == j).OnlyEnforceIf(outgoing[j])
                model.Add(x[i] != j).OnlyEnforceIf(outgoing[j].Not())
            else:
                model.Add(outgoing[j] == 0)
        model.Add(sum(outgoing) == 1)

    # 12. Ensure taxi end nodes are used
    for j in end_nodes:
        incoming = [model.NewBoolVar(f'taxi_in_{i}_{j}') for i in range(num_locations + data['NumTaxis'] + 1)]
        for i in range(num_locations + data['NumTaxis'] + 1):
            model.Add(x[i] == j).OnlyEnforceIf(incoming[i])
            model.Add(x[i] != j).OnlyEnforceIf(incoming[i].Not())
        model.Add(sum(incoming) == 1)

    # 3. weight constraint

    for i in range(1, num_locations + data['NumTaxis'] + 1):
        for j in range(1, num_locations + 2 * data['NumTaxis'] + 1):
            b = model.NewBoolVar(f'b_dist_{i}_{j}')
            model.Add(x[i] == j).OnlyEnforceIf(b)
            model.Add(x[i] != j).OnlyEnforceIf(b.Not())
            model.Add(w[j] == w[i] + data['Request'][j]).OnlyEnforceIf(b)

    for i in range(1,data['NumTaxis']+1):
        model.Add(w[i+ num_locations+ data['NumTaxis']] <= data['Capacity'][i-1])

    # objective function

    model.Minimize(sum(l[i] for i in end_nodes))

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(f"Total distance: {solver.ObjectiveValue()}")
        print("Routes:")

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

        for k in range(data['NumTaxis']):
            print(f"Taxi {k+1} route: {' -> '.join(map(str, routes[k]))}")

        for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + data['NumTaxis'] + 1 ):
            print(f"next point {i}: {solver.Value(x[i])}")

        for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2*data['NumTaxis'] + 1):
            print(f"ir {i}: {solver.Value(ir[i])}")

        for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2*data['NumTaxis'] + 1):
            print(f"w {i}: {solver.Value(w[i])}")
    else:
        print("No solution found.")


if __name__ == "__main__":
    main()