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
    for(int i = 1;i <= n;i++)/*�����õ����������������Сֵ*/
    {
        while (head <= tail && q[tail] >= a[i])
        {
            tail--;
        }
        q[++tail] = a[i];
        p[tail] = i;/*ע����һ�в����Ѿ���tail�����ˣ��˴�tail��Ϊ�յģ�ֱ�Ӹ�ֵ����*/
        while (p[head] <= i - k)
        {
            head++;
        }
        if(i >= k)
        printf("%d ",q[head]);
    }
    printf("\n");
    head = 1 , tail = 0;
    for(int i = 1;i <= n;i++)/*�����õ����ݼ����������Сֵ*/
    {
        while (head <= tail && q[tail] <= a[i])
        {
            tail--;
        }
        q[++tail] = a[i];
        p[tail] = i;/*ע����һ�в����Ѿ���tail�����ˣ��˴�tail��Ϊ�յģ�ֱ�Ӹ�ֵ����*/
        while (p[head] <= i - k)
        {
            head++;
        }
        if(i >= k)
        printf("%d ",q[head]);
    }
    return 0;
}