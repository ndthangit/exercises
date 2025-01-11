/*
At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way. The department D has m teachers T={1,2,...,m} and n courses C={1,2,...,n}. Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her specialization. We known a list of pairs of conflicting two courses that cannot be assigned to the same teacher as these courses have been already scheduled in the same slot of the timetable. The load of a teacher is the number of courses assigned to her/him. How to assign nn courses to mm teacher such that each course assigned to a teacher is in his/her preference list, no two conflicting courses are assigned to the same teacher, and the maximal load is minimal.
Input
The input consists of following lines
Line 1: contains two integer m and n (1≤m≤10, 1≤n≤30)
Line i+1: contains an positive integer k and k positive integers indicating the courses that teacher i can teach (∀i=1,…,m)
Line m+2: contains an integer k
Line i+m+2: contains two integer i and j indicating two conflicting courses (∀i=1,…,k)
Output
The output contains a unique number which is the maximal load of the teachers in the solution found and the value -1 if not solution found.
Example
Input
4 12
5 1 3 5 10 12
5 9 3 4 8 12
6 1 2 3 4 9 7
7 1 2 3 5 6 10 11
25
1 2
1 3
1 5
2 4
2 5
2 6
3 5
3 7
3 10
4 6
4 9
5 6
5 7
5 8
6 8
6 9
7 8
7 10
7 11
8 9
8 11
8 12
9 12
10 11
11 12

Output
3
*/

#include<bits/stdc++.h>
using namespace std;
int m,n,k;

vector<int> teach[12];
vector<vector<bool>> confic;
vector<bool> visited;
vector<int> num_teach;
vector<vector<bool>> teacher_course;

int minCourses= INT_MAX;

bool check( int course, int teacher)
{
    if(find(teach[teacher].begin(),teach[teacher].end(), course)== teach[teacher].end()) return false;

    if(visited[course]) return false;
    if(teacher_course[teacher][course]) return false;
    for( int i =1; i<=n; i++)
    {
        if(confic[course][i])
        {
            if(teacher_course[teacher][i]) return false;
        }
    }
    return true;
}

void solve(int course)
{
    if( course == n +1)
    {
        int cur = *max_element(num_teach.begin(),num_teach.end());
        minCourses = min( minCourses, cur);
        return;
    }
    for(int i =0; i<m; i++)
    {
        if( check(course, i))
        {

            visited[course]= true;
            num_teach[i]++;
            teacher_course[i][course]= true;

            solve(course+1);

            teacher_course[i][course]= false;
            visited[course]= false;
            num_teach[i]--;
        }

    }
}
int main()
{
    cin >> m >> n;

    confic.resize(n + 1, vector<bool>(n + 1, false));
    visited.resize(n + 1, false);
    num_teach.resize(m, 0);
    teacher_course.resize(m, vector<bool>(n + 1, false));

    for( int i=0; i<m; i++)
    {
        int num;
        cin>> num;
        for( int j=0; j<num; j++)
        {
            int a;
            cin>> a;
            teach[i].push_back(a);
        }
    }
    cin>>k;
    for( int i=0; i<k; i++)
    {
        int a,b;
        cin>> a>> b;
        confic[a][b]= true;
        confic[b][a]= true;
    }
    solve(1);
    cout<< minCourses;
    return 0;
}


