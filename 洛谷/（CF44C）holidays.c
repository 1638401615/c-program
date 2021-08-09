#include<stdio.h>
/*错误示范：桶排序解
int main()
{
    int a[100] , b[100];
    int i , j , n , m;
    int count[100] = {0};
    scanf("%d %d",&n,&m);
    for(i = 1;i <= m;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        for(j = a[i];j <= b[i];j++)
        count[j]++;
    }
    for(i = 1;i <= n;i++)
    {
        if(count[i] != 1)
        {
            printf("%d %d",i,count[i]);
            return 0;
        }
    }
    printf("OK");
    return 0;
}*/
/*正确解法：差分法*/
int main()
{
    int i , j , n , m;
    int cf[110] = {0};
    int x , y;
    scanf("%d %d",&n,&m);
    for(i = 1;i <= m;i++)
    {
        scanf("%d %d",&x,&y);
        cf[x]++;
        cf[y+1]--;
    }
    for(j = 1;j <= n;j++)
    {
        cf[j] += cf[j -1];
        if(cf[j] != 1)
        {
            printf("%d %d",j,cf[j]);
            return 0;
        }
    }
    printf("OK");
    return 0;
}