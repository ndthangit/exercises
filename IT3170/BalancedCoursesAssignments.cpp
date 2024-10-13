/*
At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way.
The department D has m teachers T={1,2,...,m} and n courses C={1,2,...,n}.
Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her specialization.
We known a list of pairs of conflicting two courses that cannot be assigned to the same teacher as these courses
have been already scheduled in the same slot of the timetable. The load of a teacher is the number of courses assigned to her/him.
How to assign n courses to m teacher such that each course assigned to a teacher is in his/her preference list,
no two conflicting courses are assigned to the same teacher, and the maximal load is minimal.
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
bool conf[40][40];
vector<vector<int>> tech;
vector<int> taught;
vector<int> tech_classes;
int minOfMaxCourses;

int n,m;// m teacher(1,m) n course(1,n)

bool check(int course, int teacher){
    if (find(tech[teacher].begin(), tech[teacher].end(), course) == tech[teacher].end())  //O(N)
        return false;

    for (int i = 1; i <= n; ++i) {    // O(N)
        if (taught[i] == teacher && conf[course][i])
            return false;
    }

    return true;
}
void deliver( int course){
    if(course == n+1){
        int curMax = *max_element(tech_classes.begin(), tech_classes.end());
        minOfMaxCourses= min(minOfMaxCourses, curMax);
        return;
    }
    for(int i=1; i<= m;i++){
        if(check(course, i)){
            taught[course]= i;
            tech_classes[i]++;

            int curMax = *max_element(tech_classes.begin(), tech_classes.end());

            if(curMax>minOfMaxCourses){
                tech_classes[i]--;
                taught[course]= 0;
                return;
            }
            else deliver(course+1);

            tech_classes[i]--;
            taught[course]= 0;
        }
    }
}

int main(){

    for(int i=0;i<40;i++){
        for(int j=0;j<40;j++){
           conf[i][j]= false;
        }
    }
    cin>>m>>n;
    tech.resize(m+1);
    tech_classes.resize(m+1,0);
    taught.resize(n+1,0);
    int num;
    for (int teacher = 1; teacher <= m; ++teacher) {
        cin >> num;
        tech[teacher].resize(num);
        for (int i = 0; i < num; ++i) {
            cin >> tech[teacher][i];
        }
    }

    int k;
    cin >> k;
    int course1, course2;
    for (int i = 0; i < k; ++i) {
        cin >> course1 >> course2;
        conf[course1][course2] =true ;
        conf[course2][course1] = true;
    }

    minOfMaxCourses=999;
    deliver(1);
    cout<< minOfMaxCourses;
    return 0;
}
