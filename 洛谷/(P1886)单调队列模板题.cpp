#include<stdio.h>
int k , n;
long long int a[100010];
long long int q[100010] , p[100010];
int main()
{
    scanf("%d %d",&n,&k);
    for(int i = 1;i <= n;i++)
    scanf("%lld",&a[i]);
    int head = 1 , tail = 0;
    for(int i = 1;i <= n;i++)/*先利用单调递增队列求个最小值*/
    {
        while (head <= tail && q[tail] >= a[i])
        {
            tail--;
        }
        q[++tail] = a[i];
        p[tail] = i;/*注意上一行操作已经让tail增加了，此处tail即为空的，直接赋值即可*/
        while (p[head] <= i - k)
        {
            head++;
        }
        if(i >= k)
        printf("%d ",q[head]);
    }
    printf("\n");
    head = 1 , tail = 0;
    for(int i = 1;i <= n;i++)/*先利用单调递减队列求个最小值*/
    {
        while (head <= tail && q[tail] <= a[i])
        {
            tail--;
        }
        q[++tail] = a[i];
        p[tail] = i;/*注意上一行操作已经让tail增加了，此处tail即为空的，直接赋值即可*/
        while (p[head] <= i - k)
        {
            head++;
        }
        if(i >= k)
        printf("%d ",q[head]);
    }
    return 0;
}