#include<stdio.h>
int fa[10001];
int rank[10001];
void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        rank[i] = 1;//���Ⱥϲ��ĳ�ʼ������¼�õ�Ϊ���ڵ���������
    }
}
int find(int x)//����
{
    if(x == fa[x])
        return x;
    else{
        fa[x] = find(fa[x]);  //·��ѹ��
        return fa[x];         //���ظ��ڵ�
    }
}
void merge(int i, int j)//���Ⱥϲ�
{
    int x = find(i), y = find(j);    //���ҵ��������ڵ�
    if (rank[x] <= rank[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (rank[x] == rank[y] && x != y)
        rank[y]++;                   //��������ͬ�Ҹ��ڵ㲻ͬ�����µĸ��ڵ�����+1
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