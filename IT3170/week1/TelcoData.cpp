/*
Write a C program to perform some queries on a telco data (comming from stdin) with the following format:
The first block of data consists of lines (terminated by a line containing #), each line (number of lines can be up to 100000) is under the form:
        call <from_number> <to_number> <date> <from_time> <end_time>
which is a call from the phone number <from_number> to a phone number <to_number> on <date>, and starting at time-point <from_time>, terminating at time-point <end_time>
<from_number> and <to_number> are string of 10 characters (a phone number is correct if it contains only digits 0,1,...,9, otherwise, the phone number is incorrect)
<date> is under the form YYYY-MM-DD (for example 2022-10-21)
<from_time> and <to_time> are under the form hh:mm:ss (for example, 10:07:23)

The second block consists of queries (terminated by a line containing #), each query in a line (number of lines can be up to 100000) and belongs to one of the following types:
?check_phone_number: print to stdout (in a new line) value 1 if no phone number is incorrect
?number_calls_from <phone_number>: print to stdout (in a new line) the number of times a call is made from <phone_number>
?number_total_calls: print to stdout (in a new line) the total number of calls of the data
?count_time_calls_from <phone_number>: print to stdout (in a new line) the total time duration (in seconds) the calls are made from <phone_number>

Example
Input
call 0912345678 0132465789 2022-07-12 10:30:23 10:32:00
call 0912345678 0945324545 2022-07-13 11:30:10 11:35:11
call 0132465789 0945324545 2022-07-13 11:30:23 11:32:23
call 0945324545 0912345678 2022-07-13 07:30:23 07:48:30
#
?check_phone_number
?number_calls_from 0912345678
?number_total_calls
?count_time_calls_from 0912345678
?count_time_calls_from 0132465789
#

Output
1
2
4
398
120*/
#include <bits/stdc++.h>
using namespace std;

struct Call
{
    string from_number;
    string to_number;
    string date;
    string from_time;
    string end_time;
};

bool checkPhone(string phone)
{
    if (phone.size() != 10)
        return false;
    for (char c : phone)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

int time(string stime){
    int h = ((stime[0]-'0')*10 + stime[1]-'0');
    int p= ((stime[3]-'0')*10 + stime[4]-'0');
    int s= (stime[6]-'0')*10 + stime[7]-'0';
    return 3600*h + 60*p + s;
}

int main()
{
    vector<Call> calls;
    string line;
    int incorrectPhone = 0;
    map<string, int> callsFrom;
    int totalCalls = 0;
    map<string,int> timeCalls;

    while (getline(cin, line) && line != "#")
    {
        stringstream ss(line);
        string type;
        ss >> type;
        if (type == "call")
        {
            Call call;
            ss >> call.from_number >> call.to_number >> call.date >> call.from_time >> call.end_time;
            calls.push_back(call);
            if (!checkPhone(call.from_number))
                incorrectPhone++;
            callsFrom[call.from_number]++;
            totalCalls++;
            timeCalls[call.from_number] += time(call.end_time) - time(call.from_time);
        }
    }
    while (getline(cin, line) && line != "#")
    {
        stringstream ss(line);
        string type;
        ss >> type;
        if (type == "?check_phone_number")
        {
            cout << (incorrectPhone == 0) << endl;
        }
        else if(type == "?number_calls_from")
        {
            string phone;
            ss >> phone;
            cout << callsFrom[phone] << endl;
        }
        else if(type == "?number_total_calls")
        {
            cout<< totalCalls << endl;
        }
        else if(type == "?count_time_calls_from")
        {
            string phone;
            ss >> phone;
            cout << timeCalls[phone] << endl;
        }
    }
    return 0;
}