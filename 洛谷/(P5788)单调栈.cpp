#include<stdio.h>
/*60分做法：暴力破解复杂度o(n^2)
int n;
void f(int i,int a[])
{
    if(i >= n)
    {printf("0 ");
    return;}
   for(int j = i + 1;j <= n;j++)
   {
       if(a[j] > a[i])
       {printf("%d ",j);
       return;}
   }
   printf("0 ");
   return;
}
int main()
{
    scanf("%d",&n);
    int a[maxn];
    int i;
    for(i = 1;i <= n;i++)
    scanf("%d",&a[i]);
    for(i = 1;i <= n;i++)
    f(i,a);
    return 0;
}*/
/*题目正确做法：单调栈*/
int main()
{
    int s[300005];
    int n;
    scanf("%d",&n);
    int a[n+1] , f[300005] = {0};
    for(int i = 1;i <= n;i++)
    scanf("%d",&a[i]);
    int top = 0;
    for(int i = n;i >= 1;i--)
    {
        while(top  && a[s[top]] <= a[i])
        top--;
        if(top == 0)
        f[i] = 0;
        else
        f[i] = s[top];
        s[++top] = i;
    }
    for(int i = 1;i <=n;i++)
    printf("%d ",f[i]);
    return 0;
}