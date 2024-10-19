/*
A database contains a sequence of key k1, k2, ..., kn which are strings (1<=n<=100000). Perform a sequence of actions of two kinds:
· find k: find and return 1 if k exists in the database, and return 0, otherwise
· insert k: insert a key k into the database and return 1
if the insertion is successful (k does not exist in the database) and return 0 if the insertion is failed (k exists in the database)
Note that the length of any key is greater than 0 and less than or equal to 50.
Input
Two blocks of information. The first block contains a key of (k1,k2,...,kn) in each line.
The first block is terminated with a line containing *.
 The second block is a sequence of actions of two finds described above:
 each line contains 2 string: cmd and k in which cmd = find or insert and k is the key (parameter of the action).
 The second block is terminated with a line containing ***. Note that the number of actions can be up to 100000.
Output
Each line contains the result (0 or 1) of the corresponding action.
Example
Input
computer
university
school
technology
phone
*
find school
find book
insert book
find algorithm
find book
insert book
***
Output
1
0
1
0
1
0
*/
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
    unordered_set<string> database;
    string input;


    while (true) {
        cin >> input;
        if (input == "*") {
            break;
        }
        database.insert(input);
    }


    string command, key;
    while (true) {
        cin >> command >> key;
        if (command == "***") {
            break;
        }
        if (command == "find") {
            if (database.find(key) != database.end()) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        } else if (command == "insert") {
            if (database.find(key) != database.end()) {
                cout << 0 << endl;
            } else {
                database.insert(key);
                cout << 1 << endl;
            }
        }
    }

    return 0;
}

