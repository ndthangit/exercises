from ortools.sat.python import cp_model


def create_data_model():
    data = {}
    m, n, p = map(int, input().split())
    data['NumTrucks'] = m
    data['NumItems'] = n
    data['ValuePerItem'] = p

    data['Weights'] = list(map(int, input().split()))  # Trọng lượng từng vật phẩm
    data['Capacities'] = []
    data['Costs'] = []
    for _ in range(data['NumTrucks']):
        capacity, cost = map(int, input().split())
        data['Capacities'].append(capacity)
        data['Costs'].append(cost)
    return data


def main():
    data = create_data_model()

    model = cp_model.CpModel()

    # Biến quyết định: x[truck][item] = 1 nếu item được gán cho truck
    x = [[model.NewBoolVar(f'x_{truck}_{item}') for item in range(data['NumItems'])]
         for truck in range(data['NumTrucks'])]

    # Biến res[item] = truck nếu item được gán cho truck, -1 nếu không được gán
    res = [model.NewIntVar(-1, data['NumTrucks'] - 1, f"res_{item}")
           for item in range(data['NumItems'])]

    # Mỗi item được gán tối đa 1 truck
    for item in range(data['NumItems']):
        model.Add(sum(x[truck][item] for truck in range(data['NumTrucks'])) <= 1)

    # Ràng buộc tải trọng cho mỗi truck
    for truck in range(data['NumTrucks']):
        model.Add(
            sum(data['Weights'][item] * x[truck][item]
                for item in range(data['NumItems'])) <= data['Capacities'][truck]
        )

    # Ràng buộc đồng nhất giữa x và res
    for item in range(data['NumItems']):
        # Nếu item không được gán cho truck nào
        model.Add(res[item] == -1).OnlyEnforceIf(
            [x[truck][item].Not() for truck in range(data['NumTrucks'])]
        )

        # Nếu item được gán cho một truck cụ thể
        for truck in range(data['NumTrucks']):
            model.Add(res[item] == truck+1).OnlyEnforceIf(x[truck][item])

    # Biến chỉ sử dụng truck hay không
    truck_used = [model.NewIntVar(0,1,f'truck_used_{truck}')
                  for truck in range(data['NumTrucks'])]

    for truck in range(data['NumTrucks']):
        check = model.NewBoolVar(f'check_{truck}')
        model.Add(sum(x[truck][item] for item in range(data['NumItems'])) > 0).OnlyEnforceIf(check)
        model.Add(sum(x[truck][item] for item in range(data['NumItems'])) == 0).OnlyEnforceIf(check.Not())
        model.Add(truck_used[truck] == 1).OnlyEnforceIf(check)
        model.Add(truck_used[truck] == 0).OnlyEnforceIf(check.Not())

    # for truck in range(data['NumTrucks']):
    #     # Truck được sử dụng nếu có ít nhất 1 item được gán cho nó
    #     model.AddMaxEquality(
    #         truck_used[truck],
    #         [x[truck][item] for item in range(data['NumItems'])]
    #     )

    # Hàm mục tiêu: Tổng giá trị - tổng chi phí các truck được sử dụng
    model.Maximize(
        sum(data['ValuePerItem']*data['Weights'][item] * x[truck][item]
            for truck in range(data['NumTrucks'])
            for item in range(data['NumItems']))
        - sum(data['Costs'][truck] * truck_used[truck]
              for truck in range(data['NumTrucks']))
    )

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(data['NumItems'])
        for item in range(data['NumItems']):
            print(solver.Value(res[item]), end=" ")

        # print('\n')
        # for truck in range(data['NumTrucks']):
        #     print(solver.Value(truck_used[truck]), end=" ")

    else:
        print("NOT_FEASIBLE")


if __name__ == "__main__":
    main()