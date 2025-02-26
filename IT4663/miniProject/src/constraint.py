from ortools.linear_solver import pywraplp
from ortools.sat.python import cp_model


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

    # Passenger request
    for i in range(1, data['NumPassenger'] + 1):
        data['Delivery']['PassengerRequest'].append([i, i + data['NumParcel'] + data['NumPassenger']])

    # Parcel request
    for i in range(1, data['NumParcel'] + 1):
        data['Delivery']['ParcelRequest'].append(
            [i + data['NumParcel'], i + 2 * data['NumParcel'] + data['NumPassenger']])


    data['Request']= [0]*(2 * (data['NumParcel'] + 2*data['NumPassenger'])+1)
    for i in data['Quantity']:
        data['Request'][i + data['NumParcel']] = i
        data['Request'][i + 2 * data['NumParcel'] + data['NumPassenger']] = -i

    return data


def main():
    data = importData("test/test1.txt")
    num_locations = 2 * (data['NumParcel'] + data['NumPassenger']) + 1


    # Creates the model.
    model = cp_model.CpModel()

    # Biến quyết định: result[i][j][k] = 1 nếu xe i đi qua điểm thứ j của chuyến đi và đi tiếp đến k
    result = [[[model.new_int_var(0, 1, f'result(vehicle: {i}, order: {j}, next: {k})')
                for j in range(data['NumTaxis'])]
               for i in range(num_locations)]
              for k in range(num_locations)]


    # Hàm mục tiêu: Tổng khoảng cách xe di chuyển phải nhỏ nhất
    objectiveFunction = 0
    for i in range(data['NumTaxis']):
        for j in range(num_locations):
            for k in range(num_locations):
                if result[i][j][k] == 1:
                    objectiveFunction += data['Matrix'][i][j] * result[i][j][k]
    model.Minimize(objectiveFunction)

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        pass
    else:
        print("No solution found.")


if __name__ == "__main__":
    main()