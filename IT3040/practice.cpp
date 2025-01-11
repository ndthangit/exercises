#include<bits/stdc++.h>
using namespace std;
struct ban{
    string masp, maloai;
    double giathue;
    string hinhdang;
    double thanhtien;

};
vector<ban> dsban;

void nhapds(){
    dsban.clear();
    cout<< setfill('-');
    cout<< left;
    cout<< setw(15)<< "tuoi"<< endl;
}

void inds(){
     cout<< "ds";
}

int main(){

    int control= -1;
    while( true){
        cin>> control;
        switch(control){
            case 1: {nhapds(); break;}
            case 2: inds();
            case 0: return 0;
            default: {
                cout << "Lua chon ban nhap khong dung! moi ban nhap lai!";
                break;
            }
        }
    }
}
