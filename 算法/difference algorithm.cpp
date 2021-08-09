#include<stdio.h>
int main()
{
    int n , p , z , x , y;
    scanf("%d %d",&n,&p);
    int a[n+1] , d[n+1];
    int i;
    a[0] = 0;
    for(i = 1;i <= n;i++)
    scanf("%d",&a[i]);
    for(i = 1;i <= n;i++) 
    d[i] = a[i] - a[i - 1];
    while(p--)
    {
        scanf("%d %d %d", &x , &y , &z);
        d[x] += z;
        d[y + 1] -= z;
    }
    int min;
    for(i = 1;i <= n;i++)
    {
        a[i] = a[i - 1] + d[i];
        if(i == 1)
        min = a[i];
        if(a[i] < min)
        min = a[i];
    }
    printf("%d",min);
}