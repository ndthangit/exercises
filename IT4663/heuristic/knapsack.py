def create_data_model():
    data = {}
    # Danh sách trọng số các vật
    data['w'] = [4, 8, 1, 4, 2, 1]
    data['w'].sort(reverse=True)  # Duyệt từ vật nặng nhất trước
    data['capacity'] = 10
    return data

data = create_data_model()
visited = [False] * len(data['w'])
count = 0

def find_fit(cap):
    for i, val in enumerate(data['w']):
        if not visited[i] and val <= cap:
            return i, val
    return None, None

for i in range(len(data['w'])):
    if not visited[i]:
        visited[i] = True
        count += 1
        remaining = data['capacity'] - data['w'][i]
        while True:
            key, val = find_fit(remaining)
            if key is None:
                break
            visited[key] = True
            remaining -= val

print("Số thùng cần dùng:", count)
