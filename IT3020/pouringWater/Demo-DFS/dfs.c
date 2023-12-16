#include <stdio.h>
#define MAX 100
typedef  int dothi[MAX][MAX];

int sodinh = 12;
int visited[MAX];
void hienthi_graphviz(dothi G);
void explore(dothi G, int v);
void dfs(dothi G);


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
    //explore(G, 10);
    dfs(G);
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
void explore(dothi G, int v)
{
    visited[v] = 1;
    for (int u = 0; u < sodinh; u++)
    {
        if (G[v][u] == 1)
            if (visited[u]!=1) {
                printf("%d--%d;\n", v, u);
                explore(G, u);
            }
    }
}

void dfs(dothi G)
{
    printf("graph dfs{\n");

    for (int v=0; v < sodinh; v++)
        visited[v] = 0;
    
    for (int v=0; v < sodinh; v++)
        if (visited[v] == 0)
            explore(G, v);
    
    printf("}\n");
}
