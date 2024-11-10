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

int total_transactions = 0;
int total_money_transaction = 0;
map<string, int> from_transactions;
set<string> unique_accounts;
unordered_map<string, vector<string>> graph;

bool inspect_cycle_k(const string &start, const string &currentAccount, int k, int depth, set<string> visited)
{
    if (depth == k)
    {
        return currentAccount == start;
    }
    visited.insert(currentAccount);

    for (const auto &neighbor : graph[currentAccount])
    {
        if (neighbor == start && depth + 1 == k)
            return true;

        if (visited.find(neighbor) == visited.end())
            if (has_cycle_of_length_k(start, neighbor, k, depth + 1, visited))
                return true;
    }

    visited.erase(currentAccount);
    return false;
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        if (line == "#")
            break;

        stringstream ss(line);
        string from_account, to_account, time_point, atm;
        int money;
        ss >> from_account >> to_account >> money >> time_point >> atm;

        total_transactions++;
        total_money_transaction += money;

        from_transactions[from_account] += money;

        unique_accounts.insert(from_account);
        unique_accounts.insert(to_account);
        graph[from_account].push_back(to_account);
    }

    while (getline(cin, line))
    {
        if (line == "#")
            break;

        stringstream ss(line);
        string query;
        ss >> query;
        if (query == "?number_transactions")
        {
            cout << total_transactions << endl;
        }
        else if (query == "?total_money_transaction")
        {
            cout << total_money_transaction << endl;
        }
        else if (query == "?list_sorted_accounts")
        {
            for (const auto &account : unique_accounts)
                cout << account << " ";
            cout << endl;
        }
        else if (query == "?total_money_transaction_from")
        {
            string transaction_from_account;
            ss >> transaction_from_account;
            cout << from_transactions[transaction_from_account] << endl;
        }
        else if (query == "?inspect_cycle")
        {
            string inspect_cycle_account;
            int k;
            ss >> inspect_cycle_account >> k;

            set<string> visited;
            bool has_cycle = inspect_cycle_k(inspect_cycle_account, inspect_cycle_account, k, 0, visited);
            cout << (has_cycle ? 1 : 0) << endl;
        }
    }

    return 0;
}