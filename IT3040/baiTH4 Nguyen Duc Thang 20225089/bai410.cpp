/*bai 4.10 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include<bits/stdc++.h>

using namespace std;
//*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/


const int N_thangnd = 10000;

// Mảng chứa các văn bản, mỗi văn bản là một vector các từ
vector<string> doc_thangnd[N_thangnd];

// Mảng lưu số lần xuất hiện của từng từ trong từng văn bản
map<string, int> f_thangnd[N_thangnd];

// Map lưu số văn bản chứa mỗi từ
map<string, int> df_thangnd;

// Mảng lưu giá trị lớn nhất của số lần xuất hiện của từng từ trong từng văn bản, biến n lưu số văn bản
int maxf_thangnd[N_thangnd], n_thangnd;

 // Hàm tính TF
double TF(string t_thangnd, int d_thangnd){
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (f_thangnd[d_thangnd][t_thangnd] == 0) return 0;
    return 0.5 + 0.5 * f_thangnd[d_thangnd][t_thangnd] / maxf_thangnd[d_thangnd];     
}


// Hàm tính IDF
double IDF(string t_thangnd){
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return log2(1.0 * n_thangnd / df_thangnd[t_thangnd]);    
}


// Hàm tính điểm số
double score(string t_thangnd, int d_thangnd){
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (df_thangnd.count(t_thangnd) == 0) return 0;
    return TF(t_thangnd, d_thangnd) * IDF(t_thangnd);     
}

int main(){
    ios_base :: sync_with_stdio (false);
    cin.tie(0); cout.tie(0);

    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Unable to open input file" << endl;
        return 1;
    }

    infile >> n_thangnd;     // Nhập số văn bản
    for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++){
        string t_thangnd;
        infile >> t_thangnd;
        string w_thangnd;
        map<string, int> d_f_thangnd;
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

        for (char c_thangnd : t_thangnd){
            if (c_thangnd != ',') w_thangnd.push_back(c_thangnd);
            else {
                d_f_thangnd[w_thangnd]++;

                // Cập nhật số lần xuất hiện của từ t_thangnd và số văn bản chứa từ t_thangnd
                if(d_f_thangnd[w_thangnd] == 1) df_thangnd[w_thangnd]++;
                doc_thangnd[i_thangnd].push_back(w_thangnd);
                f_thangnd[i_thangnd][w_thangnd]++;
                w_thangnd = "";
                continue;
            }
        }
        d_f_thangnd[w_thangnd]++;
        if (d_f_thangnd[w_thangnd] == 1) df_thangnd[w_thangnd]++;
        doc_thangnd[i_thangnd].push_back(w_thangnd);
        f_thangnd[i_thangnd][w_thangnd]++;

        for (auto it_thangnd : f_thangnd[i_thangnd]){

            // Tìm giá trị lớn nhất của số lần xuất hiện của từng từ trong văn bản i_thangnd
            maxf_thangnd[i_thangnd] = max(maxf_thangnd[i_thangnd], it_thangnd.second);
        }
    }

    int q_thangnd;
    infile >> q_thangnd;     // Nhập số truy vấn
    while (q_thangnd--){
        vector<string> query_thangnd;
        string t_thangnd;
        infile >> t_thangnd;
        string w_thangnd;
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

        for (char c_thangnd : t_thangnd){
            if(c_thangnd != ',') w_thangnd.push_back(c_thangnd);
            else{
                query_thangnd.push_back(w_thangnd);
                w_thangnd = "";
                continue;
            }
        }

        query_thangnd.push_back(w_thangnd);
        double temp_score_thangnd = -1e9;
        int document_thangnd = 0;
        int d_thangnd = 0;
        while (d_thangnd < n_thangnd){
            double total_score_thangnd = 0;
            /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

            for(string t_thangnd : query_thangnd){
                // Tính tổng điểm số của từng từ trong truy vấn đối với văn bản d_thangnd
                total_score_thangnd += score(t_thangnd, d_thangnd);     
            }
            d_thangnd++;

            if (total_score_thangnd > temp_score_thangnd){
                temp_score_thangnd = total_score_thangnd;
                document_thangnd = d_thangnd;
            }
        }
        cout << document_thangnd << '\n';     // In ra chỉ số của văn bản khớp với truy vấn
    }
}
/*bai 4.10 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/