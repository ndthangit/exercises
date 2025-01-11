#include<bits/stdc++.h>
using namespace std;
// _Nguyễn Đức Thắng 20225089 -744463
int sopb_5089;
struct nhanvien
{
    string manv,hotennv,chucdanh;
    double hesoluong, luong, phucap,tongluong,cdphi;
    int namsinh;
};

struct phongban
{
    string ten,diachi;
    int sonv;
    double luongtoithieu, tongluong, tongchidoanphi;

    vector<nhanvien> dsnv;
};
vector<phongban> dspb;



void nhapds()
{
    cout<< "Ban da chon nhap ds phong ban nhan vien!"<< endl;
    for( int i=0; i<sopb_5089; i++)
    {
        phongban pb_5089;
        cout<< "Nhap thong tin phong ban thu "<< i+1<<":"<< endl;

        cout<< "\t Ten phong ban:";
        cin>> pb_5089.ten;

        cout<< "\t Dia chi:";
        cin>> pb_5089.diachi;

        cout<< "\t Luong toi thieu:";
        cin>> pb_5089.luongtoithieu;

        cout<< "\t So nhan vien:";
        cin>> pb_5089.sonv;

        cout<< "\t Nhap ds nhan vien:"<< endl;

        for( int j=0; j<pb_5089.sonv; j++)
        {
            nhanvien nv_5089;
            cout<<"\t Nhan vien thu "<< j+1<< endl;

            cout<< "\t\t Manv:";
            cin>> nv_5089.manv;

            cout<< "\t\t Ho ten nhan vien:";
            cin.ignore();
            getline(cin,nv_5089.hotennv);
//            cout<< nv_5089.hotennv;

            cout<< "\t\t Nhap nam sinh:";
            cin>> nv_5089.namsinh;

            cout<< "\t\t nhap hs luong:";
            cin>> nv_5089.hesoluong;
//            cout<< nv_5089.hesoluong;

            cout<< "\t\t nhap chuc danh:";
            cin>> nv_5089.chucdanh;

            nv_5089.luong = nv_5089.hesoluong * pb_5089.luongtoithieu;

            if( nv_5089.chucdanh == "GVCC")
            {
                nv_5089.phucap = 2000;
            }
            else if( nv_5089.chucdanh == "GVTS")
            {
                nv_5089.phucap = 1000;
            }
            else if(nv_5089.chucdanh == "GVC")
            {
                nv_5089.phucap = 1500;
            }
            else if( nv_5089.chucdanh == "CBKT")
            {
                nv_5089.phucap = 750;
            }
            else if( nv_5089.chucdanh == "CBHT")
            {
                nv_5089.phucap = 500;
            }
//            cout<< nv_5089.phucap;

            nv_5089.tongluong = nv_5089.phucap+nv_5089.luong;
            nv_5089.cdphi = nv_5089.tongluong/100;

            pb_5089.tongluong += nv_5089.tongluong;
            pb_5089.tongchidoanphi += nv_5089.cdphi;



            pb_5089.dsnv.push_back(nv_5089);

        }

        dspb.push_back(pb_5089);


    }

    cout<<"Ban da nhap thanh cong!Le Thi Hoa-744462-2024.1"<< endl;
    cout<<"Bam phim bat ky de tiep tuc!"<< endl;


}
void inds()
{

    cout<<"Le Thi Hoa-744462-2024.1"<<endl;
    cout<< endl;
    cout<<"Ban da chon xuat ds phong ban, !"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"--------"<<endl;



    for( int i=0; i< sopb_5089; i++)
    {
        cout<<"\tTen phong ban: "<< dspb[i].ten<<endl;
        cout<<"\tDia chi: "<< dspb[i].diachi<<endl;
        cout<<"\tLuong TT: "<< dspb[i].luongtoithieu<<endl;
        cout<<"\tTong luong PB: "<< dspb[i].tongluong<<endl;
        cout<<"\ttong CD phi: "<< dspb[i].tongchidoanphi<<endl;
        cout<<"Bang luong nhan vien"<<endl;

        cout<< left<< setw(10)<< "MaNV"<< setw(20)<< "HotenNV"<< setw(10)<<"Chucdanh"<< setw(10)<<"PCCD" << setw(10)<< "Hesol"<< setw(15)<< "Luong"<< setw(10)<< "SDP"<< setw(10)<<"Con nhan"<< endl;
        for( int j =0; j< dspb[i].dsnv.size(); j++)
        {
            cout<< left<< setw(10)<< dspb[i].dsnv[j].manv<< setw(20)<< dspb[i].dsnv[j].hotennv<< setw(10)<<dspb[i].dsnv[j].chucdanh<< setw(10)<<dspb[i].dsnv[j].phucap << setw(10)<<dspb[i].dsnv[j].hesoluong<< setw(15)<< dspb[i].dsnv[j].tongluong << setw(10)<< dspb[i].dsnv[j].cdphi<< setw(10)<<dspb[i].dsnv[j].tongluong- dspb[i].dsnv[j].cdphi<< endl;
        }

    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"--------"<<endl;

    cout<<"Bam phim bat ky de tiep tuc! Le Thi Hoa-744462-2024.1"<< endl;


}
int main()
{
    cout<< "Kip 12h30 tuan 17 ngay 28/12/2024"<< endl;
    cout<< "Kiem tra thuc hanh- quan ly nhan vien"<< endl;
    cout<< "Le Thi Hoa -744463-2024.1"<< endl;
    cout<< "Nhap so phong ban: ";
    cin>> sopb_5089;
    system("cls");
    while( true)
    {
        cout<< "Kip 12h30 tuan 17 ngay 28/12/2024"<< endl;
        cout<< "Le Thi Hoa -744463-2024.1"<< endl;
        cout<< "**CHUONG TRINH QUAN LY -Phong ban - nhan vien**"<< endl;
        cout<< "**1. Nhap cac phong ban**"<< endl;
        cout<< "**2. In ket qua ds phong ban va nhan vien**"<< endl;
        cout<< "**0. Thoat**"<< endl;
        cout<< "*******************************************"<< endl;
        cout<< "**         Nhap lua chon cua ban         **"<< endl;

        int controll;
        cin>> controll;

        switch(controll)
        {
        case 0:
        {
            cout<< endl;
            cout<< "Le Thi Hoa-744462-2024.1" <<endl;
            cout<< endl;
            cout<< "Ban da chon thoat chuong trinh!" <<endl;
            return 0;
        }
        case 1:
        {
            nhapds();
            break;
        }
        case 2:
        {
            inds();
            break;
        }
        default:
        {
            cout<<endl;
            cout<< "Khong co chuc nang nay!"<<endl;
            cout<<"Bam phim bat ky de tiep tuc! Le Thi Hoa-744462-2024.1"<< endl;


            break;
        }


        }



    }


}
