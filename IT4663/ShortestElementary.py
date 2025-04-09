from ortools.sat.python import cp_model


def main():
    # Đọc dữ liệu đầu vào
    import sys
    input = sys.stdin.read().split()
    ptr = 0

    n = int(input[ptr]);
    ptr += 1
    m = int(input[ptr]);
    ptr += 1
    k = int(input[ptr]);
    ptr += 1
    s = int(input[ptr]);
    ptr += 1
    t = int(input[ptr]);
    ptr += 1

    edges = []
    edge_index = {}  # (u,v) -> index
    for _ in range(m):
        u = int(input[ptr]);
        ptr += 1
        v = int(input[ptr]);
        ptr += 1
        cost = int(input[ptr]);
        ptr += 1
        edges.append((u, v, cost))
        edge_index[(u, v)] = len(edges) - 1

    forbidden_pairs = []
    for _ in range(k):
        u1 = int(input[ptr]);
        ptr += 1
        v1 = int(input[ptr]);
        ptr += 1
        u2 = int(input[ptr]);
        ptr += 1
        v2 = int(input[ptr]);
        ptr += 1
        e1 = (u1, v1)
        e2 = (u2, v2)
        if e1 in edge_index and e2 in edge_index:
            forbidden_pairs.append((edge_index[e1], edge_index[e2]))

    # Tạo mô hình SAT
    model = cp_model.CpModel()

    # Biến quyết định: x[i] = True nếu cạnh thứ i được chọn
    x = [model.NewBoolVar(f'x_{i}') for i in range(m)]

    # Biến phụ: y[v] = True nếu đỉnh v nằm trên đường đi
    y = [model.NewBoolVar(f'y_{v}') for v in range(n)]

    # Biến thứ tự: rank[v] = vị trí của đỉnh v trong đường đi
    rank = [model.NewIntVar(0, n - 1, f'rank_{v}') for v in range(n)]

    # Ràng buộc điểm bắt đầu và kết thúc
    model.Add(y[s] == 1)
    model.Add(rank[s] == 0)
    model.Add(y[t] == 1)

    # Ràng buộc luồng vào-ra
    for v in range(n):
        # Tổng cạnh vào
        in_edges = [x[i] for i in range(m) if edges[i][1] == v]
        # Tổng cạnh ra
        out_edges = [x[i] for i in range(m) if edges[i][0] == v]

        if v == s:
            # Điểm bắt đầu: 1 cạnh ra, 0 cạnh vào
            model.Add(sum(out_edges) == 1)
            model.Add(sum(in_edges) == 0)
        elif v == t:
            # Điểm kết thúc: 1 cạnh vào, 0 cạnh ra
            model.Add(sum(in_edges) == 1)
            model.Add(sum(out_edges) == 0)
        else:
            # Điểm trung gian: nếu có trong đường đi thì 1 vào 1 ra
            model.Add(sum(in_edges) == y[v])
            model.Add(sum(out_edges) == y[v])

    # Ràng buộc thứ tự để tránh chu trình
    for i in range(m):
        u, v, _ = edges[i]
        if u != v:  # không xét khuyên
            model.Add(rank[v] > rank[u]).OnlyEnforceIf(x[i])

    # Ràng buộc cặp cạnh cấm
    for e1, e2 in forbidden_pairs:
        model.Add(x[e1] + x[e2] <= 1)

    # Hàm mục tiêu: tổng trọng số các cạnh được chọn
    total_cost = sum(x[i] * edges[i][2] for i in range(m))
    model.Minimize(total_cost)

    # Giải bài toán
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        # Truy vết đường đi
        path = [s]
        current = s
        while current != t:
            for i in range(m):
                if solver.Value(x[i]) and edges[i][0] == current:
                    next_node = edges[i][1]
                    path.append(next_node)
                    current = next_node
                    break

        print(int(solver.ObjectiveValue()))
        print(' '.join(map(str, path)))
    else:
        print(-1)


if __name__ == '__main__':
    main()