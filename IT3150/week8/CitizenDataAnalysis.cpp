/*CITIZEN
Given a DataBase about citizen, perform queries over this DataBase.
Input
The input consists of two blocks: the first block is the DataBase and the second block is the list of queries. Two blocks are separated by a line containing a character *.
1. The first block (DataBase about citizen) consists of lines (number of lines can be upto 100000), each line is the information about a person and is under the format:
                                   <code>  <dat_of_birth>  <father_code>   <mother_code>  <is_alive>  <region_code>
in which:
 <code>: the code of the person which is a string of length 7
 <date_of_birth>: the date of birth of the person and has the format YYYY-MM-DD (for example 1980-02-23), <date_of_birth> is before 3000-12-31
 <father_code> and <mother_code> is the code of father and mother: they are also strings of length 7. If the code is 0000000, then the current person does not has information about his father or mother
 <is_alive>: a character with two values: ‘Y’ means that the person is still alive, and ‘N’ means tat the current person is died.
 <region_code>: the code of the region where the person lives

2. The second block is the list of queries (number of queries can be upto 100000) over the DataBase which consists of following commands:
 NUMBER_PEOPLE: return the number of people (number of lines of the DataBase)
 NUMBER_PEOPLE_BORN_AT <date>: return the number of people having date-of-birth is equal to <date>
 MOST_ALIVE_ANCESTOR <code>: find the most ancestor (farthest in term of generation distance) of the given person <code>. Return the generation distance between the ancestor found and the given person
 NUMBER_PEOPLE_BORN_BETWEEN <from_date> <to_date>: compute the number of people having date-of-birth between <from_date> and <to_date> (<from_date> and <to_date> are under the form YYYY-MM-DD, <to_date> is before 3000-12-31)
 MAX_UNRELATED_PEOPLE: find a subset of people in which two any people of the subset do not have father/mother-children and the size of the subset is maximal. Return the size of the subset found.
The second block is terminated by a line containing ***.
Output
 Each line presents the result of the corresponding query (described above).
Example
Input
0000001 1920-08-10 0000000 0000000 Y 00002
0000002 1920-11-03 0000000 0000000 Y 00003
0000003 1948-02-13 0000001 0000002 Y 00005
0000004 1946-01-16 0000001 0000002 Y 00005
0000005 1920-11-27 0000000 0000000 Y 00005
0000006 1920-02-29 0000000 0000000 Y 00004
0000007 1948-07-18 0000005 0000006 Y 00005
0000008 1948-07-18 0000005 0000006 Y 00002
0000009 1920-03-09 0000000 0000000 Y 00005
0000010 1920-10-16 0000000 0000000 Y 00005
*
NUMBER_PEOPLE
NUMBER_PEOPLE_BORN_AT 1919-12-10
NUMBER_PEOPLE_BORN_AT 1948-07-18
MAX_UNRELATED_PEOPLE
MOST_ALIVE_ANCESTOR 0000008
MOST_ALIVE_ANCESTOR 0000001
NUMBER_PEOPLE_BORN_BETWEEN 1900-12-19 1928-11-16
NUMBER_PEOPLE_BORN_BETWEEN 1944-08-13 1977-12-15
NUMBER_PEOPLE_BORN_BETWEEN 1987-01-24 1988-06-03
***
Output
10
0
2
6
1
0
6
4
0*/
#include <bits/stdc++.h>

using namespace std;

struct Citizen
{
    string code;
    string date_of_birth;
    string father_code;
    string mother_code;
    char is_alive;
    string region_code;
};

int toInt(string s) {
    int result = 0, multiplier = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        result += (s[i] - '0') * multiplier;
        multiplier *= 10;
    }
    return result;
}

int main()
{
    vector<Citizen> citizenList;
    map<string,int> numPeopleBorn;
    string line;

    while (getline(cin, line) && line != "*")
    {
        stringstream ss(line);
        Citizen citizen;
        ss >> citizen.code >> citizen.date_of_birth >> citizen.father_code >> citizen.mother_code >> citizen.is_alive >> citizen.region_code;


        citizenList.push_back(citizen);
        numPeopleBorn[citizen.date_of_birth]++;


        if (citizen.father_code != "0000000")
        {
            relationships[citizen.code].insert(citizen.father_code);
            relationships[citizen.father_code].insert(citizen.code);
        }
        if (citizen.mother_code != "0000000")
        {
            relationships[citizen.code].insert(citizen.mother_code);
            relationships[citizen.mother_code].insert(citizen.code);
        }
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

    // Process queries
    while (getline(cin, line) && line != "***")
    {
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "NUMBER_PEOPLE")
        {
            cout << citizens.size() << endl;
        }
        else if (query == "NUMBER_PEOPLE_BORN_AT")
        {
            string date;
            ss >> date;
            cout << numPeopleBorn[date] << endl;
        }
        else if (query == "MOST_ALIVE_ANCESTOR")
        {
            string code;
            ss >> code;
            cout<< maxAncestorAge[toInt(code)]<< endl;

        }
        else if (query == "NUMBER_PEOPLE_BORN_BETWEEN")
        {
            string fromTime, toTime;
            ss >> fromTime >> toTime;

            int start_index = findFirstIndex(fromTime);
            int end_index = findLastIndex(toTime);

            if (start_index <= end_index) {
                cout << end_index - start_index +1<< endl;
            } else {
                cout << 0 << endl;
            }
        }
        else if (query == "MAX_UNRELATED_PEOPLE")
        {
            cout << findMaxUnrelatedPeople(citizenList, relationships) << endl;
        }
    }

    return 0;
}
