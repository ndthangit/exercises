from ortools.linear_solver import pywraplp
def create_data_model():
    data ={}
    data['num_point'] = int(input())
    data['Matrix']= []
    for _ in range(data['num_point']):
        parts = list(map(int, input().split()))
        data['Matrix'].append(parts)
    return data


def main():
    data = create_data_model()
    # print(data)
    solver = pywraplp.Solver.CreateSolver("SAT")
    if not solver:
        return

    # xe có đi từ i tới j không
    x =[[solver.IntVar(0, 1, f"x{i}_{j}") for j in range(data['num_point'])] for i in range(data['num_point'])]
    # thứ tự thăm của điểm i là ui
    u = [solver.IntVar(0, data['num_point']-1, f"u{i}") for i in range(data['num_point']+1)]
    u[0].SetBounds(0, 0)

    for i in range(1, data['num_point']):
        for j in range(1, data['num_point']):
            if i != j:
                solver.Add(u[i]-u[j]+(data['num_point'])*x[i][j] <= data['num_point']-1)

    # Mỗi điểm chỉ được thăm 1 lần (trừ điểm 0)
    for i in range(data['num_point']):
        solver.Add(sum(x[i][j] for j in range(data['num_point']))==1)  # Tổng cột = 1
        solver.Add(sum(x[j][i] for j in range(data['num_point'])) == 1)  # Tổng hàng = 1

    # Đảm bảo không có đường đi từ i đến i (x[i][i] = 0)
    for i in range(data['num_point']):
        solver.Add(x[i][i] == 0)


    objective = sum(x[i][j] * data['Matrix'][i][j] for i in range(data['num_point']) for j in range(data['num_point']))
    solver.Minimize(objective)

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print(f"{solver.Objective().Value():.0f}")
        # for i in range(data['num_point']+1):
        #     print(f"{u[i].solution_value():.1f}", end=" ")
        # for i in range(data['num_point']+1):
        #     for j in range(data['num_point']+1):
        #         if i != j:
        #             print(f"{x[i][j].solution_value():.1f}", end=" ")
    else:
        print("-1")

if __name__ == "__main__":
    main()
