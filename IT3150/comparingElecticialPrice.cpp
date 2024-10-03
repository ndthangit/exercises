#include<bits/stdc++.h>
using namespace std;
float getOddPRice(float kwh){
    if (kwh <= 50) {
        return kwh * 1728;
    } else if (kwh <= 100) {
        return 50 * 1728 + (kwh - 50) * 1786;
    } else if (kwh <= 200) {
        return 50 * 1728 + 50 * 1786 + (kwh - 100) * 2074;
    } else if (kwh <= 300) {
        return 50 * 1728 + 50 * 1786 + 100 * 2074 + (kwh - 200) * 2612;
    } else if (kwh <= 400) {
        return 50 * 1728 + 50 * 1786 + 100 * 2074 + 100 * 2612 + (kwh - 300) * 2919;
    } else {
        return 50 * 1728 + 50 * 1786 + 100 * 2074 + 100 * 2612 + 100 * 2919 + (kwh - 400) * 3015;
    }
}
float getNewPrice(float kwh){
    if (kwh <= 100) {
        return kwh * 1728;
    } else if (kwh <= 200) {
        return 100 * 1728 + (kwh - 100) * 2074;
    } else if (kwh <= 400) {
        return 100 * 1728 + 100 * 2074 + (kwh - 200) * 2612;
    } else if (kwh <= 700) {
        return 100 * 1728 + 100 * 2074 + 200 * 2612 + (kwh - 400) * 3111;
    } else {
        return 100 * 1728 + 100 * 2074 + 200 * 2612 + 300 * 3111 + (kwh - 700) * 3457;
    }
    
}

int main(){
    float kwh;
    cout << fixed << setprecision(2);
    cin>> kwh;
    cout<< (getNewPrice(kwh) - getOddPRice(kwh))*1.1;
    return 0;
}