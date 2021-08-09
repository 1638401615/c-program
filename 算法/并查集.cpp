#include<stdio.h>
int fa[10001];
int rank[10001];
void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        rank[i] = 1;//按秩合并的初始化，记录该点为根节点的树的深度
    }
}
int find(int x)//查找
{
    if(x == fa[x])
        return x;
    else{
        fa[x] = find(fa[x]);  //路径压缩
        return fa[x];         //返回父节点
    }
}
void merge(int i, int j)//按秩合并
{
    int x = find(i), y = find(j);    //先找到两个根节点
    if (rank[x] <= rank[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (rank[x] == rank[y] && x != y)
        rank[y]++;                   //如果深度相同且根节点不同，则新的根节点的深度+1
}
int main()
{
    int n , m;
    int z , x , y;
    scanf("%d %d",&n,&m);
    init(n);
    for(int i = 1;i <= m;i++)
    {
        scanf("%d %d %d",&z,&x,&y);
        if(z == 1)
        merge(x , y);
        if(z == 2)
        {
            if(find(x) == find(y))
            printf("Y\n");
            else
            printf("N\n");
        }
    }
    return 0;
}