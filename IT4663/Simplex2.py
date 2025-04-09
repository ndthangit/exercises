from ortools.linear_solver import pywraplp

def create_data_model():
    n,m = map(int, input().split())
    dl =[]
    du=[]
    for i in range(n):
        d, u = map(int, input().split())
        dl.append(d)
        du.append(u)
    c = list(map(int, input().split()))
    a=[]
    for i in range(m):
        a.append(list(map(int, input().split())))
    low = []
    up = []
    for i in range(m):
        l, u = map(int, input().split())
        low.append(l)
        up.append(u)
    return n, m, dl, du, c, a, low, up


def main():
    n, m, dl, du, c, a, low, up = create_data_model()



if __name__ == "__main__":
    main()
