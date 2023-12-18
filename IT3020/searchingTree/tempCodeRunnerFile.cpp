bool check2differentWords(const string &word1, const string &word2)
{
    // Kiểm tra xem bốn chữ cuối của word1 có xuất hiện trong word2 hay không
    size_t len = word1.length();
    return (word2.find(word1.substr(len - 4)) != string::npos);
}