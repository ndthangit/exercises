def greedy(data):
    route = [[] for _ in range(data['NumTaxis'])]
    for i in range(data['NumTaxis']):
        # route[i].append(num_locations + i + 1)
        route[i].append(0)
    # print(route[0][-1])
    cur_index_cap = [[] for _ in range(data['NumTaxis'])]
    cur_cap = [0] * data['NumTaxis']
    cur_dis = [0] * data['NumTaxis']

    for req in data['Delivery']['PassengerRequest']:
        taxi = cur_dis.index(min(cur_dis))
        # print(taxi)
        # print(type(route[taxi][0]))
        # print(req)
        cur_dis[taxi] += data['Matrix'][route[taxi][-1]][req[0]]
        route[taxi].append(req[0])
        # print(route[taxi])
        # print(data['Matrix'][route[taxi][-1]][req[0]])

        cur_dis[taxi] += data['Matrix'][route[taxi][-1]][req[1]]
        route[taxi].append(req[1])

        # print(cur_dis)

    # print(cur_dis)
    for req in data['Delivery']['ParcelRequest']:
        taxi = cur_dis.index(min(cur_dis))
        if cur_index_cap[taxi] == []:
            cur_dis[taxi] += data['Matrix'][route[taxi][-1]][req[0]]
            route[taxi].append(req[0])

            cur_cap[taxi] += data['Request'][req[0]]
            cur_index_cap[taxi].append(req[1])
        else:
            if cur_cap[taxi] + data['Request'][req[0]] <= data['Capacity'][taxi]:
                cur_dis[taxi] += data['Matrix'][route[taxi][-1]][req[0]]
                route[taxi].append(req[0])

                cur_index_cap[taxi].append(req[1])
                cur_cap[taxi] += data['Request'][req[0]]
            else:
                while cur_cap[taxi] + data['Request'][req[0]] > data['Capacity'][taxi]:
                    point = cur_index_cap[taxi][0]
                    for i in cur_index_cap[taxi][1:]:
                        if data['Matrix'][route[taxi][-1]][i] < data['Matrix'][route[taxi][-1]][point]:
                            point = i
                    cur_dis[taxi] += data['Matrix'][route[taxi][-1]][point]
                    route[taxi].append(point)
                    cur_index_cap[taxi].remove(point)

                    cur_cap[taxi] += data['Request'][point]
                cur_dis[taxi] += data['Matrix'][route[taxi][-1]][req[0]]
                route[taxi].append(req[0])
                cur_index_cap[taxi].append(req[1])

                cur_cap[taxi] += data['Request'][req[0]]
    #     print(cur_dis)
    # print(cur_index_cap)

    for taxi in range(data['NumTaxis']):
        while cur_index_cap[taxi] != []:
            point = cur_index_cap[taxi][0]
            for i in cur_index_cap[taxi][1:]:
                if data['Matrix'][route[taxi][-1]][i] < data['Matrix'][route[taxi][-1]][point]:
                    point = i
            route[taxi].append(point)
            cur_index_cap[taxi].remove(point)
            cur_dis[taxi] += data['Matrix'][route[taxi][-1]][point]
            cur_cap[taxi] += data['Request'][point]
        # route[taxi].append(num_locations + data['NumTaxis']+taxi+1)
        cur_dis[taxi] += data['Matrix'][route[taxi][-1]][0]
        route[taxi].append(0)
    return route