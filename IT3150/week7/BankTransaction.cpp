/*The data about bank transactions consists of a sequence of transactions: the information of each transaction has the following format:
                                                                    <from_account>   <to_account>   <money>   <time_point>   <atm>
In which:
•	<from_account>: the account from which money is transferred (which is a string of length from 6 to 20 )
•	<to_account>: the account which receives money in the transaction (which is a string of length from 6 to 20)
•	<money>: amount of money transferred in the transaction (which is an integer from 1 to 10000)
•	<time_point>: the time point at which the transaction is performed, it is a string under the format HH:MM:SS  (hour: minute: second)
•	<atm>: the code of the ATM where the transaction is taken (a string of length from 3 to 10)
Example: T00112233445 T001234002 2000 08:36:25 BIDV (at the ATM BIDV, account T00112233445 transfers 2000$ to account T001234002 at time point 08:36:25 (08 hour, 36 minutes, 25 seconds)
A transaction cycle of length k starting from account a1 is defined to be a sequence of distinct account a1, a2, …, ak  in which there are transactions from account a1 to a2, from a2 to a3, …, from ak to a1.
Write a program that process the following queries:
?number_transactions: compute the total number of transactions of the data
?total_money_transaction: compute the total amount of money of transactions
?list_sorted_accounts: compute the sequence of bank accounts (including sending and receiving accounts) appearing in the transaction (sorted in an increasing (alphabetical) order)
?total_money_transaction_from <account>: compute the total amount of money transferred from the account <account>
?inspect_cycle <account> k : return 1 if there is a transaction cycle of length k, starting from <account>, and return 0, otherwise
Input (stdin)
The input consists of 2 blocks of information: the data block and the query block
•	The data block consists of lines:
o	Each line contains the information about a transaction described above
o	The data is terminated by a line containing #
•	The query block consists of lines:
o	Each line is a query described above
o	The query block is terminated by a line containing #

Output (stdout)
•	Print to stdout (in each line) the result of each query described above

Example
Input
T000010010 T000010020 1000 10:20:30 ATM1
T000010010 T000010030 2000 10:02:30 ATM2
T000010010 T000010040 1500 09:23:30 ATM1
T000010020 T000010030 3000 08:20:31 ATM1
T000010030 T000010010 4000 12:40:00 ATM2
T000010040 T000010010 2000 10:30:00 ATM1
T000010020 T000010040 3000 08:20:31 ATM1
T000010040 T000010030 2000 11:30:00 ATM1
T000010040 T000010030 1000 18:30:00 ATM1
#
?number_transactions
?total_money_transaction
?list_sorted_accounts
?total_money_transaction_from T000010010
?inspect_cycle T000010010 3
#
Output
9
19500
T000010010 T000010020 T000010030 T000010040
4500
1
*/

#include <bits/stdc++.h>
using namespace std;

struct Transaction {
    string from_account;
    string to_account;
    int money;
    string time_point;
    string atm;
};

bool findCycle(const unordered_map<string, vector<string>>& graph, const string& start_account, int k,int depth, set<string>& visited) {
    
    if (depth == k) {
        return true;
    }

    visited.insert(start_account);

    for (const string& next_account : graph.at(start_account)) {
        if (next_account == start_account && depth == k - 1) { 
            return true;
        }
        if (visited.find(next_account) == visited.end()) { 
            if (findCycle(graph, next_account, k, depth + 1, visited)) {
                return true;
            }
        }
    }

    visited.erase(start_account); 
    return false;
}

int main() {
    vector<Transaction> transactions;
    unordered_map<string, int> total_money_from;
    unordered_map<string, vector<string>> graph;
    set<string> all_accounts;
    int total_money_transaction = 0;

    string line;
    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        Transaction transaction;
        iss >> transaction.from_account >> transaction.to_account >> transaction.money >> transaction.time_point >> transaction.atm;

        transactions.push_back(transaction);
        total_money_transaction += transaction.money;

        total_money_from[transaction.from_account] += transaction.money;
        graph[transaction.from_account].push_back(transaction.to_account);

        all_accounts.insert(transaction.from_account);
        all_accounts.insert(transaction.to_account);
    }

    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        string query;
        iss >> query;

        if (query == "?number_transactions") {
            cout << transactions.size() << endl;

        } else if (query == "?total_money_transaction") {
            cout << total_money_transaction << endl;

        } else if (query == "?list_sorted_accounts") {
            for (const auto& account : all_accounts) {
                cout << account << " ";
            }
            cout << endl;

        } else if (query == "?total_money_transaction_from") {
            string account;
            iss >> account;
            cout << total_money_from[account] << endl;

        } else if (query == "?inspect_cycle") {
            string account;
            int k;
            iss >> account >> k;

            set<string> visited;
            cout << findCycle(graph, account, k, 0, visited) << endl;
        }
    }

    return 0;
}