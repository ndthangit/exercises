/*bai 4.8 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <map>

using namespace std;

template<class T>
map<T, double> fuzzy_set_union(const map<T, double> &a, const map<T, double> &b) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

   map<T, double> c; 
    for (auto it = a.begin(); it != a.end(); ++it) { 
        c[it->first] = it->second; 
    }
    for (auto it = b.begin(); it != b.end(); ++it) { 
        if (c.find(it->first) == c.end()) { 
            c[it->first] = it->second; 
        } else { 
            c[it->first] = max(c[it->first], it->second); 
        }
    }
    return c;
}

template<class T>
map<T, double> fuzzy_set_intersection(const map<T, double> &a, const map<T, double> &b) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

   map<T, double> c; // result
    for (auto it = a.begin(); it != a.end(); ++it) { 
        if (b.find(it->first) != b.end()) { 
            c[it->first] = min(it->second, b.at(it->first)); 
        }
    }
    return c;
}

template<class T>
void print_fuzzy_set(const std::map<T, double> &a) {
    cout << "{ ";
    for (const auto &x : a) {
        std::cout << "(" << x.first << ", " << x.second << ") ";
    }
    cout << "}";
    std::cout << std::endl;
}

int main() {
    std::map<int, double> a = {{1, 0.2}, {2, 0.5}, {3, 1}, {4, 0.6}, {5, 0.7}};
    std::map<int, double> b = {{1, 0.5}, {2, 0.4}, {4, 0.9}, {5, 0.4}, {6, 1}};
    std::cout << "A = "; print_fuzzy_set(a);
    std::cout << "B = "; print_fuzzy_set(b);
    std::map<int, double> c = fuzzy_set_union(a, b);
    std::map<int, double> d = fuzzy_set_intersection(a, b);
    std::cout << "Union: "; print_fuzzy_set(c);
    std::cout << "Intersection: "; print_fuzzy_set(d);
}
/*bai 4.8 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/