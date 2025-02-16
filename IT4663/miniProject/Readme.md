# People and Parcel Share a Ride

## Mô tả bài toán

- Có **𝐾** taxi (đặt tại điểm 0) được lên lịch để phục vụ các yêu cầu vận chuyển bao gồm **𝑁** yêu cầu hành khách (1, 2, ..., 𝑁) và **𝑀** yêu cầu hàng hóa (1, 2, ..., 𝑀).
- Yêu cầu hành khách thứ **𝑖** (𝑖 = 1, ..., 𝑁) có điểm đón là **𝑖** và điểm trả là **𝑖 + 𝑁 + 𝑀**.
- Yêu cầu hàng hóa thứ **𝑖** (𝑖 = 1, ..., 𝑀) có điểm đón là **𝑖 + 𝑁** và điểm trả là **𝑖 + 2𝑁 + 𝑀**.
- **𝑑(𝑖, 𝑗)** là khoảng cách di chuyển từ điểm **𝑖** đến điểm **𝑗** (𝑖, 𝑗 = 0, 1, ..., 2𝑁 + 2𝑀).
- Mỗi hành khách phải được phục vụ bởi một chuyến đi trực tiếp không bị gián đoạn (không có điểm dừng giữa điểm đón và điểm trả của hành khách trong mỗi tuyến đường).
- Mỗi taxi **𝑘** có sức chứa **𝑄[𝑘]** để phục vụ các yêu cầu hàng hóa.
- Yêu cầu hàng hóa thứ **𝑖** (𝑖 = 1, 2, ..., 𝑀) có khối lượng **𝑞[𝑖]**.

## Yêu cầu

- Tính toán các tuyến đường cho các taxi sao cho thỏa mãn các ràng buộc trên và độ dài của tuyến đường dài nhất trong số **𝐾** taxi là nhỏ nhất (để cân bằng độ dài giữa các taxi).
- Một tuyến đường của taxi **𝑘** được biểu diễn bằng một chuỗi các điểm mà tuyến đường đó đi qua: **𝑟[0], 𝑟[1], ..., 𝑟[𝐿𝑘]** trong đó **𝑟[0] = 𝑟[𝐿𝑘] = 0** (điểm xuất phát).

## Đầu vào

- **Dòng 1**: chứa **𝑁**, **𝑀**, và **𝐾** (1 ≤ 𝑁, 𝑀 ≤ 500, 1 ≤ 𝐾 ≤ 100).
- **Dòng 2**: chứa **𝑞[1], 𝑞[2], ..., 𝑞[𝑀]** (1 ≤ 𝑞[𝑖] ≤ 100).
- **Dòng 3**: chứa **𝑄[1], 𝑄[2], ..., 𝑄[𝐾]** (1 ≤ 𝑄[𝑖] ≤ 200).
- **Dòng 𝑖 + 3** (𝑖 = 0, 1, ..., 2𝑁 + 2𝑀): chứa hàng thứ **𝑖** của ma trận khoảng cách.

## Đầu ra

- **Dòng 1**: chứa một số nguyên **𝐾**.
- **Dòng 2𝑘** (𝑘 = 1, 2, ..., 𝐾): chứa một số nguyên dương **𝐿𝑘**.
- **Dòng 2𝑘 + 1** (𝑘 = 1, 2, ..., 𝐾): chứa một chuỗi **𝐿𝑘** số nguyên **𝑟[0], 𝑟[1], ..., 𝑟[𝐿𝑘]**.

## Ví dụ

### Đầu vào
3 3 2 \
8 4 5 \
16 16 \
0 8 7 9 6 5 11 6 11 12 12 12 13\
8 0 4 1 2 8 5 13 19 12 4 8 9\
7 4 0 3 3 8 4 12 15 8 5 6 7\
9 1 3 0 3 9 4 14 19 11 3 7 8\
6 2 3 3 0 6 6 11 17 11 6 9 10\
5 8 8 9 6 0 12 5 16 15 12 15 15\
11 5 4 4 6 12 0 16 18 7 4 3 4\
6 13 12 14 11 5 16 0 15 18 17 18 19\
11 19 15 19 17 16 18 15 0 13 21 17 17\
12 12 8 11 11 15 7 18 13 0 11 5 4\
12 4 5 3 6 12 4 17 21 11 0 7 8\
12 8 6 7 9 15 3 18 17 5 7 0 1\
13 9 7 8 10 15 4 19 17 4 8 1 0\


### Đầu ra
2\
6\
0 5 1 7 11 0\
10\
0 4 6 10 3 9 12 2 8 0


## Lưu ý

- Đảm bảo rằng các ràng buộc về sức chứa của taxi và yêu cầu không bị gián đoạn của hành khách được tuân thủ.
- Mục tiêu là tối thiểu hóa độ dài của tuyến đường dài nhất trong số các taxi.