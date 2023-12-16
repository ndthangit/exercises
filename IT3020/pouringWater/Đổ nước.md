---
Title: Toán Rời Rạc
Lecture: Tìm kiếm theo chiều sâu trên đồ thị
Author: Trần Vĩnh Đức
---
# Bài toán Đổ nước

Ta có ba bình thể tích $10$ lít, $7$ lít, và $4$ lít. Ban đầu,
  bình $7$ lít và $4$ lít chứa đầy nước, còn bình $10$ lít rỗng. Ta
  chỉ được phép sử dụng thao tác sau: Đổ hết lượng nước còn lại từ một bình sang một bình khác, chỉ dừng khi bình rỗng hoặc bình kia đầy. 

**Bài toán đổ nước:** Liệu với một dãy các thao tác này, ta có thể để lại đúng $2$ lít nước trong bình $4$ lít hoặc $2$ lít nước trong bình $7$ lít không?  

Để giải bài toán này, ta xây dựng đồ thị có hướng $G=(V,E)$ trong đó: 

- Tập đỉnh $V$ là các bộ ba số nguyên không âm $(x,y,z)$ trong đó $x, y$ và $z$ tương ứng là lượng nước trong ba bình $10$ lít, $7$ lít và $4$ lít. *Ví dụ*, đỉnh $(0,7,4)$ thể hiện: bình $10$ lít rỗng, còn bình $7$ lít và $4$ lít chứa đầy nước. 
- Có cung nối từ đỉnh $(x,y,z)$ tới đỉnh $(x', y', z')$ nếu từ $(x,y,z)$ có thể sử dụng thao tác đổ nước như ở trên để thu  được $(x',y',z')$. 
				Ví dụ, $(0, 7, 4) \to (4,7,0) \to (10, 1, 0)$ có nghĩa rằng ta đổ hết nước từ bình $4$ lít sang bình $10$ lít, và đổ đầy bình $10$ lít từ bình $7$ lít.

Hãy chạy thuật toán DFS trên đồ thị $G$ này bắt đầu từ đỉnh $(0,7,4)$ để tìm lời giải cho bài toán đổ nước. 

**Yêu cầu:** Hãy vẽ cây DFS (không cần các cung nét đứt) dùng Graphviz bắt đầu từ đỉnh $(0,7,4)$. Nếu cần quyết định thứ tự các đỉnh thăm, bạn hãy  sử dụng một thứ tự mà theo bạn là tự nhiên.
	