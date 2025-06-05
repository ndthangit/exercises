import sys
import random


def count_conflicts(state, n):
    """Đếm số cặp quân hậu xung đột."""
    conflicts = 0
    row_counts = {}  # row_counts[r] = số quân hậu ở hàng r
    diag1_counts = {}  # diag1_counts[r + col] = số quân hậu trên đường chéo chính (r + col)
    diag2_counts = {}  # diag2_counts[r - col] = số quân hậu trên đường chéo phụ (r - col)

    # đếm số lượng quân hậu nằm trên từng hàng và từng đường chéo hiện tại
    for col in range(n):  # duyệt qua từng cột
        r = state[col]  # lấy vị trí hàng của quân hậu ở cột col
        row_counts[r] = row_counts.get(r, 0) + 1
        diag1_counts[r + col] = diag1_counts.get(r + col, 0) + 1
        diag2_counts[r - col] = diag2_counts.get(r - col, 0) + 1

    for counts in [row_counts, diag1_counts, diag2_counts]:
        for c in counts.values():
            if c > 1:
                conflicts += c * (c - 1) // 2
                # Nếu có c quân hậu cùng một hàng hoặc cùng một đường chéo, số cặp xung đột là c*(c-1)/2

    return conflicts


def min_conflicts(n, max_steps=1000000):
    # Khởi tạo ngẫu nhiên: state[i] = row của quân hậu cột i
    state = [random.randint(0, n - 1) for _ in range(n)]  # state[i] lưu vị trí hàng của quân hậu cột i.

    for step in range(max_steps):
        conflicts = [0] * n  # danh sách lưu số xung đột của từng quân hậu (cột).

        total_conflicts = 0

        # Đếm xung đột cho từng quân hậu

        # các dictionary đếm số quân hậu trên từng hàng và từng đường chéo.
        row_counts = {}
        diag1_counts = {}
        diag2_counts = {}

        for col in range(n):
            r = state[col]
            row_counts[r] = row_counts.get(r, 0) + 1
            diag1_counts[r + col] = diag1_counts.get(r + col, 0) + 1
            diag2_counts[r - col] = diag2_counts.get(r - col, 0) + 1

        conflicted_cols = []
        for col in range(n):
            r = state[col]
            conflict_count = (row_counts[r] - 1) + (diag1_counts[r + col] - 1) + (diag2_counts[r - col] - 1)
            conflicts[col] = conflict_count
            if conflict_count > 0:
                conflicted_cols.append(col)

        if not conflicted_cols:
            # Không còn xung đột -> tìm được lời giải
            return state

        # Chọn ngẫu nhiên một quân hậu đang bị xung đột
        col = random.choice(conflicted_cols)

        # Tìm vị trí đặt lại tốt nhất trong cột này
        min_conflict = conflicts[col]
        best_rows = []
        for r in range(n):
            conflict_here = 0
            # Tính số xung đột nếu đặt quân hậu ở hàng r cột col
            conflict_here += (row_counts.get(r, 0) - (1 if r == state[col] else 0))
            conflict_here += (diag1_counts.get(r + col, 0) - (1 if (r + col) == (state[col] + col) else 0))
            conflict_here += (diag2_counts.get(r - col, 0) - (1 if (r - col) == (state[col] - col) else 0))
            if conflict_here < min_conflict:
                min_conflict = conflict_here
                best_rows = [r]
            elif conflict_here == min_conflict:
                best_rows.append(r)

        # Đặt quân hậu tại vị trí ít xung đột nhất trong cột
        if best_rows:
            state[col] = random.choice(best_rows)

    # Nếu không tìm được sau max_steps
    return None


def main():
    n = int(sys.stdin.readline())
    solution = min_conflicts(n)
    if solution:
        print(n)
        print(' '.join(str(r + 1) for r in solution))
    else:
        print("No solution found")


if __name__ == "__main__":
    main()
