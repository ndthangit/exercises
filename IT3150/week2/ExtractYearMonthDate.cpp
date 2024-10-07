#include<bits/stdc++.h>
using namespace std;
int getYear(string input){
    return 1000*(input[0]-'0') + 100*(input[1]-'0') + 10*(input[2]-'0') + input[3]-'0';
}
int getMonth(string input){
    return 10*(input[5]-'0') + input[6]-'0';
}
int getDate(string input){
    return 10*(input[8]-'0') + input[9]-'0';
}
void solve(string input){
    if(input[4]!='-' || input[7] !='-') cout<<"INCORRECT";
    else{
        int year, month, date;
        year = getYear(input);
        month =getMonth(input);
        date =getDate(input);
        if( month>0 && month<13 && date <32){

            cout<< year <<" "<< month<<" "<< date;
        }
        else cout<<"INCORRECT";
    }

}
int main(){
    string input;
    cin>>input;
    solve(input);
    return 0;

}