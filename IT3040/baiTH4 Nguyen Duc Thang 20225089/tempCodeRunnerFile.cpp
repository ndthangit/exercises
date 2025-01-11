void dfs(std::vector<std::list<int>> adj)
{
    std::stack<int> S;
    std::vector<bool> visited(adj.size(), false); // Đánh dấu tất cả các đỉnh chưa được thăm
    S.push(1);                                    // Bắt đầu từ đỉnh số 1 (giả sử đồ thị dùng 1-based index)

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    while (!S.empty())
    {
        int u_thangnd = S.top(); // Lấy đỉnh trên cùng của stack
        S.pop();

        if (!visited[u_thangnd])
        {
            std::cout << u_thangnd << std::endl; // In ra đỉnh đang thăm
            visited[u_thangnd] = true;           // Đánh dấu đỉnh này đã thăm
        }

        // Duyệt các đỉnh kề với đỉnh u
        std ::set<int> p;

        for (auto v : adj[u_thangnd])
        {
            if (!visited[v])
            {
                // S.push(v); // Đưa đỉnh kề chưa thăm vào stack
                p.insert(v);
            }
        }
        for (auto i : p)
            S.push(i);
    }
}