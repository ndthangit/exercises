/*bai 2.12 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main() {
    vector<pair<int, int>> list_thangnd;
    map<int, int> index_thangnd;
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    cout<< "Input= ";

    for (int i = 0; true; ++i) {
        static string s_thangnd;
        getline(cin, s_thangnd);

        if (s_thangnd.empty()) {
            break;
        } else {
            int key_thangnd, value_thangnd;
            stringstream ss_thangnd(s_thangnd);
            
            ss_thangnd >> key_thangnd >> value_thangnd;
            
            if (index_thangnd.find(key_thangnd) == index_thangnd.end()) {
                list_thangnd.emplace_back(key_thangnd, value_thangnd);
                index_thangnd[key_thangnd] = i;
            } else {
                list_thangnd[index_thangnd[key_thangnd]] = make_pair(key_thangnd, value_thangnd);
                --i;
            }
        }
    }

    sort(list_thangnd.begin(), list_thangnd.end(), [](pair<int, int> a_thangnd, pair<int, int> b_thangnd) -> bool {
        if (a_thangnd.second > b_thangnd.second) return true;
        if (a_thangnd.second < b_thangnd.second) return false;
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

        return a_thangnd.first > b_thangnd.first;
    });

    cout<< "Output= ";
    for (auto i : list_thangnd) {
        cout << i.first << " " << i.second << endl;
    }

    return 0;
}
/*bai 2.12 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
