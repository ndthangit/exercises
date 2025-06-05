from ortools.sat.python import cp_model

def unique_3x3_grid():
    model = cp_model.CpModel()

    # Khởi tạo biến x[i][j] với domain từ 1 đến 9
    x = [[model.NewIntVar(1, 9, f'x[{i}][{j}]') for j in range(3)] for i in range(3)]

    # Ràng buộc: tất cả các ô trong lưới đều khác nhau
    model.AddAllDifferent([x[i][j] for i in range(3) for j in range(3)])

    # Giải bài toán
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    # In kết quả
    if status == cp_model.FEASIBLE or status == cp_model.OPTIMAL:
        for i in range(3):
            print([solver.Value(x[i][j]) for j in range(3)])
    else:
        print("No solution found.")

unique_3x3_grid()
