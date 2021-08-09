#include<stdio.h>
struct node
{
    int deep;
    int fa;
}tree[200];
int wide[200] = {0};
int main()
{
    int depth = 1, width = 0;
    int n , u , v;
    scanf("%d",&n);
    tree[1].deep = 1;//�Ѹ��ڵ��ʼ��һ��
    wide[1] = 1;
    for(int i = 1;i < n;i++)
    {
        scanf("%d %d",&u,&v);
        tree[v].fa = u;
        tree[v].deep = tree[u].deep + 1;
        if(tree[v].deep > depth)
        depth = tree[v].deep;//Ѱ��������
        wide[tree[v].deep]++;//��¼�ò�����
    }
    scanf("%d %d",&u,&v);//����Ҫ���ҵĽ��
    for(int i = 1;i <= depth;i++)
    width = width > wide[i] ? width : wide[i];//������ȸ����
    printf("%d\n",depth);
    printf("%d\n",width);
    if(u == v)
    {
        printf("0");
        return 0;
    }
    int d1 = 0 , d2 = 0;//d1����u�ߵľ��룬d2����v�ߵ�
    while (tree[u].fa != tree[v].fa)
    {
        if(tree[u].deep > tree[v].deep)
        {
            d1++;
            u = tree[u].fa;
        }
        if(tree[u].deep < tree[v].deep)
        {
            d2++;
            v = tree[v].fa;
        }
        if(tree[u].fa == v)
        {
            printf("%d",(d1+1)*2);
            return 0;
        }
        if(tree[v].fa == u)
        {
            printf("%d",d2+1);
            return 0;
        }
        if(tree[u].deep == tree[v].deep && tree[u].fa != tree[v].fa)
        {
            d1++;
            d2++;
            u = tree[u].fa;
            v = tree[v].fa;
        }
    }
    printf("%d",((d1 + 1) * 2 + d2 + 1));
    return 0;
}