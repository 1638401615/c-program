#include<stdio.h>
int s[100010] , h[100010] , p[100010];
int l[100010] , r[100010];
int main()
{
    int n , i , j , top = 0;
    int ans = 0;
    scanf("%d",&n);
    for(i = 1;i <= n;i++)
    {
        scanf("%d",&h[i]);
    }
    for(i = 1;i <= n;i++)/*Ѱ�ҵ�������h[i]����Сλ��*/
    {
        while(top != 0 && h[s[top]] < h[i])
        top--;
        if(top != 0)
        l[i] = s[top];
        else
        l[i] = 0;
        s[++top] = i;
    }
    top = 0;
    for(i = n;i >= 1;i--)/*Ѱ�ҵ��Ҳ�С��h[i]����Сλ��*/
    {
        while(top != 0 && h[p[top]] > h[i])
        top--;
        if(top != 0)
        r[i] = p[top];
        else
        r[i] = n + 1;
        p[++top] = i;
    }
    for(i = n;i >= 1;i--)
    {
        for(j = l[i] + 1;j < i;j++)
        {
            if(r[j] > i)
            {
                ans = ans > (i - j + 1) ? ans : (i - j + 1);
                break;
            }
        }
        if(i <= ans)/*�Ż����������������ǰ����ѭ��*/
        break;
    }
    printf("%d",ans);
    return 0;
}