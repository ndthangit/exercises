/*data about submission of a programming contest consists a sequence of lines, each line has the following information:
                                                      <UserID> <ProblemID> <TimePoint> <Status> <Point>
in which the user <UserID> submits his/her code to solve the problem <ProblemID> at time-point <TimePoint>, and gets status <Status> and point <Point>
<UserID>: string of length from 3 to 10
<ProblemID>: string under the format Pxy where x, y are digits 0,1,...,9 (for example P03, P10)
<TimePoint>: string representing time-point with the format HH:MM:SS (for example, 09:45:20 means the time-point 9 hour 45 minutes 20 seconds)
<Status>: string with two cases (ERR, OK)
<Point>: integer from {0, 1, 2, ..., 10}

A user can submit the code for solving each problem several time. The point that the user gets for a problem is the maximal point among the submissions for that problem.

Perform a sequence of queries of following types:
?total_number_submissions: return the number of submissions of the contest
?number_error_submision: return the number of submissions having status ERR
?number_error_submision_of_user <UserID>: return the number of submission having status ERR of user <UserID>
?total_point_of_user <UserID>: return the total point of user <UserID>
?number_submission_period <from_time_point> <to_time_point>: return the number of submissions in the period from <from_time_point> to <to_time_point> (inclusive)

Input
The input consists of two blocks of data:
The first block is the operational data, which is a sequence of lines (number of lines can be up to 100000), each line contains the information of a submission with above format .The first block is terminated with a line containing the character #
The second block is the query block, which is a sequence of lines (number of lines can be up to 100000), each line is a query described above. The second block is terminated with a line containing the character #

Output
Write in each line, the result of the corresponding query

Example
Input
U001 P01 10:30:20 ERR 0
U001 P01 10:35:20 OK 10
U001 P02 10:40:20 ERR 0
U001 P02 10:55:20 OK 7
U002 P01 10:40:20 ERR 0
U001 P01 11:35:20 OK 8
U002 P02 10:40:20 OK 10
#
?total_number_submissions
?number_error_submision
?number_error_submision_of_user U002
?total_point_of_user U001
?number_submission_period 10:00:00 11:30:45
#


Output
7
3
1
17
6
*/
#include <bits/stdc++.h>

using namespace std;

struct Submission {
    string userID;
    string problemID;
    string timePoint;
    string status;
    int point;
};

int main() {
    vector<Submission> submissions;
    map<string, map<string, int>> userProblemMaxPoints;
    string line;

    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        Submission submission;
        ss >> submission.userID >> submission.problemID >> submission.timePoint >> submission.status >> submission.point;
        submissions.push_back(submission);
        if (submission.status == "OK") {
            userProblemMaxPoints[submission.userID][submission.problemID] = max(userProblemMaxPoints[submission.userID][submission.problemID], submission.point);
        }
    }

    int totalSubmissions = submissions.size();
    int errorSubmissions = 0;
    map<string, int> userErrorCount;
    map<string, int> userTotalPoints;

    sort(submissions.begin(), submissions.end(), [](const Submission& a, const Submission& b) {
        return a.timePoint < b.timePoint;
    });

    auto findFirstIndex = [&](const string& time) {
        return lower_bound(submissions.begin(), submissions.end(), time, [](const Submission& sub, const string& time) {
            return sub.timePoint < time;
        }) - submissions.begin();
    };

    auto findLastIndex = [&](const string& time) {
        auto it = upper_bound(submissions.begin(), submissions.end(), time, [](const string& time, const Submission& sub) {
            return time < sub.timePoint;
        });
        return it == submissions.begin() ? -1 : it - submissions.begin() - 1;
    };

    for (const auto &submission : submissions) {
        if (submission.status == "ERR") {
            errorSubmissions++;
            userErrorCount[submission.userID]++;
        }
    }

    for (const auto &user : userProblemMaxPoints) {
        int totalPoints = 0;
        for (const auto &problem : user.second) {
            totalPoints += problem.second;
        }
        userTotalPoints[user.first] = totalPoints;
    }

    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "?total_number_submissions") {
            cout << totalSubmissions << endl;
        } else if (query == "?number_error_submision") {
            cout << errorSubmissions << endl;
        } else if (query == "?number_error_submision_of_user") {
            string userID;
            ss >> userID;
            cout << userErrorCount[userID] << endl;
        } else if (query == "?total_point_of_user") {
            string userID;
            ss >> userID;
            cout << userTotalPoints[userID] << endl;
        } else if (query == "?number_submission_period") {
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
    }

    return 0;
}
