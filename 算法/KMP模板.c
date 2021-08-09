#include<stdio.h>
#include<string.h>
int kmp[1000010];/*失配数组*/
int main()
{
    int j = 0;
    char a[1000010];/*文本串*/
    char b[1000010];/*模式串*/
    scanf("%s",a+1);
    scanf("%s",b+1);
    int la = strlen(a+1);
    int lb = strlen(b+1);
    kmp[0] = kmp[1] = 0;
    for(int i = 2;i <= lb;i++)/*初始化kmp数组，其实全局变量已经默认初始化为0，此处只是说明*/
    {
        while(j && b[i] != b[j + 1])
        j = kmp[j];
        if(b[i] == b[j + 1])
        j++;
        kmp[i] = j;
    }
    j = 0;//注意将j的值重新初始化！！！
    for(int i = 1;i <= la;i++)
    {
        while (j > 0 && a[i] != b[j + 1])
        {
            j = kmp[j];
        }
        if(a[i] == b[j + 1])
        j++;
        if(j == lb)
        {
            printf("%d\n",i - j + 1);
            j = kmp[j];//匹配成功后模式串返回最初的位置，重新寻找新的匹配
        }
    }
    for(int i = 1;i <= lb;i++)
    printf("%d ",kmp[i]);
    return 0;
}