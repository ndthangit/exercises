/*bai 1.8 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
#include <stdlib.h>
void allocate_mem(int ***mt_thangnd, int m_thangnd, int n_thangnd)
{
    // #Allocate memory for the matrix

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    *mt_thangnd = (int **)malloc(m_thangnd * sizeof(int *));

    for (int i = 0; i < m_thangnd; i++)
    {
        (*mt_thangnd)[i] = (int *)malloc(n_thangnd * sizeof(int));
    }
}
void input(int **mt_thangnd, int m_thangnd, int n_thangnd)
{
    // #Input elements of the matrix

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 0; i < m_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            scanf("%d", &mt_thangnd[i][j]);
        }
    }
}
void output(int **mt_thangnd, int m_thangnd, int n_thangnd)
{
    // # Print all elements of the matrix

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 0; i < m_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            printf("mt[%d][%d] = ", i,j);
        }
    }

    for (int i = 0; i < m_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            printf("%d ", mt_thangnd[i][j]);
        }
        printf("\n");
    }
}
int process(int **mt_thangnd, int m_thangnd, int n_thangnd)
{
    int tong_thangnd = 0;
    // # Calculate the sum of all even elements in the matrix

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 0; i < m_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            if (!(mt_thangnd[i][j] & 1))
                tong_thangnd += mt_thangnd[i][j];
        }
    }

    return tong_thangnd;
}
void free_mem(int **mt_thangnd, int m_thangnd)
{
    // # Free memory

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 0; i < m_thangnd; i++)
    {
        free(mt_thangnd[i]);
    }
    free(mt_thangnd);
}
int main()
{
    int m_thangnd, n_thangnd, **mt_thangnd;
    printf("Enter m, n = ");
    scanf("%d%d", &m_thangnd, &n_thangnd);
    allocate_mem(&mt_thangnd, m_thangnd, n_thangnd);
    input(mt_thangnd, m_thangnd, n_thangnd);
    output(mt_thangnd, m_thangnd, n_thangnd);
    printf("The sum of all even elements is %d", process(mt_thangnd, m_thangnd, n_thangnd));
    free_mem(mt_thangnd, m_thangnd);
    return 0;
}
/*bai 1.8 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
