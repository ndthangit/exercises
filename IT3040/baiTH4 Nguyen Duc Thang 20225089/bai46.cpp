/*bai 4.6 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <bits/stdc++.h>
#include <set>

using namespace std;

void bfs(vector< list<int> > adj) {
    queue<int> Q;
    vector<bool> visited(adj.size());
    Q.push(1); // Bắt đầu từ đỉnh số 1
    
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

   visited[1] = true; 
    while (!Q.empty()) {
        int u = Q.front(); 
        Q.pop(); 
        cout << u << endl; 
        for (auto v : adj[u]) { 
            if (!visited[v]) { 
                Q.push(v); 
                visited[v] = true; 
            }
        }
    }
}
int main()
{
    // Tạo đồ thị dưới dạng danh sách kề (1-based index)
    // Ví dụ đồ thị:
    // 1 -> 2, 3
    // 2 -> 4
    // 3 -> 4
    // 4 -> 5
    std::vector<std::list<int>> adj(8); // 5 đỉnh (1-based, thêm 1 phần tử để dễ truy cập)

    adj[1].push_back(2);
    adj[2].push_back(4);
    adj[1].push_back(3);
    adj[3].push_back(4);
    adj[3].push_back(5);
    adj[5].push_back(2);
    adj[2].push_back(7);
    adj[6].push_back(7);

    std::cout << "DFS traversal starting from vertex 1: ";
    dfs(adj); // Gọi hàm DFS để duyệt đồ thị
    std::cout << std::endl;

    return 0;
}
/*bai 4.6 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/