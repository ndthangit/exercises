#include <stdio.h>
#define MAX 100
#define INF 100000

typedef  int dothi[MAX][MAX];

int Queue[MAX];
int dau=0;
int cuoi=-1;

int eject(){
    int x = Queue[dau];
    dau++;
    return x;
}

void inject(int v){
    Queue[++cuoi] = v;
}

int empty_queue()
{
    if (cuoi < dau) return 1;
    return 0;
}



int sodinh = 12;
int dist[MAX];
void hienthi_graphviz(dothi G);

void bfs(dothi G, int s)
{
    printf("graph bfs {\n");
    for (int u=0; u < sodinh; u++)
        dist[u] = INF;
    
    dist[s] = 0;
    inject(s);
    while (!empty_queue()){
        int u = eject();
        for (int v = 0; v < sodinh; v++){
            if (G[u][v] == 1)
                if (dist[v] == INF){
                    inject(v);
                    dist[v] = dist[u] + 1;
                    printf ("%d--%d;\n", u,v);
                }
        }
    }

    printf ("}\n");


}


int main(int argc, char const *argv[])
{
    
    dothi G = {
        //      A  B  C  D  E  F  G  H  I  J  K  L
        /*A*/  {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 
        /*B*/  {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        /*C*/  {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        /*D*/  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        /*E*/  {0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        /*F*/  {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*G*/  {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        /*H*/  {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        /*I*/  {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        /*J*/  {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        /*K*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        /*L*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };
    //hienthi_graphviz(G);
    bfs(G, 0);

    return 0;
}

void hienthi_graphviz(dothi G)
{
    printf("graph test{\n");
    for (int u=0; u < sodinh-1; u ++)
        for (int v=u+1; v< sodinh; v++)
            if (G[u][v]==1)
                printf("%d--%d;\n", u, v);
    printf("}\n");
}

