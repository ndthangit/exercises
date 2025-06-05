def create_data_model():
    data = {}
    n, m, s, l = map(int, input().split())
    data['NumNodes'] = n
    data['NumEdges'] = m
    data['depot'] = s
    data['limit'] = l
    data['Edge'] = []
    data['time'] = {}
    data['cost'] = {}
    data['graph'] = {i: [] for i in range(n+1)}  # Initialize graph with empty lists
    for i in range(m):
        u, v, t, c = map(int, input().split())
        data['Edge'].append([u, v])
        data['time'][(u, v)] = t
        data['time'][(v, u)] = t
        data['cost'][(u, v)] = c
        data['cost'][(v, u)] = c
        data['graph'][u].append(v)
        data['graph'][v].append(u)

    return data


def isStop(visited):
    for i in visited:
        if not i:
            return False
    return True


def search(data, node, visited, slack, res):
    lim = 99999
    next = -1
    visited[node] = True
    for next_node in data['graph'][node]:  # Remove unnecessary slicing
        if not visited[next_node]:
            if data['time'][(node, next_node)] < lim and slack[node] + data['time'][(node, next_node)] <= data['limit']:
                next = next_node
                lim = data['time'][(node, next_node)]

    if next == -1:
        return None
    else:
        # visited[next] = True
        slack[next] = slack[node] + data['time'][(node, next)]
        res.append((node, next))
        return next


def main():
    data = create_data_model()

    slack = [0] * (data['NumNodes']+1)
    visited = [False] * (data['NumNodes']+1)
    visited[0]= True
    res = []

    for i in range(len(data['graph'][data['depot']])):
        next = search(data, data['depot'], visited, slack, res)
        while next is not None:
            next = search(data, next, visited, slack, res)

    # print(visited)
    # print(slack)

    for i in range(data['NumNodes']+1):
        if not visited[i]:  # Fix condition to check if node is visited
            print("NO_SOLUTION")
            return
    else:
        total_cost = sum(data['cost'][(edge[0], edge[1])] for edge in res)
        print(total_cost)
        return


if __name__ == '__main__':
    main()