# from main import importData
import time

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

        # matrix = []
        #
        # for i in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
        #     row = []
        #     if i < 2 * (data['NumParcel'] + data['NumPassenger']) + 1:
        #         for j in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
        #             if j > 2 * (data['NumParcel'] + data['NumPassenger']):
        #                 row.append(data['Matrix'][i][0])
        #             else:
        #                 row.append(data['Matrix'][i][j])
        #
        #     else:
        #         for j in range(2 * (data['NumParcel'] + data['NumPassenger']) + 2 * data['NumTaxis'] + 1):
        #             if j > 2 * (data['NumParcel'] + data['NumPassenger']):
        #                 row.append(0)
        #             else:
        #                 row.append(data['Matrix'][0][j])
        #     matrix.append(row)
        # data['Matrix'] = matrix

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
        data['Request'][i + 1+  2 * data['NumParcel'] + data['NumPassenger']] = -value
    # print(data['Request'])
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

    data['Depot'] = 0

    data['Delivery'] = {
        'PassengerRequest': [[i, i + n + m] for i in range(1, m + 1)],
        'ParcelRequest': [[i + n, i + 2 * n + m] for i in range(1, n + 1)]
    }

    data['Request'] = [0] * (2 * (n + 2 * m) + 1)
    for i in data['Quantity']:
        data['Request'][i + n] = i
        data['Request'][i + 2 * n + m] = -i

    return data

def select(dis: dict, visited: list) -> int:
    min_value = float('inf')
    min_index = -1
    for i in dis:
        if not visited[i] and dis[i] < min_value:
            min_value = dis[i]
            min_index = i
    return min_index

# def greedy(data)

def print_out_put(route: list) -> None:
    print(len(route))
    # total_distance = 0
    for i in route:
        print(len(i))
        print(' '.join(map(str, i)))

def main():
    # data = importData("test/test3.txt")
    data = importData2()
    # num_locations = 2 * (data['NumParcel'] + data['NumPassenger'])
    # visited = [False] * num_locations
    # visited[0] 0= True
    # print(data['Matrix'][13])
    # print(len(data['Request']))
    # print(data['Matrix'][0])

    start_time = time.time()


    route = [[] for _ in range(data['NumTaxis'])]
    for i in range(data['NumTaxis']):
        # route[i].append(num_locations + i + 1)
        route[i].append(0)
    # print(route[0][-1])
    cur_index_cap = [[] for _ in range(data['NumTaxis'])]
    cur_cap = [0]* data['NumTaxis']
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
                while cur_cap[taxi] + data['Request'][req[0]]> data['Capacity'][taxi]:
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

    end_tme =time.time()
    # print(f"Total time: {end_tme - start_time}")




    # print(route)
    # print(cur_dis)
    print_out_put(route)
    # print(calculate_route_distance(data,route))


if __name__ == "__main__":
    main()