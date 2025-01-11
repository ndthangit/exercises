#include <bits/stdc++.h>
using namespace std;

struct Citizen {
    string code;          // Mã công dân
    string date_of_birth; // Ngày sinh
    string father_code;   // Mã cha
    string mother_code;   // Mã mẹ
    char is_alive;        // Trạng thái sống
    string region_code;   // Mã vùng
};

// Hàm chuyển chuỗi thành số nguyên
int toInt(string s) {
    int result = 0, multiplier = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        result += (s[i] - '0') * multiplier;
        multiplier *= 10;
    }
    return result;
}

// Hàm xử lý ngày thành chỉ số duy nhất (để lưu trữ dữ liệu thống kê sinh nhật)
int dateToIndex(const string& date) {
    int year = stoi(date.substr(0, 4)) - 1900;
    int month = stoi(date.substr(5, 2)) - 1;
    int day = stoi(date.substr(8, 2)) - 1;
    return year * 500 + month * 31 + day;
}

int main() {
    vector<Citizen> citizenList; // Danh sách công dân
    vector<int> birthIndex(150000, 0); // Lưu trữ số người sinh nhật tới một ngày nhất định
    map<string, int> numPeopleBorn;    // Lưu số người sinh vào từng ngày
    map<string, int> maxAncestorAge;  // Tuổi tổ tiên lâu đời nhất
    map<string, int> relationCount;   // Số lượng quan hệ của từng công dân
    int totalPeople = 0;

    string line;
    // Nhập dữ liệu công dân
    while (getline(cin, line) && line != "*") {
        stringstream ss(line);
        Citizen citizen;
        ss >> citizen.code >> citizen.date_of_birth >> citizen.father_code >> citizen.mother_code >> citizen.is_alive >> citizen.region_code;

        citizenList.push_back(citizen);
        totalPeople++;

        // Tăng số người sinh trong ngày
        int index = dateToIndex(citizen.date_of_birth);
        birthIndex[index]++;
        numPeopleBorn[citizen.date_of_birth]++;

        // Cập nhật tuổi tổ tiên và quan hệ
        if (citizen.father_code != "0000000") {
            maxAncestorAge[citizen.code] = max(maxAncestorAge[citizen.father_code], maxAncestorAge[citizen.mother_code]) + 1;
            relationCount[citizen.father_code]++;
            relationCount[citizen.mother_code]++;
        }
    }

    // Tích lũy birthIndex để tính nhanh số người sinh giữa hai ngày
    for (int i = 1; i < 150000; i++) {
        birthIndex[i] += birthIndex[i - 1];
    }
    sort(citizenList.begin(), citizenList.end(),[](const Citizen& a, const Citizen)
    {
        return a.date_of_birth< b.date_of_birth
    });
    auto findFirstIndex = [&](const string& time) {
        return lower_bound(citizenList.begin(), citizenList.end(), time, [](const Citizen& city, const string& time) {
            return city.date_of_birth < time;
        }) - citizenList.begin();
    };

    auto findLastIndex = [&](const string& time) {
        auto it = upper_bound(citizenList.begin(), citizenList.end(), time, [](const string& time, const Citizen& city) {
            return time < city.date_of_birth;
        });
        return it == citizenList.begin() ? -1 : it - citizenList.begin() - 1;
    };

    // Xử lý truy vấn
    while (getline(cin, line) && line != "***") {
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "NUMBER_PEOPLE") {
            cout << totalPeople << "\n";
        } else if (query == "NUMBER_PEOPLE_BORN_AT") {
            string date;
            ss >> date;
            cout << numPeopleBorn[date] << "\n";
        } else if (query == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string startDate, endDate;
            ss >> startDate >> endDate;

            int startIdx = dateToIndex(startDate);
            int endIdx = dateToIndex(endDate);
            cout << (birthIndex[endIdx] - (startIdx > 0 ? birthIndex[startIdx - 1] : 0)) << "\n";
        } else if (query == "MOST_ALIVE_ANCESTOR") {
            string fromTime, toTime;
            ss >> fromTime >> toTime;

            int start_index = findFirstIndex(fromTime);
            int end_index = findLastIndex(toTime);

            if (start_index <= end_index) {
                cout << end_index - start_index +1<< endl;
            } else {
                cout << 0 << endl;
            }
        } else if (query == "MAX_UNRELATED_PEOPLE") {
            // Tính số người không liên quan (ví dụ)
            vector<int> relationCounts;
            for (const auto& [_, count] : relationCount) {
                relationCounts.push_back(count);
            }
            sort(relationCounts.rbegin(), relationCounts.rend());

            int unrelatedPeople = totalPeople;
            for (int count : relationCounts) {
                if (count > 0) unrelatedPeople--;
            }
            cout << unrelatedPeople << "\n";
        }
    }

    return 0;
}
