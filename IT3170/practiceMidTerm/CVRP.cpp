#include <bits/stdc++.h>

using namespace std;

int c[15][15], s[7][15], d[15], vi[15] = {};
bool conf[15][15];
int n,m, kni, k, ki, q, mn = 1e6, p = 0, cmin = 1e6, c0min = 1e6;

bool check(int point , int vehicle){
    int j=-1;
    while( s[vehicle][++j]){
        if(conf[point][s[vehicle][j]]) return false;
    }
    return true;
}

int cal(){
    int dis = (n - p) * cmin, dii = 0;
    for(int i = 1; i <= n; ++i)
        if(!vi[i])
            dii += d[i];
    for(int i = 1; i <= k; ++i){
        int j = -1, ci = c[0][s[i][0]], di = 0;
        while(s[i][++j]){
            ci += c[s[i][j]][s[i][j+1]];
            di += d[s[i][j]];
        }
        if(i >= ki){
            ci += c0min - c[s[i][j-1]][0];
            dii += di % q;
        }
        dis += ci * ((di + q - 1) / q);
    }
    if(dii > q * (k + 1 - ki))
        dis += 2 * c0min + cmin;
    return dis;
}

void X(){
    if(p == n){
        int dis = 0;
        for(int i = 1; i <= k; ++i){
            int j = -1, ci = c[0][s[i][0]], di = 0;
            while(s[i][++j]){
                ci += c[s[i][j]][s[i][j+1]];
                di += d[s[i][j]];
            }
            dis += ci * ((di + q - 1) / q);
        }
        if(dis < mn)
            mn = dis;
        return;
    }
    if(ki < k){
        int tmp = kni;
        ++ki;
        kni = 1;
        X();
        --ki;
        kni = tmp;
    }
    for(int i = 1; i <= n; ++i)
        if(!vi[i] && check(i,ki)){
            s[ki][kni++] = i;
            ++p;
            vi[i] = 1;
            if(cal() < mn)
                X();
            vi[i] = 0;
            --p;
            s[ki][--kni] = 0;
        }
}

void Y(int a){
    if(a > k){
        p = k;
        ki = 1;
        kni = 1;
        X();
        return;
    }
    for(int i = s[a-1][0] + 1; i <= n; i++){
        s[a][0] = i;
        vi[i] = 1;
        Y(a + 1);
        vi[i] = 0;
    }
}

int main(){
    cin >> n >> k >> q;
    for(int i = 1; i <= n; i++)
        scanf("%d", &d[i]);
    for(int i = 0; i <= n; i++){
        scanf("%d", &c[i][0]);
        if(c[i][0])
            c0min = min(c[i][0], c0min);
        for(int j = 1; j <= n; j++){
            scanf("%d", &c[i][j]);
            if(c[i][j])
                cmin = min(c[i][j], cmin);
        }
    }
    cin>> m;
    memset(conf,false, sizeof(conf));
    for( int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        conf[a][b]=true;
        conf[b][a]=true;
    }
    ++k;
    while(--k){
        Y(1);
    }
    cout << mn;
}


