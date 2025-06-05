
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

def selection( slack, stacks, data, item):
    index = -1
    cost = 0
    for truck in range(data['NumTrucks']):
        if slack[truck] + data['Weights'][item] <= data['Capacities'][truck]:
            index = truck
            break
    return index


def find_max_capacity_index(capacities, x):
    valid_indices = [i for i in range(len(capacities)) if x[i] != -1]

    if not valid_indices:
        return None  # Không có chỉ số hợp lệ

    max_index = max(valid_indices, key=lambda i: capacities[i])
    return max_index


def main():
    data = create_data_model()

    slack = [0] * data['NumTrucks']
    stacks = []
    for i in range(data['NumTrucks']):
        stacks.append([])
    x = [-1]* data['NumItems']
    res =0

    while True:
        index = find_max_capacity_index(data['Capacities'], x)
        if index is None:
            break
        stacks[index] = []
        slack[index] = 0
    for item in range(data['NumItems']):
        index = selection(slack, stacks, data, item)
        if index != -1:
            stacks[index].append(item)
            x[item] = index+1
            slack[index] += data['Weights'][item]
            res += data['ValuePerItem'] * data['Weights'][item]
    # for items in range(data['NumItems']):
    #     for truck in range(data['NumTrucks']):
    #         if x[items] == truck + 1:
    #             print(f"Item {items} is assigned to Truck {truck + 1}")


    print(data['NumItems'])
    print(' '.join(map(str, x)))

if __name__ == "__main__":
    main()