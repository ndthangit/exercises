from ortools.linear_solver import pywraplp
from ortools.sat.python import cp_model

def create_data_model():
    data = {}

    n, m = map(int, input().split())
    data['NumTeachers'] = n
    data['NumCourses'] = m
    data['CanTeach'] =[]
    for i in range(n):
        a = list(map(int, input().split()))
        a.remove(a[0])
        data['CanTeach'].append(a)
    y = int(input())
    data['Conflict']=[]
    for i in range(y):
        a,b = map(int, input().split())
        data['Conflict'].append([a,b])
    return data
def main():
    data = create_data_model()
    model = cp_model.CpModel()
    # model = pywraplp.Solver.CreateSolver('SCIP')

    x = [[model.NewIntVar(0,1,f"teacher {j} course {i}") for i in range(data['NumCourses']+1)] for j in range(data['NumTeachers'])]

    sumcou = [model.NewIntVar(0, data['NumCourses'], f"sum cou teach{i}") for i in range(data['NumTeachers'])]

    # max_cou = maximum courses assigned to any teacher (this is what we want to minimize)
    max_cou = model.NewIntVar(0, data['NumCourses'], "max_cou")

    # mỗi môn chỉ được dạy bởi 1 giáo viên
    for i in range(1, data['NumCourses']+1):
        model.Add(sum(x[j][i] for j in range(data['NumTeachers'])) == 1)



    #các môn gv không thể dạy thì = 0
    for id, course_list in enumerate(data['CanTeach']):
        for i in range(1, data['NumCourses']+1):
            if i not in course_list:
                model.Add(x[id][i] == 0)
    # print(data['CanTeach'])

    #mỗi môn 1 người dạy
    for course in range(1, data['NumCourses']+1):
        model.Add(sum(x[i][course] for i in range(data['NumTeachers'])) == 1)
    model.Add(sum(x[j][0] for j in range(data['NumTeachers'])) == 0)

    for conflict in data['Conflict']:
        for teacher in range(data['NumTeachers']):
            model.Add(x[teacher][conflict[0]]+ x[teacher][conflict[1]] < 2)

    # Constraints
    for j in range(data['NumTeachers']):
        model.Add(sumcou[j] == sum(x[j][i] for i in range(data['NumCourses']+1)))
        model.Add(max_cou >= sumcou[j])

    model.Minimize(max_cou)
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL:
        # print(f"Optimal Solution Found!")
        # print(f"Minimized Maximum Courses per Teacher: {solver.ObjectiveValue():.0f}")
        print(f"{solver.ObjectiveValue():.0f}")

        # Print assignments
        # for j in range(data['NumTeachers']):
        #     courses_assigned = [i for i in range(data['NumCourses']) if solver.Value(x[j][i])]
        #     print(f"Teacher {j} teaches courses: {courses_assigned}")
    else:
        print("No optimal solution found.")


if __name__ == '__main__':
    main()