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

    data['Depot']=0

    data['Delivery'] = {
        'PassengerRequest': [],
        'ParcelRequest': []
    }

    # Passenger data['Request']
    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

    # Parcel data['Request']
    for i in range(1, data['NumParcel'] + 1):
        data['Delivery']['ParcelRequest'].append(
            [i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']])


    data['Request']= [0]*(2 * (data['NumParcel'] + 2*data['NumPassenger'])+1)
    for i in data['Quantity']:
        data['Request'][i + data['NumParcel']] = i
        data['Request'][i + 2 * data['NumParcel'] + data['NumPassenger']] = -i

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


def calculate_route_distance(data, routes):
    """
    Tính toán độ dài mỗi tuyến đường của từng xe dựa trên dữ liệu đầu vào

    Args:
        data: Dữ liệu đã được import từ hàm importData
        route1: Danh sách các điểm trong lộ trình xe 1 (bao gồm cả điểm đầu và cuối là 0 - depot)
        route2: Danh sách các điểm trong lộ trình xe 2 (bao gồm cả điểm đầu và cuối là 0 - depot)

    Returns:
        Tuple (distance1, distance2) là độ dài tuyến đường của xe 1 và xe 2
    """

    def calculate_single_route_distance(route):
        """Tính độ dài của một tuyến đường đơn lẻ"""
        distance = 0
        for i in range(len(route)-1):
            from_point = route[i]
            to_point = route[i + 1]
            distance += data['Matrix'][from_point][to_point]
        return distance

    return sum(calculate_single_route_distance(route) for route in routes)
def main():
    dataPath = "test/test5.txt"  # Replace with your actual data file path
    data = importData(dataPath)
    check =[
               [0, 5, 3, 9, 11, 1, 7, 0],
               [0, 4, 10, 6, 12, 2, 8, 0]
           ]
    sample=[
            [0, 4, 10, 6, 12, 2, 8, 0],
            [0, 5, 3, 9, 11, 1, 7, 0]
        ]
    print(calculate_route_distance(data, check))
    print(calculate_route_distance(data, sample))


if __name__ == '__main__':
    main()