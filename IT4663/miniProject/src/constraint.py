import sys

def check_next_point(next_client, vehicle):
    if next_client > 0 and visited[next_client]:
        return False
    if cur_capacity[vehicle] + request[next_client] > capacity:
        return False
    return True


def try_schedule(point, vehicle):
    global cur_route, min_route, num_visited

    if point == 0:
        if vehicle < num_trucks:
            try_schedule(first_point[vehicle + 1], vehicle + 1)
        return

    for next_client in range(num_clients + 1):
        if check_next_point(next_client, vehicle):
            visited[next_client] = True
            next_point[vehicle] = next_client
            cur_route += dis[point][next_client]
            cur_capacity[vehicle] += request[next_client]
            num_visited += 1

            if next_client > 0:
                predict = cur_route + (num_clients + nbr - num_visited) * dis_min
                if predict < min_route:
                    try_schedule(next_client, vehicle)
            else:
                if vehicle == num_trucks:
                    if (num_clients + nbr) == num_visited:
                        min_route = min(min_route, cur_route)
                else:
                    predict = cur_route + (num_clients + nbr - num_visited) * dis_min
                    if predict < min_route:
                        try_schedule(first_point[vehicle + 1], vehicle + 1)

            visited[next_client] = False
            cur_route -= dis[point][next_client]
            cur_capacity[vehicle] -= request[next_client]
            num_visited -= 1


def check_first_point(point, vehicle):
    if point == 0:
        return True
    if visited[point]:
        return False
    if cur_capacity[vehicle] + request[point] > capacity:
        return False
    return True


def try_first_point(vehicle):
    global nbr, cur_route, num_visited
    s = 0
    if first_point[vehicle - 1] > 0:
        s = first_point[vehicle - 1] + 1

    for client in range(s, num_clients + 1):
        if check_first_point(client, vehicle):
            first_point[vehicle] = client
            if client > 0:
                num_visited += 1
            visited[client] = True
            cur_route += dis[0][client]
            cur_capacity[vehicle] += request[client]

            if vehicle < num_trucks:
                try_first_point(vehicle + 1)
            else:
                nbr = num_visited
                try_schedule(first_point[1], 1)

            if client > 0:
                num_visited -= 1
            visited[client] = False
            cur_route -= dis[0][client]
            cur_capacity[vehicle] -= request[client]


if __name__ == "__main__":
    sys.setrecursionlimit(10 ** 6)

    num_clients, num_trucks, capacity = map(int, input().split())
    request = [0] + list(map(int, input().split()))

    visited = [False] * (num_clients + 1)
    first_point = [0] * (num_trucks + 1)
    next_point = [0] * (num_trucks + 1)
    cur_capacity = [0] * (num_trucks + 1)
    cur_route_vehicle = [0] * (num_trucks + 1)
    num_visited = 0
    min_route = float('inf')
    cur_route = 0
    dis_min = float('inf')
    first_point[0] = 0

    dis = [[0] * (num_clients + 1) for _ in range(num_clients + 1)]

    for i in range(num_clients + 1):
        row = list(map(int, input().split()))
        for j in range(num_clients + 1):
            dis[i][j] = row[j]
            if 0 < dis[i][j] < dis_min:
                dis_min = dis[i][j]

    try_first_point(1)

    print(min_route)
